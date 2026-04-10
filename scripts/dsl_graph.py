from collections import defaultdict
import dsl_ast
from graphviz import Digraph
import math
import networkx as nx
from networkx.algorithms import community
import plotly.graph_objects as go
import sys

def build_graphviz(edge_weights, node_counts):
    dot = Digraph(engine = "sfdp", format = "svg")

    # nodes
    for node, count in node_counts.items():
        dot.node(node, label = f"{node}\n({count})", shape = "box")

    # edges
    for (src, dst), w in edge_weights.items():
        dot.edge(src, dst, penwidth = str(1 + math.log(1 + w)))

    return dot

edge_weights = defaultdict(int)
node_counts = defaultdict(int)

def traverse(node):
    node_counts[node.op] += 1

    for child in node.args:
        edge = (node.op, child.op)
        edge_weights[edge] += 1
        traverse(child)

def plot_3d_graph(G, pos):
    edge_x, edge_y, edge_z = [], [], []
    widths = []

    for u, v, data in G.edges(data = True):
        x0, y0, z0 = pos[u]
        x1, y1, z1 = pos[v]

        edge_x += [x0, x1, None]
        edge_y += [y0, y1, None]
        edge_z += [z0, z1, None]

        widths.append(data["weight"])

    edge_trace = go.Scatter3d(
        x = edge_x,
        y = edge_y,
        z = edge_z,
        mode = 'lines',
        line = dict(
            width = 2,
            color = 'blue'
        ),
        hoverinfo = 'none'
    )

    node_x, node_y, node_z = [], [], []
    texts = []

    for node in G.nodes():
        x, y, z = pos[node]
        node_x.append(x)
        node_y.append(y)
        node_z.append(z)
        texts.append(node)

    node_trace = go.Scatter3d(
        x = node_x,
        y = node_y,
        z = node_z,
        mode = 'markers+text',
        text = texts,
        textposition = "top center",
        marker = dict(size = 5, color = 'red'),
        hoverinfo = 'text'
    )

    fig = go.Figure(
        data = edge_traces + [node_trace]
    )

    fig.update_layout(
        title = "ARC DSL Graph 3D",
        showlegend = False,
        margin = dict(l = 0, r = 0, b = 0, t = 40)
    )

    fig.show()

if (__name__ == "__main__"):
    all_asts = {}

    for task in dsl_ast.hodelTasks():
        e, t, n = dsl_ast.taskAst(task)
        all_asts[task] = n

    if ("2d" in sys.argv):
        for task, ast in all_asts.items():
            traverse(ast)

        dot = build_graphviz(edge_weights, node_counts)

        print(len(edge_weights), "edges")
        print(len(node_counts), "nodes")

        G = nx.DiGraph()

        for node, count in node_counts.items():
            G.add_node(node, weight = count)

        for (src, dst), w in edge_weights.items():
            G.add_edge(src, dst, weight = w)

        communities = community.greedy_modularity_communities(G)

        for i, comm in enumerate(communities):
            for node in comm:
                dot.node(node, color = f"/set19/{i+1}")

        dot.attr(rankdir = "LR")  # left → right
        dot.attr(dpi = "600")
        dot.attr(overlap = "false")
        dot.attr(K = "0.6")
        dot.render("dsl_graph", view = True)

    if ("3d" in sys.argv):
        G = nx.DiGraph()
        node_types = {}

        def traverse_types(node):
            node_types[node.op] = node.type

            for child in node.args:
                G.add_edge(node.op, child.op, weight = G.get_edge_data(node.op, child.op, default = {"weight" : 0})["weight"] + 1)
                traverse_types(child)

        for task, ast in all_asts.items():
            traverse_types(ast)

        pos = nx.spring_layout(G, dim = 3, seed = 42)
        
        edge_traces = []

        for u, v, data in G.edges(data = True):
            x0, y0, z0 = pos[u]
            x1, y1, z1 = pos[v]

            w = data["weight"]

            edge_traces.append(
                go.Scatter3d(
                    x=[x0, x1],
                    y=[y0, y1],
                    z=[z0, z1],
                    mode = 'lines',
                    line = dict(
                        width = 1 + math.log(1 + w),
                        color = 'blue'
                    ),
                    hoverinfo = 'text',
                    text = [f"{u} → {v} ({w})"]
                )
            )

        node_x, node_y, node_z = [], [], []
        texts = []

        for node in G.nodes():
            x, y, z = pos[node]

            node_x.append(x)
            node_y.append(y)
            node_z.append(z)

            node_type = node_types.get(node, "?")

            label = f"{node}:{node_type}"
            texts.append(label)

        plot_3d_graph(G, pos)
