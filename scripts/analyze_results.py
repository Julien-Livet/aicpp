import matplotlib.pyplot as plt
import numpy as np

def analyseFolder(folder: str):
    assert(folder == "training" or folder == "evaluation")

    f = open(folder + "_results.md")
    content = f.read()
    f.close()
    
    lines = list(filter(None, content.split("\n")))
    
    i = 0
    labels = []
    y1 = []
    y2 = []
    y3 = []
    y4 = []
    yt = []
    dsls = []

    while (i < len(lines)):
        f, t, s1, s2, s3, s4, st = lines[i].split(" ")
        labels.append(t)
        y1.append(float(s1))
        y2.append(float(s2))
        y3.append(float(s3))
        y4.append(float(s4))
        yt.append(float(st))

        i += 2

        dsl = []

        while (lines[i] != "```"):
            dsl.append(lines[i])
            i += 1

        dsls.append("\n".join(dsl))

        i += 1

    x = range(0, len(labels))
    
    fig, ax = plt.subplots()

    ax.plot(x, y1, label = "size_cost")
    ax.plot(x, y2, label = "value_cost")
    ax.plot(x, y3, label = "pixel_overlap_cost")
    ax.plot(x, y4, label = "bounding_box_cost")
    ax.plot(x, yt, label = "total_cost")
    ax.plot(x, [x.count("\n") for x in dsls], label = "len_cost")
    plt.xticks(x, labels, rotation = 'vertical')
    plt.legend()
    plt.yscale('log')
    mng = plt.get_current_fig_manager()
    mng.resize(*mng.window.maxsize())
    plt.show()

analyseFolder("training")
analyseFolder("evaluation")

