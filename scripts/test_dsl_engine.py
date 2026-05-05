import copy
import dsl_engine
from neuron import Neuron

def learnInt(engine: dsl_engine.Engine, v: int):
    c, args, cost = engine.learn(v)
    print(c.toStr())
    connnection = copy.deepcopy(c).applyInputs([engine.variableNeurons[n].function() for n in args])
    print(connnection.toStr())
    print(args)
    print(connnection.output())
    print(cost)

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
    learnInt(engine, 5)

def test_one_addition():
    engine = buildSimplifiedEngine()
    learnInt(engine, 7 + 8)

def test_three_addition():
    engine = buildSimplifiedEngine({"add"})
    learnInt(engine, 5 + 7 + 8)
