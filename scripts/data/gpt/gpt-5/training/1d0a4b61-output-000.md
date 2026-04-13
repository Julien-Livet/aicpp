```python
def dsl1(I):
    # Global propagation by multi-directional shifts: fill zeros by underpainting far-shifted nonzero cells
    idx_all = asindices(I)
    zeros = ofcolor(I, ZERO)
    nonzero_idx = difference(idx_all, zeros)
    obj = toobject(nonzero_idx, I)
    left2 = invert(ZERO_BY_TWO)
    left3 = add(LEFT, left2)
    left4 = invert(double(ZERO_BY_TWO))
    right2 = ZERO_BY_TWO
    right3 = add(RIGHT, ZERO_BY_TWO)
    right4 = double(ZERO_BY_TWO)
    up2 = invert(TWO_BY_ZERO)
    up3 = add(UP, up2)
    up4 = invert(double(TWO_BY_ZERO))
    down2 = TWO_BY_ZERO
    down3 = add(DOWN, TWO_BY_ZERO)
    down4 = double(TWO_BY_ZERO)
    S = shift(obj, LEFT)
    S = combine(S, shift(obj, right=RIGHT))
    S = combine(S, shift(obj, left2))
    S = combine(S, shift(obj, right2))
    S = combine(S, shift(obj, left3))
    S = combine(S, shift(obj, right3))
    S = combine(S, shift(obj, left4))
    S = combine(S, shift(obj, right4))
    S = combine(S, shift(obj, UP))
    S = combine(S, shift(obj, DOWN))
    S = combine(S, shift(obj, up2))
    S = combine(S, shift(obj, down2))
    S = combine(S, shift(obj, up3))
    S = combine(S, shift(obj, down3))
    S = combine(S, shift(obj, up4))
    S = combine(S, shift(obj, down4))
    O = underpaint(I, S)
    return O

def dsl2(I):
    # Global symmetry completion: underpaint mirrored nonzero content (horizontal, vertical, 180-rot)
    H = hmirror(I)
    V = vmirror(I)
    R = rot180(I)
    idx = asindices(I)
    objH = toobject(difference(idx, ofcolor(H, ZERO)), H)
    objV = toobject(difference(idx, ofcolor(V, ZERO)), V)
    objR = toobject(difference(idx, ofcolor(R, ZERO)), R)
    S = combine(objH, objV)
    S = combine(S, objR)
    O = underpaint(I, S)
    return O

def dsl3(I):
    # Object extraction over background: paint all nonzero cells over a canvas of the dominant color
    bg = mostcolor(I)
    base = canvas(bg, shape(I))
    idx_all = asindices(I)
    nonzero = difference(idx_all, ofcolor(I, ZERO))
    obj = toobject(nonzero, I)
    O = paint(base, obj)
    return O

def dsl4(I):
    # Geometric consistency via symmetric agreement: keep cells agreeing with mirrors, else fill with dominant color
    mc = mostcolor(I)
    A = cellwise(I, hmirror(I), mc)
    O = cellwise(A, vmirror(A), mc)
    return O

def dsl5(I):
    # Relational fill inside the global nonzero bounding box: fill holes (zeros within bbox) with dominant color
    mc = mostcolor(I)
    idx_all = asindices(I)
    nonzero = difference(idx_all, ofcolor(I, ZERO))
    box_idx = backdrop(nonzero)
    holes = difference(box_idx, nonzero)
    O = fill(I, mc, holes)
    return O
```