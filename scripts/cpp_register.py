import re
import sys
from pathlib import Path

def remove_parameter_name(parameter: str) -> str:
    parameter = parameter.strip()

    match = re.match(
        r"^(.*?)\s+([A-Za-z_]\w*)\s*$",
        parameter,
    )

    if match:
        candidate_type = match.group(1).strip()
        candidate_name = match.group(2)

        if candidate_type and candidate_name not in {
            "const", "volatile"
        }:
            return candidate_type

    return parameter

TYPEDEF_RE = re.compile(
    r"""
    ^\s*
    typedef\s+
    (?P<cpp_type>.+?)
    \s+
    (?P<dsl_type>[A-Za-z_]\w*)
    \s*;
    \s*(?://.*)?$
    """,
    re.VERBOSE,
)

def extract_dsl_types(header_path: str) -> dict[str, str]:
    types = {}

    for line_number, line in enumerate(
        Path(header_path).read_text(encoding="utf-8").splitlines(),
        start=1,
    ):
        match = TYPEDEF_RE.match(line)

        if match:
            cpp_type = match.group("cpp_type").strip()
            dsl_type = match.group("dsl_type")

            types[dsl_type] = cpp_type

    return types

BUILTIN_TYPES = {
    "bool",
    "char",
    "short",
    "int",
    "long",
    "float",
    "double",
    "void",
    "const",
    "volatile",
    "unsigned",
    "signed",
}

def qualify_type(types: dict, type_name: str) -> str:
    type_name = type_name.strip()

    # Ajoute hodel:: devant les noms de types DSL,
    # uniquement lorsqu'ils ne sont pas déjà qualifiés.
    for dsl_type in sorted(types, key=len, reverse=True):
        pattern = (
            r"(?<![\w:])"
            + re.escape(dsl_type)
            + r"(?!\w)"
        )

        type_name = re.sub(
            pattern,
            lambda _: f"hodel::{dsl_type}",
            type_name,
        )

    # Évite la double qualification.
    type_name = type_name.replace("hodel::hodel::", "hodel::")

    return type_name

def split_arguments(arguments: str) -> list[str]:
    if not arguments.strip() or arguments.strip() == "void":
        return []

    result = []
    start = 0
    angle_depth = 0
    paren_depth = 0
    bracket_depth = 0

    for i, char in enumerate(arguments):
        if char == "<":
            angle_depth += 1
        elif char == ">":
            angle_depth -= 1
        elif char == "(":
            paren_depth += 1
        elif char == ")":
            paren_depth -= 1
        elif char == "[":
            bracket_depth += 1
        elif char == "]":
            bracket_depth -= 1
        elif (
            char == ","
            and angle_depth == 0
            and paren_depth == 0
            and bracket_depth == 0
        ):
            result.append(arguments[start:i].strip())
            start = i + 1

    result.append(arguments[start:].strip())
    return result

SIGNATURE_RE = re.compile(
    r"""
    ^\s*
    (?P<return_type>[\w:]+(?:\s*[*&])*)
    \s+
    (?P<name>[A-Za-z_]\w*)
    \s*
    \(
        (?P<arguments>.*)
    \)
    \s*;
    \s*//
    """,
    re.VERBOSE,
)

def parse_header(types: dict, header_path: Path) -> list[dict]:
    declarations = []

    for line_number, line in enumerate(
        header_path.read_text(encoding="utf-8").splitlines(),
        start=1,
    ):
        if "; //" not in line:
            continue

        match = SIGNATURE_RE.match(line)

        if not match:
            print(
                f"Avertissement : déclaration non reconnue "
                f"à la ligne {line_number} : {line.strip()}",
                file=sys.stderr,
            )
            continue

        return_type = qualify_type(types, match.group("return_type"))
        name = match.group("name")

        arguments = [
            qualify_type(types, remove_parameter_name(arg))
            for arg in split_arguments(match.group("arguments"))
        ]

        declarations.append({
            "line": line_number,
            "return_type": return_type,
            "name": name,
            "arguments": arguments,
        })

    return declarations

def generate_cpp(name: str, declarations: list[dict], output_path: Path) -> None:
    lines = [
        "// Automatically generated file. Do not modify.",
        "",
        "#include <cstddef>",
        "",
        f'#include "{name}.h"',
        '#include "Neuron.h"',
        "",
        "namespace aicpp",
        "{",
        f"using namespace {name.lower()};",
        "",
    ]

    for index, declaration in enumerate(declarations):
        return_type = declaration["return_type"]
        name = declaration["name"]
        arguments = declaration["arguments"]

        neuron_type = (
            f"aicpp::Neuron<{return_type}"
            + "".join(f", {arg}" for arg in arguments)
            + ">"
        )

        function_type = f"{neuron_type}::Function"

        variable_name = f"neuron_{name}_{index}"

        lines.extend([
            f"// Original declaration: line {declaration['line']}",
            f"using FunctionType_{index} = {function_type};",
            "",
            f"{neuron_type} {variable_name}{{",
            f'    "{name}",',
            f"    static_cast<FunctionType_{index}>(&hodel::{name})",
            "};",
            "",
        ])

    registry_entries = []

    for index, declaration in enumerate(declarations):
        variable_name = f"neuron_{declaration['name']}_{index}"

        registry_entries.append(
            f'    registry.emplace("{variable_name}", &{variable_name});'
        )
    
    lines.extend([
        "NeuronRegistry makeNeuronRegistry()",
        "{",
        "    NeuronRegistry registry;",
        *registry_entries,
        "    return registry;",
        "}",
    ])

    lines.extend([
        "} // namespace aicpp",
        "",
    ])

    output_path.write_text(
        "\n".join(lines),
        encoding="utf-8",
    )

    print(
        f"{len(declarations)} generated neuron(s) in {output_path}"
    )

def main() -> None:
    if len(sys.argv) != 2:
        print(
            "Usage : python generate_neurons.py "
            "Hodel",
            file=sys.stderr,
        )
        sys.exit(1)

    header_path = Path("../include/aicpp/" + sys.argv[1] + ".h")
    output_path = Path("../src/aicpp/" + sys.argv[1] + "Register.cpp")

    if not header_path.is_file():
        print(
            f"Error: file not found: {header_path}",
            file=sys.stderr,
        )
        sys.exit(1)

    types = extract_dsl_types(header_path)
    declarations = parse_header(types, header_path)

    if not declarations:
        print(
            "No known declaration. "
            "Check comment and signature format.",
            file=sys.stderr,
        )
        sys.exit(1)

    generate_cpp(sys.argv[1], declarations, output_path)

if __name__ == "__main__":
    main()
