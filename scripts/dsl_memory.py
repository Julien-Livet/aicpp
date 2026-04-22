from collections import defaultdict
import pickle
import os
import sys

def load(filename: str) -> set:
    if (os.path.exists(filename)):
        with open(filename, "rb") as f:
            return set(pickle.load(f))

    return {"def dsl(I):\n    O = I\n    return O", }

def save(dsls: set, filename: str):
    with open(filename, "wb") as f:
        pickle.dump(sorted(dsls, key = lambda x: (len(x), x)), f, protocol = pickle.HIGHEST_PROTOCOL)

def build(llm: tuple, folder: str):
    import test_arc

    dsls = load(f"data/{test_arc.llmPath(llm)}/dsl_memory.pkl")
    llmPath = test_arc.llmPath(llm)

    outputFiles = list(filter(lambda x: "output" in x, os.listdir(f"data/{llmPath}/{folder}")))

    taskFiles = defaultdict(list)
    
    for file in outputFiles:
        taskFiles[file[:file.index("-")]].append(file)

    for task, files in taskFiles.items():
        taskPairs = test_arc.trainTestPairs(folder, task)
        
        for file in files:
            programs = test_arc.outputPrograms(f"data/{llmPath}/{folder}/{file}", taskPairs[0], "train")
            
            for program in programs:
                dsl, taskResults = program
                df, outputs, tracebacks = taskResults

                if (not tracebacks):
                    dsls.add(dsl)

    save(dsls, f"data/{llmPath}/dsl_memory.pkl")

if (__name__ == "__main__"):
    build((sys.argv[-3], sys.argv[-2]), sys.argv[-1])
