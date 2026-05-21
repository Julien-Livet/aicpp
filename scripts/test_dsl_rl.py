import dsl_rl
import json
from tabulate import tabulate
import time
import test_dsl_engine
from typing import Dict, List, Tuple

device = "cpu"
modelName = "dsl_rl.pt"
n = 10
temp = 0.5
max_depth = 6
model = dsl_rl.load_model(modelName, device)

def load_task(folder: str, task: str) -> Tuple[List, List]:
    with open(f"../ARC-AGI-2/data/{folder}/{task}.json") as f:
        data = json.load(f)

    trainPairs = [(ex["input"], ex["output"]) for ex in data["train"]]
    testPairs = [(ex["input"], ex["output"]) for ex in data["test"]]

    return trainPairs, testPairs

def processTask(folder: str, task: str) -> Tuple[float, float, str]:
    n: int = 10
    temp: float = 0.5
    max_depth: int = 0
    model = dsl_rl.load_model(modelName, device)
    grids, pad_mask, pairs = dsl_rl.load_task(task, "..")
    results: list = []

    for i in range(n):
        generated, log_probs, programs = dsl_rl.sample_with_tree_mask(
            model, dsl_rl.VOCAB, grids, pad_mask,
            temperature = temp, max_depth = max_depth, device = device,
        )
        prog    = programs[0]
        r       = dsl_rl.compute_reward(prog, pairs)
        results.append((r, prog))

    best_r, best_p = max(results, key=lambda x: x[0])

    trainPairs, testPairs = load_task(folder, task)

    def pairCost(pairs: list):
        total_cost = 0.0

        for inp, out in pairs:
            result = dsl_rl.execute_dsl(best_p, inp)
            total_cost += test_dsl_engine.arcHeuristic(result, out)

        return total_cost

    return pairCost(trainPairs), pairCost(testPairs), best_p

def passTask(folder: str, task: str, debug: bool = False):
    trainCost, testCost, dsl = processTask(folder, task)

    if (debug):
        print(f"Train cost: {trainCost}, test cost: {testCost}, DSL: {dsl}")

    assert(not (trainCost + testCost))

def test_hodel_tasks():
    tasksByStep: dict = test_dsl_engine.hodelTasksByStep()

    with open("../ARC-AGI-2/data/training.txt", "r") as f:
        trainingTasks = f.read().split("\n")

    for k, v in tasksByStep.items():
        t1 = time.time()

        for task in v:
            print("training", task)

            if (not task in trainingTasks):
                print("Skipped")
                continue

            t2 = time.time()
            passTask("training", task, True)
            print(f"Duration: {time.time() - t2} s")

        print(f"Duration for {k} step{'s' if k > 1 else ''} of DSL ({len(v)} tasks): {time.time() - t1} s")
        
def processTasks(folder: str) -> Dict[str, Tuple[float, float, str]]:
    with open(f"../ARC-AGI-2/data/{folder}.txt", "r") as f:
        tasks = f.read().split("\n")

    results: dict = {}
    t1 = time.time()

    for task in tasks:
        print(folder, task)
        t2 = time.time()
        results[task] = passTask(folder, task, True)
        print(f"Duration: {time.time() - t2} s")

    print(f"Duration for {folder} ({len(tasks)} tasks): {time.time() - t1} s")

    rows = [
        [task, trainCost, testCost, dsl]
        for task, (trainCost, testCost, dsl) in results.items()
    ]

    md = tabulate(
        rows,
        headers =["Task", "Train cost", "Test cost", "DSL"],
        tablefmt = "pipe"
    )

    with open(f"{folder}_results.md", "w", encoding = "utf-8") as f:
        f.write(md)

    trainSuccess = 0
    testSuccess = 0

    for trainCost, testCost, dsl in results.values():
        if (not trainCost):
            trainSuccess += 1

        if (not testCost):
            testSuccess += 1

    print(f"{folder} train: {trainSuccess}/{len(tasks)} ({trainSuccess/len(tasks)*100:.2f}%)")
    print(f"{folder} test: {testSuccess}/{len(tasks)} ({testSuccess/len(tasks)*100:.2f}%)")

    return results

def test_training_tasks():
    processTasks("training")

def test_evaluation_tasks():
    processTasks("evaluation")
