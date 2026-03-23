```python
def dsl1(I):
    z = ofcolor(I, ZERO)
    th = ofcolor(I, THREE)
    vcols = merge(mapply(vfrontier, z))
    hrows = merge(mapply(hfrontier, z))
    band = combine(vcols, hrows)
    keep = intersection(th, band)
    marks = intersection(th, merge(mapply(ineighbors, z)))
    base = replace(replace(I, FIVE, SEVEN), THREE, SEVEN)
    with3 = fill(base, THREE, keep)
    O = fill(with3, FIVE, marks)
    return O

def dsl2(I):
    z = ofcolor(I, ZERO)
    thobjs = colorfilter(objects(I, T, F, T), THREE)
    adjobjs = sfilter(thobjs, rbind(adjacent, z))
    patches = apply(toindices, adjobjs)
    orth = merge(mapply(neighbors, z))
    contacts = apply(lbind(intersection, orth), patches)
    keep = merge(contacts)
    corners = apply(ulcorner, contacts)
    marks = merge(apply(initset, corners))
    base = replace(replace(I, FIVE, SEVEN), THREE, SEVEN)
    with3 = fill(base, THREE, keep)
    O = fill(with3, FIVE, marks)
    return O

def dsl3(I):
    z = ofcolor(I, ZERO)
    th = ofcolor(I, THREE)
    orth = merge(mapply(neighbors, z))
    diag = merge(mapply(ineighbors, z))
    near = combine(orth, diag)
    keep = intersection(th, near)
    marks = intersection(th, diag)
    base = replace(replace(I, FIVE, SEVEN), THREE, SEVEN)
    with3 = fill(base, THREE, keep)
    O = fill(with3, FIVE, marks)
    return O

def dsl4(I):
    z = ofcolor(I, ZERO)
    th = ofcolor(I, THREE)
    lines = merge(prapply(connect, z, z))
    keep = intersection(th, lines)
    marks = intersection(th, merge(mapply(ineighbors, z)))
    base = replace(replace(I, FIVE, SEVEN), THREE, SEVEN)
    with3 = fill(base, THREE, keep)
    O = fill(with3, FIVE, marks)
    return O

def dsl5(I):
    z = ofcolor(I, ZERO)
    th = ofcolor(I, THREE)
    cols = combine(merge(mapply(rbind(shoot, UP), z)), merge(mapply(rbind(shoot, DOWN), z)))
    rows = combine(merge(mapply(rbind(shoot, LEFT), z)), merge(mapply(rbind(shoot, RIGHT), z)))
    rightcols = shift(cols, RIGHT)
    downrows = shift(rows, DOWN)
    band = combine(rightcols, downrows)
    keep = intersection(th, band)
    marks = intersection(th, merge(mapply(ineighbors, z)))
    base = replace(replace(I, FIVE, SEVEN), THREE, SEVEN)
    with3 = fill(base, THREE, keep)
    O = fill(with3, FIVE, marks)
    return O
```