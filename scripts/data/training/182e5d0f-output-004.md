```python
def dsl1(I):
    z = ofcolor(I, ZERO)
    th = ofcolor(I, THREE)
    vec = gravitate(z, th)
    rays = combine(mapply(rbind(shoot, vec), z), mapply(rbind(shoot, invert(vec)), z))
    edges = combine(difference(th, shift(th, LEFT)), difference(th, shift(th, RIGHT)))
    marks = intersection(rays, edges)
    cleared = replace(I, FIVE, SEVEN)
    O = fill(cleared, FIVE, marks)
    return O

def dsl2(I):
    thobjs = colorfilter(objects(I, T, F, T), THREE)
    thpatches = mapply(toindices, thobjs)
    cornersets = mapply(corners, thpatches)
    cornersall = merge(cornersets)
    z = ofcolor(I, ZERO)
    zdiag = merge(mapply(ineighbors, z))
    candidates = intersection(cornersall, zdiag)
    th = ofcolor(I, THREE)
    marks = intersection(candidates, th)
    cleared = replace(I, FIVE, SEVEN)
    O = fill(cleared, FIVE, marks)
    return O

def dsl3(I):
    thobjs = colorfilter(objects(I, T, F, T), THREE)
    thpatches = mapply(toindices, thobjs)
    perimeters = merge(mapply(box, thpatches))
    z = ofcolor(I, ZERO)
    near = merge(mapply(ineighbors, z))
    marks = intersection(perimeters, near)
    cleared = replace(I, FIVE, SEVEN)
    O = fill(cleared, FIVE, marks)
    return O

def dsl4(I):
    z = ofcolor(I, ZERO)
    rows = merge(mapply(hfrontier, z))
    cols = merge(mapply(vfrontier, z))
    th = ofcolor(I, THREE)
    rowth = intersection(th, rows)
    colth = intersection(th, cols)
    rowredge = difference(rowth, shift(rowth, RIGHT))
    coltopedge = difference(colth, shift(colth, UP))
    marks = combine(rowredge, coltopedge)
    cleared = replace(I, FIVE, SEVEN)
    O = fill(cleared, FIVE, marks)
    return O

def dsl5(I):
    z = ofcolor(I, ZERO)
    near = merge(combine(mapply(ineighbors, z), mapply(dneighbors, z)))
    th = ofcolor(I, THREE)
    ledge = difference(th, shift(th, LEFT))
    redge = difference(th, shift(th, RIGHT))
    edges = combine(ledge, redge)
    marks = intersection(near, edges)
    cleared = replace(I, FIVE, SEVEN)
    O = fill(cleared, FIVE, marks)
    return O
```