from collections import defaultdict
import itertools

with open("../include/aicpp/Hodel.h", "r") as f:
    lines: list = f.read().split("\n")

typeDefinitions: list = list(filter(lambda x: x.strip().startswith("typedef "), lines))
variableDefinitions: list = list(filter(lambda x: " = " in x, lines))
primitiveDefinitions: list = list(filter(lambda x: x.strip().startswith("std::any "), lines))

dslTypes: dict = defaultdict(list)
nativeTypes: dict = {}

for definition in typeDefinitions:
    definition = definition.strip()
    dslType = definition[definition.rindex(" ")+1:-1]
    
    spaceList = definition.split(" ")
    nativeTypes[dslType] = " ".join(spaceList[1:-1])
    
    if (nativeTypes[dslType].startswith("std::variant<")):
        s = nativeTypes[dslType].replace("std::variant<", "").rstrip(">")
        dslTypes[dslType] += [x.strip() for x in s.split(",")]
    else:
        dslTypes[dslType].append(dslType)

frozenSetTypes = []

for k, v in nativeTypes.items():
    if (v.startswith("std::set") or v.startswith("std::vector")):
        frozenSetTypes += dslTypes[k]

dslTypes["FrozenSet"] = frozenSetTypes

containerTypes = dslTypes["FrozenSet"] + dslTypes["Grid"]

dslTypes["Container"] = containerTypes
dslTypes["Callable"] = ["std::function<std::any(std::vector<std::any> const&)>"]

anyTypes = []

for v in dslTypes.values():
    anyTypes += v

dslTypes["Any"] = anyTypes

for k in dslTypes.keys():
    dslTypes[k] = tuple(sorted(dslTypes[k]))

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

    content += f'    neurons.emplace("{name}"'
    content += ", Neuron{"
    content += f'"{name}"'
    content += ", [] (std::vector<std::any> const&) -> std::any { return hodel::"
    content += name
    content += "; }, std::vector<std::type_index>{}, typeid(hodel::"
    content += variableType
    content += ")});\n"

content += "\n"

for definition in primitiveDefinitions:
    definition = definition.strip()
    i1 = definition.index(" ")
    i2 = definition.index("(")
    name = definition[i1+1:i2]
    trueName = name

    if (trueName.endswith("_")):
        trueName = trueName[:-1]

    content += f'    neurons.emplace("{trueName}"'
    content += ", Neuron{"
    content += f'"{trueName}"'
    content += ", hodel::"
    content += name
    content += ", std::vector<std::type_index>{}, typeid(std::function<std::any(std::vector<std::any> const&)>)});\n"

content += """
    return neurons;
}

std::map<std::string, Neuron> aicpp::dslPrimitiveNeurons()
{
    std::map<std::string, Neuron> neurons;

"""

def typeName(x: str) -> str:
    if (x.startswith("std::")):
        return x.replace("std::vector<", "std::vector<hodel::")
    else:
        return "hodel::" + x

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

    pattern: list = [dslTypes[return_type]]

    for arg in arg_types:
        pattern.append(dslTypes[arg])

    unique: list = list(dict.fromkeys(map(id, pattern)))

    objects: dict = {id(lst): lst for lst in pattern}
    products: set = set()

    for vals in itertools.product(*(objects[i] for i in unique)):
        d: dict = dict(zip(unique, vals))
        products.add(tuple(d[id(lst)] for lst in pattern))

    products = sorted(products)

    for i, p in enumerate(products):
        if (p[0].startswith("std::function")):
            continue

        b = False

        for v in p[1:]:
            if (v.startswith("std::function")):
                b = True
                break

        if (b):
            continue

        trueName = name

        if (trueName.endswith("_")):
            trueName = trueName[:-1]

        n = trueName

        if (len(products) > 1):
            n += str(i)

        tt = [f"typeid({typeName(x)})" for x in p[1:]]

        content += f'    neurons.emplace("{n}"'
        content += ", Neuron{"
        content += f'"{trueName}"'
        content += f", hodel::{name}"
        content += ", std::vector<std::type_index>{"
        content += ", ".join(tt)
        content += "}, typeid("
        content += typeName(p[0])
        content += ")});\n"

content += """
    return neurons;
}
"""

with open("../src/aicpp/DslSystem.cpp", "w") as f:
    f.write(content)

