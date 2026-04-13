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

import sys, json, math, random, hashlib, copy
from pathlib import Path
from typing import List, Tuple, Dict, Optional, Any, Set, Callable
from dataclasses import dataclass, field
import numpy as np
import test_arc

import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.utils.data import Dataset, DataLoader
import torch.optim as optim

@dataclass
class Config:
    # ── paths ─────────────────────────────────────────────────────────────────
    arc_folder   : str = "training"
    dsl_repo_dir   : str = "arc-dsl"           # Hodel's git clone
    memory_path    : str = "arc_memory.json"
    checkpoint_dir : str = "checkpoints"

    # ── grid encoding ─────────────────────────────────────────────────────────
    max_h      : int = 30
    max_w      : int = 30
    num_colors : int = 11      # colours 0-9  +  padding token 10
    max_pairs  : int = 8       # max training pairs kept per task

    # ── DSL tokeniser ─────────────────────────────────────────────────────────
    max_dsl_len : int = 128    # character-level token sequence length

    # ── shared embedding ──────────────────────────────────────────────────────
    embed_dim   : int   = 256
    temperature : float = 0.07

    # ── optimiser ─────────────────────────────────────────────────────────────
    lr              : float = 3e-4
    batch_size      : int   = 32
    epochs_per_iter : int   = 5

    # ── retrieval ─────────────────────────────────────────────────────────────
    top_k : int = 5

    # ── LLM loop (step D) ─────────────────────────────────────────────────────
    llm_max_iters : int = 10

    # ── curriculum ────────────────────────────────────────────────────────────
    curriculum_iters : int = 20

    device : str = "cuda" if torch.cuda.is_available() else "cpu"

CFG    = Config()
DEVICE = torch.device(CFG.device)

class DSLVocab:
    """Character-level vocabulary built from the loaded DSL primitive names."""

    SPECIAL = ["<PAD>", "<BOS>", "<EOS>", "<UNK>"]

    def __init__(self, primitives: list):
        chars: Set[str] = set()
        for name in primitives:
            chars.update(name)
        chars.update("(),_ 0123456789")
        self.token2id: Dict[str, int] = {t: i for i, t in enumerate(self.SPECIAL)}
        for ch in sorted(chars):
            if ch not in self.token2id:
                self.token2id[ch] = len(self.token2id)
        self.id2token = {v: k for k, v in self.token2id.items()}
        self.pad_id = self.token2id["<PAD>"]
        self.bos_id = self.token2id["<BOS>"]
        self.eos_id = self.token2id["<EOS>"]
        self.unk_id = self.token2id["<UNK>"]

    def __len__(self) -> int:
        return len(self.token2id)

    def encode(self, program: str, max_len: int = CFG.max_dsl_len) -> List[int]:
        ids = [self.bos_id]
        for ch in program:
            ids.append(self.token2id.get(ch, self.unk_id))
        ids.append(self.eos_id)
        ids = ids[:max_len]
        ids += [self.pad_id] * (max_len - len(ids))
        return ids

    def decode(self, ids: List[int]) -> str:
        return "".join(
            self.id2token.get(i, "?") for i in ids
            if i not in (self.pad_id, self.bos_id, self.eos_id)
        )

def allPrimitives():
    with open("arc-dsl/dsl.py", "r") as f:
        lines = f.readlines()

    primitives = []

    for line in lines:
        if (line.startswith("def ")):
            primitive = line.split("def ")[1].split("(")[0]
            primitives.append(primitive)

    return sorted(primitives)

VOCAB = DSLVocab(allPrimitives())

Grid = List[List[int]]

def grid_to_tensor(
    grid: Grid,
    h: int = CFG.max_h,
    w: int = CFG.max_w,
) -> torch.Tensor:
    """2-D colour grid → one-hot tensor  [num_colors, h, w].
    Cells outside the grid are filled with colour-10 (PAD token)."""
    arr = np.full((h, w), 10, dtype=np.int64)
    gh = len(grid)
    gw = len(grid[0]) if grid else 0
    arr[:min(gh, h), :min(gw, w)] = (
        np.array(grid, dtype=np.int64)[:min(gh, h), :min(gw, w)]
    )
    t = torch.zeros(CFG.num_colors, h, w)
    t.scatter_(0, torch.from_numpy(arr).unsqueeze(0), 1.0)
    return t                                   # [C, H, W]

def pair_to_tensor(inp: Grid, out: Grid) -> torch.Tensor:
    """Stack input + output one-hots → [2*C, H, W]."""
    return torch.cat([grid_to_tensor(inp), grid_to_tensor(out)], dim=0)

def task_pairs_to_tensor(
    pairs: List[Tuple[Grid, Grid]],
    max_pairs: int = CFG.max_pairs,
) -> torch.Tensor:
    """Stack up to max_pairs grid-pair tensors → [P, 2C, H, W].
    Missing pairs are zero-padded (detected by mask in TaskEncoder)."""
    tensors = [pair_to_tensor(i, o) for i, o in pairs[:max_pairs]]
    while len(tensors) < max_pairs:
        tensors.append(torch.zeros_like(tensors[0]))
    return torch.stack(tensors)                # [P, 2C, H, W]

def grid_hash(grid: Grid) -> str:
    return hashlib.md5(json.dumps(grid, sort_keys=True).encode()).hexdigest()[:10]

def task_complexity(
    pairs: List[Tuple[Grid, Grid]],
    dsl: Optional[str] = None,
) -> float:
    """Heuristic complexity score (lower = simpler):
        • mean grid area across all pairs
        • number of distinct colours
        • DSL nesting depth (optional)
    """
    scores = []
    for inp, out in pairs:
        area = (len(inp) * len(inp[0])) if inp else 1
        colors = len(
            {c for row in inp for c in row} |
            {c for row in out for c in row}
        )
        scores.append(area * 0.01 + colors * 0.5)
    base  = float(np.mean(scores)) if scores else 1.0
    depth = dsl.count("(") if dsl else 0
    return base + depth * 0.3

def dsl_complexity(program: str) -> float:
    """Proxy for DSL tree depth via parenthesis count."""
    return float(program.count("("))

@dataclass
class ARCTask:
    folder     : str
    task_id    : str
    train      : List[Tuple[Grid, Grid]]
    test       : List[Tuple[Grid, Grid]]
    complexity : float = 0.0

def load_arc_tasks(folder: str, taskIds: list = []) -> List[ARCTask]:
    """Load all .json task files from an ARC-AGI-2 data directory.
    Returns tasks sorted by ascending complexity (curriculum order)."""
    tasks: List[ARCTask] = []
    
    if (not taskIds):
        taskIds = [path.stem for path in sorted(Path(f"../ARG-AGI-2/data/{folder}").glob("*.json"))]

    for taskId in taskIds:
        with open(f"{data_dir}/{taskId}.json") as f:
            raw = json.load(f)
        train = [(p["input"], p["output"]) for p in raw.get("train", [])]
        test  = [(p["input"], p["output"]) for p in raw.get("test",  [])]
        tasks.append(ARCTask(
            folder     = folder,
            task_id    = taskId,
            train      = train,
            test       = test,
            complexity = task_complexity(train),
        ))
    tasks.sort(key=lambda t: t.complexity)
    print(f"[Data] Loaded {len(tasks)} ARC tasks (sorted by complexity).")
    return tasks

@dataclass
class MemoryEntry:
    task_id    : str
    program    : str
    pairs      : List[Tuple[Grid, Grid]]   # validated (input, output) pairs
    z_task     : Optional[np.ndarray] = None
    z_dsl      : Optional[np.ndarray] = None
    complexity : float = 0.0

class AbstractionMemory:
    """
    Persistent store of validated (task, DSL-program) pairs.

    Supports:
      • add()      – insert a new MemoryEntry (dedup by task_id+program)
      • retrieve() – top-k cosine-similarity lookup in z_task space
      • _save()/_load() – JSON persistence
    """

    def __init__(self, path: str = CFG.memory_path):
        self.path    = path
        self.entries : List[MemoryEntry] = []
        self._load()

    # ── write ─────────────────────────────────────────────────────────────────

    def add(self, entry: MemoryEntry) -> bool:
        key = (entry.task_id, entry.program)
        if any((e.task_id, e.program) == key for e in self.entries):
            return False
        self.entries.append(entry)
        self._save()
        return True

    # ── read ──────────────────────────────────────────────────────────────────

    def retrieve(
        self,
        z_query: np.ndarray,
        k: int = CFG.top_k,
    ) -> List[MemoryEntry]:
        """Return top-k entries ordered by cosine similarity to z_query."""
        scored = []
        for e in self.entries:
            if e.z_task is not None:
                sim = float(
                    np.dot(z_query, e.z_task) /
                    (np.linalg.norm(z_query) * np.linalg.norm(e.z_task) + 1e-8)
                )
                scored.append((sim, e))
        scored.sort(key=lambda x: -x[0])
        return [e for _, e in scored[:k]]

    def __len__(self) -> int:
        return len(self.entries)

    # ── persistence ───────────────────────────────────────────────────────────

    def _save(self):
        data = [
            {
                "task_id"   : e.task_id,
                "program"   : e.program,
                "complexity": e.complexity,
                "pairs"     : [{"input": i, "output": o} for i, o in e.pairs],
            }
            for e in self.entries
        ]
        with open(self.path, "w") as f:
            json.dump(data, f, indent=2)

    def _load(self):
        if not Path(self.path).exists():
            return
        with open(self.path) as f:
            data = json.load(f)
        for d in data:
            pairs = [(p["input"], p["output"]) for p in d["pairs"]]
            self.entries.append(MemoryEntry(
                task_id    = d["task_id"],
                program    = d["program"],
                pairs      = pairs,
                complexity = d.get("complexity", 0.0),
            ))
        print(f"[Memory] Loaded {len(self.entries)} entries from {self.path}")

class ResBlock(nn.Module):
    """Residual convolutional block with GroupNorm."""

    def __init__(self, c: int, groups: int = 8):
        super().__init__()
        groups = min(groups, c)
        self.net = nn.Sequential(
            nn.Conv2d(c, c, 3, padding=1),
            nn.GroupNorm(groups, c),
            nn.GELU(),
            nn.Conv2d(c, c, 3, padding=1),
            nn.GroupNorm(groups, c),
        )

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        return F.gelu(x + self.net(x))

class PairEncoder(nn.Module):
    """Encode one (input_grid, output_grid) pair → feature vector [pair_dim]."""

    def __init__(
        self,
        in_ch   : int = CFG.num_colors * 2,
        pair_dim: int = 128,
    ):
        super().__init__()
        self.stem = nn.Sequential(
            nn.Conv2d(in_ch, 64,  3, padding=1), nn.GELU(),
            nn.Conv2d(64,   128,  3, padding=1), nn.GELU(),
        )
        self.res  = nn.Sequential(ResBlock(128), ResBlock(128))
        self.pool = nn.AdaptiveAvgPool2d(1)
        self.proj = nn.Linear(128, pair_dim)

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        # x : [B, 2C, H, W]
        h = self.stem(x)
        h = self.res(h)
        h = self.pool(h).flatten(1)   # [B, 128]
        return self.proj(h)           # [B, pair_dim]

class TaskEncoder(nn.Module):
    """
    Step A — Aggregate P pair embeddings → single z_task embedding [D].

    Masked mean-pooling ignores zero-padded pairs.
    """

    def __init__(self, pair_dim: int = 128, embed_dim: int = CFG.embed_dim):
        super().__init__()
        self.pair_enc = PairEncoder(pair_dim=pair_dim)
        self.proj     = nn.Linear(pair_dim, embed_dim)
        self.norm     = nn.LayerNorm(embed_dim)

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        # x : [B, P, 2C, H, W]
        B, P, C, H, W = x.shape
        pairs_flat = x.view(B * P, C, H, W)
        embs = self.pair_enc(pairs_flat).view(B, P, -1)       # [B, P, pair_dim]

        # Mask padding pairs (those that are all zeros)
        mask = (x.view(B, P, -1).abs().sum(-1) > 0).float().unsqueeze(-1)  # [B,P,1]
        embs = (embs * mask).sum(1) / mask.sum(1).clamp(min=1)             # [B, pair_dim]

        return self.norm(self.proj(embs))                                   # [B, embed_dim]

class DSLEncoder(nn.Module):
    """
    Step B — Character-level Transformer: DSL string → z_dsl [D].

    The BOS token at position 0 acts as a CLS token whose final hidden state
    is used as the sequence-level representation.
    """

    def __init__(
        self,
        vocab_size : int = len(VOCAB),
        max_len    : int = CFG.max_dsl_len,
        embed_dim  : int = CFG.embed_dim,
        n_heads    : int = 4,
        n_layers   : int = 3,
        ff_dim     : int = 512,
        dropout    : float = 0.1,
    ):
        super().__init__()
        self.tok_emb = nn.Embedding(vocab_size, embed_dim, padding_idx=VOCAB.pad_id)
        self.pos_emb = nn.Embedding(max_len, embed_dim)
        enc_layer = nn.TransformerEncoderLayer(
            d_model        = embed_dim,
            nhead          = n_heads,
            dim_feedforward= ff_dim,
            dropout        = dropout,
            batch_first    = True,
            norm_first     = True,
        )
        self.transformer = nn.TransformerEncoder(enc_layer, num_layers=n_layers)
        self.norm = nn.LayerNorm(embed_dim)

    def forward(self, ids: torch.Tensor) -> torch.Tensor:
        # ids : [B, L]
        B, L = ids.shape
        pos      = torch.arange(L, device=ids.device).unsqueeze(0)
        pad_mask = (ids == VOCAB.pad_id)                   # [B, L]  True=ignore
        h   = self.tok_emb(ids) + self.pos_emb(pos)        # [B, L, D]
        h   = self.transformer(h, src_key_padding_mask=pad_mask)
        cls = h[:, 0]                                      # CLS = BOS position
        return self.norm(cls)                              # [B, D]

class ContrastiveModel(nn.Module):
    """
    CLIP-style symmetric InfoNCE alignment:

        L = ½ [ CE(z_task · z_dslᵀ / τ) + CE(z_dsl · z_taskᵀ / τ) ]

    τ (temperature) is a learnable scalar.
    """

    def __init__(self, cfg: Config = CFG):
        super().__init__()
        self.task_enc = TaskEncoder(embed_dim=cfg.embed_dim)
        self.dsl_enc  = DSLEncoder(embed_dim=cfg.embed_dim)
        # Learnable log-temperature (initialised from cfg.temperature)
        self.log_temp = nn.Parameter(torch.tensor(math.log(1.0 / cfg.temperature)))

    @property
    def temperature(self) -> torch.Tensor:
        return self.log_temp.exp().clamp(min=1e-4)

    def encode_task(self, x: torch.Tensor) -> torch.Tensor:
        """x : [B, P, 2C, H, W]  →  L2-normalised [B, D]"""
        return F.normalize(self.task_enc(x), dim=-1)

    def encode_dsl(self, ids: torch.Tensor) -> torch.Tensor:
        """ids : [B, L]  →  L2-normalised [B, D]"""
        return F.normalize(self.dsl_enc(ids), dim=-1)

    def forward(
        self,
        task_x  : torch.Tensor,   # [B, P, 2C, H, W]
        dsl_ids : torch.Tensor,   # [B, L]
    ) -> torch.Tensor:
        """Symmetric InfoNCE loss over a batch of aligned (task, DSL) pairs."""
        z_t = self.encode_task(task_x)    # [B, D]
        z_d = self.encode_dsl(dsl_ids)    # [B, D]

        logits_td = z_t @ z_d.T / self.temperature   # [B, B]
        logits_dt = logits_td.T

        labels = torch.arange(len(z_t), device=z_t.device)
        loss = (
            F.cross_entropy(logits_td, labels) +
            F.cross_entropy(logits_dt, labels)
        ) / 2.0
        return loss

class ContrastiveDataset(Dataset):
    """Dataset built from all validated (grid_pairs, DSL_program) entries in memory."""

    def __init__(self, memory: AbstractionMemory):
        self.samples: List[Tuple[torch.Tensor, torch.Tensor]] = []
        for entry in memory.entries:
            grid_t = task_pairs_to_tensor(entry.pairs)
            dsl_t  = torch.tensor(VOCAB.encode(entry.program), dtype=torch.long)
            self.samples.append((grid_t, dsl_t))

    def __len__(self) -> int:
        return len(self.samples)

    def __getitem__(self, idx: int) -> Tuple[torch.Tensor, torch.Tensor]:
        return self.samples[idx]

class RetrievalEngine:
    """
    Step B — For a new task, retrieve the most similar DSL programs from memory.

    Similarity is measured by cosine distance in the shared z_task space.
    """

    def __init__(self, model: ContrastiveModel, memory: AbstractionMemory):
        self.model  = model
        self.memory = memory

    @torch.no_grad()
    def embed_task(self, pairs: List[Tuple[Grid, Grid]]) -> np.ndarray:
        """Encode a list of (input, output) grid pairs → z_task vector."""
        self.model.eval()
        t = task_pairs_to_tensor(pairs).unsqueeze(0).to(DEVICE)   # [1,P,2C,H,W]
        return self.model.encode_task(t)[0].cpu().numpy()          # [D]

    def retrieve(
        self,
        pairs: List[Tuple[Grid, Grid]],
        k: int = CFG.top_k,
    ) -> List[Tuple[float, MemoryEntry]]:
        """Return top-k (similarity, MemoryEntry) pairs."""
        z = self.embed_task(pairs)
        entries = self.memory.retrieve(z, k=k)
        scored  = []
        for e in entries:
            sim = (
                float(np.dot(z, e.z_task) /
                      (np.linalg.norm(z) * np.linalg.norm(e.z_task) + 1e-8))
                if e.z_task is not None else 0.0
            )
            scored.append((sim, e))
        scored.sort(key=lambda x: -x[0])
        return scored

    def update_embeddings(self):
        """Refresh z_task and z_dsl for every entry in memory (call after retraining)."""
        self.model.eval()
        with torch.no_grad():
            for entry in self.memory.entries:
                entry.z_task = self.embed_task(entry.pairs)
                ids = torch.tensor(
                    VOCAB.encode(entry.program), dtype=torch.long
                ).unsqueeze(0).to(DEVICE)
                entry.z_dsl = self.model.encode_dsl(ids)[0].cpu().numpy()

def generate_synthetic_pairs(
    program       : str,
    existing_pairs: List[Tuple[Grid, Grid]],
    n             : int = 4,
) -> List[Tuple[Grid, Grid]]:
    """
    Step E — Enrich training data with synthetic pairs.

    Strategy: apply random colour permutations to existing input grids,
    re-execute the validated DSL program to produce correct outputs.
    """
    synthetic: List[Tuple[Grid, Grid]] = []
    inputs = []
    for _ in range(n):
        base_in, _ = random.choice(existing_pairs)
        colors     = list({c for row in base_in for c in row})
        if len(colors) >= 2:
            perm    = colors[:]
            random.shuffle(perm)
            mapping = {o: p for o, p in zip(colors, perm)}
            new_in  = [[mapping.get(c, c) for c in row] for row in base_in]
        else:
            new_in = [row[:] for row in base_in]
        inputs.append(new_in)

    df, outputs, tracebacks = test_arc.taskResults(program, inputs, "train")
    for inp, out in zip(inputs, outputs):
        if (np.any(np.isnan(out))):
            continue
        synthetic.append((inp, out))

    return synthetic

def _train_one_epoch(
    model    : ContrastiveModel,
    loader   : DataLoader,
    optimizer: optim.Optimizer,
) -> float:
    model.train()
    total = 0.0
    for task_x, dsl_ids in loader:
        task_x  = task_x.to(DEVICE)
        dsl_ids = dsl_ids.to(DEVICE)
        loss = model(task_x, dsl_ids)
        optimizer.zero_grad()
        loss.backward()
        nn.utils.clip_grad_norm_(model.parameters(), 1.0)
        optimizer.step()
        total += loss.item()
    return total / max(len(loader), 1)

def retrain_embeddings(
    model  : ContrastiveModel,
    memory : AbstractionMemory,
    engine : RetrievalEngine,
    cfg    : Config = CFG,
):
    """
    Step F — Retrain both encoders on all validated (grid, DSL) pairs in memory.
    Then refresh the stored embeddings for all entries.
    """
    if len(memory) < 2:
        print("[Train] Need ≥ 2 memory entries for contrastive training — skipping.")
        return

    dataset   = ContrastiveDataset(memory)
    loader    = DataLoader(
        dataset, batch_size=cfg.batch_size, shuffle=True, drop_last=len(dataset) >= 2
    )
    optimizer = optim.AdamW(model.parameters(), lr=cfg.lr, weight_decay=1e-4)
    scheduler = optim.lr_scheduler.CosineAnnealingLR(optimizer, T_max=cfg.epochs_per_iter)

    print(f"[Train] Retraining on {len(dataset)} entries "
          f"for {cfg.epochs_per_iter} epochs …")
    for epoch in range(cfg.epochs_per_iter):
        loss = _train_one_epoch(model, loader, optimizer)
        scheduler.step()
        print(f"  epoch {epoch + 1}/{cfg.epochs_per_iter}  loss={loss:.4f}")

    engine.update_embeddings()
    print("[Train] Embeddings refreshed for all memory entries.")

# ══════════════════════════════════════════════════════════════════════════════
# §15 — SEED MEMORY INITIALISATION  (Step C)
# ══════════════════════════════════════════════════════════════════════════════

# Ordered from trivial (depth 0) to composed (depth 2)
SEED_PROGRAMS: List[Tuple[str, str]] = [
    # task_id              # DSL expression
    ("__seed_identity__",  "I"),
    ("__seed_rot90__",     "rot90(I)"),
    ("__seed_rot180__",    "rot180(I)"),
    ("__seed_rot270__",    "rot270(I)"),
    ("__seed_hmirror__",   "hmirror(I)"),
    ("__seed_vmirror__",   "vmirror(I)"),
    ("__seed_dmirror__",   "dmirror(I)"),
    ("__seed_cmirror__",   "cmirror(I)"),
    # depth-2 compositions
    ("__seed_rot90_hmirror__",   "rot90(hmirror(I))"),
    ("__seed_rot90_vmirror__",   "rot90(vmirror(I))"),
    ("__seed_rot180_hmirror__",  "rot180(hmirror(I))"),
    ("__seed_rot270_vmirror__",  "rot270(vmirror(I))"),
    ("__seed_dmirror_rot90__",   "dmirror(rot90(I))"),
    ("__seed_cmirror_rot180__",  "cmirror(rot180(I))"),
]

def _make_seed_pairs(program: str, n: int = 4, max_size: int = 5) -> List[Tuple[Grid, Grid]]:
    """Generate canonical (input, output) pairs for a known seed program."""
    pairs: List[Tuple[Grid, Grid]] = []
    random.seed(42)
    inputs = []
    for _ in range(n * 3):                   # over-generate, keep valid
        if len(pairs) == n:
            break
        h   = random.randint(2, max_size)
        w   = random.randint(2, max_size)
        inp = [[random.randint(0, 5) for _ in range(w)] for _ in range(h)]
        inputs.append(inp)
            
    df, outputs, tracebacks = test_arc.taskResults(program, inputs, "train")
    
    for inp, out in zip(inputs, outputs):
        if (np.any(np.isnan(out))):
            continue
        pairs.append((inp, out))

    return pairs

def init_seed_memory(memory: AbstractionMemory):
    """
    Step C — Bootstrap the memory with the simplest DSL transforms.

    Only seeds programs that are executable in the currently loaded DSL
    and that are not already present in memory.
    """
    existing = {e.program for e in memory.entries}
    added    = 0
    for task_id, prog in SEED_PROGRAMS:
        if prog in existing:
            continue
        pairs = _make_seed_pairs(prog)
        if not pairs:
            continue
        entry = MemoryEntry(
            task_id    = task_id,
            program    = prog,
            pairs      = pairs,
            complexity = dsl_complexity(prog),
        )
        memory.add(entry)
        added += 1
    print(f"[Seed] Added {added} seed programs to memory "
          f"(total: {len(memory)}).")

@dataclass
class SolveResult:
    task_id : str
    solved  : bool
    program : Optional[str]
    cost    : float

def solve_task(
    task   : ARCTask,
    model  : ContrastiveModel,
    engine : RetrievalEngine,
    memory : AbstractionMemory,
    cfg    : Config = CFG,
) -> SolveResult:
    """
    Per-task resolution loop:

      A. Encode task → z_task
      B. Retrieve top-k similar DSL programs from memory
      D. LLM proposes candidates with progressive cost penalties
         → validate each candidate against all training pairs
      E. On success: augment with synthetic pairs, store in memory
    """
    print(f"\n[Solve] {task.task_id:40s}  "
          f"complexity={task.complexity:.2f}  pairs={len(task.train)}")

    # A — embed task
    z_task    = engine.embed_task(task.train)

    # B — retrieve
    retrieved = engine.retrieve(task.train, k=cfg.top_k)
    print(f"  Retrieved: {[e.program for _, e in retrieved]}")

    dsl, f, t, step, c1, c2, c3, c4, ct = test_arc.processTask(task.folder, task.task_id, initPrograms = [(s, e.program) for s, e in retrieved])

    if (not ct):
        # E — augment pairs
        extra     = generate_synthetic_pairs(dsl, task.train)
        all_pairs = task.train + extra

        # Persist to memory
        entry = MemoryEntry(
            task_id    = task.task_id,
            program    = dsl,
            pairs      = all_pairs,
            z_task     = z_task,
            complexity = task.complexity,
        )
        memory.add(entry)

        return SolveResult(
            task_id = task.task_id,
            solved  = True,
            program = dsl,
            cost    = ct,
        )

    print(f"  ✗ Failed after {cfg.llm_max_iters} iterations.")
    return SolveResult(
        task_id = task.task_id,
        solved  = False,
        program = None,
        cost    = float("inf"),
    )

def run_curriculum(
    tasks  : List[ARCTask],
    model  : ContrastiveModel,
    memory : AbstractionMemory,
    engine : RetrievalEngine,
    cfg    : Config = CFG,
) -> Dict[str, SolveResult]:
    """
    Main curriculum loop — simplest tasks first, iterating to convergence.

    Each iteration:
      1. Attempt every unsolved task (A → D)
      2. Add validated programs + synthetic pairs to memory  (E)
      3. Retrain embeddings on enriched memory              (F)
      4. Repeat with harder tasks                           (G)
    """
    results : Dict[str, SolveResult] = {}
    n_tasks  = len(tasks)

    for curriculum_iter in range(cfg.curriculum_iters):
        unsolved = [t for t in tasks
                    if t.task_id not in results or not results[t.task_id].solved]
        if not unsolved:
            print("\n[Curriculum] ✓ All tasks solved!")
            break

        print(f"\n{'═' * 64}")
        print(f"[Curriculum] Iter {curriculum_iter + 1}/{cfg.curriculum_iters}"
              f"  unsolved={len(unsolved)}/{n_tasks}")

        newly_solved = 0
        for task in unsolved:
            result = solve_task(task, model, engine, memory, cfg)
            results[task.task_id] = result
            if result.solved:
                newly_solved += 1

        print(f"\n[Curriculum] Newly solved this iter: {newly_solved}")

        if newly_solved == 0:
            print("[Curriculum] No progress — stopping early.")
            break

        # F — retrain both encoders on accumulated memory
        retrain_embeddings(model, memory, engine, cfg)

    return results

def save_checkpoint(model: ContrastiveModel, path: str):
    Path(path).parent.mkdir(parents=True, exist_ok=True)
    torch.save(model.state_dict(), path)
    print(f"[Ckpt] Saved → {path}")

def load_checkpoint(model: ContrastiveModel, path: str) -> bool:
    if not Path(path).exists():
        return False
    model.load_state_dict(torch.load(path, map_location=DEVICE))
    print(f"[Ckpt] Loaded ← {path}")
    return True

def evaluate(results: Dict[str, SolveResult]) -> Dict[str, Any]:
    solved   = [r for r in results.values() if r.solved]
    unsolved = [r for r in results.values() if not r.solved]
    metrics  = {
        "total"           : len(results),
        "solved"          : len(solved),
        "unsolved"        : len(unsolved),
        "accuracy"        : len(solved) / max(len(results), 1),
        "mean_cost"       : float(np.mean([r.cost  for r in solved])) if solved else 0.0,
        "solved_programs" : {r.task_id: r.program for r in solved},
    }
    sep = "═" * 64
    print(f"\n{sep}")
    print(f"[Eval] Accuracy  : {metrics['accuracy'] * 100:.1f}%  "
          f"({metrics['solved']}/{metrics['total']})")
    print(f"       Mean cost  : {metrics['mean_cost']:.3f}")
    print(sep)
    return metrics

def main(cfg: Config = CFG) -> Dict[str, Any]:
    random.seed(42)
    np.random.seed(42)
    torch.manual_seed(42)
    if torch.cuda.is_available():
        torch.cuda.manual_seed_all(42)

    print("═" * 64)
    print(" ARC-AGI-2 Latent DSL Solver")
    print(f" device={cfg.device}  embed_dim={cfg.embed_dim}  τ={cfg.temperature}")
    print("═" * 64)

    # ── Contrastive model ─────────────────────────────────────────────────────
    model = ContrastiveModel(cfg).to(DEVICE)
    ckpt  = str(Path(cfg.checkpoint_dir) / "contrastive.pt")
    load_checkpoint(model, ckpt)

    # ── Persistent memory ─────────────────────────────────────────────────────
    memory = AbstractionMemory(cfg.memory_path)

    # ── Step C: seed trivial DSL programs ────────────────────────────────────
    init_seed_memory(memory)

    # ── Retrieval engine ──────────────────────────────────────────────────────
    engine = RetrievalEngine(model, memory)

    # ── Initial embedding pass on seed data ───────────────────────────────────
    retrain_embeddings(model, memory, engine, cfg)
    save_checkpoint(model, ckpt)

    # ── Load ARC tasks ─────────────────────────────────────────────────────────
    tasks = load_arc_tasks(cfg.arc_folder)

    # ── Curriculum loop  (Steps F → G) ────────────────────────────────────────
    results = run_curriculum(tasks, model, memory, engine, cfg)

    # ── Evaluation ────────────────────────────────────────────────────────────
    metrics = evaluate(results)

    # ── Persist artefacts ─────────────────────────────────────────────────────
    save_checkpoint(model, ckpt)

    results_path = "results.json"
    with open(results_path, "w") as f:
        json.dump(
            {
                k: {
                    "solved" : v.solved,
                    "program": v.program,
                    "cost"   : v.cost,
                }
                for k, v in results.items()
            },
            f,
            indent=2,
        )
    print(f"[Main] Results saved to {results_path}")
    return metrics
