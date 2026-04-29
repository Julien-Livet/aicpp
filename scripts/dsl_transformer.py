from __future__ import annotations
import ast
from dataclasses import dataclass, field
import json
import math
from pathlib import Path
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.utils.data import Dataset, DataLoader
import torch.optim as optim
from typing import Dict, List, Optional, Tuple

def getDslVariables() -> Dict[str, str]:
    import test_arc

    arc_types_module = test_arc.load_module("arc_types", "arc-dsl/arc_types.py")

    with open("arc-dsl/constants.py", "r") as f:
        content = f.read()

    namespace = {}
    namespace.update(vars(arc_types_module))

    types = {}

    for k, v in namespace.items():
        if (not k.startswith("_")):
            types[v] = k

    from typing import Tuple

    types[tuple] = Tuple

    exec(content, namespace)

    variables = {}

    for k, v in namespace.items():
        if (not k in vars(arc_types_module)):
            variables[k] = types[type(v)]

    variables["I"] = types[Tuple[Tuple]]

    return variables

def getDslPrimitives() -> Dict[str, dict]:
    with open("arc-dsl/dsl.py", "r") as f:
        lines = f.read().split("\n")

    i = 0
    definition = ""
    primitives = {}
    
    while (i < len(lines)):
        if (lines[i].startswith("def ")):
            definition = lines[i]        

        if (definition.endswith(":")):
            definition = definition.replace("def", "").replace(" ", "")[:-1]

            sig = "def " + definition + ": pass"

            tree = ast.parse(sig)
            func = tree.body[0]

            args = []

            for arg in func.args.args:
                args.append({"name": arg.arg, "type": ast.unparse(arg.annotation)})

            primitives[func.name] = {"args": args, "return_type": ast.unparse(func.returns)}

            definition = ""
        elif (len(definition) and not lines[i].startswith("def ")):
            definition += lines[i]

        i += 1

    return primitives

@dataclass
class Vocabulary:
    input_tokens  : List[str] = field(default_factory = list)
    input_to_id   : Dict[str, int] = field(default_factory = dict)

    output_tokens : List[str] = field(default_factory = list)
    output_to_id  : Dict[str, int] = field(default_factory = dict)

    dsl_variables  : Dict[str, str]  = field(default_factory = dict)
    dsl_primitives : Dict[str, dict] = field(default_factory = dict)

    PAD : int = 0
    BOS : int = 1
    EOS : int = 2

    @classmethod
    def build(cls) -> "Vocabulary":
        vocab = cls()

        digits = [str(i) for i in range(10)]

        specials     = ["<PAD>", "<BOS>", "<EOS>"]
        grid_chars   = digits + ["|", ",", "-"]
        vocab.input_tokens  = specials + grid_chars
        vocab.input_to_id   = {t: i for i, t in enumerate(vocab.input_tokens)}

        vocab.dsl_variables  = getDslVariables()
        vocab.dsl_primitives = getDslPrimitives()
        structural = [",", "(", ")"]
        variables  = list(vocab.dsl_variables.keys())
        primitives = list(vocab.dsl_primitives.keys())
        vocab.output_tokens = specials + structural + digits + sorted(variables) + sorted(primitives)
        vocab.output_to_id  = {t: i for i, t in enumerate(vocab.output_tokens)}

        vocab.PAD = vocab.output_to_id["<PAD>"]
        vocab.BOS = vocab.output_to_id["<BOS>"]
        vocab.EOS = vocab.output_to_id["<EOS>"]

        return vocab

    @property
    def input_size(self) -> int:
        return len(self.input_tokens)

    @property
    def output_size(self) -> int:
        return len(self.output_tokens)

    def encode_input(self, text: str, max_len: int = 2048) -> List[int]:
        ids = [self.input_to_id.get("<BOS>", 1)]

        for ch in text:
            ids.append(self.input_to_id.get(ch, self.input_to_id.get("<PAD>", 0)))

        ids.append(self.input_to_id.get("<EOS>", 2))
        ids = ids[:max_len]
        ids += [0] * (max_len - len(ids))

        return ids

    def encode_output(self, program: str, max_len: int = 256) -> List[int]:
        ids = [self.BOS]
        i   = 0

        all_tokens = sorted(
            [t for t in self.output_tokens if t not in ("<PAD>", "<BOS>", "<EOS>")],
            key = len, reverse = True
        )

        while (i < len(program)):
            matched = False

            for tok in all_tokens:
                if program[i:i+len(tok)] == tok:
                    ids.append(self.output_to_id[tok])
                    i += len(tok)
                    matched = True
                    break

            if (not matched):
                i += 1  # caractère inconnu, skip

        ids.append(self.EOS)
        ids = ids[:max_len]
        ids += [self.PAD] * (max_len - len(ids))

        return ids

    def decode_output(self, ids: List[int]) -> str:
        result = []

        for i in ids:
            tok = self.output_tokens[i] if i < len(self.output_tokens) else ""

            if (tok in ("<PAD>", "<BOS>")):
                continue

            if (tok == "<EOS>"):
                break

            result.append(tok)

        return "".join(result)

class TypeSystem:
    def __init__(self, vocab: Vocabulary):
        self.vocab      = vocab
        self.variables  = vocab.dsl_variables
        self.primitives = vocab.dsl_primitives

        self.grid_types = {
            t for t in ["Grid", "Tuple[Tuple[int]]", "tuple"]
        }

        self.grid_primitives = {
            name for name, spec in self.primitives.items()
            if self._is_grid_type(str(spec["return_type"]))
        }

        self.grid_variables = {
            name for name, typ in self.variables.items()
            if self._is_grid_type(str(typ))
        }

    def _is_grid_type(self, t: str) -> bool:
        return any(g in t for g in ["Grid", "Tuple[Tuple", "tuple"])

    def _is_int_type(self, t: str) -> bool:
        return "int" in t or "Integer" in t

    def _is_bool_type(self, t: str) -> bool:
        return "bool" in t or "Boolean" in t

    def _tokens_of_type(self, expected_type: str) -> set:
        result = set()

        for name, typ in self.variables.items():
            if (self._type_compatible(str(typ), expected_type)):
                result.add(name)

        for name, spec in self.primitives.items():
            if (self._type_compatible(str(spec["return_type"]), expected_type)):
                result.add(name)

        return result

    def _type_compatible(self, actual: str, expected: str) -> bool:
        if (expected == "Any" or actual == "Any"):
            return True

        if (expected == actual):
            return True

        if (self._is_grid_type(expected) and self._is_grid_type(actual)):
            return True

        if self._is_int_type(expected) and self._is_int_type(actual):
            return True

        if self._is_bool_type(expected) and self._is_bool_type(actual):
            return True

        return False

    def valid_mask(
        self,
        partial_program : str,
        vocab           : Vocabulary,
    ) -> torch.Tensor:
        mask = torch.zeros(vocab.output_size, dtype = torch.bool)

        if (self._is_complete(partial_program)):
            mask[vocab.EOS] = True

            return mask

        ctx = self._parse_context(partial_program)

        if (ctx["state"] == "expect_root"):
            for name in self.grid_primitives:
                if (name in vocab.output_to_id):
                    mask[vocab.output_to_id[name]] = True
        elif (ctx["state"] == "expect_open_paren"):
            if ("(" in vocab.output_to_id):
                mask[vocab.output_to_id["("]] = True
        elif (ctx["state"] == "expect_arg"):
            expected = ctx.get("expected_type", "Any")

            for tok in self._tokens_of_type(expected):
                if (tok in vocab.output_to_id):
                    mask[vocab.output_to_id[tok]] = True
        elif (ctx["state"] == "expect_comma_or_close"):
            if (ctx.get("has_more_args", False)):
                if ("," in vocab.output_to_id):
                    mask[vocab.output_to_id[","]] = True
            else:
                if (")" in vocab.output_to_id):
                    mask[vocab.output_to_id[")"]] = True
        elif (ctx["state"] == "expect_close"):
            if (")" in vocab.output_to_id):
                mask[vocab.output_to_id[")"]] = True
        else:
            mask[:] = True
            mask[vocab.PAD] = False

        return mask

    def _is_complete(self, program: str) -> bool:
        if (not program):
            return False

        depth = 0

        for ch in program:
            if (ch == "("):
                depth += 1
            elif (ch == ")"):
                depth -= 1

        return depth == 0 and "(" in program

    def _parse_context(self, partial: str) -> dict:
        if (not partial):
            return {"state": "expect_root"}

        depth = sum(1 if c == "(" else -1 if c == ")" else 0 for c in partial)

        stack = [] # (primitive_name, arg_index)
        i = 0
        tokens = self._tokenize_partial(partial)

        for j, tok in enumerate(tokens):
            if (tok in self.primitives):
                if (j + 1 < len(tokens) and tokens[j + 1] == "("):
                    spec = self.primitives[tok]
                    stack.append({"name": tok, "spec": spec, "arg_idx": 0, "arg_depth": 0})
            elif (tok == "(" and stack):
                pass
            elif (tok == "," and stack):
                stack[-1]["arg_idx"] += 1
            elif (tok == ")" and stack):
                stack.pop()

        last = tokens[-1] if tokens else ""

        if (not stack):
            if (last in self.primitives):
                return {"state": "expect_open_paren"}

            return {"state": "expect_root"}

        top      = stack[-1]
        spec     = top["spec"]
        arg_idx  = top["arg_idx"]
        n_args   = len(spec["args"])

        if (last == "(" or last == ","):
            if (arg_idx < n_args):
                expected_type = str(spec["args"][arg_idx]["type"])

                return {
                    "state"        : "expect_arg",
                    "expected_type": expected_type,
                    "primitive"    : top["name"],
                    "arg_idx"      : arg_idx,
                }

            return {"state": "expect_close"}

        if (arg_idx < n_args - 1):
            return {"state": "expect_comma_or_close", "has_more_args": True}
        else:
            return {"state": "expect_comma_or_close", "has_more_args": False}

    def _tokenize_partial(self, program: str) -> List[str]:
        tokens = []

        known = sorted(
            list(self.primitives.keys()) + list(self.variables.keys()) + ["(", ")", ","],
            key = len, reverse = True
        )
        i = 0

        while (i < len(program)):
            matched = False

            for tok in known:
                if (program[i:i+len(tok)] == tok):
                    if (tok.strip()):
                        tokens.append(tok)

                    i += len(tok)
                    matched = True
                    break

            if (not matched):
                i += 1

        return tokens

class PositionalEncoding(nn.Module):
    def __init__(self, d_model: int, max_len: int = 4096, dropout: float = 0.1):
        super().__init__()
        self.dropout = nn.Dropout(dropout)
        pe  = torch.zeros(max_len, d_model)
        pos = torch.arange(max_len).unsqueeze(1).float()
        div = torch.exp(torch.arange(0, d_model, 2).float() * (-math.log(10000.0) / d_model))
        pe[:, 0::2] = torch.sin(pos * div)
        pe[:, 1::2] = torch.cos(pos * div)
        self.register_buffer("pe", pe.unsqueeze(0))  # [1, max_len, d_model]

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        return self.dropout(x + self.pe[:, :x.size(1)])

class DSLTransformer(nn.Module):
    def __init__(
        self,
        input_vocab_size  : int,
        output_vocab_size : int,
        d_model    : int   = 256,
        n_heads    : int   = 4,
        n_layers   : int   = 6,
        ff_dim     : int   = 512,
        dropout    : float = 0.1,
        max_input  : int   = 2048,
        max_output : int   = 256,
    ):
        super().__init__()
        self.d_model = d_model

        self.input_embed  = nn.Embedding(input_vocab_size, d_model)
        self.input_pe     = PositionalEncoding(d_model, max_input, dropout)
        enc_layer = nn.TransformerEncoderLayer(
            d_model = d_model, nhead = n_heads, dim_feedforward = ff_dim,
            dropout = dropout, batch_first = True, norm_first = True,
        )
        self.encoder = nn.TransformerEncoder(enc_layer, num_layers = n_layers)

        self.output_embed = nn.Embedding(output_vocab_size, d_model)
        self.output_pe    = PositionalEncoding(d_model, max_output, dropout)
        dec_layer = nn.TransformerDecoderLayer(
            d_model = d_model, nhead = n_heads, dim_feedforward = ff_dim,
            dropout = dropout, batch_first = True, norm_first = True,
        )
        self.decoder = nn.TransformerDecoder(dec_layer, num_layers = n_layers)

        self.output_proj = nn.Linear(d_model, output_vocab_size)

        self._init_weights()

    def _init_weights(self):
        for p in self.parameters():
            if p.dim() > 1:
                nn.init.xavier_uniform_(p)

    def encode(
        self,
        src     : torch.Tensor,  # [B, S_in]
        src_pad_mask: Optional[torch.Tensor] = None,
    ) -> torch.Tensor:
        """Encoder: grids → memory [B, S_in, D]"""
        x = self.input_embed(src) * math.sqrt(self.d_model)
        x = self.input_pe(x)
        return self.encoder(x, src_key_padding_mask = src_pad_mask)

    def decode(
        self,
        tgt     : torch.Tensor,  # [B, S_out]
        memory  : torch.Tensor,  # [B, S_in, D]
        tgt_pad_mask : Optional[torch.Tensor] = None,
        src_pad_mask : Optional[torch.Tensor] = None,
    ) -> torch.Tensor:
        """Decoder: DSL tokens + memory → logits [B, S_out, V_out]"""
        S = tgt.size(1)
        causal_mask = nn.Transformer.generate_square_subsequent_mask(S, device = tgt.device)

        x = self.output_embed(tgt) * math.sqrt(self.d_model)
        x = self.output_pe(x)
        x = self.decoder(
            x, memory,
            tgt_mask = causal_mask,
            tgt_key_padding_mask = tgt_pad_mask,
            memory_key_padding_mask = src_pad_mask,
        )
        return self.output_proj(x)  # [B, S_out, V_out]

    def forward(
        self,
        src      : torch.Tensor,
        tgt      : torch.Tensor,
        src_pad  : Optional[torch.Tensor] = None,
        tgt_pad  : Optional[torch.Tensor] = None,
    ) -> torch.Tensor:
        memory = self.encode(src, src_pad)
        return self.decode(tgt, memory, tgt_pad, src_pad)

class DSLDataset(Dataset):
    """
    Pair dataset (ARC text grids, DSL program).

    JSONL file format:
    {"input": "012|345,210|543|-789,987", "output": "rot90(hmirror(I))"}
    """

    def __init__(
        self,
        path       : str,
        vocab      : Vocabulary,
        max_input  : int = 512,
        max_output : int = 128,
        max_seq_filter: int = 512,
    ):
        self.vocab      = vocab
        self.max_input  = max_input
        self.max_output = max_output
        self.samples    : List[dict] = []

        skipped = 0

        with open(path, "r") as f:
            for line in f:
                line = line.strip()

                if (line):
                    try:
                        s = json.loads(line)

                        if (len(s.get("input", "")) <= max_seq_filter):
                            self.samples.append(s)
                        else:
                            skipped += 1
                    except json.JSONDecodeError:
                        pass

        print(f"[Dataset] {len(self.samples)} loaded examples "
              f"({skipped} filtered > {max_seq_filter} chars) from {path}")

    def __len__(self) -> int:
        return len(self.samples)

    def __getitem__(self, idx: int) -> dict:
        sample = self.samples[idx]
        src_ids = self.vocab.encode_input(sample["input"],  self.max_input)
        tgt_ids = self.vocab.encode_output(sample["output"], self.max_output)

        src = torch.tensor(src_ids, dtype = torch.long)
        tgt = torch.tensor(tgt_ids, dtype = torch.long)

        src_pad = (src == 0)
        tgt_pad = (tgt == self.vocab.PAD)

        return {
            "src"    : src,
            "tgt"    : tgt,
            "src_pad": src_pad,
            "tgt_pad": tgt_pad,
            "program": sample["output"],
        }

def _collate_trim(batch: List[dict]) -> dict:
    max_src = max(b["src"].ne(0).sum().item() + 1 for b in batch)
    max_tgt = max(b["tgt"].ne(0).sum().item() + 1 for b in batch)
    max_src = min(max_src, batch[0]["src"].size(0))
    max_tgt = min(max_tgt, batch[0]["tgt"].size(0))

    return {
        "src"    : torch.stack([b["src"][:max_src]     for b in batch]),
        "tgt"    : torch.stack([b["tgt"][:max_tgt]     for b in batch]),
        "src_pad": torch.stack([b["src_pad"][:max_src] for b in batch]),
        "tgt_pad": torch.stack([b["tgt_pad"][:max_tgt] for b in batch]),
        "program": [b["program"] for b in batch],
    }

def train(
    model         : DSLTransformer,
    dataset       : DSLDataset,
    vocab         : Vocabulary,
    epochs        : int   = 50,
    batch_size    : int   = 8,
    lr            : float = 3e-4,
    device        : str   = "cuda",
    ckpt_path     : str   = "dsl_transformer.pt",
    val_split     : float = 0.1,
    grad_accum    : int   = 4,
    use_amp       : bool  = True,   # mixed precision fp16
):
    model = model.to(device)

    if (hasattr(model.encoder, "enable_nested_tensor")):
        pass

    try:
        model.encoder.enable_gradient_checkpointing = True
        model.decoder.enable_gradient_checkpointing = True
    except AttributeError:
        pass

    # Split train/val
    n_val   = max(1, int(len(dataset) * val_split))
    n_train = len(dataset) - n_val
    train_set, val_set = torch.utils.data.random_split(dataset, [n_train, n_val])

    train_loader = DataLoader(
        train_set, batch_size = batch_size, shuffle = True,
        drop_last = True, collate_fn = _collate_trim,
        num_workers = 2, pin_memory = (device != "cpu"),
    )
    val_loader = DataLoader(
        val_set, batch_size = batch_size, shuffle = False,
        collate_fn = _collate_trim,
        num_workers = 2, pin_memory = (device != "cpu"),
    )

    optimizer = optim.AdamW(model.parameters(), lr = lr, weight_decay = 1e-4)
    scheduler = optim.lr_scheduler.CosineAnnealingLR(optimizer, T_max = epochs)
    criterion = nn.CrossEntropyLoss(ignore_index = vocab.PAD, label_smoothing = 0.1)

    # AMP scaler (no-op if device=cpu or if use_amp=False)
    use_amp   = use_amp and (device != "cpu") and torch.cuda.is_available()
    scaler    = torch.amp.GradScaler(device, enabled = use_amp)

    best_val_loss = float("inf")

    print(f"[Train] batch_size={batch_size}  grad_accum={grad_accum}  "
          f"batch_effective={batch_size*grad_accum}  AMP={use_amp}")

    for epoch in range(1, epochs + 1):
        # Train
        model.train()
        total_loss  = 0.0
        optimizer.zero_grad()

        for step, batch in enumerate(train_loader):
            src     = batch["src"].to(device)
            tgt     = batch["tgt"].to(device)
            src_pad = batch["src_pad"].to(device)
            tgt_pad = batch["tgt_pad"].to(device)

            tgt_in     = tgt[:, :-1]
            tgt_out    = tgt[:, 1:]
            tgt_pad_in = tgt_pad[:, :-1]

            # Forward with AMP
            with torch.amp.autocast(device, enabled=use_amp):
                logits = model(src, tgt_in, src_pad, tgt_pad_in)
                loss   = criterion(
                    logits.reshape(-1, vocab.output_size),
                    tgt_out.reshape(-1),
                ) / grad_accum   # normaliser pour l'accumulation

            scaler.scale(loss).backward()

            if ((step + 1) % grad_accum == 0):
                scaler.unscale_(optimizer)
                nn.utils.clip_grad_norm_(model.parameters(), 1.0)
                scaler.step(optimizer)
                scaler.update()
                optimizer.zero_grad()

            total_loss += loss.item() * grad_accum

        avg_train = total_loss / max(len(train_loader), 1)

        # Validation
        model.eval()
        val_loss = 0.0

        with torch.no_grad():
            for batch in val_loader:
                src     = batch["src"].to(device)
                tgt     = batch["tgt"].to(device)
                src_pad = batch["src_pad"].to(device)
                tgt_pad = batch["tgt_pad"].to(device)

                tgt_in     = tgt[:, :-1]
                tgt_out    = tgt[:, 1:]
                tgt_pad_in = tgt_pad[:, :-1]

                with torch.amp.autocast(device, enabled = use_amp):
                    logits    = model(src, tgt_in, src_pad, tgt_pad_in)
                    val_loss += criterion(
                        logits.reshape(-1, vocab.output_size),
                        tgt_out.reshape(-1),
                    ).item()

        avg_val = val_loss / max(len(val_loader), 1)
        scheduler.step()

        if (device != "cpu"):
            torch.cuda.empty_cache()

        print(f"Epoch {epoch:3d}/{epochs}  "
              f"train={avg_train:.4f}  val={avg_val:.4f}")

        if (avg_val < best_val_loss):
            best_val_loss = avg_val
            torch.save({
                "epoch"     : epoch,
                "model"     : model.state_dict(),
                "optimizer" : optimizer.state_dict(),
                "val_loss"  : best_val_loss,
            }, ckpt_path)
            print(f"  ✓ Checkpoint saved (val={best_val_loss:.4f})")

    print(f"\n[Train] Finished. Best val_loss={best_val_loss:.4f}")

@torch.no_grad()
def greedy_decode(
    model       : DSLTransformer,
    vocab       : Vocabulary,
    type_system : TypeSystem,
    input_text  : str,
    max_output  : int = 256,
    device      : str = "cpu",
    use_type_constraints: bool = True,
) -> str:
    model.eval()

    src_ids = vocab.encode_input(input_text, 2048)
    src     = torch.tensor(src_ids, dtype = torch.long).unsqueeze(0).to(device)
    src_pad = (src == 0)

    memory  = model.encode(src, src_pad)

    # Decoding token by token
    generated = [vocab.BOS]
    program   = ""

    for step in range(max_output - 1):
        tgt = torch.tensor([generated], dtype = torch.long).to(device)
        logits = model.decode(tgt, memory)[:, -1, :]  # [1, V_out]

        if (use_type_constraints):
            mask = type_system.valid_mask(program, vocab).to(device)

            if (mask.any()):
                logits[0][~mask] = float("-inf")

        next_id  = logits.argmax(-1).item()
        next_tok = vocab.output_tokens[next_id]

        if (next_tok == "<EOS>"):
            break

        generated.append(next_id)

        ctx = type_system._parse_context(program)
        add_par = False

        if (ctx["state"] == "expect_arg"):
            expected = ctx.get("expected_type", "Any")

            if (expected != "Callable" and next_tok in vocab.dsl_primitives.keys()):
                add_par = True

        if (next_tok not in ("<PAD>", "<BOS>")):
            program += next_tok

        if (add_par):
            program += "("

    return program

@torch.no_grad()
def beam_search(
    model       : DSLTransformer,
    vocab       : Vocabulary,
    type_system : TypeSystem,
    input_text  : str,
    beam_width  : int  = 5,
    max_output  : int  = 256,
    device      : str  = "cuda",
    use_type_constraints: bool = True,
    diversity_penalty   : float = 0.3,
) -> List[Tuple[float, str]]:
    model.eval()

    src_ids = vocab.encode_input(input_text, 2048)
    src     = torch.tensor(src_ids, dtype = torch.long).unsqueeze(0).to(device)
    src_pad = (src == 0)
    memory  = model.encode(src, src_pad)

    # Beam state: (score, token_ids, text_program)
    beams = [(0.0, [vocab.BOS], "")]

    for step in range(max_output - 1):
        all_candidates = []

        for score, ids, program in beams:
            if (ids[-1] == vocab.EOS):
                all_candidates.append((score, ids, program))
                continue

            tgt    = torch.tensor([ids], dtype = torch.long).to(device)
            logits = model.decode(tgt, memory)[:, -1, :]  # [1, V]

            if (use_type_constraints):
                mask = type_system.valid_mask(program, vocab).to(device)

                if (mask.any()):
                    logits[0][~mask] = float("-inf")

            log_probs = F.log_softmax(logits[0], dim = -1)

            # Top-k tokens
            top_k = min(beam_width * 2, vocab.output_size)
            top_log_probs, top_ids = log_probs.topk(top_k)

            for log_p, tok_id in zip(top_log_probs.tolist(), top_ids.tolist()):
                tok = vocab.output_tokens[tok_id]
                ctx = type_system._parse_context(program)
                add_par = False

                if (ctx["state"] == "expect_arg"):
                    expected = ctx.get("expected_type", "Any")

                    if (expected != "Callable" and tok in vocab.dsl_primitives.keys()):
                        add_par = True

                new_program = program + (tok if tok not in ("<PAD>","<BOS>","<EOS>") else "")
                new_program += "(" if add_par else ""
                new_score   = score + log_p
                new_ids     = ids + [tok_id]
                all_candidates.append((new_score, new_ids, new_program))

        all_candidates.sort(key = lambda x: -x[0])
        selected = []
        seen_prefixes = set()

        for score, ids, program in all_candidates:
            prefix = program[:min(len(program), 15)]

            if (prefix in seen_prefixes):
                score -= diversity_penalty

            seen_prefixes.add(prefix)

            selected.append((score, ids, program))

            if (len(selected) >= beam_width):
                break

        beams = sorted(selected, key = lambda x: -x[0])

        if (all(b[1][-1] == vocab.EOS for b in beams)):
            break

    results = []

    for score, ids, program in beams:
        results.append((score, program))

    return results

def grids_to_input_text(
    pairs: List[Tuple[List[List[int]], List[List[int]]]],
) -> str:
    parts = []

    for inp, out in pairs:
        inp_str = "|".join("".join(str(c) for c in row) for row in inp)
        out_str = "|".join("".join(str(c) for c in row) for row in out)
        parts.append(f"{inp_str},{out_str}")

    return "-".join(parts)

def save_model(
    model   : DSLTransformer,
    vocab   : Vocabulary,
    path    : str = "dsl_transformer.pt",
):
    torch.save(
        {"model_state": model.state_dict(), "d_model": model.d_model},
        path,
    )

    def _make_serializable(obj):
        if (isinstance(obj, dict)):
            return {k: _make_serializable(v) for k, v in obj.items()}
        elif (isinstance(obj, (list, tuple))):
            return [_make_serializable(i) for i in obj]
        elif (isinstance(obj, type)):
            return obj.__name__
        else:
            try:
                s = str(obj)
                json.dumps(s)

                return s
            except Exception:
                return repr(obj)

    meta_path = path + ".json"

    with open(meta_path, "w") as f:
        json.dump({
            "input_vocab" : vocab.input_tokens,
            "output_vocab": vocab.output_tokens,
            "dsl_vars"    : _make_serializable(vocab.dsl_variables),
            "dsl_prims"   : _make_serializable(vocab.dsl_primitives),
            "d_model"     : model.d_model,
            "n_layers"    : len(model.encoder.layers),
        }, f, indent = 2)

    print(f"[Save] Weigths → {path}")
    print(f"[Save] Metadata → {meta_path}")

def load_model(path: str, device: str = "cuda") -> Tuple[DSLTransformer, Vocabulary, TypeSystem]:
    meta_path = path + ".json"

    if (Path(meta_path).exists()):
        with open(meta_path, "r") as f:
            meta = json.load(f)

        ckpt = torch.load(path, map_location = device, weights_only = True)
    else:
        import warnings
        
        warnings.warn(
            f"Old format detected ({path}). Use weights_only=False. "
            "Restart save_model() to migrate to new format.",
            UserWarning, stacklevel = 2,
        )
        ckpt = torch.load(path, map_location = device, weights_only = False)
        meta = {
            "input_vocab" : ckpt["input_vocab"],
            "output_vocab": ckpt["output_vocab"],
            "dsl_vars"    : ckpt["dsl_vars"],
            "dsl_prims"   : ckpt["dsl_prims"],
            "d_model"     : ckpt.get("d_model", 128),
            "n_layers"    : 4,
        }

    vocab = Vocabulary()
    vocab.input_tokens   = meta["input_vocab"]
    vocab.output_tokens  = meta["output_vocab"]
    vocab.input_to_id    = {t: i for i, t in enumerate(vocab.input_tokens)}
    vocab.output_to_id   = {t: i for i, t in enumerate(vocab.output_tokens)}
    vocab.dsl_variables  = meta["dsl_vars"]
    vocab.dsl_primitives = meta["dsl_prims"]
    vocab.PAD = vocab.output_to_id.get("<PAD>", 0)
    vocab.BOS = vocab.output_to_id.get("<BOS>", 1)
    vocab.EOS = vocab.output_to_id.get("<EOS>", 2)

    model = DSLTransformer(
        input_vocab_size  = len(vocab.input_tokens),
        output_vocab_size = len(vocab.output_tokens),
        d_model           = meta.get("d_model", 128),
        n_layers          = meta.get("n_layers", 4),
    )
    model.load_state_dict(ckpt["model_state"])
    model.to(device)

    type_system = TypeSystem(vocab)
    print(f"[Load] Loaded model ← {path}")

    return model, vocab, type_system

def main():
    import argparse

    parser = argparse.ArgumentParser(description = "DSL Transformer for ARC-AGI / Hodel DSL")
    sub    = parser.add_subparsers(dest = "cmd")

    # train
    p_train = sub.add_parser("train")
    p_train.add_argument("--data",       default = "dsl_dataset.json")
    p_train.add_argument("--epochs",     type = int,   default = 50)
    p_train.add_argument("--batch",      type = int,   default = 4,    help = "Batch size (default 8 for 8 GB VRAM)")
    p_train.add_argument("--lr",         type = float, default = 3e-4)
    p_train.add_argument("--d_model",    type = int,   default = 64,   help = "Dim model (128=8GB, 256=16GB)")
    p_train.add_argument("--grad_accum", type = int,   default = 4,    help = "Gradient accumulation (effective batch=batch*grad_accum)")
    p_train.add_argument("--max_input",  type = int,   default = 1024, help = "Length max input in tokens")
    p_train.add_argument("--no_amp",     action = "store_true",        help = "Desactivate mixed precision")
    p_train.add_argument("--max_seq",    type = int,   default = 2048, help = "Filter examples input > N chars")
    p_train.add_argument("--n_layers",   type = int,   default = 2,    help = "Number of layers (4=8GB, 6=16GB)")
    p_train.add_argument("--device",     default = "cuda")
    p_train.add_argument("--ckpt",       default = "dsl_transformer.pt")

    # infer
    p_infer = sub.add_parser("infer")
    p_infer.add_argument("--task", required = True, help = "ARC task")
    p_infer.add_argument("--model", default = "dsl_transformer.pt")
    p_infer.add_argument("--device", default = "cuda")
    p_infer.add_argument("--no_types", action = "store_true")

    # beam
    p_beam = sub.add_parser("beam")
    p_beam.add_argument("--task",   required = True)
    p_beam.add_argument("--model",  default = "dsl_transformer.pt")
    p_beam.add_argument("--k",      type = int, default = 5)
    p_beam.add_argument("--device", default = "cuda")
    p_beam.add_argument("--no_types", action = "store_true")

    # vocab
    sub.add_parser("vocab")

    args = parser.parse_args()

    if (args.cmd == "vocab"):
        vocab = Vocabulary.build()

        print(f"Input tokens ({vocab.input_size})  : {vocab.input_tokens}")
        print(f"Output tokens ({vocab.output_size}) : {vocab.output_tokens[:30]} ...")
        print(f"Variables: {len(vocab.dsl_variables)}")
        print(f"Primitives: {len(vocab.dsl_primitives)}")
    elif (args.cmd == "train"):
        vocab   = Vocabulary.build()
        dataset = DSLDataset(
            args.data, vocab,
            max_input      = getattr(args, 'max_input', 512),
            max_output     = 128,
            max_seq_filter = getattr(args, 'max_seq', 512),
        )
        model   = DSLTransformer(
            input_vocab_size  = vocab.input_size,
            output_vocab_size = vocab.output_size,
            d_model           = args.d_model,
            n_layers          = args.n_layers,
        )
        n_params = sum(p.numel() for p in model.parameters())
        print(f"[Model] {n_params:,} parameters")

        train(model, dataset, vocab,
              epochs = args.epochs, batch_size = args.batch,
              lr = args.lr, device = args.device, ckpt_path = args.ckpt,
              grad_accum = getattr(args, 'grad_accum', 4),
              use_amp = not getattr(args, 'no_amp', False))

        save_model(model, vocab, args.ckpt)
    elif (args.cmd == "infer"):
        with open(f"../ARC-AGI-2/data/training/{args.task}.json") as f:
            data = json.load(f)

        trainData = data["train"]
        input_text = grids_to_input_text([(pair["input"], pair["output"]) for pair in trainData])

        model, vocab, ts = load_model(args.model, args.device)

        program = greedy_decode(
            model, vocab, ts, input_text,
            device = args.device,
            use_type_constraints = not args.no_types,
        )

        print(f"Generated program: {program}")
    elif (args.cmd == "beam"):
        with open(f"../ARC-AGI-2/data/training/{args.task}.json") as f:
            data = json.load(f)

        trainData = data["train"]
        input_text = grids_to_input_text([(pair["input"], pair["output"]) for pair in trainData])

        model, vocab, ts = load_model(args.model, args.device)

        candidates = beam_search(
            model, vocab, ts, input_text,
            beam_width = args.k, device = args.device,
            use_type_constraints = not args.no_types,
        )
        print(f"Top-{args.k} candidates :")

        for i, (score, prog) in enumerate(candidates):
            print(f"  [{i+1}] score={score:.3f}  {prog}")
    else:
        parser.print_help()

if __name__ == "__main__":
    main()
