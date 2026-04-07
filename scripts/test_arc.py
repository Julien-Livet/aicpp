import anthropic
import base64
from concurrent.futures import ThreadPoolExecutor
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
from tqdm import tqdm
import traceback

errors = set()
#llm = ("claude", "claude-sonnet-4-6")
#llm = ("gpt", "gpt-5")
llm = ("ollama", "gemma4:31b-cloud")
#llm = ("ollama", "gpt-oss:120b-cloud")

def ndarray_to_str_one_liner(arr):
    return '\n'.join(''.join(map(str, row)) for row in arr)

def callOllama(model: str, prompt: str, image: str = "") -> str:
    cmd = ["ollama", "run", model, prompt]

    if (len(image)):
        prompt = f"![Task image](data:image/png;base64,{image})\n\n" + prompt

    try:
        result = subprocess.run(cmd, capture_output = True, text = True)

        return result.stdout
    except FileNotFoundError as e:
        if (not str(e) in errors):
            print(e)

        errors.add(str(e))

        return ""

def callGpt(prompt: str, image: str = "", model: str = "gpt-5") -> str:
    try:
        if (len(image)):
            return OpenAI().responses.create(model = model, input = [
                {
                    "role": "user",
                    "content": [
                        {"type": "input_text", "text": prompt},
                        {
                            "type": "input_image",
                            "image_url": f"data:image/png;base64,{image}"
                        }
                    ]
                }
            ]).output_text
        else:
            return OpenAI().responses.create(model = model, input = prompt).output_text
    except OpenAIError as e:
        if (not str(e) in errors):
            print(e)

        errors.add(str(e))

        return ""

def callClaude(prompt: str, image: str = "", model: str = "claude-sonnet-4-6") -> str:
    try:
        budget_tokens = 8192
        max_tokens = 2 * budget_tokens
        thinking = "enabled"

        if (len(image)):
            response = anthropic.Anthropic().messages.create(model = model, max_tokens = max_tokens,
                                                         thinking = {"type": thinking, "budget_tokens": budget_tokens},
                                                         messages = [
                {
                    "role": "user",
                    "content": [
                        {
                            "type": "image",
                            "source": {"type": "base64", "media_type": "image/png", "data": image}
                        },
                        {"type": "text", "text": prompt}
                    ]
                }
            ])

            return "".join(block.text for block in response.content if block.type == "text")
        else:
            response = anthropic.Anthropic().messages.create(model = model, max_tokens = max_tokens,
                                                         thinking = {"type": thinking, "budget_tokens": budget_tokens},
                                                         messages = [
                {
                    "role": "user",
                    "content": prompt
                }
            ])

            return "".join(block.text for block in response.content if block.type == "text")
    except anthropic.APIError as e:
        if (not str(e) in errors):
            print(e)

        errors.add(str(e))

        return ""

def callLLM(prompt: str, image: str = "") -> str:
    match (llm[0]):
        case "claude":
            return callClaude(prompt, image, llm[1])
        case "gpt":
            return callGpt(prompt, image, llm[1])
        case "ollama":
            return callOllama(llm[1], prompt, image)

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
    assert(folder in ("training", "evaluation"))

    with open(f"../ARC-AGI-2/data/{folder}/{task}.json", "r") as file:
        data = json.loads(file.read())

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

def taskPrompt(trainPairs: list, withImages: bool) -> str:
    command = ""
    
    if (withImages):
        command += "The attached image describes the input grids in the left column and the output grids of an ARC task in the right column.\n\n"

    command += "# Input->output grid pairs of an ARC task\n\n"

    for i in range(len(trainPairs[0])):
        command += f"## train{i+1}\n\n"
        command += f"### Input\n\n```bash\n"
        command += ndarray_to_str_one_liner(trainPairs[0][i])
        command += f"\n```\n\n### Output\n\n```bash\n"
        command += ndarray_to_str_one_liner(trainPairs[1][i]) + "\n```\n\n"

    command += "# Available types\n\n"

    f = open("arc-dsl/arc_types.py", "r")
    content = f.read()
    f.close()
    
    command += "```python\n"
    command += content
    command += "```\n"

    command += "\n# Available variables\n\n"

    f = open("arc-dsl/constants.py", "r")
    content = f.read()
    f.close()
    
    command += "```python\n"
    command += "I: Tuple[Tuple]\n"
    command += "\n".join(filter(None, content.split("\n", ))) + "\n"
    command += "```\n"

    command += "\n# Available primitives\n\n"

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

def taskResults(source: str, pairs: list, label: str) -> tuple:
    assert(label in ("train", "test"))

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
        except (AttributeError, IndexError, KeyError, NameError, RecursionError, RuntimeError, StopIteration, SyntaxError, TimeoutError, TypeError, ValueError, ZeroDivisionError) as e:
            if (hasattr(e, "traceback")):
                tracebacks.add("```bash\n" + e.traceback + "```")

            score = [math.nan] * len(scoreFunctions)
            output = np.array(pair[0], dtype = float)
            np.ndarray.fill(output, np.nan)
            output = tuple(map(tuple, output))

        scores.append(score + [sum(score)])
        outputs.append(output)

    runner.terminate()

    df = pd.DataFrame(scores, index = [f"{label}{i+1}" for i in range(len(pairs))], columns = scoreColumns)

    return (df, outputs, tracebacks)

def outputPrograms(outputFile: str, pairs: list, step: str) -> list:
    assert(step in ("train", "test"))

    f = open(outputFile, "r")
    content = f.read()
    f.close()
    
    groups = re.findall(r'```python(.*?)```', content, flags = re.S)

    assert(len(groups))

    groups = re.findall(r'def (dsl\d)\(I\):\s*(.*?)(?=\ndef dsl\d|\Z)', groups[-1], re.S)

    assert(len(groups) == 5)

    programs = []

    for group in groups:
        dsl = f"def {group[0]}(I):\n    " + group[1].strip()
        programs.append((dsl, taskResults(dsl, pairs, step)))

    return programs

def processTask(folder: str, task: str, withImages: bool = False, debug: bool = True) -> list:
    taskPairs = trainTestPairs(folder, task)
    trainPairs = inputOutputPairs(taskPairs[0])
    image_base64 = ""

    if (withImages and os.path.exists(f"data/{folder}/{task}.png")):
        with open(f"data/{folder}/{task}.png", "rb") as f:
            image_base64 = base64.b64encode(f.read()).decode("utf-8")

    programs = []

    for i in range(0, 5):
        dsl = f"""def dsl{i+1}(I):
    O = I
    return O"""
        programs.append((dsl, taskResults(dsl, taskPairs[0], "train")))

    index = 0

    for file in os.listdir(f"data/{folder}"):
        if ("input" in file and task in file):
            index = max(index, int(file.replace(".md", "").replace(f"{task}-input-", "")))

    if (os.path.exists(f"data/{folder}/{task}-output-{index:03d}.md")):
        programs = outputPrograms(f"data/{folder}/{task}-output-{index:03d}.md", taskPairs[0], "train")
        index += 1
    elif (os.path.exists(f"data/{folder}/{task}-output-{index-1:03d}.md")):
        programs = outputPrograms(f"data/{folder}/{task}-output-{index-1:03d}.md", taskPairs[0], "train")

    arc_types_module = load_module("arc_types", "arc-dsl/arc_types.py")
    constants_module = load_module("constants", "arc-dsl/constants.py")
    dsl_module = load_module("dsl", "arc-dsl/dsl.py")

    env = {}
    env.update(vars(arc_types_module))
    env.update(vars(constants_module))
    env.update(vars(dsl_module))

    bestProgram = programs[0]

    for _ in range(0, 10):
        command = taskPrompt(trainPairs, withImages) + "\n"
        nanValues = False

        for i, program in enumerate(programs):
            command += f"# Program {i+1}\n"
            command += "## DSL\n"
            command += "```python\n"
            command += program[0] + "\n"
            command += "```\n"

            cost = program[1][0][scoreColumns[-1]].sum(skipna = False)
            bestCost = bestProgram[1][0][scoreColumns[-1]].sum(skipna = False)

            if (cost < bestCost):
                bestProgram = program
            elif (cost == bestCost and len(program[0]) < len(bestProgram[0])):
                bestProgram = program

            if (debug):
                print(f"Program {i+1}")
                print(program[1][0])
                print("Total cost", cost)
                print("Program length", len(program[0]))
                print("Program lines", len(program[0].split("\n")))

            command += "\n## Explosive scores\n\n"
            command += program[1][0].to_markdown() + "\n"
            command += "\n## Output grids\n\n"
            
            for i, output in enumerate(program[1][1]):
                if (np.any(np.isnan(output))):
                    continue

                command += f"### train{i+1} output\n\n```bash\n"
                command += ndarray_to_str_one_liner(output) + "\n```\n\n"

            if (len(program[1][2])):
                nanValues = True
                command += "\n## Tracebacks\n"
                command += "\n".join([str(x) for x in program[1][2]]) + "\n"

            command += "\n---\n\n"

        command += """The goal is to improve the 5 DSL programs incrementally in two phases:

--------------------------------
PHASE 1 — EXPANSION (DISCOVERY)
--------------------------------

- Analyze failures and identify missing spatial or relational patterns.
- Introduce new intermediate concepts using ONLY the provided DSL primitives.
- All transformations MUST be expressed as compositions of DSL primitives.
- Do NOT write imperative logic (loops, indexing, or manual grid traversal).
- Do NOT use global case distinctions based on grid-level properties.

Guidelines:
- Represent all structures as sets of indices or objects derived from the grid.
- Express behaviors as transformations over these sets.
- You may use multiple intermediate concepts, but each must be defined using DSL primitives.
- Avoid hardcoded positional logic or scanning patterns.

--------------------------------
PHASE 2 — REDUCTION (ABSTRACTION)
--------------------------------

- Identify structurally similar transformations.
- Merge them into higher-order transformations using apply, mapply, interval, etc.
- Reduce program length and number of concepts.

Guidelines:
- Merge only transformations that share the same structure.
- Prefer parameterized transformations over duplicated logic.
- Avoid unnecessary intermediate variables.

--------------------------------
STRICT DSL CONSTRAINTS
--------------------------------

- The final program MUST be written entirely using the provided DSL primitives.
- No Python control flow (if, for, while).
- No manual indexing (index, shape, etc.).
- No explicit loops or list comprehensions.
- No global grid analysis (e.g. "if a full row exists", "if checkerboard pattern exists").

--------------------------------
STRUCTURAL BIAS
--------------------------------

- Prefer local, compositional rules over global heuristics.
- Prefer transformations that operate uniformly across the grid.
- Avoid splitting the solution into unrelated cases.

--------------------------------
SEARCH STRATEGY
--------------------------------

- Maintain multiple candidate programs with different structural approaches.
- Vary:
    - how anchors are defined,
    - how propagation directions are constructed,
    - how masks are generated.
- Avoid reusing previously failed structural ideas.

--------------------------------
OBJECTIVE
--------------------------------

Among correct programs, prefer those that:
- use fewer concepts,
- are fully expressed in DSL primitives,
- and describe the transformation as a composition of local operations.

The program must use a single consistent rule to decide where to apply the transformation.
Do not combine multiple independent heuristics (parity, diagonal, density, etc.).
Choose ONE principle and apply it consistently.
Identify a single property that explains all training examples.
Use only that property to guide the transformation.
Remove any part of the program that does not strictly improve performance on all training examples.
Prefer shorter and simpler programs.
Try removing a component of the logic and check if performance improves.

If the transformation cannot be explained by a single local rule,
introduce a global structural property (e.g., symmetry, periodicity, alignment)
and branch on it.

Avoid reusing previously tried concepts such as:
- parity-based rules
- diagonal propagation
- run-length heuristics
unless they clearly solve all examples.

Prefer solutions that are:
1. correct on all training examples
2. simple
3. based on a single idea

Each program MUST belong to a different reasoning family:
1. Global transformation:
   - Apply operations like crop, compress, trim, downscale, symmetry
2. Object extraction:
   - Identify a subset of pixels (e.g., using ofcolor or object detection)
   - Extract a subgrid or bounding box from them
3. Color filtering:
   - Select or remove specific colors and reconstruct the output
4. Geometric reasoning:
   - Use symmetry, mirroring, alignment, or relative positions
5. Relational / structural reasoning:
   - Use relationships between parts (e.g., center, adjacency, repetition)

Constraints:
- Each program must use a DIFFERENT core strategy
- Avoid reusing the same sequence of operations
- Use the DSL primitives explicitly
- Avoid reusing the same core operators across candidates
- Each program should reflect a distinct hypothesis about the task

Ensure diversity across candidates by varying:
- global vs local processing (full grid vs subgrid)
- object-level vs pixel-level reasoning
- use vs avoidance of normalization / cropping

Programs should be short, clean, and compositional.
Prefer minimal and compositional programs.

Important:
Do NOT generate 5 variations of the same idea.

Before writing each program, explicitly choose a different reasoning strategy.

If two programs use similar primitives (e.g., both use compress + downscale),
they will be considered invalid.

If a program achieves zero cost on any training example,
you MUST preserve the underlying transformation responsible for that success.

Do NOT modify or destroy parts of the program that already perfectly solve a training example,
unless you can generalize them without increasing their cost.\n"""

        if (nanValues):
            command += "\nnan values correspond to exceptions that are explained by tracebacks and must be corrected by analyzing them.\n"

        command += """\nGenerate 5 new structurally diverse hypotheses of plausible DSL programs exploring different transformations issued from the step 2.

# EXPECTED OUTPUT EXAMPLE WITHOUT ANY FORMATTING AND ANY EXPLANATION
```python
def dsl1(I):
    # O = ...
    return O

def dsl2(I):
    # O = ...
    return O

def dsl3(I):
    # O = ...
    return O

def dsl4(I):
    # O = ...
    return O

def dsl5(I):
    # O = ...
    return O
```"""

        if (not bestProgram[1][0][scoreColumns[-1]].sum(skipna = False)):
            break

        if (index > 9):
            break

        f = open(f"data/{folder}/{task}-input-{index:03d}.md", "w")
        f.write(command)
        f.close()

        content = callLLM(command, image_base64)

        if (len(content) == 0):
            return [bestProgram[0], folder, task, "train"] + [bestProgram[1][0][x].sum(skipna = False) for x in scoreColumns]

        groups = re.findall(r'```python(.*?)```', content, flags = re.S)

        if (len(groups) == 0):
            content = f"```python\n{content}\n```"

        f = open(f"data/{folder}/{task}-output-{index:03d}.md", "w")
        f.write(content)
        f.close()

        programs = outputPrograms(f"data/{folder}/{task}-output-{index:03d}.md", taskPairs[0], "train")
        index += 1
    
    costs = [bestProgram[1][0][x].sum(skipna = False) for x in scoreColumns]

    if (costs[-1]):
        if (debug):
            print(" ".join(str(x) for x in [folder, task, "train"] + costs))
            print(bestProgram[1][0])
            print("Total cost", cost)
            print("Program length", len(bestProgram[0]))
            print("Program lines", len(bestProgram[0].split("\n")))
            print(bestProgram[0])

        return [bestProgram[0], folder, task, "train"] + costs

    testResults = taskResults(bestProgram[0], taskPairs[1], "test")
    costs = [testResults[0][x].sum(skipna = False) for x in scoreColumns]

    if (debug):
        print(" ".join(str(x) for x in [folder, task, "test"] + costs))
        print(testResults[0])
        print("Total cost", costs[-1])
        print("Program length", len(bestProgram[0]))
        print("Program lines", len(bestProgram[0].split("\n")))
        print(bestProgram[0])

    return [bestProgram[0], folder, task, "test"] + costs

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

def test_task90f3ed37():
    assert(processTask("training", "90f3ed37")[-1] == 0)

def test_task12422b43():
    assert(processTask("training", "12422b43")[-1] == 0)
""" #TODO: to remove
def test_task11dc524f():
    assert(processTask("training", "11dc524f", withImages = True)[-1] == 0)
""" #TODO: to remove
"""
def test_task():
    assert(processTask("training", "")[-1] == 0)
"""

def run_tasks(folder: str) -> tuple[int, int]:
    assert(folder in ("training", "evaluation"))

    with open(f"../ARC-AGI-2/data/{folder}.txt", "r") as file:
        data = file.read()

    tasks = data.split("\n")
    files = list(filter(lambda x: x.endswith(".md"), os.listdir(f"data/{folder}")))
    unexploredTasks = []

    for task in tasks:
        if (not any([task in x for x in files])):
            unexploredTasks.append(task)
    print(len(unexploredTasks))

    tasks = sorted(set(tasks) - set(unexploredTasks)) + sorted(unexploredTasks)
    tasks = tasks[:120] #TODO: to remove

    with ThreadPoolExecutor(max_workers = os.cpu_count()) as executor:
        results = list(tqdm(
            executor.map(lambda task: processTask(folder, task, withImages = False, debug = False), tasks),
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
""" #TODO: to remove
def test_evaluation_tasks():
    count, tasks = run_tasks("evaluation")

    print(f"{count}/{tasks} {count/tasks*100}% passed evaluation tasks")
""" #TODO: to remove