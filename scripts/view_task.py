import json
from matplotlib import colors
import matplotlib.pyplot as plt
import numpy as np
import sys
import urllib.request

arc_colors = [
    '#000000', '#0074D9', '#FF4136', '#2ECC40', '#FFDC00',
    '#AAAAAA', '#F012BE', '#FF851B', '#7FDBFF', '#870C25'
]
cmap_arc = colors.ListedColormap(arc_colors)
norm_arc = colors.BoundaryNorm(np.arange(-0.5, 10, 1), cmap_arc.N)

def neg_arc_color(i: int):
    hex_color = arc_colors[i].lstrip('#')

    r = int(hex_color[0:2], 16)
    g = int(hex_color[2:4], 16)
    b = int(hex_color[4:6], 16)

    r_neg = 255 - r
    g_neg = 255 - g
    b_neg = 255 - b

    return f"#{r_neg:02X}{g_neg:02X}{b_neg:02X}"

def show(text, pairs):
    fig, axs = plt.subplots(len(pairs), 2)

    if (len(axs.shape) == 1):
        axs.resize((1, axs.shape[0]))

    fig.suptitle(text + ' input/output pairs')

    def plot_data(ax, data):
        ax.set_xticks([])
        ax.set_yticks([])
        im = ax.matshow(data, cmap = cmap_arc, norm = norm_arc)
        cbar = plt.colorbar(im, ax = ax, ticks = np.arange(0, 10))
        cbar.ax.set_yticklabels(np.arange(0, 10)) 
        cbar.outline.set_edgecolor('black')

        for (i, j), z in np.ndenumerate(data):
            ax.text(j, i, f'{z}', c = neg_arc_color(z), ha = 'center', va = 'center', size = "x-small")#, bbox = dict(boxstyle = 'round', facecolor = 'white', edgecolor = '0.3'))

        #ax.set_axis_off()
        rows, cols = np.array(data).shape
        ax.set_xticks(np.arange(-0.5, cols, 1), minor = True)
        ax.set_yticks(np.arange(-0.5, rows, 1), minor = True)
        ax.grid(which = 'minor', color = 'white', linestyle = '-', linewidth = 1)
        ax.tick_params(which = 'both', bottom = False, left = False, labelbottom = False, labelleft = False)

    for k in range(0, len(pairs)):
        plot_data(axs[k][0], pairs[k]["input"])
        plot_data(axs[k][1], pairs[k]["output"])

    mng = plt.get_current_fig_manager()
    mng.resize(*mng.window.maxsize())
    plt.show()

def view(folder: str, task: str):
    assert(folder in ("training", "evaluation"))

    url = urllib.request.urlopen(f"https://raw.githubusercontent.com/arcprize/ARC-AGI-2/refs/heads/main/data/{folder}/{task}.json")
    data = json.loads(url.read().decode())

    train = data["train"]
    test = data["test"]

    show("Train", train)
    show("Test", test)

if (__name__ == "__main__"):
    view(sys.argv[-2], sys.argv[-1])

