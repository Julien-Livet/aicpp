from collections import defaultdict
from neuron import Neuron
from dsl_ga import TypeSystem

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

        for neuron in self.primitiveNeurons:
            self.sortedPrimitiveNeurons[len(neuron.inputTypes)].append(neuron)

if (__name__ == "__main__"):
    engine = Engine()

    """
    neuron = engine.variableNeurons[0]
    print(neuron.name)
    print(neuron.outputType)
    print(neuron.function())
    """
    
    #print(engine.sortedVariableNeurons)

    """
    neuron = engine.primitiveNeurons[0]
    print(neuron.name)
    print(neuron.inputTypes)
    print(neuron.outputType)
    print(neuron.function("a"))
    """

    #print(engine.sortedPrimitiveNeurons)
