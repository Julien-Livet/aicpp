import ast
from concurrent.futures import ThreadPoolExecutor
import copy
import importlib.util
import json
import math
import multiprocessing as mp
import numpy as np
from openai import OpenAI, OpenAIError
import os
import pandas as pd
import pytest
import queue
import re
import subprocess
import sys
import time
import traceback
from tqdm import tqdm
import urllib.request

errors = set()

def callOllama(model: str, prompt: str) -> str:
    cmd = ["ollama", "run", model, prompt]
    result = subprocess.run(cmd, capture_output = True, text = True)
    
    return result.stdout

def callGpt(prompt: str, model: str = "gpt-5") -> str:
    try:
        return OpenAI().responses.create(model = model, input = prompt).output_text
    except OpenAIError as e:
        if (not str(e) in errors):
            print(e)

        errors.add(str(e))

        return ""

def callLLM(prompt: str) -> str:
    return callGpt(prompt)
    return callOllama("llama3.1:405b", prompt)

class DSLWorker:
    def __init__(self):
        self.task_q = mp.Queue()
        self.result_q = mp.Queue()

        self.p = mp.Process(target = self._worker_loop, args = (self.task_q, self.result_q), daemon = True)
        self.p.start()

    @staticmethod
    def _worker_loop(task_q, result_q):
        arc_types_module = load_module("arc_types", "arc-dsl/arc_types.py")
        constants_module = load_module("constants", "arc-dsl/constants.py")
        dsl_module = load_module("dsl", "arc-dsl/dsl.py")

        env = {}
        env.update(vars(arc_types_module))
        env.update(vars(constants_module))
        env.update(vars(dsl_module))

        namespace = {}
        namespace.update(env)

        while (True):
            code, func_name, args, kwargs = task_q.get()

            try:
                exec(code, namespace)
                result = namespace[func_name](*args, **kwargs)
                result_q.put(("ok", result))
            except Exception as e:
                lines = traceback.format_exc().split("\n")
                lines = lines[4:]
                lines = lines[:1] + [code] + lines[1:]
                e.traceback = "\n".join(lines)
                result_q.put(("err", e))

    def run_with_timeout(self, code: str, func_name: str, timeout: float, *args, **kwargs):
        self.task_q.put((code, func_name, args, kwargs))

        try:
            status, value = self.result_q.get(timeout = timeout)
        except queue.Empty:
            raise TimeoutError("Function execution exceeded timeout")

        if (status == "err"):
            raise value

        return value

    def terminate(self):
        self.p.terminate()
        self.p.join()

def load_module(name: str, path: str):
    spec = importlib.util.spec_from_file_location(name, path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    sys.modules[name] = module
    
    return module

def size_cost(x: np.ndarray, y: np.ndarray) -> float:
    return np.linalg.norm(np.array(x.shape) - np.array(y.shape))

def value_cost(x: np.ndarray, y: np.ndarray) -> float:
    if (x.shape == y.shape):
        return np.linalg.norm(x - y)
        
    return abs(sum(sum(x)) - sum(sum(y)))

def pixel_overlap_cost(x: np.ndarray, y: np.ndarray) -> float:
    if (x.shape != y.shape):
        return np.prod(x.shape) + np.prod(y.shape)

    total = x.size
    matches = np.sum(x == y)

    return 1.0 - (matches / total)

def bounding_box(arr: np.ndarray):
    coords = np.argwhere(arr != 0)
    
    if (coords.size == 0):
        return None

    y_min, x_min = coords.min(axis = 0)
    y_max, x_max = coords.max(axis = 0)

    return (y_min, x_min, y_max, x_max)

def bounding_box_cost(x: np.ndarray, y: np.ndarray) -> float:
    box_x = bounding_box(x)
    box_y = bounding_box(y)

    if (box_x is None and box_y is None):
        return 0.0

    if (box_x is None or box_y is None):
        return 1.0

    diff = np.linalg.norm(np.array(box_x) - np.array(box_y))
    norm = np.linalg.norm(np.array(x.shape) + np.array(y.shape))

    return diff / (norm + 1e-8)

scoreFunctions = [size_cost, value_cost, pixel_overlap_cost, bounding_box_cost]
scoreColumns = ["Grid size cost", "Value cost", "Pixel overlap cost", "Bounding box cost", "Total cost"]

@pytest.fixture(autouse = True)
def print_test_duration(request):
    start_time = time.time()
    yield
    duration = time.time() - start_time
    print(f"\nTest {request.node.name} took {duration:.2f} seconds to execute.")

def trainTestPairs(folder: str, task: str) -> tuple:
    assert(folder == "training" or folder == "evaluation")

    url = urllib.request.urlopen(f"https://raw.githubusercontent.com/arcprize/ARC-AGI-2/refs/heads/main/data/{folder}/{task}.json")
    data = json.loads(url.read().decode())

    train = data["train"]
    trainPairs = []

    for v in train:
        trainPairs.append((np.array(v["input"]), np.array(v["output"])))

    test = data["test"]
    testPairs = []

    for v in test:
        testPairs.append((np.array(v["input"]), np.array(v["output"])))

    return (trainPairs, testPairs)

def inputOutputPairs(pairs):
    inputs = []
    outputs = []

    for p in pairs:
        inputs.append(p[0])
        outputs.append(p[1])

    return (inputs, outputs)

def taskPrompt(trainPairs: list) -> str:
    command = "You are given several input->output grid pairs from an ARC task:\n"

    for i in range(len(trainPairs[0])):
        command += f"train{i+1}: " + str(tuple(map(tuple, trainPairs[0][i].tolist()))) + " -> " + str(tuple(map(tuple, trainPairs[1][i].tolist()))) + "\n"

    command += "\nAvailable types:\n"

    f = open("arc-dsl/arc_types.py", "r")
    content = f.read()
    f.close()
    
    command += "```python\n"
    command += content
    command += "```\n"

    command += "\nAvailable variables:\n"

    f = open("arc-dsl/constants.py", "r")
    content = f.read()
    f.close()
    
    command += "```python\n"
    command += "I: Tuple[Tuple]\n"
    command += "\n".join(filter(None, content.split("\n", ))) + "\n"
    command += "```\n"

    command += "\nAvailable primitives:\n"

    result = subprocess.run('cd arc-dsl && python -c "import dsl; help(dsl)"', shell = True, capture_output = True, text = True)
    lines = result.stdout.split("\n")

    functions = []
    words = []
    finish = False

    for i in range(lines.index("FUNCTIONS") + 1, lines.index("DATA") ):
        if (finish):
            functions.append("".join(words) + " # " + lines[i].strip())
            words = []
        else:
            words.append(lines[i].strip())
            
        finish = ")" in lines[i]

    command += "```python\n"
    command += "\n".join(functions) + "\n"
    command += "```\n"
        
    return command

def taskResults(source: str, pairs: list, label: str):
    name = source.split("\n")[0].replace("def ", "").replace("(I):", "")
    runner = DSLWorker()
    scores = []
    outputs = []
    tracebacks = set()

    for pair in pairs:
        try:
            score = [0] * len(scoreFunctions)

            for i in range(0, len(scoreFunctions)):
                output = runner.run_with_timeout(source, name, 5, tuple(map(tuple, pair[0].tolist())))
                score[i] += scoreFunctions[i](np.array(output), pair[1])
        except (AttributeError, IndexError, KeyError, NameError, RecursionError, StopIteration, TimeoutError, TypeError, ValueError, ZeroDivisionError) as e:
            if (type(e) != TimeoutError):
                tracebacks.add("```\n" + e.traceback + "```")

            score = [math.nan] * len(scoreFunctions)
            output = np.array(pair[0], dtype = float)
            np.ndarray.fill(output, np.nan)
            output = tuple(map(tuple, output))

        scores.append(score + [sum(score)])
        outputs.append(output)

    runner.terminate()

    df = pd.DataFrame(scores, index = [f"{label}{i+1}" for i in range(len(pairs))], columns = scoreColumns)

    return (df, outputs, tracebacks)

def processTask(folder: str, task: str, debug: bool = True) -> list:
    taskPairs = trainTestPairs(folder, task)
    trainPairs = inputOutputPairs(taskPairs[0])

    cost = math.nan
    currentDsl = """def dsl(I):
    O = I
    return O"""
    index = 0

    for file in os.listdir(f"data/{folder}"):
        if ("input" in file and task in file):
            index = max(index, int(file.replace(".md", "").replace(f"{task}-input-", "")))

    if (os.path.exists(f"data/{folder}/{task}-output-{index:03d}.md")):
        f = open(f"data/{folder}/{task}-output-{index:03d}.md", "r")
        content = f.read()
        f.close()

        groups = re.findall(r'```python(.*?)```', content, flags = re.S)

        if (len(groups)):
            currentDsl = groups[-1].strip()
            index += 1
    elif (os.path.exists(f"data/{folder}/{task}-output-{index-1:03d}.md")):
        f = open(f"data/{folder}/{task}-output-{index-1:03d}.md", "r")
        content = f.read()
        f.close()

        groups = re.findall(r'```python(.*?)```', content, flags = re.S)

        if (len(groups)):
            currentDsl = groups[-1].strip()

    arc_types_module = load_module("arc_types", "arc-dsl/arc_types.py")
    constants_module = load_module("constants", "arc-dsl/constants.py")
    dsl_module = load_module("dsl", "arc-dsl/dsl.py")

    env = {}
    env.update(vars(arc_types_module))
    env.update(vars(constants_module))
    env.update(vars(dsl_module))

    for _ in range(0, 10):
        command = taskPrompt(trainPairs) + "\n"
        command += "Current DSL program:\n"
        command += "```python\n"
        command += currentDsl + "\n"
        command += "```\n"

        trainResults = taskResults(currentDsl, taskPairs[0], "train")
        cost = trainResults[0][scoreColumns[-1]].sum(skipna = False)

        if (not cost):
            break
        elif (debug):
            print(trainResults[0])
            print("Total cost", cost)
            print("Program length", len(currentDsl))
            print("Program lines", len(currentDsl.split("\n")))

        command += "\nExplosive scores:\n"
        command += trainResults[0].to_csv(sep = ",", na_rep = "nan")
        command += "\nOutput grids:\n"
        command += "\n".join(list(filter(lambda x: not "NaN" in x, [f"train{i+1}: " + str(x) for i, x in enumerate(trainResults[1])]))) + "\n"

        if (len(trainResults[2])):
            command += "\nTracebacks:\n"
            command += "\n".join([str(x) for x in trainResults[2]]) + "\n"

        command += """\nThe goal is to incrementally improve the current DSL program to match the examples, while avoiding previously low-scoring solutions, in two steps:
1. Expansion: add missing generic concepts to fix observed errors.
2. Reduction: refactor the program into a minimal, unified, and fully factorized form.

Constraints:
- Use a single transformation pipeline.
- All spatial propagation must be expressed as:
    vectors = ...
    shifted = mapply(shift, vectors)
- The final result must be obtained by filtering (masking) these propagated indices.
- Do not implement multiple propagation mechanisms or case-based logic.
- All variations (direction, step size, repetition) must be encoded as data (vectors), not separate branches.
- Avoid row-level or object-level special cases; operate directly on indices whenever possible.

Guidelines:
- Merge all similar transformations into one parameterized rule.
- Replace repeated patterns with higher-order constructs (interval, apply, mapply).
- Prefer invariant and position-independent primitives.
- Eliminate unnecessary conditions and constants.

Goal:
Produce the simplest program that applies a single coherent transformation rule uniformly across the grid.\n"""

        if (len(trainResults[2])):
            command += "\nNaN values correspond to exceptions that are explained by tracebacks and must be corrected by analyzing them.\n"

        command += """\nGenerate the new DSL program issued from the step 2.

A good final program should look like:
```python
def dsl(I):
    # 1. Extract entities
    x1 = objects(...)
    # 2. For each entity, select the best transformation
    x2 = mapply(some_transform, x1)
    # 3. Apply to grid
    O = underfill(I, ONE, x2)
    return O
```

EXPECTED OUTPUT EXAMPLE WITHOUT ANY FORMATTING AND ANY EXPLANATION:
```python
def dsl(I):
    O = vmirror(I)
    return O
```"""

        f = open(f"data/{folder}/{task}-input-{index:03d}.md", "w")
        f.write(command)
        f.close()

        content = callLLM(command)

        if (len(content) == 0):
            return [currentDsl, folder, task, "train", cost]

        f = open(f"data/{folder}/{task}-output-{index:03d}.md", "w")
        f.write(content)
        f.close()

        groups = re.findall(r'```python(.*?)```', content, flags = re.S)

        if (len(groups) == 0):
            currentDsl = content.strip()

            f = open(f"data/{folder}/{task}-output-{index:03d}.md", "w")
            f.write(f"```python\n{currentDsl}\n```")
            f.close()
        else:
            currentDsl = groups[-1].strip()

        index += 1

    if (cost):
        costs = [trainResults[0][x].sum(skipna = False) for x in scoreColumns]

        if (debug):
            print(" ".join(str(x) for x in [folder, task, "train"] + costs))
            print(trainResults[0])
            print("Total cost", cost)
            print("Program length", len(currentDsl))
            print("Program lines", len(currentDsl.split("\n")))
            print(currentDsl)

        return [currentDsl, folder, task, "train"] + costs

    testResults = taskResults(currentDsl, taskPairs[1], "test")
    cost = testResults[0][scoreColumns[-1]].sum(skipna = False)
    costs = [testResults[0][x].sum(skipna = False) for x in scoreColumns]

    if (debug):
        print(" ".join(str(x) for x in [folder, task, "test"] + costs))
        print(testResults[0])
        print("Total cost", cost)
        print("Program length", len(currentDsl))
        print("Program lines", len(currentDsl.split("\n")))
        print(currentDsl)

    return [currentDsl, folder, task, "test"] + costs

def test_task3c9b0459(): #Flip left/right and flip up/down
    assert(processTask("training", "3c9b0459")[-1] == 0)

def test_task0d3d703e(): #Color mapping
    assert(processTask("training", "0d3d703e")[-1] == 0)

def test_taskc909285e():
    assert(processTask("training", "c909285e")[-1] == 0)

def test_task67a3c6ac():
    assert(processTask("training", "67a3c6ac")[-1] == 0)

def test_task68b16354():
    assert(processTask("training", "68b16354")[-1] == 0)

def test_task74dd1130():
    assert(processTask("training", "74dd1130")[-1] == 0)

def test_task6150a2bd():
    assert(processTask("training", "6150a2bd")[-1] == 0)

def test_task9172f3a0():
    assert(processTask("training", "9172f3a0")[-1] == 0)

def test_task9dfd6313():
    assert(processTask("training", "9dfd6313")[-1] == 0)

def test_taska416b8f3():
    assert(processTask("training", "a416b8f3")[-1] == 0)

def test_taskb1948b0a():
    assert(processTask("training", "b1948b0a")[-1] == 0)

def test_taskc59eb873():
    assert(processTask("training", "c59eb873")[-1] == 0)

def test_taskc8f0f002():
    assert(processTask("training", "c8f0f002")[-1] == 0)

def test_taskd10ecb37():
    assert(processTask("training", "d10ecb37")[-1] == 0)

def test_taskd511f180():
    assert(processTask("training", "d511f180")[-1] == 0)

def test_tasked36ccf7():
    assert(processTask("training", "ed36ccf7")[-1] == 0)

def test_task4c4377d9():
    assert(processTask("training", "4c4377d9")[-1] == 0)

def test_task6d0aefbc():
    assert(processTask("training", "6d0aefbc")[-1] == 0)

def test_task6fa7a44f():
    assert(processTask("training", "6fa7a44f")[-1] == 0)

def test_task5614dbcf():
    assert(processTask("training", "5614dbcf")[-1] == 0)

def test_task8be77c9e():
    assert(processTask("training", "8be77c9e")[-1] == 0)

def test_taskc9e6f938():
    assert(processTask("training", "c9e6f938")[-1] == 0)

def test_task5582e5ca():
    assert(processTask("training", "5582e5ca")[-1] == 0)

def test_task2dee498d():
    assert(processTask("training", "2dee498d")[-1] == 0)

def test_task5bd6f4ac():
    assert(processTask("training", "5bd6f4ac")[-1] == 0)

def test_task1cf80156():
    assert(processTask("training", "1cf80156")[-1] == 0)

def test_task32597951():
    assert(processTask("training", "32597951")[-1] == 0)

def test_task25ff71a9():
    assert(processTask("training", "25ff71a9")[-1] == 0)

"""
def test_task():
    assert(processTask("training", "")[-1] == 0)
"""

def run_tasks(folder: str) -> tuple[int, int]:
    assert(folder == "training" or folder == "evaluation")

    url = urllib.request.urlopen(f"https://raw.githubusercontent.com/arcprize/ARC-AGI-2/refs/heads/main/data/{folder}.txt")
    data = url.read().decode()
    tasks = data.split("\n")
    files = os.listdir(f"data/{folder}")
    unexploredTasks = []

    for task in tasks:
        if (not any([task in x for x in files])):
            unexploredTasks.append(task)

    tasks = sorted(unexploredTasks) + sorted(set(tasks) - set(unexploredTasks))
    tasks = tasks[:120] #TODO: to remove

    if (folder == "training"):
        tasks = ["90f3ed37"] #["90f3ed37", "46c35fc7", "351d6448"]
    elif (folder == "evaluation"):
        tasks = [] #["28a6681f", "9bbf930d", "7b5033c1"]

    with ThreadPoolExecutor(max_workers = os.cpu_count()) as executor:
        results = list(tqdm(
            executor.map(lambda task: processTask(folder, task, debug = True), tasks),
            total = len(tasks), miniters = 1, smoothing = 1
        ))

    results = sorted(sorted(results, key = lambda x: math.isnan(x[-1])), key = lambda x: (x[-1], len(x[0])))

    f = open(f"{folder}_results.md", "w")

    for result in results:
        f.write(" ".join(str(x) for x in result[1:]) + "\n")
        f.write("```python\n" + result[0] + "\n```\n")

    f.close()

    return sum(1 for r in results if r[-1] == 0), len(tasks)

def test_training_tasks():
    count, tasks = run_tasks("training")

    print(f"{count}/{tasks} {count/tasks*100}% passed training tasks")

def test_evaluation_tasks():
    count, tasks = run_tasks("evaluation")

    print(f"{count}/{tasks} {count/tasks*100}% passed evaluation tasks")
