from collections import defaultdict
import itertools
import sys

dslName = sys.argv[-1]

with open(f"../include/aicpp/{dslName}.h", "r") as f:
    lines: list = f.read().split("\n")

typeDefinitions: list = list(filter(lambda x: x.strip().startswith("typedef "), lines))
variableDefinitions: list = list(filter(lambda x: " = " in x, lines))
primitiveDefinitions: list = list(filter(lambda x: x.strip().startswith("//"), lines))

dslTypes: dict = defaultdict(list)
nativeTypes: dict = {}

for definition in typeDefinitions:
    definition = definition.strip()
    dslType = definition[definition.rindex(" ")+1:-1]
    
    spaceList = definition.split(" ")
    nativeTypes[dslType] = " ".join(spaceList[1:-1])
    
    if (nativeTypes[dslType].startswith("std::variant<")):
        s = nativeTypes[dslType].replace("std::variant<", "").rstrip(">")
        types = [x.strip() for x in s.split(",")]

        for t in types:
            if (t in dslTypes):
                dslTypes[dslType] += dslTypes[t]
            else:    
                dslTypes[dslType].append(t)
    elif (nativeTypes[dslType].startswith("std::tuple")):
        s = nativeTypes[dslType].replace("std::tuple<", "").rstrip(">")
        types = [x.strip() for x in s.split(",")]

        for t in types:
            if (t in dslTypes):
                dslTypes[dslType] += dslTypes[t]
            else:
                dslTypes[dslType].append(t)
    else:
        if (nativeTypes[dslType] in dslTypes):
            dslTypes[dslType] += dslTypes[nativeTypes[dslType]]
        else:
            dslTypes[dslType].append(dslType)

for k in dslTypes.keys():
    dslTypes[k] = tuple(sorted(dslTypes[k]))

content = f'#include "aicpp/{dslName}DslSystem.h"' + """
#include "aicpp/""" + dslName + """.h"

using namespace aicpp;

std::map<std::string, Neuron> aicpp::""" + f'{dslName.lower()}DslVariableNeurons()' + """
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
    content += ", [] (std::vector<std::any> const&) -> std::any { return " + dslName.lower() + "::"
    content += name
    content += "; }, std::vector<std::type_index>{}, typeid(" + dslName.lower() + "::"
    content += variableType
    content += ")});\n"

content += "\n"

addedNames = set()

for definition in primitiveDefinitions:
    definition = definition.strip()
    i1 = definition.index(" ")
    i2 = definition.index("(")
    name = definition[i1+1:i2]

    if (name in addedNames):
        continue

    addedNames.add(name)

    trueName = name

    if (trueName.endswith("_")):
        trueName = trueName[:-1]

    content += f'    neurons.emplace("{trueName}"'
    content += ", Neuron{"
    content += f'"{trueName}"'
    content += ", [] (std::vector<std::any> const&) -> std::any { return std::function<std::any(std::vector<std::any> const&)>(" + dslName.lower() + "::"
    content += name
    content += "); }, std::vector<std::type_index>{}, typeid(std::function<std::any(std::vector<std::any> const&)>)});\n"

content += """
    return neurons;
}

""" + f'std::map<std::string, Neuron> aicpp::{dslName.lower()}DslPrimitiveNeurons()' + """
{
    std::map<std::string, Neuron> neurons;

"""

def typeName(x: str) -> str:
    if (x.startswith("std::vector")):
        return x.replace("std::vector<", f"std::vector<{dslName.lower()}::")
    elif (x.startswith("std::set")):
        return x.replace("std::set<", f"std::set<{dslName.lower()}::")
    else:
        return f"{dslName.lower()}::" + x

indices: dict = {}

for definition in primitiveDefinitions:
    definition = definition.strip()
    return_type = definition[len("//"):definition.index(" ")]
    i = definition.index("(")
    name = definition[definition.index(" ")+1:i]
    args = definition[i+1:definition.index(")")]
    arg_types = [x.strip() for x in args.split(",")]

    pattern: list = []
    returnArgs: list = []

    for k in dslTypes:
        if (k in return_type):
            returnArgs.append(k)

    for arg in returnArgs:
        pattern.append(dslTypes[arg])

    args: list = []

    for arg in arg_types:
        for k in dslTypes:
            if (k in arg):
                args.append(k)

    for arg in args:
        pattern.append(dslTypes[arg]) 

    unique: list = list(dict.fromkeys(map(id, pattern)))

    objects: dict = {id(lst): lst for lst in pattern}
    products: set = set()

    for vals in itertools.product(*(objects[i] for i in unique)):
        d: dict = dict(zip(unique, vals))
        products.add(tuple(d[id(lst)] for lst in pattern))

    products = sorted(products)

    for i, p in enumerate(products):
        trueName = name

        if (trueName.endswith("_")):
            trueName = trueName[:-1]

        n = trueName
        n += str(indices.get(name, 0) + i)

        tt: list = []

        for x, y, z in zip(arg_types, args, p[1:]):
            tt.append(f"typeid({x.replace(y, typeName(z))})")

        content += f'    neurons.emplace("{n}"'
        content += ", Neuron{"
        content += f'"{trueName}"'
        content += f", {dslName.lower()}::{name}"
        content += ", std::vector<std::type_index>{"
        content += ", ".join(tt)
        content += "}, typeid("
        content += return_type.replace(returnArgs[0], typeName(p[0]))
        content += ")});\n"

    indices[name] = indices.get(name, 0) + i + 1

content += """
    return neurons;
}
"""

with open(f"../src/aicpp/{dslName}DslSystem.cpp", "w") as f:
    f.write(content)

