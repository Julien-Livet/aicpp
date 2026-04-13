```python
def dsl1(I):
    S1 = ofcolor(I, ONE)
    S3 = ofcolor(I, THREE)
    S2 = ofcolor(I, TWO)
    R1 = mapply(hfrontier, S1)
    R3 = mapply(hfrontier, S3)
    C2 = mapply(vfrontier, S2)
    G0 = fill(I, TWO, C2)
    G1 = fill(G0, THREE, R3)
    O = fill(G1, ONE, R1)
    return O

def dsl2(I):
    Os = objects(I, T, F, T)
    O1s = colorfilter(Os, ONE)
    O3s = colorfilter(Os, THREE)
    O2s = colorfilter(Os, TWO)
    fhr = compose(hfrontier, center)
    fvr = compose(vfrontier, center)
    R1idx = mapply(fhr, O1s)
    R3idx = mapply(fhr, O3s)
    C2idx = mapply(fvr, O2s)
    R1obj = recolor(ONE, R1idx)
    R3obj = recolor(THREE, R3idx)
    C2obj = recolor(TWO, C2idx)
    Z = canvas(ZERO, shape(I))
    G0 = paint(Z, C2obj)
    G1 = paint(G0, R3obj)
    O = paint(G1, R1obj)
    return O

def dsl3(I):
    S1 = ofcolor(I, ONE)
    S3 = ofcolor(I, THREE)
    S2 = ofcolor(I, TWO)
    toR = rbind(shoot, RIGHT)
    toL = rbind(shoot, LEFT)
    toU = rbind(shoot, UP)
    toD = rbind(shoot, DOWN)
    R1 = combine(mapply(toR, S1), mapply(toL, S1))
    R3 = combine(mapply(toR, S3), mapply(toL, S3))
    C2 = combine(mapply(toU, S2), mapply(toD, S2))
    G0 = fill(I, TWO, C2)
    G1 = fill(G0, THREE, R3)
    O = fill(G1, ONE, R1)
    return O

def dsl4(I):
    S1 = ofcolor(I, ONE)
    S3 = ofcolor(I, THREE)
    S2 = ofcolor(I, TWO)
    R1idx = mapply(hfrontier, S1)
    R3idx = mapply(hfrontier, S3)
    C2idx = mapply(vfrontier, S2)
    Z = I
    G0 = underfill(Z, TWO, C2idx)
    G1 = paint(G0, recolor(THREE, R3idx))
    O = paint(G1, recolor(ONE, R1idx))
    return O

def dsl5(I):
    S13 = combine(ofcolor(I, ONE), ofcolor(I, THREE))
    S2 = ofcolor(I, TWO)
    Dh = insert(RIGHT, initset(LEFT))
    Dv = insert(DOWN, initset(UP))
    Hparts = prapply(shoot, S13, Dh)
    Vparts = prapply(shoot, S2, Dv)
    Hmask = merge(Hparts)
    Vmask = merge(Vparts)
    G0 = fill(I, TWO, Vmask)
    G1 = fill(G0, THREE, intersection(Hmask, ofcolor(fill(canvas(ZERO, shape(I)), THREE, Hmask), THREE)))
    O = fill(G1, ONE, Hmask)
    return O
```