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
    content: str = f"TEST(ArcDslTest, {task})\n" + "{\n    std::vector<hodel::Grid> inputs, outputs;\n"

    trainPairs: list = [(ex["input"], ex["output"]) for ex in data["train"]]

    content += f"    inputs.reserve({len(trainPairs)});\n"
    content += f"    outputs.reserve({len(trainPairs)});\n"

    for i, o in trainPairs:
        content += "    inputs.emplace_back(hodel::Grid" + str(i).replace("[", "{").replace("]", "}") + ");\n"
        content += "    outputs.emplace_back(hodel::Grid" + str(o).replace("[", "{").replace("]", "}") + ");\n"

    content += """
    auto const iFunction{[] () -> hodel::Grid { return hodel::Grid{}; }};
    aicpp::Neuron<hodel::Grid> iNeuron{"I", iFunction};
"""

    content += "    Connection const I{&iNeuron, {}};\n"

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

        content += f"    Connection const {rightSymbol}" + '{buildConnection("' + symbol + '", {})};\n'

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

    content += f"""
    for (size_t i = 0; i < {len(trainPairs)}; ++i)\n"""
    content += """    {
        iNeuron.function() = [inputs, i] () -> hodel::Grid { return inputs[i]; };
        EXPECT_TRUE(outputs[i] == std::any_cast<hodel::Grid>(O.output()));
    }
"""

    content += "}\n\n"

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
#include "aicpp/Hodel.h"
#include "aicpp/HodelRegister.h"
#include "aicpp/PolymorphicNeuron.h"

using namespace aicpp;

static auto const registry = makeNeuronRegistry();

aicpp::NeuronBase const* findNeuron(DslType const& expected)
{
    auto it = std::find_if(
        registry.begin(),
        registry.end(),
        [&expected](auto const& entry)
        {
            return !entry.second->isPolymorphic()
                && entry.second->signature() == expected;
        });

    if (it == registry.end())
    {
        throw std::runtime_error(
            "Neuron not found for expected signature");
    }

    return it->second;
};

Connection buildConnection(
    std::string const& name,
    std::vector<std::any> const& args)
{
    DslType::Inputs argumentTypes;
    argumentTypes.reserve(args.size());

    for (auto const& arg : args)
    {
        if (arg.type() != typeid(Connection))
        {
            throw std::invalid_argument(
                "Arguments must be connections");
        }

        argumentTypes.push_back(
            std::any_cast<Connection const&>(arg).signature());
    }

    for (auto const& [_, neuron] : registry)
    {
        if (neuron->name() != name)
            continue;

        if (neuron->isPolymorphic())
        {
            auto const* polymorphic =
                dynamic_cast<PolymorphicNeuron const*>(neuron);

            if (polymorphic == nullptr)
                continue;

            try
            {
                polymorphic->inferSignature(argumentTypes);
                return Connection{neuron, args};
            }
            catch (std::exception const&)
            {
                continue;
            }
        }

        if (neuron->inputTypes().size() != args.size())
            continue;

        bool compatible = true;

        for (size_t i = 0; i < args.size(); ++i)
        {
            auto const& connection =
                std::any_cast<Connection const&>(args[i]);

            auto const expectedType = neuron->inputTypes()[i];

            if (expectedType == typeid(FunctionValue))
            {
                compatible = connection.signature().isFunction();
            }
            else
            {
                compatible =
                    connection.neuron()->returnType() == expectedType;
            }

            if (!compatible)
                break;
        }

        if (compatible)
            return Connection{neuron, args};
    }

    throw std::runtime_error{
        "No compatible connection found for neuron: " + name
    };
}

"""

    for id_, lines in tasks.items():
        content += processTask(id_, data[id_], lines, functions)

    with open("../src/test_solvers.cpp", "w") as f:
        f.write(content)
