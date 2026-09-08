import json
import re

def loadFolder(folder: str) -> dict:    
    with open(f"../ARC-AGI-2/data/{folder}.txt", "r") as f:
        taskIds = f.read().split("\n")
    
    data: dict = {}

    for id_ in taskIds:
        with open(f"../ARC-AGI-2/data/{folder}/{id_}.json") as f:
            data[id_] = json.load(f)
    
    return data

def processTask(task: str, lines: str, functions: set) -> str:
    content: str = "{\n    //" + task + "\n\n    Connection const I{iNeuron, {}};\n"

    symbols = set()

    for line in lines:
        l = line.split(" = ")
        symbols.add((l[0].strip(), l[1]))

    indices: dict = {}
    
    for symbol, _ in symbols:
        for i, line in enumerate(lines):
            if (symbol in line):
                indices[symbol] = i
                break
    
    indices["O"] = len(lines) - 1
    indices = sorted(indices.items(), key = lambda x: x[1])

    onlySymbols = set(s for s, _ in symbols)
    otherSymbols = set()

    for line in lines:
        s = line.split(" = ")[1].replace(")", "")
        l = s.split("(")[1].split(", ")

        for v in l:
            if (not v in onlySymbols):
                otherSymbols.add(v)

    otherSymbols = sorted(otherSymbols)

    for symbol in otherSymbols:
        if (symbol == "I"):
            continue

        content += f"    Connection const {symbol}" + '{variables.at("' + symbol + '"), {}};\n'

    symbols = dict(symbols)

    for symbol, _ in indices:
        l = symbols[symbol].split("(")
        s = l[1].replace(")", "")
        
        if (l[0] in functions):
            content += f"    Connection const {symbol}" + '{primitives.at("' + l[0] + 'X")'
            content += ", {" + s + "}}"
        else:
            content += f"    Connection {symbol}" + "{" + l[0] + "};\n"
            content += f"    {symbol}.applyInputs(" + "{" + s + "})"

        content += ";\n"

    content += "}\n"

    return content

if (__name__ == "__main__"):
    data: dict = loadFolder("training")
    data.update(loadFolder("evaluation"))

    with open("arc-dsl/solvers.py", "r") as f:
        content = f.read()

    pattern = r"def solve_([a-f0-9]+)\(I\):\n(.*?)^\s*return\b.*?$"
    
    matches = re.finditer(pattern, content, re.MULTILINE | re.DOTALL)

    tasks: dict = {}

    for match in matches:
        id_ = match.group(1)
        
        if (id_ in data):
            tasks[id_] = match.group(2).strip().split("\n")

    with open("arc-dsl/dsl.py", "r") as f:
        lines = f.read().split("\n")

    functions = set()

    for line in lines:
        if (line.startswith("def ")):
            functions.add(line.split("(")[0].replace("def ", ""))

    content: str = ""

    for id_, lines in tasks.items():
        content += processTask(id_, lines, functions)

    print(content)
