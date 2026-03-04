import importlib.util
import inspect
import json
import numpy as np
from openai import OpenAI
import pytest
import subprocess
import sys
import time
import types
import urllib.request

def load_module(name: str, path: str):
    spec = importlib.util.spec_from_file_location(name, path)
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    
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

def processTask(folder: str, task: str) -> int:
    taskPairs = trainTestPairs(folder, task)
    trainPairs = inputOutputPairs(taskPairs[0])
    testPairs = inputOutputPairs(taskPairs[1])

    cost = None
    dsl = ""
    scores = []
    first = True
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
        
        command += "I: np.ndarray\n"
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
            
            command += "\nPropose 5 improved variants avoiding previous low-scoring.\n"
        else:
            command += "Generate 5 plausible DSL programs using only the declared primitives.\n"

        command += """
EXPECTED OUTPUT EXAMPLE WITHOUT ANY FORMATTING AND ANY EXPLANATION:
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
"""

        f = open("data/" + folder + "/prompt" + task + ".txt", "w")
        f.write(command)
        f.close()

        if (first):
            try:
                f = open("data/" + folder + "/output" + task + ".txt", "r")
                content = f.read()
                f.close()
            except FileNotFoundError:
                result = OpenAI().responses.create(model = "gpt-5", input = command).output_text
                content = result
                f = open("data/" + folder + "/output" + task + ".txt", "w")
                f.write(content)
                f.close()
        else:
            result = OpenAI().responses.create(model = "gpt-5", input = command).output_text
            content = result
            f = open("data/" + folder + "/output" + task + ".txt", "w")
            f.write(content)
            f.close()

        first = False

        f = open("proposals.py", "w")
        f.write("""import importlib.util
import sys

def load_module(name: str, path: str):
    spec = importlib.util.spec_from_file_location(name, path)
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)

    return module

arc_types = load_module("arc_types", "arc-dsl/arc_types.py")
constants = load_module("constants", "arc-dsl/constants.py")
dsl = load_module("dsl", "arc-dsl/dsl.py")

from arc_types import *
from constants import *
from dsl import *

""")
        f.write(content)
        f.close()
        
        proposals = load_module("proposals", "proposals.py")
        functions = []
        
        for x in dir(proposals):
            f = getattr(proposals, x)

            if (type(f) is types.FunctionType and f.__name__.startswith("dsl")):
                functions.append(f)

        scoreFunctions = [size_cost, value_cost, pixel_overlap_cost, bounding_box_cost]
        totalScores = []

        for function in functions:
            score = [0] * len(scoreFunctions)

            for pair in taskPairs[0]:
                for i in range(0, len(scoreFunctions)):
                    score[i] += scoreFunctions[i](np.array(function(tuple(map(tuple, pair[0].tolist())))), pair[1])
                    
            scores.append([";".join(inspect.getsource(function).split("\n"))] + [str(x) for x in score] + [str(sum(score))])
            totalScores.append((function, sum(score)))

        scores = sorted(scores, key = lambda x: float(x[-1]))[:3]
        totalScores = sorted(totalScores, key = lambda x: x[1])

        dsl = inspect.getsource(totalScores[0][0])
        cost = totalScores[0][1]

    print(folder, task, "\n", dsl)

    return cost == 0

def test_task3c9b0459(): #Flip left/right and flip up/down
    processTask("training", "3c9b0459")

def test_task0d3d703e(): #Color mapping
    processTask("training", "0d3d703e")

def test_taskc909285e():
    processTask("training", "c909285e")

