import torch
import torch.nn as nn

from .arc_grid_encoder import ARCGridEncoder

class ARCGridListEncoder(nn.Module):
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

        self.attn_pool = nn.Linear(
            d_model,
            1
        )

    def forward(self, grids):
        """
        grids : [B, N, H, W]

        Retourne :
        z_grids : [B, d_model]
        """

        B, N, H, W = grids.shape

        z_list = []

        for i in range(N):
            grid = grids[:, i]

            # Toutes les cellules sont valides.
            mask = torch.ones_like(
                grid,
                dtype=torch.bool
            )

            z_i = self.grid_encoder(
                grid,
                grid,
                mask
            )

            z_list.append(z_i)

        # [B, N, D]
        z = torch.stack(
            z_list,
            dim=1
        )

        scores = self.attn_pool(z)
        weights = torch.softmax(
            scores,
            dim=1
        )

        z_grids = (
            weights * z
        ).sum(dim=1)

        return z_grids
