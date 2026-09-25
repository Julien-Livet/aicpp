from collections import defaultdict

def programDepth(program: str):
    count = 0
    n = 0

    for c in program:
        if (c == "("):
            n += 1
        elif (c == ")"):
            n -= 1

        count = max(count, n)

    return count

with open("dsl_dataset.txt", "r") as f:
    lines = f.read().split("\n")

dataset = defaultdict(list)

for line in lines:
    dataset[programDepth(line)].append(line)

dataset = dict(sorted(dataset.items()))
del dataset[0]

for i in range(1, max(dataset) + 1):
    programs: list = []

    for k, v in dataset.items():
        if (k > i):
            break

        programs += sorted(v)

    with open(f'dsl_dataset_depth{i}.txt', 'w') as f:
        f.write('\n'.join(programs))

