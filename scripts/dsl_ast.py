import os
import site

site_packages = site.getsitepackages()[0]
nvidia_libs = [
    "nvidia/nvjitlink/lib", "nvidia/cublas/lib", "nvidia/cuda_runtime/lib",
    "nvidia/cudnn/lib", "nvidia/cusolver/lib", "nvidia/cusparse/lib",
    "nvidia/curand/lib", "nvidia/cufft/lib",
]
lib_paths = ":".join(f"{site_packages}/{lib}" for lib in nvidia_libs)
current = os.environ.get("LD_LIBRARY_PATH", "")
os.environ["LD_LIBRARY_PATH"] = f"{lib_paths}:{current}" if current else lib_paths

import ctypes

def _preload_cuda_libs():
    sp = site.getsitepackages()[0]
    libs = [
        'nvidia/cuda_runtime/lib/libcudart.so.12',
        'nvidia/nvjitlink/lib/libnvJitLink.so.12',
        'nvidia/cublas/lib/libcublasLt.so.12',
        'nvidia/cublas/lib/libcublas.so.12',
        'nvidia/cufft/lib/libcufft.so.11',
        'nvidia/curand/lib/libcurand.so.10',
        'nvidia/cusolver/lib/libcusolver.so.11',
        'nvidia/cusparse/lib/libcusparse.so.12',
        'nvidia/cudnn/lib/libcudnn.so.9',
        'nvidia/cudnn/lib/libcudnn_ops.so.9',
        'nvidia/cudnn/lib/libcudnn_cnn.so.9',
        'nvidia/cudnn/lib/libcudnn_adv.so.9',
        'nvidia/cudnn/lib/libcudnn_graph.so.9',
        'nvidia/cudnn/lib/libcudnn_heuristic.so.9',
        'nvidia/cudnn/lib/libcudnn_engines_precompiled.so.9',
        'nvidia/cudnn/lib/libcudnn_engines_runtime_compiled.so.9',
    ]

    for lib in libs:
        path = f'{sp}/{lib}'

        try:
            ctypes.CDLL(path, mode=ctypes.RTLD_GLOBAL)
        except OSError:
            pass

_preload_cuda_libs()

import ast
import json
import math
import multiprocessing as mp
import numpy as np
import os
import pickle
import random
import test_arc
import torch
import torch.nn as nn
from torch.utils.data import DataLoader, Dataset
from tqdm import tqdm
import view_dsl_graph

NUM_COLORS = 10
PAD_GRID = 11  # valeur de padding pour les grilles
DEVICE = 'cuda' if torch.cuda.is_available() else 'cpu'
MAX_GRID = 40

class ASTTokenizer:
    PUNCTUATION = ["(", ")", ","]

    def __init__(self):
        self.vocab   = {"PAD": 0, "ENTER": 1, "EXIT": 2}
        self.reverse = {0: "PAD", 1: "ENTER", 2: "EXIT"}

        for tok in self.PUNCTUATION:
            idx = len(self.vocab)
            self.vocab[tok]   = idx
            self.reverse[idx] = tok

    def _extract_symbols(self, expr: str) -> list[str]:
        tokens = []
        i = 0

        while (i < len(expr)):
            if (expr[i] in self.vocab):
                tokens.append(expr[i])
                i += 1
            elif (expr[i].isalpha() or expr[i] == '_'):
                j = i

                while (j < len(expr) and (expr[j].isalnum() or expr[j] == '_')):
                    j += 1

                tokens.append(expr[i:j])
                i = j
            else:
                tokens.append(expr[i])
                i += 1

        return tokens

    def build(self, expr_list):
        idx = len(self.vocab)

        for expr in expr_list:
            for tok in self._extract_symbols(expr):
                if tok not in self.vocab:
                    self.vocab[tok]   = idx
                    self.reverse[idx] = tok
                    idx += 1

    def _tokenize(self, expr: str) -> list[str]:
        sorted_vocab = sorted(self.vocab.keys(), key = len, reverse = True)
        tokens = []
        i = 0

        while (i < len(expr)):
            matched = False

            for token in sorted_vocab:
                if (expr[i:].startswith(token)):
                    tokens.append(token)
                    i += len(token)
                    matched = True
                    break

            if (not matched):
                tokens.append(expr[i])
                i += 1

        return tokens

    def __call__(self, expr: str) -> list[int]:
        return (
            [self.vocab["ENTER"]]
            + [self.vocab.get(t, 0) for t in self._tokenize(expr)]
            + [self.vocab["EXIT"]]
        )

    def decode(self, ids: list[int]) -> str:
        return "".join(
            self.reverse[i]
            for i in ids
            if i not in (self.vocab["PAD"], self.vocab["ENTER"], self.vocab["EXIT"])
        )

    def save(self, path):
        with open(path, 'w') as f:
            json.dump({"vocab": self.vocab, "reverse": self.reverse}, f)

    @classmethod
    def load(cls, path):
        t = cls()

        with open(path) as f:
            data = json.load(f)

        t.vocab   = data["vocab"]
        t.reverse = {int(k): v for k, v in data["reverse"].items()}

        return t

# ──────────────────────────────────────────────
# Dataset
# ──────────────────────────────────────────────

class ARCDataset(Dataset):
    def __init__(self, data, tokenizer, max_grid = 40, max_len = 256):
        self.data      = data
        self.tokenizer = tokenizer
        self.max_grid  = max_grid
        self.max_len   = max_len

    def __len__(self):
        return len(self.data)

    def encode_grid(self, grid):
        arr = torch.full((self.max_grid, self.max_grid), PAD_GRID, dtype = torch.long)

        for i, row in enumerate(grid):
            if (i >= self.max_grid):
                break

            for j, val in enumerate(row):
                if (j >= self.max_grid):
                    break

                arr[i, j] = int(val)

        return arr.flatten()

    def __getitem__(self, idx):
        pairs, expr = self.data[idx]

        MAX_PAIRS = 4

        # Encode available pairs
        encoded = [
            torch.cat([self.encode_grid(I), self.encode_grid(O)])
            for I, O in pairs[:MAX_PAIRS]
        ]

        # Pad with zeros if less than MAX_PAIRS pairs
        while len(encoded) < MAX_PAIRS:
            encoded.append(torch.zeros(2 * self.max_grid * self.max_grid, dtype=torch.long))

        grids = torch.stack(encoded)  # (MAX_PAIRS, 2*max_grid²) — fixed size

        tokens = self.tokenizer(expr)
        tokens = tokens[:self.max_len]
        tokens += [0] * (self.max_len - len(tokens))

        return grids, torch.tensor(tokens, dtype = torch.long)

# ──────────────────────────────────────────────
# Modèle
# ──────────────────────────────────────────────

class PositionalEncoding(nn.Module):
    def __init__(self, d_model, max_len = 4096, dropout = 0.1):
        super().__init__()
        self.dropout = nn.Dropout(dropout)

        pe  = torch.zeros(max_len, d_model)
        pos = torch.arange(max_len).unsqueeze(1).float()
        div = torch.exp(
            torch.arange(0, d_model, 2).float() * (-math.log(10000.0) / d_model)
        )
        pe[:, 0::2] = torch.sin(pos * div)
        pe[:, 1::2] = torch.cos(pos * div)
        self.register_buffer('pe', pe.unsqueeze(0))

    def forward(self, x):
        return self.dropout(x + self.pe[:, :x.size(1)])

class ARCTransformer(nn.Module):
    def __init__(self, vocab_size, d_model = 256, nhead = 8, num_layers = 4, dropout = 0.1):
        super().__init__()

        # CNN encoder — réduit (40,40) → vecteur fixe bien plus petit
        self.cnn = nn.Sequential(
            nn.Embedding(PAD_GRID + 1, 32),         # (B, 3200, 32)
        )
        # Reshape implicite dans forward : (B, 32, 40, 40)
        self.cnn_conv = nn.Sequential(
            nn.Conv2d(32, 64,  3, padding = 1), nn.ReLU(), nn.MaxPool2d(2),  # 20x20
            nn.Conv2d(64, 128, 3, padding = 1), nn.ReLU(), nn.MaxPool2d(2),  # 10x10
            nn.Conv2d(128, d_model, 3, padding = 1), nn.ReLU(), nn.MaxPool2d(2),  # 5x5
        )
        # Sortie CNN : (B, d_model, 5, 5) → (B, 25, d_model) — 25 tokens au lieu de 3200

        self.grid_pos  = PositionalEncoding(d_model, max_len = 64, dropout = dropout)

        self.encoder   = nn.TransformerEncoder(
            nn.TransformerEncoderLayer(d_model, nhead, batch_first = True,
                                       dim_feedforward = 1024, dropout = dropout),
            num_layers = num_layers
        )

        self.token_emb = nn.Embedding(vocab_size, d_model, padding_idx = 0)
        self.token_pos = PositionalEncoding(d_model, max_len = 512, dropout = dropout)

        self.decoder   = nn.TransformerDecoder(
            nn.TransformerDecoderLayer(d_model, nhead, batch_first = True,
                                       dim_feedforward = 1024, dropout = dropout),
            num_layers = num_layers
        )

        self.fc = nn.Linear(d_model, vocab_size)

    def encode_grids(self, grids):
        """grids : (B, MAX_PAIRS, 2*max_grid²)"""
        B, N, _ = grids.size()

        features = torch.stack([
            self._encode_single(grids[:, i, :]) for i in range(N)
        ], dim = 1)  # (B, N, 50, d_model)

        # Mask padded pairs (all zeroes)
        mask = (grids.sum(dim = -1) != 0).float()  # (B, N)
        mask = mask.unsqueeze(-1).unsqueeze(-1)   # (B, N, 1, 1)

        features = (features * mask).sum(dim = 1) / mask.sum(dim = 1).clamp(min = 1)
        # → (B, 50, d_model)

        return features

    def _encode_single(self, grid):
        """grid : (B, 2 * max_grid²) → memory : (B, 50, d_model)"""
        B        = grid.size(0)
        max_grid = 40

        # Séparer input et output grids
        g_in  = grid[:, :max_grid*max_grid].reshape(B, max_grid, max_grid)
        g_out = grid[:, max_grid*max_grid:].reshape(B, max_grid, max_grid)

        def cnn_encode(g):
            x = self.cnn(g)                        # (B, 40, 40, 32)
            x = x.permute(0, 3, 1, 2)             # (B, 32, 40, 40)
            x = self.cnn_conv(x)                   # (B, d_model, 5, 5)
            x = x.flatten(2).permute(0, 2, 1)     # (B, 25, d_model)
            return x

        feat_in  = cnn_encode(g_in)   # (B, 25, d_model)
        feat_out = cnn_encode(g_out)  # (B, 25, d_model)

        # Concaténer les deux encodages
        return torch.cat([feat_in, feat_out], dim=1)  # (B, 50, d_model)

    def forward(self, grid, tgt):
        # Encoder via CNN — 50 tokens au lieu de 3200
        memory = self.grid_pos(self.encode_grids(grid))
        memory = self.encoder(memory)

        # Decoder (inchangé)
        tgt_len  = tgt.size(1)
        tgt_mask = nn.Transformer.generate_square_subsequent_mask(
            tgt_len, device = tgt.device
        )
        tgt_pad_mask = (tgt == 0)
        tgt_emb  = self.token_pos(self.token_emb(tgt))

        out = self.decoder(
            tgt_emb, memory,
            tgt_mask = tgt_mask,
            tgt_key_padding_mask = tgt_pad_mask,
        )

        return self.fc(out)

# ──────────────────────────────────────────────
# Entraînement
# ──────────────────────────────────────────────

def train(model, dataset, sampler, epochs = 20, batch_size = 32, lr = 1e-4):
    model   = model.to(DEVICE)
    loader  = DataLoader(dataset, batch_size = batch_size,
                         sampler = sampler, pin_memory = (DEVICE == 'cuda'))
    opt     = torch.optim.Adam(model.parameters(), lr = lr)
    scheduler = torch.optim.lr_scheduler.ReduceLROnPlateau(
        opt, patience = 3, factor = 0.5
    )
    loss_fn = nn.CrossEntropyLoss(ignore_index = 0)

    best_loss = float('inf')

    for epoch in range(epochs):
        model.train()
        total_loss = 0.0

        for grids, tokens in tqdm(loader, desc = f"Epoch {epoch+1}/{epochs}"):
            grids   = grids.to(DEVICE)
            tokens = tokens.to(DEVICE)

            inp    = tokens[:, :-1]
            target = tokens[:, 1:]

            logits = model(grids, inp)
            loss   = loss_fn(
                logits.reshape(-1, logits.size(-1)),
                target.reshape(-1)
            )

            opt.zero_grad()
            loss.backward()
            torch.nn.utils.clip_grad_norm_(model.parameters(), 1.0)
            opt.step()

            total_loss += loss.item()

        avg_loss = total_loss / len(loader)
        scheduler.step(avg_loss)
        print(f"Epoch {epoch+1}/{epochs} — loss: {avg_loss:.4f}")

        if (avg_loss < best_loss):
            best_loss = avg_loss
            torch.save(model.state_dict(), "best_model.pt")
            print(f"  → Best model saved (loss: {best_loss:.4f})")

# ──────────────────────────────────────────────
# Inférence
# ──────────────────────────────────────────────

def generate(model, pairs, tokenizer,
             dataset_obj, max_len = 256, beam_size = 1):
    """
    Generate an AST from a paire (input, output).
    beam_size=1 → greedy, beam_size>1 → beam search.
    """
    model.eval()

    grids = torch.stack([
        torch.cat([dataset_obj.encode_grid(I), dataset_obj.encode_grid(O)])
        for I, O in pairs
    ]).unsqueeze(0).to(DEVICE)  # (1, N, 2*max_grid²)

    if (beam_size == 1):
        return _greedy(model, grids, tokenizer, max_len)
    else:
        return _beam_search(model, grids, tokenizer, max_len, beam_size)

def _greedy(model, grids, tokenizer, max_len):
    tokens = [tokenizer.vocab["ENTER"]]

    with torch.no_grad():
        for _ in range(max_len):
            tgt    = torch.tensor(tokens).unsqueeze(0).to(DEVICE)
            logits = model(grids, tgt)

            next_tok = logits[0, -1].argmax().item()
            tokens.append(next_tok)

            if (next_tok == tokenizer.vocab["EXIT"]):
                break

    return [tokenizer.reverse[t] for t in tokens[1:-1]]

def _beam_search(model, grids, tokenizer, max_len, beam_size):
    """Beam search — returns the best AST."""
    enter = tokenizer.vocab["ENTER"]
    exit_ = tokenizer.vocab["EXIT"]

    # (sequence, log_prob)
    beams = [([enter], 0.0)]

    with torch.no_grad():
        for _ in range(max_len):
            candidates = []

            for seq, score in beams:
                if (seq[-1] == exit_):
                    candidates.append((seq, score))
                    continue

                tgt    = torch.tensor(seq).unsqueeze(0).to(DEVICE)
                logits = model(grids, tgt)
                log_probs = torch.log_softmax(logits[0, -1], dim = -1)

                topk = log_probs.topk(beam_size)

                for log_p, tok in zip(topk.values, topk.indices):
                    candidates.append((seq + [tok.item()], score + log_p.item()))

            # Keep best beam_size
            beams = sorted(candidates, key = lambda x: x[1], reverse = True)[:beam_size]

            # Stop if all beams have EXIT
            if (all(s[-1] == exit_ for s, _ in beams)):
                break

    best_seq = beams[0][0]

    return [tokenizer.reverse[t] for t in best_seq[1:-1] if t != exit_]

def to_dot(node):
    lines = ["digraph G {"]

    counter = 0

    def visit(n):
        nonlocal counter
        my_id = counter
        counter += 1

        label = n.op

        if (n.type):
            label += f"\\n{n.type}"

        lines.append(f'{my_id} [label="{label}"];')

        for child in n.args:
            child_id = visit(child)
            lines.append(f"{my_id} -> {child_id};")

        return my_id

    visit(node)
    lines.append("}")

    return "\n".join(lines)

def pretty_tree(node, prefix = "", is_last = True):
    connector = "└── " if is_last else "├── "

    label = node.op

    if (node.type):
        label += f":{node.type}"

    if (node.role):
        label += f" [{node.role}]"

    print(prefix + connector + label)

    new_prefix = prefix + ("    " if is_last else "│   ")

    for i, child in enumerate(node.args):
        pretty_tree(child, new_prefix, i == len(node.args) - 1)

def diff_ast(a, b, serialize_function, path = "root"):
    diffs = []

    if (a is None and b is None):
        return diffs

    if (a is None):
        diffs.append((path, "ADD", serialize_function(b)))
        return diffs

    if (b is None):
        diffs.append((path, "REMOVE", serialize_function(a)))
        return diffs

    if (a.op != b.op):
        diffs.append((path, "CHANGE_OP", a.op, b.op))

    if (a.type != b.type):
        diffs.append((path, "CHANGE_TYPE", a.type, b.type))

    if (a.role != b.role):
        diffs.append((path, "CHANGE_ROLE", a.role, b.role))

    max_len = max(len(a.args), len(b.args))

    for i in range(max_len):
        child_a = a.args[i] if i < len(a.args) else None
        child_b = b.args[i] if i < len(b.args) else None

        diffs.extend(diff_ast(child_a, child_b, serialize_function, f"{path}.{i}"))

    return diffs

def serialize(node):
    if (node is None):
        return "None"

    if (not node.args):
        return node.op

    args_str = ", ".join(serialize(a) for a in node.args)

    return f"{node.op}({args_str})"

def embedded_serialize(node):
    if (node is None):
        return "None"

    args = [serialize(a) for a in node.args]
    args = sorted(args)

    return f"{node.op}({','.join(args)})" if args else node.op

def serialize_pretty(node, indent = 0):
    pad = "  " * indent
    label = f"{node.op}:{node.type}[{node.role}]"

    if (not node.args):
        return pad + label

    s = pad + label + "\n"

    for child in node.args:
        s += serialize_pretty(child, indent + 1) + "\n"

    return s.rstrip()

def format_diff(diffs):
    lines = []

    for d in diffs:
        path, kind, *rest = d

        if (kind == "CHANGE_OP"):
            lines.append(f"{path}: op {rest[0]} → {rest[1]}")
        elif (kind == "CHANGE_TYPE"):
            lines.append(f"{path}: type {rest[0]} → {rest[1]}")
        elif (kind == "CHANGE_ROLE"):
            lines.append(f"{path}: role {rest[0]} → {rest[1]}")
        elif (kind == "ADD"):
            lines.append(f"{path}: + {rest[0]}")
        elif (kind == "REMOVE"):
            lines.append(f"{path}: - {rest[0]}")

    return "\n".join(lines)

def diff_to_json(diffs):
    out = []

    for d in diffs:
        path, kind, *rest = d
        out.append({
            "path": path,
            "type": kind,
            "from": rest[0] if len(rest) > 0 else None,
            "to": rest[1] if len(rest) > 1 else None
        })
    return out

def serialize_json(node):
    if node is None:
        return None

    return {
        "op": node.op,
        "type": node.type,
        "role": node.role,
        "args": [serialize_json(a) for a in node.args]
    }

def hodelTasks():
    with open("arc-dsl/solvers.py", "r") as f:
        lines = f.read().split("\n")

    tasks = []

    for line in lines:
        if (line.startswith("def solve_")):
            task = line.split("def solve_")[1].split("(")[0]
            tasks.append(task)

    return sorted(tasks)

def generate_structured_grid():
    kind = np.random.choice(['stripes', 'blocks', 'pattern', 'gradient', 'sparse'])
    h = np.random.randint(4, 15)
    w = np.random.randint(4, 15)

    if (kind == 'stripes'):
        grid = np.zeros((h, w), dtype = int)

        for i in range(h):
            if (np.random.rand() > 0.5):
                grid[i, :] = np.random.randint(1, NUM_COLORS)
    elif (kind == 'blocks'):
        grid = np.zeros((h, w), dtype = int)

        for _ in range(np.random.randint(2, 6)):
            r1, r2 = sorted(np.random.randint(0, h, 2))
            c1, c2 = sorted(np.random.randint(0, w, 2))
            grid[r1:r2+1, c1:c2+1] = np.random.randint(1, NUM_COLORS)
    elif (kind == 'pattern'):
        base_h = np.random.randint(2, max(3, h // 2))
        base_w = np.random.randint(2, max(3, w // 2))
        base   = np.random.randint(0, NUM_COLORS, (base_h, base_w))
        grid   = np.tile(base, (h // base_h + 1, w // base_w + 1))[:h, :w]
    elif (kind == 'gradient'):
        grid = np.zeros((h, w), dtype = int)

        for i in range(h):
            grid[i, :] = int(i * (NUM_COLORS - 1) / max(h - 1, 1))
    else:  # sparse
        grid = np.zeros((h, w), dtype = int)

        for _ in range(np.random.randint(3, 10)):
            grid[np.random.randint(h), np.random.randint(w)] = np.random.randint(1, NUM_COLORS)

    return grid

def taskData(task: str):
    arc_types_module = test_arc.load_module("arc_types", "arc-dsl/arc_types.py")
    constants_module = test_arc.load_module("constants", "arc-dsl/constants.py")
    dsl_module = test_arc.load_module("dsl", "arc-dsl/dsl.py")
    solvers_module = test_arc.load_module("solvers", "arc-dsl/solvers.py")

    namespace = {}
    namespace.update(vars(arc_types_module))
    namespace.update(vars(constants_module))
    namespace.update(vars(dsl_module))
    namespace.update(vars(solvers_module))

    pairs = []

    for i in range(100):
        arr = generate_structured_grid() #np.random.randint(0, 10, (np.random.randint(3, 20), np.random.randint(3, 20)))
        I = tuple(tuple(int(x) for x in row) for row in arr)
        source = f"I = {I}\n\nO = solve_{task}(I)"

        import signal

        def _timeout_handler(signum, frame):
            raise TimeoutError()

        signal.signal(signal.SIGALRM, _timeout_handler)
        signal.alarm(5)

        try:
            exec(source, namespace)
            O = namespace.get("O")
            signal.alarm(0)

            if (O is None):
                continue

            O = np.reshape(O, (len(O), len(O[0])))

            if (np.max(O) > NUM_COLORS or O.shape[0] > MAX_GRID or O.shape[1] > MAX_GRID):
                continue

            pairs.append((I, O))
        except (AttributeError, IndexError, KeyError, NameError, RecursionError,
                RuntimeError, StopIteration, SyntaxError, TypeError,
                ValueError, ZeroDivisionError) as e:
            pass
        except TimeoutError:
            break

    return (*view_dsl_graph.taskAst(task), pairs)

def hodelDataset():
    tasks = hodelTasks()
    dataset = []

    with mp.Pool(processes = 1+0*mp.cpu_count()) as pool:
        with tqdm(total = len(tasks), desc = "Dataset generation") as pbar:
            for task_results in pool.imap_unordered(taskData, tasks):
                dataset.append(task_results)
                pbar.update(1)
                pbar.set_postfix({"Examples": sum([len(result[-1]) for result in dataset])})

    print(f"Final dataset: {sum([len(result[-1]) for result in dataset])} examples")

    return dataset

def extract_tokens(expr: str) -> set:
    tokens = set()
    
    tree = ast.parse(expr, mode = 'eval')
    
    for node in ast.walk(tree):
        if (isinstance(node, ast.Name)):
            tokens.add(node.id)
        elif (isinstance(node, ast.Call)):
            pass
    
    return tokens

if (__name__ == "__main__"):
    """
    import sys

    e, t, n = view_dsl_graph.taskAst(sys.argv[-1], True)
    print(e)
    pretty_tree(n)
    exit()
    """

    """
    e1, t1, n1 = view_dsl_graph.taskAst("90f3ed37", True)
    e2, t2, n2 = view_dsl_graph.taskAst("8403a5d5", True)

    for fn in [serialize, embedded_serialize, serialize_pretty, serialize_json]:
        diffs = diff_ast(n1, n2, fn)
        print(format_diff(diffs))
        print(diff_to_json(diffs))
    exit()
    """

    datasetFilename = "ast_hodel_dataset.pkl"

    if (os.path.exists(datasetFilename)):
        ast_dataset = pickle.load(open(datasetFilename, "rb"))
    else:
        ast_dataset = hodelDataset()
        pickle.dump(ast_dataset, open(datasetFilename, "wb"))

    MAX_TOKEN_LEN = 350
    N_SETS  = 50   # pair sets by task
    MAX_PAIRS = 8  # pairs by set

    raw_dataset = []

    for expr, tree, node, pairs in ast_dataset:
        if (len(pairs) < 2):
            continue

        for _ in range(N_SETS):
            sampled = random.sample(pairs, min(MAX_PAIRS, len(pairs)))
            raw_dataset.append((sampled, expr.replace(" ", "")))

    print(f"raw_dataset size: {len(raw_dataset)}")

    """
    from collections import Counter
    counts = Counter(expr for pairs, expr in raw_dataset)
    print(f"Tâches uniques : {len(counts)}")
    print(f"Min exemples : {min(counts.values())}")
    print(f"Max exemples : {max(counts.values())}")
    print(f"Moyenne : {sum(counts.values())/len(counts):.1f}")
    """

    """
    simple_transforms = ["vmirror(I)", "hmirror(I)", "dmirror(I)", "cmirror(I)",
                     "rot90(I)", "rot180(I)", "rot270(I)"]
    for t in simple_transforms:
        count = sum(1 for pairs, expr in raw_dataset if expr == t)
        print(f"{t}: {count} exemples")
    """

    tokenizer = None

    if (os.path.exists("tokenizer.json")):
        tokenizer = ASTTokenizer.load("tokenizer.json")
        print(f"Loaded tokenizer with {len(tokenizer.vocab)} tokens")

    # Training
    if (os.path.exists("best_model.pt")):
        model = ARCTransformer(
            vocab_size = len(tokenizer.vocab),
            d_model = 256,
            nhead = 8,
            num_layers = 4
        )

        model.load_state_dict(torch.load("best_model.pt", map_location = DEVICE))
        print("Loaded model from best_model.pt")
    else:
        # Build tokenizer
        if (tokenizer == None):
            tokenizer = ASTTokenizer()
            tokenizer.build([expr for pairs, expr in raw_dataset])
            tokenizer.save("tokenizer.json")
            print(f"Vocabulary: {len(tokenizer.vocab)} tokens")

        # AST statistics
        lengths = [len(tokenizer(expr)) for pairs, expr in raw_dataset]
        print(f"AST — min: {min(lengths)}, max: {max(lengths)}, "
            f"average: {sum(lengths)/len(lengths):.1f}")

        """
        lengths = [len(tokenizer(expr)) for pairs, expr in raw_dataset]
        percentiles = [50, 75, 90, 95, 99]
        for p in percentiles:
            print(f"p{p}: {np.percentile(lengths, p):.0f} tokens")
        """

        raw_dataset = [(pairs, expr) for pairs, expr in raw_dataset
                    if len(tokenizer(expr)) <= MAX_TOKEN_LEN]

        # Dataset and model
        dataset = ARCDataset(raw_dataset, tokenizer, max_grid = MAX_GRID, max_len = MAX_TOKEN_LEN)
        model = ARCTransformer(
            vocab_size = len(tokenizer.vocab),
            d_model = 256,
            nhead = 8,
            num_layers = 4
        )

        n_params = sum(p.numel() for p in model.parameters() if p.requires_grad)
        print(f"Parameters: {n_params:,}")
        print(f"Device: {DEVICE}")

        from collections import Counter

        expr_counts = Counter(expr for pairs, expr in raw_dataset)
        total = len(raw_dataset)

        # Weight inversely proportional to frequency
        weights = torch.tensor([
            total / expr_counts[expr] for pairs, expr in raw_dataset
        ], dtype = torch.float)
        weights = weights / weights.mean() # normalize around 1

        sampler = torch.utils.data.WeightedRandomSampler(weights, num_samples = len(weights), replacement = True)

        train(model, dataset, sampler, epochs = 20, batch_size = 32)

    # Inference
    model = model.to(DEVICE)

    print("vmirror(I) examples in dataset:", sum(1 for pairs, expr in raw_dataset if expr == "vmirror(I)"))

    model.eval()
    loss_fn = nn.CrossEntropyLoss(ignore_index = 0)
    losses = []

    for pairs, expr in raw_dataset:
        if (expr != "vmirror(I)"):
            continue

        grids_tensor, tokens_tensor = ARCDataset([(pairs, expr)], tokenizer,
                                                max_grid = MAX_GRID,
                                                max_len = MAX_TOKEN_LEN)[0]
        grids_tensor  = grids_tensor.unsqueeze(0).to(DEVICE)
        tokens_tensor = tokens_tensor.unsqueeze(0).to(DEVICE)

        with torch.no_grad():
            logits = model(grids_tensor, tokens_tensor[:, :-1])
            loss   = loss_fn(logits.reshape(-1, logits.size(-1)),
                            tokens_tensor[:, 1:].reshape(-1))
            losses.append(loss.item())

    print(f"Loss moyenne sur vmirror(I) : {sum(losses)/len(losses):.4f}")

    for pairs, expr in raw_dataset:
        if (expr == "vmirror(I)"):
            print("Example AST:\n", expr)
            dataset = ARCDataset(raw_dataset, tokenizer, max_grid = MAX_GRID, max_len = MAX_TOKEN_LEN)
            pred = generate(model, pairs, tokenizer, dataset, beam_size = 5)
            print("Predicted AST:", "".join(pred))
            break

    for task in ["67a3c6ac"]:#, "90f3ed37", "8403a5d5"]:
        expr, tree, node = view_dsl_graph.taskAst(task)
        true_ast = expr

        print(f"Task {task}\nExpected AST :\n{true_ast}")

        trainPairs, testPairs = test_arc.trainTestPairs("training", task)

        # Greedy
        pred_greedy = generate(model, trainPairs, tokenizer,
                            ARCDataset([], tokenizer), beam_size = 1)
        print(f"Predicted AST (greedy) : {''.join(pred_greedy)}")

        # Beam search
        pred_beam = generate(model, trainPairs, tokenizer,
                            ARCDataset([], tokenizer), beam_size = 5)
        print(f"Predicted AST (beam=5) : {''.join(pred_beam)}")
