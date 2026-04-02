```python
def dsl1(I):
    # Global: 2x2 tiling, then fill 8s on the entire left half background; keep right half unchanged
    H = hconcat(I, I)
    B = vconcat(H, H)
    LH = lefthalf(B)
    RH = righthalf(B)
    L8 = underfill(LH, EIGHT, asindices(LH))
    O = hconcat(L8, RH)
    return O

def dsl2(I):
    # Object extraction: 2x2 tiling, then fill 8s outside the bounding box of all nonzeros
    H = hconcat(I, I)
    B = vconcat(H, H)
    BG = mostcolor(B)
    NZ = difference(asindices(B), ofcolor(B, BG))
    NZOBJ = toobject(NZ, B)
    BD = backdrop(NZOBJ)
    OUT = difference(asindices(B), BD)
    O = fill(B, EIGHT, OUT)
    return O

def dsl3(I):
    # Color filtering: 2x2 tiling, then place 8s on background cells along horizontal and vertical frontiers induced by nonzeros
    H = hconcat(I, I)
    B = vconcat(H, H)
    BG = mostcolor(B)
    NZ = difference(asindices(B), ofcolor(B, BG))
    HF = merge(apply(hfrontier, NZ))
    VF = merge(apply(vfrontier, NZ))
    BAND = merge(combine(initset(HF), initset(VF)))
    TGT = intersection(ofcolor(B, BG), BAND)
    O = fill(B, EIGHT, TGT)
    return O

def dsl4(I):
    # Geometric: 2x2 tiling, then draw both main diagonals with 8s (only on background)
    H = hconcat(I, I)
    B = vconcat(H, H)
    P = asindices(B)
    UL = ulcorner(P)
    UR = urcorner(P)
    LL = llcorner(P)
    LR = lrcorner(P)
    D1 = connect(UL, LR)
    D2 = connect(UR, LL)
    DIAG = merge(combine(initset(D1), initset(D2)))
    O = underfill(B, EIGHT, DIAG)
    return O

def dsl5(I):
    # Relational: 2x2 tiling, then shoot rays from each nonzero in four directions and fill 8s along those rays where background
    H = hconcat(I, I)
    B = vconcat(H, H)
    BG = mostcolor(B)
    NZ = difference(asindices(B), ofcolor(B, BG))
    Ls = merge(apply(lbind(shoot, LEFT), NZ))
    Rs = merge(apply(lbind(shoot, RIGHT), NZ))
    Us = merge(apply(lbind(shoot, UP), NZ))
    Ds = merge(apply(lbind(shoot, DOWN), NZ))
    RAYS = merge(combine(combine(initset(Ls), initset(Rs)), combine(initset(Us), initset(Ds))))
    TGT = intersection(ofcolor(B, BG), RAYS)
    O = fill(B, EIGHT, TGT)
    return O
```