```python
def dsl1(I):
    A = ofcolor(I, THREE)
    L = prapply(connect, A, A)
    HL = sfilter(L, hline)
    VL = sfilter(L, vline)
    Hset = merge(HL)
    Vset = merge(VL)
    M = intersection(Hset, Vset)
    TGT = difference(M, A)
    O = fill(I, FOUR, TGT)
    return O

def dsl2(I):
    A = ofcolor(I, THREE)
    P = product(A, A)
    objify = compose(lbind(toobject, I), initset)
    ffirst = compose(objify, first)
    flast = compose(objify, last)
    cond_h = fork(hmatching, ffirst, flast)
    cond_v = fork(vmatching, ffirst, flast)
    HP = sfilter(P, cond_h)
    VP = sfilter(P, cond_v)
    mkline = fork(connect, first, last)
    HL = apply(mkline, HP)
    VL = apply(mkline, VP)
    Hset = merge(HL)
    Vset = merge(VL)
    M = intersection(Hset, Vset)
    TGT = difference(M, A)
    O = fill(I, FOUR, TGT)
    return O

def dsl3(I):
    A = ofcolor(I, THREE)
    L = prapply(connect, A, A)
    HL = sfilter(L, hline)
    VL = sfilter(L, vline)
    Hset = merge(HL)
    Vset = merge(VL)
    M = intersection(Hset, Vset)
    O = underfill(I, FOUR, M)
    return O

def dsl4(I):
    OBJS = objects(I, F, F, T)
    O3 = colorfilter(OBJS, THREE)
    S3 = apply(toindices, O3)
    hconn = lbind(prapply, connect)
    sameboth = fork(hconn, identity, identity)
    LinesPerObj = apply(sameboth, S3)
    AllLines = merge(LinesPerObj)
    HL = sfilter(AllLines, hline)
    VL = sfilter(AllLines, vline)
    Hset = merge(HL)
    Vset = merge(VL)
    M = intersection(Hset, Vset)
    Z = ofcolor(I, ZERO)
    TGT = intersection(M, Z)
    O = fill(I, FOUR, TGT)
    return O

def dsl5(I):
    A = ofcolor(I, THREE)
    L = prapply(connect, A, A)
    HL = sfilter(L, hline)
    VL = sfilter(L, vline)
    Hset = merge(HL)
    Vset = merge(VL)
    M = intersection(Hset, Vset)
    ObjM = recolor(FOUR, toobject(M, I))
    O = underpaint(I, ObjM)
    return O
```