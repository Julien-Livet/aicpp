import matplotlib.pyplot as plt
import numpy as np

def plotTasks(folder: str, step: str, labels: list, costs: list, dsls: list):
    fig, ax = plt.subplots()

    maxCost = 100
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

    while (i < len(lines)):
        f, t, step, gridSizeCost, valueCost, pixelOverlapCost, boudingBoxCost, totalCost = lines[i].split(" ")
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
    """
    if (len(trainLabels)):
        plotTasks(folder, "train", trainLabels, trainCosts, trainDsls)

    if (len(testLabels)):
        plotTasks(folder, "test", testLabels, testCosts, testDsls)
    """
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

