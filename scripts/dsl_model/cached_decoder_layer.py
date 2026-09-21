from .cached_self_attention import CachedSelfAttention
import torch
import torch.nn as nn

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
