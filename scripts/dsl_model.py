from aicpppy import Engine
import ast
import copy
from dsl_rl import VOCAB
import math
import multiprocessing as mp
from multiprocessing import get_context, Queue
import os
import pandas as pd
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch_geometric.data import Batch, Data
from torch_geometric.nn import GCNConv
from torch_geometric.nn import global_mean_pool
from tqdm import tqdm
from typing import List, Tuple

Grid = Tuple[Tuple[int]]
M: int = 50

scoreColumns = ["Total cost", "Grid size cost", "Bounding box cost", "Pixel overlap cost", "Value cost"]

minTemperature: float = 0.1
maxTemperature: float = 5.0
minAlpha: float = 0.1

MAX_ITERATIONS_PER_TARGET: int = 500000
PLATEAU_PATIENCE: int = 50000

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
    def __init__(
        self,
        d_model=256,
        device: str = "cpu"
    ):
        super().__init__()

        self.grid_encoder = ARCGridEncoder(
            d_model=d_model,
            device=device
        )

        self.attn_pool = nn.Sequential(
            nn.Linear(d_model, 1)
        )

    def forward(
        self,
        inputs,
        outputs,
        masks
    ):
        """
        inputs : [B, N, H, W]
        outputs: [B, N, H, W]
        masks  : [B, N, H, W]

        return:
            z_grids: [B, d_model]
        """

        B, N, H, W = inputs.shape

        # --------------------------------------------------
        # Transform B*N grids in one batch
        # --------------------------------------------------

        inputs_flat = inputs.reshape(
            B * N,
            H,
            W
        )

        outputs_flat = outputs.reshape(
            B * N,
            H,
            W
        )

        masks_flat = masks.reshape(
            B * N,
            H,
            W
        )

        z = self.grid_encoder(
            inputs_flat,
            outputs_flat,
            masks_flat
        )
        # [B*N, D]

        # --------------------------------------------------
        # Return at format [B, N, D]
        # --------------------------------------------------

        z = z.reshape(
            B,
            N,
            -1
        )

        scores = self.attn_pool(z)
        # [B, N, 1]

        weights = torch.softmax(
            scores,
            dim=1
        )

        z_grids = (
            weights * z
        ).sum(dim=1)
        # [B, D]

        return z_grids

def pad_grid(grid, max_h, max_w, pad_value=0):
    padded = [
        list(row) + [pad_value] * (max_w - len(row))
        for row in grid
    ]
    padded += [[pad_value] * max_w for _ in range(max_h - len(grid))]

    mask = [
        [1] * len(row) + [0] * (max_w - len(row))
        for row in grid
    ]
    mask += [[0] * max_w for _ in range(max_h - len(grid))]

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

        max_w = max(max_w,
                    max((len(r) for r in inp), default=0),
                    max((len(r) for r in out), default=0))

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
        self.fusion_norm = nn.LayerNorm(d_model) #TODO: to remove
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
        inputs: torch.Tensor,
        outputs: torch.Tensor,
        masks: torch.Tensor,
        prog_graphs: List[Data],
        cost_tensors: List[torch.Tensor]
    ) -> torch.Tensor:
        B = inputs.size(0)
        M = len(prog_graphs)

        # ======================================================
        # 1. ARC
        # ======================================================

        z_grids = self.grid_encoder(
            inputs,
            outputs,
            masks
        )

        # ======================================================
        # 2. DSL M graphs
        # ======================================================

        graph_batch = Batch.from_data_list(
            prog_graphs
        )

        graph_batch = graph_batch.to(
            inputs.device
        )

        z_prog = self.prog_encoder(
            graph_batch
        )

        z_prog = z_prog.unsqueeze(0)

        z_prog = z_prog.expand(
            B,
            -1,
            -1
        )

        # ======================================================
        # 3. M cost tensors
        # ======================================================

        cost_batch = torch.stack(
            cost_tensors,
            dim=1
        )

        cost_batch = cost_batch.reshape(
            B * M,
            cost_batch.size(2),
            cost_batch.size(3)
        )

        z_cost = self.cost_encoder(
            cost_batch
        )

        z_cost = z_cost.reshape(
            B,
            M,
            -1
        )

        # ======================================================
        # 4. Program + cost fusion
        # ======================================================

        z_progs_stack = (
            z_prog + z_cost
        )

        # ======================================================
        # 5. Attention ARC -> programs
        # ======================================================

        z_grids_q = z_grids.unsqueeze(1)

        z_attended, _ = self.prog_attn(
            z_grids_q,
            z_progs_stack,
            z_progs_stack
        )

        z_attended = z_attended.squeeze(1)

        # ======================================================
        # 6. Final fusion
        # ======================================================

        z_context = self.fusion_proj(
            torch.cat(
                [
                    z_grids,
                    z_attended
                ],
                dim=-1
            )
        )

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
        self.decoder     = nn.TransformerDecoder(dec_layer, num_layers=n_layers, norm=nn.LayerNorm(d_model))
        self.cached_layers = nn.ModuleList([
            CachedDecoderLayer(
                d_model=d_model,
                n_heads=n_heads,
                ff_dim=ff_dim,
                dropout=0.0,
            )
            for _ in range(n_layers)
        ])
        self.cached_norm = nn.LayerNorm(d_model)
        self.output_proj = nn.Linear(d_model, vocab_size)

        self._init_weights()

    def _init_weights(self):
        for p in self.parameters():
            if (p.dim() > 1):
                nn.init.xavier_uniform_(p)

    def sync_cached_decoder(self):
        for old_layer, cached_layer in zip(
            self.decoder.layers,
            self.cached_layers,
        ):
            cached_layer.load_from_transformer_layer(old_layer)

        self.cached_norm.load_state_dict(
            self.decoder.norm.state_dict()
        )
    
    def build_cached_decoder(self):
        self.cached_layers = nn.ModuleList([
            CachedDecoderLayer(
                d_model=self.d_model,
                n_heads=layer.self_attn.num_heads,
                ff_dim=layer.linear1.out_features,
                dropout=0.0,
            )
            for layer in self.decoder.layers
        ])

        self.cached_norm = nn.LayerNorm(self.d_model)

        for old_layer, cached_layer in zip(
            self.decoder.layers,
            self.cached_layers,
        ):
            cached_layer.load_from_transformer_layer(old_layer)

        self.cached_norm.load_state_dict(
            self.decoder.norm.state_dict()
        )

        device = next(self.parameters()).device

        self.cached_layers.to(device)
        self.cached_norm.to(device)

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

    def decode_step_cached(
        self,
        token: torch.Tensor,          # [B, 1]
        memory,
        cache=None,
    ):
        """
        token : [B, 1]
        memory: self.context_proj(z_context).unsqueeze(1)
        cache : (K, V) list, one entry by layer

        Return :
            logits : [B, V]
            new_cache : (K, V) list
        """

        if cache is None:
            cache = [None] * len(self.cached_layers)

        position = 0 if cache[0] is None else cache[0][0].size(2)

        x = self.token_embed(token) * math.sqrt(self.d_model)

        x = self.pos_enc.forward_at(
            x,
            position,
        )

        new_cache = []

        for layer, layer_cache in zip(
            self.cached_layers,
            cache,
        ):
            x, layer_cache = layer(
                x,
                memory,
                cache=layer_cache,
            )

            new_cache.append(layer_cache)

        x = self.cached_norm(x)

        logits = self.output_proj(x[:, -1, :])

        return logits, new_cache

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

    def forward_at(self, x: torch.Tensor, position: int) -> torch.Tensor:
        return self.dropout(
            x + self.pe[:, position:position + x.size(1)]
        )

class CachedSelfAttention(nn.Module):
    def __init__(self, d_model, n_heads, dropout=0.0):
        super().__init__()

        assert d_model % n_heads == 0

        self.d_model = d_model
        self.n_heads = n_heads
        self.head_dim = d_model // n_heads

        self.q_proj = nn.Linear(d_model, d_model)
        self.k_proj = nn.Linear(d_model, d_model)
        self.v_proj = nn.Linear(d_model, d_model)
        self.out_proj = nn.Linear(d_model, d_model)

        self.dropout = dropout

    def load_from_multihead_attention(self, attn):
        """
        Copie les poids d'un nn.MultiheadAttention
        PyTorch vers notre implémentation.
        """

        D = self.d_model

        with torch.no_grad():
            self.q_proj.weight.copy_(
                attn.in_proj_weight[:D]
            )
            self.k_proj.weight.copy_(
                attn.in_proj_weight[D:2 * D]
            )
            self.v_proj.weight.copy_(
                attn.in_proj_weight[2 * D:]
            )

            self.q_proj.bias.copy_(
                attn.in_proj_bias[:D]
            )
            self.k_proj.bias.copy_(
                attn.in_proj_bias[D:2 * D]
            )
            self.v_proj.bias.copy_(
                attn.in_proj_bias[2 * D:]
            )

            self.out_proj.weight.copy_(
                attn.out_proj.weight
            )
            self.out_proj.bias.copy_(
                attn.out_proj.bias
            )

    def _split_heads(self, x):
        B, L, D = x.shape

        return (
            x.reshape(
                B,
                L,
                self.n_heads,
                self.head_dim,
            )
            .transpose(1, 2)
        )

    def _merge_heads(self, x):
        B, H, L, Dh = x.shape

        return (
            x.transpose(1, 2)
            .contiguous()
            .reshape(B, L, H * Dh)
        )

    def forward(
        self,
        x,
        cache=None,
    ):
        """
        x:
            [B, L, D]

        cache:
            None
            or (k_cache, v_cache)

        Return:
            output, new_cache
        """

        q = self._split_heads(
            self.q_proj(x)
        )

        k = self._split_heads(
            self.k_proj(x)
        )

        v = self._split_heads(
            self.v_proj(x)
        )

        if cache is not None:
            k_cache, v_cache = cache

            k = torch.cat(
                [k_cache, k],
                dim=2,
            )

            v = torch.cat(
                [v_cache, v],
                dim=2,
            )

        new_cache = (k, v)

        out = F.scaled_dot_product_attention(
            q,
            k,
            v,
            is_causal=False,
        )

        out = self._merge_heads(out)

        return self.out_proj(out), new_cache

class CachedDecoderLayer(nn.Module):
    def __init__(
        self,
        d_model,
        n_heads,
        ff_dim,
        dropout=0.0,
    ):
        super().__init__()

        self.norm1 = nn.LayerNorm(d_model)
        self.norm2 = nn.LayerNorm(d_model)
        self.norm3 = nn.LayerNorm(d_model)

        self.self_attn = CachedSelfAttention(
            d_model=d_model,
            n_heads=n_heads,
            dropout=dropout,
        )

        self.cross_attn = nn.MultiheadAttention(
            embed_dim=d_model,
            num_heads=n_heads,
            dropout=dropout,
            batch_first=True,
        )

        self.linear1 = nn.Linear(
            d_model,
            ff_dim,
        )

        self.linear2 = nn.Linear(
            ff_dim,
            d_model,
        )

        self.dropout = nn.Dropout(dropout)
        self.activation = nn.ReLU()

    def forward(
        self,
        x,
        memory,
        cache=None,
    ):

        # -------------------------
        # Self attention
        # -------------------------

        residual = x

        x_norm = self.norm1(x)

        self_out, new_cache = self.self_attn(
            x_norm,
            cache=cache,
        )

        x = residual + self_out

        # -------------------------
        # Cross attention
        # -------------------------

        residual = x

        x_norm = self.norm2(x)

        cross_out, _ = self.cross_attn(
            x_norm,
            memory,
            memory,
            need_weights=False,
        )

        x = residual + cross_out

        # -------------------------
        # Feed Forward
        # -------------------------

        residual = x

        x_norm = self.norm3(x)

        x_norm = self.linear1(x_norm)
        x_norm = self.activation(x_norm)
        x_norm = self.dropout(x_norm)
        x_norm = self.linear2(x_norm)

        x = residual + x_norm

        return x, new_cache

    def load_from_transformer_layer(self, layer):
        with torch.no_grad():

            # -------------------------
            # LayerNorm
            # -------------------------

            self.norm1.load_state_dict(
                layer.norm1.state_dict()
            )

            self.norm2.load_state_dict(
                layer.norm2.state_dict()
            )

            self.norm3.load_state_dict(
                layer.norm3.state_dict()
            )

            # -------------------------
            # Self attention
            # -------------------------

            self.self_attn.load_from_multihead_attention(
                layer.self_attn
            )

            # -------------------------
            # Cross attention
            # -------------------------

            self.cross_attn.load_state_dict(
                layer.multihead_attn.state_dict()
            )

            # -------------------------
            # FFN
            # -------------------------

            self.linear1.load_state_dict(
                layer.linear1.state_dict()
            )

            self.linear2.load_state_dict(
                layer.linear2.state_dict()
            )

@torch.no_grad()
def generate_one(
    model       : DSLModel,
    vocab,
    z_context   : torch.Tensor,
    engine,
    temperature : float = 1.0,
    max_depth   : int   = 6,
    device      : str   = "cuda",
) -> str:
    model.eval()

    BOS = vocab.token2id.get("<BOS>", 1)
    EOS = vocab.token2id.get("<EOS>", 2)

    ids = [BOS]
    connectionBuilder = engine.connectionBuilder()
    connectionBuilder.reset(max_depth)

    for _ in range(128):
        if (ids[-1] == EOS or connectionBuilder.done()):
            break

        tgt = torch.tensor([ids], dtype=torch.long, device=device)
        logits = model.decoder.decode_step(tgt, z_context)[0]
        logits = logits / max(temperature, 1e-6)

        mask     = torch.zeros(len(vocab.token2id), dtype=torch.bool)
        valid    = connectionBuilder.availableNames()

        for name in valid:
            if (name in vocab.token2id):
                mask[vocab.token2id[name]] = True

        if (not mask.any()):
            eos_id = vocab.token2id.get("<EOS>", 2)
            mask[eos_id] = True

        mask = mask.to(device)

        if (mask.any()):
            logits = logits.masked_fill(~mask, float("-inf"))

        probs  = F.softmax(logits, dim=-1)
        tok_id = torch.multinomial(probs, 1).item()
        tok    = vocab.id2token.get(tok_id, "<PAD>")

        if (tok in ("<PAD>", "<BOS>")):
            break

        if (tok == "<EOS>" or connectionBuilder.done()):
            break

        if (connectionBuilder.applyName(tok)):
            ids.append(tok_id)
        else:
            break

    if (not connectionBuilder.valid()):
        return None

    return connectionBuilder.program()

@torch.no_grad()
def generate_one_cached(
    model       : DSLModel,
    vocab,
    z_context   : torch.Tensor,
    engine,
    temperature : float = 1.0,
    max_depth   : int   = 6,
    device      : str   = "cuda",
) -> str:
    model.eval()

    BOS = vocab.token2id.get("<BOS>", 1)
    EOS = vocab.token2id.get("<EOS>", 2)

    ids = [BOS]

    connectionBuilder = engine.connectionBuilder()
    connectionBuilder.reset(max_depth)

    # Cache du décodeur
    cache = None

    # Premier token = BOS
    token = torch.tensor(
        [[BOS]],
        dtype=torch.long,
        device=device,
    )

    z_context = z_context.to(device)
    memory = model.decoder.context_proj(z_context).unsqueeze(1)

    for _ in range(128):

        if ids[-1] == EOS or connectionBuilder.done():
            break

        # -----------------------------------------------------
        # Décodage avec KV cache
        # -----------------------------------------------------

        logits, cache = model.decoder.decode_step_cached(
            token,
            memory,
            cache,
        )

        logits = logits[0]
        logits = logits / max(temperature, 1e-6)

        # -----------------------------------------------------
        # Masque des tokens autorisés
        # -----------------------------------------------------

        mask = torch.zeros(
            len(vocab.token2id),
            dtype=torch.bool,
            device=device,
        )

        valid = connectionBuilder.availableNames()

        for name in valid:
            if name in vocab.token2id:
                mask[vocab.token2id[name]] = True

        if not mask.any():
            mask[EOS] = True

        logits = logits.masked_fill(
            ~mask,
            float("-inf"),
        )

        # -----------------------------------------------------
        # Sampling
        # -----------------------------------------------------

        probs = F.softmax(logits, dim=-1)

        tok_id = torch.multinomial(
            probs,
            1,
        ).item()

        tok = vocab.id2token.get(
            tok_id,
            "<PAD>",
        )

        # -----------------------------------------------------
        # Gestion token
        # -----------------------------------------------------

        if tok in ("<PAD>", "<BOS>"):
            break

        if tok == "<EOS>" or connectionBuilder.done():
            break

        if connectionBuilder.applyName(tok):
            ids.append(tok_id)

            # Le prochain appel ne reçoit QUE le nouveau token
            token = torch.tensor(
                [[tok_id]],
                dtype=torch.long,
                device=device,
            )
        else:
            break

    if not connectionBuilder.valid():
        return None

    return connectionBuilder.program()

def build_prog_graph(
    program: str,
    vocab,
    device: str = "cpu"
) -> Data:
    builder = DSLGraphBuilder(
        vocab.token2id
    )

    try:
        graph = builder.build(program)

        return graph.to(device)
    except Exception:
        x = torch.tensor(
            [vocab.token2id.get("I", 0)],
            dtype=torch.long,
            device=device
        )

        edge_index = torch.empty(
            (2, 0),
            dtype=torch.long,
            device=device
        )

        return Data(
            x=x,
            edge_index=edge_index
        )

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

def addOutput(filename: str, line: str):
    with open(filename, "a") as f:
        f.write(line + "\n")

def build_cached_decoder_from_model(model):
    old_decoder = model.decoder

    layers = nn.ModuleList([
        CachedDecoderLayer(
            d_model=old_decoder.d_model,
            n_heads=old_decoder.decoder.layers[0].self_attn.num_heads,
            ff_dim=old_decoder.decoder.layers[0].linear1.out_features,
            dropout=0.0,
        )
        for _ in old_decoder.decoder.layers
    ])

    norm = nn.LayerNorm(
        old_decoder.d_model
    )

    for old_layer, new_layer in zip(
        old_decoder.decoder.layers,
        layers,
    ):
        new_layer.load_from_transformer_layer(
            old_layer
        )

    norm.load_state_dict(
        old_decoder.decoder.norm.state_dict()
    )

    device = next(model.parameters()).device
    layers = layers.to(device)
    norm = norm.to(device)

    return layers, norm

class Worker:
    def __init__(self, engine):
        self.j = None
        self.engine = engine

    def prepare_experience(self):
        prog_graphs = []
        cost_tensors = []

        for program, df in self.candidates:
            g = build_prog_graph(program, VOCAB, "cpu")
            prog_graphs.append(g.cpu())

            c = dataframe_to_cost_tensor(df)
            cost_tensors.append(c.cpu())

        return prog_graphs, cost_tensors

    def init(self, device: str, j: int):
        self.j = j
        self.targetProgram = self.engine.program(j)
        self.trajectory = self.engine.trajectory(j)
        self.grids = self.engine.grids(j)
        self.outputs = self.engine.outputs(j)
        pairs = list(zip(self.grids, self.outputs))
        inputs, outputs, masks = arc_pairs_to_tensors(pairs)
        self.inputs = inputs.to(device)
        self.outputs = outputs.to(device)
        self.masks = masks.to(device)
        self.costs = list(reversed(self.trajectory))
        self.costs = sorted(self.costs, key = lambda x: (-x[0], len(x[1])))
        self.candidates: list = [("I", pd.DataFrame(self.engine.dfIdentity(j), columns = scoreColumns))] * M
        self.computeGraphs: bool = True
        self.temperature: float = minTemperature
        self.testedPrograms = set()
        self.alpha: float = 1.0
        self.programCount: int = 1
        self.best_seen_cost = self.candidates[-1][1].sum(axis = 0, skipna = False)["Total cost"]
        self.iters_since_improvement = 0
        self.program = None
        self.cost = None
        self.df = None
        self.use_semantic = None
        self.count: int = 0

    def process(self, model, device) -> bool:
        if (self.j == None):
            return True

        if (not self.candidates[-1][1].sum(axis = 0, skipna = False)["Total cost"]):
            return True

        if (not len(self.costs)):
            return True
        
        self.current_best = self.candidates[-1][1].sum(axis = 0, skipna = False)["Total cost"]

        if (self.current_best < self.best_seen_cost):
            self.best_seen_cost = self.current_best
        else:
            self.iters_since_improvement += 1

        if (self.count >= MAX_ITERATIONS_PER_TARGET or self.iters_since_improvement >= PLATEAU_PATIENCE):
            return True

        if (self.computeGraphs):
            prog_graphs: list  = []
            cost_tensors: list = []

            for program, df in self.candidates:
                g = build_prog_graph(program, VOCAB, device)
                prog_graphs.append(g)
                cost_tensors.append(dataframe_to_cost_tensor(df).to(device))

            self.prog_graphs = [
                    g.cpu()
                    for g in prog_graphs
                ]

            self.cost_tensors = [
                c.cpu()
                for c in cost_tensors
            ]

            self.computeGraphs = False

            model.eval()

            with torch.no_grad():
                self.z_context = model.encode_context(
                    self.inputs, self.outputs, self.masks,
                    prog_graphs, cost_tensors
                ).cpu()

        self.program = generate_one_cached(
            model, VOCAB, self.z_context, self.engine,
            temperature = self.temperature,
            device = device,
            max_depth = programDepth(self.costs[0][1]),
        )

        if (not self.program):
            self.cost = math.inf
        else:
            try:
                self.df = pd.DataFrame(self.engine.dfConnectionBuilder(self.j), columns = scoreColumns)
                self.cost = self.df["Total cost"].sum(skipna = False)
            except RuntimeError:
                self.cost = math.inf

        if (not self.program or math.isinf(self.cost)):
            self.temperature = min(maxTemperature, self.temperature * 1.05)
            self.alpha = min(1.0, self.alpha * 1.5)
            self.use_semantic = False
        elif (self.cost <= self.costs[0][0]):
            self.temperature = max(minTemperature, self.temperature * 0.95)
            self.alpha = max(minAlpha, self.alpha * 0.9)
            self.use_semantic = True
        else:
            self.temperature = min(maxTemperature, self.temperature * 1.05)
            self.alpha = min(1.0, self.alpha * 1.5)
            self.use_semantic = False
            
        if (self.program):
            if (self.cost < self.candidates[0][1].sum(axis = 0, skipna = False)["Total cost"]
                and not self.program in [c[0] for c in self.candidates]):
                self.computeGraphs = True
                self.iters_since_improvement = 0

                self.candidates.pop(0)
                self.candidates.append((self.program, self.df))
                self.candidates = sorted(self.candidates, key = lambda x: (tuple(-x[1].sum(axis = 0, skipna = False)), -len(x[0]), x[0]))

                while (len(self.costs) and self.cost <= self.costs[0][0]):
                    self.costs.pop(0)
            elif (not math.isinf(self.cost) and not self.program in self.testedPrograms):
                self.iters_since_improvement = 0 #TODO: to remove?

            if (not self.program in self.testedPrograms):
                self.testedPrograms.add(self.program)

        self.count += 1

        return False

def learner_step(device, model, optimizer, experiences):
    versions = {
        exp.model_version
        for exp in experiences
    }

    assert len(versions) == 1

    optimizer.zero_grad()

    losses: list = []

    for exp in experiences:
        # ---------------------------------------
        # Recompute context with learner
        # ---------------------------------------

        inputs = exp.inputs.to(device)
        outputs = exp.outputs.to(device)
        masks = exp.masks.to(device)

        prog_graphs = [
            g.to(device)
            for g in exp.prog_graphs
        ]

        cost_tensors = [
            c.to(device)
            for c in exp.cost_tensors
        ]

        z_context = model.encode_context(
            inputs,
            outputs,
            masks,
            prog_graphs,
            cost_tensors
        )

        # ---------------------------------------
        # Target loss
        # ---------------------------------------

        target_ids = encode_program_tokens(
            exp.target_program,
            VOCAB
        ).to(device)

        decoder_input = target_ids[:-1]
        decoder_target = target_ids[1:]

        logits = model.decoder(
            decoder_input.unsqueeze(0),
            z_context
        )

        L_tokens = F.cross_entropy(
            logits.reshape(-1, logits.size(-1)),
            decoder_target.reshape(-1)
        )

        # ---------------------------------------
        # Semantic loss
        # ---------------------------------------

        if exp.use_semantic:
            gen_ids = encode_program_tokens(
                exp.generated_program,
                VOCAB
            ).to(device)

            gen_input = gen_ids[:-1]
            gen_target = gen_ids[1:]

            logits_self = model.decoder(
                gen_input.unsqueeze(0),
                z_context
            )

            L_semantic = F.cross_entropy(
                logits_self.reshape(-1, logits_self.size(-1)),
                gen_target.reshape(-1)
            )
        else:
            L_semantic = L_tokens

        # ---------------------------------------
        # Total
        # ---------------------------------------

        L_total = (
            exp.alpha * L_tokens
            + (1.0 - exp.alpha) * L_semantic
        )

        losses.append(L_total)

    sum(losses).backward()

    optimizer.step()

    model.decoder.sync_cached_decoder()

    torch.save({
        "model_state": model.state_dict(),
        "d_model"    : model.decoder.d_model,
        "vocab_size" : model.decoder.vocab_size,
    }, modelFilename.replace(".pt", ".tmp"))

    os.remove(modelFilename)
    os.rename(modelFilename.replace(".pt", ".tmp"), modelFilename)

class Experience:
    def __init__(
        self,
        workerId,
        inputs,
        outputs,
        masks,
        prog_graphs,
        cost_tensors,
        target_program,
        generated_program,
        alpha,
        use_semantic,
        model_version,
    ):
        self.workerId = workerId
        self.inputs = inputs.detach().cpu()
        self.outputs = outputs.detach().cpu()
        self.masks = masks.detach().cpu()
        self.prog_graphs = prog_graphs
        self.cost_tensors = [
            c.detach().cpu()
            for c in cost_tensors
        ]
        self.target_program = target_program
        self.generated_program = generated_program
        self.alpha = float(alpha)
        self.use_semantic = bool(use_semantic)
        self.model_version = int(model_version)

def sync_actor_model(actor_model, learner_model):
    actor_model.load_state_dict(learner_model.state_dict())
    actor_model.eval()

    for p in actor_model.parameters():
        assert p.grad is None

    for actor_param, learner_param in zip(
        actor_model.parameters(),
        learner_model.parameters(),
    ):
        assert torch.equal(
            actor_param,
            learner_param
        )

def serialize_prog_graph(g):
    return {
        "x": g.x.cpu().numpy(),
        "edge_index": g.edge_index.cpu().numpy(),
    }

def deserialize_prog_graph(g):
    return Data(
        x=torch.from_numpy(g["x"]),
        edge_index=torch.from_numpy(g["edge_index"]),
    )

def worker_process(input_queue, output_queue, worker_id, model_version, actor_state):
    # Un seul Engine pour toute la durée du processus
    engine = Engine("dsl_dataset")
    torch.set_num_threads(1)
    torch.set_num_interop_threads(1)
    # Un seul Worker réutilisé
    worker = Worker(engine)

    # Un seul actor_model réutilisé
    actor_model = DSLModel(
        len(VOCAB.token2id),
        d_model=256,
        device="cuda",
    ).to("cuda")
    torch.set_flush_denormal(True)
    actor_model.load_state_dict(actor_state)

    actor_model.requires_grad_(False)
    actor_model.eval()

    actor_model.decoder.sync_cached_decoder()

    current_model_version = model_version

    while True:
        message = input_queue.get()

        # Sentinel d'arrêt
        if message is None:
            break

        message_type = message[0]

        # --------------------------------------------------
        # Synchronisation de l'actor
        # --------------------------------------------------
        if message_type == "sync":
            _, current_model_version, new_actor_state = message

            actor_model.load_state_dict(new_actor_state)

            actor_model.requires_grad_(False)
            actor_model.eval()

            actor_model.decoder.sync_cached_decoder()

            output_queue.put({
                "type": "sync_ack",
                "workerId": worker_id,
                "model_version": current_model_version,
            })

            continue

        # --------------------------------------------------
        # Job
        # --------------------------------------------------
        if message_type == "job":
            _, batch_id, j = message

            worker.init("cpu", j)

            prog_graphs, cost_tensors = worker.prepare_experience()

            with torch.no_grad():
                z_context = actor_model.encode_context(
                    worker.inputs.cuda(),
                    worker.outputs.cuda(),
                    worker.masks.cuda(),
                    [g.to("cuda") for g in prog_graphs],
                    [c.cuda() for c in cost_tensors],
                )

            program = generate_one_cached(
                actor_model,
                VOCAB,
                z_context,
                engine,
                temperature=worker.temperature,
                device="cuda",
                max_depth=programDepth(worker.costs[0][1]),
            )

            output_queue.put({
                "type": "experience",
                "batch_id": batch_id,
                "workerId": worker_id,
                "model_version": current_model_version,
                "j": j,
                "inputs": worker.inputs.cpu().numpy(),
                "outputs": worker.outputs.cpu().numpy(),
                "masks": worker.masks.cpu().numpy(),

                "prog_graphs": [
                    serialize_prog_graph(g)
                    for g in prog_graphs
                ],

                "cost_tensors": [
                    c.cpu().numpy()
                    for c in cost_tensors
                ],

                "target_program": worker.targetProgram,
                "generated_program": program,

                "alpha": worker.alpha,
                "use_semantic": worker.use_semantic,
            })

            continue

        raise RuntimeError(
            f"Message inconnu reçu par worker {worker_id}: "
            f"{message_type}"
        )

class WorkerPool:
    def __init__(
        self,
        num_workers,
        model_version,
        actor_model,
    ):
        self.ctx = mp.get_context("spawn")

        self.input_queues = [
            self.ctx.Queue()
            for _ in range(num_workers)
        ]

        self.output_queue = self.ctx.Queue()
        self.pending_results = {}
        self.processes = []

        actor_state = {
            name: tensor.detach().cpu()
            for name, tensor in actor_model.state_dict().items()
        }

        for worker_id in range(num_workers):
            p = self.ctx.Process(
                target=worker_process,
                args=(
                    self.input_queues[worker_id],
                    self.output_queue,
                    worker_id,
                    model_version,
                    actor_state,
                ),
            )

            p.start()
            self.processes.append(p)

    def submit_jobs(self, batch_id, jobs):
        for i, j in enumerate(jobs):
            worker_id = i % len(self.input_queues)

            self.input_queues[worker_id].put(
                (
                    "job",
                    batch_id,
                    j,
                )
            )

    def _get_output(self):
        return self.output_queue.get()

    def collect_experiences(
        self,
        batch_id,
        jobs,
        model_version,
    ):
        experiences = []

        while len(experiences) < len(jobs):

            if (
                batch_id in self.pending_results
                and len(self.pending_results[batch_id]) > 0
            ):
                result = self.pending_results[batch_id].pop(0)

                if not self.pending_results[batch_id]:
                    del self.pending_results[batch_id]

            else:
                result = self._get_output()

                if result["type"] != "experience":
                    raise RuntimeError(
                        f"Résultat inattendu : {result['type']}"
                    )

                result_batch_id = result["batch_id"]

                if result_batch_id != batch_id:
                    self.pending_results.setdefault(
                        result_batch_id,
                        []
                    ).append(result)

                    continue

            assert result["batch_id"] == batch_id
            assert result["model_version"] == model_version
            assert result["target_program"] is not None

            experience = reconstruct_experience(result)

            experiences.append(experience)

        assert len(experiences) == len(jobs)

        assert {
            exp.model_version
            for exp in experiences
        } == {model_version}

        return experiences

    def sync(
        self,
        model_version,
        actor_model,
    ):
        actor_state = {
            name: tensor.detach().cpu()
            for name, tensor in actor_model.state_dict().items()
        }

        for worker_id in range(len(self.processes)):
            self.input_queues[worker_id].put(
                (
                    "sync",
                    model_version,
                    actor_state,
                )
            )

        sync_acks = []

        while len(sync_acks) < len(self.processes):

            result = self._get_output()

            if result["type"] == "experience":
                self.pending_results.setdefault(
                    result["batch_id"],
                    []
                ).append(result)

                continue

            if result["type"] != "sync_ack":
                raise RuntimeError(
                    f"Résultat inattendu pendant sync : {result['type']}"
                )

            assert result["model_version"] == model_version
            assert result["workerId"] in range(len(self.processes))

            sync_acks.append(result)
    
        assert len(sync_acks) == len(self.processes)

    def close(self):
        for input_queue in self.input_queues:
            input_queue.put(None)

        for input_queue in self.input_queues:
            input_queue.close()
            input_queue.join_thread()

        self.output_queue.close()
        self.output_queue.join_thread()

        for p in self.processes:
            p.join()
            assert p.exitcode == 0

        self.processes = []
    
def reconstruct_experience(result):
    prog_graphs = [
        deserialize_prog_graph(g)
        for g in result["prog_graphs"]
    ]

    cost_tensors = [
        torch.from_numpy(c)
        for c in result["cost_tensors"]
    ]

    return Experience(
        workerId=result["workerId"],
        inputs=torch.from_numpy(result["inputs"]),
        outputs=torch.from_numpy(result["outputs"]),
        masks=torch.from_numpy(result["masks"]),
        prog_graphs=prog_graphs,
        cost_tensors=cost_tensors,
        target_program=result["target_program"],
        generated_program=result["generated_program"],
        alpha=result["alpha"],
        use_semantic=result["use_semantic"],
        model_version=result["model_version"],
    )

if (__name__ == "__main__"):
    device = "cuda" if torch.cuda.is_available() else "cpu"
    engine = Engine("dsl_dataset")
    n = engine.count()
    indexes = engine.orderedIndexes()
    dslModel = DSLModel(len(VOCAB.token2id), d_model = 256, device = device)
    model = dslModel.to(device)
    modelFilename: str = "dsl_model.pt"

    if (os.path.exists(modelFilename)):
        checkpoint = torch.load(modelFilename, map_location = device)
        model.load_state_dict(checkpoint["model_state"])

    model.decoder.sync_cached_decoder()

    optimizer = torch.optim.AdamW(model.parameters(), lr = 1e-4)

    model_version: int = 1
    process = tqdm(
        total=len(indexes),
        desc="Programs",
        dynamic_ncols=True,
    )
    actor_model = copy.deepcopy(model).to(device)
    actor_model.requires_grad_(False)
    actor_model.eval()

    sync_actor_model(actor_model, model)

    worker_pool = WorkerPool(
        num_workers=1, #TODO: os.cpu_count() or 1,
        model_version=model_version,
        actor_model=actor_model,
    )

    jobs_per_worker = 4
    batch_id = 0
    pending_batches = {}

    while True:
        batch_size = min(
            len(indexes),
            len(worker_pool.processes) * jobs_per_worker,
        )

        if batch_size == 0:
            break

        jobs = indexes[:batch_size]
        indexes = indexes[batch_size:]

        batch_id += 1

        pending_batches[batch_id] = {
            "jobs": jobs,
            "model_version": model_version,
        }

        worker_pool.submit_jobs(
            batch_id,
            jobs,
        )

        # Pour cette première étape, on ne traite
        # le batch que lorsqu'on a suffisamment
        # de travail en attente.
        if len(pending_batches) < 2:
            continue

        first_batch_id = min(pending_batches)

        batch = pending_batches.pop(first_batch_id)

        experiences = worker_pool.collect_experiences(
            first_batch_id,
            batch["jobs"],
            batch["model_version"],
        )

        learner_step(
            device,
            model,
            optimizer,
            experiences,
        )

        model_version += 1

        sync_actor_model(
            actor_model,
            model,
        )

        worker_pool.sync(
            model_version,
            actor_model,
        )

        process.update(len(experiences))

        process.set_postfix(
            version=model_version,
            workers=len(worker_pool.processes),
        )

    for remaining_batch_id, batch in pending_batches.items():
        experiences = worker_pool.collect_experiences(
            remaining_batch_id,
            batch["jobs"],
            batch["model_version"],
        )

        learner_step(
            device,
            model,
            optimizer,
            experiences,
        )

        model_version += 1

        sync_actor_model(
            actor_model,
            model,
        )

        worker_pool.sync(
            model_version,
            actor_model,
        )

        process.update(len(experiences))

        process.set_postfix(
            version=model_version,
            workers=len(worker_pool.processes),
        )

    worker_pool.close()
    process.close()
