import torch.nn as nn
import torch.nn.functional as F
from torch_geometric.nn import GCNConv, global_mean_pool

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
