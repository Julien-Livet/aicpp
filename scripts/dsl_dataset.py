import collections
from connection import compatibleType
from dsl_tree import args, tree, Tree, vocabulary
import math
from multiprocess import Pool
import numpy as np
import os
import random
from typing import get_args, get_origin, Tuple
import dsl_engine

GRID_SIZE = (10, 10)

arc_types = dsl_engine.load_module("arc_types", "arc-dsl/arc_types.py")
constants = dsl_engine.load_module("constants",  "arc-dsl/constants.py")
dsl       = dsl_engine.load_module("dsl",        "arc-dsl/dsl.py")
ns = {}
ns.update(vars(arc_types))
ns.update(vars(constants))
ns.update(vars(dsl))

def execute_dsl(program: str, input_grid: List) -> Optional[List]:
    try:
        ns["I"] = tuple(map(tuple, input_grid))
        result = eval(program, {"__builtins__": {}}, ns)

        return result
    except Exception:
        pass

    return None

def randomDslTree(maxDepth: int) -> Tree:
    roots: list = []

    for name, (t, v) in vocabulary.items():
        if (get_origin(t) is collections.abc.Callable):
            t = get_args(t)[1]

        if (compatibleType(t, Tuple[Tuple[int]])):
            roots.append(name)

    tr = tree(random.choice(roots))

    while (not tr.isFinished()):
        c = str(tr).count("(")
        a = args(tr.nextType())

        if (c >= maxDepth):
            s = []

            for arg in a:
                t, v = vocabulary[arg]

                if (not get_origin(t) is collections.abc.Callable):
                    s.append(arg)

                a = s
        
        if (not a):
            return tr

        tr.applyNextType(tree(random.choice(a)))

    return tr

def dslProgram(n: int, depth: int) -> set:
    s = set()
    I = tuple(map(tuple, np.random.randint(0, 10, GRID_SIZE).tolist()))

    while (len(s) < n):
        tr = randomDslTree(depth)
        program = str(tr)

        if (not "(I)" in program and not "(I, " in program and not ", I," in program and not ", I)" in program):
            continue

        O = execute_dsl(program, I)

        try:
            if (O and compatibleType(type(O), Tuple[Tuple[int]]) and type(O[0]) is tuple and I != O and len(O) > 1 and np.min(O) >= 0 and np.max(O) <= 9):
                s.add(program)
        except Exception:
            pass

    return s

def buildDataset(n: int = 200, maxDepth: int = 8) -> list:
    args = [(n, depth) for depth in range(1, maxDepth + 1)]

    with Pool(os.cpu_count()) as pool:
        list_of_sets = pool.starmap(dslProgram, args)
    
    dataset = set().union(*list_of_sets)
    dataset = sorted(list(dataset))

    return dataset

def randomTrajectory() -> list:
    with open("dsl_dataset.txt", "r") as f:
        programs = f.read().split("\n")

    programs.append("I")

    choosedProgram = random.choice(programs)
    gridPairs: list = []

    for _ in range(3):
        I = tuple(map(tuple, np.random.randint(0, 10, GRID_SIZE).tolist()))
        O = execute_dsl(choosedProgram, I)
        gridPairs.append((I, O))

    sortedPrograms: list = []

    from test_dsl_engine import arcHeuristic

    for program in programs:
        cost: float = 0

        for pairs in gridPairs:
            cost += arcHeuristic(pairs[1], execute_dsl(program, pairs[0]))

        if (not math.isinf(cost)):
            sortedPrograms.append((cost, program))

    sortedPrograms.sort(key = lambda x: x[0], reverse = True)

    trajectory: list = []

    while (sortedPrograms):
        c, p = sortedPrograms.pop(0)
        
        if (p == "I"):
            trajectory.append((c, p))
            break

    cost: float = trajectory[0][0]

    while (sortedPrograms):
        c, p = sortedPrograms.pop(0)

        if (c < cost):
            cost = c
            trajectory.append((c, p))

    return choosedProgram, trajectory

if (__name__ == "__main__"):
    dataset = buildDataset()
    datasetFilename: str = "dsl_dataset.txt"

    with open(datasetFilename, "r") as f:
        dataset = sorted(set(dataset + f.read().split("\n")))

    with open(datasetFilename, "w") as f:
        f.write("\n".join(dataset))

    choosedProgram, trajectory = randomTrajectory()

    with open("dsl_random_trajectory.txt", "w") as f:
        f.write(choosedProgram + "\n")
        f.write("\n".join([str(x) for x in trajectory]))
