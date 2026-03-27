import matplotlib.pyplot as plt
import numpy as np
import os
import pandas as pd
import test_arc

def exportResults(folder: str, sortedTasks: list):
    assert(folder in ("training", "evaluation"))

    files = os.listdir(f"data/{folder}")
    outputFiles = sorted(filter(lambda x: "output" in x, files))

    tasksFiles = {}

    for file in outputFiles:
        task = file[:file.index("-")]
        l = tasksFiles.get(task, [])
        tasksFiles[task] = l + [file]

    tasksFiles = {k: tasksFiles[k] for k in sortedTasks}

    results = []

    for task, files in tasksFiles.items():
        files = sorted(files)

        subResults = []

        for file in files:
            taskPairs = test_arc.trainTestPairs(folder, task)
            trainPrograms = test_arc.outputPrograms(f"data/{folder}/{file}", taskPairs[0], "train")
            testPrograms = test_arc.outputPrograms(f"data/{folder}/{file}", taskPairs[1], "test")
            subResults.append((trainPrograms, testPrograms))

        results.append((task, subResults))

    content = ""

    with pd.ExcelWriter(f"{folder}_results.xlsx", engine = "openpyxl") as writer:
        for result in results:
            task, subResults = result
            trainSolved = False
            testSolved = False
            trainPrograms, testPrograms = subResults[-1]

            for i in range(0, len(trainPrograms)):
                trainProgram = trainPrograms[i]
                testProgram = testPrograms[i]

                if (not trainSolved):
                    trainSolved = not trainProgram[1][0]["Total cost"].sum(skipna = False)

                if (not testSolved):
                    testSolved = not testProgram[1][0]["Total cost"].sum(skipna = False)

            content += f"# Task {task}\n"
            content += f"train {'solved' if trainSolved else 'failed'}, test {'solved' if testSolved else 'failed'}\n\n"
            row = 0

            for iteration, (trainPrograms, testPrograms) in enumerate(subResults):
                col = 0
                content += f"## Iteration {iteration+1}\n\n"

                for i in range(0, len(trainPrograms)):
                    trainProgram = trainPrograms[i]
                    testProgram = testPrograms[i]
                    trainDsl, trainResult = trainProgram
                    testDsl, testResult = testProgram
                    trainDf, testDf = trainResult[0], testResult[0]
                    trainDf.to_excel(writer, sheet_name = f"{task}", index = True, startrow = row, startcol = col, na_rep = "NaN")
                    testDf.to_excel(writer, sheet_name = f"{task}", index = True, startrow = row + len(trainDf) + 2, startcol = col, na_rep = "NaN")
                    col += len(trainDf.columns) + 2

                    content += f"### Program {i+1}\n\n"
                    content += f"#### Train costs\n\n"
                    content += trainDf.to_markdown() + "\n\n"
                    content += f"#### Test costs\n\n"
                    content += testDf.to_markdown() + "\n\n"
                    content += f"#### DSL\n\n```python\n{trainDsl}\n```\n\n"

                row += len(trainDf) + len(testDf) + 4

    f = open(f"{folder}_full_results.md", "w")
    f.write(content)
    f.close()

def plotTasks(folder: str, step: str, labels: list, costs: list, dsls: list):
    assert(folder in ("training", "evaluation"))
    assert(step in ("train", "test"))

    fig, ax = plt.subplots()

    maxCost = 200
    totalCosts = [x["Total cost"] for x in costs]

    print(folder, step)
    print("Maximum total cost:", max(totalCosts))
    print(f"Task ratio with a total cost < {maxCost}: {len(list(filter(lambda x: x < maxCost, totalCosts))) / len(totalCosts) * 100}%")

    x = range(0, len(labels))
    taskCosts = {}

    for v in costs[0].keys():
        taskCosts[v] = []

    for cost in costs:
        for k, v in cost.items():
            taskCosts[k].append(v)

    for k, v in taskCosts.items():
        ax.plot(x, v, label = k, marker='o')

    ax.plot(x, np.log([len(x) for x in dsls]), label = "Program length (log)", marker='o')
    ax.plot(x, [len(x.split("\n")) for x in dsls], label = "Program lines", marker='o')
    fig.suptitle(" ".join([folder, step, "results"]))
    plt.xticks(x, labels, rotation = 'vertical')
    plt.legend()
    mng = plt.get_current_fig_manager()
    mng.resize(*mng.window.maxsize())
    plt.savefig(f"{folder}_{step}_results.png")
    plt.show()

def analyseFolder(folder: str):
    assert(folder == "training" or folder == "evaluation")

    f = open(folder + "_results.md")
    content = f.read()
    f.close()
    
    lines = list(filter(None, content.split("\n")))
    
    i = 0
    trainLabels = []
    trainCosts = []
    trainDsls = []
    testLabels = []
    testCosts = []
    testDsls = []
    sortedTasks = []

    while (i < len(lines)):
        f, t, step, gridSizeCost, valueCost, pixelOverlapCost, boudingBoxCost, totalCost = lines[i].split(" ")
        sortedTasks.append(t)
        cost = {"Grid size cost": float(gridSizeCost), "Value cost": float(valueCost), "Pixel overlap cost": float(pixelOverlapCost),
                "Bounding box cost": float(boudingBoxCost), "Total cost": float(totalCost)}
        i += 2

        dsl = []

        while (lines[i] != "```"):
            dsl.append(lines[i])
            i += 1

        match (step):
            case "train":
                trainLabels.append(t)
                trainCosts.append(cost)
                trainDsls.append("\n".join(dsl))
            case "test":
                testLabels.append(t)
                testCosts.append(cost)
                testDsls.append("\n".join(dsl))

        i += 1

    exportResults(folder, sortedTasks)

    if (len(testLabels)):
        plotTasks(folder, "test", testLabels, testCosts, testDsls)

    if (len(testLabels)):
        plotTasks(folder, "test", testLabels, testCosts, testDsls)

    if (len(trainLabels)):
        plotTasks(folder, "train", trainLabels, trainCosts, trainDsls)

    taskTotal = len(trainLabels) + len(testLabels)

    if (taskTotal):
        taskCosts = {}

        for v in testCosts[0].keys():
            taskCosts[v] = []

        for cost in testCosts:
            for k, v in cost.items():
                taskCosts[k].append(v)

        optimalCount = len(list(filter(lambda x: not x, taskCosts[list(taskCosts.keys())[-1]])))

        print(folder)
        print(f"{len(testLabels)/taskTotal*100}% passing train dataset")
        print(f"{optimalCount/taskTotal*100}% passing test dataset")

analyseFolder("training")
analyseFolder("evaluation")
