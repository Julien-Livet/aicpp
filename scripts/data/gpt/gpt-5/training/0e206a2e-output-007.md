```python
def dsl1(I):
    # Global: compress full grid and place at bottom-right
    C = compress(I)
    obj = asobject(C)
    dr = subtract(height(I), height(C))
    dc = subtract(width(I), width(C))
    off = astuple(dr, dc)
    O = move(canvas(ZERO, shape(I)), obj, off)
    return O

def dsl2(I):
    # Object extraction: move all nonzero cells so their lower-right aligns with grid lower-right
    NZ = difference(asindices(I), ofcolor(I, ZERO))
    obj = toobject(NZ, I)
    off = subtract(lrcorner(asindices(I)), lrcorner(toindices(obj)))
    O = move(canvas(ZERO, shape(I)), obj, off)
    return O

def dsl3(I):
    # Color filtering: merge {1,2,4} into 3, keep 8, zero the top half
    J1 = replace(I, ONE, THREE)
    J2 = replace(J1, TWO, THREE)
    J3 = replace(J2, FOUR, THREE)
    TopZero = canvas(ZERO, shape(tophalf(I)))
    O = vconcat(TopZero, bottomhalf(J3))
    return O

def dsl4(I):
    # Geometric: drop all nonzero cells straight down until adjacent to bottom border
    NZ = difference(asindices(I), ofcolor(I, ZERO))
    obj = toobject(NZ, I)
    P = asindices(I)
    B = connect(llcorner(P), lrcorner(P))
    off = gravitate(NZ, B)
    O = move(canvas(ZERO, shape(I)), obj, off)
    return O

def dsl5(I):
    # Relational: move all non-4 colors to be adjacent to the 4s; keep 4s fixed
    S4 = ofcolor(I, FOUR)
    NZ = difference(asindices(I), ofcolor(I, ZERO))
    Snot4 = difference(NZ, S4)
    obj = toobject(Snot4, I)
    off = gravitate(Snot4, S4)
    Moved = move(canvas(ZERO, shape(I)), obj, off)
    o4 = toobject(S4, I)
    O = paint(Moved, o4)
    return O
```