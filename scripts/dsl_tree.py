import collections.abc
from connection import compatibleType
from dsl_engine import load_module, getDslPrimitives
from typing import Callable, get_args, get_origin, List, Dict, Tuple, Union

def dslVocabulary() -> Dict[str, Tuple[type, object]]:
    vocabulary: Dict[str, Tuple[type, object]] = {}

    arc_types_module = load_module("arc_types", "arc-dsl/arc_types.py")

    namespace = {}
    namespace.update(vars(arc_types_module))

    with open("arc-dsl/constants.py", "r") as f:
        content = f.read()

    namespace = {}
    namespace.update(vars(arc_types_module))

    exec(content, namespace)

    lines = content.split("\n")

    for line in lines:
        s = line.strip().replace(" ", "")

        if (not "=" in s):
            continue

        l1 = s.split(":")
        l2 = l1[1].split("=")
        
        vocabulary[l1[0]] = (namespace[l2[0]], namespace[l1[0]])

    with open("arc-dsl/dsl.py", "r") as f:
        content = f.read()

    exec(content, namespace)

    primitives = getDslPrimitives()

    for k, v in primitives.items():
        code = f"t = Callable[[{', '.join([x["type"] for x in v["args"]])}], {v["return_type"]}]"
        exec(code, namespace)
        vocabulary[k] = (namespace["t"], namespace[k])

    vocabulary["I"] = (Tuple[Tuple[int]], None)

    return vocabulary

vocabulary = dslVocabulary()

def args(target: type) -> List[str]:
    result: List[str] = []

    for k, v in vocabulary.items():
        t, val = v

        if (get_origin(t) is collections.abc.Callable):
            t = get_args(t)[1]

        if (compatibleType(target, t)):
            result.append(k)

    return sorted(result)

def root(name: str) -> Tuple[str, type, object]:
    return (name, *vocabulary[name])

class Tree:
    def __init__(self, root: Tuple[str, type, object], types: List[type]):
        self.root = root
        self.types = types
        self.args = list(types)

    def __str__(self):
        n, t, v = self.root
        s = str(n)

        if (get_origin(t) is collections.abc.Callable and self.types):
            arguments: list = []

            for i in range(len(self.args)):
                if (type(self.args[i]) is Tree and self.types[i] is Callable):
                    arguments.append(self.args[i].root[0])
                else:
                    arguments.append(self.args[i])

            s += f"({', '.join([str(a) for a in arguments])})"

        return s

    def isFinished(self) -> bool:
        for i in range(len(self.args)):
            if (type(self.args[i]) is Tree):
                if (not self.types[i] is Callable):
                    if (not self.args[i].isFinished()):
                        return False
            else:
                return False

        return True

    def nextType(self) -> type:
        for i in range(len(self.args)):
            if (type(self.args[i]) is Tree):
                if (not self.types[i] is Callable):
                    t = self.args[i].nextType()

                    if (t):
                        return t
            else:
                return self.args[i]

        return None

    def applyNextType(self, value: object) -> bool:
        for i in range(0, len(self.args)):
            if (type(self.args[i]) is Tree):
                if (not self.types[i] is Callable):
                    if (self.args[i].applyNextType(value)):
                        return True
            else:
                self.args[i] = value

                return True

        return False

    def eval(self):
        if (not self.args):
            return self.root[2]

        inputs = []

        for a in self.args:
            if (type(a) is Tree):
                inputs.append(a.eval())
            else:
                inputs.append(a)

        return self.root[2](*inputs)

def tree(name: str) -> Tree:
    t, v = vocabulary[name]

    return Tree(root(name), get_args(t)[0] if get_origin(t) is collections.abc.Callable else [])

if (__name__ == "__main__"):
    #print(vocabulary)

    import numpy as np
    import random

    seed = 0
    random.seed(seed)
    np.random.seed(seed)

    vocabulary["I"] = (Tuple[Tuple[int]], tuple(map(tuple, np.random.randint(0, 10, (3, 3)).tolist())))

    t = tree("fill")
    print(t, t.isFinished(), t.nextType())
    t.applyNextType(tree("I"))
    print(t, t.isFinished(), t.nextType())
    t1 = tree("mostcolor")
    t1.applyNextType(tree("I"))
    t.applyNextType(t1)
    print(t, t.isFinished(), t.nextType())
    t2 = tree("asobject")
    t2.applyNextType(tree("I"))
    t.applyNextType(t2)
    print(t, t.isFinished(), t.nextType())
    print(t.eval())

    depth = 0
    maxDepth = 0

    t = tree("fill")
    #print(t)

    while (not t.isFinished()):
        names = args(t.nextType())
        name = random.choice(names)
        tp, v = vocabulary[name]

        if (depth >= maxDepth):
            s = set()

            for n in names:
                tp, v = vocabulary[n]

                if (get_origin(tp) is collections.abc.Callable):
                    s.add(n)

            newNames = sorted(list(set(names) - s))

            if (newNames):
                names = newNames

            name = random.choice(names)
            depth = 0

        tp, v = vocabulary[name]
        
        if (not get_origin(t.nextType()) is collections.abc.Callable and get_origin(tp) is collections.abc.Callable):
            depth += 1

        t.applyNextType(Tree(root(name), []) if get_origin(t.nextType()) is collections.abc.Callable else tree(name))
        #print(t)

    print(t)
    print(t.eval())