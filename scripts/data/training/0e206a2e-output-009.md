```python
def dsl1(I):
    # Global: compress and place at bottom-right
    C = compress(I)
    obj = asobject(C)
    off = subtract(shape(I), shape(C))
    O = move(canvas(ZERO, shape(I)), obj, off)
    return O

def dsl2(I):
    # Geometric: drop all nonzeros straight down to the bottom border
    NZ = difference(asindices(I), ofcolor(I, ZERO))
    obj = toobject(NZ, I)
    P = asindices(I)
    B = connect(llcorner(P), lrcorner(P))
    off = gravitate(NZ, B)
    O = move(canvas(ZERO, shape(I)), obj, off)
    return O

def dsl3(I):
    # Object extraction: keep the largest foreground object and place it at bottom-left
    OBJS = fgpartition(I)
    BIG = argmax(OBJS, size)
    G = subgrid(BIG, I)
    obj = asobject(G)
    off = astuple(subtract(height(I), height(G)), ZERO)
    O = move(canvas(ZERO, shape(I)), obj, off)
    return O

def dsl4(I):
    # Color filtering: keep least frequent nonzero color, crop it, and place at bottom-left
    CSET = remove(ZERO, palette(I))
    c = valmin(CSET, lbind(colorcount, I))
    S = ofcolor(I, c)
    G = subgrid(toobject(S, I), I)
    obj = asobject(G)
    off = astuple(subtract(height(I), height(G)), ZERO)
    O = move(canvas(ZERO, shape(I)), obj, off)
    return O

def dsl5(I):
    # Relational: move all nonzeros to be adjacent to the grid center
    NZ = difference(asindices(I), ofcolor(I, ZERO))
    obj = toobject(NZ, I)
    P = asindices(I)
    Cpt = initset(center(P))
    off = gravitate(NZ, Cpt)
    O = move(canvas(ZERO, shape(I)), obj, off)
    return O
```