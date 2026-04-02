```python
def dsl1(I):
    F = frontiers(I)
    edges = merge(F)
    O = fill(I, ONE, edges)
    return O

def dsl2(I):
    ones = ofcolor(I, ONE)
    objs = objects(I, T, F, T)
    twos = colorfilter(objs, TWO)
    sel = sfilter(twos, rbind(hmatching, ones))
    recol = apply(lbind(recolor, ONE), sel)
    O = paint(I, merge(recol))
    return O

def dsl3(I):
    ones = ofcolor(I, ONE)
    bbox = backdrop(ones)
    twocells = ofcolor(I, TWO)
    target = intersection(twocells, bbox)
    O = fill(I, ONE, target)
    return O

def dsl4(I):
    ones = ofcolor(I, ONE)
    mir_ones = ofcolor(vmirror(I), ONE)
    sym = combine(ones, mir_ones)
    O = fill(I, ONE, sym)
    return O

def dsl5(I):
    ones = ofcolor(I, ONE)
    vparts = apply(vfrontier, ones)
    vline = merge(vparts)
    J = fill(I, ONE, vline)
    objs = objects(I, T, F, T)
    twos = colorfilter(objs, TWO)
    cond = rbind(vmatching, vline)
    sel = sfilter(twos, cond)
    recol = apply(lbind(recolor, ONE), sel)
    union = merge(recol)
    O = paint(J, union)
    return O
```