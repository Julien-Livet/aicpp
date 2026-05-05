import copy
import dsl_engine
import numpy as np
from neuron import Neuron
from typing import Tuple
import time

dslEngine: dsl_engine.Engine = dsl_engine.Engine()
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

def processTask(folder: str, task: str):
    import test_arc

    taskPairs = test_arc.trainTestPairs(folder, task)
    results = []
    
    for inp, out in taskPairs[0]:
        inputNeuron.function = lambda inp = inp: inp
        results.append(dslEngine.learn(out))

    sortedResults = []
    
    for result in results:
        c, args, cost = result
        totalCost: float = 0
        connection = copy.deepcopy(c).applyInputs([dslEngine.variableNeurons[n].function() for n in args])

        for inp, out in taskPairs[0]:
            inputNeuron.function = lambda inp = inp: inp
            output = connection.output()
            totalCost += dsl_engine.heuristic(output, out)

        sortedResults.append((totalCost, result))

    sortedResults = sorted(sortedResults, key = lambda x: x[0])
    testCost: float = 0
    trainCost, result = sortedResults[0]
    c, args, cost = result
    connection = copy.deepcopy(c).applyInputs([dslEngine.variableNeurons[n].function() for n in args])

    for inp, out in taskPairs[1]:
        inputNeuron.function = lambda inp = inp: inp
        output = connection.output()
        testCost += dsl_engine.heuristic(output, out)

    return (trainCost, testCost, connection.toStr())

def passTask(folder: str, task: str, debug: bool = False):
    trainCost, testCost, dsl = processTask(folder, task)

    if (debug):
        print(f"Train cost: {trainCost}, test cost: {testCost}, dsl: {dsl}")

    assert(not (trainCost + testCost))
"""
def test_task3c9b0459(): #Flip left/right and flip up/down
    passTask("training", "3c9b0459", True)
"""
