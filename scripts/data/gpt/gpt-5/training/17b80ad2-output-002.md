```python
def dsl1(I):
    # Global: propagate only columns indicated by bottom-row nonzeros using 180-rotated content
    idx = asindices(I)
    bl = llcorner(idx)
    bottom = hfrontier(bl)
    nz = difference(idx, ofcolor(I, ZERO))
    bcols = intersection(bottom, nz)
    cols = merge(apply(vfrontier, bcols))
    J = rot180(I)
    mask = rot180(cols)
    obj = toobject(mask, J)
    O = underpaint(I, obj)
    return O

def dsl2(I):
    # Object extraction: take upward shoots from all nonzeros, keep only selected bottom columns, recolor from I, underpaint
    idx = asindices(I)
    bl = llcorner(idx)
    bottom = hfrontier(bl)
    nz = difference(idx, ofcolor(I, ZERO))
    bcols = intersection(bottom, nz)
    cols = merge(apply(vfrontier, bcols))
    up = rbind(shoot, UP)
    rays = merge(apply(up, nz))
    segs = intersection(rays, cols)
    obj = toobject(segs, I)
    O = underpaint(I, obj)
    return O

def dsl3(I):
    # Color filtering: select bottom-row columns, fill them uniformly with the least color among their original pixels
    idx = asindices(I)
    bl = llcorner(idx)
    bottom = hfrontier(bl)
    nz = difference(idx, ofcolor(I, ZERO))
    bcols = intersection(bottom, nz)
    cols = merge(apply(vfrontier, bcols))
    base = toobject(cols, I)
    c = leastcolor(base)
    obj = recolor(c, cols)
    O = underpaint(I, obj)
    return O

def dsl4(I):
    # Geometric: for each bottom nonzero, paint its full column with its own color
    idx = asindices(I)
    bl = llcorner(idx)
    bottom = hfrontier(bl)
    bmask = intersection(bottom, difference(idx, ofcolor(I, ZERO)))
    colf = compose(color, rbind(toobject, I), initset)
    g = fork(recolor, colf, vfrontier)
    objs = merge(apply(g, bmask))
    O = underpaint(I, objs)
    return O

def dsl5(I):
    # Relational: connect all nonzeros within selected bottom columns, recolor with bottom-row majority color, and underpaint
    idx = asindices(I)
    bl = llcorner(idx)
    bottom = hfrontier(bl)
    nz = difference(idx, ofcolor(I, ZERO))
    bcols = intersection(bottom, nz)
    cols = merge(apply(vfrontier, bcols))
    markers = intersection(nz, cols)
    pairs = prapply(connect, markers, markers)
    vls = sfilter(pairs, vline)
    lines = merge(vls)
    base = toobject(bcols, I)
    c = mostcolor(base)
    obj = recolor(c, lines)
    O = underpaint(I, obj)
    return O
```