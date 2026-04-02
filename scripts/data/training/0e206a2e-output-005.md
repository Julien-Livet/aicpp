```python
def dsl1(I):
    # Global: compress bottom half and place it bottom-right
    B = bottomhalf(I)
    C = compress(B)
    obj = asobject(C)
    dr = subtract(height(I), height(C))
    dc = subtract(width(I), width(C))
    off = astuple(dr, dc)
    O = move(canvas(ZERO, shape(I)), obj, off)
    return O

def dsl2(I):
    # Object extraction: take {1,2,4,8} and drop them to the bottom
    p1 = ofcolor(I, ONE)
    p2 = ofcolor(I, TWO)
    p4 = ofcolor(I, FOUR)
    p8 = ofcolor(I, EIGHT)
    S = combine(combine(p1, p2), combine(p4, p8))
    obj = toobject(S, I)
    dr = subtract(subtract(height(I), ONE), lowermost(S))
    off = astuple(dr, ZERO)
    O = move(canvas(ZERO, shape(I)), obj, off)
    return O

def dsl3(I):
    # Color filtering: keep only the least-common nonzero color
    FG = asobject(I)
    c = leastcolor(FG)
    P = ofcolor(I, c)
    obj = toobject(P, I)
    O = paint(canvas(ZERO, shape(I)), obj)
    return O

def dsl4(I):
    # Geometric: combine vertical and horizontal mirrors of {1,2,4,8}
    V = vmirror(I)
    H = hmirror(I)
    v1 = ofcolor(V, ONE); v2 = ofcolor(V, TWO); v4 = ofcolor(V, FOUR); v8 = ofcolor(V, EIGHT)
    h1 = ofcolor(H, ONE); h2 = ofcolor(H, TWO); h4 = ofcolor(H, FOUR); h8 = ofcolor(H, EIGHT)
    SV = combine(combine(v1, v2), combine(v4, v8))
    SH = combine(combine(h1, h2), combine(h4, h8))
    oV = toobject(SV, V)
    oH = toobject(SH, H)
    both = combine(oV, oH)
    O = paint(canvas(ZERO, shape(I)), both)
    return O

def dsl5(I):
    # Relational: draw a 3-colored frame around the bbox of {1,2,4,8}
    p1 = ofcolor(I, ONE)
    p2 = ofcolor(I, TWO)
    p4 = ofcolor(I, FOUR)
    p8 = ofcolor(I, EIGHT)
    S = combine(combine(p1, p2), combine(p4, p8))
    frame = recolor(THREE, box(S))
    sel = toobject(S, I)
    both = combine(sel, frame)
    O = paint(canvas(ZERO, shape(I)), both)
    return O
```