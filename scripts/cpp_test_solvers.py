import json
import re

commentedTasks: set = set()

def loadFolder(folder: str) -> dict:    
    with open(f"../ARC-AGI-2/data/{folder}.txt", "r") as f:
        taskIds = f.read().split("\n")
    
    data: dict = {}

    for id_ in taskIds:
        with open(f"../ARC-AGI-2/data/{folder}/{id_}.json") as f:
            data[id_] = json.load(f)
    
    return data

def processTask(task: str, data: dict, lines: str, functions: set) -> str:
    content: str = ""

    if (task in commentedTasks):
        content += "/*\n"
    else:
        content += "\n"

    content += f"TEST(ArcDslTest, {task})\n" + "{\n    std::vector<hodel::Grid> inputs, outputs;\n"

    trainPairs: list = [(ex["input"], ex["output"]) for ex in data["train"]]

    content += f"    inputs.reserve({len(trainPairs)});\n"
    content += f"    outputs.reserve({len(trainPairs)});\n"

    for i, o in trainPairs:
        content += "    inputs.emplace_back(hodel::Grid" + str(i).replace("[", "{").replace("]", "}") + ");\n"
        content += "    outputs.emplace_back(hodel::Grid" + str(o).replace("[", "{").replace("]", "}") + ");\n"

    content += """
    Neuron iNeuron{"I", [&inputs] (std::vector<std::any> const&) -> std::any { return inputs[0]; }, {}, typeid(hodel::Grid)};
"""

    content += "    Connection const I{iNeuron, {}};\n"

    symbols: list = []

    for line in lines:
        l = line.split(" = ")
        symbols.append((l[0].strip(), l[1]))

    onlySymbols = {s for s, _ in symbols}
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

        content += f"    auto const {rightSymbol}" + '{buildConnection("' + symbol + '", {})};\n'

    symbols = dict(symbols)

    for symbol, definition in symbols.items():
        l = definition.split("(")
        s = l[1].replace(")", "")

        s = s.replace("double", "double_").replace("switch", "switch_")

        rightSymbol = symbol
        
        if (symbol in ("double", "switch")):
            rightSymbol += "_"

        if (l[0] in functions):
            content += f"    auto const {rightSymbol}" + '{buildConnection("' + l[0] + '"'
            content += ", {" + s + "})}"
        else:
            content += f"    auto const {rightSymbol}{{std::any_cast<hodel::Callable>({l[0]}.output())({{{s}.output()}})}};"

        content += ";\n"

    content += f"""
    for (size_t i = 0; i < {len(trainPairs)}; ++i)\n"""
    content += """    {
        iNeuron.function() = [&inputs, i] (std::vector<std::any> const&) -> std::any { return inputs[i]; };
        EXPECT_TRUE(outputs[i] == std::any_cast<hodel::Grid>(O.output()));
    }
"""

    content += "}\n"

    if (task in commentedTasks):
        content += "*/\n"

    return content

if (__name__ == "__main__"):
    data: dict = loadFolder("training")

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

    content: str = """#include <gtest/gtest.h>

#include "aicpp/Connection.h"
#include "aicpp/HodelDslSystem.h"
#include "aicpp/Hodel.h"

using namespace aicpp;

std::map<std::string, Neuron> const variableNeurons{hodelDslVariableNeurons()};
std::map<std::string, Neuron> const primitiveNeurons{hodelDslPrimitiveNeurons()};

Connection buildConnection(std::string const& name, std::vector<std::any> const& args)
{
    if (args.empty())
    {
        for (auto const& [n, neuron] : variableNeurons)
        {
            if (neuron.name() == name)
            {
                try
                {
                    Connection const connection{neuron, args};

                    return connection;
                }
                catch (std::exception const&)
                {
                }
            }
        }
    }

    for (auto const& [n, neuron] : primitiveNeurons)
    {
        if (neuron.name() == name)
        {
            try
            {
                Connection const connection{neuron, args};

                return connection;
            }
            catch (std::exception const&)
            {
            }
        }
    }

    throw std::runtime_error{"Wrong connection"};
}

"""

    for id_, lines in tasks.items():
        content += processTask(id_, data[id_], lines, functions)

    with open("../src/test_solvers.cpp", "w") as f:
        f.write(content)
