```python
def dsl1(I):
    # Relational: tile 2x2, then fill 8 on background cells that are not in any row or column containing a nonzero (via line shoots)
    H = hconcat(I, I)
    B = vconcat(H, H)
    NZ = difference(asindices(B), ofcolor(B, ZERO))
    Ls = apply(lbind(shoot, LEFT), NZ)
    Rs = apply(lbind(shoot, RIGHT), NZ)
    Us = apply(lbind(shoot, UP), NZ)
    Ds = apply(lbind(shoot, DOWN), NZ)
    ROWS = merge(combine(Ls, Rs))
    COLS = merge(combine(Us, Ds))
    LINES = merge(combine(initset(ROWS), initset(COLS)))
    BG = ofcolor(B, ZERO)
    FAR = difference(BG, LINES)
    O = fill(B, EIGHT, FAR)
    return O

def dsl2(I):
    # Structural: tile 2x2, then paint 8s on frontiers thickened by one-neighbor dilation
    H = hconcat(I, I)
    B = vconcat(H, H)
    Fobjs = frontiers(B)
    F = merge(apply(toindices, Fobjs))
    N = merge(apply(neighbors, F))
    BAND = merge(combine(initset(F), initset(N)))
    O = fill(B, EIGHT, BAND)
    return O

def dsl3(I):
    # Global: tile 2x2, then underfill the top half background with 8s and keep the bottom half unchanged
    H = hconcat(I, I)
    B = vconcat(H, H)
    TH = tophalf(B)
    BH = bottomhalf(B)
    T8 = underfill(TH, EIGHT, asindices(TH))
    O = vconcat(T8, BH)
    return O

def dsl4(I):
    # Geometric: mirror-based 2x2 tiling, then overlay 8s on a shifted union of the nonzero bounding-box outline
    H = hconcat(I, vmirror(I))
    K = hmirror(H)
    B = vconcat(H, K)
    NZ = difference(asindices(B), ofcolor(B, ZERO))
    NZOBJ = toobject(NZ, B)
    BX = box(NZOBJ)
    BXr = shift(BX, RIGHT)
    BXd = shift(BX, DOWN)
    PAT = merge(combine(combine(initset(BX), initset(BXr)), initset(BXd)))
    O = fill(B, EIGHT, PAT)
    return O

def dsl5(I):
    # Object extraction: tile 2x2, then fill 8s in the interior of the nonzero bounding rectangle (excluding the nonzeros)
    H = hconcat(I, I)
    B = vconcat(H, H)
    NZ = difference(asindices(B), ofcolor(B, ZERO))
    NZOBJ = toobject(NZ, B)
    BD = backdrop(NZOBJ)
    HOLES = difference(BD, toindices(NZOBJ))
    O = fill(B, EIGHT, HOLES)
    return O
```