```python
def dsl1(I):
    H = hconcat(I, I)
    B = vconcat(H, H)
    R = rot90(B)
    O = cellwise(B, R, EIGHT)
    return O

def dsl2(I):
    H = hconcat(I, I)
    B = vconcat(H, H)
    OBJS = objects(B, T, F, T)
    BOXES = merge(apply(inbox, OBJS))
    OUT = difference(asindices(B), BOXES)
    O = fill(B, EIGHT, OUT)
    return O

def dsl3(I):
    H = hconcat(I, I)
    B = vconcat(H, H)
    BG = mostcolor(B)
    L = lefthalf(B)
    R = righthalf(B)
    L2 = replace(L, BG, EIGHT)
    O = hconcat(L2, R)
    return O

def dsl4(I):
    H = hconcat(I, I)
    B = vconcat(H, H)
    BG = mostcolor(B)
    NZ = difference(asindices(B), ofcolor(B, BG))
    HF = merge(apply(hfrontier, NZ))
    VF = merge(apply(vfrontier, NZ))
    FR = combine(HF, VF)
    TGT = intersection(ofcolor(B, BG), FR)
    O = fill(B, EIGHT, TGT)
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