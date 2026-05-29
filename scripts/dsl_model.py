from dsl_engine import size_cost, bounding_box_cost, pixel_overlap_cost, value_cost
from dsl_dataset import execute_dsl
import math
from multiprocessing import Pool
import numpy as np
import os
import pandas as pd
import json
from typing import List, Tuple

scoreFunctions = [size_cost, bounding_box_cost, pixel_overlap_cost, value_cost]
scoreColumns = ["Grid size cost", "Bounding box cost", "Pixel overlap cost", "Value cost", "Total cost"]

Grid = Tuple[Tuple[int]]

def programDf(program: str, pairs: List[Tuple[Grid, Grid]]) -> pd.DataFrame:
    scores: list = []
        
    for pair in pairs:
        O = execute_dsl(program, pair[0])

        score: list = [0] * len(scoreFunctions)

        for i in range(0, len(scoreFunctions)):
            a1 = 0
            a2 = 0

            try:
                a1 = np.array(O)
                a2 = np.array(pair[1])
                score[i] = scoreFunctions[i](a1, a2)
            except:
                score[i] = math.inf

            del a1
            del a2

        del O

        scores.append(score + [sum(score)])

    df = pd.DataFrame(scores, index = [f"grid{i+1}" for i in range(len(pairs))], columns = scoreColumns)

    del scores

    return df

def programCosts(targetProgram: str, programs: List[str], inputs: Tuple[Tuple[int]]) -> List[pd.DataFrame]:
    outputs: list = []
    
    for grid in inputs:
        outputs.append(execute_dsl(targetProgram, grid))
    
    pairs = list(zip(inputs, outputs))

    with Pool(os.cpu_count()) as pool:
        dfs = pool.starmap(programDf, [(program, pairs) for program in programs])
    
    return dfs

if (__name__ == "__main__"):
    with open("model_dataset.jsonl", "r") as f:
        lines = f.read().split("\n")

    modelDataset: dict = {}

    for line in lines:
        try:
            o = json.loads(line)
            modelDataset[o["program"]] = tuple([tuple(map(tuple, x)) for x in o["grids"]])
        except Exception:
            pass

    modelDataset["I"] = modelDataset[list(modelDataset.keys())[-1]]
    modelDataset = dict(sorted(modelDataset.items(), key = lambda x: (len(x[0]), x[0])))
    modelDataset = dict(list(modelDataset.items())[:100])

    for k, v in modelDataset.items():
        costs = dict(zip(modelDataset.keys(), programCosts(k, modelDataset.keys(), v)))
        costs = sorted(costs.items(), key = lambda x: (tuple(-x[1].sum(axis = 0, skipna = False)), len(x[0]), x[0]))

        while (costs[0][0] != "I"):
            costs.pop(0)

        costs = dict(costs)

        try:
            print(k)
            print(list(costs.keys())[0], costs[list(costs.keys())[0]])
            print(list(costs.keys())[1], costs[list(costs.keys())[1]])
            print(list(costs.keys())[-2], costs[list(costs.keys())[-2]])
            print(list(costs.keys())[-1], costs[list(costs.keys())[-1]])
        except Exception:
            pass
        input("hit")

        del costs