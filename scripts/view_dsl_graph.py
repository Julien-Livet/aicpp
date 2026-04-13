import ast
import hodel_dsl_graph
import imageio
import inspect
import networkx as nx
import os
import plotly.graph_objects as go
import re
import subprocess
import sys
import test_arc

def extract_signature(fn):
    sig = inspect.signature(fn)
    args = []

    for name, param in sig.parameters.items():
        args.append({
            "name": name,
            "type": param.annotation.__name__
        })

    ret_type = sig.return_annotation.__name__

    return {
        "args": args,
        "ret": ret_type
    }

class Node:
    def __init__(self, op, args = None, type = None, role = None):
        self.op = op
        self.args = args or []
        self.type = type
        self.role = role

    def __repr__(self):
        return f"{self.op}:{self.type}"

def convert(node, nodes: dict, constants: dict):
    if (isinstance(node, ast.Call)):
        if (isinstance(node.func, ast.Name)):
            op = node.func.id
            spec = nodes.get(op)
            children = [convert(a, nodes, constants) for a in node.args]

            if (spec):
                for child, arg_spec in zip(children, spec["args"]):
                    child.role = arg_spec["name"]
                    child.type = arg_spec["type"]

                return Node(
                    op = op,
                    args = children,
                    type = spec["ret"]
                )

            return Node(op, children)
        elif (isinstance(node.func, ast.Call)):
            func_node = convert(node.func, nodes, constants)
            children = [convert(a, nodes, constants) for a in node.args]

            return Node(
                op = "apply",
                args = [func_node] + children
            )
        else:
            raise NotImplementedError(
                f"Unsupported function type: {ast.dump(node.func)}"
            )
    elif (isinstance(node, ast.Name)):
        return Node(
            op = node.id,
            type = constants.get(node.id)
        )
    elif (isinstance(node, ast.Constant)):
        return Node(
            op = str(node.value),
            type = type(node.value).__name__
        )
    elif (isinstance(node, ast.Tuple)):
        return Node(
            op = "tuple",
            type = "tuple",
            args = [convert(elt, nodes, constants) for elt in node.elts]
        )
    else:
        raise NotImplementedError(type(node))

def allNodes():
    arc_types_module = test_arc.load_module("arc_types", "arc-dsl/arc_types.py")
    constants_module = test_arc.load_module("constants", "arc-dsl/constants.py")
    dsl_module = test_arc.load_module("dsl", "arc-dsl/dsl.py")

    namespace = {}
    namespace.update(vars(arc_types_module))
    namespace.update(vars(constants_module))
    namespace.update(vars(dsl_module))
    
    exec("", namespace)
    
    with open("arc-dsl/dsl.py", "r") as f:
        lines = f.read().split("\n")
        
    functions = []
    
    for line in lines:
        if (line.startswith("def ")):
            functions.append(line.split("def ")[1].split("(")[0])
    
    functions = sorted(functions)
    nodes = {}
    
    for function in functions:
        fn = namespace[function]
        signature = extract_signature(fn)
        nodes[function] = signature

    return nodes

def taskExpression(task: str):
    with open("arc-dsl/solvers.py", "r") as f:
        lines = f.read().split("\n")
        
    index = len(lines)
    
    for i, line in enumerate(lines):
        if (line.startswith("def solve_" + task)):
            index = i
            break

    taskLines = []
    
    for i in range(index + 1, len(lines)):
        line = lines[i]

        if (line.strip() == "return O"):
            break

        taskLines.append(line)

    if (len(taskLines) == 0):
        return ""

    taskLines = list(reversed(taskLines))
    var, expression = taskLines[0].split(" = ")

    for i in range(1, len(taskLines)):
        var, expr = taskLines[i].strip().split(" = ")
        expression = expression.replace(var, expr)

    return expression

def expressionTreeNode(expression: str):
    nodes = allNodes()

    with open("arc-dsl/constants.py", "r") as f:
        lines = f.read().split("\n")

    constants = {"I": "Grid"}

    for line in lines:
        if ("=" in line):
            key, value = line.split("=", 1)
            constants[key.strip()] = value.strip()

    tree = ast.parse(expression, mode = "eval")
    node = convert(tree.body, nodes, constants)

    return tree, node

def taskAst(task: str, png: bool = False):
    expression = taskExpression(task)

    tree, node = expressionTreeNode(expression)

    if (png):
        with open(f"{task}_tree.dot", "w") as f:
            f.write(to_dot(node))

        subprocess.run(["dot", "-Tpng", f"{task}_tree.dot", "-o", f"{task}_tree.png"])
    
    return expression, tree, node

def programExpression(program: str):
    lines = re.split(r'[\n;]+', program)
    programLines = []
    
    for i in range(1, len(lines)):
        line = lines[i]

        if (line.strip().startswith("return")):
            break

        if ("#" in line):
            line = line[:line.index("#")].strip()

        if (line.strip()):
            programLines.append(line)

    if (len(programLines) == 0):
        return ""

    programLines = list(reversed(programLines))
    programLine = programLines[0].strip()
    affectations = {}

    if ("=" in programLine):
        var, expr = programLine.strip().split(" = ")
        affectations[var] = expr.replace(" ", "")
        programLine = ""

    for i in range(1, len(programLines)):
        if ("=" in programLines[i]):
            programLine = programLines[i].strip() + programLine.strip()
        else:
            programLine = programLines[i].strip() + " " + programLine.strip()
            continue

        var, expr = programLine.strip().split(" = ")
        affectations[var] = expr.replace(" ", "")
        programLine = ""

    affectations = dict(reversed(list(affectations.items())))

    while (len(affectations) > 1):
        var, expr = list(affectations.items())[0]
        del affectations[var]

        for v, e in affectations.items():
            affectations[v] = e.replace(f"({var})", f"({expr})") \
                               .replace(f"({var},", f"({expr},") \
                               .replace(f",{var},", f",{expr},") \
                               .replace(f",{var})", f",{expr})") \
                               .replace(f",{var}(", f",{expr}(") \
                               .replace(f"({var}(", f"({expr}(")

            if (affectations[v].startswith(f"{var}(")):
                affectations[v] = affectations[v].replace(f"{var}(", f"{expr}(", 1)

    return list(affectations.values())[0]

def hodelPrograms():
    with open("arc-dsl/solvers.py", "r") as f:
        lines = f.read().split("\n")

    programs = []
    program = ""

    for line in lines:
        if (line.startswith("def ")):
            if (program):
                programs.append(program.strip())

            program = line + "\n"
        elif (not line):
            if (program):
                programs.append(program.strip())

            program = ""
        elif (program):
            program += line + "\n"

    return programs

def resultsPrograms(folder: str):
    assert(folder in ("training", "evaluation"))

    with open(f"{folder}_results.md", "r") as f:
        lines = f.read().split("\n")

    programs = []
    program = ""
    i = 0

    while (i < len(lines)):
        line = lines[i]
        values = line.split(" ")

        if (float(values[-1])):
            break

        i += 2

        while (i < len(lines)):
            line = lines[i]
 
            if (line.startswith("```")):
                if (program):
                    programs.append(program.strip())

                program = ""
                break
            else:
                program += line + "\n"

            i += 1

        i += 1

    return programs

node_types = {}

def traverse_types(G, node):
    node_types[node.op] = node.type

    for child in node.args:
        G.add_edge(node.op, child.op, weight = G.get_edge_data(node.op, child.op, default = {"weight" : 0})["weight"] + 1)
        traverse_types(G, child)

def programGraphs(programs: list):
    graphs = []
    G = nx.DiGraph()

    for program in programs:
        expression = programExpression(program)

        try:
            tree, node = expressionTreeNode(expression)
        except SyntaxError:
            continue

        traverse_types(G, node)

        graphs.append(G.copy())

    return graphs
    
def viewGraph(programs: list):
    graphs = programGraphs(programs)

    frames = []

    for i, G in enumerate(graphs):
        pos = hodel_dsl_graph.compute_grid_3d_layout(G.nodes(), node_types)
        edge_trace, node_trace = hodel_dsl_graph.edgeNodeTraces(G, pos, node_types)

        frames.append(go.Frame(
            data = [edge_trace, node_trace],
            name = str(i)
        ))

    fig = go.Figure(
        data = frames[0].data,
        frames = frames
    )

    fig.update_layout(
        updatemenus = [{
            "type": "buttons",
            "buttons": [
                {
                    "label": "Play",
                    "method": "animate",
                    "args": [None]
                }
            ]
        }]
    )

    fig.show()

    if ("gif" in sys.argv):
        folder = f"{sys.argv[-1]}_frames"

        os.makedirs(folder, exist_ok = True)

        for i, frame in enumerate(fig.frames):
            fig.update(data = frame.data)
            fig.write_image(f"{folder}/frame_{i:03d}.png")

        images = []

        for file in sorted(os.listdir(folder)):
            images.append(imageio.imread(os.path.join(folder, file)))

        imageio.mimsave(f"{sys.argv[-1]}_graph.gif", images, fps = 2)

if (__name__ == "__main__"):
    if (sys.argv[-1] == "hodel"):
        viewGraph(hodelPrograms())
    else:
        viewGraph(resultsPrograms(sys.argv[-1]))
