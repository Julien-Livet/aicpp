from aicpppy import Engine
import datetime
import dsl_model
import dsl_rl
import json
import math
import numpy as np
import os
import pandas as pd
import tabulate
import time
import torch
from typing import Dict, Tuple

modelFilename = "dsl_model.pt"
device = "cuda" if torch.cuda.is_available() else "cpu"

MAX_COUNT = 500

def processTask(engine, model, id_, data, depth: int = 6, debug: bool = True):
    testPairs: list = [(ex["input"], ex["output"]) for ex in data["test"]]
    trainPairs: list = [(ex["input"], ex["output"]) for ex in data["train"]]

    inputsTrain: list = []
    outputsTrain: list = []

    for i, o in trainPairs:
        inputsTrain.append(i)
        outputsTrain.append(o)

    inputsTest: list = []
    outputsTest: list = []

    for i, o in testPairs:
        inputsTest.append(i)
        outputsTest.append(o)

    inputs, outputs, masks = dsl_model.arc_pairs_to_tensors(trainPairs)
    inputs = inputs.to(device)
    outputs = outputs.to(device)
    masks = masks.to(device)

    candidates: list = [("I",
                         pd.DataFrame(engine.dfIdentityVsPairs(inputsTrain, outputsTrain), columns = dsl_model.scoreColumns),
                         pd.DataFrame(engine.dfIdentityVsPairs(inputsTest, outputsTest), columns = dsl_model.scoreColumns))] * dsl_model.M
    candidates = sorted(candidates, key = lambda x: (tuple(-x[1].sum(axis = 0, skipna = False)), len(x[0]), x[0]))
    count: int = 0
    computeGraphs: bool = True

    model.eval()

    while (candidates[-1][1].sum(axis = 0, skipna = False)["Total cost"] and count < MAX_COUNT):
        if (computeGraphs):
            prog_graphs: list  = []
            cost_tensors: list = []

            for program, df, _ in candidates:
                g = dsl_model.build_prog_graph(program, dsl_rl.VOCAB, device)
                prog_graphs.append(g)
                cost_tensors.append(dsl_model.dataframe_to_cost_tensor(df).to(device))

            computeGraphs = False

            with torch.no_grad():
                z_context = model.encode_context(
                    inputs, outputs, masks,
                    prog_graphs, cost_tensors
                )   # [1, D]

        program = dsl_model.generate_one(
            model, dsl_rl.VOCAB, z_context, engine,
            temperature = 5.0,
            device = device,
            max_depth = depth
        )

        if (program):
            try:
                dfTrain = pd.DataFrame(engine.dfConnectionBuilderVsPairs(inputsTrain, outputsTrain), columns = dsl_model.scoreColumns)
                dfTest = pd.DataFrame(engine.dfConnectionBuilderVsPairs(inputsTest, outputsTest), columns = dsl_model.scoreColumns)
                cost = dfTrain["Total cost"].sum(skipna = False)
            except RuntimeError:
                cost = math.inf
        else:
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

    if (debug):
        trainCost = candidate[1].sum(axis = 0, skipna = False)["Total cost"]
        testCost = candidate[2].sum(axis = 0, skipna = False)["Total cost"]
        print(f'{datetime.datetime.now()} #{id_} Found program: {candidate[0]}, train cost: {trainCost}, test cost: {testCost}')

    return candidate

def passTask(folder: str, task: str, debug: bool = False, depth: int = 6):
    dslModel = dsl_model.DSLModel(len(dsl_rl.VOCAB.token2id), d_model = 256, device = device)
    model = dslModel.to(device)
    checkpoint = torch.load(modelFilename, map_location = device)
    model.load_state_dict(checkpoint["model_state"])
    engine = Engine()
    
    with open(f"../ARC-AGI-2/data/{folder}/{task}.json") as f:
        data = json.load(f)

    program, dfTrain, dfTest = processTask(engine, model, task, data, depth, debug)
    trainCost = dfTrain.sum(axis = 0, skipna = False)["Total cost"]
    testCost = dfTest.sum(axis = 0, skipna = False)["Total cost"]

    assert(not (trainCost + testCost))

    return program, trainCost, testCost

def test_task67a3c6ac():
    passTask("training", "67a3c6ac", True, 2)

def test_task68b16354():
    passTask("training", "68b16354", True, 2)

def test_task74dd1130():
    passTask("training", "74dd1130", True, 2)
"""
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
"""
def passTasks(tasks, debug: bool = True):
    dslModel = dsl_model.DSLModel(len(dsl_rl.VOCAB.token2id), d_model = 256, device = device)
    model = dslModel.to(device)
    checkpoint = torch.load(modelFilename, map_location = device)
    model.load_state_dict(checkpoint["model_state"])
    engine = Engine()

    results = {}

    for id_, arc_data in tasks:
        results[id_] = processTask(engine, model, id_, arc_data, debug)

    return results

def processTasks(folder: str, taskIds = set(), debug: bool = True) -> Dict[str, Tuple[float, float, str]]:
    if (len(taskIds) == 0):
        with open(f"../ARC-AGI-2/data/{folder}.txt", "r") as f:
            taskIds = f.read().split("\n")

    data: dict = {}

    for id_ in taskIds:
        with open(f"../ARC-AGI-2/data/{folder}/{id_}.json") as f:
            data[id_] = json.load(f)

    results: dict = {}
    t1 = time.time()

    tasks: list = np.array_split(list(data.items()), os.cpu_count())

    import multiprocessing

    multiprocessing.set_start_method("spawn", force = True)

    with multiprocessing.Pool(os.cpu_count() // 2 + 1) as pool:
        results: list = pool.starmap(passTasks, [(task, debug) for task in tasks])

    result: dict = {}

    for r in results:
        result.update(r)

    results = result

    print(f"Duration for {folder} ({len(taskIds)} tasks): {time.time() - t1} s")

    rows = [
        [task, dfTrain.sum(axis = 0, skipna = False)["Total cost"], dfTest.sum(axis = 0, skipna = False)["Total cost"], program]
        for task, (program, dfTrain, dfTest) in results.items()
    ]

    rows = sorted(rows, key = lambda x: x[0])

    md = tabulate.tabulate(
        rows,
        headers = ["Task", "Train cost", "Test cost", "Program"],
        tablefmt = "pipe"
    )

    with open(f"{folder}_results.md", "w", encoding = "utf-8") as f:
        f.write(md)

    trainSuccess = 0
    testSuccess = 0

    for program, dfTrain, dfTest in results.values():
        trainCost = dfTrain.sum(axis = 0, skipna = False)["Total cost"]
        testCost = dfTest.sum(axis = 0, skipna = False)["Total cost"]

        if (not trainCost):
            trainSuccess += 1

        if (not testCost):
            testSuccess += 1

    print(f"{folder} train: {trainSuccess}/{len(taskIds)} ({trainSuccess/len(taskIds)*100:.2f}%)")
    print(f"{folder} test: {testSuccess}/{len(taskIds)} ({testSuccess/len(taskIds)*100:.2f}%)")

    return results

def test_subtraining_tasks():
    processTasks("training", {'67a3c6ac', '68b16354', '0692e18c', '1caeab9d', '09629e4f', '0f63c0b9', '1c56ad9f', '137eaa0f', '18286ef8', '1d398264', '0bb8deee', '6fa7a44f', '0b17323b', '12997ef3', '184a9768', '08ed6ac7', '5bd6f4ac', '19bb5feb', '3c9b0459', '1b59e163', '25ff71a9', '1b8318e3', '137f0df0', '1b60fb0c', '045e512c', '11e1fe23', '0ca9ddb6', '4c4377d9', '05269061', '15696249', '0962bcdd', '182e5d0f', '0a2355a6', '17b80ad2', '009d5c81', '017c7c7b', '1a07d186', '140c817e', '1cf80156', '0becf7df', '0d87d2a6', '1c02dbbe', '1da012fc', 'd10ecb37', '32597951', '1478ab18', '0607ce86', 'c909285e', '14b8e18c', '195ba7dc', '12eac192', '1c786137', '6150a2bd', '06df4c85', 'b1948b0a', '9dfd6313', '178fcbfb', 'a416b8f3', '17829a00', '11dc524f', '18447a8d', '10fcaaa3', '150deff5', '1d61978c', '13713586', '0c786b71', '03560426', 'c8f0f002', '15113be4', '05a7bcf2', '13f06aa5', '1b2d62fb', '00dbd492', '8be77c9e', '1190bc91', '0d3d703e', '2dee498d', '74dd1130', '0b148d64', '90f3ed37', '1be83260', '15663ba9', '05f2a901', '0e671a1a', '1c0d0a4b', '1990f7a8', '09c534e7', '5614dbcf', '0a1d4ef5', '0a938d79', 'd511f180', '00d62c1b', '0520fde7', '1a244afd', '14754a24', 'c59eb873', '9172f3a0', '18419cfa', '070dd51e', '12422b43', '1a6449f1', '007bbfb7', '17b866bd', '0c9aba6e', '00576224', '0e206a2e', '1190e5a7', '1d0a4b61', '1a2e2828', '15660dd6', '6d0aefbc', '1acc24af', '025d127b', '17cae0c1', 'c9e6f938', 'ed36ccf7', '1bfc4729', '103eff5b', '11852cab', '5582e5ca'}, debug = True)

"""
def test_training_tasks():
    processTasks("training", debug = True)
"""

def test_evaluation_tasks():
    processTasks("evaluation", debug = True)
