```python
def dsl1(I):
    # Connect every pair of same-color objects (no row/col restriction)
    O = I
    obs = totuple(objects(I, T, F, T))
    for a in obs:
        ca = color(a)
        la = ulcorner(a)
        for b in obs:
            if a == b:
                continue
            if color(b) != ca:
                continue
            lb = ulcorner(b)
            seg = connect(la, lb)
            O = fill(O, ca, seg)
    return O

def dsl2(I):
    # For each color, fill its bounding box completely
    O = I
    cols = remove(ZERO, palette(I))
    for c in totuple(cols):
        inds = ofcolor(I, c)
        if size(inds) == 0:
            continue
        bb = backdrop(inds)
        O = fill(O, c, bb)
    return O

def dsl3(I):
    # From each nonzero cell, extend rays along both diagonals
    O = I
    nz = difference(asindices(I), ofcolor(I, ZERO))
    for loc in totuple(nz):
        v = index(I, loc)
        r1 = shoot(loc, UP_RIGHT)
        r2 = shoot(loc, DOWN_LEFT)
        r3 = shoot(loc, UP_LEFT)
        r4 = shoot(loc, DOWN_RIGHT)
        patch = combine(combine(r1, r2), combine(r3, r4))
        O = fill(O, v, patch)
    return O

def dsl4(I):
    # Draw the outline of the bounding box of all nonzeros using the least frequent color
    nz = difference(asindices(I), ofcolor(I, ZERO))
    if size(nz) == 0:
        return I
    bb = box(backdrop(nz))
    c = leastcolor(I)
    O = fill(I, c, bb)
    return O

def dsl5(I):
    # For each color, connect all pairs that share a row or a column at the cell level
    O = I
    cols = remove(ZERO, palette(I))
    for c in totuple(cols):
        pts = totuple(ofcolor(I, c))
        for a in pts:
            for b in pts:
                if a == b:
                    continue
                if a[0] == b[0] or a[1] == b[1]:
                    seg = connect(a, b)
                    O = fill(O, c, seg)
    return O
```