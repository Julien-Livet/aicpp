import difflib
from io import StringIO
import matplotlib.pyplot as plt
import numpy as np
import os
import pandas as pd
import sys

def diff(a: str, b: str):
    return "\n".join(difflib.unified_diff(
        a.splitlines(),
        b.splitlines(),
        lineterm = ""
    ))

def plotTask(folder: str, task: str):
    assert(folder in ("training", "evaluation"))

    files = os.listdir(f"data/{folder}")
    taskFiles = list(filter(lambda x: task in x, files))
    inputFiles = sorted(filter(lambda x: "input" in x, taskFiles))

    programs = []

    for file in inputFiles:
        f = open(f"data/{folder}/{file}", "r")
        content = f.read()
        f.close()

        lines = content.split("\n")
        index = 0
        programSet = []

        for i in range(0, 5):
            while (not lines[index].startswith("**Program")):
                index += 1

            while (lines[index] != "*DSL*"):
                index += 1

            index += 2
            program = []

            while (lines[index] != "```"):
                program.append(lines[index])
                index += 1

            program = "\n".join(program)

            while (lines[index] != "*Explosive scores*"):
                index += 1

            index += 2
            grid = []

            while (len(lines[index])):
                grid.append(lines[index])
                index += 1

            grid = "\n".join(grid)
            
            df = pd.read_table(StringIO(grid), sep="|", skiprows=[1])
            df = df.drop(columns = [col for col in df.columns if "Unnamed" in col])
            df.columns = df.columns.str.strip()
            df = df.apply(lambda x: x.str.strip() if x.dtype == "object" else x)
            df = df.set_index(df.columns[0]).astype(float)

            programSet.append((program, df))

        programs.append(programSet)

    history = []
    dfs = [None] * len(programs[0])

    for i in range(1, len(programs)):
        for j in range(0, len(programs[i])):
            dsl1, df1 = programs[i - 1][j]
            dsl2, df2 = programs[i][j]
            df1.index = df1.index.str.strip()
            df2.index = df2.index.str.strip()
            df1.columns = df1.columns.str.strip()
            df2.columns = df2.columns.str.strip()
            df1, df2 = df1.align(df2)
            df = df1.combine(df2, lambda s1, s2: s1.combine(s2, lambda x, y: f"{x if pd.notna(x) else 'NaN'},{y if pd.notna(y) else 'NaN'}"))

            if (dfs[j] is None):
                dfs[j] = df
            else:
                dfs[j] = dfs[j].combine(df2, lambda s1, s2: s1.combine(s2, lambda x, y: f"{x if pd.notna(x) else 'NaN'},{y if pd.notna(y) else 'NaN'}"))

            history.append((diff(dsl1, dsl2), df))

    content = ""
    
    for i in range(0, len(programs[0])):
        content += f"# Program {i+1}\n\n"

        content += f"## Scores\n\n"
        content += dfs[i].to_markdown() + "\n\n"

        for j in range(0, len(programs) - 1):            
            content += f"## Iteration {j+1} - DSL diff\n\n"
            content += f"```bash\n{history[i + j * len(programs[0])][0]}\n```\n\n"

    f = open(f"{folder}_{task}_history.md", "w")
    f.write(content)
    f.close()

    dsl, df = programs[0][0]
    costs = {}

    for row in df.iterrows():
        costs[row[0]] = []

        for program in programs[0]:
            d = {}

            for index, _ in list(row[1].items())[1:]:
                d[index] = []

            costs[row[0]].append(d)

    for programSet in programs:
        for i, program in enumerate(programSet):
            dsl, df = program

            for row in df.iterrows():
                label = row[0]
                d = costs[label][i]

                for index, val in list(row[1].items())[1:]:
                    l = d.get(index, [])
                    l.append(val)
                    d[index] = l

    fig, ax = plt.subplots(nrows = len(costs) + 1, ncols = len(programs[0]))

    for i, (name, programCost) in enumerate(costs.items()):
        for j, cost in enumerate(programCost):
            for key, value in cost.items():
                ax[i, j].plot(range(len(value)), value, label = key, marker='o')
                ax[i, j].set_title(" ".join([name, f"Program {j+1}"]))
                ax[i, j].legend(loc = "upper right")

    lines = {}
    length = {}

    for i in range(0, len(programs[0])):
        lines[i] = []
        length[i] = []

    for programSet in programs:
        for i, program in enumerate(programSet):
            lines[i].append(len(program[0].split("\n")))
            length[i].append(len(program[0]))

    for i in range(0, len(lines)):
        ax[-1, i].plot(range(len(lines[i])), lines[i], label = "Program lines", marker='o')
        ax[-1, i].plot(range(len(length[i])), np.log(length[i]), label = "Program length (log)", marker='o')
        ax[-1, i].set_title(" ".join(["Programs", f"Program {j+1}"]))
        ax[-1, i].legend(loc = "upper right")

    fig.suptitle(" ".join([folder, task, "results"]))
    plt.legend()
    mng = plt.get_current_fig_manager()
    mng.resize(*mng.window.maxsize())
    plt.show()

if (__name__ == "__main__"):
    plotTask(sys.argv[-2], sys.argv[-1])
