from __future__ import annotations
import collections
from connection import compatibleType
import dsl_engine
from dsl_tree import vocabulary, args, tree, root, Tree
import json
import math
import numpy as np
import os
from pathlib import Path
import random
import sys
from test_dsl_engine import arcHeuristic
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.distributions import Categorical
import torch.optim as optim
from torch.utils.data import Dataset, DataLoader
from typing import Dict, List, Optional, Tuple

class DSLVocab:
    SPECIAL = ["<PAD>", "<BOS>", "<EOS>"]

    def __init__(self):
        structural = [",", "(", ")"]
        self.tokens    = self.SPECIAL + structural + sorted(vocabulary.keys())
        self.token2id  = {t: i for i, t in enumerate(self.tokens)}
        self.id2token  = {i: t for t, i in self.token2id.items()}
        self.PAD = self.token2id["<PAD>"]
        self.BOS = self.token2id["<BOS>"]
        self.EOS = self.token2id["<EOS>"]

    def __len__(self) -> int:
        return len(self.tokens)

    def encode(self, program: str, max_len: int = 128) -> List[int]:
        ids: list = [self.BOS]
        known = sorted([t for t in self.tokens if t not in self.SPECIAL],
                       key = len, reverse = True)
        i = 0

        while (i < len(program)):
            for tok in known:
                if (program[i:i+len(tok)] == tok):
                    ids.append(self.token2id[tok])
                    i += len(tok)
                    break
            else:
                i += 1

        ids.append(self.EOS)
        ids = ids[:max_len]
        ids += [self.PAD] * (max_len - len(ids))

        return ids

    def decode(self, ids: List[int]) -> str:
        result: list = []

        for i in ids:
            tok = self.id2token.get(i, "")

            if (tok in ("<PAD>", "<BOS>")):
                continue

            if (tok == "<EOS>"):
                break

            result.append(tok)

        return "".join(result)

VOCAB = DSLVocab()

def pad_grid(grid: List, max_h: int = 10, max_w: int = 10) -> torch.Tensor:
    h = min(len(grid), max_h)
    w = min(len(grid[0]) if grid else 0, max_w)
    arr = torch.full((max_h, max_w), 10, dtype=torch.long)

    for r in range(h):
        for c in range(min(len(grid[r]), max_w)):
            arr[r, c] = int(grid[r][c])

    return arr


class GridPairEncoder(nn.Module):
    def __init__(self, d_model: int = 128, max_h: int = 10, max_w: int = 10):
        super().__init__()
        d2 = d_model // 2
        self.color_embed = nn.Embedding(11, d_model, padding_idx=10)
        self.row_embed   = nn.Embedding(max_h, d2)
        self.col_embed   = nn.Embedding(max_w, d2)
        self.pair_embed  = nn.Embedding(2, d_model)
        self.norm        = nn.LayerNorm(d_model)
        self.pos_proj    = nn.Linear(d2 * 2, d_model, bias=False)

    def forward(self, inp: torch.Tensor, out: torch.Tensor) -> torch.Tensor:
        B, H, W = inp.shape
        rows = torch.arange(H, device=inp.device)
        cols = torch.arange(W, device=inp.device)
        r_e  = self.row_embed(rows)
        c_e  = self.col_embed(cols)
        pos  = torch.cat([r_e.unsqueeze(1).expand(H, W, -1),
                          c_e.unsqueeze(0).expand(H, W, -1)], dim=-1)
        pos  = self.pos_proj(pos).unsqueeze(0).expand(B, -1, -1, -1)

        def embed(grid, idx):
            c = self.color_embed(grid)
            p = self.pair_embed(torch.tensor(idx, device=grid.device))
 
            return self.norm(c + pos + p).view(B, H * W, -1)

        return torch.cat([embed(inp, 0), embed(out, 1)], dim=1)  # [B, 2HW, D]

class MultiPairEncoder(nn.Module):
    def __init__(self, d_model: int = 128, n_heads: int = 4,
                 n_layers: int = 3, max_pairs: int = 6):
        super().__init__()
        self.grid_enc = GridPairEncoder(d_model)
        self.sep      = nn.Parameter(torch.randn(1, 1, d_model) * 0.02)
        enc_layer = nn.TransformerEncoderLayer(
            d_model=d_model, nhead=n_heads, dim_feedforward=d_model*2,
            dropout=0.1, batch_first=True, norm_first=True)
        self.transformer = nn.TransformerEncoder(enc_layer, num_layers=n_layers)
        self.norm = nn.LayerNorm(d_model)

    def forward(self, grids: torch.Tensor,
                pad_mask: Optional[torch.Tensor] = None) -> torch.Tensor:
        # grids : [B, P, 2, H, W]
        B, P, _, H, W = grids.shape
        all_embs = []

        for p in range(P):
            emb = self.grid_enc(grids[:, p, 0], grids[:, p, 1])  # [B, 2HW, D]
            sep = self.sep.expand(B, 1, -1)
            all_embs.append(torch.cat([emb, sep], dim=1))

        seq = torch.cat(all_embs, dim=1)  # [B, P*(2HW+1), D]

        if pad_mask is not None:
            cells = 2 * H * W + 1
            cmask = pad_mask.unsqueeze(-1).expand(-1, -1, cells).reshape(B, -1)
        else:
            cmask = None

        return self.norm(self.transformer(seq, src_key_padding_mask=cmask))

class PositionalEncoding(nn.Module):
    def __init__(self, d_model: int, max_len: int = 256, dropout: float = 0.1):
        super().__init__()
        self.dropout = nn.Dropout(dropout)
        pe  = torch.zeros(max_len, d_model)
        pos = torch.arange(max_len).unsqueeze(1).float()
        div = torch.exp(torch.arange(0, d_model, 2).float()
                        * (-math.log(10000.0) / d_model))
        pe[:, 0::2] = torch.sin(pos * div)
        pe[:, 1::2] = torch.cos(pos * div)
        self.register_buffer("pe", pe.unsqueeze(0))

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        return self.dropout(x + self.pe[:, :x.size(1)])

class TreeState:
    def __init__(self, max_depth: int = 6):
        self.max_depth  = max_depth
        self.tree_root  : Optional[Tree] = None
        self.depth      : int = 0
        self.state      : str = "EXPECT_ROOT"
        self._token_history : List[str] = []

    def reset(self):
        self.tree_root     = None
        self.depth         = 0
        self.state         = "EXPECT_ROOT"
        self._token_history = []

    def valid_names(self) -> List[str]:
        if (self.state == "EXPECT_ROOT"):
            from typing import get_origin, get_args
            Grid = __import__("typing").Tuple[__import__("typing").Tuple[int]]
            candidates = []

            for name, (t, _) in vocabulary.items():
                ret = get_args(t)[1] if get_origin(t) is collections.abc.Callable else t

                if (compatibleType(ret, Tuple[Tuple[int]])):
                    candidates.append(name)

            return sorted(candidates)

        if (self.state == "EXPECT_ARG" and self.tree_root is not None):
            next_type = self.tree_root.nextType()

            if (next_type is None):
                self.state = "FINISHED"

                return []

            candidates = args(next_type)

            if (self.depth >= self.max_depth):
                from typing import get_origin
                candidates = [
                    n for n in candidates
                    if not (get_origin(vocabulary[n][0]) is collections.abc.Callable)
                ]

            return candidates

        return []

    def apply_token(self, token_name: str) -> bool:
        if (self.state == "FINISHED" or self.state == "ERROR"):
            return False

        valid = self.valid_names()

        if (token_name not in valid):
            self.state = "ERROR"
            return False

        self._token_history.append(token_name)

        if (self.state == "EXPECT_ROOT"):
            self.tree_root = tree(token_name)
            self.state     = "EXPECT_ARG" if not self.tree_root.isFinished() else "FINISHED"

            return True

        if (self.state == "EXPECT_ARG"):
            from typing import get_origin
            t_name, (t_type, _) = token_name, vocabulary[token_name]
            next_type           = self.tree_root.nextType()

            if (get_origin(next_type) is collections.abc.Callable):
                sub = Tree(root(token_name), [])
            else:
                sub = tree(token_name)

            if (not get_origin(next_type) is collections.abc.Callable
                    and get_origin(t_type) is collections.abc.Callable):
                self.depth += 1

            self.tree_root.applyNextType(sub)

            if (self.tree_root.isFinished()):
                self.state = "FINISHED"
            else:
                next_after = self.tree_root.nextType()

                if (next_after is None):
                    self.state = "FINISHED"

            return True

        return False

    def is_finished(self) -> bool:
        return self.state == "FINISHED"

    def is_error(self) -> bool:
        return self.state == "ERROR"

    def program(self) -> str:
        if (self.tree_root is None):
            return ""

        return str(self.tree_root)

    def valid_mask(self, token2id: Dict[str, int], vocab_size: int) -> torch.Tensor:
        mask = torch.zeros(vocab_size, dtype=torch.bool)

        if (self.is_finished()):
            if ("<EOS>" in token2id):
                mask[token2id["<EOS>"]] = True

            return mask

        valid = self.valid_names()

        for name in valid:
            if (name in token2id):
                mask[token2id[name]] = True

        if (not mask.any()):
            if ("<EOS>" in token2id):
                mask[token2id["<EOS>"]] = True

        return mask

class ARCDataset(Dataset):
    def __init__(
        self,
        data_dir : str,
        max_pairs: int = 6,
        max_h    : int = 10,
        max_w    : int = 10,
    ):
        self.max_pairs = max_pairs
        self.max_h     = max_h
        self.max_w     = max_w
        self.tasks     = []

        for path in sorted(Path(data_dir).glob("*.json")):
            try:
                with open(path) as f:
                    raw = json.load(f)

                train = [(p["input"], p["output"]) for p in raw.get("train", [])]

                if (len(train) >= 2):
                    self.tasks.append({"id": path.stem, "train": train})
            except Exception:
                pass

        print(f"[Dataset] {len(self.tasks)} ARC tasks loaded from {data_dir}")

    def __len__(self) -> int:
        return len(self.tasks)

    def __getitem__(self, idx: int) -> dict:
        task    = self.tasks[idx]
        pairs   = task["train"][:self.max_pairs]
        n_real  = len(pairs)

        grids_list = []

        for inp, out in pairs:
            grids_list.append(torch.stack([
                pad_grid(inp, self.max_h, self.max_w),
                pad_grid(out, self.max_h, self.max_w),
            ]))

        while len(grids_list) < self.max_pairs:
            grids_list.append(torch.full((2, self.max_h, self.max_w), 10,
                                         dtype=torch.long))

        grids    = torch.stack(grids_list)                       # [P, 2, H, W]
        pad_mask = torch.tensor([i >= n_real
                                 for i in range(self.max_pairs)],
                                dtype=torch.bool)                # [P]

        return {
            "grids"   : grids,
            "pad_mask": pad_mask,
            "pairs"   : pairs,
            "task_id" : task["id"],
        }

class RLDSLTransformer(nn.Module):
    def __init__(
        self,
        vocab_size  : int   = len(VOCAB),
        d_model     : int   = 128,
        n_enc_layers: int   = 3,
        n_dec_layers: int   = 4,
        n_heads     : int   = 4,
        max_pairs   : int   = 6,
        max_output  : int   = 128,
        dropout     : float = 0.1,
    ):
        super().__init__()
        self.d_model    = d_model
        self.vocab_size = vocab_size
        self.max_output = max_output

        self.encoder = MultiPairEncoder(d_model, n_heads, n_enc_layers, max_pairs)

        self.out_embed  = nn.Embedding(vocab_size, d_model)
        self.out_pe     = PositionalEncoding(d_model, max_output, dropout)
        dec_layer = nn.TransformerDecoderLayer(
            d_model=d_model, nhead=n_heads, dim_feedforward=d_model*2,
            dropout=dropout, batch_first=True, norm_first=True)
        self.decoder    = nn.TransformerDecoder(dec_layer, num_layers=n_dec_layers)
        self.output_proj = nn.Linear(d_model, vocab_size)

        self.baseline_net = nn.Sequential(
            nn.Linear(d_model, d_model),
            nn.GELU(),
            nn.Linear(d_model, 1),
            nn.Sigmoid(),
        )

        self._init_weights()

    def _init_weights(self):
        for p in self.parameters():
            if p.dim() > 1:
                nn.init.xavier_uniform_(p)

    def encode(self, grids: torch.Tensor,
               pad_mask: Optional[torch.Tensor] = None) -> torch.Tensor:
        return self.encoder(grids, pad_mask)

    def decode_step(self, tgt: torch.Tensor,
                    memory: torch.Tensor) -> torch.Tensor:
        S = tgt.size(1)
        causal = nn.Transformer.generate_square_subsequent_mask(S, device=tgt.device)
        x = self.out_embed(tgt) * math.sqrt(self.d_model)
        x = self.out_pe(x)
        x = self.decoder(x, memory, tgt_mask=causal)
        return self.output_proj(x)

    def baseline(self, memory: torch.Tensor) -> torch.Tensor:
        ctx = memory.mean(dim=1)  # [B, D]
        return self.baseline_net(ctx).squeeze(-1)  # [B]

    @torch.no_grad()
    def sample(
        self,
        grids      : torch.Tensor,
        pad_mask   : Optional[torch.Tensor] = None,
        temperature: float = 1.0,
        max_len    : int   = 128,
        device     : str   = "cpu",
    ) -> Tuple[List[List[int]], torch.Tensor]:
        self.eval()
        B       = grids.size(0)
        memory  = self.encode(grids.to(device), pad_mask)

        generated = torch.full((B, 1), VOCAB.BOS, dtype=torch.long, device=device)
        log_probs = []
        finished  = torch.zeros(B, dtype=torch.bool, device=device)

        for _ in range(max_len - 1):
            logits     = self.decode_step(generated, memory)[:, -1, :]  # [B, V]
            logits     = logits / max(temperature, 1e-6)
            probs      = F.softmax(logits, dim=-1)
            dist       = Categorical(probs)
            next_tok   = dist.sample()                    # [B]
            lp         = dist.log_prob(next_tok)          # [B]

            next_tok = next_tok.masked_fill(finished, VOCAB.PAD)
            lp       = lp.masked_fill(finished, 0.0)

            generated  = torch.cat([generated, next_tok.unsqueeze(1)], dim=1)
            log_probs.append(lp)

            finished = finished | (next_tok == VOCAB.EOS)

            if (finished.all()):
                break

        log_probs = torch.stack(log_probs, dim=1)  # [B, L-1]

        return generated, log_probs

    def forward(self, grids: torch.Tensor, tgt: torch.Tensor,
                pad_mask: Optional[torch.Tensor] = None) -> torch.Tensor:
        memory = self.encode(grids, pad_mask)

        return self.decode_step(tgt, memory)

class BatchTreeStateManager:
    def __init__(self, batch_size: int, max_depth: int = 6):
        self.states = [TreeState(max_depth) for _ in range(batch_size)]

    def valid_masks(
        self,
        token2id   : Dict[str, int],
        vocab_size : int,
        device     : str = "cpu",
    ) -> torch.Tensor:
        masks = torch.stack([
            s.valid_mask(token2id, vocab_size)
            for s in self.states
        ])

        return masks.to(device)

    def apply_tokens(self, token_names: List[str]) -> None:
        for state, name in zip(self.states, token_names):
            if (not state.is_finished() and not state.is_error()):
                state.apply_token(name)

    def all_finished(self) -> bool:
        return all(s.is_finished() or s.is_error() for s in self.states)

    def programs(self) -> List[str]:
        return [s.program() for s in self.states]

    def reset_all(self):
        for s in self.states:
            s.reset()

import dsl_engine

arc_types = dsl_engine.load_module("arc_types", "arc-dsl/arc_types.py")
constants = dsl_engine.load_module("constants",  "arc-dsl/constants.py")
dsl       = dsl_engine.load_module("dsl",        "arc-dsl/dsl.py")
ns = {}
ns.update(vars(arc_types))
ns.update(vars(constants))
ns.update(vars(dsl))

def execute_dsl(program: str, input_grid: List) -> Optional[List]:
    try:
        ns["I"] = tuple(map(tuple, input_grid))
        result = eval(program, {"__builtins__": {}}, ns)

        return result
    except Exception:
        pass

    return None

def compute_reward(
    program        : str,
    pairs          : List[Tuple],
    execute_fn     = None,          # function execute_dsl(program, input) → output|None
    cost_fn        = None,          # function arc_cost(output, target) → float
    alpha          : float = 0.02,  # term length weight
    length_unit    : str   = "tokens",  # "tokens" or "chars"
) -> Tuple[float, Dict]:
    if (not program or "I" not in program):
        return 0.0, {"cost": float("inf"), "length": 0, "r_cost": 0.0, "r_len": 0.0, "reward": 0.0}

    if (execute_fn is None or cost_fn is None):
        execute_fn = execute_fn or execute_dsl
        cost_fn    = cost_fn    or arcHeuristic

    total_cost = 0.0

    for inp, out in pairs:
        result     = execute_fn(program, inp)
        total_cost += cost_fn(result, out)

    avg_cost = total_cost / max(len(pairs), 1)
    r_cost   = 1.0 / (1.0 + avg_cost)

    if (length_unit == "tokens"):
        L = sum(1 for name in vocabulary if name in program)
    else:
        L = len(program)

    r_len = 1.0 / (1.0 + L)

    reward = r_cost + alpha * r_len

    details = {
        "avg_cost" : avg_cost,
        "length"   : L,
        "r_cost"   : r_cost,
        "r_len"    : r_len,
        "reward"   : reward,
    }

    return reward, details

def reward_batch(
    programs       : List[str],
    pairs_batch    : List[List[Tuple]],
    **kwargs,
) -> Tuple[torch.Tensor, List[Dict]]:
    rewards = []
    details = []

    for prog, pairs in zip(programs, pairs_batch):
        r, d = compute_reward(prog, pairs, **kwargs)
        rewards.append(r)
        details.append(d)
    
    return torch.tensor(np.array(rewards), dtype=torch.float32), details

@torch.no_grad()
def sample_with_tree_mask(
    model,                          # RLDSLTransformer
    vocab,                          # DSLVocab (with .token2id, .BOS, .EOS, .PAD)
    grids      : torch.Tensor,      # [B, P, 2, H, W]
    pad_mask   : torch.Tensor,      # [B, P]
    temperature: float = 1.0,
    max_len    : int   = 128,
    max_depth  : int   = 6,
    device     : str   = "cpu",
) -> Tuple[torch.Tensor, torch.Tensor, List[str]]:
    import torch.nn.functional as F
    from torch.distributions import Categorical

    model.eval()
    B      = grids.size(0)
    memory = model.encode(grids.to(device), pad_mask.to(device))

    manager   = BatchTreeStateManager(B, max_depth=max_depth)
    generated = torch.full((B, 1), vocab.BOS, dtype=torch.long, device=device)
    log_probs = []
    finished  = torch.zeros(B, dtype=torch.bool, device=device)

    for step in range(max_len - 1):
        logits = model.decode_step(generated, memory)[:, -1, :]  # [B, V]
        logits = logits / max(temperature, 1e-6)

        mask = manager.valid_masks(vocab.token2id, len(vocab), device=device)
        logits = logits.masked_fill(~mask, float("-inf"))

        probs    = F.softmax(logits, dim=-1)
        dist     = Categorical(probs)
        next_tok = dist.sample()          # [B]
        lp       = dist.log_prob(next_tok)

        next_tok = next_tok.masked_fill(finished, vocab.PAD)
        lp       = lp.masked_fill(finished, 0.0)

        token_names = [
            vocab.id2token.get(tid.item(), "<PAD>")
            for tid in next_tok
        ]
        manager.apply_tokens(token_names)

        generated = torch.cat([generated, next_tok.unsqueeze(1)], dim=1)
        log_probs.append(lp)

        eos_mask = (next_tok == vocab.EOS)
        tree_done = torch.tensor(
            [s.is_finished() or s.is_error() for s in manager.states],
            dtype=torch.bool, device=device
        )
        finished = finished | eos_mask | tree_done

        if (finished.all()):
            break

    log_probs_t = torch.stack(log_probs, dim=1)  # [B, L-1]
    programs    = manager.programs()

    max_actual_len = generated.size(1)

    if (max_actual_len < max_len):
        padded_log_probs = torch.zeros(B, max_len-1, device=device)
        padded_log_probs[:, :max_actual_len-1] = log_probs_t
        log_probs_t = padded_log_probs

        padded_generated = torch.full((B, max_len), vocab.PAD, dtype=torch.long, device=device)
        padded_generated[:, :max_actual_len] = generated
        generated = padded_generated

    return generated, log_probs_t, programs

def collate_rl(batch: List[dict]) -> dict:
    return {
        "grids"   : torch.stack([b["grids"]    for b in batch]),
        "pad_mask": torch.stack([b["pad_mask"] for b in batch]),
        "pairs"   : [b["pairs"]   for b in batch],
        "task_ids": [b["task_id"] for b in batch],
    }

def reinforce_loss(
    log_probs  : torch.Tensor,   # [B, L]  log-proba of eachc token
    rewards    : torch.Tensor,   # [B]     total reward by program
    baselines  : torch.Tensor,   # [B]     guessed reward (criticak)
    mask       : torch.Tensor,   # [B, L]  True = valid token (no PAD/EOS)
) -> torch.Tensor:
    advantage = (rewards - baselines).detach()  # [B]  — no gradient on b
    advantage = advantage.unsqueeze(1)           # [B, 1] for broadcast

    weighted  = -log_probs * advantage * mask.float()
    return weighted.sum() / mask.float().sum().clamp(min=1)

def baseline_loss(
    predicted_baseline : torch.Tensor,   # [B]
    rewards            : torch.Tensor,   # [B]
) -> torch.Tensor:
    return F.mse_loss(predicted_baseline, rewards.detach())

def train_rl(
    model,
    dataset,
    vocab,
    epochs      : int   = 100,
    batch_size  : int   = 8,
    lr          : float = 3e-4,
    temperature : float = 1.0,
    k_samples   : int   = 4,
    device      : str   = "cuda",
    ckpt_path   : str   = "dsl_rl_tree.pt",
    temp_decay  : float = 0.995,
    min_temp    : float = 0.3,
    max_depth   : int   = 6,
    alpha: float = 0.02,
    log_every   : int   = 10,
):
    from torch.utils.data import DataLoader
    import torch.optim as optim
    import torch.nn as nn

    model = model.to(device)
    loader = DataLoader(dataset, batch_size=batch_size, shuffle=True,
                        collate_fn=collate_rl, num_workers=2,
                        pin_memory=(device != "cpu"))

    optimizer = optim.AdamW(model.parameters(), lr=lr, weight_decay=1e-4)
    scheduler = optim.lr_scheduler.CosineAnnealingLR(optimizer, T_max=epochs)

    best_reward = 0.0
    temp        = temperature

    for epoch in range(1, epochs + 1):
        model.train()
        epoch_reward = 0.0
        epoch_loss   = 0.0
        n_batches    = 0
        n_perfect    = 0

        for batch in loader:
            grids     = batch["grids"].to(device)
            pad_mask  = batch["pad_mask"].to(device)
            all_pairs = batch["pairs"]
            B         = grids.size(0)

            with torch.no_grad():
                memory = model.encode(grids, pad_mask)

            all_lp, all_rw, all_mk = [], [], []

            for _ in range(k_samples):
                model.eval()
                generated, log_probs, programs = sample_with_tree_mask(
                    model, vocab, grids, pad_mask,
                    temperature=temp, max_depth=max_depth, device=device,
                )
                model.train()

                rewards_t, details = reward_batch(
                    programs, all_pairs, alpha=alpha,
                )
                rewards_t = rewards_t.to(device)

                for d in details:
                    if (d["reward"] >= 0.99):
                        n_perfect += 1

                L    = log_probs.size(1)
                mask = (generated[:, 1:1+L] != vocab.PAD)
                all_lp.append(log_probs)
                all_rw.append(rewards_t)
                all_mk.append(mask)

            lp_cat = torch.cat(all_lp, dim=0)
            rw_cat = torch.cat(all_rw, dim=0)
            mk_cat = torch.cat(all_mk, dim=0)

            # Baseline
            grids_rep    = grids.repeat_interleave(k_samples, dim=0)
            pad_mask_rep = pad_mask.repeat_interleave(k_samples, dim=0)
            mem_rep      = model.encode(grids_rep, pad_mask_rep)
            bl_pred      = model.baseline(mem_rep)

            loss_rl = reinforce_loss(lp_cat, rw_cat, bl_pred.detach(), mk_cat)
            loss_bl = baseline_loss(bl_pred, rw_cat)
            loss    = loss_rl + 0.5 * loss_bl

            optimizer.zero_grad()
            loss.backward()
            nn.utils.clip_grad_norm_(model.parameters(), 1.0)
            optimizer.step()

            epoch_reward += rw_cat.mean().item()
            epoch_loss   += loss.item()
            n_batches    += 1

        scheduler.step()
        temp = max(min_temp, temp * temp_decay)

        avg_r = epoch_reward / max(n_batches, 1)
        avg_l = epoch_loss   / max(n_batches, 1)

        if (epoch % log_every == 0 or epoch == 1):
            print(f"Epoch {epoch:4d}/{epochs}"
                  f"  reward={avg_r:.4f}"
                  f"  loss={avg_l:.4f}"
                  f"  perfect={n_perfect}"
                  f"  temp={temp:.3f}")

        if (avg_r > best_reward):
            best_reward = avg_r
            torch.save({
                "model_state": model.state_dict(),
                "d_model"    : model.d_model,
                "vocab_size" : model.vocab_size,
            }, ckpt_path)
            print(f"  ✓ Saved (reward={best_reward:.4f})")

    print(f"\n[RL+Tree] Finished. Best reward={best_reward:.4f}")

def save_model(model: RLDSLTransformer, path: str):
    torch.save({"model_state": model.state_dict(),
                "d_model"    : model.d_model,
                "vocab_size" : model.vocab_size}, path)
    meta = path + ".json"

    with open(meta, "w") as f:
        json.dump({
            "vocab_tokens": VOCAB.tokens,
            "d_model"     : model.d_model,
        }, f, indent=2)

def load_model(path: str, device: str = "cpu") -> RLDSLTransformer:
    ckpt  = torch.load(path, map_location=device, weights_only=True)
    model = RLDSLTransformer(
        vocab_size=ckpt["vocab_size"],
        d_model   =ckpt["d_model"],
    )
    model.load_state_dict(ckpt["model_state"])
    model.to(device)
    print(f"[Load] ← {path}")

    return model

def load_task(task_id: str, arc_root: str = "..",
              max_pairs: int = 6) -> Tuple[torch.Tensor, torch.Tensor, List]:
    for split in ("training", "evaluation", "test"):
        p = Path(arc_root) / "ARC-AGI-2" / "data" / split / f"{task_id}.json"

        if (p.exists()):
            break
    else:
        raise FileNotFoundError(f"Task {task_id} not found under {arc_root}")

    with open(p) as f:
        data = json.load(f)

    pairs   = [(ex["input"], ex["output"]) for ex in data["train"]][:max_pairs]
    n_real  = len(pairs)

    glist = [torch.stack([pad_grid(i), pad_grid(o)]) for i, o in pairs]

    while (len(glist) < max_pairs):
        glist.append(torch.full((2, 10, 10), 10, dtype=torch.long))

    grids    = torch.stack(glist).unsqueeze(0)       # [1, P, 2, H, W]
    pad_mask = torch.tensor([[i >= n_real
                               for i in range(max_pairs)]], dtype=torch.bool)

    return grids, pad_mask, pairs

if (__name__ == "__main__"):
    import random
    random.seed(0)

    print("=== Test TreeState ===")

    state = TreeState(max_depth = 4)
    print(f"Initial state: {state.state}")
    print(f"Valid tokens: {state.valid_names()[:5]}...")

    state.apply_token("fill")
    print(f"\nAfter 'fill': {state.program()}")
    print(f"Valid tokens: {state.valid_names()[:5]}...")

    state.apply_token("I")
    print(f"\nAfter 'I': {state.program()}")
    print(f"Valid tokens: {state.valid_names()[:5]}...")

    state.apply_token("mostcolor")
    state.apply_token("I")
    print(f"\nAfter 'mostcolor(I)': {state.program()}")
    print(f"Finished: {state.is_finished()}")

    state.apply_token("asobject")
    state.apply_token("I")
    print(f"\nAfter 'asobject(I)': {state.program()}")
    print(f"Finished: {state.is_finished()}")

    print("\n=== Test reward ===")

    import numpy as np
    np.random.seed(0)

    inp = np.random.randint(0, 5, (4, 4)).tolist()
    out = np.rot90(inp, 2).tolist()
    pairs = [(inp, out)]

    for prog, label in [
        ("rot180(I)",                       "exact solution"),
        ("rot90(I)",                          "wrong rotation"),
        ("hmirror(vmirror(I))",              "correct composition but long"),
        ("I",                                 "identity"),
    ]:
        r, d = compute_reward(prog, pairs)
        print(f"  {label:40s} : reward={r:.4f}"
              f"  r_cost={d['r_cost']:.4f}"
              f"  r_len={d['r_len']:.4f}"
              f"  L={d['length']}")

    print("\n=== Test mask vocab ===")

    token2id = VOCAB.token2id
    vocab_size = len(token2id)

    state2 = TreeState()
    mask   = state2.valid_mask(token2id, vocab_size)
    valid  = [t for t, i in token2id.items() if mask[i]]
    print(f"Valid tokens at start (Grid roots): {valid}")

    state2.apply_token("rot90")
    mask  = state2.valid_mask(token2id, vocab_size)
    valid = [t for t, i in token2id.items() if mask[i]]
    print(f"After 'rot90', valid tokens (arg Grid): {valid}")

    state2.apply_token("I")
    mask  = state2.valid_mask(token2id, vocab_size)
    valid = [t for t, i in token2id.items() if mask[i]]
    print(f"After 'rot90(I)', finished={state2.is_finished()}, valid: {valid}")

    device: str = "cuda"
    modelName: str = "dsl_rl.pt"

    if (os.path.exists(modelName)):
        model = load_model(modelName, device)
    else:
        d_model: int = 128
        model = RLDSLTransformer(d_model = d_model).to(device)
        n_param = sum(p.numel() for p in model.parameters())
        print(f"[Model] {n_param:,} parameters d_model={d_model}")

    if ("train" in sys.argv):
        import copy
        import test_dsl_engine

        tasksByStep: dict = test_dsl_engine.hodelTasksByStep()
        dataset = ARCDataset("../ARC-AGI-2/data/training")
        epochs: int = 1000
        lr: float = 3e-4
        temperature: float = 1.0
        min_temp: float = 1.0
        k_samples: int = 4
        log_every: int = 1

        for k, v in tasksByStep.items():
            subdataset = copy.deepcopy(dataset)
            tasks: list = []

            for task in subdataset.tasks:
                if (task["id"] in v):
                    tasks.append(task)

            subdataset.tasks = tasks
            
            print(f"[Subdataset] {len(tasks)} Hodel ARC tasks of {k} step{'s' if k > 1 else ''} of DSL")

            train_rl(
                model, subdataset,
                VOCAB,
                epochs = epochs, batch_size = len(tasks),
                lr = lr, temperature = temperature,
                k_samples = k_samples,
                device = device, ckpt_path = modelName,
                log_every = log_every,
                max_depth = k - 1, min_temp = min_temp
            )

        batch_size: int = 50

        train_rl(
            model, dataset,
            VOCAB,
            epochs = epochs, batch_size = batch_size,
            lr = lr, temperature = temperature,
            k_samples = k_samples,
            device = device, ckpt_path = modelName,
            log_every = log_every,
            max_depth = 32,
        )

    task: str = "67a3c6ac"
    n: int = 10
    temp: float = 0.5
    max_depth: int = 2
    grids, pad_mask, pairs = load_task(task, "..")
    print(f"Task {task} — {len(pairs)} train pairs")
    results: list = []

    for i in range(n):
        generated, log_probs, programs = sample_with_tree_mask(
            model, VOCAB, grids, pad_mask,
            temperature = temp, max_depth = max_depth, device = device,
        )
        prog    = programs[0]
        r, d    = compute_reward(prog, pairs)
        results.append((r, prog))
        print(f"  [{i+1:2d}] reward={r:.4f}  {prog[:70]}")

    best_r, best_p = max(results, key=lambda x: x[0])
    print(f"\nBest : reward={best_r:.4f}  {best_p}")
