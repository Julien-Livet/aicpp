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

    import dsl_memory
    
    dsls = list(sorted(dsl_memory.load(f"data/{test_arc.llmPath(llm)}/dsl_memory.pkl"), key = lambda x: (len(x), x)))

    import view_dsl_graph

    expressions = set()

    for dsl in dsls:
        try:
            expressions.add(view_dsl_graph.programExpression(dsl))
        except Exception:
            pass

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

    #print("topPrograms", topPrograms)

    seed_expressions = [p[0] for p in topPrograms]

    ts = TypeSystem()

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
 
    nodes1 = get_typed_nodes(child1, ts)
    nodes2 = get_typed_nodes(copy_ast(parent2), ts)
 
    candidates1 = [(n, t, p, i) for n, t, p, i in nodes1 if p is not None]
    random.shuffle(candidates1)
 
    for n1, t1, p1, i1 in candidates1:
        compatible = [
            (n2, t2, p2, i2) for n2, t2, p2, i2 in nodes2
            if t2 == t1 and p2 is not None and ast_to_expr(n2) != ast_to_expr(n1)
        ]

        if (compatible):
            n2, t2, p2, i2 = random.choice(compatible)
            p1.children[i1] = copy_ast(n2)
            return child1
 
    return child1

def parse_expression(expr: str) -> Node:
    expr = expr.strip()
 
    if (not expr):
        return Node("I")
 
    if ("(" not in expr):
        return Node(expr)
 
    if (expr.startswith("(")):
        inner = expr[1:-1]
        args = _split_args(inner)

        return Node("_tuple", [parse_expression(a) for a in args])
 
    name_end = expr.index("(")
    name     = expr[:name_end]
    rest     = expr[name_end+1:-1]
 
    args = _split_args(rest)

    return Node(name, [parse_expression(a) for a in args]) 
 
def _split_args(s: str) -> list:
    args, depth, current = [], 0, ""

    for c in s:
        if (c == "," and depth == 0):
            if (current.strip()):
                args.append(current.strip())

            current = ""
        else:
            if (c in ("(", ))  : depth += 1
            elif (c in (")",)): depth -= 1

            current += c

    if (current.strip()):
        args.append(current.strip())

    return args

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

            return self.score_func((res[0], prog_str))
        except Exception:
            return (float('inf'), float('inf'), float('inf'), float('inf'), len(prog_str))

    def get_node_type(self, node: Node):
        if (node.name in self.ts.dslVariables):
            return self.ts.dslVariables[node.name]

        if (node.name in self.ts.dslPrimitives):
            return self.ts.dslPrimitives[node.name]["return_type"]

        return Any

    def mutate(self, parent_ast: Node) -> Node:
        Grid = Tuple[Tuple[int]]
        child    = copy_ast(parent_ast)
        all_nodes = get_all_nodes(child)
 
        target   = random.choice(all_nodes)
        t_type   = self.get_node_type(target)
        strategy = random.random()
 
        # A. Variable substitution (leaf)
        if strategy < 0.35 or not target.children:
            valid_vars = self.ts.variablesForType(t_type)
            if valid_vars:
                # Biais fort vers I quand le type est Grid
                if t_type == Grid and "I" in valid_vars:
                    weights = [5.0 if v == "I" else 1.0 for v in valid_vars]
                    total   = sum(weights)
                    r       = random.random() * total
                    cumul   = 0.0
                    chosen  = valid_vars[-1]
                    for v, w in zip(valid_vars, weights):
                        cumul += w
                        if r <= cumul:
                            chosen = v
                            break
                else:
                    chosen = random.choice(valid_vars)
                target.name     = chosen
                target.children = []
 
        # B. Primitive substitution
        elif (strategy < 0.65 and target.children):
            same_arity = [
                name for name, spec in self.ts.dslPrimitives.items()
                if (self.ts.dslPrimitives[name]["return_type"] == t_type
                    and len(spec["args"]) == len(target.children)
                    and name != target.name)
            ]
            if (same_arity):
                new_prim       = random.choice(same_arity)
                target.name    = new_prim
 
        # C. Elevation (simplification)
        elif (strategy < 0.80 and target.children):
            grid_children = [c for c in target.children
                             if self.get_node_type(c) == Grid]
            if grid_children and t_type == Grid:
                chosen_child   = random.choice(grid_children)
                target.name    = chosen_child.name
                target.children = chosen_child.children[:]
 
        # D. Winding (augmentation)
        else:
            wrappers = [
                name for name, spec in self.ts.dslPrimitives.items()
                if (spec["return_type"] == t_type
                    and len(spec["args"]) >= 1
                    and spec["args"][0]["type"] == t_type)
            ]

            if (wrappers):
                wrapper  = random.choice(wrappers)
                spec     = self.ts.dslPrimitives[wrapper]
                inner    = copy_ast(target)
                new_args = [inner]

                for arg_spec in spec["args"][1:]:
                    arg_type = arg_spec["type"]
                    opts     = self.ts.variablesForType(arg_type)
                    new_args.append(Node(random.choice(opts)) if opts
                                    else Node(self.gene_pool.get(
                                        self.ts.primitiveTypes.get(arg_type, ["I"])[0],
                                        parse_expression("I")).name))

                target.name     = wrapper
                target.children = new_args
 
        return child
 
    def _random_individual(self, max_depth: int = 4) -> Node:
        Grid = Tuple[Tuple[int]]
        grid_prims = [
            n for n, s in self.ts.dslPrimitives.items()
            if s["return_type"] == Grid
        ]

        if (not grid_prims):
            return parse_expression("I")
 
        def rand_node(expected_type, depth: int) -> Node:
            Grid = Tuple[Tuple[int]]
            vars_ok = self.ts.variablesForType(expected_type)
            prims_ok = [n for n, s in self.ts.dslPrimitives.items()
                        if s["return_type"] == expected_type]
 
            if (depth >= max_depth or not prims_ok):
                if (vars_ok):
                    if (expected_type == Grid and "I" in vars_ok):
                        return Node("I")

                    return Node(random.choice(vars_ok))

                return Node("I")
 
            use_prim = random.random() < (0.8 - depth * 0.15)

            if (not use_prim and vars_ok):
                if (expected_type == Grid and "I" in vars_ok):
                    return Node("I")

                return Node(random.choice(vars_ok))
 
            prim_name = random.choice(prims_ok)
            spec      = self.ts.dslPrimitives[prim_name]
            children  = [rand_node(arg["type"], depth + 1) for arg in spec["args"]]

            return Node(prim_name, children)
 
        return rand_node(Grid, 0)
 
    def evolve(
        self,
        seeds       : list,
        generations : int = 25,
        pop_size    : int = 40,
        elite_k     : int = 5,
        rand_inject : int = 5,
    ):
        population = [parse_expression(p) for p in seeds]

        while (len(population) < pop_size):
            population.append(self._random_individual())
 
        best_overall = None
        best_score   = (float("inf"),) * 5
 
        for gen in range(generations):
            scored = sorted(
                [(p, self.evaluate(p)) for p in population],
                key = lambda x: x[1],
            )
            gen_best_score = scored[0][1]
            gen_best_expr  = ast_to_expr(scored[0][0])
 
            if (gen_best_score < best_score):
                best_score   = gen_best_score
                best_overall = scored[0][0]
 
            print(f"  Gen {gen+1:3d}/{generations}"
                  f"  score={gen_best_score[:4]}"
                  f"  prog={gen_best_expr[:60]}")
 
            if (sum(s for s in gen_best_score[:4]) == 0):
                print("  ✓ Perfect solution found!")

                return best_overall, best_score
 
            # Elitism
            next_gen = [s[0] for s in scored[:elite_k]]
 
            for _ in range(rand_inject):
                next_gen.append(self._random_individual())
 
            while (len(next_gen) < pop_size):
                op = random.random()
 
                if op < 0.55 and len(scored) > 1:
                    p1    = random.choice(scored[:min(10, len(scored))])[0]
                    p2    = random.choice(scored[:min(10, len(scored))])[0]
                    child = crossover(p1, p2, self.ts)

                    if (random.random() < 0.25):
                        child = self.mutate(child)

                elif (op < 0.85):
                    parent = random.choice(scored[:min(10, len(scored))])[0]
                    child  = self.mutate(parent)
 
                else:
                    child = self._random_individual()
 
                next_gen.append(child)
 
            population = next_gen
 
        return best_overall, best_score

if (__name__ == "__main__"):
    """
    ts = TypeSystem()

    print("dslVariables", ts.dslVariables)
    print("variableTypes", ts.variableTypes)
    print("dslPrimitives", ts.dslPrimitives)
    print("primitiveTypes", ts.primitiveTypes)
    print("declinedPrimitives", ts.declinedPrimitives)
    """

    processTask((sys.argv[-4], sys.argv[-3]), sys.argv[-2], sys.argv[-1])
