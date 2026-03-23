```python
def dsl1(I):
    # Global: rotate and shoot downward from each nonzero, rotate back
    J = rot180(I)
    idx = asindices(J)
    nz = difference(idx, ofcolor(J, ZERO))
    f1 = compose(rbind(toobject, J), initset)
    colf = compose(color, f1)
    rayf = rbind(shoot, DOWN)
    g = fork(recolor, colf, rayf)
    objs = merge(apply(g, nz))
    K = underpaint(J, objs)
    O = rot180(K)
    return O

def dsl2(I):
    # Object extraction: for each nonzero object, shoot upward from its center
    seeds = fgpartition(I)
    colf = color
    rayf = compose(rbind(shoot, UP), center)
    g = fork(recolor, colf, rayf)
    objs = merge(apply(g, seeds))
    O = underpaint(I, objs)
    return O

def dsl3(I):
    # Color filtering: for each nonzero, take its column and remove the downward shoot to keep the upward segment
    idx = asindices(I)
    nz = difference(idx, ofcolor(I, ZERO))
    vff = vfrontier
    dshoot = rbind(shoot, DOWN)
    upseg = fork(difference, vff, dshoot)
    f1 = compose(rbind(toobject, I), initset)
    colf = compose(color, f1)
    g = fork(recolor, colf, upseg)
    objs = merge(apply(g, nz))
    O = underpaint(I, objs)
    return O

def dsl4(I):
    # Geometric: connect each nonzero to the top of its column
    idx = asindices(I)
    nz = difference(idx, ofcolor(I, ZERO))
    vf = vfrontier
    topf = compose(ulcorner, vf)
    connf = fork(connect, identity, topf)
    f1 = compose(rbind(toobject, I), initset)
    colf = compose(color, f1)
    g = fork(recolor, colf, connf)
    objs = merge(apply(g, nz))
    O = underpaint(I, objs)
    return O

def dsl5(I):
    # Relational: shoot upward from every nonzero and paint background
    idx = asindices(I)
    nz = difference(idx, ofcolor(I, ZERO))
    f1 = compose(rbind(toobject, I), initset)
    colf = compose(color, f1)
    rayf = rbind(shoot, UP)
    g = fork(recolor, colf, rayf)
    objs = merge(apply(g, nz))
    O = underpaint(I, objs)
    return O
```