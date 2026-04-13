```python
def dsl1(I):
    # Global: compress and place at bottom-left
    C = compress(I)
    obj = asobject(C)
    dr = subtract(height(I), height(C))
    off = astuple(dr, ZERO)
    O = move(canvas(ZERO, shape(I)), obj, off)
    return O

def dsl2(I):
    # Object extraction: move all nonzeros horizontally to the right border
    NZ = difference(asindices(I), ofcolor(I, ZERO))
    obj = toobject(NZ, I)
    P = asindices(I)
    Right = connect(urcorner(P), lrcorner(P))
    off = gravitate(NZ, Right)
    O = move(canvas(ZERO, shape(I)), obj, off)
    return O

def dsl3(I):
    # Color filtering: keep only the dominant nonzero color
    P = remove(ZERO, palette(I))
    dom = valmax(P, lbind(colorcount, I))
    S = ofcolor(I, dom)
    O = paint(canvas(ZERO, shape(I)), toobject(S, I))
    return O

def dsl4(I):
    # Geometric: drop only the dominant color straight down to the bottom border
    P = asindices(I)
    B = connect(llcorner(P), lrcorner(P))
    dom = valmax(remove(ZERO, palette(I)), lbind(colorcount, I))
    Sdom = ofcolor(I, dom)
    objdom = toobject(Sdom, I)
    off = gravitate(Sdom, B)
    O = move(canvas(ZERO, shape(I)), objdom, off)
    return O

def dsl5(I):
    # Relational: move all non-dominant colors to be adjacent to the dominant color; keep dominant fixed
    NZ = difference(asindices(I), ofcolor(I, ZERO))
    dom = valmax(remove(ZERO, palette(I)), lbind(colorcount, I))
    Sdom = ofcolor(I, dom)
    Snot = difference(NZ, Sdom)
    objNot = toobject(Snot, I)
    off = gravitate(Snot, Sdom)
    Moved = move(canvas(ZERO, shape(I)), objNot, off)
    O = paint(Moved, toobject(Sdom, I))
    return O
```