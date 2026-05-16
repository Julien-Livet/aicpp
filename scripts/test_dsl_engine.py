from collections import defaultdict
from connection import Connection
import copy
import dsl_engine
import numpy as np
from neuron import Neuron
from typing import Tuple
import time

def arcHeuristic(x: tuple, y: tuple):
    x_ = np.array(x)
    y_ = np.array(y)

    return dsl_engine.size_cost(x_, y_) + dsl_engine.bounding_box_cost(x_, y_) + dsl_engine.pixel_overlap_cost(x_, y_) + dsl_engine.value_cost(x_, y_)

dslEngine: dsl_engine.Engine = dsl_engine.Engine(arcHeuristic)
Grid = Tuple[Tuple[int]]
I = np.random.randint(0, 10, (4, 4))
inputNeuron = Neuron("I", lambda I = I: I, [], Grid)
dslEngine.addVariableNeuron(inputNeuron)

def learnInt(engine: dsl_engine.Engine, expression: str, maxLevel: int = 3):
    t = time.time()
    print(f"Target expression: {expression} = {eval(expression)}")
    c, args, cost = engine.learn(eval(expression), maxLevel = maxLevel)
    print("Found connection:", c.toStr())
    connection = copy.deepcopy(c).applyInputs([engine.variableNeurons[n].function() for n in args])
    print("Applied connection:", connection.toStr())
    print(f"Args: {args}, output: {connection.output()}, cost: {cost}")
    print(f"Duration: {time.time() - t} s")

    assert(not cost)

def buildSimplifiedEngine(ops: set = {"add", "sub", "mul"}):
    engine: dsl_engine.Engine = dsl_engine.Engine()
    engine.clearVariableNeurons()
    
    for i in range(10):
        engine.addVariableNeuron(Neuron(str(i), lambda i = i: i, [], int))

    engine.clearPrimitiveNeurons()

    if ("add" in ops):
        engine.addPrimitiveNeuron(Neuron("add", lambda x, y: x + y, [int, int], int, lambda y, x: y - x))

    if ("sub" in ops):
        engine.addPrimitiveNeuron(Neuron("sub", lambda x, y: x - y, [int, int], int, lambda y, x: y + x))

    if ("mul" in ops):
        engine.addPrimitiveNeuron(Neuron("mul", lambda x, y: x * y, [int, int], int, lambda y, x: y / x))

    if ("neg" in ops):
        engine.addPrimitiveNeuron(Neuron("neg", lambda x: -x, [int], int))

    #if ("div" in ops):
    #    engine.addPrimitiveNeuron(Neuron("div", lambda x, y: x / y, [int, int], float, lambda y, x: y * x))

    return engine

def test_digit():
    engine = buildSimplifiedEngine()
    learnInt(engine, "5")

def test_one_addition():
    engine = buildSimplifiedEngine()
    learnInt(engine, "7 + 8")

def test_three_additions():
    engine = buildSimplifiedEngine({"add"})
    learnInt(engine, "5 + 7 + 8")

def test_simple_operation():
    engine = buildSimplifiedEngine({"add", "mul", "neg"})
    learnInt(engine, "5 + 7 * 8", maxLevel = 1)

def test_operations():
    engine = buildSimplifiedEngine({"add", "mul", "neg"})
    learnInt(engine, "5")
    learnInt(engine, "7 + 8")
    learnInt(engine, "5 + 7 + 8")
    learnInt(engine, "5 + 7 * 8", maxLevel = 1)

def test_three_levels():
    engine = buildSimplifiedEngine({"add", "mul", "sub"})
    learnInt(engine, "(3 + 4) * (8 - 2)")

def processTask(folder: str, task: str) -> tuple:
    taskPairs = dsl_engine.trainTestPairs(folder, task)
    results: list = []
    connection: Connection = None
    
    for inp, out in taskPairs[0]:
        inputNeuron.function = lambda inp = inp: tuple(map(tuple, inp))
        process = True

        if (connection):
            connectionTmp = copy.deepcopy(connection).applyInputs([dslEngine.variableNeurons[n].function() for n in args])
            output = connectionTmp.output()
            cost = dsl_engine.heuristic(output, tuple(map(tuple, out)))
            process = cost

        if (process):
            result = dslEngine.learn(out, Grid)
            c, args, cost = result
            connection = c

        results.append(result)

    sortedResults = []
    
    for result in results:
        totalCost: float = 0

        for inp, out in taskPairs[0]:
            inputNeuron.function = lambda inp = inp: tuple(map(tuple, inp))
            c, args, cost = result
            connection = copy.deepcopy(c).applyInputs([dslEngine.variableNeurons[n].function() for n in args])
            output = connection.output()
            totalCost += dslEngine.heuristicFunction(output, tuple(map(tuple, out)))

        sortedResults.append((totalCost, result))

    sortedResults = sorted(sortedResults, key = lambda x: x[0])
    testCost: float = 0
    trainCost, result = sortedResults[0]

    for inp, out in taskPairs[1]:
        inputNeuron.function = lambda inp = inp: tuple(map(tuple, inp))
        c, args, cost = result
        connection = copy.deepcopy(c).applyInputs([dslEngine.variableNeurons[n].function() for n in args])
        output = connection.output()
        testCost += dslEngine.heuristicFunction(output, tuple(map(tuple, out)))

    c, args, cost = result
    connection = copy.deepcopy(c).applyInputs(args)

    return (trainCost, testCost, connection.toStr())

def passTask(folder: str, task: str, debug: bool = False):
    trainCost, testCost, dsl = processTask(folder, task)

    if (debug):
        print(f"Train cost: {trainCost}, test cost: {testCost}, dsl: {dsl}")

    assert(not (trainCost + testCost))

def test_hodel_tasks():
    with open("arc-dsl/solvers.py", "r") as f:
        lines: list = f.read().split("\n")

    tasks: list = list(filter(lambda x: x.startswith("def solve_"), lines))
    tasks = [x[x.index("_")+1:x.index("(")] for x in tasks]
    tasksByStep: dict = defaultdict(list)

    for task in tasks:
        i = lines.index(f"def solve_{task}(I):") + 1
        count = 0

        while (i < len(lines) and not lines[i].startswith("def solve_")):
            if (lines[i].strip() and not lines[i].strip().startswith("return")):
                count += 1

            i += 1

        tasksByStep[count].append(task)

    for k, v in tasksByStep.items():
        if (k != 1):
            continue

        t1 = time.time()

        for task in v:
            print("training", task)
            t2 = time.time()
            passTask("training", task, True)
            print(f"Duration: {time.time() - t2} s")

        print(f"Duration for {k} step{'s' if k > 1 else ''} of DSL ({len(v)} tasks): {time.time() - t1} s")
"""
def test_task0d3d703e(): #Color mapping
    passTask("training", "0d3d703e", True)
"""