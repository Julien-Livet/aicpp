import json
import numpy as np
import os
import re
import subprocess
import urllib.request

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

def splitCppArgs(arg_str: str):
    args = []
    depth = 0
    current = []

    for c in arg_str:
        if c == '<':
            depth += 1
        elif c == '>':
            depth -= 1
        elif c == ',' and depth == 0:
            args.append("".join(current).strip())
            current = []
            continue
        current.append(c)

    if current:
        args.append("".join(current).strip())

    return args

def splitTypeName(arg):
    parts = arg.rsplit(" ", 1)

    if len(parts) == 2 and parts[1].isidentifier():
        return parts[0], parts[1]

    return arg, None

def extractDeclaration(declaration: str):
    pattern = re.compile(
        r"""
        ^\s*
        (?P<ret>.+?)                  # return type (lazy)
        \s+
        (?P<name>[a-zA-Z_]\w*)        # function name
        \s*\(
            (?P<args>.*)
        \)
        \s*;
        \s*$
        """,
        re.VERBOSE,
    )

    return pattern.match(declaration)

def getFunctions():
    f = open("../include/aicpp/primitives.h", "r")
    content = f.read()
    f.close()

    declarations = []

    for line in content.split("\n"):
        s = line.strip()

        if (s.startswith("///")):
            declarations.append(s.replace("///", "").strip())

    functions = []

    for declaration in declarations:
        i = declaration.rfind("//")
        function = declaration[:i]
        description = declaration[i + 2:].strip()
        m = extractDeclaration(function)

        if (m):
            ret = m.group("ret")
            name = m.group("name")
            args = [splitTypeName(x) for x in splitCppArgs(m.group("args"))]

            functions.append((declaration, ret, name, args, description))

    return functions

def processTask(folder: str, task: str):
    functions = getFunctions()

    url = urllib.request.urlopen("https://raw.githubusercontent.com/arcprize/ARC-AGI-2/refs/heads/main/data/" + folder + "/" + task + ".json")
    data = json.loads(url.read().decode())

    modelName = "llama3.1"

    cost = None
    expression = ""

    while (cost is None or cost):
        command = "You are given several input-output grid pairs from an ARC task:\n"
        for i in range(len(data["train"])):
            command += "(" + json.dumps(data["train"][i]["input"]) + ", " + json.dumps(data["train"][i]["output"]) + ")\n"
        command += "\nYou are given several C++ function declarations as primitives:\n"
        for function in functions:
            command += function[0] + "\n"

        command += """
Your task is NOT to solve the ARC task directly.

You must help a symbolic program synthesis engine by generating
PARTIALLY PARAMETERIZED C++ FUNCTIONS based on the given primitives.

These functions must restrict the search space by fixing some parameters
(constants, sizes, colors, booleans, or structural choices),
while keeping other parameters free.

"""
        command += """A partially parameterized function:
- calls exactly ONE existing primitive function
- fixes one or more arguments to constant values
- exposes the remaining arguments as parameters
- does not introduce new logic
- does not combine multiple primitives

"""
        command += """Rules:
- Do NOT invent new primitive operations.
- Do NOT modify the body logic of primitives.
- Do NOT combine multiple primitives in a single function.
- Do NOT use loops, conditionals, or additional computations.
- Only generate function wrappers that call an existing function.

"""
        command += """Output example:
SELECTED_PRIMITIVES:
<verbatim function signatures>

PARTIAL_PARAMETERIZATIONS:
<zero or more C++ functions with unique identifiers>

DEPTH LEVEL:
<one number>

"""
        command += """Output format:
- Output ONLY valid C++ function declarations and definitions.
- No explanations.
- No comments.
- No markdown.
- No extra text.
- Each function must be standalone and compilable.

"""
        command += """Example:

Primitive:
int foo(int i, bool b);

Valid partial parameterizations:
int foo_i4(bool b) { return foo(4, b); }
int foo_i6(bool b) { return foo(6, b); }

Invalid:
int bar(int x) { return foo(x, true) + 1; }
int baz(int x) { if (x > 0) return foo(x, true); }

"""
        command += """Based on the observed input-output grid transformations,
identify constants or structural patterns that are likely invariant
across examples (such as fixed colors, fixed grid sizes,
specific region counts, or alignment directions).

Generate partial parameterizations that reflect these invariants.
"""
        command += """Generate at most 5 partial parameterizations per primitive.
Prefer fewer, higher-confidence specializations.

"""
        command += """If no reasonable partial parameterization can be inferred for a primitive,
do NOT generate any function for it.

"""
        command += """The symbolic engine will evaluate all generated functions exhaustively.
Do not attempt to rank, score, or select solutions.

"""
        command += """If a primitive already fully matches the observed transformation
without requiring any fixed parameter,
DO NOT generate any partial parameterization for it.

"""
        command += """Only generate a partial parameterization if it is expected
to significantly reduce the search depth or branching factor
compared to using the primitive directly

"""
        command += """Do not generate partial parameterizations for primitives
that do not have free scalar or structural parameters.

"""
        command += """Before outputting a function, ask yourself:
"Does this function restrict the domain of the primitive
more than calling the primitive directly?"
If the answer is no, do not output it.

"""
        command += """First, select which of the given primitives are potentially useful
for explaining the observed input-output transformations.

Output the selected primitives verbatim.

"""
        command += """Then, for each selected primitive, generate partial parameterizations
ONLY IF fixing parameters is likely to further reduce the search space.

"""
        command += """Finally, provide a integer number as the maximum depth level required
to combine the different primitives for the exploration engine.

"""
        command += """It is valid to select a primitive without generating any partial parameterization for it.

"""

        if (cost):
            command += "The best found connection from the engine has a cost of " + str(cost) + " and his expression is: " + expression + ".\n"

        f = open("prompt.txt", "w")
        f.write(command)
        f.close()
        cmd = ["ollama", "run", modelName, command]
        result = subprocess.run(cmd, capture_output = True, text = True)
        f = open("output.txt", "w")
        f.write(result.stdout)
        f.close()
        exit()
        lines = result.stdout.split("\n")
        
        f = open("../src/engine.cpp.in1", "r")
        engineContent = f.read()
        f.close()

        partialsContent = """#ifndef AICPP_PARTIALS_H
#define AICPP_PARTIALS_H

#include <any>
#include <vector>

#include "aicpp/primitives.h"

namespace aicpp
{
    namespace fulls
    {
"""
        i1 = lines.find("SELECTED_PRIMITIVES:") + 1

        for i in range(i1 + 1, i2):
            line = lines[i].strip()

            if (len(line)):
                pass #TODO: ...

        partialsContent += """    }

    namespace partials
    {
"""

        i2 = lines.find("PARTIAL_PARAMETERIZATIONS:")

        partialsContent += """    }
}

#endif // AICPP_PARTIALS_H
"""
        f = open("../include/aicpp/partials.h", "w")
        f.write(partialsContent)
        f.close()

        f = open("../src/engine.cpp.in2", "r")
        engineContent += f.read()
        f.close()
        
        f = open("../src/engine.cpp.in2", "r")
        f.write(engineContent)
        f.close()

        i3 = lines.find("DEPTH LEVEL:")
        level = int(lines[i3 + 1])
        
        result = subprocess.run(["cmake", "--build", "C:/Users/julie/Documents/GitHub/aicpp/build/vc143-Release", "--target all"], capture_output = True, text = True)
        
        if (result):
            continue
            
        result = subprocess.run(["C:/Users/julie/Documents/GitHub/aicpp/build/vc143-Release/engine.exe", folder, task, level], capture_output = True, text = True)
        lines = result.stdout.split("\n")
        cost = float(lines[0])
        expression = lines[1].strip()

    print(expression)

def main():
    processTask("training", "3c9b0459")

if (__name__ == "__main__"):
    main()

