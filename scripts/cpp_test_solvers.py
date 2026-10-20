import json
import re

commentedTasks: set = {'9af7a82c', 'a64e4611', '7447852a', 'aba27056', 'f8ff0b80', 'eb5a1d5d', '6cf79266', 'd89b689b', '484b58aa', 'a85d4709', 'f15e1fac', 'e509e548', '4093f84a', '1e32b0e9', 'beb8660c', 'e73095fd', '53b68214', '05269061', 'a65b410d', 'd9f24cd1', '5168d44c', 'ff805c23', 'e21d9049', '50846271', '85c4e7cd', '6a1e5592', '6cdd2623', '4290ef0e', '760b3cac', '3befdf3e', '0e206a2e', '75b8110e', '363442ee', 'ae3edfdc', '8d510a79', '253bf280', '4be741c5', '3f7978a0', 'fcc82909', 'a5f85a15', '23581191', '5c2c9af4', 'de1cd16c', 'ef135b50', '82819916', '28e73c20', '952a094c', '49d1d64f', '11852cab', '5521c0d9', 'd6ad076f', 'e26a3af2', '868de0fa', '321b1fc6', '137eaa0f', '1caeab9d', '8e1813be', '9aec4887', '2c608aff', 'e9614598', '93b581b8', '08ed6ac7', '91413438', '746b3537', '6ecd11f4', 'db3e9e38', '6b9890af', '22168020', '025d127b', '72322fa7', '99fa7670', 'b7249182', '3e980e27', 'c8cbb738', '228f6490', '06df4c85', '29623171', 'b0c4d837', 'bbc9ae5d', '2281f1f4', '941d9a10', 'f8b3ba0a', '6e82a1ae', '77fdfe62', 'db93a21d', '1f642eb9', 'eb281b96', '0a938d79', '8403a5d5', '623ea044', 'c0f76784', '3bdb4ada', 'a78176bb', 'f8a8fe49', '56dc2b01', '963e52fc', 'f8c80d96', '29c11459', 'a8d7556c', 'e6721834', '8eb1be9a', 'af902bf9', '8e5a5113', '846bdb03', 'bda2d7a6', '508bd3b6', '3345333e', '83302e8f', 'a87f7484', 'ff28f65a', '4522001f', '1190e5a7', 'cdecee7f', 'cbded52d', 'e40b9e2f', '54d82841', 'd4f3cd78', '1b60fb0c', 'f1cefba8', '36d67576', '2204b7a8', '5daaa586', 'ddf7fa4f', '3eda0437', '2dd70a9a', '7ddcd7ec', 'b190f7f5', '694f12f3', '3428a4f5', 'a61ba2ce', '780d0b14', 'e76a88a6', '1f0c79e5', 'a3325580', 'e48d4e1a', '6aa20dc0', '8a004b2b', 'e5062a87', 'ce602527', 'b230c067', '4938f0c2', '6773b310', 'a1570a43', '72ca375d', 'bc1d5164', '6855a6e4', '6c434453', '95990924', 'b527c5c6', '264363fd', '5ad4f10b', '88a62173', 'ba26e723', '673ef223', '97a05b5b', 'dc433765', '6d0160f0', '2bee17df', '09629e4f', 'd4469b4b',
"feca6190",
"97999447",
"ecdecbb3",
"90f3ed37",
"ec883f72",
"e8dc4411",
"272f95fa",
"caa06a1f",
"f9012d9b",
"a48eeaf7",
"995c5fa3",
"d06dbe63",
"36fdfd69",
"045e512c",
"855e0971",
"447fd412",
"2bcee788",
"98cf29f8",
"469497ad",
"39e1d7f9",
"57aa92db",
"d07ae81c",
"d22278a0",
"150deff5",
"9d9215db",
"7df24a62",
"234bbc79",
"22233c11",
"7837ac64",
"a8c38be5",
"b775ac94",}

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

    content += f"TEST(ArcDslTest, {task})\n" + "{\n    std::vector<hodel::GridType> inputs, outputs;\n"

    trainPairs: list = [(ex["input"], ex["output"]) for ex in data["train"]]

    content += f"    inputs.reserve({len(trainPairs)});\n"
    content += f"    outputs.reserve({len(trainPairs)});\n"

    for i, o in trainPairs:
        content += "    inputs.emplace_back(hodel::GridType" + str(i).replace("[", "{").replace("]", "}") + ");\n"
        content += "    outputs.emplace_back(hodel::GridType" + str(o).replace("[", "{").replace("]", "}") + ");\n"

    content += """
    Neuron iNeuron{"I", [&inputs] (std::vector<std::any> const&) -> std::any { return inputs[0]; }, {}, typeid(hodel::GridType)};
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
        EXPECT_TRUE(outputs[i] == std::any_cast<hodel::GridType>(O.output()));
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
