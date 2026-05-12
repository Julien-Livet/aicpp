import ast
from collections import defaultdict
from connection import compatibleType, Connection, is_container_of_container, is_container_type
import heapq
import importlib.util
import itertools
import json
from neuron import Neuron
import numpy as np
import random
from scipy.stats import norm
from sklearn.gaussian_process import GaussianProcessRegressor
from sklearn.gaussian_process.kernels import RBF, ConstantKernel
from sklearn.preprocessing import StandardScaler
import sympy
import sys
import textdistance
import typing
from typing import Any, Callable, Dict, get_args, get_origin, Iterator, Tuple, Union

Grid = Tuple[Tuple[int]]

def trainTestPairs(folder: str, task: str) -> tuple:
    assert(folder in ("training", "evaluation"))

    with open(f"../ARC-AGI-2/data/{folder}/{task}.json", "r") as file:
        data = json.loads(file.read())

    train = data["train"]
    trainPairs = []

    for v in train:
        trainPairs.append((np.array(v["input"]), np.array(v["output"])))

    test = data["test"]
    testPairs = []

    for v in test:
        testPairs.append((np.array(v["input"]), np.array(v["output"])))

    return (trainPairs, testPairs)

def getDslVariables() -> Dict[str, str]:
    arc_types_module = load_module("arc_types", "arc-dsl/arc_types.py")

    with open("arc-dsl/constants.py", "r") as f:
        content = f.read()

    namespace = {}
    namespace.update(vars(arc_types_module))

    types = {}

    for k, v in namespace.items():
        if (not k.startswith("_")):
            types[v] = k

    from typing import Tuple

    types[tuple] = Tuple

    exec(content, namespace)

    variables = {}

    for k, v in namespace.items():
        if (not k in vars(arc_types_module)):
            variables[k] = types[type(v)]

    variables["I"] = types[Tuple[Tuple]]

    return variables

def getDslPrimitives() -> Dict[str, dict]:
    with open("arc-dsl/dsl.py", "r") as f:
        lines = f.read().split("\n")

    i = 0
    definition = ""
    primitives = {}
    
    while (i < len(lines)):
        if (lines[i].startswith("def ")):
            definition = lines[i]        

        if (definition.endswith(":")):
            definition = definition.replace("def", "").replace(" ", "")[:-1]

            sig = "def " + definition + ": pass"

            tree = ast.parse(sig)
            func = tree.body[0]

            args = []

            for arg in func.args.args:
                args.append({"name": arg.arg, "type": ast.unparse(arg.annotation)})

            primitives[func.name] = {"args": args, "return_type": ast.unparse(func.returns)}

            definition = ""
        elif (len(definition) and not lines[i].startswith("def ")):
            definition += lines[i]

        i += 1

    return primitives

def load_module(name: str, path: str):
    spec = importlib.util.spec_from_file_location(name, path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    sys.modules[name] = module
    
    return module

def size_cost(x: np.ndarray, y: np.ndarray) -> float:
    return np.linalg.norm(np.array(x.shape) - np.array(y.shape))

def value_cost(x: np.ndarray, y: np.ndarray) -> float:
    if (x.shape == y.shape):
        return np.linalg.norm(x - y)
        
    return abs(sum(sum(x)) - sum(sum(y)))

def pixel_overlap_cost(x: np.ndarray, y: np.ndarray) -> float:
    if (x.shape != y.shape):
        return np.prod(x.shape) + np.prod(y.shape)

    total = x.size
    matches = np.sum(x == y)

    return 1.0 - (matches / total)

def bounding_box(arr: np.ndarray):
    coords = np.argwhere(arr != 0)
    
    if (coords.size == 0):
        return None

    y_min, x_min = coords.min(axis = 0)
    y_max, x_max = coords.max(axis = 0)

    return (y_min, x_min, y_max, x_max)

def bounding_box_cost(x: np.ndarray, y: np.ndarray) -> float:
    box_x = bounding_box(x)
    box_y = bounding_box(y)

    if (box_x is None and box_y is None):
        return 0.0

    if (box_x is None or box_y is None):
        return 1.0

    diff = np.linalg.norm(np.array(box_x) - np.array(box_y))
    norm = np.linalg.norm(np.array(x.shape) + np.array(y.shape))

    return diff / (norm + 1e-8)

class TypeSystem:
    def __init__(self):
        arc_types_module = load_module("arc_types", "arc-dsl/arc_types.py")

        with open("arc-dsl/constants.py", "r") as f:
            content = f.read()

        namespace = {}
        namespace.update(vars(arc_types_module))

        types = {}

        for k, v in namespace.items():
            if (not k.startswith("_")):
                types[v] = k

        from typing import Tuple

        Integer = int
        types[tuple] = Tuple[Integer, Integer]

        exec(content, namespace)

        variables = {}
        self.dslVariableValues = {}

        for k, v in namespace.items():
            if (not k in vars(arc_types_module)):
                variables[k] = types[type(v)]
                self.dslVariableValues[k] = v

        self.dslVariables = {"I": Grid}
        
        exec("import typing", namespace)

        for k, v in variables.items():
            exec(f"variable = {v}", namespace)
            self.dslVariables[k] = namespace["variable"]

        for i in range(10):
            self.dslVariables[str(i)] = Integer

        self.dslPrimitives = getDslPrimitives()

        for name in self.dslPrimitives.keys():
            self.dslVariables[name] = Callable

        self.variableTypes = defaultdict(list)

        for k, v in self.dslVariables.items():
            self.variableTypes[v].append(k)

        for k1, v1 in self.dslPrimitives.items():
            for arg in v1["args"]:
                exec(f"arg = {arg['type']}", namespace)
                arg["type"] = namespace["arg"]

            exec(f"arg = {v1['return_type']}", namespace)
            v1["return_type"] = namespace["arg"]

        self.primitiveTypes = defaultdict(list)

        for k, v in self.dslPrimitives.items():
            expected = v["return_type"]

            if (get_origin(expected) is Union):
                for arg in get_args(expected):
                    self.primitiveTypes[arg].append(k)
            else:
                self.primitiveTypes[expected].append(k)

        self.declinedPrimitives = {}

        for name in self.dslPrimitives.keys():
            self.declinedPrimitives[name] = self.declinedPrimitive(name)

        self.declinedPrimitives = dict(sorted(self.declinedPrimitives.items()))

    def declinedPrimitive(self, name: str) -> str:
        args = []
            
        for arg in self.dslPrimitives[name]["args"]:
            expected = arg["type"]
            result = self.variablesForType(expected)

            if (result):
                args.append(result[-1])
            else:
                result = []
                
                if (expected is typing.Container):
                    for k, v in self.primitiveTypes.items():
                        if (is_container_type(k)):
                            result += v
                elif (expected is typing.Container[typing.Container]):
                    for k, v in self.primitiveTypes.items():
                        if (is_container_of_container(k)):
                            result += v
                elif (get_origin(expected) is Union):
                    for arg in get_args(expected):
                        result += self.primitiveTypes[arg]
                else:
                    result = self.primitiveTypes[expected]
                
                if (result):
                    args.append(self.declinedPrimitive(result[-1]))
                else:
                    args.append(f"{expected}:unknown")

        return f"{name}({','.join(args)})"

    def variablesForType(self, expected: type) -> list:
        result = []

        if (expected is Any):
            for v in self.variableTypes.values():
                result += v
        elif (expected is typing.Container):
            for k, v in self.variableTypes.items():
                if (is_container_type(k)):
                    result += v
        elif (expected is typing.Container[typing.Container]):
            for k, v in self.variableTypes.items():
                if (is_container_of_container(k)):
                    result += v
        elif (get_origin(expected) is Union):
            for arg in get_args(expected):
                result += self.variableTypes[arg]
        else:
            result = self.variableTypes[expected]

        return result

def expected_improvement(mu, sigma, y_best, xi = 0.01):
    improvement = y_best - mu - xi
    Z = improvement / (sigma + 1e-9)
    ei = improvement * norm.cdf(Z) + sigma * norm.pdf(Z)
    ei[sigma <= 0] = 0

    return ei

def heuristic(val, target):
    if (isinstance(target, str)):
        s = val

        cost = 0 if isinstance(val, str) else 1

        try:
            s = str(val)
        except:
            pass

        if (isinstance(s, str)):
            a, b = s, target

            if (b in a):
                a, b = b, a

            if (a in b):
                return cost + 1 - 1 / target.count(a) + 1 / (1 + len(a)) - 1 / (1 + len(b))

            return cost + 1 / (1 + len(a)) - 1 / (1 + len(b)) + textdistance.Levenshtein().distance(a, b)
        else:
            return abs(hash(val) - hash(target))
    elif (isinstance(target, sympy.Expr)):
        if (isinstance(val, sympy.Expr)):
            if (val == target):
                return 0
            else:
                return heuristic(str(val), str(target))
        else:
            return 1 + heuristic(str(val), str(target))

    unknown = False

    try:
        x = np.array(val)
        y = np.array(target)

        if (x.shape == y.shape):
            return np.linalg.norm(x - y)
        else:
            xs = np.array(x.shape)
            ys = np.array(y.shape)
            
            if (np.all(np.equal(xs, np.flip(ys)))):
                return np.linalg.norm(xs - ys) + np.linalg.norm(x - np.transpose(y))
            else:
                return np.linalg.norm(xs - ys) + abs(np.sum(x) - np.sum(y))
    except:
        unknown = True

    if (unknown):
        unknown = False

        if (type(val) == list and type(target) == list):
            try:
                v = val
                t = target

                if (len(v) != len(t)):
                    return 100 + abs(sum(v) - sum(t))

                x = []

                for i in range(0, len(v)):
                    x.append(heuristic(v[i], t[i]))

                return np.linalg.norm(x)
            except:
                unknown = True
        else:
            unknown = True

    return 999.0

def space_size(combinations: list) -> int:
    s = 1

    for c in combinations:
        s *= len(c)

    return s

def sample_space(
    combinations : list,
    n            : int,
    strategy     : str = "mixed",
    exclude      : set | None = None,
) -> list:
    """
    strategy :
      "random" — uniform draw
      "grid"   — latin hypercube approximation (good uniform coverage)
      "mixed"  — 50% grid + 50% random  (recommanded)
    """
    if (exclude is None):
        exclude = set()

    size = space_size(combinations)

    n    = min(n, max(0, size - len(exclude)))

    if (n <= 0):
        return []

    samples: set = set()

    # Latin hypercube approximate
    if (strategy in ("grid", "mixed")):
        n_grid  = n if strategy == "grid" else max(1, n // 2)
        indices = []
    
        for dim_vals in combinations:
            k    = len(dim_vals)
            step = max(1, k // n_grid)
            idx  = list(range(0, k, step))[:n_grid]
    
            while (len(idx) < n_grid):
                idx.append(random.randrange(k))

            random.shuffle(idx)
            indices.append(idx)

        for row in zip(*indices):
            pt = tuple(combinations[d][row[d]] for d in range(len(combinations)))
            
            if (pt not in exclude):
                samples.add(pt)

    # Complete with random draw
    attempts     = 0
    max_attempts = n * 30
    
    while (len(samples) < n and attempts < max_attempts):
        pt = tuple(random.choice(dim_vals) for dim_vals in combinations)
        
        if (pt not in exclude):
            samples.add(pt)

        attempts += 1

    return list(samples)

def iter_space(combinations: list, shuffle: bool = True) -> Iterator:
    if (shuffle):
        shuffled = [list(c) for c in combinations]

        for c in shuffled:
            random.shuffle(c)

        yield from itertools.product(*shuffled)
    else:
        yield from itertools.product(*combinations)

def _sampled_neighbors(
    point        : tuple,
    dim          : int,
    combinations : list,
    k            : int,
) -> list:
    dim_vals   = combinations[dim]
    cur        = point[dim]
    other_vals = [v for v in dim_vals if v != cur]

    if (not other_vals):
        return []

    chosen = random.sample(other_vals, min(k, len(other_vals)))
    result = []

    for v in chosen:
        nb       = list(point)
        nb[dim]  = v
        result.append(tuple(nb))

    return result

def encode_output_space_discrete(points: list, op: Callable, combinations: list, target: object,
                                 heuristicFunction: Callable, k_neighbors: int = 8) -> np.ndarray:
    D      = len(combinations)
    result = []

    for point in points:
        v         = heuristicFunction(op(point), target)
        subresult = [v]

        for dim in range(D):
            nbs    = _sampled_neighbors(point, dim, combinations, k_neighbors)
            scores = [heuristicFunction(op(nb), target) for nb in nbs] if nbs else [v]
            subresult += [
                float(np.mean(scores)),
                float(np.std(scores)) if len(scores) > 1 else 0.0,
                float(min(scores)),
                float(max(scores)),
                float(v - np.mean(scores)),
            ]

        result.append(subresult)

    if (not result):
        return np.zeros((0, 1 + D * 5), dtype = float)

    max_len = max(len(r) for r in result)

    for r in result:
        while (len(r) < max_len):
            r.append(0.0)

    return np.array(result, dtype=float)

def bayesian_optimization_discrete(
    op: Callable,
    target: object,
    combinations: list,
    heuristicFunction: Callable,
    n_init: int = 5,
    top_k: int = 3,
    xi: float = 0.01,
    count_max: int = 10,
    n_sample: int = 200,
    k_neighbors: int = 8,
    threshold: float = 0.0
) -> tuple[object, object]:
    size: int = space_size(combinations)
    
    init_pts = sample_space(combinations, n_init, strategy = "mixed")
    obs_x    = []
    obs_y    = []

    for x in init_pts:
        try:
            y = float(heuristicFunction(op(x), target))
            obs_x.append(x)
            obs_y.append(y)

            if (y <= threshold):
                return x, y
        except Exception:
            pass
    
    if (not obs_x):
        first = next(iter_space(combinations), None)

        return (first, 999.0) if first else ((), 999.0)
    
    best_x    = obs_x[int(np.argmin(obs_y))]
    best_y    = min(obs_y)
    prev_best = float("inf")
    count     = 0
    C_enc = None
    candidates = None

    kernel = ConstantKernel(1.0) * RBF(length_scale = 1.0)
    gp     = GaussianProcessRegressor(
        kernel = kernel, n_restarts_optimizer = 3,
        normalize_y = True, alpha = 1e-2,
    )

    while (True):
        obs_set = set(obs_x)

        X_enc = encode_output_space_discrete(obs_x, op, combinations, target, heuristicFunction, k_neighbors)
        Y = np.array(obs_y, dtype = float)

        if (X_enc.shape[0] < 2):
            break

        try:
            scaler  = StandardScaler().fit(X_enc)
            X_sc    = scaler.transform(X_enc)
            gp.fit(X_sc, Y)
        except Exception:
            break

        candidates = sample_space(
            combinations, n_sample, strategy = "mixed", exclude=obs_set
        )

        if (not candidates):
            break

        C_enc = encode_output_space_discrete(candidates, op, combinations, target, heuristicFunction, k_neighbors)

        if (C_enc.shape[0] == 0):
            break

        # Align dimensions (security if X_enc and C_enc are different)
        n_cols  = min(X_sc.shape[1], C_enc.shape[1])

        try:
            scaler2 = StandardScaler().fit(X_enc[:, :n_cols])
            C_sc    = scaler2.transform(C_enc[:, :n_cols])
            mu, sigma = gp.predict(C_sc, return_std=True)
        except Exception:
            break

        ei          = expected_improvement(mu, sigma, float(np.min(Y)), xi = xi)
        top_idx     = np.argsort(-ei)[:top_k]
        top_cands   = [candidates[i] for i in top_idx]

        improved = False

        for x in top_cands:
            try:
                y = float(heuristicFunction(op(x), target))
                obs_x.append(x)
                obs_y.append(y)

                if (y <= threshold):
                    return x, y

                if (y < best_y):
                    best_x   = x
                    best_y   = y
                    improved = True
            except Exception:
                pass

        if (best_y < prev_best):
            prev_best = best_y
            count     = 0
        elif (not improved):
            count += 1

        if (count >= count_max):
            break

        if (len(obs_x) >= size):
            break

    del X_enc
    del Y
    del obs_x
    del obs_y
    del gp
    del obs_set

    if (np.all(C_enc)):
        del C_enc

    if (candidates):
        del candidates

    return best_x, best_y

class Engine:
    def __init__(self, heuristicFunction: Callable = heuristic,
                 bo_n_init: int = 1000, bo_top_k: int = 100, bo_count_max: int = 20):
        self.heuristicFunction = heuristicFunction
        self.bo_n_init = bo_n_init
        self.bo_top_k = bo_top_k
        self.bo_count_max = bo_count_max
        self.typeSystem: TypeSystem = TypeSystem()
        self.variableNeurons: dict = dict()

        for k, v in self.typeSystem.dslVariableValues.items():    
            neuron: Neuron = Neuron(k, lambda v = v: v, [], self.typeSystem.dslVariables[k])
            self.variableNeurons[k] = neuron

        arc_types_module = load_module("arc_types", "arc-dsl/arc_types.py")

        with open("arc-dsl/dsl.py", "r") as f:
            content = f.read()

        namespace = {}
        namespace.update(vars(arc_types_module))

        exec(content, namespace)

        self.primitiveNeurons: dict = dict()

        for k, v in self.typeSystem.dslPrimitives.items():
            neuron: Neuron = Neuron(k, namespace[k], [x["type"] for x in v["args"]], v["return_type"])
            self.primitiveNeurons[k] = neuron
            neuron: Neuron = Neuron(k, lambda v = v: v, [], Callable)
            self.variableNeurons[k] = neuron

        self.primitiveNeurons = dict(sorted(self.primitiveNeurons.items(), key = lambda x: (len(x[1].inputTypes), x[0])))
        self.sortedPrimitiveNeurons: dict = defaultdict(list)
        self.typedPrimitiveNeurons: dict = defaultdict(list)

        for name, neuron in self.primitiveNeurons.items():
            self.sortedPrimitiveNeurons[len(neuron.inputTypes)].append(neuron)

            if (get_origin(neuron.outputType) is Union):
                for arg in get_args(neuron.outputType):
                    self.typedPrimitiveNeurons[arg].append(neuron)
            else:
                self.typedPrimitiveNeurons[neuron.outputType].append(neuron)

        self.typedVariableNeurons: dict = defaultdict(list)

        for neuron in self.variableNeurons.values():
            self.typedVariableNeurons[neuron.outputType].append(neuron)

        for k, v in self.typedVariableNeurons.items():
            self.typedVariableNeurons[k] = sorted(v, key = lambda x: x.name)

        self.connections: dict = dict()
        self.typedConnections: dict = defaultdict(list)

    def valuesForType(self, typedValues: dict, expected: type) -> list:
        result = []

        if (expected is Any):
            for v in typedValues.values():
                result += v
        elif (expected is typing.Container):
            for k, v in typedValues.items():
                if (is_container_type(k)):
                    result += v
        elif (expected is typing.Container[typing.Container]):
            for k, v in typedValues.items():
                if (is_container_of_container(k)):
                    result += v
        elif (get_origin(expected) is Union):
            for arg in get_args(expected):
                result += typedValues[arg]
        else:
            result = typedValues[expected]

        return result

    def clearVariableNeurons(self):
        self.variableNeurons.clear()
        self.typedVariableNeurons.clear()

    def clearPrimitiveNeurons(self):
        self.primitiveNeurons.clear()
        self.typedPrimitiveNeurons.clear()

    def learn(self, target: object, targetType: type = None) -> tuple[Connection, object, object]:
        if (not targetType):
            targetType = type(target)

        frontier: list = []
        addedConnections: dict = {}

        def explore():
            for n in self.primitiveNeurons.values():
                if (not compatibleType(targetType, n.outputType)):
                    continue
                #print("n.name", n.name) #TODO: to remove
                combinations: list = []

                for inputType in n.inputTypes:
                    possibleConnections = self.valuesForType(self.typedConnections, inputType)
                    combinations.append([inputType] + possibleConnections)

                if (not combinations):
                    continue

                product = itertools.product(*combinations)
                del combinations

                for value in product:
                    connection = Connection(n, n.inputTypes).applyInputs(value)
                    combinations = []
                    
                    for inputType in connection.inputTypes():
                        possibleConnections = self.valuesForType(self.typedVariableNeurons, inputType)
                        combinations.append([n.name for n in possibleConnections])

                    if (not combinations):
                        continue

                    op = lambda x, self = self, connection = connection: connection.output([self.variableNeurons[n].function() for n in x])

                    try:
                        result = bayesian_optimization_discrete(op, target, combinations, self.heuristicFunction, n_init = self.bo_n_init, top_k = self.bo_top_k, count_max = self.bo_count_max)
                        s = connection.toStr()
                        self.connections[s] = tuple([connection] + list(result))
                        addedConnections[s] = connection

                        if (not result[1]):
                            return self.connections[s]

                        heapq.heappush(frontier, (result[1], len(s), s))
                    except Exception:
                        pass

                    del combinations

            return None

        result = explore()

        if (result):
            return result

        while (frontier):
            cost, length, name = heapq.heappop(frontier)
            #print("name", name) #TODO: to remove
            if (not cost):
                break

            connection = addedConnections[name]
            del addedConnections[name]

            if (connection.neuron.outputType is Any):
                for v in self.typedConnections.values():
                    v.append(connection)
            elif (connection.neuron.outputType is typing.Container):
                for k, v in self.typedConnections.items():
                    if (is_container_type(k)):
                        v.append(connection)
            elif (connection.neuron.outputType is typing.Container[typing.Container]):
                for k, v in self.typedConnections.items():
                    if (is_container_of_container(k)):
                        v.append(connection)
            elif (get_origin(connection.neuron.outputType) is Union):
                for arg in get_args(connection.neuron.outputType):
                    self.typedConnections[arg].append(connection)
            else:
                self.typedConnections[connection.neuron.outputType].append(connection)

            result = explore()

            if (result):
                return result

        return self.connections[name]

    def addVariableNeuron(self, neuron: Neuron, name: str = None):
        if (not name):
            name = neuron.name

        self.variableNeurons[name] = neuron
        self.typedVariableNeurons[neuron.outputType].append(neuron)

    def addPrimitiveNeuron(self, neuron: Neuron, name: str = None):
        if (not name):
            name = neuron.name

        self.primitiveNeurons[name] = neuron
        self.typedPrimitiveNeurons[neuron.outputType].append(neuron)

def sortedNamedNeurons(neurons: dict) -> dict:
    result: dict = defaultdict(list)

    for k, v in neurons.items():
        result[k] += [x.name for x in v]

    for k, v in result.items():
        result[k] = sorted(v)    

    return result

if (__name__ == "__main__"):
    seed = 0
    np.random.seed(seed)
    random.seed(seed)

    engine: Engine = Engine()

    def printNeuron(neuron: Neuron, args: list):
        print(f"name: {neuron.name}, type: {neuron.outputType}, output: {neuron.function(*args)}")

    #printNeuron(engine.variableNeurons[0], [])
    #print(engine.typedVariableNeurons)
    #print(sortedNamedNeurons(engine.typedVariableNeurons))

    #printNeuron(engine.primitiveNeurons[0], ["a"])
    #print(engine.sortedPrimitiveNeurons)
    #print(engine.typedPrimitiveNeurons)
    #print(sortedNamedNeurons(engine.sortedPrimitiveNeurons))
    #print(sortedNamedNeurons(engine.typedPrimitiveNeurons))
