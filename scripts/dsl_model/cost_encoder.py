import torch
import torch.nn as nn

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
