```python
def dsl1(I):
    # Global lattice from full-grid periodicity: use total grid object to infer periods and tile it over zeros
    A = asobject(I)
    hp = hperiod(A)
    vp = vperiod(A)
    r = tojvec(hp)
    d = toivec(vp)
    K = interval(invert(EIGHT), add(EIGHT, ONE), ONE)
    HV = apply(lbind(multiply, r), K)
    DV = apply(lbind(multiply, d), K)
    OFF = prapply(add, HV, DV)
    S = merge(apply(lbind(shift, A), OFF))
    O = underpaint(I, S)
    return O

def dsl2(I):
    # Object extraction anchored by the largest foreground component to set the lattice, then tile all foreground
    P = objects(I, T, F, T)
    U = merge(P)
    A = argmax(P, size)
    hp = hperiod(A)
    vp = vperiod(A)
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
    # Color filtering: remove background color(s), infer lattice on remaining colors, and propagate them
    P = palette(I)
    BG = mostcolor(I)
    P1 = remove(ZERO, P)
    PF = remove(BG, P1)
    patches = apply(lbind(ofcolor, I), PF)
    V = merge(patches)
    C = toobject(V, I)
    hp = hperiod(C)
    vp = vperiod(C)
    r = tojvec(hp)
    d = toivec(vp)
    K = interval(invert(EIGHT), add(EIGHT, ONE), ONE)
    HV = apply(lbind(multiply, r), K)
    DV = apply(lbind(multiply, d), K)
    OFF = prapply(add, HV, DV)
    S = merge(apply(lbind(shift, C), OFF))
    O = underpaint(I, S)
    return O

def dsl4(I):
    # Geometric anchoring via frontiers at the upper-left: infer horizontal/vertical periods from first row/column intersections
    U = toobject(difference(asindices(I), ofcolor(I, ZERO)), I)
    V = toindices(U)
    a = ulcorner(U)
    row = hfrontier(a)
    col = vfrontier(a)
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
    # Relational propagation: derive lattice vectors from relative positions of halves, then propagate globally
    L, R = vsplit(I, 2)
    oL = toobject(difference(asindices(L), ofcolor(L, ZERO)), L)
    oR = toobject(difference(asindices(R), ofcolor(R, ZERO)), R)
    U0 = toobject(difference(asindices(I), ofcolor(I, ZERO)), I)
    offH = position(oL, oR)
    K = interval(invert(EIGHT), add(EIGHT, ONE), ONE)
    HV = apply(lbind(multiply, offH), K)
    SH = merge(apply(lbind(shift, U0), HV))
    O1 = underpaint(I, SH)
    T, B = hsplit(O1, 2)
    oT = toobject(difference(asindices(T), ofcolor(T, ZERO)), T)
    oB = toobject(difference(asindices(B), ofcolor(B, ZERO)), B)
    offV = position(oT, oB)
    DV = apply(lbind(multiply, offV), K)
    SV = merge(apply(lbind(shift, toobject(difference(asindices(O1), ofcolor(O1, ZERO)), O1)), DV))
    O2 = underpaint(O1, SV)
    return O2
```