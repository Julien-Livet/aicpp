```python
def dsl1(I):
    # Global: overlay 180-rotated grid onto original by underpainting
    J = rot180(I)
    obj = asobject(J)
    O = underpaint(I, obj)
    return O

def dsl2(I):
    # Object extraction: draw each object's bounding box outline with its color, then underpaint
    objs = objects(I, T, F, T)
    g = fork(recolor, color, compose(box, backdrop))
    outlines = merge(apply(g, objs))
    O = underpaint(I, outlines)
    return O

def dsl3(I):
    # Color filtering: pick a nonzero extremal color, extend its columns via vfrontier, then underpaint
    palnz = remove(ZERO, palette(I))
    anch = minimum(palnz)
    locs = ofcolor(I, anch)
    cols = mapply(vfrontier, locs)
    obj = recolor(anch, cols)
    O = underpaint(I, obj)
    return O

def dsl4(I):
    # Geometric: paint the vertical mirror of the grid onto the original
    J = vmirror(I)
    obj = asobject(J)
    O = paint(I, obj)
    return O

def dsl5(I):
    # Relational/structural: connect all nonzero pairs, keep vertical lines, recolor with majority color, then underpaint
    nz = difference(asindices(I), ofcolor(I, ZERO))
    pairs = prapply(connect, nz, nz)
    vls = sfilter(pairs, vline)
    lines = merge(vls)
    c = mostcolor(I)
    obj = recolor(c, lines)
    O = underpaint(I, obj)
    return O
```