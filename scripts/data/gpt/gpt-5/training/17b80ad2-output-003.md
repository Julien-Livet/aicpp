```python
def dsl1(I):
    # Global: rotate, select top columns in rotated grid, fill them with their majority color, rotate back
    J = rot180(I)
    idx = asindices(J)
    tl = ulcorner(idx)
    top = hfrontier(tl)
    nz = difference(idx, ofcolor(J, ZERO))
    tmask = intersection(top, nz)
    cols = merge(apply(vfrontier, tmask))
    seeds = intersection(nz, cols)
    c = mostcolor(toobject(seeds, J))
    obj = recolor(c, cols)
    K = underpaint(J, obj)
    O = rot180(K)
    return O

def dsl2(I):
    # Object extraction: for each bottom nonzero, paint its full column with that bottom cell's color
    idx = asindices(I)
    bl = llcorner(idx)
    bottom = hfrontier(bl)
    nz = difference(idx, ofcolor(I, ZERO))
    bmask = intersection(bottom, nz)
    f1 = compose(rbind(toobject, I), initset)
    colf = compose(color, f1)
    g = fork(recolor, colf, vfrontier)
    objs = merge(apply(g, bmask))
    O = underpaint(I, objs)
    return O

def dsl3(I):
    # Color filtering: per selected bottom column, fill column with the least color among its nonzero seeds
    idx = asindices(I)
    bl = llcorner(idx)
    bottom = hfrontier(bl)
    nz = difference(idx, ofcolor(I, ZERO))
    bmask = intersection(bottom, nz)
    inter_nz = rbind(intersection, nz)
    mkf = compose(inter_nz, vfrontier)
    toI = rbind(toobject, I)
    mkobjf = compose(toI, mkf)
    colf = compose(leastcolor, mkobjf)
    g = fork(recolor, colf, vfrontier)
    objs = merge(apply(g, bmask))
    O = underpaint(I, objs)
    return O

def dsl4(I):
    # Geometric: copy colors into selected columns from the 180-rotated grid at the same indices
    idx = asindices(I)
    bl = llcorner(idx)
    bottom = hfrontier(bl)
    nz = difference(idx, ofcolor(I, ZERO))
    bmask = intersection(bottom, nz)
    cols = merge(apply(vfrontier, bmask))
    J = rot180(I)
    obj = toobject(cols, J)
    O = underpaint(I, obj)
    return O

def dsl5(I):
    # Relational: within each selected column, connect all nonzeros vertically and recolor with the column's majority seed color
    idx = asindices(I)
    bl = llcorner(idx)
    bottom = hfrontier(bl)
    nz = difference(idx, ofcolor(I, ZERO))
    bmask = intersection(bottom, nz)
    inter_nz = rbind(intersection, nz)
    mkf = compose(inter_nz, vfrontier)
    toI = rbind(toobject, I)
    mkobj = compose(toI, mkf)
    colf = compose(mostcolor, mkobj)
    prc = rbind(prapply, connect)
    pairsf = fork(prc, mkf, mkf)
    vlf = rbind(sfilter, vline)
    vlsf = compose(vlf, pairsf)
    linesf = compose(merge, vlsf)
    g = fork(recolor, colf, linesf)
    objs = merge(apply(g, bmask))
    O = underpaint(I, objs)
    return O
```