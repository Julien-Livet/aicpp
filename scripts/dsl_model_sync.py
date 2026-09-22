from aicpppy import Engine
import argparse
from dsl_model.dsl_model import DSLModel
import dsl_model.utils as utils
from dsl_model.worker_sync import Worker
from dsl_rl import VOCAB
import os
import torch
import torch.nn.functional as F
from tqdm import tqdm

def parse_args():
    parser = argparse.ArgumentParser(
        description="DSL model training"
    )

    parser.add_argument(
        "--num-workers",
        type=int,
        default=25,
        help="Number of workers used to generate experiments (default: 25)",
    )

    args = parser.parse_args()

    if args.num_workers < 1:
        parser.error("--num-workers must be >= 1")

    return args

if __name__ == "__main__":
    args = parse_args()
    device = "cuda" if torch.cuda.is_available() else "cpu"
    engine = Engine("dsl_dataset")
    n = engine.count()
    indexes = engine.orderedIndexes()
    process = tqdm(total = len(indexes), desc = "Programs")
    dslModel = DSLModel(len(VOCAB.token2id), d_model=256, device = device)
    model = dslModel.to(device)
    modelFilename: str = "dsl_model.pt"

    if (os.path.exists(modelFilename)):
        checkpoint = torch.load(modelFilename, map_location=device)
        model.load_state_dict(checkpoint["model_state"])

    optimizer = torch.optim.AdamW(
        model.parameters(),
        lr=1e-4
    )

    workers: list = []

    for _ in range(args.num_workers):
        workers.append(Worker())

    count: int = 0

    while (True):
        worker_L_tokens: list = []
        
        for worker in workers:
            loop: bool = True
            c: bool = False

            while (loop):
                if (worker.process(device, engine, model)):
                    if (worker.j != None):
                        count += 1
                        process.update()

                    if (not len(indexes)):
                        c = True

                    worker.init(engine, device, indexes.pop(0))
                else:
                    loop = False

            if (count == n):
                break

            if (c):
                continue

            model.train()
            optimizer.zero_grad()
            target_ids = utils.encode_program_tokens(worker.costs[0][1], VOCAB).to(device)
            decoder_input = target_ids[:-1]
            decoder_target = target_ids[1:]
            logits = model.decoder(decoder_input.unsqueeze(0), worker.z_context)

            L_tokens = F.cross_entropy(
                logits.reshape(
                    -1,
                    logits.size(-1)
                ),
                decoder_target.reshape(-1)
            )
            
            worker_L_tokens.append((worker, L_tokens))

        if (count == n):
            break

        list_L_total: list = []

        for worker, L_tokens in worker_L_tokens:
            list_L_total.append(worker.update(device, model, L_tokens, modelFilename))
        
        sum(list_L_total).backward()
        optimizer.step()
