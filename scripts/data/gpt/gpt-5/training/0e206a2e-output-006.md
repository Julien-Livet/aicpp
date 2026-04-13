```python
def dsl1(I):
    # Global: compress entire grid and place it bottom-left
    C = compress(I)
    obj = asobject(C)
    dr = subtract(height(I), height(C))
    off = astuple(dr, ZERO)
    O = move(canvas(ZERO, shape(I)), obj, off)
    return O

def dsl2(I):
    # Object extraction: take {1,2,4,8}, crop and compress their bbox, drop to bottom-left
    p1 = ofcolor(I, ONE)
    p2 = ofcolor(I, TWO)
    p4 = ofcolor(I, FOUR)
    p8 = ofcolor(I, EIGHT)
    S = combine(combine(p1, p2), combine(p4, p8))
    obj = toobject(S, I)
    G = subgrid(obj, I)
    C = compress(G)
    objC = asobject(C)
    dr = subtract(height(I), height(C))
    off = astuple(dr, ZERO)
    O = move(canvas(ZERO, shape(I)), objC, off)
    return O

def dsl3(I):
    # Color filtering: map {1,2,3,4} -> 8, compress result, place bottom-left
    J1 = replace(I, ONE, EIGHT)
    J2 = replace(J1, TWO, EIGHT)
    J3 = replace(J2, THREE, EIGHT)
    J4 = replace(J3, FOUR, EIGHT)
    C = compress(J4)
    obj = asobject(C)
    dr = subtract(height(I), height(C))
    off = astuple(dr, ZERO)
    O = move(canvas(ZERO, shape(I)), obj, off)
    return O

def dsl4(I):
    # Geometric: union of {1,2,3,4,8} from I and its 180° rotation
    R = rot180(I)
    i1 = ofcolor(I, ONE); i2 = ofcolor(I, TWO); i3 = ofcolor(I, THREE); i4 = ofcolor(I, FOUR); i8 = ofcolor(I, EIGHT)
    r1 = ofcolor(R, ONE); r2 = ofcolor(R, TWO); r3 = ofcolor(R, THREE); r4 = ofcolor(R, FOUR); r8 = ofcolor(R, EIGHT)
    SI = combine(combine(combine(i1, i2), combine(i3, i4)), i8)
    SR = combine(combine(combine(r1, r2), combine(r3, r4)), r8)
    oI = toobject(SI, I)
    oR = toobject(SR, R)
    both = combine(oI, oR)
    O = paint(canvas(ZERO, shape(I)), both)
    return O

def dsl5(I):
    # Relational: move {1,2,4,8} so their center of mass aligns with grid center
    p1 = ofcolor(I, ONE)
    p2 = ofcolor(I, TWO)
    p4 = ofcolor(I, FOUR)
    p8 = ofcolor(I, EIGHT)
    S = combine(combine(p1, p2), combine(p4, p8))
    cm_grid = center(asindices(I))
    cm_sel = centerofmass(S)
    off = subtract(cm_grid, cm_sel)
    obj = toobject(S, I)
    O = move(canvas(ZERO, shape(I)), obj, off)
    return O
```