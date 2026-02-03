import copy
import json
import math
import numpy as np
import pyaicpp
import pytest
import re
import subprocess
import time
import urllib.request
import utils

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

def bestPrimitives(folder: str, task: str, connectionStr: str, cost: float) -> tuple[list[str], list[str]]:
    url = urllib.request.urlopen("https://raw.githubusercontent.com/arcprize/ARC-AGI-2/refs/heads/main/data/" + folder + "/" + task + ".json")
    data = json.loads(url.read().decode())

    modelName = "llama3.1"
    #modelName = "gemma3:27b-it-qat"

    file = open("primitives.py")
    content = file.read()
    file.close()

    verbProperties = {}
    
    lines = content.split("\n")
    index = 0
    
    while (index < len(lines) and not lines[index].startswith("Verb properties")):
        index += 1
    
    index += 1
    
    while (index < len(lines) and lines[index] != '"""'):
        i = lines[index].index(":")
        verbProperties[lines[index][:i]] = lines[index][i + 2:] 
        index += 1

    functions = []

    lines = content.split("\n")

    for line in lines:
        if (line.startswith("def ")):
            functions.append(line[len("def "):line.find("(")])

    import primitives

    descriptions = {}

    for function in functions:
        cmd = ["python", "-c", "import primitives; help(primitives." + function + ")"]
        result = subprocess.run(cmd, capture_output = True, text = True)

        functionLines = result.stdout.split("\n")

        for i in range(0, 2):
            del functionLines[0]
            del functionLines[-1]

        descriptions[function] = functionLines[-1].strip()

    selection = []

    for count in range(0, 5):
        verbs = set(np.unique([x.split()[0] for x in descriptions.values()]))
        selectedVerbs = []
        
        while (len(verbs) != 1):
            command = "You are given several input-output grid pairs from an ARC task.\n"
            
            #command += json.dumps(data["train"]) + "\n"
            for i in range(len(data["train"])):
                command += "(" + json.dumps(data["train"][i]["input"]) + ", " + json.dumps(data["train"][i]["output"]) + ")\n"

            command += """
    For EACH verb below, check whether it ENFORCES the following property:

    PROPERTY:
    "If this verb is the main abstraction, then this property MUST hold for ALL input-output pairs."

    If the property is violated by at least one example, the verb is INVALID.

    Verbs and their mandatory properties:
    """
            selectedProperties = dict(list(filter(lambda x: x[0] in verbs, verbProperties.items())))

            command += "\n".join(["- " + k + ": " + v for k, v in selectedProperties.items()]) + "\n"
            command += """
    Task:
    Select ONE verb whose mandatory property is violated.

    WITHOUT ANY FORMATTING, answer ONLY with the right verb name.
    Do NOT explain."""

            scores = {}

            for i in range(0, 5):
                cmd = ["ollama", "run", modelName, command]
                result = subprocess.run(cmd, capture_output = True, text = True)
                verb = result.stdout.strip()
                score = scores.get(verb, 0)
                score += 1
                scores[verb] = score
            #print("scores", scores)
            verb = sorted(scores.items(), key = lambda x: x[1])[-1][0]
            #print(verb)
            verbs.remove(verb)
            selectedVerbs.append(verb)
        
        selectedVerbs.append(verbs.pop())
        selectedVerbs = list(reversed(selectedVerbs))
        selection.append(tuple(selectedVerbs))

    hashes = [hash(x) for x in selection]
    un, count = np.unique(hashes, return_counts = True)
    i = count.tolist().index(max(count))

    selectedVerbs = []

    for x in selection:
        if (hash(x) == un[i]):
            selectedVerbs = x
            break
    print(selectedVerbs)
    functions = {}

    for k, v in descriptions.items():
        l = functions.get(v.split()[0], [])
        l.append(k)
        functions[v.split()[0]] = l

    selectedFunctions = []

    for verb in selectedVerbs:
        selectedFunctions.extend(functions[verb])
    print(selectedFunctions)
    return selectedFunctions, []

def updateRegionNeurons(regionNeurons: dict, pairs: list[np.ndarray]):
    regionMap = dict()

    for input_ in pairs:
        s = utils.regionSet(input_, False)

        regions = dict()

        for i in range(0, 10):
            regions[i] = []

        for r in s:
            regions[input_[r[0][0], r[0][1]]].append(r)

        for k, v in regions.items():
            l = regionMap.get(k, [])
            l.append(v)
            regionMap[k] = l

    for k, v in regionMap.items():
        function = lambda v = v: v

        emptyCount = 0

        for l in v:
            if (len(l) == 0):
                emptyCount += 1

        if (regionNeurons.get(k, None) == None):
            if (emptyCount != len(v)):
                regionNeurons[k] = pyaicpp.PyNeuron("region" + str(k), function, [], pyaicpp.type_index_from_name("list[list[list[tuple[int, int]]]]"))
        else:
            if (emptyCount != len(v)):
                regionNeurons[k].function = function
            else:
                del regionNeurons[k]

def processTask(folder: str, task: str) -> int:
    taskPairs = trainTestPairs(folder, task)
    trainPairs = inputOutputPairs(taskPairs[0])
    testPairs = inputOutputPairs(taskPairs[1])

    falseNeuron = pyaicpp.PyNeuron("False", lambda: False, [], pyaicpp.type_index_from_name("bool"))
    trueNeuron = pyaicpp.PyNeuron("True", lambda: True, [], pyaicpp.type_index_from_name("bool"))
    inputNeuron = pyaicpp.PyNeuron("input", lambda trainPairs = trainPairs: trainPairs[0], [], pyaicpp.type_index_from_name("list[numpy.ndarray]"))
    pairsNeuron = pyaicpp.PyNeuron("pairs", lambda v, taskPairs = taskPairs: [] if len(taskPairs[0]) != len(v) else [(v[i], taskPairs[0][i][1]) for i in range(0, len(taskPairs[0]))], [pyaicpp.type_index_from_name("list[numpy.ndarray]")], pyaicpp.type_index_from_name("list[tuple[numpy.ndarray, numpy.ndarray]]"))
    trainPairsNeuron = pyaicpp.PyNeuron("trainPairs", lambda taskPairs = taskPairs: taskPairs[0], [], pyaicpp.type_index_from_name("list[tuple[numpy.ndarray, numpy.ndarray]]"))

    digitNeurons = []

    for i in range(0, 10):
        digitNeurons.append(pyaicpp.PyNeuron(str(i), lambda i = i: i, [], pyaicpp.type_index_from_name("int")))

    connectionStr = "input"
    cost = pyaicpp.heuristic(trainPairs[0], trainPairs[1])

    while (cost):
        regionNeurons = dict()
        updateRegionNeurons(regionNeurons, trainPairs[0])

        neurons = [inputNeuron, falseNeuron, trueNeuron, pairsNeuron, trainPairsNeuron]

        for k, v in regionNeurons.items():
            neurons.append(v)

        digits = set()

        for m in trainPairs[0]:
            for v in m.reshape(m.size):
                digits.add(v)

        for m in trainPairs[1]:
            for v in m.reshape(m.size):
                digits.add(v)

        existingDigits = []

        for i in range(0, 10):
            existingDigits.append(i in digits)

        for i in range(0, len(digitNeurons)):
            if (existingDigits[i]):
                neurons.append(digitNeurons[i])

        #selectedPrimitives, definitions = bestPrimitives(folder, task, connectionStr, cost)
        selectedPrimitives = ["flipud", "fliplr"]

        import primitives

        for i in range(0, len(selectedPrimitives)):
            primitive = selectedPrimitives[i]
            function = getattr(primitives, primitive)
            annotations = copy.deepcopy(function.__annotations__)
            outputType = copy.deepcopy(annotations["return"])
            del annotations["return"]
            inputTypes = list(annotations.values())

            neurons.append(pyaicpp.PyNeuron(primitive, function,
                                            [pyaicpp.type_index_from_name(str(x).replace("<class '", "").replace("'>", "")) for x in inputTypes],
                                            pyaicpp.type_index_from_name(str(outputType).replace("<class '", "").replace("'>", ""))))

            b = pyaicpp.Brain(neurons)

            connections = b.learn([trainPairs[1]], level = 3)

            if (len(connections) == 0):
                continue

            connection = connections[0]
            connectionStr = connection.toStr()

            cost = pyaicpp.heuristic(connection.output(), trainPairs[1])

            if (cost):
                continue

            updateRegionNeurons(regionNeurons, testPairs[0]);

            inputNeuron.function = lambda testPairs = testPairs: testPairs[0]
            cost = pyaicpp.heuristic(connection.output(), testPairs[1])

            if (cost):
                continue

            break

    print(connectionStr)

def test_task3c9b0459(): #Flip left/right and flip up/down
    processTask("training", "3c9b0459")

def test_task0d3d703e(): #Color mapping
    processTask("training", "0d3d703e")

def test_task253bf280(): #Draw colored segment between pixels that have same x or y coordinates
    processTask("training", "253bf280")

