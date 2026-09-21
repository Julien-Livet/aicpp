import torch
import torch.nn as nn
import torch.nn.functional as F

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
