```python
def dsl1(I):
    H = hconcat(I, I)
    B = vconcat(H, H)
    HM = hmirror(B)
    VM = vmirror(B)
    C1 = cellwise(B, HM, EIGHT)
    C2 = cellwise(C1, VM, EIGHT)
    BG = mostcolor(B)
    NZ = difference(asindices(B), ofcolor(B, BG))
    OBJ = toobject(NZ, B)
    O = paint(C2, OBJ)
    return O

def dsl2(I):
    H = hconcat(I, I)
    B = vconcat(H, H)
    FRS = frontiers(B)
    MU = merge(FRS)
    O = underfill(B, EIGHT, MU)
    return O

def dsl3(I):
    H = hconcat(I, I)
    B = vconcat(H, H)
    OBJS = objects(B, T, F, T)
    MU = merge(OBJS)
    IND = toindices(MU)
    DLT = delta(IND)
    O = underfill(B, EIGHT, DLT)
    return O

def dsl4(I):
    H = hconcat(I, I)
    B = vconcat(H, H)
    BG = mostcolor(B)
    NZ = difference(asindices(B), ofcolor(B, BG))
    HR = merge(apply(hfrontier, NZ))
    VR = merge(apply(vfrontier, NZ))
    LNS = combine(HR, VR)
    O = underfill(B, EIGHT, LNS)
    return O

def dsl5(I):
    H = hconcat(I, I)
    B = vconcat(H, H)
    BG = mostcolor(B)
    NZ = difference(asindices(B), ofcolor(B, BG))
    D = initset(UP)
    D = insert(DOWN, D)
    D = insert(LEFT, D)
    D = insert(RIGHT, D)
    RAYS = prapply(shoot, NZ, D)
    LNS = merge(RAYS)
    O = underfill(B, EIGHT, LNS)
    return O
```