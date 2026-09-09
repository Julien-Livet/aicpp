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

def processTask(task: str, data: dict, lines: str, functions: set) -> str:
    content: str = "{\n    //" + task + "\n\n    std::vector<hodel::GridType> grids;\n"

    trainPairs: list = [(ex["input"], ex["output"]) for ex in data["train"]]

    content += f"    grids.reserve({len(trainPairs)});\n"

    for i, _ in trainPairs:
        content += "    grids.emplace_back(hodel::GridType" + str(i).replace("[", "{").replace("]", "}") + ");\n"

    content += "    grids_.emplace_back(grids);\n\n"
    content += '    iNeurons_.emplace_back("I", [] (std::vector<std::any> const&) -> std::any { return std::any{}; }, std::vector<std::type_index>{}, typeid(hodel::GridType));\n'
    content += "    Connection const I{iNeurons_.back(), {}};\n"

    symbols = list()

    for line in lines:
        l = line.split(" = ")
        symbols.append((l[0].strip(), l[1]))

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

        rightSymbol = symbol
        
        if (symbol in ("double", "switch")):
            rightSymbol += "_"

        content += f"    Connection const {rightSymbol}" + '{variableNeurons_.at("' + symbol + '"), {}};\n'

    symbols = dict(symbols)

    for symbol, definition in symbols.items():
        l = definition.split("(")
        s = l[1].replace(")", "")

        s = s.replace("double", "double_").replace("switch", "switch_")

        rightSymbol = symbol
        
        if (symbol in ("double", "switch")):
            rightSymbol += "_"

        if (l[0] in functions):
            content += f"    Connection const {rightSymbol}" + '{buildConnection("' + l[0] + '"'
            content += ", {" + s + "})}"
        else:
            content += f"    Connection const {rightSymbol}" + '{buildConnection("lbind"'
            content += ", {" + l[0] + ", " + s + "})}"

        content += ";\n"

    content += "\n    connections_.emplace_back(O);\n}\n\n"

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
        content += processTask(id_, data[id_], lines, functions)

    print(content)
