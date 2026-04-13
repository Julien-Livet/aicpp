```python
def dsl1(I):
    z = ofcolor(I, ZERO)
    th = ofcolor(I, THREE)
    rays_h = combine(mapply(rbind(shoot, LEFT), z), mapply(rbind(shoot, RIGHT), z))
    rays_v = combine(mapply(rbind(shoot, UP), z), mapply(rbind(shoot, DOWN), z))
    rays = combine(rays_h, rays_v)
    ledge = difference(th, shift(th, LEFT))
    redge = difference(th, shift(th, RIGHT))
    tedge = difference(th, shift(th, UP))
    bedge = difference(th, shift(th, DOWN))
    edges = combine(combine(ledge, redge), combine(tedge, bedge))
    marks = intersection(rays, edges)
    base = replace(replace(I, FIVE, SEVEN), THREE, SEVEN)
    O = fill(base, FIVE, marks)
    return O

def dsl2(I):
    thobjs = colorfilter(objects(I, T, F, T), THREE)
    thpatches = apply(toindices, thobjs)
    corner_sets = apply(corners, thpatches)
    thcorners = merge(corner_sets)
    z = ofcolor(I, ZERO)
    zdiag = merge(mapply(ineighbors, z))
    marks = intersection(thcorners, zdiag)
    base = replace(replace(I, FIVE, SEVEN), THREE, SEVEN)
    O = fill(base, FIVE, marks)
    return O

def dsl3(I):
    th = ofcolor(I, THREE)
    z = ofcolor(I, ZERO)
    near4 = merge(mapply(dneighbors, z))
    near8 = merge(mapply(ineighbors, z))
    keep3 = intersection(th, near4)
    diag3 = intersection(th, near8)
    mark5 = difference(diag3, near4)
    base = replace(replace(I, FIVE, SEVEN), THREE, SEVEN)
    with3 = fill(base, THREE, keep3)
    O = fill(with3, FIVE, mark5)
    return O

def dsl4(I):
    thobjs = colorfilter(objects(I, T, F, T), THREE)
    thpatches = apply(toindices, thobjs)
    perims = apply(box, thpatches)
    perimall = merge(perims)
    z = ofcolor(I, ZERO)
    zdiag = merge(mapply(ineighbors, z))
    marks = intersection(perimall, zdiag)
    base = replace(replace(I, FIVE, SEVEN), THREE, SEVEN)
    O = fill(base, FIVE, marks)
    return O

def dsl5(I):
    z = ofcolor(I, ZERO)
    znear = merge(mapply(dneighbors, z))
    rows = merge(mapply(hfrontier, znear))
    th = ofcolor(I, THREE)
    rowgreens = intersection(th, rows)
    rightedge = difference(rowgreens, shift(rowgreens, RIGHT))
    base = fill(replace(I, FIVE, SEVEN), SEVEN, rowgreens)
    O = fill(base, FIVE, rightedge)
    return O
```