from collections import defaultdict
from collections.abc import Container
import dsl_transformer
import math
import random
import sys
import typing
from typing import Any, Callable, get_args, get_origin, Tuple, Union

Boolean = bool
Grid = Tuple[Tuple[int]]
Integer = int
IntegerTuple = Tuple[Integer, Integer]

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

class TypeSystem:
    def __init__(self):
        import test_arc

        arc_types_module = test_arc.load_module("arc_types", "arc-dsl/arc_types.py")

        with open("arc-dsl/constants.py", "r") as f:
            content = f.read()

        namespace = {}
        namespace.update(vars(arc_types_module))

        types = {}

        for k, v in namespace.items():
            if (not k.startswith("_")):
                types[v] = k

        from typing import Tuple

        Integer = int
        types[tuple] = Tuple[Integer, Integer]

        exec(content, namespace)

        variables = {}

        for k, v in namespace.items():
            if (not k in vars(arc_types_module)):
                variables[k] = types[type(v)]

        self.dslVariables = {"I": Grid}
        
        exec("import typing", namespace)

        for k, v in variables.items():
            exec(f"variable = {v}", namespace)
            self.dslVariables[k] = namespace["variable"]

        for i in range(10):
            self.dslVariables[str(i)] = Integer

        self.dslPrimitives = dsl_transformer.getDslPrimitives()

        for name in self.dslPrimitives.keys():
            self.dslVariables[name] = Callable

        self.variableTypes = defaultdict(list)

        for k, v in self.dslVariables.items():
            self.variableTypes[v].append(k)

        for k1, v1 in self.dslPrimitives.items():
            for arg in v1["args"]:
                exec(f"arg = {arg['type']}", namespace)
                arg["type"] = namespace["arg"]

            exec(f"arg = {v1['return_type']}", namespace)
            v1["return_type"] = namespace["arg"]

        self.primitiveTypes = defaultdict(list)

        for k, v in self.dslPrimitives.items():
            expected = v["return_type"]

            if (get_origin(expected) is Union):
                for arg in get_args(expected):
                    self.primitiveTypes[arg].append(k)
            else:
                self.primitiveTypes[expected].append(k)

        self.declinedPrimitives = {}

        for name in self.dslPrimitives.keys():
            self.declinedPrimitives[name] = self.declinedPrimitive(name)

        self.declinedPrimitives = dict(sorted(self.declinedPrimitives.items()))

    def declinedPrimitive(self, name: str) -> str:
        args = []
            
        for arg in self.dslPrimitives[name]["args"]:
            expected = arg["type"]
            result = self.variablesForType(expected)

            if (result):
                args.append(result[-1])
            else:
                result = []
                
                if (expected is typing.Container):
                    for k, v in self.primitiveTypes.items():
                        if (is_container_type(k)):
                            result += v
                elif (expected is typing.Container[typing.Container]):
                    for k, v in self.primitiveTypes.items():
                        if (is_container_of_container(k)):
                            result += v
                elif (get_origin(expected) is Union):
                    for arg in get_args(expected):
                        result += self.primitiveTypes[arg]
                else:
                    result = self.primitiveTypes[expected]
                
                if (result):
                    args.append(self.declinedPrimitive(result[-1]))
                else:
                    args.append(f"{expected}:unknown")

        return f"{name}({','.join(args)})"

    def variablesForType(self, expected: type) -> list:
        result = []

        if (expected is Any):
            for v in self.variableTypes.values():
                result += v
        elif (expected is typing.Container):
            for k, v in self.variableTypes.items():
                if (is_container_type(k)):
                    result += v
        elif (expected is typing.Container[typing.Container]):
            for k, v in self.variableTypes.items():
                if (is_container_of_container(k)):
                    result += v
        elif (get_origin(expected) is Union):
            for arg in get_args(expected):
                result += self.variableTypes[arg]
        else:
            result = self.variableTypes[expected]

        return result

def processTask(llm: tuple, folder: str, task: str):
    assert(folder in ("training", "evaluation"))

    import test_arc

    taskPairs = test_arc.trainTestPairs(folder, task)
    """
    import dsl_memory
    
    dsls = list(sorted(dsl_memory.load(f"data/{test_arc.llmPath(llm)}/dsl_memory.pkl"), key = lambda x: (len(x), x)))

    import view_dsl_graph

    expressions = set()

    for dsl in dsls:
        try:
            expressions.add(view_dsl_graph.programExpression(dsl))
        except Exception:
            pass
    """
    expressions = ['vconcat(switch(I,ONE,TWO),first(vsplit(switch(I,ONE,TWO),2)))',
                   'vconcat(switch(I,ONE,TWO),crop(switch(I,ONE,TWO),(uppermost(asobject(switch(I,ONE,TWO))),ZERO),(divide(add(subtract(lowermost(asobject(switch(I,ONE,TWO))),uppermost(asobject(switch(I,ONE,TWO)))),ONE),TWO),width(switch(I,ONE,TWO)))))',
                   'vconcat(canvas(7,shape(trim(I))),trim(I))',
                   'vconcat(switch(I,ONE,TWO),paint(canvas(ZERO,shape(switch(I,ONE,TWO))),intersection(asobject(switch(I,ONE,TWO)),asobject(vmirror(switch(I,ONE,TWO))))))',
                   'vupscale(I,2)',
                   'combine(I,hmirror(I))',
                   'vconcat(hmirror(I),I)',
                   'vconcat(I,hmirror(I))',
                   'vconcat(I,vmirror(rot180(I)))',
                   'vconcat(rot180(vmirror(I)),I)']

    results = []

    for expression in expressions:
        try:
            l = list(test_arc.taskResults(f"def dsl(I):\n    return {expression}", taskPairs[0], "train")) + [expression]
            results.append(tuple(l))
        except Exception:
            pass

    results = list(filter(lambda x: not math.isnan(x[0][test_arc.scoreColumns[-1]].sum(skipna = False)), results))

    def score(x):
        l = []

        for i in (0, 3, 2, 1):
            l.append(x[0][test_arc.scoreColumns[i]].sum(skipna = False))

        l.append(len(x[-1]))

        return tuple(l)

    results = sorted(results, key = score)
    topPrograms = [(x[-1], x[0]) for x in results[:10]]

    print("topPrograms", topPrograms)
    seed_expressions = [p[0] for p in topPrograms]

    print("\n--- Startig GA (refinement) ---")
    optimizer = GeneticOptimizer(ts, taskPairs, score)
    best_ast, final_score = optimizer.evolve(seed_expressions, generations = 15, pop_size = 30)

    print(f"\nFinal result GA:")
    print(f"Score: {final_score}")
    print(f"Program: {ast_to_expr(best_ast)}")

class Node:
    def __init__(self, name, children = None):
        self.name = name
        self.children = children or []

def get_typed_nodes(node: Node, ts: TypeSystem):
    """
    Walk tree and return tuple list (node, type, parent_node, index_in_parent).
    """
    nodes = []
    
    def walk(n, parent = None, idx = None):
        try:
            if (n.name in ts.dslVariables):
                t = ts.dslVariables[n.name]
            elif (n.name in ts.dslPrimitives):
                t = ts.dslPrimitives[n.name]["return_type"]
            else:
                t = Any
            
            nodes.append((n, t, parent, idx))

            for i, child in enumerate(n.children):
                walk(child, n, i)
        except Exception:
            pass

    walk(node)
 
    return nodes

import random

def crossover(parent1: Node, parent2: Node, ts: TypeSystem):
    child1 = copy_ast(parent1)
    child2 = copy_ast(parent2)
    
    nodes1 = get_typed_nodes(child1, ts)
    nodes2 = get_typed_nodes(child2, ts)
    
    random.shuffle(nodes1)
    
    for n1, t1, p1, i1 in nodes1:
        if (p1 is None):
            continue
        
        compatible_nodes = [x for x in nodes2 if x[1] == t1 and x[2] is not None]
        
        if (compatible_nodes):
            n2, t2, p2, i2 = random.choice(compatible_nodes)
            
            p1.children[i1], p2.children[i2] = p2.children[i2], p1.children[i1]

            return child1
            
    return child1

def parse_expression(expr: str) -> Node:
    expr = expr.strip()

    if ("(" not in expr):
        return Node(expr)

    name, rest = expr.split("(", 1)
    rest = rest[:-1]  # remove )

    args = []
    depth = 0
    current = ""

    for c in rest:
        if (c == "," and depth == 0):
            args.append(parse_expression(current))
            current = ""
        else:
            if (c == "("):
                depth += 1
            elif (c == ")"):
                depth -= 1

            current += c

    if (current):
        args.append(parse_expression(current))

    return Node(name, args)

def ast_to_expr(node: Node) -> str:
    if (not node.children):
        return node.name

    return f"{node.name}({','.join(ast_to_expr(c) for c in node.children)})"

def infer_type(ts: TypeSystem, node: Node) -> type:
    return ts.dslVariables[node.name]

def infer_function_type(ts: TypeSystem, node: Node) -> type:
    return ts.dslPrimitives[node.name]["return_type"]

def get_all_nodes(node: Node):
    nodes = [node]

    for child in node.children:
        nodes.extend(get_all_nodes(child))

    return nodes

def copy_ast(node: Node):
    return Node(node.name, [copy_ast(c) for c in node.children])

class GeneticOptimizer:
    def __init__(self, ts: TypeSystem, task_pairs, score_func):
        self.ts = ts
        self.task_pairs = task_pairs
        self.score_func = score_func
        self.gene_pool = {name: parse_expression(expr) 
                         for name, expr in ts.declinedPrimitives.items()}

    def evaluate(self, ast_node: Node):
        import test_arc

        prog_str = ast_to_expr(ast_node)
        
        try:
            res = test_arc.taskResults(f"def dsl(I):\n    return {prog_str}", self.task_pairs[0], "train")

            return self.score_func(list(res) + [prog_str])
        except Exception:
            return (float('inf'), float('inf'), float('inf'), float('inf'), len(prog_str))

    def get_node_type(self, node: Node):
        if (node.name in self.ts.dslVariables):
            return self.ts.dslVariables[node.name]

        if (node.name in self.ts.dslPrimitives):
            return self.ts.dslPrimitives[node.name]["return_type"]

        return Any

    def mutate(self, parent_ast: Node):
        child = copy_ast(parent_ast)
        all_nodes = get_all_nodes(child)
        target = random.choice(all_nodes)
        target_type = self.get_node_type(target)

        # Strategy 1: replace by an existant variable of same type
        valid_vars = self.ts.variablesForType(target_type)
        # Strategy 2: replace by a declined primitive (prebuilt AST)
        valid_prims = [self.gene_pool[p] for p in self.ts.primitiveTypes.get(target_type, [])]

        if (target_type is Callable and target.children):
            valid_vars = []

        options = valid_vars + valid_prims

        if (options):
            replacement = random.choice(options)

            if (isinstance(replacement, str)): # variable
                target.name = replacement
                target.children = []
            else: # primitive AST
                target.name = replacement.name
                target.children = [copy_ast(c) for c in replacement.children]
        
        return child

    def evolve(self, seeds, generations = 15, pop_size = 30):
        population = [parse_expression(p) for p in seeds]

        for gen in range(generations):
            scored = sorted([(p, self.evaluate(p)) for p in population], key = lambda x: x[1])
            best_fit = scored[0][1]
                
            if (sum(best_fit[:4]) == 0): # Perfect solution found
                return scored[0]

            # Elitism
            next_gen = [s[0] for s in scored[:5]]

            while (len(next_gen) < pop_size):
                # 70% crossover, 30% pure mutation
                if (random.random() < 0.7 and len(scored) > 1):
                    p1 = random.choice(scored[:10])[0]
                    p2 = random.choice(scored[:10])[0]
                    child = crossover(p1, p2, self.ts)

                    if (random.random() < 0.2):
                        child = self.mutate(child)
                else:
                    parent = random.choice(scored[:10])[0]
                    child = self.mutate(parent)
                
                next_gen.append(child)
            
            population = next_gen

        return scored[0]

if (__name__ == "__main__"):
    ts = TypeSystem()

    print("dslVariables", ts.dslVariables)
    print("variableTypes", ts.variableTypes)
    print("dslPrimitives", ts.dslPrimitives)
    print("primitiveTypes", ts.primitiveTypes)
    print("declinedPrimitives", ts.declinedPrimitives)

    processTask((sys.argv[-4], sys.argv[-3]), sys.argv[-2], sys.argv[-1])
