```python
def dsl1(I):
    H = hconcat(I, I)
    B = vconcat(H, H)
    R = rot180(B)
    O = cellwise(B, R, EIGHT)
    return O

def dsl2(I):
    H = hconcat(I, I)
    B = vconcat(H, H)
    BG = mostcolor(B)
    NZ = difference(asindices(B), ofcolor(B, BG))
    NZOBJ = toobject(NZ, B)
    BD = backdrop(NZOBJ)
    TGT = intersection(ofcolor(B, BG), BD)
    O = fill(B, EIGHT, TGT)
    return O

def dsl3(I):
    H = hconcat(I, I)
    B = vconcat(H, H)
    BG = mostcolor(B)
    RPL = replace(B, BG, EIGHT)
    NZ = difference(asindices(B), ofcolor(B, BG))
    NZOBJ = toobject(NZ, B)
    O = paint(RPL, NZOBJ)
    return O

def dsl4(I):
    H = hconcat(I, I)
    B = vconcat(H, H)
    P = asindices(B)
    BRD = box(P)
    BG = mostcolor(B)
    TGT = intersection(ofcolor(B, BG), BRD)
    O = fill(B, EIGHT, TGT)
    return O

def dsl5(I):
    H = hconcat(I, I)
    B = vconcat(H, H)
    BG = mostcolor(B)
    NZ = difference(asindices(B), ofcolor(B, BG))
    HF = merge(apply(hfrontier, NZ))
    VF = merge(apply(vfrontier, NZ))
    LNS = merge(combine(initset(HF), initset(VF)))
    TGT = intersection(ofcolor(B, BG), LNS)
    O = fill(B, EIGHT, TGT)
    return O
```