```python
def dsl1(I):
    # Global: crop all foreground and place it at the start of the bottom half
    parts = objects(I, T, F, T)
    fg = merge(parts)
    cropped = subgrid(fg, I)
    off = astuple(halve(height(I)), ZERO)
    O = move(canvas(ZERO, shape(I)), asobject(cropped), off)
    return O

def dsl2(I):
    # Object extraction (bottom half): keep {1,2,4,8} and add a horizontal 3-wire across their span
    B = bottomhalf(I)
    p1 = ofcolor(B, ONE)
    p2 = ofcolor(B, TWO)
    p4 = ofcolor(B, FOUR)
    p8 = ofcolor(B, EIGHT)
    sel = combine(combine(p1, p2), combine(p4, p8))
    bl = llcorner(sel)
    br = lrcorner(sel)
    wire = recolor(THREE, connect(bl, br))
    obj = toobject(sel, B)
    both = combine(obj, wire)
    off = astuple(halve(height(I)), ZERO)
    O = move(canvas(ZERO, shape(I)), both, off)
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
    # Geometric: mirror the bottom-half selection {1,2,4,8} horizontally (left-right) and place in bottom half
    B = bottomhalf(I)
    HB = vmirror(B)
    q1 = ofcolor(HB, ONE)
    q2 = ofcolor(HB, TWO)
    q4 = ofcolor(HB, FOUR)
    q8 = ofcolor(HB, EIGHT)
    sel = combine(combine(q1, q2), combine(q4, q8))
    obj = toobject(sel, HB)
    off = astuple(halve(height(I)), ZERO)
    O = move(canvas(ZERO, shape(I)), obj, off)
    return O

def dsl5(I):
    # Relational: connect centers of leftmost and rightmost {1,2,4,8} objects in bottom half with 3-wire and keep them
    B = bottomhalf(I)
    parts = objects(B, T, F, T)
    a = colorfilter(parts, ONE)
    b = colorfilter(parts, TWO)
    c = colorfilter(parts, FOUR)
    d = colorfilter(parts, EIGHT)
    selparts = merge((a, merge((b, merge((c, d))))))  # union of selected color objects
    L = argmin(selparts, leftmost)
    R = argmax(selparts, rightmost)
    c1 = center(L)
    c2 = center(R)
    wire = recolor(THREE, connect(c1, c2))
    sel = combine(combine(ofcolor(B, ONE), ofcolor(B, TWO)), combine(ofcolor(B, FOUR), ofcolor(B, EIGHT)))
    obj = toobject(sel, B)
    both = combine(obj, wire)
    off = astuple(halve(height(I)), ZERO)
    O = move(canvas(ZERO, shape(I)), both, off)
    return O
```