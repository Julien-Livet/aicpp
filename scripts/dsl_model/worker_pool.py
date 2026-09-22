import multiprocessing as mp
import queue
from . import utils

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

            experience = utils.reconstruct_experience(result)
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
