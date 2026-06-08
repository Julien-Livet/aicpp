"""
Usage :
  python analyze_dsl_model.py --n 100 --method tsne
  python analyze_dsl_model.py --n 100 --method umap
  python analyze_dsl_model.py --n 100 --method both
================================================================================
"""

import argparse
import ast
import re
import sys
from pathlib import Path

import matplotlib.pyplot as plt
import matplotlib.cm as cm
import matplotlib.patches as mpatches
import numpy as np
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch_geometric.data import Data

try:
    from sklearn.manifold import TSNE
    HAS_TSNE = True
except ImportError:
    HAS_TSNE = False
    print("[Warning] sklearn not available — t-SNE desactived")

try:
    import umap
    HAS_UMAP = True
except ImportError:
    HAS_UMAP = False
    print("[Warning] umap-learn not available — UMAP desactivated")

def extract_embeddings(
    programs     : list[str],
    prog_encoder,              # DSLProgramEncoder (or None → random embeddings)
    vocab        : dict,       # token2id
    device       : str = "cpu",
) -> np.ndarray:
    embeddings = []

    for prog in programs:
        try:
            graph = build_graph(prog, vocab, device)

            if prog_encoder is not None:
                prog_encoder.eval()
                with torch.no_grad():
                    z = prog_encoder(graph)   # [1, D]
                embeddings.append(z.squeeze(0).cpu().numpy())
            else:
                token_ids = graph.x.cpu().numpy()
                emb = np.mean(
                    np.eye(max(vocab.values()) + 1)[token_ids], axis=0
                )
                embeddings.append(emb)

        except Exception as e:
            print(f"  [Skip] {prog[:40]} — {e}")
            D = 256 if prog_encoder is not None else max(vocab.values()) + 1
            embeddings.append(np.zeros(D))

    return np.array(embeddings)   # [N, D]

def build_graph(program_str: str, vocab: dict, device: str = "cpu") -> Data:
    node_features = []
    edges         = []

    def add_node(token: str) -> int:
        idx = len(node_features)
        node_features.append(vocab.get(token, vocab.get("<PAD>", 0)))
        return idx

    def visit(node, parent_idx=None):
        if isinstance(node, ast.Call):
            name = node.func.id if isinstance(node.func, ast.Name) else str(node.func)
            idx  = add_node(name)
            if parent_idx is not None:
                edges.append([parent_idx, idx])
                edges.append([idx, parent_idx])
            for arg in node.args:
                visit(arg, idx)
            return idx

        elif isinstance(node, ast.Name):
            idx = add_node(node.id)
            if parent_idx is not None:
                edges.append([parent_idx, idx])
                edges.append([idx, parent_idx])
            return idx

        elif isinstance(node, ast.Constant):
            idx = add_node(str(node.value))
            if parent_idx is not None:
                edges.append([parent_idx, idx])
                edges.append([idx, parent_idx])
            return idx

    tree = ast.parse(program_str, mode="eval")
    visit(tree.body)

    x          = torch.tensor(node_features, dtype=torch.long, device=device)
    edge_index = (torch.tensor(edges, dtype=torch.long, device=device).t().contiguous()
                  if edges else torch.empty((2, 0), dtype=torch.long, device=device))

    g       = Data(x=x, edge_index=edge_index)
    g.batch = torch.zeros(x.size(0), dtype=torch.long, device=device)

    return g

def program_metadata(programs: list[str]) -> dict:
    meta = {
        "root"   : [],
        "depth"  : [],
        "uses_I" : [],
        "n_nodes": [],
        "label"  : [],
    }

    for prog in programs:
        root = prog.split("(")[0] if "(" in prog else prog
        meta["root"].append(root)

        depth = prog.count("(")
        meta["depth"].append(depth)

        uses_I = bool(re.search(r'\bI\b', prog))
        meta["uses_I"].append(uses_I)

        tokens = re.findall(r'[a-zA-Z_][a-zA-Z0-9_]*', prog)
        meta["n_nodes"].append(len(tokens))

        label = prog if len(prog) <= 35 else prog[:32] + "..."
        meta["label"].append(label)

    return meta

def assign_colors(roots: list[str]) -> tuple[list, dict]:
    unique_roots = sorted(set(roots))
    n            = len(unique_roots)

    cmap     = plt.cm.get_cmap("tab20", max(n, 20))
    color_map = {r: cmap(i / max(n, 1)) for i, r in enumerate(unique_roots)}
    colors    = [color_map[r] for r in roots]

    return colors, color_map

def reduce_tsne(embeddings: np.ndarray, perplexity: float = 15.0) -> np.ndarray:
    if not HAS_TSNE:
        raise ImportError("sklearn not installed — pip install scikit-learn")
    n          = len(embeddings)
    perplexity = min(perplexity, n - 1)
    reducer    = TSNE(
        n_components=2, perplexity=perplexity,
        n_iter_without_progress=1000, random_state=42, init="pca",
    )
    return reducer.fit_transform(embeddings)

def reduce_umap(embeddings: np.ndarray, n_neighbors: int = 15) -> np.ndarray:
    if not HAS_UMAP:
        raise ImportError("umap-learn not installed — pip install umap-learn")
    n_neighbors = min(n_neighbors, len(embeddings) - 1)
    reducer     = umap.UMAP(
        n_components=2, n_neighbors=n_neighbors,
        min_dist=0.1, random_state=42,
    )
    return reducer.fit_transform(embeddings)

def plot_embeddings(
    coords     : np.ndarray,    # [N, 2]
    programs   : list[str],
    meta       : dict,
    method     : str   = "t-SNE",
    show_labels: bool  = True,
    max_labels : int   = 100,
    save_path  : str   = None,
    interactive: bool  = True,
) -> None:
    N = len(programs)
    colors, color_map = assign_colors(meta["root"])

    sizes      = [(d + 1) * 30 for d in meta["depth"]]
    edgecolors = ["#1f77b4" if u else "#aaaaaa" for u in meta["uses_I"]]

    fig, ax = plt.subplots(figsize=(16, 12))
    fig.patch.set_facecolor("#1a1a2e")
    ax.set_facecolor("#16213e")

    scatter = ax.scatter(
        coords[:, 0], coords[:, 1],
        c          = colors,
        s          = sizes,
        edgecolors = edgecolors,
        linewidths = 1.2,
        alpha      = 0.85,
        zorder     = 3,
    )

    if show_labels and N <= max_labels:
        for i, (x, y) in enumerate(coords):
            ax.annotate(
                meta["label"][i],
                (x, y),
                fontsize   = 6.5,
                color      = "white",
                alpha      = 0.9,
                xytext     = (4, 4),
                textcoords = "offset points",
                zorder     = 5,
            )
    elif N > max_labels:
        print(f"  [Info] {N} programs — masked labels (> {max_labels})")
        print("         Use --n ≤ 100 to see labels.")

    unique_roots = sorted(color_map.keys())
    handles = [
        mpatches.Patch(color=color_map[r], label=r)
        for r in unique_roots
    ]
    ncol = 2 if len(unique_roots) > 12 else 1
    ax.legend(
        handles   = handles,
        title     = "Root primitive",
        title_fontsize = 9,
        fontsize  = 8,
        loc       = "upper left",
        framealpha= 0.3,
        facecolor = "#0f3460",
        edgecolor = "white",
        labelcolor= "white",
        ncol      = ncol,
    )

    for depth, label in [(0, "depth 1"), (2, "depth 3"), (5, "depth 6")]:
        ax.scatter([], [], c="white", alpha=0.6,
                   s=(depth+1)*30, label=label)
    ax.legend(
        *[ax.get_legend_handles_labels()[i][len(unique_roots):]
          for i in range(2)],
        title     = "Depth",
        title_fontsize = 9,
        fontsize  = 8,
        loc       = "upper right",
        framealpha= 0.3,
        facecolor = "#0f3460",
        edgecolor = "white",
        labelcolor= "white",
    )
    ax.add_artist(ax.legend(
        handles   = handles,
        title     = "Root primitive",
        title_fontsize = 9,
        fontsize  = 8,
        loc       = "upper left",
        framealpha= 0.3,
        facecolor = "#0f3460",
        edgecolor = "white",
        labelcolor= "white",
        ncol      = ncol,
    ))

    if interactive:
        try:
            import mplcursors
            cursor = mplcursors.cursor(scatter, hover=True)

            @cursor.connect("add")
            def on_hover(sel):
                i = sel.index
                sel.annotation.set_text(
                    f"Program: {programs[i]}\n"
                    f"Root: {meta['root'][i]}\n"
                    f"Depth: {meta['depth'][i]}\n"
                    f"Nodes: {meta['n_nodes'][i]}"
                )
                sel.annotation.get_bbox_patch().set(
                    facecolor="#0f3460", alpha=0.9
                )
                sel.annotation.set_color("white")

        except ImportError:
            print("  [Info] pip install mplcursors for interactive tooltips")

    ax.set_title(
        f"Embeddings DSL — {method} ({N} programs)",
        fontsize=14, color="white", pad=15
    )
    ax.set_xlabel(f"{method} dimension 1", color="#aaaaaa", fontsize=10)
    ax.set_ylabel(f"{method} dimension 2", color="#aaaaaa", fontsize=10)
    ax.tick_params(colors="#aaaaaa")
    for spine in ax.spines.values():
        spine.set_edgecolor("#333355")

    plt.tight_layout()

    if save_path:
        plt.savefig(save_path, dpi=150, bbox_inches="tight",
                    facecolor=fig.get_facecolor())
        print(f"  [Saved] {save_path}")

    plt.show()


def plot_side_by_side(
    coords_tsne : np.ndarray,
    coords_umap : np.ndarray,
    programs    : list[str],
    meta        : dict,
    save_path   : str = None,
):
    """Display t-SNE and UMAP side by side to compare."""
    N = len(programs)
    colors, color_map = assign_colors(meta["root"])
    sizes      = [(d + 1) * 25 for d in meta["depth"]]
    edgecolors = ["#1f77b4" if u else "#555555" for u in meta["uses_I"]]

    fig, axes = plt.subplots(1, 2, figsize=(22, 10))
    fig.patch.set_facecolor("#1a1a2e")

    for ax, coords, title in zip(
        axes,
        [coords_tsne, coords_umap],
        ["t-SNE", "UMAP"],
    ):
        ax.set_facecolor("#16213e")
        sc = ax.scatter(
            coords[:, 0], coords[:, 1],
            c          = colors,
            s          = sizes,
            edgecolors = edgecolors,
            linewidths = 1.0,
            alpha      = 0.85,
        )
        if N <= 40:
            for i, (x, y) in enumerate(coords):
                ax.annotate(
                    meta["label"][i], (x, y),
                    fontsize=6, color="white", alpha=0.85,
                    xytext=(3, 3), textcoords="offset points",
                )
        ax.set_title(f"{title} ({N} programs)",
                     fontsize=13, color="white", pad=12)
        ax.tick_params(colors="#aaaaaa")
        for spine in ax.spines.values():
            spine.set_edgecolor("#333355")

    unique_roots = sorted(color_map.keys())
    handles      = [mpatches.Patch(color=color_map[r], label=r)
                    for r in unique_roots]
    ncol = 2 if len(unique_roots) > 10 else 1
    fig.legend(
        handles     = handles,
        title       = "Root primitive",
        title_fontsize = 9,
        fontsize    = 8,
        loc         = "lower center",
        ncol        = min(len(unique_roots), 8),
        framealpha  = 0.3,
        facecolor   = "#0f3460",
        edgecolor   = "white",
        labelcolor  = "white",
        bbox_to_anchor=(0.5, -0.02),
    )

    plt.tight_layout(rect=[0, 0.06, 1, 1])

    if save_path:
        plt.savefig(save_path, dpi=150, bbox_inches="tight",
                    facecolor=fig.get_facecolor())
        print(f"  [Saved] {save_path}")

    plt.show()

def main():
    parser = argparse.ArgumentParser(
        description="DSL embedding visualization via t-SNE / UMAP"
    )
    parser.add_argument("--dataset",   default="dsl_dataset.txt",
                        help="Text file with one DSL program per line")
    parser.add_argument("--model",     default="dsl_model.pt",
                        help="Path to dsl_model.pt (optional)")
    parser.add_argument("--n",         type=int, default=100,
                        help="Program number to visualize")
    parser.add_argument("--method",    choices=["tsne","umap","both"],
                        default="tsne")
    parser.add_argument("--labels",    action="store_true",
                        help="Force label display even if N > 50")
    parser.add_argument("--save",      default="",
                        help="Image save path (PNG)")
    parser.add_argument("--device",    default="cpu")
    parser.add_argument("--no_model",  action="store_true",
                        help="Use proxy (average token embeddings) without GNN")
    args = parser.parse_args()

    dataset_path = Path(args.dataset)

    if (not dataset_path.exists()):
        print(f"[Error] File not found: {args.dataset}")
        sys.exit(1)

    with open(dataset_path) as f:
        all_programs = [l.strip() for l in f if l.strip()]
        all_programs = sorted(all_programs, key = lambda x: len(x))

    programs = all_programs[:args.n]
    print(f"[Dataset] {len(programs)} programs loaded (on {len(all_programs)})")

    from dsl_rl import VOCAB
    vocab = VOCAB.token2id
    print(f"[Vocab] {len(vocab)} tokens")

    prog_encoder = None

    if (not args.no_model and args.model):
        model_path = Path(args.model)

        if model_path.exists():
            try:
                import dsl_model
                import dsl_rl
                dslModel = dsl_model.DSLModel(len(dsl_rl.VOCAB.token2id), d_model = 256, device = args.device)
                model = dslModel.to(args.device)
                checkpoint = torch.load(args.model, map_location = args.device)
                model.load_state_dict(checkpoint["model_state"])
                prog_encoder = dslModel.prog_encoder
                prog_encoder.eval()
                print(f"[Model] Encoder GNN loaded from {args.model}")
            except Exception as e:
                print(f"[Warning] Impossible to load model: {e}")
                print("           Use token-embedding proxy")
    elif args.no_model:
        print("[Mode] Proxy token-embedding (without trained GNN)")
    else:
        print("[Mode] Proxy token-embedding (--model not specified)")

    print(f"[Extract] Embedding computation for {len(programs)} programs...")
    embeddings = extract_embeddings(programs, prog_encoder, vocab, args.device)
    print(f"  Shape : {embeddings.shape}")

    meta = program_metadata(programs)
    roots_unique = sorted(set(meta["root"]))
    print(f"  Root primitives: {len(roots_unique)}")
    print(f"  Depth max: {max(meta['depth'])}")

    show_labels = args.labels or len(programs) <= 100
    save_path   = args.save or None

    if args.method == "tsne":
        print("[t-SNE] Reduction in progress...")
        coords = reduce_tsne(embeddings)
        plot_embeddings(coords, programs, meta, method="t-SNE",
                        show_labels=show_labels,
                        save_path=save_path or "embeddings_tsne.png")

    elif args.method == "umap":
        print("[UMAP] Reduction in progress...")
        coords = reduce_umap(embeddings)
        plot_embeddings(coords, programs, meta, method="UMAP",
                        show_labels=show_labels,
                        save_path=save_path or "embeddings_umap.png")

    elif args.method == "both":
        if not HAS_TSNE or not HAS_UMAP:
            print("[Error] 'both' needs sklearn AND umap-learn")
            sys.exit(1)
        print("[t-SNE + UMAP] Reductions in progress...")
        coords_tsne = reduce_tsne(embeddings)
        coords_umap = reduce_umap(embeddings)
        plot_side_by_side(
            coords_tsne, coords_umap, programs, meta,
            save_path=save_path or "embeddings_both.png"
        )

if __name__ == "__main__":
    main()
