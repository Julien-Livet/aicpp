```python
def dsl1(I):
    # Global diagonal symmetries (dmirror, cmirror, rot180) restricted to 8-bordered interiors
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    IN = merge(mapply(inbox, EO))
    BO = merge(mapply(box, EO))
    INT = difference(IN, BO)
    Pd = ofcolor(dmirror(I), TWO)
    Pc = ofcolor(cmirror(I), TWO)
    Pr = ofcolor(rot180(I), TWO)
    P = intersection(INT, combine(Pr, combine(Pd, Pc)))
    O = underfill(I, TWO, P)
    return O

def dsl2(I):
    # Per-2-object local 180° rotation within each object's own bounding box
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    IN = merge(mapply(inbox, EO))
    BO = merge(mapply(box, EO))
    INT = difference(IN, BO)
    O2 = colorfilter(objects(I, T, F, T), TWO)
    Gf = rbind(subgrid, I)
    Ar = chain(rbind(ofcolor, TWO), rot180, Gf)
    Sr = fork(shift, Ar, ulcorner)
    Pr = merge(mapply(Sr, O2))
    P = intersection(INT, Pr)
    O = underfill(I, TWO, P)
    return O

def dsl3(I):
    # Local midpoint bridging: fill cells centered between symmetric 2s (axis and diagonals) inside interiors
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    IN = merge(mapply(inbox, EO))
    BO = merge(mapply(box, EO))
    INT = difference(IN, BO)
    S = intersection(ofcolor(I, TWO), INT)
    L = shift(S, LEFT)
    R = shift(S, RIGHT)
    U = shift(S, UP)
    D = shift(S, DOWN)
    Hmid = intersection(L, R)
    Vmid = intersection(U, D)
    ULdir = add(UP, LEFT)
    URdir = add(UP, RIGHT)
    DLdir = add(DOWN, LEFT)
    DRdir = add(DOWN, RIGHT)
    ULs = shift(S, ULdir)
    URs = shift(S, URdir)
    DLs = shift(S, DLdir)
    DRs = shift(S, DRdir)
    D1 = intersection(ULs, DRs)
    D2 = intersection(URs, DLs)
    P = intersection(INT, combine(combine(Hmid, Vmid), combine(D1, D2)))
    O = underfill(I, TWO, P)
    return O

def dsl4(I):
    # Fixed 2-step lattice propagation (eight directions) within each 8-enclosure
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    IN = merge(mapply(inbox, EO))
    BO = merge(mapply(box, EO))
    INT = difference(IN, BO)
    S = intersection(ofcolor(I, TWO), INT)
    dU = double(UP)
    dD = double(DOWN)
    dL = double(LEFT)
    dR = double(RIGHT)
    P0 = combine(shift(S, dU), shift(S, dD))
    P1 = combine(shift(S, dL), shift(S, dR))
    P2 = combine(shift(S, add(dU, dL)), shift(S, add(dU, dR)))
    P3 = combine(shift(S, add(dD, dL)), shift(S, add(dD, dR)))
    P = intersection(INT, combine(combine(S, P0), combine(P1, combine(P2, P3))))
    O = underfill(I, TWO, P)
    return O

def dsl5(I):
    # Color-adjacency expansion: one-step orthogonal dilation of 2s inside 8-bordered interiors
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    IN = merge(mapply(inbox, EO))
    BO = merge(mapply(box, EO))
    INT = difference(IN, BO)
    S = intersection(ofcolor(I, TWO), INT)
    N = combine(combine(shift(S, UP), shift(S, DOWN)), combine(shift(S, LEFT), shift(S, RIGHT)))
    P = intersection(INT, difference(N, S))
    O = underfill(I, TWO, P)
    return O
```