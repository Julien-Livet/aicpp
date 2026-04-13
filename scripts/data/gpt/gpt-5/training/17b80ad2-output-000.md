```python
def dsl1(I):
    # Global: propagate each object's color to its entire column (union of vertical frontiers), then underpaint
    objs = objects(I, T, F, T)
    f = fork(recolor, color, compose(vfrontier, center))
    cols = merge(apply(f, objs))
    O = underpaint(I, cols)
    return O

def dsl2(I):
    # Object extraction: expand each object to its bounding box (backdrop) with its color, then underpaint
    objs = objects(I, T, F, T)
    g = fork(recolor, color, backdrop)
    boxes = merge(apply(g, objs))
    O = underpaint(I, boxes)
    return O

def dsl3(I):
    # Color filtering: pick a nonzero anchor color, extend its columns via vfrontier, then underpaint
    pal = palette(I)
    palnz = remove(ZERO, pal)
    anch = leastcommon(palnz)
    locs = ofcolor(I, anch)
    cols = mapply(vfrontier, locs)
    obj = recolor(anch, cols)
    O = underpaint(I, obj)
    return O

def dsl4(I):
    # Geometric: vertically mirror and overlay with original where equal, else keep background
    J = vmirror(I)
    O = cellwise(I, J, ZERO)
    return O

def dsl5(I):
    # Relational/structural: connect all nonzero indices pairwise, recolor with a nonzero common color, then underpaint
    nz = difference(asindices(I), ofcolor(I, ZERO))
    pairs = prapply(connect, nz, nz)
    lines = merge(pairs)
    pal = remove(ZERO, palette(I))
    c = mostcommon(pal)
    obj = recolor(c, lines)
    O = underpaint(I, obj)
    return O
```