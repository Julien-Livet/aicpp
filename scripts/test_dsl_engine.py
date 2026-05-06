from connection import Connection
import copy
import dsl_engine
import numpy as np
from neuron import Neuron
import test_arc
from typing import Tuple
import time

def arcHeuristic(x: tuple, y: tuple):
    x_ = np.array(x)
    y_ = np.array(y)

    return test_arc.size_cost(x_, y_) + test_arc.bounding_box_cost(x_, y_) + test_arc.pixel_overlap_cost(x_, y_) + test_arc.value_cost(x_, y_)

dslEngine: dsl_engine.Engine = dsl_engine.Engine(arcHeuristic)
Grid = Tuple[Tuple[int]]
I = np.random.randint(0, 10, (4, 4))
inputNeuron = Neuron("I", lambda I = I: I, [], Grid)
dslEngine.addVariableNeuron(inputNeuron)

def learnInt(engine: dsl_engine.Engine, expression: str):
    t = time.time()
    print(f"Target expression: {expression} = {eval(expression)}")
    c, args, cost = engine.learn(eval(expression))
    print("Found connection:", c.toStr())
    connnection = copy.deepcopy(c).applyInputs([engine.variableNeurons[n].function() for n in args])
    print("Applied connection:", connnection.toStr())
    print(f"Args: {args}, output: {connnection.output()}, cost: {cost}")
    print(f"Duration: {time.time() - t} s")

    assert(not cost)

def buildSimplifiedEngine(ops: set = {"add", "sub", "mul"}):
    engine: dsl_engine.Engine = dsl_engine.Engine()
    engine.variableNeurons.clear()
    engine.typedVariableNeurons.clear()
    
    for i in range(10):
        engine.addVariableNeuron(Neuron(str(i), lambda i = i: i, [], int))

    engine.primitiveNeurons.clear()
    engine.typedPrimitiveNeurons.clear()

    if ("add" in ops):
        engine.addPrimitiveNeuron(Neuron("add", lambda x, y: x + y, [int, int], int))

    if ("sub" in ops):
        engine.addPrimitiveNeuron(Neuron("sub", lambda x, y: x - y, [int, int], int))

    if ("mul" in ops):
        engine.addPrimitiveNeuron(Neuron("mul", lambda x, y: x * y, [int, int], int))

    return engine

def test_digit():
    engine = buildSimplifiedEngine()
    learnInt(engine, "5")

def test_one_addition():
    engine = buildSimplifiedEngine()
    learnInt(engine, "7 + 8")

def test_three_addition():
    engine = buildSimplifiedEngine({"add"})
    learnInt(engine, "5 + 7 + 8")

def test_simple_operation():
    engine = buildSimplifiedEngine({"add", "mul"})
    learnInt(engine, "5 + 7 * 8")

def test_operations():
    engine = buildSimplifiedEngine({"add", "mul"})
    learnInt(engine, "5")
    learnInt(engine, "7 + 8")
    learnInt(engine, "5 + 7 + 8")
    learnInt(engine, "5 + 7 * 8")

def test_three_levels():
    engine = buildSimplifiedEngine({"add", "mul", "sub"})
    learnInt(engine, "(3 + 4) * (8 - 2)")

def processTask(folder: str, task: str):
    taskPairs = test_arc.trainTestPairs(folder, task)
    results = []
    connection: Connection = None
    
    for inp, out in taskPairs[0]:
        inputNeuron.function = lambda inp = inp: inp
        process = True

        if (connection):
            output = connection.output()
            cost = dsl_engine.heuristic(output, out)
            process = cost

        if (process):
            result = dslEngine.learn(out, Grid)
            c, args, cost = result
            connnection = copy.deepcopy(c).applyInputs([dslEngine.variableNeurons[n].function() for n in args])

        results.append(result)

    sortedResults = []
    
    for result in results:
        totalCost: float = 0

        for inp, out in taskPairs[0]:
            inputNeuron.function = lambda inp = inp: inp
            c, args, cost = result
            connection = copy.deepcopy(c).applyInputs([dslEngine.variableNeurons[n].function() for n in args])
            output = connection.output()
            totalCost += dslEngine.heuristicFunction(output, out)

        sortedResults.append((totalCost, result))

    sortedResults = sorted(sortedResults, key = lambda x: x[0])
    testCost: float = 0
    trainCost, result = sortedResults[0]

    for inp, out in taskPairs[1]:
        inputNeuron.function = lambda inp = inp: inp
        c, args, cost = result
        connection = copy.deepcopy(c).applyInputs([dslEngine.variableNeurons[n].function() for n in args])
        output = connection.output()
        testCost += dslEngine.heuristicFunction(output, out)

    c, args, cost = result
    inputNeuron.function = lambda: "I"
    connection = copy.deepcopy(c).applyInputs([dslEngine.variableNeurons[n].function() for n in args])

    return (trainCost, testCost, connection.toStr())

def passTask(folder: str, task: str, debug: bool = False):
    trainCost, testCost, dsl = processTask(folder, task)

    if (debug):
        print(f"Train cost: {trainCost}, test cost: {testCost}, dsl: {dsl}")

    assert(not (trainCost + testCost))

def test_task3c9b0459(): #Flip left/right and flip up/down
    passTask("training", "3c9b0459", True)
