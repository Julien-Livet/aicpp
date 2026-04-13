```python
def dsl1(I):
    # Global: compress and bottom-align the compressed foreground
    C = compress(I)
    obj = asobject(C)
    offrow = subtract(height(I), height(C))
    off = astuple(offrow, ZERO)
    O = move(canvas(ZERO, shape(I)), obj, off)
    return O

def dsl2(I):
    # Object extraction: keep {1,2,4,8} in bottom half, preserve their positions there
    B = bottomhalf(I)
    p1 = ofcolor(B, ONE)
    p2 = ofcolor(B, TWO)
    p4 = ofcolor(B, FOUR)
    p8 = ofcolor(B, EIGHT)
    sel = combine(combine(p1, p2), combine(p4, p8))
    obj = toobject(sel, B)
    off = astuple(halve(height(I)), ZERO)
    O = move(canvas(ZERO, shape(I)), obj, off)
    return O

def dsl3(I):
    # Color filtering: keep only colors {1,2,4,8} everywhere
    p1 = ofcolor(I, ONE)
    p2 = ofcolor(I, TWO)
    p4 = ofcolor(I, FOUR)
    p8 = ofcolor(I, EIGHT)
    sel = combine(combine(p1, p2), combine(p4, p8))
    obj = toobject(sel, I)
    O = paint(canvas(ZERO, shape(I)), obj)
    return O

def dsl4(I):
    # Geometric: mirror the selected colors {1,2,4,8} left-right over the whole grid
    M = vmirror(I)
    q1 = ofcolor(M, ONE)
    q2 = ofcolor(M, TWO)
    q4 = ofcolor(M, FOUR)
    q8 = ofcolor(M, EIGHT)
    sel = combine(combine(q1, q2), combine(q4, q8))
    obj = toobject(sel, M)
    O = paint(canvas(ZERO, shape(I)), obj)
    return O

def dsl5(I):
    # Relational: in bottom half, keep {1,2,4,8} and add a 3-wire: bottom edge + verticals at extreme columns within their bbox
    B = bottomhalf(I)
    p1 = ofcolor(B, ONE)
    p2 = ofcolor(B, TWO)
    p4 = ofcolor(B, FOUR)
    p8 = ofcolor(B, EIGHT)
    sel = combine(combine(p1, p2), combine(p4, p8))
    bl = llcorner(sel)
    br = lrcorner(sel)
    base = recolor(THREE, connect(bl, br))
    BB = backdrop(sel)
    vL = intersection(vfrontier(bl), BB)
    vR = intersection(vfrontier(br), BB)
    pillars = recolor(THREE, combine(vL, vR))
    obj = toobject(sel, B)
    both = combine(obj, combine(base, pillars))
    off = astuple(halve(height(I)), ZERO)
    O = move(canvas(ZERO, shape(I)), both, off)
    return O
```