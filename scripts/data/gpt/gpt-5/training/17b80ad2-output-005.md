```python
def dsl1(I):
    # Global: rotate, propagate horizontally, rotate back
    J = rot90(I)
    idx = asindices(J)
    nz = difference(idx, ofcolor(J, ZERO))
    f1 = compose(rbind(toobject, J), initset)
    colf = compose(color, f1)
    rayf = rbind(shoot, LEFT)
    g = fork(recolor, colf, rayf)
    objs = merge(apply(g, nz))
    K = underpaint(J, objs)
    O = rot270(K)
    return O

def dsl2(I):
    # Object extraction: connect each object center to the top of its column
    seeds = fgpartition(I)
    cf = center
    vf = compose(vfrontier, cf)
    topf = compose(ulcorner, vf)
    connf = fork(connect, cf, topf)
    g = fork(recolor, color, connf)
    objs = merge(apply(g, seeds))
    O = underpaint(I, objs)
    return O

def dsl3(I):
    # Color filtering: for each color group, union upward rays from all its cells
    seeds = fgpartition(I)
    samec = compose(lbind(colorfilter, seeds), color)
    inds = compose(merge, lbind(apply, toindices))
    colseeds = compose(inds, samec)
    ray = rbind(shoot, UP)
    rays = compose(merge, lbind(apply, ray))
    seg = compose(rays, colseeds)
    g = fork(recolor, color, seg)
    objs = merge(apply(g, seeds))
    O = underpaint(I, objs)
    return O

def dsl4(I):
    # Geometric: take upward segment in the column including the anchor cell
    idx = asindices(I)
    nz = difference(idx, ofcolor(I, ZERO))
    vff = vfrontier
    dshoot = rbind(shoot, DOWN)
    upseg = fork(difference, vff, dshoot)
    inc = fork(insert, identity, upseg)
    f1 = compose(rbind(toobject, I), initset)
    colf = compose(color, f1)
    g = fork(recolor, colf, inc)
    objs = merge(apply(g, nz))
    O = underpaint(I, objs)
    return O

def dsl5(I):
    # Relational: connect to top but restrict painting to rows that contain any nonzero
    idx = asindices(I)
    nz = difference(idx, ofcolor(I, ZERO))
    rowmask = merge(apply(hfrontier, nz))
    vf = vfrontier
    topf = compose(ulcorner, vf)
    pathf = fork(connect, identity, topf)
    maskf = lbind(intersection, rowmask)
    segf = compose(maskf, pathf)
    f1 = compose(rbind(toobject, I), initset)
    colf = compose(color, f1)
    g = fork(recolor, colf, segf)
    objs = merge(apply(g, nz))
    O = underpaint(I, objs)
    return O
```