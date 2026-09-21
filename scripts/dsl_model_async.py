from aicpppy import Engine
import argparse
import copy
from dsl_model.dsl_model import DSLModel
from dsl_model.experience import Experience
import dsl_model.utils as utils
from dsl_rl import VOCAB
import multiprocessing as mp
import os
import queue
import torch
from tqdm import tqdm

class WorkerPool:
    def __init__(
        self,
        num_workers,
        model_version,
        actor_model,
    ):
        self.ctx = mp.get_context("spawn")

        self.input_queues = [
            self.ctx.Queue()
            for _ in range(num_workers)
        ]

        self.output_queue = self.ctx.Queue()
        self.pending_results = {}
        self.processes = []

        actor_state = {
            name: tensor.detach().cpu()
            for name, tensor in actor_model.state_dict().items()
        }

        for worker_id in range(num_workers):
            p = self.ctx.Process(
                target=utils.worker_process,
                args=(
                    self.input_queues[worker_id],
                    self.output_queue,
                    worker_id,
                    model_version,
                    actor_state,
                ),
            )

            p.start()
            self.processes.append(p)

    def submit_job(self, worker_id, batch_id, j):
        self.input_queues[worker_id].put(
            (
                "job",
                batch_id,
                j,
            )
        )

    def submit_continue(self, worker_id, batch_id, j):
        self.input_queues[worker_id].put(
            (
                "continue",
                batch_id,
                j,
            )
        )
    
    def _get_output(self):
        return self.output_queue.get()

    def collect_one_experience(self, batch_id, model_version):
        while True:
            if (
                batch_id in self.pending_results
                and len(self.pending_results[batch_id]) > 0
            ):
                result = self.pending_results[batch_id].pop(0)

                if not self.pending_results[batch_id]:
                    del self.pending_results[batch_id]

            else:
                result = self.output_queue.get()

                if result["type"] == "ready":
                    return result

                if result["batch_id"] != batch_id:
                    self.pending_results.setdefault(
                        result["batch_id"],
                        []
                    ).append(result)

                    continue

            assert result["batch_id"] == batch_id

            if result["type"] == "skip":
                assert result["reason"] == "invalid_grid"
                return result

            if result["type"] != "experience":
                raise RuntimeError(
                    f"Unexpected result: {result['type']}"
                )

            return result

    def collect_experiences(
        self,
        batch_id,
        jobs,
        model_version,
    ):
        experiences = []
        processed = 0

        while processed < len(jobs):
            if (
                batch_id in self.pending_results
                and len(self.pending_results[batch_id]) > 0
            ):
                result = self.pending_results[batch_id].pop(0)

                if not self.pending_results[batch_id]:
                    del self.pending_results[batch_id]

            else:
                try:
                    result = self.output_queue.get(timeout=1.0)
                except queue.Empty:
                    dead_workers = [
                        (i, p.pid, p.exitcode)
                        for i, p in enumerate(self.processes)
                        if not p.is_alive()
                    ]

                    if dead_workers:
                        raise RuntimeError(
                            f"Worker mort pendant collect_experiences: "
                            f"{dead_workers}"
                        )

                    continue

                result_batch_id = result["batch_id"]

                if result_batch_id != batch_id:
                    self.pending_results.setdefault(
                        result_batch_id,
                        []
                    ).append(result)

                    continue

            assert result["batch_id"] == batch_id
            assert result["model_version"] == model_version

            if result["type"] == "skip":
                assert result["reason"] == "invalid_grid"

                print(
                    f"SKIPPED j={result['j']} "
                    f"reason={result['reason']}",
                    flush=True,
                )

                processed += 1

                continue

            if result["type"] != "experience":
                raise RuntimeError(
                    f"Unexpected result: {result['type']}"
                )

            assert result["target_program"] is not None

            experience = reconstruct_experience(result)
            experiences.append(experience)

            processed += 1

        assert processed == len(jobs)

        if experiences:
            assert {
                exp.model_version
                for exp in experiences
            } == {model_version}

        return experiences

    def sync(
        self,
        worker_id,
        model_version,
        actor_model,
    ):
        actor_state = {
            name: tensor.detach().cpu()
            for name, tensor in actor_model.state_dict().items()
        }

        self.input_queues[worker_id].put(
            (
                "sync",
                model_version,
                actor_state,
            )
        )

        while True:
            try:
                result = self.output_queue.get(timeout=1.0)
            except queue.Empty:
                dead_workers = [
                    (i, p.pid, p.exitcode)
                    for i, p in enumerate(self.processes)
                    if not p.is_alive()
                ]

                if dead_workers:
                    raise RuntimeError(
                        f"Worker mort pendant sync: {dead_workers}"
                    )

                continue

            if result["type"] in ("experience", "skip"):
                self.pending_results.setdefault(
                    result["batch_id"],
                    []
                ).append(result)
                continue

            if result["type"] == "ready":
                self.pending_results.setdefault(
                    "ready",
                    []
                ).append(result)
                continue

            if result["type"] != "sync_ack":
                raise RuntimeError(
                    f"Résultat inattendu pendant sync : {result['type']}"
                )

            assert result["model_version"] == model_version
            assert result["workerId"] == worker_id

            return

    def close(self):
        for input_queue in self.input_queues:
            input_queue.put(None)

        for input_queue in self.input_queues:
            input_queue.close()
            input_queue.join_thread()

        self.output_queue.close()
        self.output_queue.join_thread()

        for p in self.processes:
            p.join()
            assert p.exitcode == 0

        self.processes = []
    
def reconstruct_experience(result):
    prog_graphs = [
        utils.deserialize_prog_graph(g)
        for g in result["prog_graphs"]
    ]

    cost_tensors = [
        torch.from_numpy(c)
        for c in result["cost_tensors"]
    ]

    return Experience(
        workerId=result["workerId"],
        inputs=torch.from_numpy(result["inputs"]),
        outputs=torch.from_numpy(result["outputs"]),
        masks=torch.from_numpy(result["masks"]),
        prog_graphs=prog_graphs,
        cost_tensors=cost_tensors,
        target_program=result["target_program"],
        subtarget_program=result["subtarget_program"],
        generated_program=result["generated_program"],
        alpha=result["alpha"],
        use_semantic=result["use_semantic"],
        model_version=result["model_version"],
    )

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

        experience = reconstruct_experience(result)

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
