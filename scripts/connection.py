import itertools
from neuron import Neuron
import typing
from typing import Any, Container, get_args, get_origin, Union

def is_container_type(tp):
    origin = get_origin(tp)

    return origin in (list, tuple, set, frozenset)

def is_container_of_container(tp):
    origin = get_origin(tp)

    if (origin is None):
        return False

    if (not issubclass(origin, Container)):
        return False

    args = get_args(tp)

    if (not args):
        return False

    inner = args[0]
    inner_origin = get_origin(inner) or inner

    return issubclass(inner_origin, Container)

def compatibleType(target: type, expected: type) -> bool:
    targetTypes = get_args(target) if get_origin(target) is Union else [target]
    expectedTypes = get_args(expected) if get_origin(expected) is Union else [expected]

    product = list(itertools.product(targetTypes, expectedTypes))

    if (len(product) == 1):
        if (expected == target):
            return True
        elif (get_origin(expected) is frozenset and get_origin(target) is frozenset and not get_args(expected)):
            return True
        elif (expected is Any or target is Any):
            return True
        elif (expected is typing.Container):
            if (is_container_type(target)):
                return True
        elif (expected is typing.Container[typing.Container]):
            if (is_container_of_container(target)):
                return True
        elif (target is typing.Container):
            return compatibleType(expected, target)
        elif (target is typing.Container[typing.Container]):
            return compatibleType(expected, target)
    else:
        for t, e in product:
            if (compatibleType(t, e)):
                return True
    
    return False

class Connection:
    def __init__(self, neuron: Neuron, inputs: list):
        self.neuron = neuron
        self.inputs = []

        for i in range(0, len(inputs)):
            if (isinstance(inputs[i], Connection)):
                self.inputs.append(inputs[i].copy())
            else:
                self.inputs.append(inputs[i])

    def __eq__(self, other):
        if (isinstance(other, Connection)):
            return self.neuron == other.neuron and self.inputs == other.inputs

        return False

    def __hash__(self):
        return hash(self.neuron) + sum([hash(x) for x in self.inputs])

    def dot(self, index: int = 0):
        s = ""
        startIndex = index

        s += "n" + str(index) + ' [label="' + self.neuron.name + '", shape=circle, style=fill];\n'
        nodeIndex = index
        index += 1

        for i in range(0, len(self.inputs)):
            input_ = self.inputs[i]

            if (isinstance(input_, Connection)):
                sTmp, index = input_.dot(index)
                s += "n" + str(index - 1) + " -> n" + str(nodeIndex) + ";\n"
                s += sTmp
            elif (isinstance(input_, Neuron)):
                sTmp, index = input_.dot(index)
                s += "n" + str(index - 1) + " -> n" + str(nodeIndex) + ";\n"
                s += sTmp
            else:
                s += "n" + str(index) + ' [label="' + str(input_).replace("<class '", "").replace("'>", "") + '", shape=circle, style=fill];\n'
                s += "n" + str(index) + " -> n" + str(nodeIndex) + ";\n"
                index += 1

        try:
            output = self.output()
        except:
            output = self.neuron.outputType

        s += "n" + str(index) + ' [label="' + str(output).replace("<class '", "").replace("'>", "") + '", shape=circle, style=fill];\n'
        s += "n" + str(nodeIndex) + " -> n" + str(index) + ";\n"
        index += 1

        return s, index

    def copy(self):
        return Connection(self.neuron, self.inputs)

    def applyInputs(self, inputs: list):
        index = 0

        for i in range(0, len(self.inputs)):
            input_ = self.inputs[i]

            if (isinstance(input_, Connection)):
                size = len(input_.inputTypes())
                input_.applyInputs(inputs[index:index + size])
                index += size
            else:
                if (index < len(inputs)):
                    if (isinstance(inputs[index], Connection)):
                        assert(compatibleType(inputs[index].neuron.outputType, self.neuron.inputTypes[i]))
                    elif (isinstance(inputs[index], Neuron)):
                        assert(compatibleType(inputs[index].outputType, self.neuron.inputTypes[i]))
                    elif (isinstance(inputs[index], type)):
                        if (inputs[index] == typing.Any):
                            pass
                        else:
                            assert(compatibleType(inputs[index], self.neuron.inputTypes[i]))
                    elif (typing.get_origin(inputs[index]) is not None):
                        assert(inputs[index] == self.neuron.inputTypes[i])

                    if (isinstance(inputs[index], Connection)):
                        self.inputs[i] = inputs[index].copy()
                    else:
                        self.inputs[i] = inputs[index]

                    index += 1

        return self
    
    def output(self, inputs: list = None):
        args = []
        index = 0

        for i in range(0, len(self.inputs)):
            input_ = self.inputs[i]

            if (isinstance(input_, Connection)):
                if (inputs == None):
                    args.append(input_.output())
                else:
                    size = len(input_.inputTypes())
                    args.append(input_.output(inputs[index:index + size]))
                    index += size
            else:
                if (inputs != None):
                    if (index < len(inputs)):
                        args.append(inputs[index])
                        index += 1
                elif (isinstance(input_, Neuron)):
                    args.append(input_.function())
                else:
                    args.append(input_)

        assert(len(args) == len(self.inputs))

        return self.neuron.function(*args)

    def inputTypes(self) -> list:
        types = []

        for input_ in self.inputs:
            if (isinstance(input_, Connection)):
                types.extend(input_.inputTypes())
            elif (isinstance(input_, Neuron)):
                types.extend(input_.inputTypes)
            elif (isinstance(input_, typing.GenericAlias)):
                types.append(input_)
            elif (isinstance(input_, type)):
                types.append(input_)
            elif (typing.get_origin(input_) is not None):
                types.append(input_)
            elif (input_ == typing.Any):
                types.append(input_)
            else:
                types.append(type(input_))

        return types

    def depth(self, d: int = 0) -> int:
        de = d

        for input_ in self.inputs:
            if (isinstance(input_, Connection)):
                de = max(de, input_.depth(d + 1))

        return de

    def cost(self) -> int:
        cost = 0

        for i in self.inputs:
            cost += 1

            if (type(i) is Connection):
                cost += i.cost()

        return cost

    def toStr(self) -> str:
        args = []

        for i in self.inputs:
            if (type(i) is Connection):
                args.append(i.toStr())
            elif (type(i) is Neuron):
                args.append(i.name)
            else:
                args.append(str(i))

        s = self.neuron.name

        if (len(self.neuron.inputTypes)):
            s += "(" + ", ".join(args) + ")"

        return s

    def __str__(self):
        return self.toStr()
