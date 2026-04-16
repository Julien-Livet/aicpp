import json
import numpy as np
import re

NUM_COLORS = 10

def generate_structured_grid():
    kind = np.random.choice(['stripes', 'blocks', 'pattern', 'gradient', 'sparse'])
    h = np.random.randint(4, 15)
    w = np.random.randint(4, 15)

    if (kind == 'stripes'):
        grid = np.zeros((h, w), dtype = int)

        for i in range(h):
            if (np.random.rand() > 0.5):
                grid[i, :] = np.random.randint(1, NUM_COLORS)
    elif (kind == 'blocks'):
        grid = np.zeros((h, w), dtype = int)

        for _ in range(np.random.randint(2, 6)):
            r1, r2 = sorted(np.random.randint(0, h, 2))
            c1, c2 = sorted(np.random.randint(0, w, 2))
            grid[r1:r2+1, c1:c2+1] = np.random.randint(1, NUM_COLORS)
    elif (kind == 'pattern'):
        base_h = np.random.randint(2, max(3, h // 2))
        base_w = np.random.randint(2, max(3, w // 2))
        base   = np.random.randint(0, NUM_COLORS, (base_h, base_w))
        grid   = np.tile(base, (h // base_h + 1, w // base_w + 1))[:h, :w]
    elif (kind == 'gradient'):
        grid = np.zeros((h, w), dtype = int)

        for i in range(h):
            grid[i, :] = int(i * (NUM_COLORS - 1) / max(h - 1, 1))
    else:  # sparse
        grid = np.zeros((h, w), dtype = int)

        for _ in range(np.random.randint(3, 10)):
            grid[np.random.randint(h), np.random.randint(w)] = np.random.randint(1, NUM_COLORS)

    return grid

def generate_dsl():
    import test_arc

    command = test_arc.dslPrompt()
    command += """

Generate a valid DSL program using the previous primitives.

Constraints:
- must represent a meaningful transformation on grids
- avoid trivial identity
- avoid overly complex nesting
- prefer transformations like: rotation, symmetry, object filtering, color mapping

Return only the DSL expression.

# EXPECTED OUTPUT EXAMPLE WITHOUT ANY FORMATTING AND ANY EXPLANATION
```python
def dsl(I):
    # O = ...
    return O
```
"""

    content = test_arc.callOllama("gpt-oss:120b", command)

    groups = re.findall(r'```python(.*?)```', content, flags = re.S)

    assert(len(groups))

    return groups[-1]

def generate_example():
    import test_arc

    dsl = generate_dsl()
    grids = []
    runner = test_arc.DSLWorker()

    for _ in range(4):
        inp = generate_structured_grid()
        out = runner.run_with_timeout(dsl, "dsl", 5, tuple(map(tuple, inp.tolist())))

    return {
        "dsl": dsl,
        "pairs": grids
    }

def format_example(example):
    text = "# Input->output grid pairs\n\n"

    for i, (inp, out) in enumerate(example["pairs"]):
        text += f"## train{i+1}\n\n"
        text += "### Input\n\n```\n"
        text += "\n".join("".join(map(str, row)) for row in inp)
        text += "\n```\n\n"

        text += "### Output\n\n```\n"
        text += "\n".join("".join(map(str, row)) for row in out)
        text += "\n```\n\n"

    return {
        "input": text,
        "output": f"def dsl(I): return {example['dsl']}"
    }

def generate_dataset(n = 10000, path = "dataset.json"):
    data = []

    while (len(data) < n):
        try:
            ex = generate_example()

            formatted = format_example(ex)
            data.append(formatted)

            if (len(data) % 100 == 0):
                print(f"{len(data)} examples")
        except Exception:
            pass

    with open(path, "w") as f:
        json.dump(data, f, indent = 2)

    print("Dataset saved.")
    
if (__name__ == "__main__"):
    generate_dataset()