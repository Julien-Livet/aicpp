```python
def dsl1(I):
    # Relational: tile 2x2, turn zeros to 8 except keep zeros adjacent to any non-zero
    H = hconcat(I, I)
    B = vconcat(H, H)
    NZ = difference(asindices(B), ofcolor(B, ZERO))
    NBRSETS = apply(neighbors, NZ)
    NBRS = merge(NBRSETS)
    BG = ofcolor(B, ZERO)
    KEEP = intersection(BG, NBRS)
    O1 = replace(B, ZERO, EIGHT)
    O = fill(O1, ZERO, KEEP)
    return O

def dsl2(I):
    # Structural: tile 2x2, then draw 8s along all color frontiers
    H = hconcat(I, I)
    B = vconcat(H, H)
    Fobjs = frontiers(B)
    FindexSets = apply(toindices, Fobjs)
    F = merge(FindexSets)
    O = fill(B, EIGHT, F)
    return O

def dsl3(I):
    # Global: tile 2x2, then convert zeros to 8 only in the top half
    H = hconcat(I, I)
    B = vconcat(H, H)
    TH = tophalf(B)
    BH = bottomhalf(B)
    T8 = replace(TH, ZERO, EIGHT)
    O = vconcat(T8, BH)
    return O

def dsl4(I):
    # Geometric: mirror-based 2x2 tiling (no color change)
    H = hconcat(I, vmirror(I))
    K = hmirror(H)
    O = vconcat(H, K)
    return O

def dsl5(I):
    # Box-based: tile 2x2, then paint 8s on the outline of the non-zero bounding box
    H = hconcat(I, I)
    B = vconcat(H, H)
    NZ = difference(asindices(B), ofcolor(B, ZERO))
    NZOBJ = toobject(NZ, B)
    BX = box(NZOBJ)
    O = fill(B, EIGHT, BX)
    return O
```