import copy
import inspect
import json
import numpy as np
import os
import random
import re
import sys
import typing

NUM_COLORS = 10

def generate_structured_grid():
    kind = np.random.choice(['stripes', 'blocks', 'pattern', 'gradient', 'sparse'])
    h = np.random.randint(4, 15)
    w = np.random.randint(4, 15)

    if (kind == 'stripes'):
        grid = np.zeros((h, w), dtype = int)

        for i in range(h):
            if (np.random.rand() > 0.5):
                grid[i, :] = np.random.randint(1, NUM_COLORS)
    elif (kind == 'blocks'):
        grid = np.zeros((h, w), dtype = int)

        for _ in range(np.random.randint(2, 6)):
            r1, r2 = sorted(np.random.randint(0, h, 2))
            c1, c2 = sorted(np.random.randint(0, w, 2))
            grid[r1:r2+1, c1:c2+1] = np.random.randint(1, NUM_COLORS)
    elif (kind == 'pattern'):
        base_h = np.random.randint(2, max(3, h // 2))
        base_w = np.random.randint(2, max(3, w // 2))
        base   = np.random.randint(0, NUM_COLORS, (base_h, base_w))
        grid   = np.tile(base, (h // base_h + 1, w // base_w + 1))[:h, :w]
    elif (kind == 'gradient'):
        grid = np.zeros((h, w), dtype = int)

        for i in range(h):
            grid[i, :] = int(i * (NUM_COLORS - 1) / max(h - 1, 1))
    else:  # sparse
        grid = np.zeros((h, w), dtype = int)

        for _ in range(np.random.randint(3, 10)):
            grid[np.random.randint(h), np.random.randint(w)] = np.random.randint(1, NUM_COLORS)

    return grid

def generate_dsls(ratio: list[tuple[float, float, float]], ratioConns: float = 1.0):
    with open("arc-dsl/constants.py", "r") as f:
        lines = f.read().split("\n")

    constants = {}
    namespace = {}
    exec("\n".join(lines), namespace)
    
    for line in lines:
        if (not line):
            continue

        n, v = line.split(" = ")
        
        v = namespace[n]
        t = type(v)
        
        if (t == tuple):
            t = typing.Tuple[int, int]

        constants[n] = (t, v)

    constants["I"] = (typing.Tuple[typing.Tuple[int]], ())

    with open("arc-dsl/arc_types.py", "r") as f:
        lines = f.read().split("\n")

    source = ""
    index = 0
    
    while (index < len(lines)):
        if (not lines[index]):
            break
        
        source += lines[index]
        index += 1

    types = {}
    index += 1
    namespace = {}
    
    while (index < len(lines) and lines[index]):
        n, t = lines[index].split(" = ")

        exec(source + f"\n{n} = {t}", namespace)
        types[n] = namespace[n]

        index += 1

    with open("arc-dsl/dsl.py", "r") as f:
        lines = f.read().split("\n")

    import test_arc

    arc_types_module = test_arc.load_module("arc_types", "arc-dsl/arc_types.py")
    constants_module = test_arc.load_module("constants", "arc-dsl/constants.py")
    dsl_module = test_arc.load_module("dsl", "arc-dsl/dsl.py")

    env = {}
    env.update(vars(arc_types_module))
    env.update(vars(constants_module))
    env.update(vars(dsl_module))

    namespace = {}
    namespace.update(env)
    exec("\n".join(lines), namespace)
    
    functions = {}
    
    for line in lines:
        if (line.startswith("def ")):
            name = line[len("def "):line.index("(")]
            functions[name] = namespace[name]

    from brain import Brain
    from connection import Connection
    from neuron import Neuron

    neurons = {}

    for n, p in constants.items():
        neurons[n] = Neuron(n, lambda p = p: p[1], [], p[0])

    for n, f in functions.items():
        sig = inspect.signature(f)

        parameters = sig.parameters
        return_annotation = sig.return_annotation
        inputTypes = []

        for k, v in parameters.items():
            if (not v.annotation is inspect._empty):
                inputTypes.append(v.annotation)

        neurons[n] = Neuron(n, lambda f = f: f, inputTypes, return_annotation)

    b = Brain(neurons.values())
    connectionMapping = b.buildConnectionMapping(ratio, ratioConns, debug = True)
    connections = connectionMapping[typing.Tuple[typing.Tuple[int]]]

    del connectionMapping
    del b

    print("Building DSL expressions")

    dsls = [c.toStr() for c in connections]    

    del connections

    dsls = list(filter(lambda x: "(I" in x or ", I" in x, dsls))
    dsls = sorted(dsls, key = lambda x: (len(x), x))

    return dsls

def generate_dsl():
    import test_arc

    command = test_arc.dslPrompt()
    command += """

Generate a valid DSL program using the previous primitives.

Constraints:
- must represent a meaningful transformation on grids
- avoid trivial identity
- avoid overly complex nesting
- prefer transformations like: rotation, symmetry, object filtering, color mapping

Return only the DSL expression.

# EXPECTED OUTPUT EXAMPLE WITHOUT ANY FORMATTING AND ANY EXPLANATION
```python
def dsl(I):
    # O = ...
    return O
```
"""

    content = test_arc.callOllama("gpt-oss:120b", command)

    groups = re.findall(r'```python(.*?)```', content, flags = re.S)

    assert(len(groups))

    return groups[-1]

def generate_example(dsl: str):
    import test_arc

    grids = []
    runner = test_arc.DSLWorker()

    lines = dsl.strip().split("\n")
    source = dsl
    name = "dsl"

    if (lines[0].startswith("def ")):
        name = source[len("def "):source.index("(")]
    else:
        source = f"def dsl(I):\n    return {dsl}"

    for _ in range(random.randint(3, 6)):
        #inp = generate_structured_grid()
        inp = np.random.randint(0, 10, (np.random.randint(3, 10), np.random.randint(3, 10)))
        out = np.array(runner.run_with_timeout(source, name, 5, tuple(map(tuple, inp.tolist()))))

        if (inp.shape == out.shape and np.all(inp == out)):
            continue

        if (np.max(out) > 9 or np.min(out) < 0):
            continue

        grids.append((inp, out))
        del inp
        del out

    runner.terminate()

    if (len(grids) < 3):
        raise RuntimeError("Not enough grids")

    return {
        "code": source,
        "dsl": dsl,
        "pairs": grids
    }

def format_example(example):
    import dsl_transformer

    return {
        "input": dsl_transformer.grids_to_input_text(example["pairs"]),
        "output": f"{example['dsl']}"
    }

def dumpsDataset(depth: str, data: list):
    with open(f"dsl_dataset{depth}.json", "a") as f:
        for d in data:
            f.write(json.dumps(d) + "\n")

def generate_dataset_from_dsls(numSets: int, depth: str, dsls: list):
    import view_dsl_graph

    expressions = set()

    for dsl in dsls:
        try:
            expressions.add(view_dsl_graph.programExpression(dsl))
        except Exception:
            pass

    print(f"{len(expressions)} unique expressions")

    data = []
    #random.shuffle(dsls)

    with open(f"dsl_dataset{depth}.json", "w") as f:
        pass

    count = 0

    expressions = sorted(expressions, key = lambda x: (len(x), x))
    validExpressions = []    

    for expression in expressions:
        examples = []

        try:
            for _ in range(0, numSets):
                ex = generate_example(expression)
                formatted = format_example(ex)
                data.append(formatted)
                examples.append(ex)
                
                del ex
                del formatted

                count += 1

                if (count % 100 == 0):
                    print(f"{count} examples")

                if (len(data) % 400 == 0):
                    dumpsDataset(str(depth), data)
                    del data
                    data = []

                    print("Dataset saved.")
        except Exception:
            pass
        
        if (len(examples)):
            while (len(examples) < numSets):
                try:
                    ex = copy.deepcopy(random.choice(examples))
                    pairs = ex["pairs"]

                    for i in range(len(pairs)):
                        x = np.array(pairs[i])
                        np.random.shuffle(x)
                        pairs[i] = x

                    formatted = format_example(ex)
                    data.append(formatted)
                    examples.append(ex)

                    del ex
                    del formatted

                    count += 1

                    if (count % 100 == 0):
                        print(f"{count} examples")

                    if (len(data) % 400 == 0):
                        dumpsDataset(str(depth), data)
                        del data
                        data = []

                        print("Dataset saved.")
                except Exception:
                    print(expression, len(examples), numSets)
                    break

            validExpressions.append((expression, len(examples)))

    print(f"{len(validExpressions)} valid expressions")

    dumpsDataset(str(depth), data)

def generate_dataset(numSets: int, ratio: list[tuple[float, float, float]], ratioConns: float = 1.0):
    depth = len(ratio)

    filename = f"dsls{depth}.txt"

    if (os.path.exists(filename)):
        with open(filename, "r") as f:
            dsls = f.read().split("\n")
    else:
        dsls = generate_dsls(ratio, ratioConns)

        f = open(filename, "w")
        f.write("\n".join(dsls))
        f.close()

    generate_dataset_from_dsls(numSets, str(depth), dsls)

def generate_dataset_from_memory(llm: tuple, numSets: int):
    import dsl_memory
    import test_arc

    dsls = list(sorted(dsl_memory.load(f"data/{test_arc.llmPath(llm)}/dsl_memory.pkl"), key = lambda x: (len(x), x)))
    dsls = list(filter(lambda x: x.startswith("def"), dsls))

    generate_dataset_from_dsls(numSets, "", dsls)

if (__name__ == "__main__"):
    match (int(sys.argv[-1])):
        case 0:
            generate_dataset_from_memory((sys.argv[-4], sys.argv[-3]), int(sys.argv[-2]))
        case 1:
            generate_dataset(50, [(1.0, 1.0, 1.0)], 1.0)
        case 2:
            generate_dataset(50, [(0.8, 0.8, 0.8), (0.4, 0.4, 0.4)], 0.1)
        case 3:
            generate_dataset(50, [(0.4, 0.4, 0.4), (0.2, 0.2, 0.2), (0.02, 0.02, 0.02)], 0.1)
