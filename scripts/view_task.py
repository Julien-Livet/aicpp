import json
import matplotlib.pyplot as plt
import numpy as np
import sys
import urllib.request

def show(text, pairs):
    fig, axs = plt.subplots(len(pairs), 2)

    if (len(axs.shape) == 1):
        axs.resize((1, axs.shape[0]))

    fig.suptitle(text + ' input/output pairs')

    for k in range(0, len(pairs)):
        ipt = pairs[k]["input"]
        opt = pairs[k]["output"]

        fig.colorbar(axs[k][0].matshow(ipt, vmin = 1, vmax = 9))

        for (i, j), z in np.ndenumerate(ipt):
            axs[k][0].text(j, i, f'{z}', ha='center', va='center')#, size = 'xx-small', bbox=dict(boxstyle='round', facecolor='white', edgecolor='0.3'))

        fig.colorbar(axs[k][1].matshow(opt, vmin = 1, vmax = 9))

        for (i, j), z in np.ndenumerate(opt):
            axs[k][1].text(j, i, f'{z}', ha='center', va='center')#, size = 'xx-small', bbox=dict(boxstyle='round', facecolor='white', edgecolor='0.3'))

        #axs[k][0].set_axis_off()
        #axs[k][1].set_axis_off()

        rows, cols = np.array(ipt).shape
        ax = axs[k][0]
        ax.set_xticks(np.arange(-0.5, cols, 1), minor=True)
        ax.set_yticks(np.arange(-0.5, rows, 1), minor=True)
        ax.grid(which = 'minor', color = 'black', linestyle = '-', linewidth = 1)
        ax.tick_params(which = 'both', bottom = False, left = False, labelbottom = False, labelleft = False)

        rows, cols = np.array(opt).shape
        ax = axs[k][1]
        ax.set_xticks(np.arange(-0.5, cols, 1), minor=True)
        ax.set_yticks(np.arange(-0.5, rows, 1), minor=True)
        ax.grid(which = 'minor', color = 'black', linestyle = '-', linewidth = 1)
        ax.tick_params(which = 'both', bottom = False, left = False, labelbottom = False, labelleft = False)

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

