from aicpppy import Engine
import datetime
import dsl_model
import dsl_rl
import json
import math
import numpy as np
import os
import pandas as pd
import test_dsl_model
import torch

def processTask(engine, model, data, depth: int = 6):
    inputsTest: list = [(ex["input"]) for ex in data["test"]]
    trainPairs: list = [(ex["input"], ex["output"]) for ex in data["train"]]

    inputsTrain: list = []
    outputsTrain: list = []

    for i, o in trainPairs:
        inputsTrain.append(i)
        outputsTrain.append(o)

    inputs, outputs, masks = dsl_model.arc_pairs_to_tensors(trainPairs)
    inputs = inputs.to(test_dsl_model.device)
    outputs = outputs.to(test_dsl_model.device)
    masks = masks.to(test_dsl_model.device)

    candidates: list = [("I",
                         pd.DataFrame(engine.dfIdentityVsPairs(inputsTrain, outputsTrain), columns = dsl_model.scoreColumns),
                         inputsTest)] * dsl_model.M
    candidates = sorted(candidates, key = lambda x: (tuple(-x[1].sum(axis = 0, skipna = False)), len(x[0]), x[0]))
    count: int = 0
    computeGraphs: bool = True

    model.eval()

    while (candidates[-1][1].sum(axis = 0, skipna = False)["Total cost"] and count < test_dsl_model.MAX_COUNT):
        if (computeGraphs):
            prog_graphs: list  = []
            cost_tensors: list = []

            for program, df, _ in candidates:
                g = dsl_model.build_prog_graph(program, dsl_rl.VOCAB, test_dsl_model.device)
                prog_graphs.append(g)
                cost_tensors.append(dsl_model.dataframe_to_cost_tensor(df).to(test_dsl_model.device))

            computeGraphs = False

            with torch.no_grad():
                z_context = model.encode_context(
                    inputs, outputs, masks,
                    prog_graphs, cost_tensors
                )   # [1, D]

        program = dsl_model.generate_one(
            model, dsl_rl.VOCAB, z_context, engine,
            temperature = 5.0,
            device = test_dsl_model.device,
            max_depth = depth
        )

        if (program):
            try:
                dfTrain = pd.DataFrame(engine.dfConnectionBuilderVsPairs(inputsTrain, outputsTrain), columns = dsl_model.scoreColumns)
                testOutputs = engine.dfConnectionBuilderOutputs(inputsTest)
                cost = dfTrain["Total cost"].sum(skipna = False)
            except RuntimeError:
                cost = math.inf
        else:
            cost = math.inf

        if (not np.isinf(cost).any() and cost < candidates[0][1].sum(axis = 0, skipna = False)["Total cost"]
            and not program in [c[0] for c in candidates]):
            candidates.append((program, dfTrain, testOutputs))
            candidates = sorted(candidates, key = lambda x: (tuple(-x[1].sum(axis = 0, skipna = False)), len(x[0]), x[0]))
            count = 0
            computeGraphs = True

        count += 1

    candidate = candidates[-1]

    while (len(candidates) and not candidates[-1][1].sum(axis = 0, skipna = False)["Total cost"]):
        candidate = candidates.pop()

    print(f'{datetime.datetime.now()} #{id} Found program: {program}, cost: {df.sum(axis = 0, skipna = False)["Total cost"]}')

    return candidate

def processTasks(tasks):
    dslModel = dsl_model.DSLModel(len(dsl_rl.VOCAB.token2id), d_model = 256, device = test_dsl_model.device)
    model = dslModel.to(test_dsl_model.device)
    checkpoint = torch.load(test_dsl_model.modelFilename, map_location = test_dsl_model.device)
    model.load_state_dict(checkpoint["model_state"])
    engine = Engine("")

    results = {}

    for id, arc_data in tasks:
        program, df, testOutputs = processTask(engine, model, arc_data)

        results[id] = [{"attempt_1": testOutputs, "attempt_2": testOutputs}]

    return results

if (__name__ == "__main__"):
    inputFilename: str = "input/competitions/arc-prize-2026-arc-agi-2/arc-agi_evaluation_challenges.json"

    with open(inputFilename, "r") as f:
        data = json.load(f)

    outputFilename: str = "submission.json"
    submission: dict = {}

    #tasks: list = np.array_split(list(data.items()), os.cpu_count())

    #from multiprocessing import Pool

    #with Pool(os.cpu_count()) as pool:
    #    results: list = pool.map(processTasks, tasks)

    results = processTasks(data.items())

    submission: dict = {}

    for result in results:
        submission.update(result)

    with open(outputFilename, "w") as f:
        json.dump(submission, f)
