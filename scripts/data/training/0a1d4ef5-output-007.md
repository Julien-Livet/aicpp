```python
def dsl1(I):
    # Global transformation: remove interior frontiers globally, then trim outer background
    O = trim(compress(I))
    return O

def dsl2(I):
    # Object extraction: crop to the largest foreground univalued object
    obs = objects(I, T, F, T)
    o = argmax(obs, size)
    O = subgrid(o, I)
    return O

def dsl3(I):
    # Color filtering: keep only the most frequent nonzero color and trim
    colors = remove(ZERO, palette(I))
    mc = argmax(colors, lbind(colorcount, I))
    inds = ofcolor(I, mc)
    obj = toobject(inds, I)
    O = trim(paint(canvas(ZERO, shape(I)), obj))
    return O

def dsl4(I):
    # Geometric reasoning: intersect the grid with its vertical mirror and trim
    S = cellwise(I, vmirror(I), ZERO)
    O = trim(S)
    return O

def dsl5(I):
    # Relational/structural: mark bounding-box corners of each object with its color, then trim
    obs = objects(I, T, F, T)
    mk = fork(recolor, color, corners)
    corners_objs = merge(apply(mk, obs))
    O = trim(paint(canvas(ZERO, shape(I)), corners_objs))
    return O
```