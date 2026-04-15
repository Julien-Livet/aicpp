import os
import sys

def removeTasks(llm: tuple, folder: str):
    assert(folder in ("evaluation", "training"))

    with open(f"data/{llm[0]}/{llm[1]}/{folder}_results.md", "r") as f:
        lines = f.read().split("\n")

    tasks = []
    
    for line in lines:
        if (line.startswith(folder)):
            f, t, s, c1, c2, c3, c4, ct = line.split(" ")
            
            if (float(ct)):
                tasks.append(t)

    for file in os.listdir(f"data/{llm[0]}/{llm[1]}/{folder}"):
        for task in tasks:
            if (task in file[:file.index("-")]):
                os.remove(f"data/{llm[0]}/{llm[1]}/{folder}/{file}")

            break

if (__name__ == "__main__"):
    removeTasks((sys.argv[-3], sys.argv[-2]), sys.argv[-1])
