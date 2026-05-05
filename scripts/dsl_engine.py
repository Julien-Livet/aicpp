from collections import defaultdict
from connection import compatibleType, Connection, is_container_of_container, is_container_type
import copy
from dsl_ga import TypeSystem
import heapq
import itertools
from neuron import Neuron
import math
import numpy as np
import random
from scipy.stats import norm
from sklearn.gaussian_process import GaussianProcessRegressor
from sklearn.gaussian_process.kernels import RBF, ConstantKernel
from sklearn.preprocessing import StandardScaler
import sympy
import textdistance
import typing
from typing import Any, Callable, get_args, get_origin, Union, Tuple

nameFunction = "" #TODO: to remove

def expected_improvement(mu, sigma, y_best, xi = 0.01):
    improvement = y_best - mu - xi
    Z = improvement / (sigma + 1e-9)
    ei = improvement * norm.cdf(Z) + sigma * norm.pdf(Z)
    ei[sigma <= 0] = 0

    return ei

_space_cache = {}

def _cached_heuristic(op, x, target):
    key = x

    if (key not in _space_cache):
        try:
            _space_cache[key] = heuristic(op(x), target)
        except Exception:
            _space_cache[key] = 999.0

    return _space_cache[key]

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

def encode_output_space_discrete(points: list, op: Callable, space: tuple, target: object) -> np.ndarray:
    result = []

    for point in points:
        try:
            v = _cached_heuristic(op, point, target)
            subresult = [v]

            for i, x in enumerate(point):
                values = list(filter(lambda value, i = i, x = x: value[i] == x, space))

                try:
                    neighbors = [heuristic(op(x), target) for x in values]
                    subresult += [np.mean(neighbors),
                                np.std(neighbors),
                                min(neighbors),
                                max(neighbors),
                                v - np.mean(neighbors)]
                except Exception:
                    pass

            result.append(subresult)
        except Exception:
            pass

    return np.array(result, dtype = float)

def bayesian_optimization_discrete(
    op: Callable,
    target: object,
    space: list,
    n_init: int = 5,
    top_k: int = 3,
    xi: float = 0.01,
) -> tuple[object, object]:
    obs_x = []
    obs_y = []
    s = set(space)

    while (len(obs_x) < n_init):
        x = random.choice(list(s))
        s.remove(x)

        try:
            obs_y.append(heuristic(target, op(x)))
            obs_x.append(x)
        except Exception:
            pass

    """
    #TODO: to remove
    if (nameFunction == "add"):
        for x, y in zip(obs_x, obs_y):
            print(x, y)
        input("lol")
    """

    X_space_enc = encode_output_space_discrete(space, op, space, target)
    scaler = StandardScaler().fit(X_space_enc)

    kernel = ConstantKernel(1.0) * RBF(length_scale = 1.0)
    gp = GaussianProcessRegressor(
        kernel = kernel, n_restarts_optimizer = 5,
        normalize_y = True, alpha = 1e-2,
    )

    count = 0
    previous_best_y = math.inf
    #iteration = 0 #TODO: to remove
    best_candidates = None

    while (True):
        X_enc = scaler.transform(encode_output_space_discrete(obs_x, op, space, target))
        Y = np.array(obs_y, dtype = float)
        gp.fit(X_enc, Y)

        obs_set = set(obs_x)
        unobserved = [x for x in space if x not in obs_set]

        if (not unobserved):
            break

        C_enc = scaler.transform(encode_output_space_discrete(unobserved, op, space, target))
        mu, sigma = gp.predict(C_enc, return_std = True)
        ei = expected_improvement(mu, sigma, np.min(Y), xi = xi)
        best_candidates = [unobserved[i] for i in np.argsort(-ei)[:top_k]]

        for x in best_candidates:
            try:
                obs_y.append(heuristic(target, op(x)))
                obs_x.append(x)
            except Exception:
                pass

        best_idx = np.argmin(obs_y)
        best_x, best_y = obs_x[best_idx], obs_y[best_idx]

        #print(f"[Iter {iteration+1:2d}] Best: x={best_x}, op={op(best_x):.2f}, heuristic={best_y:.4f}") #TODO: to remove

        if (best_y < previous_best_y):
            previous_best_y = best_y
            count = 0

        if (best_y == 0 or count > 10):
            break

        count += 1
        #iteration += 1 #TODO: to remove

    del X_space_enc
    del X_enc
    del Y
    del obs_x
    del obs_y
    del gp
    del unobserved
    del obs_set

    if (best_candidates):
        del best_candidates
 
    return best_x, best_y

class Engine:
    def __init__(self):
        self.typeSystem: TypeSystem = TypeSystem()
        self.variableNeurons: dict = dict()

        for k, v in self.typeSystem.dslVariableValues.items():    
            neuron: Neuron = Neuron(k, lambda v = v: v, [], self.typeSystem.dslVariables[k])
            self.variableNeurons[k] = neuron

        import test_arc

        arc_types_module = test_arc.load_module("arc_types", "arc-dsl/arc_types.py")

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

        self.primitiveNeurons = dict(sorted(self.primitiveNeurons.items(), key = lambda x: x[0]))
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

        for name, neuron in self.variableNeurons.items():
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

    def learn(self, target: object) -> tuple[Connection, object, object]:
        frontier = []

        def explore():
            addedConnections = []

            for k, n in self.primitiveNeurons.items():
                if (not compatibleType(type(target), n.outputType)):
                    continue
                #print(n.name) #TODO: to remove
                global nameFunction #TODO: to remove
                nameFunction = n.name #TODO: to remove
                combinations: list = []

                for inputType in n.inputTypes:
                    possibleConnections = self.valuesForType(self.typedConnections, inputType)
                    combinations.append([inputType] + possibleConnections)

                space = list(itertools.product(*combinations))

                if (not space):
                    continue

                newConnections = []
                #print(space) #TODO: to remove
                for value in space:
                    newConnections.append(Connection(n, n.inputTypes).applyInputs(value))
                #input("space") #TODO: to remove
                del combinations
                del space
                
                for connection in newConnections:
                    combinations = []
                    
                    for inputType in connection.inputTypes():
                        possibleConnections = self.valuesForType(self.typedVariableNeurons, inputType)
                        combinations.append([n.name for n in possibleConnections])

                    space = list(itertools.product(*combinations))

                    if (not space):
                        continue
                    #print(connection.toStr(), len(space)) #TODO: to remove
                    op = lambda x, self = self, connection = connection: connection.output([self.variableNeurons[n].function() for n in x])

                    try:
                        result = bayesian_optimization_discrete(op, target, space, 10, 5)
                        self.connections[connection.toStr()] = tuple([connection] + list(result))
                        addedConnections.append(connection)
                        #print(result) #TODO: to remove
                        if (not result[1]):
                            return self.connections[connection.toStr()]

                        heapq.heappush(frontier, (result[1], connection.toStr()))
                    except Exception:
                        pass

                    del combinations
                    del space
                #if (nameFunction == "add"): #TODO: to remove
                #    input("here")
                    
            for connection in addedConnections:
                if (get_origin(connection.neuron.outputType) is Union):
                    for arg in get_args(connection.neuron.outputType):
                        self.typedConnections[arg].append(connection)
                else:
                    self.typedConnections[connection.neuron.outputType].append(connection)

            return None

        result = explore()

        if (result):
            return result

        while (frontier):
            cost, name = heapq.heappop(frontier)

            if (not cost):
                break

            result = explore()

            if (result):
                return result

        return self.connections[name]
    
    def addVariableNeuron(self, neuron: Neuron):
        self.variableNeurons[neuron.name] = neuron
        self.typedVariableNeurons[neuron.outputType].append(neuron)

    def addPrimitiveNeuron(self, neuron: Neuron):
        self.primitiveNeurons[neuron.name] = neuron
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
