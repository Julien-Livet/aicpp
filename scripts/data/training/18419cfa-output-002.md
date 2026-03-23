```python
def dsl1(I):
    OB = objects(I, T, F, T)
    EO = colorfilter(OB, EIGHT)
    IN = merge(mapply(inbox, EO))
    P0 = ofcolor(vmirror(I), TWO)
    P1 = ofcolor(hmirror(I), TWO)
    P = intersection(combine(P0, P1), IN)
    O = underfill(I, TWO, P)
    return O

def dsl2(I):
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    Gf = rbind(subgrid, I)
    g2 = rbind(ofcolor, TWO)
    Av = chain(g2, vmirror, Gf)
    Ah = chain(g2, hmirror, Gf)
    Sv = fork(shift, Av, ulcorner)
    Sh = fork(shift, Ah, ulcorner)
    Pe = fork(combine, Sv, Sh)
    P = merge(mapply(Pe, EO))
    O = underfill(I, TWO, P)
    return O

def dsl3(I):
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    Gf = rbind(subgrid, I)
    Ar = chain(rbind(ofcolor, TWO), rot180, Gf)
    Sr = fork(shift, Ar, ulcorner)
    P = merge(mapply(Sr, EO))
    O = underfill(I, TWO, P)
    return O

def dsl4(I):
    S = ofcolor(I, TWO)
    SO = toobject(S, I)
    HP = hperiod(SO)
    VP = vperiod(SO)
    HD = tojvec(HP)
    VD = toivec(VP)
    nHD = invert(HD)
    nVD = invert(VD)
    P0 = combine(shift(S, HD), shift(S, nHD))
    P1 = combine(shift(S, VD), shift(S, nVD))
    P2 = combine(P0, P1)
    P3 = combine(shift(S, add(HD, VD)), shift(S, add(nHD, VD)))
    P4 = combine(shift(S, add(HD, nVD)), shift(S, add(nHD, nVD)))
    P = combine(P2, combine(P3, P4))
    IN = merge(mapply(inbox, colorfilter(objects(I, T, F, T), EIGHT)))
    Q = intersection(P, IN)
    O = underfill(I, TWO, Q)
    return O

def dsl5(I):
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    Gf = rbind(subgrid, I)
    g2 = rbind(ofcolor, TWO)
    Av = chain(g2, vmirror, Gf)
    Ah = chain(g2, hmirror, Gf)
    Ar = chain(g2, rot180, Gf)
    Sv = fork(shift, Av, ulcorner)
    Sh = fork(shift, Ah, ulcorner)
    Sr = fork(shift, Ar, ulcorner)
    U = combine(Sv, combine(Sh, Sr))
    INT = fork(difference, inbox, box)
    Qe = fork(intersection, U, INT)
    P = merge(mapply(Qe, EO))
    O = underfill(I, TWO, P)
    return O
```