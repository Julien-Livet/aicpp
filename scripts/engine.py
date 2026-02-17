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

    modelName = "gpt-oss:20b"

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
        command += """Output format:
- Output ONLY valid C++ function declarations and definitions.
- No explanations.
- No formatting.
- No comments.
- No markdown.
- No extra text.
- Each function must be standalone and compilable.
- Use types explictly and no initializer lists.

"""
        command += """Examples of full verbatim function declarations:
int foo(int i, bool b);
std::map<int, int> inferColorMapping(std::vector<std::pair<Eigen::MatrixXi, Eigen::MatrixXi>> arg0);

"""
        command += """Example:

Primitives:
int foo(int arg0, bool arg1);
std::map<int, int> bar(int arg0, double arg1);

Valid partial parameterizations:
int foo_i4(bool arg1) { return foo(4, arg1); }
int foo_i6(bool v) { return foo(6, arg1); }
std::map<int, int> bar_d1(int arg0) { return bar(arg0, 1.0); }
std::map<int, int> bar_d2(int arg0) { return bar(arg0, 2.0); }

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

Output the selected primitive declarations verbatim.

"""
        command += """Then, for each selected primitive, generate partial parameterizations
ONLY IF fixing parameters is likely to further reduce the search space.

"""
        command += """Finally, provide a integer number as the maximum depth level required
to combine the different primitives for the exploration engine.

"""
        command += """It is valid to select a primitive without generating any partial parameterization for it.

"""
        command += """Useful utility functions for type conversions:
std::vector<std::pair<Eigen::MatrixXi, Eigen::MatrixXi> > utility::matrixPairs(std::initializer_list<std::initializer_list<std::initializer_list<int> > > const& values);
std::vector<Eigen::MatrixXi> utility::matrices(std::initializer_list<std::initializer_list<std::initializer_list<int> > > const& values);

"""

        if (cost):
            command += "The best found connection from the engine has a cost of " + str(cost) + " and his expression is: " + expression + ".\n\n"

        command += """EXPECTED OUTPUT EXAMPLE WITHOUT ANY FORMATTING AND ANY EXPLANATIONS:
SELECTED_PRIMITIVES:
int foo(int arg0, bool arg1);
std::map<int, int> bar(int arg0, double arg1);

PARTIAL_PARAMETERIZATIONS:
int foo_i4(bool arg1) { return foo(4, arg1); }
int foo_i6(bool arg1) { return foo(6, arg1); }
std::map<int, int> bar_d1(int arg0) { return bar(arg0, 1.0); }
std::map<int, int> bar_d2(int arg0) { return bar(arg0, 2.0); }

DEPTH_LEVEL:
2"""

        f = open("prompt" + task + ".txt", "w")
        f.write(command)
        f.close()

        if (False):#try:
            f = open("output" + task + ".txt", "r")
            content = f.read()
            f.close()
        else:#except FileNotFoundError:
            result = subprocess.run(["ollama", "run", modelName, command], capture_output = True, text = True)
            content = result.stdout
            f = open("output" + task + ".txt", "w")
            f.write(content)
            f.close()

        lines = [x.strip() for x in content.split("\n")]

        partialsContent = """#ifndef AICPP_PARTIALS_H
#define AICPP_PARTIALS_H

#include <any>
#include <map>
#include <vector>

#include "aicpp/primitives.h"
#include "aicpp/utility.h"

namespace aicpp
{
    namespace specifics
    {
"""
        for function in functions:
            partialsContent += "        inline std::any " + function[2] + "(" + ", ".join([x + " const& " + y for x, y in function[3]]) + ")\n"
            partialsContent += "        {\n"
            partialsContent += "            return primitives::" + function[2] + "(std::vector<std::any>{" + ", ".join(["arg" + str(i) for i in range(0, len(function[3]))]) + "});\n"
            partialsContent += "        }\n"
            partialsContent += "\n"

        partialsContent += """    }

    namespace fulls
    {
"""
        i1 = len(lines) - lines[-1::-1].index("SELECTED_PRIMITIVES:") - 1
        i2 = len(lines) - lines[-1::-1].index("PARTIAL_PARAMETERIZATIONS:") - 1
        i3 = -1

        for i in range(i2 + 1, len(lines)):
            if (lines[i].startswith("DEPTH_LEVEL:")):
                i3 = i
                
                w = lines[i3].split()
                
                if (len(w) == 2):
                    level = int(w[1])
                else:
                    level = int(lines[i3 + 1])

                break

        table = {}

        for function in functions:
            key = function[1] + " " + function[2] + "(" + ", ".join([x + " " + y for x, y in function[3]]) + ");"
            table[key] = function

        f = open("../src/engine.cpp.in1", "r")
        engineContent = f.read()
        f.close()

        for i in range(i1 + 1, i2):
            line = lines[i].strip()

            if (len(line)):
                try:
                    function = table[line]
                    name = function[2]
                    partialsContent += "        using primitives::" + name + ";\n"
                    engineContent += "    Neuron " + name + '_neuron{"' + name + '", fulls::' + name + ", {" + ", ".join(["typeid(" + x + ")" for x, y in function[3]]) + "}, typeid(" + function[1] + ")};\n"
                    engineContent += "    neurons.emplace_back(" + name + "_neuron);\n";
                except KeyError:
                    pass

        partialsContent += """    }

    namespace partials
    {
        using namespace specifics;

"""

        table = {}

        for function in functions:
            table[function[2]] = function

        i = i2 + 1

        while (i < i3):
            line = lines[i].strip()
                
            i += 1

            if (len(line)):
                try:
                    index = line.index("{")
                except ValueError:
                    index = -1

                m = extractDeclaration(line[:index].strip() + ";")

                if (not m):
                    continue

                ret = m.group("ret")
                name = m.group("name")
                args = [splitTypeName(x) for x in splitCppArgs(m.group("args"))]
            
                l = line[index + 1:].strip()
                body = ""

                while (i < len(lines) and not l.endswith("}")):
                    if (len(l.strip())):
                        body += l + "\n"

                    i += 1
                    l = lines[i]

                body += l[:-1]

                """
                partialsContent += "        inline std::any " + name + "(std::vector<std::any> const& args)\n"
                partialsContent += "        {\n"

                for j, (x, y) in enumerate(table[name[:name.index("_")]][3]):
                    partialsContent += "            auto const arg" + str(j) + "{std::any_cast<" + x + ">(args[" + str(j) + "])};\n"                    
                
                partialsContent += "        \n"
                partialsContent += "            " + body
                partialsContent += "        }\n\n"
                
                engineContent += "    Neuron " + name + '_neuron{"' + name + '", partials::' + name + ", {" + ", ".join(["typeid(" + x + ")" for x, y in args]) + "}, typeid(" + ret + ")};\n"  
                engineContent += "    neurons.emplace_back(" + name + "_neuron);\n";
                """

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
        
        f = open("../src/engine.cpp", "w")
        f.write(engineContent)
        f.close()
        
        path = os.path.abspath(os.getcwd() + "/..")

        nproc = os.cpu_count()

        docker_cmd = [
            "docker", "run", "--rm",
            "-v", f"{path}:/app/aicpp",
            "aicpp", "-c",
            "mkdir -p build && "
            "cmake . -B build && "
            f"cmake --build build --target engine -- -j$(nproc)"
        ]
        
        result = subprocess.run(docker_cmd, capture_output = True, text = True)

        if (result.returncode):
            print("CMake result", result.returncode)
            print("CMake error", result.stderr)
            print("CMake output", result.stdout)
            continue

        cmd = [
            "./../build/engine",
            folder, task, str(level)
        ]

        result = subprocess.run(cmd, capture_output = True, text = True)
        lines = result.stdout.split("\n")

        if (result.returncode):
            print("Engine result", result.returncode)
            print("Engine error", result.stderr)
            print("Engine output", result.stdout)
            continue

        cost = float(lines[0])
        expression = lines[1].strip()

        if (cost):
            print("Cost", cost)
            print("Expression", expression)

    print(expression)

def main():
    processTask("training", "3c9b0459") #Flip left/right and flip up/down
    processTask("training", "0d3d703e") #Color mapping
    processTask("training", "253bf280") #Draw colored segment between pixels that have same x or y coordinates

if (__name__ == "__main__"):
    main()

