```python
def dsl1(I):
    # Global: rotate to align columns with rows, cast rightward rays, rotate back
    J = rot270(I)
    idx = asindices(J)
    nz = difference(idx, ofcolor(J, ZERO))
    f1 = compose(rbind(toobject, J), initset)
    colf = compose(color, f1)
    rayf = rbind(shoot, RIGHT)
    g = fork(recolor, colf, rayf)
    objs = merge(apply(g, nz))
    K = underpaint(J, objs)
    O = rot90(K)
    return O

def dsl2(I):
    # Object extraction: connect each object's center to the top of its column
    seeds = fgpartition(I)
    cf = center
    vf = compose(vfrontier, cf)
    topf = compose(ulcorner, vf)
    segf = fork(connect, cf, topf)
    g = fork(recolor, color, segf)
    objs = merge(apply(g, seeds))
    O = underpaint(I, objs)
    return O

def dsl3(I):
    # Color filtering: for each color, union upward segments from all its cells
    seeds = fgpartition(I)
    samec = compose(lbind(colorfilter, seeds), color)
    inds = compose(merge, lbind(apply, toindices))
    colinds = compose(inds, samec)
    upseg = fork(difference, vfrontier, rbind(shoot, DOWN))
    rays = compose(merge, lbind(apply, upseg))
    seg = compose(rays, colinds)
    g = fork(recolor, color, seg)
    objs = merge(apply(g, seeds))
    O = underpaint(I, objs)
    return O

def dsl4(I):
    # Geometric: compute direction to column top and shoot a ray
    seeds = fgpartition(I)
    cf = center
    vf = compose(vfrontier, cf)
    topf = compose(ulcorner, vf)
    vec = fork(subtract, topf, cf)
    dirf = compose(sign, vec)
    rayf = fork(shoot, cf, dirf)
    g = fork(recolor, color, rayf)
    objs = merge(apply(g, seeds))
    O = underpaint(I, objs)
    return O

def dsl5(I):
    # Relational: connect to top and keep only cells above any same-colored cell (downward mask)
    seeds = fgpartition(I)
    cf = center
    vf = compose(vfrontier, cf)
    topf = compose(ulcorner, vf)
    pathf = fork(connect, cf, topf)
    samec = compose(lbind(colorfilter, seeds), color)
    inds = compose(merge, lbind(apply, toindices))
    downr = compose(merge, lbind(apply, rbind(shoot, DOWN)))
    maskc = compose(downr, samec)
    segf = fork(intersection, pathf, maskc)
    g = fork(recolor, color, segf)
    objs = merge(apply(g, seeds))
    O = underpaint(I, objs)
    return O
```