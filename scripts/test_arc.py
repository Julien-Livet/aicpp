from concurrent.futures import ThreadPoolExecutor
import importlib.util
import inspect
import json
import math
from multiprocessing import Process, Queue
import numpy as np
from openai import OpenAI, OpenAIError
import os
import pytest
import re
import subprocess
import sys
import time
from tqdm import tqdm
import types
import urllib.request

errors = dict()

def callOllama(model: str, prompt: str) -> str:
    cmd = ["ollama", "run", model, prompt]
    result = subprocess.run(cmd, capture_output = True, text = True)
    
    return result.stdout

def callGpt(prompt: str, model: str = "gpt-5") -> str:
    try:
        return OpenAI().responses.create(model = model, input = prompt).output_text
    except OpenAIError as e:
        if (errors.get(str(e), None) == None):
            print(e)

        errors[str(e)] = True

        return ""

def callLLM(prompt: str) -> str:
    return callGpt(prompt)
    return callOllama("llama3.1:405b", prompt)

def run_func(func, queue, *args, **kwargs):
    try:
        result = func(*args, **kwargs)
    except AttributeError:
        result = np.zeros((1, 1))
    except IndexError:
        result = np.zeros((1, 1))
    except NameError:
        result = np.zeros((1, 1))
    except TimeoutError:
        result = np.zeros((1, 1))
    except TypeError:
        result = np.zeros((1, 1))
    except StopIteration:
        result = np.zeros((1, 1))
    except ValueError:
        result = np.zeros((1, 1))

    queue.put(result)

def run_with_timeout(func, timeout, *args, **kwargs):
    queue = Queue()
    p = Process(target = run_func, args = (func, queue, *args), kwargs = kwargs)

    p.start()
    p.join(timeout)

    if (p.is_alive()):
        p.terminate()
        p.join()
        raise TimeoutError("Function execution exceeded timeout")
        
    if (not queue.empty()):
        return queue.get()

    return np.zeros((1, 1))

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

@pytest.fixture(autouse = True)
def print_test_duration(request):
    start_time = time.time()
    yield
    duration = time.time() - start_time
    print(f"\nTest {request.node.name} took {duration:.2f} seconds to execute.")

def trainTestPairs(folder: str, task: str) -> tuple:
    url = urllib.request.urlopen("https://raw.githubusercontent.com/arcprize/ARC-AGI-2/refs/heads/main/data/" + folder + "/" + task + ".json")
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

def processTask(folder: str, task: str, debug: bool = True) -> int:
    taskPairs = trainTestPairs(folder, task)
    trainPairs = inputOutputPairs(taskPairs[0])
    testPairs = inputOutputPairs(taskPairs[1])

    cost = None
    dsl = ""
    scores = []
    firstLoop = True
    count = 0

    while ((cost is None or cost) and count < 4):
        count += 1

        command = "You are given several input-output grid pairs from an ARC task:\n"

        for i in range(len(trainPairs[0])):
            command += "(" + json.dumps(trainPairs[0][i].tolist()) + ", " + json.dumps(trainPairs[1][i].tolist()) + ")\n"

        command += """
Available types:
"""
        f = open("arc-dsl/arc_types.py", "r")
        content = f.read()
        f.close()
        
        command += content

        command += """
Available variables:
"""
        f = open("arc-dsl/constants.py", "r")
        content = f.read()
        f.close()
        
        command += "I: tuple[tuple]\n"
        command += "\n".join(filter(None, content.split("\n", ))) + "\n"

        command += """
Available primitives:
"""
        result = subprocess.run("cd arc-dsl && python -c 'import dsl; help(dsl)'", shell = True, capture_output = True, text = True)
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

        command += "\n".join(functions) + "\n"
        
        if (len(scores)):
            command += "\nPrevious program scores:\n\n"
            command += "|Program|Size cost|Value cost|Pixel overlap cost|Bounding box cost|Total cost|\n"
            command += "|-|-|-|-|-|\n"
            command += "\n".join("|" + "|".join(s) + "|" for s in scores) + "\n"
            
            command += "\nPropose at most 5 improved variants avoiding previous low-scoring.\n"
        else:
            command += "\nGenerate at most 5 plausible DSL programs using only the declared primitives.\n"

        command += """All programs must be described within a single Python MarkDown tag.

"""

        command += """
EXPECTED OUTPUT EXAMPLE WITHOUT ANY FORMATTING AND ANY EXPLANATION:
```python
def dsl1(I):
    O = vmirror(I)
    return O

def dsl2(I):
    O = hmirror(I)
    return O

def dsl3(I):
    O = dmirror(I)
    return O

def dsl4(I):
    O = rot180(I)
    return O
    
def dsl5(I):
    x1 = replace(I, FIVE, ZERO)
    O = downscale(x1, THREE)
    return O
```
"""

        f = open("data/" + folder + "/prompt" + task + ".txt", "w")
        f.write(command)
        f.close()

        if (firstLoop):
            try:
                f = open("data/" + folder + "/output" + task + ".txt", "r")
                content = f.read()
                f.close()
            except FileNotFoundError as e:
                content = callLLM(command)
        else:
            content = callLLM(command)

        if (len(content) == 0):
            return False

        f = open("data/" + folder + "/output" + task + ".txt", "w")
        f.write(content)
        f.close()

        groups = re.findall(r'```python(.*?)```', content, flags = re.S)

        if (len(groups) == 0):
            continue

        content = groups[-1]

        firstLoop = False

        f = open("proposals/proposals" + task + ".py", "w")
        f.write("""import importlib.util
import sys

def load_module(name: str, path: str):
    spec = importlib.util.spec_from_file_location(name, path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    sys.modules[name] = module
    
    return module

globals().update(vars(load_module("arc_types", "arc-dsl/arc_types.py")))
globals().update(vars(load_module("constants", "arc-dsl/constants.py")))
globals().update(vars(load_module("dsl", "arc-dsl/dsl.py")))
constants = load_module("constants", "arc-dsl/constants.py")

""")
        f.write(content)
        f.close()
        
        proposals = load_module("proposals" + task, "proposals/proposals" + task + ".py")
        functions = []

        for x in dir(proposals):
            f = getattr(proposals, x)

            if (type(f) is types.FunctionType and f.__name__.startswith("dsl")):
                functions.append(f)

        scoreFunctions = [size_cost, value_cost, pixel_overlap_cost, bounding_box_cost]
        totalScores = []

        for function in functions:
            score = [0] * len(scoreFunctions)

            try:
                for pair in taskPairs[0]:
                    for i in range(0, len(scoreFunctions)):
                        score[i] += scoreFunctions[i](np.array(run_with_timeout(function, 1, tuple(map(tuple, pair[0].tolist())))), pair[1])

                for pair in taskPairs[1]:
                    for i in range(0, len(scoreFunctions)):
                        score[i] += scoreFunctions[i](np.array(run_with_timeout(function, 1, tuple(map(tuple, pair[0].tolist())))), pair[1])

                scores.append([";".join(inspect.getsource(function).split("\n"))] + [str(x) for x in score] + [str(sum(score))])
                totalScores.append((function, sum(score)))
            except TimeoutError:
                pass
            except TypeError:
                pass
            except ValueError:
                pass

        scores = sorted(scores, key = lambda x: (float(x[-1]), len(x[0])))[:3]
        totalScores = sorted(totalScores, key = lambda x: x[1])

        if (len(totalScores)):
            dsl = inspect.getsource(totalScores[0][0])
            cost = totalScores[0][1]

    if (debug):
        print(folder, task, cost, "\n", dsl)

    return cost == 0

def test_task3c9b0459(): #Flip left/right and flip up/down
    assert(processTask("training", "3c9b0459"))

def test_task0d3d703e(): #Color mapping
    assert(processTask("training", "0d3d703e"))

def test_taskc909285e():
    assert(processTask("training", "c909285e"))

def test_task67a3c6ac():
    assert(processTask("training", "67a3c6ac"))

def test_task68b16354():
    assert(processTask("training", "68b16354"))

def test_task74dd1130():
    assert(processTask("training", "74dd1130"))

def test_task6150a2bd():
    assert(processTask("training", "6150a2bd"))

def test_task9172f3a0():
    assert(processTask("training", "9172f3a0"))

def test_task9dfd6313():
    assert(processTask("training", "9dfd6313"))

def test_taska416b8f3():
    assert(processTask("training", "a416b8f3"))

def test_taskb1948b0a():
    assert(processTask("training", "b1948b0a"))

def test_taskc59eb873():
    assert(processTask("training", "c59eb873"))

def test_taskc8f0f002():
    assert(processTask("training", "c8f0f002"))

def test_taskd10ecb37():
    assert(processTask("training", "d10ecb37"))

def test_taskd511f180():
    assert(processTask("training", "d511f180"))

def test_tasked36ccf7():
    assert(processTask("training", "ed36ccf7"))

def test_task4c4377d9():
    assert(processTask("training", "4c4377d9"))

def test_task6d0aefbc():
    assert(processTask("training", "6d0aefbc"))

def test_task6fa7a44f():
    assert(processTask("training", "6fa7a44f"))

def test_task5614dbcf():
    assert(processTask("training", "5614dbcf"))

def test_task8be77c9e():
    assert(processTask("training", "8be77c9e"))

def test_taskc9e6f938():
    assert(processTask("training", "c9e6f938"))

def test_task5582e5ca():
    assert(processTask("training", "5582e5ca"))

def test_task2dee498d():
    assert(processTask("training", "2dee498d"))

def test_task5bd6f4ac():
    assert(processTask("training", "5bd6f4ac"))

def test_task1cf80156():
    assert(processTask("training", "1cf80156"))

def test_task32597951():
    assert(processTask("training", "32597951"))

def test_task25ff71a9():
    assert(processTask("training", "25ff71a9"))

"""
def test_task():
    assert(processTask("training", ""))
"""

def run_tasks(folder: str) -> int:
    url = urllib.request.urlopen("https://raw.githubusercontent.com/arcprize/ARC-AGI-2/refs/heads/main/data/" + folder + ".txt")
    data = url.read().decode()
    tasks = data.split("\n")

    unexploredTasks = []

    for task in tasks:
        if (not os.path.isfile("data/" + folder + "/" + "output" + task + ".txt")):
            unexploredTasks.append(task)

    tasks = unexploredTasks + list(set(tasks) - set(unexploredTasks))
 
    with ThreadPoolExecutor(max_workers = 1) as executor:
        results = list(tqdm(
            executor.map(lambda task: processTask(folder, task, debug = False), tasks),
            total = len(tasks), miniters = 1, smoothing = 1
        ))

    return sum(1 for r in results if r), len(tasks)

def test_training_tasks():
    count, tasks = run_tasks("training")

    print(f"{count}/{tasks} {count/tasks*100}% passed training tasks")

"""
def test_evaluation_tasks():
    count, tasks = run_tasks("evaluation")

    print(f"{count}/{tasks} {count/tasks*100}% passed evaluation tasks")
"""
