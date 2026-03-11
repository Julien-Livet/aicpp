```python
def dsl1(I):
    # Shear right by row index: (i, j) -> (i, j + i) when inside bounds
    H, W = shape(I)
    idxs = asindices(I)
    O = canvas(ZERO, astuple(H, W))
    for v, loc in totuple(asobject(I)):
        if v == ZERO:
            continue
        i, j = loc
        newloc = add(astuple(i, j), astuple(ZERO, i))
        if contained(newloc, idxs):
            O = fill(O, v, initset(newloc))
    return O

def dsl2(I):
    # From every nonzero cell, draw rays in the four orthogonal directions (↑, ↓, ←, →)
    H, W = shape(I)
    O = canvas(ZERO, astuple(H, W))
    for v, loc in totuple(asobject(I)):
        if v == ZERO:
            continue
        for d in (UP, DOWN, LEFT, RIGHT):
            ray = shoot(loc, d)
            O = fill(O, v, ray)
    return O

def dsl3(I):
    # Mirror along counter-diagonal and underpaint the original on top
    O = cmirror(I)
    O = underpaint(O, asobject(I))
    return O

def dsl4(I):
    # Overlay the four rotations of the input
    H, W = shape(I)
    O = canvas(ZERO, astuple(H, W))
    for G in (I, rot90(I), rot180(I), rot270(I)):
        O = underpaint(O, asobject(G))
    return O

def dsl5(I):
    # From each nonzero cell, draw a straight line to the lower-right corner
    H, W = shape(I)
    br = astuple(subtract(H, ONE), subtract(W, ONE))
    O = canvas(ZERO, astuple(H, W))
    for v, loc in totuple(asobject(I)):
        if v == ZERO:
            continue
        path = connect(loc, br)
        O = fill(O, v, path)
    return O
```