import difflib
from io import StringIO
import matplotlib.pyplot as plt
import numpy as np
import os
import pandas as pd
import sys
import test_arc

def diff(a: str, b: str):
    return "\n".join(difflib.unified_diff(
        a.splitlines(),
        b.splitlines(),
        lineterm = ""
    ))

def plotDataSet(folder: str, task: str, step: str, costs: list, ncols: int):
    assert(folder in ("training", "evaluation"))
    assert(step in ("train", "test"))

    fig, ax = plt.subplots(nrows = len(costs), ncols = ncols)

    for i, (name, programCost) in enumerate(costs.items()):
        for j, cost in enumerate(programCost):
            for key, value in cost.items():
                a = ax[i, j] if len(costs) > 1 else ax[j]
                a.plot(range(len(value)), value, label = key, marker='o')
                a.set_title(" ".join([name, f"Program {j+1}"]))
                a.legend(loc = "upper right")

    fig.suptitle(" ".join([folder, task, step, "results"]))
    plt.legend()
    mng = plt.get_current_fig_manager()
    mng.resize(*mng.window.maxsize())
    plt.savefig(f"{folder}_{task}_{step}_results.png")
    plt.show()

def plotTask(folder: str, task: str):
    assert(folder in ("training", "evaluation"))

    files = os.listdir(f"data/{folder}")
    taskFiles = list(filter(lambda x: task in x, files))
    outputFiles = sorted(filter(lambda x: "output" in x, taskFiles))

    results = []
    files = sorted(outputFiles)

    for file in files:
        taskPairs = test_arc.trainTestPairs(folder, task)
        trainPrograms = test_arc.outputPrograms(f"data/{folder}/{file}", taskPairs[0], "train")
        testPrograms = test_arc.outputPrograms(f"data/{folder}/{file}", taskPairs[1], "test")
        results.append((trainPrograms, testPrograms))

    n = len(trainPrograms)
    trainPrograms = []
    testPrograms = []

    for i in range(0, n):
        dsl = f"def dsl{i+1}(I):\n    O = I\n    return O"
        trainPrograms.append((dsl, test_arc.taskResults(dsl, taskPairs[0], "train")))
        testPrograms.append((dsl, test_arc.taskResults(dsl, taskPairs[1], "test")))

    results = [(trainPrograms, testPrograms)] + results
    trainSolved = False
    testSolved = False
    trainPrograms, testPrograms = results[-1]
    costs = []

    for i in range(0, len(trainPrograms)):
        trainProgram = trainPrograms[i]
        testProgram = testPrograms[i]
        trainCost = trainProgram[1][0]["Total cost"].sum(skipna = False)
        testCost = testProgram[1][0]["Total cost"].sum(skipna = False)

        if (not trainSolved):
            trainSolved = not trainCost

        if (not testSolved):
            testSolved = not testCost

        costs.append((trainCost, testCost, i))

    costs = sorted(costs)
    history = []
    dfs = [None] * len(results[0][0])

    for i in range(1, len(results)):
        trainPrograms1, testPrograms1 = results[i - 1]
        trainPrograms2, testPrograms2 = results[i]

        for j in range(0, len(trainPrograms1)):
            dsl1, result1 = trainPrograms1[j]
            dsl2, result2 = trainPrograms2[j]
            df1 = result1[0]
            df2 = result2[0]
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

    with open("arc-dsl/solvers.py", "r") as file:
        solversContent = file.read()

    solversLines = solversContent.split("\n")
    content = f"# Task {task}\n\n"
    content += f"train {'solved' if trainSolved else 'failed'}, test {'solved' if testSolved else 'failed'}\n\n"
    content += f"{len(results)-1} iteration{'s' if len(results) - 1 != 1 else ''}\n\n"
    index = len(results) - 1

    if (not costs[0][-1]):
        content += f"[Best program](#iteration-{index}-dsl-diff)\n\n"
    else:
        content += f"[Best program](#iteration-{index}-dsl-diff-{costs[0][-1]})\n\n"

    try:
        lineIndex = solversLines.index(f"def solve_{task}(I):")
        content += f"[Hodel solution](https://github.com/michaelhodel/arc-dsl/blob/main/solvers.py#L{lineIndex+1})\n\n"
    except ValueError:
        pass

    for i in range(0, len(results[0][0])):
        content += f"## Program {i+1}\n\n"
        content += f"### Train scores\n\n"
        content += dfs[i].to_markdown() + "\n\n"
        trainPrograms, testPrograms = results[-1]
        content += f"### Test scores\n\n"
        content += testPrograms[i][1][0].to_markdown() + "\n\n"

        for j in range(0, len(results) - 1):            
            content += f"### Iteration {j+1} DSL diff\n\n"
            content += f"```bash\n{history[i + j * len(results[0])][0]}\n```\n\n"

    f = open(f"{folder}_{task}_history.md", "w")
    f.write(content)
    f.close()

    trainPrograms, testPrograms = results[0]
    trainDf = trainPrograms[0][1][0]
    trainCosts = {}

    for row in trainDf.iterrows():
        trainCosts[row[0]] = []

        for _ in results[0][0]:
            d = {}

            for index, _ in list(row[1].items())[1:]:
                d[index] = []

            trainCosts[row[0]].append(d)

    testDf = testPrograms[0][1][0]
    testCosts = {}

    for row in testDf.iterrows():
        testCosts[row[0]] = []

        for _ in results[0][0]:
            d = {}

            for index, _ in list(row[1].items())[1:]:
                d[index] = []

            testCosts[row[0]].append(d)

    for result in results[1:]:
        trainPrograms, testPrograms = result

        for i in range(0, len(trainPrograms)):
            trainDsl, trainResult = trainPrograms[i]
            testDsl, testResult = testPrograms[i]
            trainDf = trainResult[0]
            testDf = testResult[0]

            for row in trainDf.iterrows():
                label = row[0]
                d = trainCosts[label][i]

                for index, val in list(row[1].items())[1:]:
                    l = d.get(index, [])
                    l.append(val)
                    d[index] = l
            
            for row in testDf.iterrows():
                label = row[0]
                d = testCosts[label][i]

                for index, val in list(row[1].items())[1:]:
                    l = d.get(index, [])
                    l.append(val)
                    d[index] = l

    plotDataSet(folder, task, "train", trainCosts, len(results[0][0]))
    plotDataSet(folder, task, "test", testCosts, len(results[0][0]))

    lines = {}
    length = {}

    for i in range(0, len(results[0][0])):
        lines[i] = []
        length[i] = []

    for result in results:
        trainPrograms, testPrograms = result

        for i, program in enumerate(trainPrograms):
            lines[i].append(len(program[0].split("\n")))
            length[i].append(len(program[0]))

    fig, ax = plt.subplots(nrows = 1, ncols = len(results[0][0]))

    for i in range(0, len(lines)):
        ax[i].plot(range(len(lines[i])), lines[i], label = "Program lines", marker='o')
        ax[i].plot(range(len(length[i])), np.log(length[i]), label = "Program length (log)", marker='o')
        ax[i].set_title(f"Program {j+1}")
        ax[i].legend(loc = "upper right")

    fig.suptitle(" ".join([folder, task, "results"]))
    plt.legend()
    mng = plt.get_current_fig_manager()
    mng.resize(*mng.window.maxsize())
    plt.savefig(f"{folder}_{task}_program_results.png")
    plt.show()

if (__name__ == "__main__"):
    plotTask(sys.argv[-2], sys.argv[-1])
