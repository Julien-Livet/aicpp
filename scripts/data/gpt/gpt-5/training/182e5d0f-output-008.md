```python
def dsl1(I):
    z = ofcolor(I, ZERO)
    th = ofcolor(I, THREE)
    up = merge(mapply(rbind(shoot, UP), z))
    down = merge(mapply(rbind(shoot, DOWN), z))
    lefts = merge(mapply(rbind(shoot, LEFT), z))
    rights = merge(mapply(rbind(shoot, RIGHT), z))
    band = combine(combine(up, down), combine(lefts, rights))
    band_woz = difference(band, z)
    keep = intersection(th, band_woz)
    diag = merge(mapply(ineighbors, z))
    marks = intersection(th, intersection(diag, band_woz))
    base = replace(replace(I, FIVE, SEVEN), THREE, SEVEN)
    with3 = fill(base, THREE, keep)
    O = fill(with3, FIVE, marks)
    return O

def dsl2(I):
    z = ofcolor(I, ZERO)
    thobjs = colorfilter(objects(I, T, F, T), THREE)
    orth = merge(mapply(neighbors, z))
    adjobjs = sfilter(thobjs, rbind(adjacent, orth))
    keep = merge(apply(toindices, adjobjs))
    diag = merge(mapply(ineighbors, z))
    marks = intersection(keep, diag)
    base = replace(replace(I, FIVE, SEVEN), THREE, SEVEN)
    with3 = fill(base, THREE, keep)
    O = fill(with3, FIVE, marks)
    return O

def dsl3(I):
    z = ofcolor(I, ZERO)
    th = ofcolor(I, THREE)
    orth = merge(mapply(neighbors, z))
    diag = merge(mapply(ineighbors, z))
    keep = intersection(th, orth)
    marks = difference(intersection(th, diag), keep)
    base = replace(replace(I, FIVE, SEVEN), THREE, SEVEN)
    with3 = fill(base, THREE, keep)
    O = fill(with3, FIVE, marks)
    return O

def dsl4(I):
    z = ofcolor(I, ZERO)
    th = ofcolor(I, THREE)
    lines = merge(prapply(connect, z, z))
    keep = intersection(th, lines)
    diag = merge(mapply(ineighbors, z))
    marks = difference(intersection(th, diag), keep)
    base = replace(replace(I, FIVE, SEVEN), THREE, SEVEN)
    with3 = fill(base, THREE, keep)
    O = fill(with3, FIVE, marks)
    return O

def dsl5(I):
    z = ofcolor(I, ZERO)
    th = ofcolor(I, THREE)
    vbands = merge(mapply(vfrontier, z))
    hbands = merge(mapply(hfrontier, z))
    crosses = intersection(vbands, hbands)
    lines = combine(vbands, hbands)
    keep = intersection(th, crosses)
    marks = intersection(th, difference(lines, crosses))
    base = replace(replace(I, FIVE, SEVEN), THREE, SEVEN)
    with3 = fill(base, THREE, keep)
    O = fill(with3, FIVE, marks)
    return O
```