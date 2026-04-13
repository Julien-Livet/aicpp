```python
def dsl1(I):
    # Global transformation: remove empty frontiers
    O = compress(I)
    return O

def dsl2(I):
    # Object extraction: keep only the largest foreground object (the big 5-block)
    objs = objects(I, T, F, T)
    big = argmax(objs, size)
    dims = shape(I)
    base = canvas(ZERO, dims)
    O = paint(base, big)
    return O

def dsl3(I):
    # Color filtering: recolor all 5s to the most common non-5 foreground color
    objs = objects(I, T, F, T)
    fives = colorfilter(objs, FIVE)
    nonfives = difference(objs, fives)
    seedcolors = apply(color, nonfives)
    c = mostcommon(seedcolors)
    O = replace(I, FIVE, c)
    return O

def dsl4(I):
    # Geometric reasoning: keep only cells that are vertically symmetric
    O = cellwise(I, vmirror(I), ZERO)
    return O

def dsl5(I):
    # Relational/structural: recolor the border of the largest object by a seed color
    objs = objects(I, T, F, T)
    big = argmax(objs, size)
    others = difference(objs, initset(big))
    seedcolors = apply(color, others)
    c = leastcommon(seedcolors)
    edge = box(big)
    O = fill(I, c, edge)
    return O
```