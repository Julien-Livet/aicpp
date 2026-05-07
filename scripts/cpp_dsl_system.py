with open("../include/aicpp/Hodel.h", "r") as f:
    lines = f.read().split("\n")

variableDefinitions = list(filter(lambda x: " = " in x, lines))
primitiveDefinitions = list(filter(lambda x: x.startswith("    std::any "), lines))

content = """#include "aicpp/DslSystem.h"
#include "aicpp/Hodel.h"

using namespace aicpp;

std::map<std::string, Neuron> aicpp::dslVariableNeurons()
{
    std::map<std::string, Neuron> neurons;

"""

for definition in variableDefinitions:
    definition = definition.strip()
    variableType = definition[:definition.index(" ")]
    affectationList = definition.split(" = ")
    spaceList = affectationList[0].split(" ")
    name = spaceList[-1]

    content += f'    neurons["{name}"]'
    content += " = Neuron{"
    content += f'"{name}"'
    content += ", [] (std::vector<std::any> const&) -> std::any { return hdl::"
    content += name
    content += "; }, std::vector<std::type_index>{}, typeid(hdl::"
    content += variableType
    content += ")};\n"

content += """
    return neurons;
}

std::map<std::string, Neuron> aicpp::dslPrimitiveNeurons()
{
    std::map<std::string, Neuron> neurons;

"""

for definition in primitiveDefinitions:
    definition = definition.strip()
    i1 = definition.index(" ")
    i2 = definition.index("(")
    name = definition[i1+1:i2]
    i1 = definition.index("//") + 2
    i2 = definition.rindex(":")
    signature = definition[i1:i2]
    comment = definition[i2+2:]
    i = signature.index("(")
    return_type = signature[:i]
    args = signature[i+1:signature.index(")")]
    arg_types = [x.strip() for x in args.split(",")]
    print(name)
    print(comment)
    print(signature)
    print(return_type)
    print(arg_types)
    args = [f"typeid(hdl::{x})" for x in arg_types]
    content += f'    neurons["{name}"]'
    content += " = Neuron{"
    content += f'"{name}"'
    content += f", hdl::{name}"
    content += ", std::vector<std::type_index>{"
    content += ", ".join(args)
    content += "}, typeid(hdl::"
    content += return_type
    content += ")};\n"

content += """
    return neurons;
}
"""

with open("../src/aicpp/DslSystem.cpp", "w") as f:
    f.write(content)

