from .cached_decoder_layer import CachedDecoderLayer
import math
from .positional_encoding import PositionalEncoding
import torch
import torch.nn as nn

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
