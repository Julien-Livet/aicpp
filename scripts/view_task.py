import json
import matplotlib.pyplot as plt
import sys
import urllib.request

def show(text, pairs):
    fig, axs = plt.subplots(len(pairs), 2)

    if (len(axs.shape) == 1):
        axs.resize((1, axs.shape[0]))

    fig.suptitle(text + ' input/output pairs')

    for i in range(0, len(pairs)):
        ipt = pairs[i]["input"]
        opt = pairs[i]["output"]

        fig.colorbar(axs[i][0].matshow(ipt))
        fig.colorbar(axs[i][1].matshow(opt))

        #axs[i][0].set_axis_off()
        #axs[i][1].set_axis_off()

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

