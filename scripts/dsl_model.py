import ast
from dsl_engine import size_cost, bounding_box_cost, pixel_overlap_cost, value_cost
from dsl_dataset import execute_dsl
from dsl_rl import VOCAB
import math
from multiprocessing import Pool
import numpy as np
import os
import pandas as pd
import json
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch_geometric.data import Data
from torch_geometric.nn import GCNConv
from torch_geometric.nn import global_mean_pool
from typing import List, Tuple

Grid = Tuple[Tuple[int]]

scoreFunctions = [size_cost, bounding_box_cost, pixel_overlap_cost, value_cost]
scoreColumns = ["Grid size cost", "Bounding box cost", "Pixel overlap cost", "Value cost", "Total cost"]

def dataframe_to_cost_tensor(df):
    """
    df: pandas.DataFrame

    tensor [1, N_grids, 5]
    """

    values = df[scoreColumns].values

    tensor = torch.tensor(
        values,
        dtype=torch.float32
    )

    tensor = tensor.unsqueeze(0)

    return tensor

class CostEncoder(nn.Module):
    def __init__(
        self,
        input_dim=5,
        hidden_dim=64,
        d_model=256
    ):
        super().__init__()
        self.attn = nn.Sequential(

            nn.Linear(d_model, d_model),
            nn.Tanh(),

            nn.Linear(d_model, 1)
        )
        self.mlp = nn.Sequential(
            nn.Linear(input_dim, hidden_dim),
            nn.ReLU(),

            nn.Linear(hidden_dim, hidden_dim),
            nn.ReLU(),

            nn.Linear(hidden_dim, d_model)
        )

    def forward(self, cost_tensor):
        """
        cost_tensor: [B, N_grids, 5]

        z_cost: [B, d_model]
        """

        x = torch.log1p(cost_tensor)
        x = self.mlp(x)
        scores = self.attn(x)
        weights = torch.softmax(
            scores,
            dim=1
        )
        z_cost = (weights * x).sum(dim=1)

        return z_cost

class DSLProgramEncoder(nn.Module):
    def __init__(
        self,
        vocab_size,
        d_model=256,
        hidden_dim=128
    ):
        super().__init__()

        self.embedding = nn.Embedding(
            vocab_size,
            hidden_dim
        )

        self.conv1 = GCNConv(
            hidden_dim,
            hidden_dim
        )

        self.conv2 = GCNConv(
            hidden_dim,
            hidden_dim
        )

        self.conv3 = GCNConv(
            hidden_dim,
            hidden_dim
        )

        self.proj = nn.Linear(
            hidden_dim,
            d_model
        )

    def forward(self, data):
        x = self.embedding(data.x)

        x = self.conv1(x, data.edge_index)
        x = F.relu(x)

        x = self.conv2(x, data.edge_index)
        x = F.relu(x)

        x = self.conv3(x, data.edge_index)
        x = F.relu(x)

        x = global_mean_pool(
            x,
            data.batch
        )

        z_prog = self.proj(x)

        return z_prog

class DSLGraphBuilder:
    def __init__(self, vocab):
        self.vocab = vocab
        self.node_features = []
        self.edges = []

    def add_node(self, token):
        idx = len(self.node_features)
        token_id = self.vocab.get(token, 0)
        self.node_features.append(token_id)

        return idx

    def visit(self, node, parent_idx=None):
        if isinstance(node, ast.Call):
            func_name = node.func.id
            current_idx = self.add_node(func_name)

            if parent_idx is not None:
                self.edges.append(
                    [parent_idx, current_idx]
                )

            for arg in node.args:
                self.visit(arg, current_idx)

            return current_idx
        elif isinstance(node, ast.Name):
            current_idx = self.add_node(node.id)

            if parent_idx is not None:
                self.edges.append(
                    [parent_idx, current_idx]
                )

            return current_idx
        elif isinstance(node, ast.Constant):
            token = str(node.value)

            current_idx = self.add_node(token)

            if parent_idx is not None:
                self.edges.append(
                    [parent_idx, current_idx]
                )

            return current_idx
        else:
            raise ValueError(
                f"Unsupported AST node: {type(node)}"
            )

    def build(self, program_str):
        tree = ast.parse(
            program_str,
            mode="eval"
        )

        self.visit(tree.body)

        x = torch.tensor(
            self.node_features,
            dtype=torch.long
        )

        if len(self.edges) == 0:
            edge_index = torch.empty(
                (2, 0),
                dtype=torch.long
            )
        else:
            edge_index = torch.tensor(
                self.edges,
                dtype=torch.long
            ).t().contiguous()

        return Data(
            x=x,
            edge_index=edge_index
        )

class ARCGridEncoder(nn.Module):
    def __init__(
        self,
        num_colors=10,
        d_model=256,
        cnn_dim=64,
    ):
        super().__init__()

        # 10 input
        # 10 output
        # 1 diff
        # 1 valid_mask
        in_channels = num_colors * 2 + 2

        self.conv_net = nn.Sequential(

            nn.Conv2d(
                in_channels,
                cnn_dim,
                3,
                padding=1
            ),
            nn.ReLU(),

            nn.Conv2d(
                cnn_dim,
                cnn_dim,
                3,
                padding=1
            ),
            nn.ReLU(),

            nn.Conv2d(
                cnn_dim,
                cnn_dim * 2,
                3,
                padding=1
            ),
            nn.ReLU(),

            nn.Conv2d(
                cnn_dim * 2,
                cnn_dim * 2,
                3,
                padding=1
            ),
            nn.ReLU(),
        )

        self.proj = nn.Linear(
            cnn_dim * 2,
            d_model
        )

    def forward(
        self,
        inp_grid,
        out_grid,
        valid_mask
    ):
        """
        inp_grid:   [B,H,W]
        out_grid:   [B,H,W]
        valid_mask: [B,H,W]
        """
        inp_oh = F.one_hot(
            inp_grid.long(),
            num_classes=10
        )
        out_oh = F.one_hot(
            out_grid.long(),
            num_classes=10
        )

        # [B,H,W,C] -> [B,C,H,W]
        inp_oh = inp_oh.permute(
            0, 3, 1, 2
        ).float()

        out_oh = out_oh.permute(
            0, 3, 1, 2
        ).float()
        diff = (
            inp_grid != out_grid
        ).float().unsqueeze(1)
        valid_mask = valid_mask.unsqueeze(1).float()
        x = torch.cat([
            inp_oh,
            out_oh,
            diff,
            valid_mask
        ], dim=1)
        x = self.conv_net(x)
        mask = valid_mask.float()
        x = x * mask
        x_sum = x.sum(dim=[2, 3])
        mask_sum = mask.sum(dim=[2, 3])
        x = x_sum / (mask_sum + 1e-6)
        z_grid = self.proj(x)

        return z_grid

class ARCContextEncoder(nn.Module):

    def __init__(self, d_model=256):
        super().__init__()

        self.grid_encoder = ARCGridEncoder(
            d_model=d_model
        )

        self.attn_pool = nn.Sequential(
            nn.Linear(d_model, 1)
        )

    def forward(self, inputs, outputs, masks):
        """
        inputs : [B, N, H, W]
        outputs: [B, N, H, W]
        masks: [B, N, H, W]

        z_grids: [B, d_model]
        """

        B, N, H, W = inputs.shape

        z_list = []

        for i in range(N):
            z_i = self.grid_encoder(
                inputs[:, i],
                outputs[:, i],
                masks[:, i]
            )

            z_list.append(z_i)

        # [B,N,D]
        z = torch.stack(z_list, dim=1)
        scores = self.attn_pool(z)  # [B,N,1]
        weights = torch.softmax(scores, dim=1)

        z_grids = (weights * z).sum(dim=1)

        return z_grids

def pad_grid(grid, max_h, max_w, pad_value=0):
    h = len(grid)
    w = len(grid[0])

    padded = [
        list(row) + [pad_value] * (max_w - w)
        for row in grid
    ]

    padded += [
        [pad_value] * max_w
        for _ in range(max_h - h)
    ]

    mask = [
        [1] * w + [0] * (max_w - w)
        for _ in range(h)
    ]

    mask += [
        [0] * max_w
        for _ in range(max_h - h)
    ]

    return padded, mask

def arc_pairs_to_tensors(arc_pairs: List[Tuple[Grid, Grid]]):
    """
    arc_pairs: List[(input_grid, output_grid)]

    inputs  -> [1, N, H, W]
    outputs -> [1, N, H, W]
    masks -> [1, N, H, W]
    """
    max_h = 0
    max_w = 0

    for inp, out in arc_pairs:
        max_h = max(
            max_h,
            len(inp),
            len(out)
        )

        max_w = max(
            max_w,
            len(inp[0]),
            len(out[0])
        )

    input_tensors = []
    output_tensors = []
    mask_tensors = []

    for inp, out in arc_pairs:
        inp_pad, mask = pad_grid(
            inp,
            max_h,
            max_w
        )

        out_pad, _ = pad_grid(
            out,
            max_h,
            max_w
        )

        input_tensors.append(
            torch.tensor(inp_pad)
        )

        output_tensors.append(
            torch.tensor(out_pad)
        )

        mask_tensors.append(
            torch.tensor(mask)
        )

    inputs = torch.stack(input_tensors)
    outputs = torch.stack(output_tensors)
    masks = torch.stack(mask_tensors)

    # [N,H,W] -> [1,N,H,W]
    inputs = inputs.unsqueeze(0)
    outputs = outputs.unsqueeze(0)
    masks = masks.unsqueeze(0)

    return inputs, outputs, masks

def programDf(program: str, pairs: List[Tuple[Grid, Grid]]) -> pd.DataFrame:
    scores: list = []
        
    for pair in pairs:
        O = execute_dsl(program, pair[0])

        score: list = [0] * len(scoreFunctions)

        for i in range(0, len(scoreFunctions)):
            a1 = 0
            a2 = 0

            try:
                a1 = np.array(O)
                a2 = np.array(pair[1])
                score[i] = scoreFunctions[i](a1, a2)
            except:
                score[i] = math.inf

            del a1
            del a2

        del O

        scores.append(score + [sum(score)])

    df = pd.DataFrame(scores, index = [f"grid{i+1}" for i in range(len(pairs))], columns = scoreColumns)

    del scores

    return df

def programCosts(targetProgram: str, programs: List[str], inputs: Tuple[Tuple[int]]) -> List[pd.DataFrame]:
    outputs: list = []
    
    for grid in inputs:
        outputs.append(execute_dsl(targetProgram, grid))
    
    pairs = list(zip(inputs, outputs))

    with Pool(os.cpu_count()) as pool:
        dfs = pool.starmap(programDf, [(program, pairs) for program in programs])
    
    return dfs

if (__name__ == "__main__"):
    with open("model_dataset.jsonl", "r") as f:
        lines = f.read().split("\n")

    modelDataset: dict = {}

    for line in lines:
        try:
            o = json.loads(line)
            modelDataset[o["program"]] = tuple([tuple(map(tuple, x)) for x in o["grids"]])
        except Exception:
            pass

    modelDataset["I"] = modelDataset[list(modelDataset.keys())[-1]]
    modelDataset = dict(sorted(modelDataset.items(), key = lambda x: (len(x[0]), x[0])))
    modelDataset = dict(list(modelDataset.items())[:100])

    builder = DSLGraphBuilder(VOCAB.token2id)
    gridModel = ARCContextEncoder(d_model=256)
    astModel = DSLProgramEncoder(
        vocab_size=len(VOCAB.token2id),
        d_model=256
    )
    costModel = CostEncoder(
        input_dim=5,
        d_model=256
    )

    for k, v in modelDataset.items():
        graph = builder.build(k)
        print(graph)
        graph.batch = torch.zeros(
            graph.x.size(0),
            dtype=torch.long
        )

        z = astModel(graph)
        print(z.shape)

        outputs: list = []
        
        for grid in v:
            outputs.append(execute_dsl(k, grid))
        
        pairs = list(zip(v, outputs))

        inputs, outputs, masks = arc_pairs_to_tensors(pairs)
        z_grids = gridModel(inputs, outputs, masks)

        print(z_grids.shape)

        costs = dict(zip(modelDataset.keys(), programCosts(k, modelDataset.keys(), v)))
        costs = sorted(costs.items(), key = lambda x: (tuple(-x[1].sum(axis = 0, skipna = False)), len(x[0]), x[0]))

        while (costs[0][0] != "I"):
            costs.pop(0)

        while (costs[-1][0] != k):
            costs.pop()

        df = costs[0][1]
        cost_tensor = dataframe_to_cost_tensor(df)
        z_cost = costModel(cost_tensor)
        print(z_cost.shape)

        costs = dict(costs)

        try:
            print(k)
            keys = list(costs.keys())
            print(keys[0], costs[keys[0]])
            print(keys[1], costs[keys[1]])
            print(keys[-2], costs[keys[-2]])
            print(keys[-1], costs[keys[-1]])
        except Exception:
            pass

        input("hit")

        del costs