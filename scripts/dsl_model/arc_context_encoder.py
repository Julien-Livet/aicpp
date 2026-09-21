from .arc_grid_encoder import ARCGridEncoder
import torch
import torch.nn as nn

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
