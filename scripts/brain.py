from connection import Connection
import copy
import itertools
import multiprocessing
from neuron import Neuron
import numpy as np
import sympy
import textdistance

eps = 1e-6

def _apply_connection(args):
    connection, params = args

    return connectionWorker(connection, params)

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
        v = np.array(val)
        t = np.array(target)

        if (v.shape != t.shape):
            return 100 + abs(np.sum(v) - np.sum(t))

        return np.linalg.norm(np.subtract(v, t))
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

class Pair:
    def __init__(self, value, cost, connectionCost, connectionId, connection):
        self.value = value
        self.cost = cost
        self.connectionCost = connectionCost
        self.connectionId = connectionId
        self.connection = connection

def connectionWorker(connection, args):
    c = connection.copy()
    c.applyInputs(args)

    return c

def worker(eps, connection, bestPair, g, target, processes, processId, connectionId):
    while (processes[processId]):
        try:
            a = next(g)
        except StopIteration:
            break

        c = connection.copy()
        c.applyInputs(a)
        value = c.output()
        cost = heuristic(value, target)

        if (cost < bestPair.cost + eps):
            processes[processId] = False

            return Pair(value, cost, connection.cost(), connectionId, c)

    return bestPair


class Brain:
    def __init__(self, neurons: list[Neuron]):
        self.neurons = neurons

    def neuronDot(self):
        dot = "digraph ConnectionTree {\n"
        dot += "node [shape=circle, style=filled, fillcolor=lightgray];\n"

        index = 0

        for neuron in self.neurons:
            s, index = neuron.dot(index)
            dot += s

        dot += "}\n"

        return dot

    def buildConnectionMapping(self, level: int = 3):
        connectionMapping, conns, connectionParameters = self.buildData(level)
        del connectionMapping

        from collections import defaultdict
        from pathos.multiprocessing import ProcessingPool as Pool

        appliedConnectionMapping = defaultdict(set)

        with Pool(nodes = multiprocessing.cpu_count()) as pool:
            for conn in conns:
                gen = connectionParameters.get(conn, None)

                if (gen is None):
                    continue

                results = pool.uimap(
                    _apply_connection,
                    ((conn, params) for params in gen)
                )

                for result in results:
                    if (result is None):
                        continue

                    appliedConnectionMapping[result.neuron.outputType].add(result)

        return appliedConnectionMapping

    def buildData(self, level: int):
        parameters = dict()
        connections = set()

        for neuron in self.neurons:
            if (len(neuron.inputTypes) == 0):
                l = parameters.get(neuron.outputType, [])
                l.append(Connection(neuron, []))
                parameters[neuron.outputType] = l
            else:
                connections.add(Connection(neuron, neuron.inputTypes))

        connectionMapping = {}

        for l in range(0, level):
            mapping = copy.deepcopy(connectionMapping)

            for connection in connections:
                s = mapping.get(connection.neuron.outputType, set())

                connectionInputTypes = connection.inputTypes()
                args = []

                for i in range(0, len(connectionInputTypes)):
                    args.append([connectionInputTypes[i]])

                for i in range(0, len(args)):
                    l = connectionMapping.get(connectionInputTypes[i], [])

                    for v in l:
                        args[i].append(v)

                product = list(itertools.product(*args))

                from pathos.multiprocessing import ProcessingPool as Pool

                with Pool(nodes = multiprocessing.cpu_count()) as p:
                    s |= set(p.map(connectionWorker, [connection] * len(product), product))

                mapping[connection.neuron.outputType] = s

            connectionMapping = mapping
            connections = []

            for k, v in connectionMapping.items():
                connections += v

            connections = set(connections)

        for neuron in self.neurons:
            if (len(neuron.inputTypes) == 0):
                connections.add(Connection(neuron, []))

        conns = sorted(list(connections), key = lambda x: x.cost())

        connectionParameters = dict()

        for i in range(0, len(conns)):
            connection = conns[i]
            connectionInputTypes = connection.inputTypes()

            args = []

            for inputType in connectionInputTypes:
                l = parameters.get(inputType, None)

                if (l == None):
                    break

                args.append(l)

            if (len(args) != len(connectionInputTypes)):
                continue

            connectionParameters[connection] = itertools.product(*args)

        return connectionMapping, conns, connectionParameters

    def learn(self, targets: list = [], targetTypes: list = None, level: int = 2, eps: float = 1e-6):
        if (targetTypes == None):
            targetTypes = []

            for t in targets:
                targetTypes.append(type(t))

        assert(len(targets) == len(targetTypes))

        connectionMapping, conns, connectionParameters = self.buildData(level)

        if (len(connectionParameters) == 0):
            return []

        from sortedcontainers import SortedKeyList

        sets = [SortedKeyList(key = lambda p: (p.cost, p.connectionCost))] * len(targets)
        args = dict()

        for i in range(0, len(conns)):
            g = connectionParameters.get(conns[i], None)

            if (g != None):
                try:
                    args[conns[i]] = next(g)
                except StopIteration:
                    args[conns[i]] = None

        for i in range(0, len(conns)):
            connection = conns[i]
            g = connectionParameters.get(conns[i], None)

            if (g == None):
                continue

            a = args[conns[i]]

            if (a == None):
                continue

            c = connection.copy()
            c.applyInputs(a)
            value = c.output()

            for j in range(0, len(targets)):
                sets[j].add(Pair(value, heuristic(value, targets[j]), connection.cost(), i, c))

        its = [0] * len(sets)
        finishedSets = np.array([False] * len(sets))
        futures = [[]] * len(its)
        processes = [True] * len(its)

        from concurrent.futures import ThreadPoolExecutor

        executor = ThreadPoolExecutor()

        while (np.any(np.logical_not(finishedSets))):
            for i in range(0, len(its)):
                futures[i] = []
                processes[i] = True

                if (its[i] == len(sets[i])):
                    finishedSets[i] = True
                    continue

                if (sets[i][its[i]].cost < eps):
                    finishedSets[i] = True
                    continue

                while (its[i] != len(sets[i])):
                    connectionId = sets[i][its[i]].connectionId
                    connection = conns[connectionId]
                    g = connectionParameters.get(connection, None)

                    if (g == None):
                        continue

                    futures[i].append(executor.submit(worker, eps, connection, sets[i][its[i]], g, targets[i], processes, i, connectionId))

                    its[i] += 1

            for i in range(0, len(its)):
                pairs = SortedKeyList(key = lambda p: (p.cost, p.connectionCost))

                if (len(futures[i])):
                    for f in futures[i]:
                        pairs.add(f.result())

                    if (len(pairs)):
                        if (sets[i] == pairs):
                            finishedSets[i] = True
                        else:
                            sets[i] = pairs
                            its[i] = 0

        learnedConnections = []

        for s in sets:
            if (len(s) == 0):
                return []

            it = 0
            solutions = [s[it].connection]
            it += 1

            while (it != len(s)):
                if (s[it].cost < s[0].cost + eps):
                    solutions.append(s[it].connection)
                else:
                    break

                it += 1

            solutions = sorted(solutions, key = lambda c: c.cost())

            learnedConnections.append(solutions[0])

        return learnedConnections

