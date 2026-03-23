```python
def dsl1(I):
    # Global: infer lattice from union of frontiers, then tile nonzero content
    U = toobject(difference(asindices(I), ofcolor(I, ZERO)), I)
    Fo = toobject(merge(frontiers(I)), I)
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

def dsl2(I):
    # Object extraction: use most frequent color object to infer periods, then propagate all nonzeros
    U = toobject(difference(asindices(I), ofcolor(I, ZERO)), I)
    mc = mostcolor(I)
    seed = toobject(ofcolor(I, mc), I)
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
    # Color filtering: use zero-color distribution to infer lattice, then tile nonzeros
    U = toobject(difference(asindices(I), ofcolor(I, ZERO)), I)
    Z = toobject(ofcolor(I, ZERO), I)
    hp = hperiod(Z)
    vp = vperiod(Z)
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
    # Geometric: use center-of-mass cross (row/col) to get periods, then tile
    U = toobject(difference(asindices(I), ofcolor(I, ZERO)), I)
    V = toindices(U)
    c = centerofmass(U)
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
    U1 = toobject(difference(asindices(O1), ofcolor(O1, ZERO)), O1)
    SV = merge(apply(lbind(shift, U1), DV))
    O = underpaint(O1, SV)
    return O
```