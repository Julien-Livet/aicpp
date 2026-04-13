```python
def dsl1(I):
    z = ofcolor(I, ZERO)
    th = ofcolor(I, THREE)
    fives = ofcolor(I, FIVE)
    orth = merge(mapply(neighbors, z))
    diag = merge(mapply(ineighbors, z))
    keep3 = intersection(th, orth)
    mark5_from3 = difference(intersection(th, diag), keep3)
    keep5 = intersection(fives, combine(orth, diag))
    base = replace(replace(I, FIVE, SEVEN), THREE, SEVEN)
    with3 = fill(base, THREE, keep3)
    with5a = fill(with3, FIVE, mark5_from3)
    O = fill(with5a, FIVE, keep5)
    return O

def dsl2(I):
    z = ofcolor(I, ZERO)
    thobjs = colorfilter(objects(I, T, F, T), THREE)
    orth = toobject(merge(mapply(neighbors, z)), I)
    diag = toobject(merge(mapply(ineighbors, z)), I)
    adjo = sfilter(thobjs, rbind(adjacent, orth))
    diago = sfilter(thobjs, rbind(adjacent, diag))
    keep3 = merge(apply(toindices, adjo))
    diag3 = merge(apply(toindices, diago))
    mark5 = difference(diag3, keep3)
    base = replace(replace(I, FIVE, SEVEN), THREE, SEVEN)
    with3 = fill(base, THREE, keep3)
    O = fill(with3, FIVE, mark5)
    return O

def dsl3(I):
    z = ofcolor(I, ZERO)
    bb = backdrop(z)
    vbands_full = merge(mapply(vfrontier, z))
    hbands_full = merge(mapply(hfrontier, z))
    vbands = intersection(vbands_full, bb)
    hbands = intersection(hbands_full, bb)
    crosses = intersection(vbands, hbands)
    th = ofcolor(I, THREE)
    keep3 = intersection(th, crosses)
    lines = combine(vbands, hbands)
    mark5 = intersection(th, difference(lines, crosses))
    base = replace(replace(I, FIVE, SEVEN), THREE, SEVEN)
    with3 = fill(base, THREE, keep3)
    O = fill(with3, FIVE, mark5)
    return O

def dsl4(I):
    z = ofcolor(I, ZERO)
    zu = shift(z, UP)
    zd = shift(z, DOWN)
    zl = shift(z, LEFT)
    zr = shift(z, RIGHT)
    zul = shift(z, UP_LEFT)
    zur = shift(z, UP_RIGHT)
    zdl = shift(z, DOWN_LEFT)
    zdr = shift(z, DOWN_RIGHT)
    orth_lines = combine(
        combine(merge(prapply(connect, z, zu)), merge(prapply(connect, z, zd))),
        combine(merge(prapply(connect, z, zl)), merge(prapply(connect, z, zr)))
    )
    diag_lines = combine(
        combine(merge(prapply(connect, z, zul)), merge(prapply(connect, z, zur))),
        combine(merge(prapply(connect, z, zdl)), merge(prapply(connect, z, zdr)))
    )
    th = ofcolor(I, THREE)
    keep3 = intersection(th, orth_lines)
    mark5 = difference(intersection(th, diag_lines), keep3)
    base = replace(replace(I, FIVE, SEVEN), THREE, SEVEN)
    with3 = fill(base, THREE, keep3)
    O = fill(with3, FIVE, mark5)
    return O

def dsl5(I):
    z = ofcolor(I, ZERO)
    thobjs = colorfilter(objects(I, T, F, T), THREE)
    cond = fork(either, rbind(vmatching, z), rbind(hmatching, z))
    aligned = sfilter(thobjs, cond)
    keep3 = merge(apply(toindices, aligned))
    mark5 = difference(keep3, keep3)
    base = replace(replace(I, FIVE, SEVEN), THREE, SEVEN)
    with3 = fill(base, THREE, keep3)
    O = fill(with3, FIVE, mark5)
    return O
```