import dsl_ast
import hodel_dsl_graph
import networkx as nx
import plotly.graph_objects as go
import re
import sys

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
                               .replace(f",{var}(", f",{expr}(")

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
            tree, node = dsl_ast.expressionTreeNode(expression)
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

if (__name__ == "__main__"):
    if (sys.argv[-1] == "hodel"):
        viewGraph(hodelPrograms())
    else:
        viewGraph(resultsPrograms(sys.argv[-1]))
