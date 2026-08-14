import ast
import collections.abc
from connection import compatibleType
import datetime
from dsl_engine import size_cost, bounding_box_cost, pixel_overlap_cost, value_cost
from dsl_dataset import execute_dsl, isValidGrid
from dsl_rl import VOCAB
from dsl_tree import vocabulary, args, tree, Tree
import math
from multiprocessing import Pool
import numpy as np
import os
import pandas as pd
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch_geometric.data import Data
from torch_geometric.nn import GCNConv
from torch_geometric.nn import global_mean_pool
from typing import get_origin, get_args, Callable, List, Tuple

Grid = Tuple[Tuple[int]]
M: int = 5

scoreFunctions = [size_cost, bounding_box_cost, pixel_overlap_cost, value_cost]
scoreColumns = ["Total cost", "Grid size cost", "Bounding box cost", "Pixel overlap cost", "Value cost"]

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
        device: str = "cpu"
    ):
        super().__init__()

        # 10 input
        # 10 output
        # 1 diff
        # 1 valid_mask
        in_channels = num_colors * 2 + 2
        self.device = device

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
        ], dim=1).to(self.device)
        x = self.conv_net(x)
        mask = valid_mask.float().to(self.device)
        x = x * mask
        x_sum = x.sum(dim=[2, 3])
        mask_sum = mask.sum(dim=[2, 3])
        x = x_sum / (mask_sum + 1e-6)
        z_grid = self.proj(x)

        return z_grid

class ARCContextEncoder(nn.Module):
    def __init__(self, d_model=256, device: str = "cpu"):
        super().__init__()

        self.grid_encoder = ARCGridEncoder(
            d_model=d_model,
            device=device
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

class DSLModel(nn.Module):
    def __init__(
        self,
        vocab_size   : int,
        d_model      : int   = 256,
        n_heads      : int   = 8,
        n_dec_layers : int   = 4,
        dropout      : float = 0.1,
        max_len      : int   = 128,
        device       : str   = "cpu"
    ):
        super().__init__()
        self.d_model = d_model

        self.grid_encoder = ARCContextEncoder(d_model=d_model, device=device)
        self.prog_encoder = DSLProgramEncoder(vocab_size=vocab_size, d_model=d_model)
        self.cost_encoder = CostEncoder(input_dim=5, d_model=d_model)

        self.prog_attn = nn.MultiheadAttention(
            d_model, n_heads, dropout=dropout, batch_first=True
        )
        self.fusion_norm = nn.LayerNorm(d_model)
        self.fusion_proj = nn.Sequential(
            nn.Linear(d_model * 2, d_model),
            nn.GELU(),
            nn.Linear(d_model, d_model),
        )

        self.decoder = DSLDecoder(
            vocab_size  = vocab_size,
            d_model     = d_model,
            n_heads     = n_heads,
            n_layers    = n_dec_layers,
            ff_dim      = d_model * 2,
            dropout     = dropout,
            max_len     = max_len,
        )

    def encode_context(
        self,
        inputs       : torch.Tensor,          # [B, N, H, W]
        outputs      : torch.Tensor,           # [B, N, H, W]
        masks        : torch.Tensor,           # [B, N, H, W]
        prog_graphs  : List[Data],             # M graphs GNN (one per program)
        cost_tensors : List[torch.Tensor],     # M tensors [B, N_grids, 5]
    ) -> torch.Tensor:
        B = inputs.size(0)
        M = len(prog_graphs)
        z_grids = self.grid_encoder(inputs, outputs, masks)   # [B, D]
        z_progs = []

        for m in range(M):
            graph_m = prog_graphs[m]
            z_prog_m = self.prog_encoder(graph_m)              # [B, D]
            z_cost_m = self.cost_encoder(cost_tensors[m])      # [B, D]
            z_progs.append(z_prog_m + z_cost_m)               # [B, D]

        # Stack : [B, M, D]
        z_progs_stack = torch.stack(z_progs, dim=1)
        z_grids_q = z_grids.unsqueeze(1)                      # [B, 1, D]
        z_attended, _ = self.prog_attn(
            z_grids_q, z_progs_stack, z_progs_stack
        )                                                       # [B, 1, D]
        z_attended = z_attended.squeeze(1)                     # [B, D]
        z_fused  = self.fusion_norm(z_grids + z_attended)
        z_context = self.fusion_proj(
            torch.cat([z_grids, z_attended], dim=-1)
        )                                                       # [B, D]

        return z_context

    def forward(
        self,
        inputs       : torch.Tensor,
        outputs      : torch.Tensor,
        masks        : torch.Tensor,
        prog_graphs  : List[Data],
        cost_tensors : List[torch.Tensor],
        tgt          : torch.Tensor,           # [B, L]  teacher forcing
    ) -> torch.Tensor:
        z_context = self.encode_context(
            inputs, outputs, masks, prog_graphs, cost_tensors
        )

        return self.decoder(tgt, z_context)

class DSLDecoder(nn.Module):
    def __init__(
        self,
        vocab_size  : int,
        d_model     : int   = 256,
        n_heads     : int   = 8,
        n_layers    : int   = 4,
        ff_dim      : int   = 512,
        dropout     : float = 0.1,
        max_len     : int   = 128,
    ):
        super().__init__()
        self.d_model    = d_model
        self.vocab_size = vocab_size
        self.max_len    = max_len

        self.context_proj = nn.Linear(d_model, d_model)

        self.token_embed = nn.Embedding(vocab_size, d_model, padding_idx=0)
        self.pos_enc     = PositionalEncoding(d_model, max_len, dropout)

        dec_layer = nn.TransformerDecoderLayer(
            d_model        = d_model,
            nhead          = n_heads,
            dim_feedforward= ff_dim,
            dropout        = dropout,
            batch_first    = True,
            norm_first     = True,
        )
        self.decoder     = nn.TransformerDecoder(dec_layer, num_layers=n_layers)
        self.output_proj = nn.Linear(d_model, vocab_size)

        self._init_weights()

    def _init_weights(self):
        for p in self.parameters():
            if (p.dim() > 1):
                nn.init.xavier_uniform_(p)

    def forward(
        self,
        tgt         : torch.Tensor,   # [B, L]
        z_context   : torch.Tensor,   # [B, D]
    ) -> torch.Tensor:
        B, L = tgt.shape

        memory = self.context_proj(z_context).unsqueeze(1)   # [B, 1, D]
        causal = nn.Transformer.generate_square_subsequent_mask(L, device=tgt.device)

        x = self.token_embed(tgt) * math.sqrt(self.d_model)
        x = self.pos_enc(x)
        x = self.decoder(x, memory, tgt_mask=causal)         # [B, L, D]

        return self.output_proj(x)                            # [B, L, V]

    def decode_step(
        self,
        generated   : torch.Tensor,   # [B, t]
        z_context   : torch.Tensor,   # [B, D]
    ) -> torch.Tensor:
        logits = self.forward(generated, z_context)

        return logits[:, -1, :]   # [B, V]  only last step

class PositionalEncoding(nn.Module):
    def __init__(self, d_model: int, max_len: int = 256, dropout: float = 0.1):
        super().__init__()
        self.dropout = nn.Dropout(dropout)
        pe  = torch.zeros(max_len, d_model)
        pos = torch.arange(max_len).unsqueeze(1).float()
        div = torch.exp(
            torch.arange(0, d_model, 2).float() * (-math.log(10000.0) / d_model)
        )
        pe[:, 0::2] = torch.sin(pos * div)
        pe[:, 1::2] = torch.cos(pos * div)
        self.register_buffer("pe", pe.unsqueeze(0))   # [1, max_len, d_model]

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        return self.dropout(x + self.pe[:, :x.size(1)])

class TreeStateMask:
    def __init__(self, vocab, max_depth: int = 6):
        self.vocab     = vocab
        self.max_depth = max_depth
        self._reset()

    def _reset(self):
        self._vocabulary = vocabulary
        self.current_tree  = None
        self.depth         = 0
        self.state         = "EXPECT_ROOT"   # EXPECT_ROOT | EXPECT_ARG | DONE | ERROR

    def reset(self):
        self._reset()

    def _grid_roots(self) -> List[str]:
        candidates = []

        for name, (t, v) in self._vocabulary.items():
            if (not isinstance(name, str)):
                continue

            if (get_origin(t) is collections.abc.Callable):
                ret = get_args(t)[1]

                if (compatibleType(ret, Tuple[Tuple[int]])):
                    candidates.append(name)

        return sorted(candidates)

    def valid_tokens(self) -> List[str]:
        if (self.state == "DONE" or self.state == "ERROR"):
            return []

        if (self.state == "EXPECT_ROOT"):
            return self._grid_roots()

        if (self.state == "EXPECT_ARG" and self.current_tree is not None):
            next_type = self.current_tree.nextType()

            if (next_type is None):
                self.state = "DONE"

                return []

            candidates = args(next_type)

            candidates = [
                n for n in candidates
                if isinstance(n, str) and n in self._vocabulary
            ]

            if (self.depth >= self.max_depth):
                candidates = [
                    n for n in candidates
                    if not (get_origin(
                        self._vocabulary[n][0]) is collections.abc.Callable and next_type != Callable)
                ]

            return candidates

        return []

    def valid_mask(self, device="cpu") -> torch.Tensor:
        mask     = torch.zeros(len(self.vocab.token2id), dtype=torch.bool)
        valid    = self.valid_tokens()

        for name in valid:
            if (name in self.vocab.token2id):
                mask[self.vocab.token2id[name]] = True

        if (not mask.any()):
            eos_id = self.vocab.token2id.get("<EOS>", 2)
            mask[eos_id] = True

        return mask.to(device)

    def apply_token(self, token_name: str) -> bool:
        if (self.state in ("DONE", "ERROR")):
            return False

        valid = self.valid_tokens()

        if (token_name not in valid):
            self.state = "ERROR"

            return False

        if (self.state == "EXPECT_ROOT"):
            self.current_tree = tree(token_name)
            self.state        = "EXPECT_ARG"

            if (self.current_tree.isFinished()):
                self.state = "DONE"

            return True

        if (self.state == "EXPECT_ARG"):
            next_type = self.current_tree.nextType()
            t_type, _ = self._vocabulary[token_name]

            if (not get_origin(next_type) is collections.abc.Callable
                    and get_origin(t_type) is collections.abc.Callable):
                self.depth += 1

            if (get_origin(next_type) is collections.abc.Callable):
                node = Tree(
                    (token_name, *self._vocabulary[token_name]), []
                )
            else:
                node = tree(token_name)

            self.current_tree.applyNextType(node)

            if (self.current_tree.isFinished()):
                self.state = "DONE"

            return True

        return False

    def is_done(self) -> bool:
        return self.state == "DONE"

    def program(self) -> str:
        if (self.current_tree is None):
            return ""

        return str(self.current_tree)

@torch.no_grad()
def generate(
    model       : DSLModel,
    vocab,
    z_context   : torch.Tensor,   # [1, D]
    beam_width  : int   = 5,
    max_len     : int   = 128,
    temperature : float = 1.0,
    max_depth   : int   = 6,
    device      : str   = "cuda",
) -> List[Tuple[float, str]]:
    model.eval()

    BOS = vocab.token2id.get("<BOS>", 1)
    EOS = vocab.token2id.get("<EOS>", 2)
    PAD = vocab.token2id.get("<PAD>", 0)

    beams = [(0.0, [BOS], TreeStateMask(vocab, max_depth))]

    import copy

    for step in range(max_len - 1):
        all_candidates = []

        for score, ids, ts in beams:
            if (ids[-1] == EOS or ts.is_done()):
                all_candidates.append((score, ids, ts))
                continue

            tgt    = torch.tensor([ids], dtype=torch.long, device=device)
            logits = model.decoder.decode_step(tgt, z_context)  # [1, V]
            logits = logits[0] / max(temperature, 1e-6)          # [V]
            mask = ts.valid_mask(device=device)   # [V]

            if (mask.any()):
                logits = logits.masked_fill(~mask, float("-inf"))

            log_probs = F.log_softmax(logits, dim=-1)

            # Top-k tokens
            top_lp, top_ids = log_probs.topk(
                min(beam_width * 2, mask.sum().item() or 1)
            )

            for lp, tok_id in zip(top_lp.tolist(), top_ids.tolist()):
                tok_name = vocab.id2token.get(tok_id, "<PAD>")

                if (tok_name in ("<PAD>", "<BOS>")):
                    continue

                ts_new = copy.deepcopy(ts)

                if (tok_name == "<EOS>" or ts_new.is_done()):
                    all_candidates.append(
                        (score + lp, ids + [tok_id], ts_new)
                    )
                    continue

                if (ts_new.apply_token(tok_name)):
                    all_candidates.append(
                        (score + lp, ids + [tok_id], ts_new)
                    )

        all_candidates.sort(key=lambda x: -x[0])

        selected   = []
        seen_progs = set()

        for s, ids, ts in all_candidates:
            prog = ts.program()

            if (prog not in seen_progs):
                seen_progs.add(prog)
                selected.append((s, ids, ts))

            if (len(selected) >= beam_width):
                break

        beams = selected

        if (all(b[1][-1] == EOS or b[2].is_done() for b in beams)):
            break

    results = []

    for score, ids, ts in beams:
        prog = ts.program()
        depth = prog.count("(") - prog.count(")")
        prog  = prog + ")" * max(0, depth)

        if (prog and "I" in prog):
            results.append((score, prog))

    return results if results else [(float("inf"), "I")]

@torch.no_grad()
def generate_one(
    model       : DSLModel,
    vocab,
    z_context   : torch.Tensor,
    temperature : float = 1.0,
    max_depth   : int   = 6,
    device      : str   = "cuda",
) -> str:
    model.eval()

    BOS = vocab.token2id.get("<BOS>", 1)
    EOS = vocab.token2id.get("<EOS>", 2)

    ids = [BOS]
    ts  = TreeStateMask(vocab, max_depth)

    for _ in range(128):
        if (ids[-1] == EOS or ts.is_done()):
            break

        tgt = torch.tensor([ids], dtype=torch.long, device=device)
        logits = model.decoder.decode_step(tgt, z_context)[0]
        logits = logits / max(temperature, 1e-6)
        mask = ts.valid_mask(device=device)

        if (mask.any()):
            logits = logits.masked_fill(~mask, float("-inf"))

        probs  = F.softmax(logits, dim=-1)
        tok_id = torch.multinomial(probs, 1).item()
        tok    = vocab.id2token.get(tok_id, "<PAD>")

        if (tok in ("<PAD>", "<BOS>")):
            break

        if (tok == "<EOS>" or ts.is_done()):
            break

        if (ts.apply_token(tok)):
            ids.append(tok_id)
        else:
            break

    if (not ts.is_done()):
        return None

    prog  = ts.program()
    depth = prog.count("(") - prog.count(")")

    return prog + ")" * max(0, depth)

def programDf(program: str, pairs: List[Tuple[Grid, Grid]]) -> pd.DataFrame:
    scores: list = []

    for pair in pairs:
        O = execute_dsl(program, pair[0])

        score: list = [0] * len(scoreFunctions)

        for i in range(0, len(scoreFunctions)):
            a1 = 0
            a2 = 0

            try:
                a1 = np.array(O, dtype = float)
                a2 = np.array(pair[1], dtype = float)
                score[i] = scoreFunctions[i](a1, a2)
            except:
                score[i] = math.inf

            del a1
            del a2

        del O

        scores.append([sum(score)] + score)

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

def build_prog_graph(program: str, vocab, device: str = "cpu") -> Data:
    builder = DSLGraphBuilder(vocab.token2id)

    try:
        graph       = builder.build(program)
        graph.batch = torch.zeros(graph.x.size(0), dtype=torch.long, device=device)

        return graph.to(device)
    except Exception:
        x          = torch.tensor([vocab.token2id.get("I", 0)], dtype=torch.long, device=device)
        edge_index = torch.empty((2, 0), dtype=torch.long, device=device)
        g          = Data(x=x, edge_index=edge_index)
        g.batch    = torch.zeros(1, dtype=torch.long, device=device)

        return g

def encode_program_tokens(program: str, vocab, max_len: int = 128) -> torch.Tensor:
    ids     = [vocab.token2id.get("<BOS>", 1)]
    known   = sorted(
        [t for t in vocab.token2id if t not in ("<PAD>","<BOS>","<EOS>")],
        key=len, reverse=True
    )
    i = 0

    while (i < len(program)):
        for tok in known:
            if (program[i:i+len(tok)] == tok):
                ids.append(vocab.token2id[tok])
                i += len(tok)
                break
        else:
            i += 1

    ids.append(vocab.token2id.get("<EOS>", 2))
    ids = ids[:max_len]
    ids += [vocab.token2id.get("<PAD>", 0)] * (max_len - len(ids))

    return torch.tensor(ids, dtype=torch.long)

def programDepth(program: str):
    count = 0
    n = 0

    for c in program:
        if (c == "("):
            n += 1
        elif (c == ")"):
            n -= 1

        count = max(count, n)

    return count

if (__name__ == "__main__"):
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
    device = "cuda" if torch.cuda.is_available() else "cpu"
    dslModel = DSLModel(len(VOCAB.token2id), d_model=256, device = device)
    model = dslModel.to(device)
    optimizer = torch.optim.AdamW(
        model.parameters(),
        lr=1e-4
    )
    modelFilename: str = "dsl_model.pt"

    if (os.path.exists(modelFilename)):
        checkpoint = torch.load(modelFilename, map_location=device)
        model.load_state_dict(checkpoint["model_state"])

    from aicpppy import Engine

    engine = Engine("dsl_dataset")
    n = engine.count()
    indexes = engine.orderedIndexes()

    for i in range(n):
        j = indexes[i]
        trajectory = engine.trajectory(j)
        targetProgram: str = engine.program(j)
        grids = engine.grids(j)
        candidatePrograms: list = ["I"] * M
        outputs: list = []

        for grid in grids:
            outputs.append(execute_dsl(targetProgram, grid))

        pairs = list(zip(grids, outputs))

        inputs, outputs, masks = arc_pairs_to_tensors(pairs)
        inputs = inputs.to(device)
        outputs = outputs.to(device)
        masks = masks.to(device)
        costs = list(reversed(trajectory))
        costs = sorted(costs, key = lambda x: (-x[0], len(x[1])))

        candidates = list(zip(candidatePrograms, programCosts(targetProgram, candidatePrograms, grids)))
        candidates = sorted(candidates, key = lambda x: (tuple(-x[1].sum(axis = 0, skipna = False)), len(x[0]), x[0]))

        print(f"{i+1}/{n} Target program: {targetProgram} (trajectory: {len(costs)} programs)")
        show: bool = True
        computeGraphs: bool = True
        temperature: float = 1.0
        testedPrograms = set()
        count: int = 1
        minAlpha: float = 0.1
        alpha: float = 1.0
        validCount: int = 0
        numPrograms: int = len(costs)
        programCount: int = 1
        uniqueCount: int = 0

        while (candidates[-1][1].sum(axis = 0, skipna = False)["Total cost"]):
            if (show):
                print(f"  {datetime.datetime.now()} #{validCount}({uniqueCount})/{count} Searched program ({programCount}/{numPrograms}): {costs[0][1]}, cost: {costs[0][0]}")
                show = False

            if (computeGraphs):
                prog_graphs: list  = []
                cost_tensors: list = []

                for program, df in candidates:
                    g = build_prog_graph(program, VOCAB, device)
                    prog_graphs.append(g)
                    cost_tensors.append(dataframe_to_cost_tensor(df).to(device))

                computeGraphs = False

                model.eval()

                with torch.no_grad():
                    z_context = model.encode_context(
                        inputs, outputs, masks,
                        prog_graphs, cost_tensors
                    )   # [1, D]

            program = generate_one(
                model, VOCAB, z_context,
                temperature = temperature,
                device = device,
                max_depth = programDepth(costs[0][1]) - 1
            )

            checked: list = []

            for inp in grids:
                checked.append(isValidGrid(program, inp))

            if (program):
                ok = "(I)" in program or "(I, " in program or ", I," in program or ", I)" in program

            if (program and ok and any(checked)):
                try:
                    df = programCosts(targetProgram, [program], grids)[0]
                    cost = df["Total cost"].sum(skipna = False)
                    validCount += 1

                    if (not program in testedPrograms):
                        uniqueCount += 1
                except Exception:
                    cost = math.inf
            else:
                cost = math.inf

            model.train()
            optimizer.zero_grad()
            target_ids = encode_program_tokens(costs[0][1], VOCAB).to(device)
            decoder_input = target_ids[:-1]
            decoder_target = target_ids[1:]
            logits = model.decoder(decoder_input.unsqueeze(0), z_context)
            L_tokens = F.cross_entropy(
                logits.reshape(
                    -1,
                    logits.size(-1)
                ),
                decoder_target.reshape(-1)
            )

            if (np.isinf(cost).any()):
                L_total = L_tokens
            else:
                generated_cost = torch.tensor(
                    cost,
                    dtype=torch.float32,
                    device=device
                )
                target_cost = torch.tensor(
                    costs[0][0],
                    dtype=torch.float32,
                    device=device
                )
                L_cost = torch.log1p(
                    torch.abs(
                        generated_cost
                        - target_cost
                    )
                )
                L_total_cost = torch.log1p(generated_cost)

                L_total = alpha * L_tokens + (1.0 - alpha) * L_total_cost

            if (not program in testedPrograms):
                try:
                    L_total.backward()
                    optimizer.step()

                    temperature = max(1.0, temperature * 0.95)
                    alpha = max(minAlpha, alpha * 0.9)
                    testedPrograms.add(program)
                except RuntimeError:
                    pass
            else:
                temperature = min(5.0, temperature * 1.05)
                alpha = min(1.0, alpha * 1.5)

            try:
                if (not np.isinf(cost).any()):
                    if (cost < candidates[0][1].sum(axis = 0, skipna = False)["Total cost"]
                        and not program in [c[0] for c in candidates]):
                        torch.save({
                            "model_state": model.state_dict(),
                            "d_model"    : model.decoder.d_model,
                            "vocab_size" : model.decoder.vocab_size,
                        }, modelFilename)

                        print(f"    Found better program: {program}, cost: {cost}")
                        show = True
                        computeGraphs = True

                        candidates.pop(0)
                        candidates.append((program, df))
                        candidates = sorted(candidates, key = lambda x: (tuple(-x[1].sum(axis = 0, skipna = False)), len(x[0]), x[0]))

                        while (len(costs) and (cost <= costs[0][0] or program == costs[0][1])):
                            costs.pop(0)
                            programCount += 1
                    elif (not program in testedPrograms):
                        print(f"    Found worst program: {program}, cost: {cost}")
            except ValueError:
                pass

            count += 1

        print(f"Found program: {candidates[-1][0]} ({validCount}({uniqueCount})/{count - 1} iterations)")
