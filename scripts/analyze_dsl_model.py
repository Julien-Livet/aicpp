"""
Usage :
  python analyze_dsl_model.py --model dsl_model.pt --level program --n 10000 --device cuda
  python analyze_dsl_model.py --model dsl_model.pt --level program --n 10000 --device cuda --method umap
================================================================================
"""

import argparse
import math

import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import numpy as np
import torch
import torch.nn.functional as F

from dsl_model import DSLModel, encode_program_tokens
from dsl_rl import VOCAB

try:
    from sklearn.manifold import TSNE
    HAS_TSNE = True
except ImportError:
    HAS_TSNE = False

try:
    import umap
    HAS_UMAP = True
except ImportError:
    HAS_UMAP = False

def load_trained_model(path: str, device: str = "cpu") -> DSLModel:
    ckpt = torch.load(path, map_location=device)

    model = DSLModel(
        vocab_size=ckpt.get("vocab_size", len(VOCAB.token2id)),
        d_model=ckpt.get("d_model", 256),
        device=device,
    ).to(device)

    model.load_state_dict(ckpt["model_state"])
    model.eval()

    n_params = sum(p.numel() for p in model.parameters())
    print(f"[Model] loaded from {path} — {n_params:,} parameters")
    return model

@torch.no_grad()
def decoder_hidden_states(
    model     : DSLModel,
    tgt       : torch.Tensor,   # [B, L]
    z_context : torch.Tensor,   # [B, D]
) -> torch.Tensor:
    dec = model.decoder
    B, L = tgt.shape

    memory = dec.context_proj(z_context).unsqueeze(1)        # [B, 1, D]
    causal = torch.nn.Transformer.generate_square_subsequent_mask(
        L, device=tgt.device
    )

    x = dec.token_embed(tgt) * math.sqrt(dec.d_model)
    x = dec.pos_enc(x)
    x = dec.decoder(x, memory, tgt_mask=causal)              # [B, L, D]

    return x

@torch.no_grad()
def extract_program_embeddings(model, programs, device="cpu", batch_size=32, max_len=128):
    PAD = VOCAB.token2id.get("<PAD>", 0)

    d_model = model.d_model
    embeddings = []
    for start in range(0, len(programs), batch_size):
        chunk = programs[start:start + batch_size]
        tgt = torch.stack([encode_program_tokens(p, VOCAB, max_len) for p in chunk]).to(device)
        z_ctx = torch.zeros(len(chunk), d_model, device=device)
        h = decoder_hidden_states(model, tgt, z_ctx)          # [B, L, D]

        last_idx = (tgt != PAD).sum(dim=1) - 1                 # [B]
        pooled = h[torch.arange(h.size(0)), last_idx]          # [B, D]
        embeddings.append(pooled.cpu().numpy())
    return np.concatenate(embeddings, axis=0)

@torch.no_grad()
def extract_token_embeddings(model: DSLModel, which: str = "input"):
    if which == "input":
        W = model.decoder.token_embed.weight
    else:
        W = model.decoder.output_proj.weight

    W = W.detach().cpu().numpy()

    special = {"<PAD>", "<BOS>", "<EOS>"}
    keep_ids, names = [], []
    for name, tid in VOCAB.token2id.items():
        if name in special or tid >= W.shape[0]:
            continue
        keep_ids.append(tid)
        names.append(name)

    return W[keep_ids], names

def program_metadata(programs: list[str]) -> dict:
    meta = {"root": [], "depth": [], "label": []}
    for p in programs:
        meta["root"].append(p.split("(")[0] if "(" in p else p)
        meta["depth"].append(p.count("("))
        meta["label"].append(p if len(p) <= 32 else p[:29] + "...")
    return meta

def token_metadata(names: list[str]) -> dict:
    families = {
        "rotation"  : {"rot90", "rot180", "rot270"},
        "mirror"    : {"hmirror", "vmirror", "cmirror", "dmirror"},
        "half"    : {"tophalf", "bottomhalf", "lefthalf", "righthalf"},
        "scale"   : {"upscale", "downscale", "hupscale", "vupscale"},
        "concat"    : {"hconcat", "vconcat", "combine"},
        "color"   : {"replace", "switch", "fill", "paint", "recolor"},
        "reduction" : {"trim", "compress", "crop", "dedupe", "subgrid"},
        "number" : {"ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "TEN"},
    }
    families = dict(zip(names, names))

    meta = {"root": [], "depth": [], "label": []}
    for n in names:
        fam = "constante" if n.isupper() or n == "I" else "autre"
        for f, members in families.items():
            if n in members:
                fam = f
                break
        meta["root"].append(fam)
        meta["depth"].append(0)
        meta["label"].append(n)
    return meta

def assign_colors(groups: list[str]):
    uniq = sorted(set(groups))
    cmap = plt.get_cmap("Spectral", max(len(uniq), 200))
    cmap_dict = {g: cmap(i / max(len(uniq), 1)) for i, g in enumerate(uniq)}
    return [cmap_dict[g] for g in groups], cmap_dict

def reduce_dim(emb: np.ndarray, method: str) -> np.ndarray:
    n = len(emb)
    if method == "tsne":
        if not HAS_TSNE:
            raise ImportError("pip install scikit-learn")
        return TSNE(
            n_components=2, perplexity=min(30, max(5, n - 1)),
            init="pca", random_state=42,
        ).fit_transform(emb)
    if not HAS_UMAP:
        raise ImportError("pip install umap-learn")
    return umap.UMAP(
        n_components=2, n_neighbors=min(15, n - 1),
        min_dist=0.1, metric="cosine", random_state=42,
    ).fit_transform(emb)

def plot(coords, meta, title, save_path, show_labels=True, programs=None):
    colors, cmap_dict = assign_colors(meta["root"])
    sizes = [(d + 1) * 32 for d in meta["depth"]]

    fig, ax = plt.subplots(figsize=(16, 12))
    fig.patch.set_facecolor("#1a1a2e")
    ax.set_facecolor("#16213e")

    sc = ax.scatter(coords[:, 0], coords[:, 1], c=colors, s=sizes,
               edgecolors="#dddddd", linewidths=0.8, alpha=0.88, zorder=3)

    if show_labels and len(coords) <= 140:
        for i, (x, y) in enumerate(coords):
            ax.annotate(meta["label"][i], (x, y), fontsize=6.5,
                        color="white", alpha=0.9, xytext=(4, 4),
                        textcoords="offset points", zorder=5)

    handles = [mpatches.Patch(color=c, label=g) for g, c in cmap_dict.items()]
    ax.legend(handles=handles, title="Group", fontsize=8, title_fontsize=9,
              loc="upper left", framealpha=0.3, facecolor="#0f3460",
              edgecolor="white", labelcolor="white",
              ncol=4 if len(handles) > 12 else 1)

    ax.set_title(title, fontsize=14, color="white", pad=15)
    ax.tick_params(colors="#aaaaaa")
    for s in ax.spines.values():
        s.set_edgecolor("#333355")

    try:
        import mplcursors

        cursor = mplcursors.cursor(sc, hover=mplcursors.HoverMode.Transient)

        @cursor.connect("add")
        def _on_hover(sel):
            i = sel.index
            texte = meta["label"][i]
            if programs is not None:
                texte = programs[i]
            lignes = [
                texte,
                f"group: {meta['root'][i]}",
                f"depth: {meta['depth'][i]}",
                f"x, y : {coords[i, 0]:.2f}, {coords[i, 1]:.2f}",
            ]
            sel.annotation.set_text("\n".join(lignes))
            sel.annotation.set_color("white")
            sel.annotation.set_fontsize(8)
            sel.annotation.get_bbox_patch().set(
                facecolor="#0f3460", edgecolor="#8888aa", alpha=0.95
            )
            sel.annotation.arrow_patch.set(arrowstyle="-", color="#8888aa")
    except ImportError:
        raise ImportError("pip install mplcursors")

    plt.tight_layout()
    plt.savefig(save_path, dpi=150, bbox_inches="tight",
                facecolor=fig.get_facecolor())
    print(f"[Saved] {save_path}")
    plt.show()

def cohesion_report(emb: np.ndarray, groups: list[str]) -> None:
    E = emb / (np.linalg.norm(emb, axis=1, keepdims=True) + 1e-8)
    S = E @ E.T
    g = np.array(groups)

    print("\n--- Family cohesion ---")
    intra_all, inter_all = [], []
    for fam in sorted(set(groups)):
        idx = np.where(g == fam)[0]
        if len(idx) < 2:
            continue
        intra = S[np.ix_(idx, idx)]
        intra = intra[~np.eye(len(idx), dtype=bool)].mean()
        other = np.where(g != fam)[0]
        inter = S[np.ix_(idx, other)].mean() if len(other) else float("nan")
        intra_all.append(intra)
        inter_all.append(inter)
        print(f"  {fam:12s} n={len(idx):3d}  "
              f"sim_intra={intra:+.3f}  sim_inter={inter:+.3f}  "
              f"ecart={intra - inter:+.3f}")

    if intra_all:
        print(f"  {'GLOBAL':12s}          "
              f"sim_intra={np.mean(intra_all):+.3f}  "
              f"sim_inter={np.mean(inter_all):+.3f}  "
              f"gap={np.mean(intra_all) - np.mean(inter_all):+.3f}")

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--model",   default="dsl_model.pt")
    ap.add_argument("--dataset", default="dsl_dataset.txt")
    ap.add_argument("--level",   choices=["program", "token", "output"],
                    default="program")
    ap.add_argument("--method",  choices=["tsne", "umap"], default="tsne")
    ap.add_argument("--n",       type=int, default=100)
    ap.add_argument("--device",  default="cpu")
    ap.add_argument("--save",    default="")
    args = ap.parse_args()

    model = load_trained_model(args.model, args.device)

    if args.level == "program":
        with open(args.dataset) as f:
            programs = [l.strip() for l in f if l.strip()]

            import random

            random.seed(0)
            random.shuffle(programs)

            programs = programs[:args.n]
        print(f"[Dataset] {len(programs)} programs")

        emb = extract_program_embeddings(model, programs, args.device)
        meta = program_metadata(programs)
        title = f"Embeddings decoder (programs) — {args.method.upper()} ({len(programs)})"

    else:
        which = "input" if args.level == "token" else "output"
        emb, names = extract_token_embeddings(model, which)
        meta = token_metadata(names)
        print(f"[Vocab] {len(names)} tokens ({which}_proj)")
        title = f"Embeddings decoder ({which} tokens) — {args.method.upper()} ({len(names)})"

    print(f"[Embeddings] shape = {emb.shape}")
    print(f"[Embeddings] average norm = {np.linalg.norm(emb, axis=1).mean():.3f}")

    cohesion_report(emb, meta["root"])

    coords = reduce_dim(emb, args.method)
    save = args.save or f"embeddings_{args.level}_{args.method}.png"

    if args.level == "program":
        plot(coords, meta, title, save, programs=programs)
    else:
        plot(coords, meta, title, save, programs=names)

if __name__ == "__main__":
    main()

