import ast
import collections.abc
from connection import compatibleType
from dsl_engine import load_module, getDslPrimitives
from typing import get_args, get_origin, List, Dict, Tuple, Union

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
        code = f"t = Callable[[{str([x["type"] for x in v["args"]]).replace("'", "")}], {v["return_type"]}]"
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

    return result

def root(name: str) -> Tuple[str, type, object]:
    return (name, *vocabulary[name])

class Tree:
    def __init__(self, root: Tuple[str, type, object], args: List[Union[Tree, type]]):
        self.root = root
        self.args = args

    def __str__(self):
        n, t, v = self.root

        s = n

        if (get_origin(t) is collections.abc.Callable):
            s += f"({', '.join([str(a) for a in self.args])})"

        return s

if (__name__ == "__main__"):
    print(vocabulary)

    fillType, fillValue = vocabulary["fill"]
    fillArgs, fillReturn = get_args(fillType)
    mostcolorType, mostcolorValue = vocabulary["mostcolor"]
    mostcolorArgs, mostcolorReturn = get_args(mostcolorType)
    asobjectType, asobjectValue = vocabulary["asobject"]
    asobjectArgs, asobjectReturn = get_args(asobjectType)
    tree = Tree(root("fill"), fillArgs)
    tree.args[0] = Tree(root("I"), [])
    tree.args[1] = Tree(root("mostcolor"), [Tree(root("I"), [])])
    tree.args[2] = Tree(root("asobject"), [Tree(root("I"), [])])
    print(tree)
