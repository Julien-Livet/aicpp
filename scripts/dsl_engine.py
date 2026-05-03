from collections import defaultdict
from connection import Connection
from dsl_ga import TypeSystem
from neuron import Neuron
from typing import get_args, get_origin, Union

class Engine:
    def __init__(self):
        self.typeSystem = TypeSystem()
        self.variableNeurons = []

        for k, v in self.typeSystem.dslVariableValues.items():    
            neuron = Neuron(k, lambda v = v: v, [], self.typeSystem.dslVariables[k])
            self.variableNeurons.append(neuron)

        self.sortedVariableNeurons = defaultdict(list)

        for neuron in self.variableNeurons:
            self.sortedVariableNeurons[neuron.outputType].append(neuron)

        for k, v in self.sortedVariableNeurons.items():
            self.sortedVariableNeurons[k] = sorted(v, key = lambda x: x.name)

        import test_arc

        arc_types_module = test_arc.load_module("arc_types", "arc-dsl/arc_types.py")

        with open("arc-dsl/dsl.py", "r") as f:
            content = f.read()

        namespace = {}
        namespace.update(vars(arc_types_module))

        exec(content, namespace)

        self.primitiveNeurons = []

        for k, v in self.typeSystem.dslPrimitives.items():
            neuron = Neuron(k, namespace[k], [x["type"] for x in v["args"]], v["return_type"])
            self.primitiveNeurons.append(neuron)

        self.sortedPrimitiveNeurons = defaultdict(list)
        self.typedPrimitiveNeurons = defaultdict(list)

        for neuron in self.primitiveNeurons:
            self.sortedPrimitiveNeurons[len(neuron.inputTypes)].append(neuron)

            if (get_origin(neuron.outputType) is Union):
                for arg in get_args(neuron.outputType):
                    self.typedPrimitiveNeurons[arg].append(neuron)
            else:
                self.typedPrimitiveNeurons[neuron.outputType].append(neuron)

def sortedNamedNeurons(neurons: dict) -> dict:
    result = defaultdict(list)

    for k, v in neurons.items():
        result[k] += [x.name for x in v]

    for k, v in result.items():
        result[k] = sorted(v)    

    return result

if (__name__ == "__main__"):
    engine = Engine()
    
    def printNeuron(neuron: Neuron, args: list = []):
        print(neuron.name, neuron.outputType, neuron.function(*args))

    #printNeuron(engine.variableNeurons[0])
    #print(engine.sortedVariableNeurons)
    #print(sortedNamedNeurons(engine.sortedVariableNeurons))

    #printNeuron(engine.primitiveNeurons[0], ["a"])
    #print(engine.sortedPrimitiveNeurons)
    #print(engine.typedPrimitiveNeurons)
    #print(sortedNamedNeurons(engine.sortedPrimitiveNeurons))
    #print(sortedNamedNeurons(engine.typedPrimitiveNeurons))
