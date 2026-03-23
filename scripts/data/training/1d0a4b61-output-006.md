```python
def dsl1(I):
    # Global: derive lattice from center-of-mass row/column of all nonzero cells, then tile the nonzero object
    U = toobject(difference(asindices(I), ofcolor(I, ZERO)), I)
    V = toindices(U)
    c = center(U)
    row = hfrontier(c)
    col = vfrontier(c)
    rp = intersection(V, row)
    cp = intersection(V, col)
    orow = toobject(rp, I)
    ocol = toobject(cp, I)
    hp = hperiod(orow)
    vp = vperiod(ocol)
    r = tojvec(hp)
    d = toivec(vp)
    K = interval(invert(EIGHT), add(EIGHT, ONE), ONE)
    HV = apply(lbind(multiply, r), K)
    DV = apply(lbind(multiply, d), K)
    OFF = prapply(add, HV, DV)
    S = merge(apply(lbind(shift, U), OFF))
    O = underpaint(I, S)
    return O

def dsl2(I):
    # Object extraction: use least frequent color to infer lattice, then propagate all nonzero colors
    U = toobject(difference(asindices(I), ofcolor(I, ZERO)), I)
    cmin = leastcolor(I)
    seed = toobject(ofcolor(I, cmin), I)
    hp = hperiod(seed)
    vp = vperiod(seed)
    r = tojvec(hp)
    d = toivec(vp)
    K = interval(invert(EIGHT), add(EIGHT, ONE), ONE)
    HV = apply(lbind(multiply, r), K)
    DV = apply(lbind(multiply, d), K)
    OFF = prapply(add, HV, DV)
    S = merge(apply(lbind(shift, U), OFF))
    O = underpaint(I, S)
    return O

def dsl3(I):
    # Color filtering: use union of frontiers to infer global lattice, then tile all nonzero colors
    U = toobject(difference(asindices(I), ofcolor(I, ZERO)), I)
    F = frontiers(I)
    FE = merge(F)
    Fo = toobject(FE, I)
    hp = hperiod(Fo)
    vp = vperiod(Fo)
    r = tojvec(hp)
    d = toivec(vp)
    K = interval(invert(EIGHT), add(EIGHT, ONE), ONE)
    HV = apply(lbind(multiply, r), K)
    DV = apply(lbind(multiply, d), K)
    OFF = prapply(add, HV, DV)
    S = merge(apply(lbind(shift, U), OFF))
    O = underpaint(I, S)
    return O

def dsl4(I):
    # Geometric: shoot rays from the upper-left of the nonzero object to get periods, then tile
    U = toobject(difference(asindices(I), ofcolor(I, ZERO)), I)
    V = toindices(U)
    a = ulcorner(U)
    row = shoot(a, RIGHT)
    col = shoot(a, DOWN)
    rp = intersection(V, row)
    cp = intersection(V, col)
    orow = toobject(rp, I)
    ocol = toobject(cp, I)
    hp = hperiod(orow)
    vp = vperiod(ocol)
    r = tojvec(hp)
    d = toivec(vp)
    K = interval(invert(EIGHT), add(EIGHT, ONE), ONE)
    HV = apply(lbind(multiply, r), K)
    DV = apply(lbind(multiply, d), K)
    OFF = prapply(add, HV, DV)
    S = merge(apply(lbind(shift, U), OFF))
    O = underpaint(I, S)
    return O

def dsl5(I):
    # Relational: infer horizontal/vertical offsets from thirds splits, then propagate globally
    A, B, C = vsplit(I, THREE)
    oA = toobject(difference(asindices(A), ofcolor(A, ZERO)), A)
    oB = toobject(difference(asindices(B), ofcolor(B, ZERO)), B)
    U0 = toobject(difference(asindices(I), ofcolor(I, ZERO)), I)
    offH = position(oA, oB)
    K = interval(invert(EIGHT), add(EIGHT, ONE), ONE)
    HV = apply(lbind(multiply, offH), K)
    SH = merge(apply(lbind(shift, U0), HV))
    O1 = underpaint(I, SH)
    X, Y, Z = hsplit(O1, THREE)
    oX = toobject(difference(asindices(X), ofcolor(X, ZERO)), X)
    oY = toobject(difference(asindices(Y), ofcolor(Y, ZERO)), Y)
    offV = position(oX, oY)
    DV = apply(lbind(multiply, offV), K)
    SV = merge(apply(lbind(shift, toobject(difference(asindices(O1), ofcolor(O1, ZERO)), O1)), DV))
    O = underpaint(O1, SV)
    return O
```