```python
def dsl1(I):
    # Global: cast upward rays from every nonzero cell and paint them
    idx = asindices(I)
    nz = difference(idx, ofcolor(I, ZERO))
    toobj = compose(rbind(toobject, I), initset)
    getc = compose(color, toobj)
    upray = rbind(shoot, UP)
    mk = fork(recolor, getc, upray)
    objs = merge(apply(mk, nz))
    O = underpaint(I, objs)
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
    # Color filtering: for each color, union top-to-cell segments from all its cells
    seeds = fgpartition(I)
    samec = compose(lbind(colorfilter, seeds), color)
    inds = compose(merge, lbind(apply, toindices))
    colinds = compose(inds, samec)
    toploc = compose(ulcorner, vfrontier)
    segloc = fork(connect, toploc, identity)
    rays = compose(merge, lbind(apply, segloc))
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
    # Relational: for each seed, connect to nearest nonzero above in its column (or top), paint only background
    seeds = fgpartition(I)
    cf = center
    vf = compose(vfrontier, cf)
    topf = compose(ulcorner, vf)
    nz = difference(asindices(I), ofcolor(I, ZERO))
    downcf = compose(rbind(shoot, DOWN), cf)
    upmask = fork(difference, vf, downcf)
    abovenz = compose(lbind(intersection, nz), upmask)
    addtop = fork(combine, abovenz, compose(initset, topf))
    anch = compose(llcorner, addtop)
    segf = fork(connect, anch, cf)
    g = fork(recolor, color, segf)
    objs = merge(apply(g, seeds))
    O = underpaint(I, objs)
    return O
```