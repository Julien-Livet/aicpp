```python
def dsl1(I):
    # Global: keep only pixels that are symmetric w.r.t both vertical and horizontal mirrors
    A = cellwise(I, vmirror(I), ZERO)
    O = cellwise(A, hmirror(A), ZERO)
    return O

def dsl2(I):
    # Object extraction: fill the bounding rectangle of the largest object with its color
    objs = objects(I, T, F, T)
    big = argmax(objs, size)
    c = color(big)
    dims = shape(I)
    base = canvas(ZERO, dims)
    rect = backdrop(big)
    O = fill(base, c, rect)
    return O

def dsl3(I):
    # Color filtering: recolor all 5s to the most common non-5 foreground color
    objs = objects(I, T, F, T)
    fives = colorfilter(objs, FIVE)
    others = difference(objs, fives)
    seedcolors = apply(color, others)
    c = mostcommon(totuple(seedcolors))
    O = replace(I, FIVE, c)
    return O

def dsl4(I):
    # Geometric: keep only pixels that match their 180-degree rotation
    O = cellwise(I, rot180(I), ZERO)
    return O

def dsl5(I):
    # Relational/structural: recolor the border of the largest object by the least common seed color
    objs = objects(I, T, F, T)
    big = argmax(objs, size)
    others = difference(objs, initset(big))
    seedcolors = apply(color, others)
    c = leastcommon(totuple(seedcolors))
    edge = box(big)
    O = fill(I, c, edge)
    return O
```