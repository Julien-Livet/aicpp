```python
def dsl1(I):
    # Global symmetry completion inside 8-bordered interiors
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    IN = merge(mapply(inbox, EO))
    BO = merge(mapply(box, EO))
    INT = difference(IN, BO)
    P0 = ofcolor(I, TWO)
    P1 = ofcolor(vmirror(I), TWO)
    P2 = ofcolor(hmirror(I), TWO)
    P3 = ofcolor(rot180(I), TWO)
    P = intersection(INT, combine(combine(P0, P1), combine(P2, P3)))
    O = underfill(I, TWO, P)
    return O

def dsl2(I):
    # Per-object subgrid mirrors (vertical, horizontal, and 180°)
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    IN = merge(mapply(inbox, EO))
    BO = merge(mapply(box, EO))
    INT = difference(IN, BO)
    Gf = rbind(subgrid, I)
    g2 = rbind(ofcolor, TWO)
    Av = chain(g2, vmirror, Gf)
    Ah = chain(g2, hmirror, Gf)
    Ar = chain(g2, rot180, Gf)
    Sv = fork(shift, Av, ulcorner)
    Sh = fork(shift, Ah, ulcorner)
    Sr = fork(shift, Ar, ulcorner)
    Pv = merge(mapply(Sv, EO))
    Ph = merge(mapply(Sh, EO))
    Pr = merge(mapply(Sr, EO))
    P = intersection(INT, combine(Pv, combine(Ph, Pr)))
    O = underfill(I, TWO, P)
    return O

def dsl3(I):
    # Color-filtered rotational completion within each 8-subgrid (paint)
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    IN = merge(mapply(inbox, EO))
    BO = merge(mapply(box, EO))
    INT = difference(IN, BO)
    Gf = rbind(subgrid, I)
    Ar = chain(rbind(ofcolor, TWO), rot180, Gf)
    Sr = fork(shift, Ar, ulcorner)
    P = merge(mapply(Sr, EO))
    Q = intersection(P, INT)
    O = underpaint(I, recolor(TWO, Q))
    return O

def dsl4(I):
    # Periodic propagation by inferred horizontal/vertical periods (global)
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    IN = merge(mapply(inbox, EO))
    BO = merge(mapply(box, EO))
    INT = difference(IN, BO)
    S = intersection(ofcolor(I, TWO), INT)
    SO = toobject(S, I)
    HP = hperiod(SO)
    VP = vperiod(SO)
    HD = tojvec(HP)
    VD = toivec(VP)
    nHD = invert(HD)
    nVD = invert(VD)
    P0 = combine(shift(S, HD), shift(S, nHD))
    P1 = combine(shift(S, VD), shift(S, nVD))
    P2 = combine(shift(S, add(HD, VD)), shift(S, add(nHD, VD)))
    P3 = combine(shift(S, add(HD, nVD)), shift(S, add(nHD, nVD)))
    P = intersection(INT, combine(combine(P0, P1), combine(P2, P3)))
    O = underfill(I, TWO, P)
    return O

def dsl5(I):
    # Geometric diagonal symmetries plus 180° within each enclosure
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    IN = merge(mapply(inbox, EO))
    BO = merge(mapply(box, EO))
    INT = difference(IN, BO)
    Gf = rbind(subgrid, I)
    g2 = rbind(ofcolor, TWO)
    Ad = chain(g2, dmirror, Gf)
    Ac = chain(g2, cmirror, Gf)
    Ar = chain(g2, rot180, Gf)
    Sd = fork(shift, Ad, ulcorner)
    Sc = fork(shift, Ac, ulcorner)
    Sr = fork(shift, Ar, ulcorner)
    Pd = merge(mapply(Sd, EO))
    Pc = merge(mapply(Sc, EO))
    Pr = merge(mapply(Sr, EO))
    P = intersection(INT, combine(Pr, combine(Pd, Pc)))
    O = underfill(I, TWO, P)
    return O
```