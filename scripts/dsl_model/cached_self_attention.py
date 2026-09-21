import torch
import torch.nn as nn
import torch.nn.functional as F

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
