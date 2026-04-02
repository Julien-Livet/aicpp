```python
def dsl1(I):
    # Global: compress frontiers and trim
    O = trim(compress(I))
    return O

def dsl2(I):
    # Object extraction: crop to the largest univalued object by size
    obs = objects(I, T, F, T)
    o = argmax(obs, size)
    O = subgrid(o, I)
    return O

def dsl3(I):
    # Color filtering: keep the most frequent nonzero color and trim
    cols = remove(ZERO, palette(I))
    mc = argmax(cols, lbind(colorcount, I))
    inds = ofcolor(I, mc)
    obj = toobject(inds, I)
    O = trim(paint(canvas(ZERO, shape(I)), obj))
    return O

def dsl4(I):
    # Geometric: intersect with vertical mirror and trim
    S = cellwise(I, vmirror(I), ZERO)
    O = trim(S)
    return O

def dsl5(I):
    # Relational: draw each object's bounding-box perimeter with its color, then trim
    obs = objects(I, T, F, T)
    mk = fork(recolor, color, box)
    perims = merge(apply(mk, obs))
    O = trim(paint(canvas(ZERO, shape(I)), perims))
    return O
```