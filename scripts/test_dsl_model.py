from aicpppy import Engine
import dsl_model
import dsl_rl
import math
import numpy as np
import pandas as pd
import test_dsl_engine
import test_dsl_rl
import tabulate
import time
import torch
from typing import Dict, Tuple

modelFilename = "dsl_model.pt"
device = "cuda" if torch.cuda.is_available() else "cpu"
dslModel = dsl_model.DSLModel(len(dsl_rl.VOCAB.token2id), d_model = 256, device = device)
model = dslModel.to(device)
checkpoint = torch.load(modelFilename, map_location = device)
model.load_state_dict(checkpoint["model_state"])
gridModel = dsl_model.ARCContextEncoder(d_model = 256)
builder = dsl_model.DSLGraphBuilder(dsl_rl.VOCAB.token2id)
gridModel = dsl_model.ARCContextEncoder(d_model = 256)
astModel = dsl_model.DSLProgramEncoder(
    vocab_size = len(dsl_rl.VOCAB.token2id),
    d_model = 256
)
costModel = dsl_model.CostEncoder(
    input_dim = 5,
    d_model = 256
)
engine = Engine("dsl_dataset")

def processTask(folder: str, task: str, depth: int = 6) -> Tuple[float, float, str]:
    trainPairs, testPairs = test_dsl_rl.load_task(folder, task)

    inputs, outputs, masks = dsl_model.arc_pairs_to_tensors(trainPairs)
    inputs = inputs.to(device)
    outputs = outputs.to(device)
    masks = masks.to(device)

    candidates: list = [("I", pd.DataFrame(engine.dfIdentityVsPairs(trainPairs[0], trainPairs[1]), columns = dsl_model.scoreColumns), pd.DataFrame(engine.dfIdentityVsPairs(testPairs[0], testPairs[1]), columns = dsl_model.scoreColumns))] * dsl_model.M
    candidates = sorted(candidates, key = lambda x: (tuple(-x[1].sum(axis = 0, skipna = False)), len(x[0]), x[0]))
    count: int = 0
    computeGraphs: bool = True

    model.eval()

    while (candidates[-1][1].sum(axis = 0, skipna = False)["Total cost"] and count < 10):
        if (computeGraphs):
            prog_graphs: list  = []
            cost_tensors: list = []

            for program, df in candidates:
                g = dsl_model.build_prog_graph(program, dsl_rl.VOCAB, device)
                prog_graphs.append(g)
                cost_tensors.append(dsl_model.dataframe_to_cost_tensor(df).to(device))

            computeGraphs = False

            with torch.no_grad():
                z_context = model.encode_context(
                    inputs, outputs, masks,
                    prog_graphs, cost_tensors
                )   # [1, D]

        program = [p for s, p in dsl_model.generate_one(
            model, dsl_rl.VOCAB, z_context, engine,
            temperature = 1.0,
            device = device,
            beam_width = 100,
            max_depth = depth - 1
        )]

        if (program):
            try:
                dfTrain = pd.DataFrame(engine.dfConnectionBuilderVsPairs(trainPairs[0], trainPairs[1]), columns = dsl_model.scoreColumns)
                dfTest = pd.DataFrame(engine.dfConnectionBuilderVsPairs(testPairs[0], testPairs[1]), columns = dsl_model.scoreColumns)
                cost = dfTrain["Total cost"].sum(skipna = False)
            except RuntimeError:
                cost = math.inf

        if (not np.isinf(cost).any() and cost < candidates[0][1].sum(axis = 0, skipna = False)["Total cost"]
            and not program in [c[0] for c in candidates]):
            candidates.append((program, dfTrain, dfTest))
            candidates = sorted(candidates, key = lambda x: (tuple(-x[1].sum(axis = 0, skipna = False)), len(x[0]), x[0]))
            count = 0
            computeGraphs = True

        count += 1

    candidate = candidates[-1]

    while (len(candidates) and not candidates[-1][1].sum(axis = 0, skipna = False)["Total cost"]):
        candidate = candidates.pop()

    return candidate[1]["Total cost"].sum(skipna = False), candidate[2]["Total cost"].sum(skipna = False), candidate[0]

def passTask(folder: str, task: str, debug: bool = False, depth: int = 6):
    trainCost, testCost, dsl = processTask(folder, task, depth)

    if (debug):
        print(f"Train cost: {trainCost}, test cost: {testCost}, dsl: {dsl}")

    assert(not (trainCost + testCost))

def test_task67a3c6ac():
    passTask("training", "67a3c6ac", True, 2)

def test_task68b16354():
    passTask("training", "68b16354", True, 2)

def test_task74dd1130():
    passTask("training", "74dd1130", True, 2)

def test_hodel_tasks():
    tasksByStep: dict = test_dsl_engine.hodelTasksByStep()

    with open("../ARC-AGI-2/data/training.txt", "r") as f:
        trainingTasks = f.read().split("\n")

    for k, v in tasksByStep.items():
        if (k == 3):
            break

        t1 = time.time()

        for task in v:
            print("training", task)

            if (not task in trainingTasks):
                print("Skipped")
                continue

            t2 = time.time()
            passTask("training", task, True, k)
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
"""
def test_training_tasks():
    processTasks("training")

def test_evaluation_tasks():
    processTasks("evaluation")
"""