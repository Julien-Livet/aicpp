```python
def dsl1(I):
    z = ofcolor(I, ZERO)
    th = ofcolor(I, THREE)
    rays_h = combine(mapply(rbind(shoot, LEFT), z), mapply(rbind(shoot, RIGHT), z))
    rays_v = combine(mapply(rbind(shoot, UP), z), mapply(rbind(shoot, DOWN), z))
    lines = combine(combine(rays_h, rays_v), z)
    keep3 = intersection(th, lines)
    diag = merge(mapply(ineighbors, z))
    mark5 = intersection(th, diag)
    base = replace(replace(I, FIVE, SEVEN), THREE, SEVEN)
    with3 = fill(base, THREE, keep3)
    O = fill(with3, FIVE, mark5)
    return O

def dsl2(I):
    z = ofcolor(I, ZERO)
    thobjs = colorfilter(objects(I, T, F, T), THREE)
    adj = sfilter(thobjs, rbind(adjacent, z))
    adjpatches = apply(toindices, adj)
    keep = merge(adjpatches)
    ulcs = apply(ulcorner, adjpatches)
    marks = merge(apply(initset, ulcs))
    base = replace(replace(I, FIVE, SEVEN), THREE, SEVEN)
    with3 = fill(base, THREE, keep)
    O = fill(with3, FIVE, marks)
    return O

def dsl3(I):
    z = ofcolor(I, ZERO)
    th = ofcolor(I, THREE)
    near4 = merge(mapply(dneighbors, z))
    keep1 = intersection(th, near4)
    near_keep1 = merge(mapply(dneighbors, keep1))
    keep2 = intersection(th, near_keep1)
    keep = combine(keep1, keep2)
    base = replace(replace(I, FIVE, SEVEN), THREE, SEVEN)
    O = fill(base, THREE, keep)
    return O

def dsl4(I):
    z = ofcolor(I, ZERO)
    th = ofcolor(I, THREE)
    ledge = difference(th, shift(th, LEFT))
    redge = difference(th, shift(th, RIGHT))
    tedge = difference(th, shift(th, UP))
    bedge = difference(th, shift(th, DOWN))
    edges = combine(combine(ledge, redge), combine(tedge, bedge))
    zdiag = merge(mapply(ineighbors, z))
    marks = intersection(edges, zdiag)
    base = replace(replace(I, FIVE, SEVEN), THREE, SEVEN)
    O = fill(base, FIVE, marks)
    return O

def dsl5(I):
    z = ofcolor(I, ZERO)
    th = ofcolor(I, THREE)
    cols = combine(combine(mapply(rbind(shoot, UP), z), mapply(rbind(shoot, DOWN), z)), z)
    rightcols = shift(cols, RIGHT)
    rows = combine(combine(mapply(rbind(shoot, LEFT), z), mapply(rbind(shoot, RIGHT), z)), z)
    band = combine(rightcols, rows)
    keep3 = intersection(th, band)
    diag = merge(mapply(ineighbors, z))
    mark5 = intersection(th, diag)
    base = replace(replace(I, FIVE, SEVEN), THREE, SEVEN)
    with3 = fill(base, THREE, keep3)
    O = fill(with3, FIVE, mark5)
    return O
```