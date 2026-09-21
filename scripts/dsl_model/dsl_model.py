from .arc_context_encoder import ARCContextEncoder
from .cost_encoder import CostEncoder
from .dsl_decoder import DSLDecoder
from .dsl_program_encoder import DSLProgramEncoder
import torch
import torch.nn as nn
from torch_geometric.data import Data
from typing import List

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
