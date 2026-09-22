from aicpppy import Engine
import argparse
import copy
from dsl_model.dsl_model import DSLModel
import dsl_model.utils as utils
from dsl_model.worker_pool import WorkerPool
from dsl_rl import VOCAB
import os
import torch
from tqdm import tqdm

def parse_args():
    parser = argparse.ArgumentParser(
        description="DSL model training"
    )

    parser.add_argument(
        "--num-workers",
        type=int,
        default=1,
        help="Number of workers used to generate experiments (default: 1)",
    )

    args = parser.parse_args()

    if args.num_workers < 1:
        parser.error("--num-workers doit être >= 1")

    return args

if __name__ == "__main__":
    args = parse_args()
    device = "cuda" if torch.cuda.is_available() else "cpu"
    engine = Engine("dsl_dataset")
    n = engine.count()
    indexes = engine.orderedIndexes()
    dslModel = DSLModel(len(VOCAB.token2id), d_model = 256, device = device)
    model = dslModel.to(device)
    modelFilename: str = "dsl_model.pt"

    if (os.path.exists(modelFilename)):
        checkpoint = torch.load(modelFilename, map_location = device)
        model.load_state_dict(checkpoint["model_state"])

    model.decoder.sync_cached_decoder()

    optimizer = torch.optim.AdamW(model.parameters(), lr = 1e-4)

    model_version: int = 1
    process = tqdm(
        total=len(indexes),
        desc="Programs",
        dynamic_ncols=True,
    )
    actor_model = copy.deepcopy(model).to(device)
    actor_model.requires_grad_(False)
    actor_model.eval()

    utils.sync_actor_model(actor_model, model)

    worker_pool = WorkerPool(
        num_workers=args.num_workers,
        model_version=model_version,
        actor_model=actor_model,
    )

    jobs_started = False
    batch_id = 0
    pending_batches = {}

    while True:
        if (not jobs_started):
            batch_size = min(
                len(indexes),
                len(worker_pool.processes),
            )

            if batch_size == 0:
                break

            batch_id += 1

            jobs = indexes[:batch_size]
            indexes = indexes[batch_size:]

            for worker_id, j in enumerate(jobs):
                worker_pool.submit_job(
                    worker_id,
                    batch_id,
                    j,
                )

            jobs_started = True

        result = worker_pool.collect_one_experience(
            batch_id,
            model_version,
        )

        if result["type"] == "ready":
            process.update(1)

            if indexes:
                next_j = indexes.pop(0)

                batch_id += 1

                worker_pool.submit_job(
                    result["workerId"],
                    batch_id,
                    next_j,
                )

            continue

        worker_id = result["workerId"]

        if result["type"] == "skip":
            process.update(1)

            utils.sync_actor_model(
                actor_model,
                model,
            )

            worker_pool.sync(
                worker_id,
                model_version,
                actor_model,
            )

            if indexes:
                next_j = indexes.pop(0)

                worker_pool.submit_job(
                    worker_id,
                    batch_id,
                    next_j,
                )

            continue

        if result["type"] != "experience":
            raise RuntimeError(
                f"Unexpected result: {result['type']}"
            )

        experience = utils.reconstruct_experience(result)

        utils.learner_step(
            device,
            model,
            optimizer,
            [experience],
            modelFilename
        )

        model_version += 1

        utils.sync_actor_model(
            actor_model,
            model,
        )
    
        worker_pool.sync(
            worker_id,
            model_version,
            actor_model,
        )

        worker_pool.submit_continue(
            worker_id,
            batch_id,
            result["j"],
        )

        process.set_postfix(
            version=model_version,
            workers=len(worker_pool.processes),
        )

    worker_pool.close()
    process.close()
