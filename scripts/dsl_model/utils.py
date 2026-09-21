from .cached_decoder_layer import CachedDecoderLayer
from .dsl_model import DSLModel
from .dsl_graph_builder import DSLGraphBuilder
from dsl_rl import VOCAB
import os
import torch
import torch.nn as nn
import torch.nn.functional as F
from torch_geometric.data import Data
from typing import List, Tuple

Grid = Tuple[Tuple[int]]
M: int = 50

scoreColumns = ["Total cost", "Grid size cost", "Bounding box cost", "Pixel overlap cost", "Value cost"]

minTemperature: float = 0.1
maxTemperature: float = 5.0
minAlpha: float = 0.1

MAX_ITERATIONS_PER_TARGET: int = 500000
PLATEAU_PATIENCE: int = 50000

def dataframe_to_cost_tensor(df):
    """
    df: pandas.DataFrame

    tensor [1, N_grids, 5]
    """

    values = df[scoreColumns].values

    tensor = torch.tensor(
        values,
        dtype=torch.float32
    )

    tensor = tensor.unsqueeze(0)

    return tensor

def pad_grid(grid, max_h, max_w, pad_value=0):
    padded = [
        list(row) + [pad_value] * (max_w - len(row))
        for row in grid
    ]
    padded += [[pad_value] * max_w for _ in range(max_h - len(grid))]

    mask = [
        [1] * len(row) + [0] * (max_w - len(row))
        for row in grid
    ]
    mask += [[0] * max_w for _ in range(max_h - len(grid))]

    return padded, mask

def arc_pairs_to_tensors(arc_pairs: List[Tuple[Grid, Grid]]):
    """
    arc_pairs: List[(input_grid, output_grid)]

    inputs  -> [1, N, H, W]
    outputs -> [1, N, H, W]
    masks -> [1, N, H, W]
    """
    max_h = 0
    max_w = 0

    for inp, out in arc_pairs:
        max_h = max(
            max_h,
            len(inp),
            len(out)
        )

        max_w = max(max_w,
                    max((len(r) for r in inp), default=0),
                    max((len(r) for r in out), default=0))

    input_tensors = []
    output_tensors = []
    mask_tensors = []

    for inp, out in arc_pairs:
        inp_pad, mask = pad_grid(
            inp,
            max_h,
            max_w
        )

        out_pad, _ = pad_grid(
            out,
            max_h,
            max_w
        )

        input_tensors.append(
            torch.tensor(inp_pad)
        )

        output_tensors.append(
            torch.tensor(out_pad)
        )

        mask_tensors.append(
            torch.tensor(mask)
        )

    inputs = torch.stack(input_tensors)
    outputs = torch.stack(output_tensors)
    masks = torch.stack(mask_tensors)

    # [N,H,W] -> [1,N,H,W]
    inputs = inputs.unsqueeze(0)
    outputs = outputs.unsqueeze(0)
    masks = masks.unsqueeze(0)

    return inputs, outputs, masks

@torch.no_grad()
def generate_one(
    model       : DSLModel,
    vocab,
    z_context   : torch.Tensor,
    engine,
    temperature : float = 1.0,
    max_depth   : int   = 6,
    device      : str   = "cuda",
) -> str:
    model.eval()

    BOS = vocab.token2id.get("<BOS>", 1)
    EOS = vocab.token2id.get("<EOS>", 2)

    ids = [BOS]
    connectionBuilder = engine.connectionBuilder()
    connectionBuilder.reset(max_depth)

    for _ in range(128):
        if (ids[-1] == EOS or connectionBuilder.done()):
            break

        tgt = torch.tensor([ids], dtype=torch.long, device=device)
        logits = model.decoder.decode_step(tgt, z_context)[0]
        logits = logits / max(temperature, 1e-6)

        mask     = torch.zeros(len(vocab.token2id), dtype=torch.bool)
        valid    = connectionBuilder.availableNames()

        for name in valid:
            if (name in vocab.token2id):
                mask[vocab.token2id[name]] = True

        if (not mask.any()):
            eos_id = vocab.token2id.get("<EOS>", 2)
            mask[eos_id] = True

        mask = mask.to(device)

        if (mask.any()):
            logits = logits.masked_fill(~mask, float("-inf"))

        probs  = F.softmax(logits, dim=-1)
        tok_id = torch.multinomial(probs, 1).item()
        tok    = vocab.id2token.get(tok_id, "<PAD>")

        if (tok in ("<PAD>", "<BOS>")):
            break

        if (tok == "<EOS>" or connectionBuilder.done()):
            break

        if (connectionBuilder.applyName(tok)):
            ids.append(tok_id)
        else:
            break

    if (not connectionBuilder.valid()):
        return None

    return connectionBuilder.program()

@torch.no_grad()
def generate_one_cached(
    model       : DSLModel,
    vocab,
    z_context   : torch.Tensor,
    engine,
    temperature : float = 1.0,
    max_depth   : int   = 6,
    device      : str   = "cuda",
) -> str:
    model.eval()

    BOS = vocab.token2id.get("<BOS>", 1)
    EOS = vocab.token2id.get("<EOS>", 2)

    ids = [BOS]

    connectionBuilder = engine.connectionBuilder()
    connectionBuilder.reset(max_depth)

    # Cache du décodeur
    cache = None

    # Premier token = BOS
    token = torch.tensor(
        [[BOS]],
        dtype=torch.long,
        device=device,
    )

    z_context = z_context.to(device)
    memory = model.decoder.context_proj(z_context).unsqueeze(1)

    for _ in range(128):

        if ids[-1] == EOS or connectionBuilder.done():
            break

        # -----------------------------------------------------
        # Décodage avec KV cache
        # -----------------------------------------------------

        logits, cache = model.decoder.decode_step_cached(
            token,
            memory,
            cache,
        )

        logits = logits[0]
        logits = logits / max(temperature, 1e-6)

        # -----------------------------------------------------
        # Masque des tokens autorisés
        # -----------------------------------------------------

        mask = torch.zeros(
            len(vocab.token2id),
            dtype=torch.bool,
            device=device,
        )

        valid = connectionBuilder.availableNames()

        for name in valid:
            if name in vocab.token2id:
                mask[vocab.token2id[name]] = True

        if not mask.any():
            mask[EOS] = True

        logits = logits.masked_fill(
            ~mask,
            float("-inf"),
        )

        # -----------------------------------------------------
        # Sampling
        # -----------------------------------------------------

        probs = F.softmax(logits, dim=-1)

        tok_id = torch.multinomial(
            probs,
            1,
        ).item()

        tok = vocab.id2token.get(
            tok_id,
            "<PAD>",
        )

        # -----------------------------------------------------
        # Gestion token
        # -----------------------------------------------------

        if tok in ("<PAD>", "<BOS>"):
            break

        if tok == "<EOS>" or connectionBuilder.done():
            break

        if connectionBuilder.applyName(tok):
            ids.append(tok_id)

            # Le prochain appel ne reçoit QUE le nouveau token
            token = torch.tensor(
                [[tok_id]],
                dtype=torch.long,
                device=device,
            )
        else:
            break

    if not connectionBuilder.valid():
        return None

    return connectionBuilder.program()

def build_prog_graph(
    program: str,
    vocab,
    device: str = "cpu"
) -> Data:
    builder = DSLGraphBuilder(
        vocab.token2id
    )

    try:
        graph = builder.build(program)

        return graph.to(device)
    except Exception:
        x = torch.tensor(
            [vocab.token2id.get("I", 0)],
            dtype=torch.long,
            device=device
        )

        edge_index = torch.empty(
            (2, 0),
            dtype=torch.long,
            device=device
        )

        return Data(
            x=x,
            edge_index=edge_index
        )

def encode_program_tokens(program: str, vocab, max_len: int = 128) -> torch.Tensor:
    ids     = [vocab.token2id.get("<BOS>", 1)]
    known   = sorted(
        [t for t in vocab.token2id if t not in ("<PAD>","<BOS>","<EOS>")],
        key=len, reverse=True
    )
    i = 0

    while (i < len(program)):
        for tok in known:
            if (program[i:i+len(tok)] == tok):
                ids.append(vocab.token2id[tok])
                i += len(tok)
                break
        else:
            i += 1

    ids.append(vocab.token2id.get("<EOS>", 2))
    ids = ids[:max_len]
    ids += [vocab.token2id.get("<PAD>", 0)] * (max_len - len(ids))

    return torch.tensor(ids, dtype=torch.long)

def programDepth(program: str):
    count = 0
    n = 0

    for c in program:
        if (c == "("):
            n += 1
        elif (c == ")"):
            n -= 1

        count = max(count, n)

    return count

def addOutput(filename: str, line: str):
    with open(filename, "a") as f:
        f.write(line + "\n")

def build_cached_decoder_from_model(model):
    old_decoder = model.decoder

    layers = nn.ModuleList([
        CachedDecoderLayer(
            d_model=old_decoder.d_model,
            n_heads=old_decoder.decoder.layers[0].self_attn.num_heads,
            ff_dim=old_decoder.decoder.layers[0].linear1.out_features,
            dropout=0.0,
        )
        for _ in old_decoder.decoder.layers
    ])

    norm = nn.LayerNorm(
        old_decoder.d_model
    )

    for old_layer, new_layer in zip(
        old_decoder.decoder.layers,
        layers,
    ):
        new_layer.load_from_transformer_layer(
            old_layer
        )

    norm.load_state_dict(
        old_decoder.decoder.norm.state_dict()
    )

    device = next(model.parameters()).device
    layers = layers.to(device)
    norm = norm.to(device)

    return layers, norm

def learner_step(device, model, optimizer, experiences, modelFilename: str):
    versions = {
        exp.model_version
        for exp in experiences
    }

    assert len(versions) == 1

    optimizer.zero_grad()

    losses: list = []

    for exp in experiences:
        # ---------------------------------------
        # Recompute context with learner
        # ---------------------------------------

        inputs = exp.inputs.to(device)
        outputs = exp.outputs.to(device)
        masks = exp.masks.to(device)

        prog_graphs = [
            g.to(device)
            for g in exp.prog_graphs
        ]

        cost_tensors = [
            c.to(device)
            for c in exp.cost_tensors
        ]

        z_context = model.encode_context(
            inputs,
            outputs,
            masks,
            prog_graphs,
            cost_tensors
        )

        # ---------------------------------------
        # Subtarget loss
        # ---------------------------------------

        target_ids = encode_program_tokens(
            exp.subtarget_program,
            VOCAB
        ).to(device)

        decoder_input = target_ids[:-1]
        decoder_target = target_ids[1:]

        logits = model.decoder(
            decoder_input.unsqueeze(0),
            z_context
        )

        L_tokens = F.cross_entropy(
            logits.reshape(-1, logits.size(-1)),
            decoder_target.reshape(-1)
        )

        # ---------------------------------------
        # Semantic loss
        # ---------------------------------------

        if exp.use_semantic:
            if exp.generated_program is None:
                continue

            gen_ids = encode_program_tokens(
                exp.generated_program,
                VOCAB
            ).to(device)

            gen_input = gen_ids[:-1]
            gen_target = gen_ids[1:]

            logits_self = model.decoder(
                gen_input.unsqueeze(0),
                z_context
            )

            L_semantic = F.cross_entropy(
                logits_self.reshape(-1, logits_self.size(-1)),
                gen_target.reshape(-1)
            )
        else:
            L_semantic = L_tokens

        # ---------------------------------------
        # Total
        # ---------------------------------------

        L_total = (
            exp.alpha * L_tokens
            + (1.0 - exp.alpha) * L_semantic
        )

        losses.append(L_total)
    
    if not losses:
        return

    sum(losses).backward()

    optimizer.step()

    model.decoder.sync_cached_decoder()

    torch.save({
        "model_state": model.state_dict(),
        "d_model"    : model.decoder.d_model,
        "vocab_size" : model.decoder.vocab_size,
    }, modelFilename.replace(".pt", ".tmp"))

    os.remove(modelFilename)
    os.rename(modelFilename.replace(".pt", ".tmp"), modelFilename)

def sync_actor_model(actor_model, learner_model):
    actor_model.load_state_dict(learner_model.state_dict())
    actor_model.eval()

    for p in actor_model.parameters():
        assert p.grad is None

    for actor_param, learner_param in zip(
        actor_model.parameters(),
        learner_model.parameters(),
    ):
        assert torch.equal(
            actor_param,
            learner_param
        )

def serialize_prog_graph(g):
    return {
        "x": g.x.cpu().numpy(),
        "edge_index": g.edge_index.cpu().numpy(),
    }

def deserialize_prog_graph(g):
    return Data(
        x=torch.from_numpy(g["x"]),
        edge_index=torch.from_numpy(g["edge_index"]),
    )

def worker_process(input_queue, output_queue, worker_id, model_version, actor_state):
    #import faulthandler
    #faulthandler.enable()

    from aicpppy import Engine
    from .worker_async import Worker

    # Un seul Engine pour toute la durée du processus
    engine = Engine("dsl_dataset")
    torch.set_num_threads(1)
    torch.set_num_interop_threads(1)
    # Un seul Worker réutilisé
    worker = Worker(engine)
    active_j = None

    # Un seul actor_model réutilisé
    actor_model = DSLModel(
        len(VOCAB.token2id),
        d_model=256,
        device="cuda",
    ).to("cuda")
    torch.set_flush_denormal(True)
    actor_model.load_state_dict(actor_state)

    actor_model.requires_grad_(False)
    actor_model.eval()

    actor_model.decoder.sync_cached_decoder()

    current_model_version = model_version

    while True:
        message = input_queue.get()

        # Sentinel d'arrêt
        if message is None:
            break

        message_type = message[0]

        # --------------------------------------------------
        # Synchronisation de l'actor
        # --------------------------------------------------
        if message_type == "sync":
            _, current_model_version, new_actor_state = message

            actor_model.load_state_dict(new_actor_state)

            actor_model.requires_grad_(False)
            actor_model.eval()

            actor_model.decoder.sync_cached_decoder()

            output_queue.put({
                "type": "sync_ack",
                "workerId": worker_id,
                "model_version": current_model_version,
            })

            continue

        if message_type == "continue":
            _, batch_id, j = message

            if active_j != j:
                raise RuntimeError(
                    f"CONTINUE incohérent: active_j={active_j}, j={j}"
                )

            result = worker.process(
                actor_model,
                "cuda",
            )

            if (not result):
                active_j = None

                output_queue.put({
                    "type": "ready",
                    "workerId": worker_id,
                    "model_version": current_model_version,
                })

                continue

            output_queue.put({
                "type": "experience",
                "batch_id": batch_id,
                "workerId": worker_id,
                "model_version": current_model_version,
                "j": j,
                "inputs": worker.inputs.cpu().numpy(),
                "outputs": worker.outputs.cpu().numpy(),
                "masks": worker.masks.cpu().numpy(),
                "prog_graphs": [
                    serialize_prog_graph(g)
                    for g in worker.prog_graphs
                ],
                "cost_tensors": [
                    c.cpu().numpy()
                    for c in worker.cost_tensors
                ],
                "target_program": worker.targetProgram,
                "subtarget_program": worker.subtargetProgram,
                "generated_program": worker.program,
                "alpha": worker.alpha,
                "use_semantic": worker.use_semantic,
            })

            continue

        # --------------------------------------------------
        # Job
        # --------------------------------------------------
        if message_type == "job":
            _, batch_id, j = message

            if active_j is None:
                active_j = j
                
                if (not worker.init("cuda", j)):
                    active_j = None

                    output_queue.put({
                        "type": "skip",
                        "batch_id": batch_id,
                        "workerId": worker_id,
                        "model_version": current_model_version,
                        "j": j,
                        "reason": "invalid_init",
                    })

                    continue
            else:
                raise RuntimeError(
                    f"JOB reçu alors que le worker est occupé: "
                    f"active_j={active_j}, nouveau j={j}"
                )

            if (
                worker.inputs.min() < 0
                or worker.inputs.max() >= 10
                or worker.outputs.min() < 0
                or worker.outputs.max() >= 10
            ):
                active_j = None

                output_queue.put({
                    "type": "skip",
                    "batch_id": batch_id,
                    "workerId": worker_id,
                    "model_version": current_model_version,
                    "j": j,
                    "reason": "invalid_grid",
                })

                continue

            result = worker.process(
                actor_model,
                "cuda",
            )

            if (not result):
                active_j = None

                output_queue.put({
                    "type": "ready",
                    "workerId": worker_id,
                    "model_version": current_model_version,
                })

                continue

            output_queue.put({
                "type": "experience",
                "batch_id": batch_id,
                "workerId": worker_id,
                "model_version": current_model_version,
                "j": j,
                "inputs": worker.inputs.cpu().numpy(),
                "outputs": worker.outputs.cpu().numpy(),
                "masks": worker.masks.cpu().numpy(),
                "prog_graphs": [
                    serialize_prog_graph(g)
                    for g in worker.prog_graphs
                ],
                "cost_tensors": [
                    c.cpu().numpy()
                    for c in worker.cost_tensors
                ],
                "target_program": worker.targetProgram,
                "subtarget_program": worker.subtargetProgram,
                "generated_program": worker.program,
                "alpha": worker.alpha,
                "use_semantic": worker.use_semantic,
            })

            continue

        raise RuntimeError(
            f"Message inconnu reçu par worker {worker_id}: "
            f"{message_type}"
        )
