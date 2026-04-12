from collections import defaultdict
from dash import Dash, dcc, html, Input, Output
import dsl_ast
from graphviz import Digraph
import math
import networkx as nx
from networkx.algorithms import community
import plotly.graph_objects as go
import random
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

def edgeNodeTraces(G, pos, node_types):
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
        label = f"{node}:{node_types.get(node, '')}"
        texts.append(label)

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

    return edge_trace, node_trace

def plot_3d_graph(G, pos, node_types):
    edge_trace, node_trace = edgeNodeTraces(G, pos, node_types)

    fig = go.Figure(
        data = [edge_trace, node_trace]
    )

    fig.update_layout(
        title = "ARC DSL Graph 3D",
        showlegend = False,
        margin = dict(l = 0, r = 0, b = 0, t = 40)
    )

    fig.show()

def compute_grid_3d_layout(nodes, node_types):
    nodes = sorted(nodes, key = lambda n: (node_types.get(n, ""), n))

    n = len(nodes)
    k = math.ceil(n ** (1 / 3))

    pos = {}

    for idx, node in enumerate(nodes):
        x = idx % k
        y = (idx // k) % k
        z = idx // (k * k)

        pos[node] = (x, y, z)

    return pos

def normalize_pos(pos):
    xs = [p[0] for p in pos.values()]
    ys = [p[1] for p in pos.values()]
    zs = [p[2] for p in pos.values()]

    def norm(v, vmin, vmax):
        return (v - vmin) / (vmax - vmin + 1e-9)

    return {
        k: (
            norm(x, min(xs), max(xs)),
            norm(y, min(ys), max(ys)),
            norm(z, min(zs), max(zs))
        )
        for k, (x, y, z) in pos.items()
    }

def jitter(pos, scale=0.1):
    return {
        k: (
            x + random.uniform(-scale, scale),
            y + random.uniform(-scale, scale),
            z + random.uniform(-scale, scale)
        )
        for k, (x, y, z) in pos.items()
    }

def build_figure(G, pos, highlight_node = None):
    edge_traces = []
        
    for u, v, data in G.edges(data = True):
        x0, y0, z0 = pos[u]
        x1, y1, z1 = pos[v]

        if (highlight_node and (u == highlight_node or v == highlight_node)):
            color = "red"
            width = 5
        else:
            color = "rgba(0,0,255,0.1)"
            width = 1

        edge_traces.append(
            go.Scatter3d(
                x = [x0, x1],
                y = [y0, y1],
                z = [z0, z1],
                mode = "lines",
                line = dict(color = color, width = width),
                hoverinfo = "text",
                text = [f"{u} → {v}"]
            )
        )

    node_x, node_y, node_z = [], [], []
    texts = []

    for node in G.nodes():
        x, y, z = pos[node]
        node_x.append(x)
        node_y.append(y)
        node_z.append(z)
        label = f"{node}:{node_types.get(node, '')}"
        texts.append(label)

    node_trace = go.Scatter3d(
        x = node_x,
        y = node_y,
        z = node_z,
        mode = "markers+text",
        text = texts,
        customdata = list(G.nodes()),
        textposition = "top center",
        marker = dict(size = 6, color = "black"),
        hoverinfo = "text"
    )

    fig = go.Figure(data = edge_traces + [node_trace])

    fig.update_layout(
        margin = dict(l = 0, r = 0, b = 0, t = 0),
        scene = dict(
            xaxis = dict(visible = False),
            yaxis = dict(visible = False),
            zaxis = dict(visible = False),
        )
    )

    return fig

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
        dot.render("hodel_dsl_graph", view = True)

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

        pos = compute_grid_3d_layout(G.nodes(), node_types)
        pos = normalize_pos(pos)
        #pos = jitter(pos)

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

        if ("plotly" in sys.argv):
            plot_3d_graph(G, pos, node_types)
        else:
            app = Dash(__name__)

            app.layout = html.Div([
                dcc.Graph(id = "graph", figure = build_figure(G, pos))
            ])

            @app.callback(
                Output("graph", "figure"),
                Input("graph", "hoverData")
            )
            def update_graph(hoverData):
                if (hoverData is None):
                    return build_figure(G, pos)

                point = hoverData["points"][0]

                if ("customdata" not in point):
                    return build_figure(G, pos)

                node = point["customdata"]

                return build_figure(G, pos, highlight_node = node)

            app.run(debug = True)
