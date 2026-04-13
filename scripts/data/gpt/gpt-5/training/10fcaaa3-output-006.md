```python
def dsl1(I):
    H = hconcat(I, I)
    B = vconcat(H, H)
    L = lefthalf(B)
    R = righthalf(B)
    BG = mostcolor(L)
    L2 = replace(L, BG, EIGHT)
    O = hconcat(L2, R)
    return O

def dsl2(I):
    H = hconcat(I, I)
    B = vconcat(H, H)
    BG = mostcolor(B)
    NZ = difference(asindices(B), ofcolor(B, BG))
    HF = merge(apply(hfrontier, NZ))
    TGT = intersection(ofcolor(B, BG), HF)
    O = fill(B, EIGHT, TGT)
    return O

def dsl3(I):
    H = hconcat(I, I)
    B = vconcat(H, H)
    BG = mostcolor(B)
    NZ = difference(asindices(B), ofcolor(B, BG))
    NZOBJ = toobject(NZ, B)
    C = canvas(EIGHT, shape(B))
    O = paint(C, NZOBJ)
    return O

def dsl4(I):
    H = hconcat(I, I)
    B = vconcat(H, H)
    M = vmirror(B)
    O = cellwise(B, M, EIGHT)
    return O

def dsl5(I):
    H = hconcat(I, I)
    B = vconcat(H, H)
    BG = mostcolor(B)
    NZ = difference(asindices(B), ofcolor(B, BG))
    D = initset(UP)
    D = insert(DOWN, D)
    D = insert(LEFT, D)
    DIRS = insert(RIGHT, D)
    RAYS = prapply(shoot, NZ, DIRS)
    LNS = merge(RAYS)
    TGT = intersection(ofcolor(B, BG), LNS)
    O = fill(B, EIGHT, TGT)
    return O
```