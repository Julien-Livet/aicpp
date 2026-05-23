import collections
from connection import compatibleType
from dsl_tree import args, tree, Tree, vocabulary
from multiprocess import Pool
import numpy as np
import os
import random
from typing import get_args, get_origin, Tuple
import dsl_engine

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

def randomDslTree(maxDepth: int):
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
    I = tuple(map(tuple, np.random.randint(0, 10, (3, 3)).tolist()))
    count = 0

    while (len(s) < n):
        tr = randomDslTree(depth)
        program = str(tr)

        if (not "(I)" in program and not "(I, " in program and not ", I," in program and not ", I)" in program):
            continue

        O = execute_dsl(program, I)

        if (O and compatibleType(type(O), Tuple[Tuple[int]]) and type(O[0]) is tuple):
            s.add(program)
            count = 0
        else:
            count += 1

        #if (count > 100):
        #    break

    return s

def buildDataset(n: int = 200, maxDepth: int = 8):
    args = [(n, depth) for depth in range(1, maxDepth + 1)]

    with Pool(os.cpu_count()) as pool:
        list_of_sets = pool.starmap(dslProgram, args)
    
    dataset = set().union(*list_of_sets)
    dataset = sorted(list(dataset))

    with open("dsl_dataset.txt", "w") as f:
        f.write("\n".join(dataset))

if (__name__ == "__main__"):
    buildDataset()