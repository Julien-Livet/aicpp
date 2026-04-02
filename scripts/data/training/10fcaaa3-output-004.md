```python
def dsl1(I):
    H = hconcat(I, I)
    B = vconcat(H, H)
    BG = mostcolor(B)
    NZ = difference(asindices(B), ofcolor(B, BG))
    HF = merge(apply(hfrontier, NZ))
    ALL = asindices(B)
    ZR = difference(ALL, HF)
    O = fill(B, EIGHT, ZR)
    return O

def dsl2(I):
    H = hconcat(I, I)
    B = vconcat(H, H)
    BG = mostcolor(B)
    NZ = difference(asindices(B), ofcolor(B, BG))
    NZOBJ = toobject(NZ, B)
    BD = backdrop(NZOBJ)
    HF = merge(apply(hfrontier, NZ))
    VF = merge(apply(vfrontier, NZ))
    HV = merge(combine(initset(HF), initset(VF)))
    INBOX_NOT_HV = difference(BD, HV)
    TGT = intersection(ofcolor(B, BG), INBOX_NOT_HV)
    O = fill(B, EIGHT, TGT)
    return O

def dsl3(I):
    H = hconcat(I, I)
    B = vconcat(H, H)
    BG = mostcolor(B)
    NZ = difference(asindices(B), ofcolor(B, BG))
    NZOBJ = toobject(NZ, B)
    DLT = delta(NZOBJ)
    TGT = intersection(ofcolor(B, BG), DLT)
    O = fill(B, EIGHT, TGT)
    return O

def dsl4(I):
    H = hconcat(I, I)
    B = vconcat(H, H)
    P = asindices(B)
    C = center(P)
    HLINE = hfrontier(C)
    VLINE = vfrontier(C)
    CROSS = merge(combine(initset(HLINE), initset(VLINE)))
    BG = mostcolor(B)
    TGT = intersection(ofcolor(B, BG), CROSS)
    O = fill(B, EIGHT, TGT)
    return O

def dsl5(I):
    H = hconcat(I, I)
    B = vconcat(H, H)
    BG = mostcolor(B)
    NZ = difference(asindices(B), ofcolor(B, BG))
    N1 = merge(apply(neighbors, NZ))
    N2 = merge(apply(neighbors, N1))
    R2 = difference(difference(N2, N1), NZ)
    TGT = intersection(ofcolor(B, BG), R2)
    O = fill(B, EIGHT, TGT)
    return O
```