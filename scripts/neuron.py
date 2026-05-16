from typing import Callable

class Neuron:
    def __init__(self, name: str, function: Callable[..., object], inputTypes: tuple[type], outputType: type, subgoal: Callable[type, ..., object] = None):
        self.name = name
        self.function = function
        self.inputTypes = inputTypes
        self.outputType = outputType
        self.subgoal = subgoal

    def dot(self, index: int = 0):
        s = ""
        startIndex = index

        for i in range(0, len(self.inputTypes)):
            s += "n" + str(index) + ' [label="' + str(self.inputTypes[i]).replace("<class '", "").replace("'>", "") + '", shape=circle, style=fill];\n'
            s += "n" + str(index) + " -> n" + str(startIndex + len(self.inputTypes)) + ";\n"
            index += 1

        s += "n" + str(index) + ' [label="' + self.name + '", shape=circle, style=fill];\n'
        index += 1

        s += "n" + str(index) + ' [label="' + str(self.outputType).replace("<class '", "").replace("'>", "") + '", shape=circle, style=fill];\n'
        s += "n" + str(startIndex + len(self.inputTypes)) + " -> n" + str(index) + ";\n"
        index += 1

        return s, index

    def __eq__(self, other):
        if (isinstance(other, Neuron)):
            return self.name == other.name and self.inputTypes == other.inputTypes and self.outputType == other.outputType

        return False

    def __hash__(self):
        return hash(self.name) + sum([hash(x) for x in self.inputTypes]) + hash(self.outputType)

