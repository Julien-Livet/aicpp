from io import StringIO
import matplotlib.pyplot as plt
import numpy as np
import os
import pandas as pd
import sys

def plotTask(folder: str, task: str):
    assert(folder == "training" or folder == "evaluation")

    files = os.listdir(f"data/{folder}")
    inputFiles = sorted(filter(lambda x: "input" in x, files))
    #outputFiles = sorted(filter(lambda x: "output" in x, files))

    results = []
    programs = []

    for file in inputFiles:
        f = open(f"data/{folder}/{file}", "r")
        content = f.read()
        f.close()

        lines = content.split("\n")
        grid = []
        add = False

        for i in range(0, len(lines)):
            if (lines[i] == "Explosive scores:"):
                add = True
            elif (add):
                if (len(lines[i])):
                    grid.append(lines[i])
                else:
                    break
    
        grid = "\n".join(grid)
        results.append(pd.read_table(StringIO(grid), sep = ','))
        
        program = []
        add = False

        for i in range(0, len(lines)):
            if (lines[i] == "Current DSL program:"):
                add = True
            elif (add):
                if (lines[i] != "```"):
                    program.append(lines[i])
                else:
                    break

        program = "\n".join(program)
        programs.append(program)

    costs =  {}

    for result in results:
        for row in result.iterrows():
            label = row[1][result.columns[0]]
            d = costs.get(label, {})

            for index, val in list(row[1].items())[1:]:
                l = d.get(index, [])
                l.append(val)
                d[index] = l

            costs[label] = d

    
    totalCosts = {}
    
    for k, v in list(costs.values())[0].items():
        totalCosts[k] = np.array(v) * 0

    for value in list(costs.values())[1:]:
        for k, v in value.items():
            totalCosts[k] += v

    costs["total"] = totalCosts

    fig, ax = plt.subplots(nrows = len(costs) + 1, ncols = 1)

    for i, (k1, v1) in enumerate(costs.items()):
        for k2, v2 in v1.items():
            ax[i].plot(range(len(v2)), v2, label = k2)
            ax[i].set_title(k1)

    ax[-1].plot(range(len(programs)), [len(x.split("\n")) for x in programs], label = "Program lines")
    ax[-1].plot(range(len(programs)), np.log([len(x) for x in programs]), label = "Program length (log)")
    ax[-1].set_title("Programs")

    fig.suptitle(" ".join([folder, task, "results"]))
    plt.legend()
    mng = plt.get_current_fig_manager()
    mng.resize(*mng.window.maxsize())
    plt.show()

if (__name__ == "__main__"):
    plotTask(sys.argv[-2], sys.argv[-1])
