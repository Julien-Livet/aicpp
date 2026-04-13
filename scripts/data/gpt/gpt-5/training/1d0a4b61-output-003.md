```python
def dsl1(I):
    # Global periodic completion via 2-pass lattice propagation using wide offset intervals
    idx = asindices(I)
    nz = difference(idx, ofcolor(I, ZERO))
    obj = toobject(nz, I)
    hp = hperiod(obj)
    vp = vperiod(obj)
    r = tojvec(hp)
    d = toivec(vp)
    K = interval(invert(EIGHT), add(EIGHT, ONE), ONE)
    HV = apply(lbind(multiply, r), K)
    SH = merge(apply(lbind(shift, obj), HV))
    O1 = underpaint(I, SH)
    idx1 = asindices(O1)
    nz1 = difference(idx1, ofcolor(O1, ZERO))
    obj1 = toobject(nz1, O1)
    DV = apply(lbind(multiply, d), K)
    SV = merge(apply(lbind(shift, obj1), DV))
    O2 = underpaint(O1, SV)
    return O2

def dsl2(I):
    # Object-based full 2D lattice tiling: propagate the unified nonzero object over cartesian offsets
    idx = asindices(I)
    nz = difference(idx, ofcolor(I, ZERO))
    obj = toobject(nz, I)
    hp = hperiod(obj)
    vp = vperiod(obj)
    r = tojvec(hp)
    d = toivec(vp)
    K = interval(invert(EIGHT), add(EIGHT, ONE), ONE)
    HV = apply(lbind(multiply, r), K)
    DV = apply(lbind(multiply, d), K)
    OFF = prapply(add, HV, DV)
    S = merge(apply(lbind(shift, obj), OFF))
    O = underpaint(I, S)
    return O

def dsl3(I):
    # Color-filtered periodic fill: propagate vivid colors {2,3,4,5} over full 2D lattice
    parts = objects(I, T, F, T)
    c2 = merge(colorfilter(parts, TWO))
    c3 = merge(colorfilter(parts, THREE))
    c4 = merge(colorfilter(parts, FOUR))
    c5 = merge(colorfilter(parts, FIVE))
    C = combine(c2, combine(c3, combine(c4, c5)))
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
    # Geometric symmetry closure combined with period-guided lattice propagation
    H = hmirror(I)
    V = vmirror(I)
    R = rot180(I)
    idxI = asindices(I)
    idxH = asindices(H)
    idxV = asindices(V)
    idxR = asindices(R)
    oI = toobject(difference(idxI, ofcolor(I, ZERO)), I)
    oH = toobject(difference(idxH, ofcolor(H, ZERO)), H)
    oV = toobject(difference(idxV, ofcolor(V, ZERO)), V)
    oR = toobject(difference(idxR, ofcolor(R, ZERO)), R)
    U = combine(combine(oI, oH), combine(oV, oR))
    hp = hperiod(U)
    vp = vperiod(U)
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
    # Relational cross-part propagation: exchange and spread patterns from left/right halves along periods
    L, R = vsplit(I, 2)
    oL = toobject(difference(asindices(L), ofcolor(L, ZERO)), L)
    oR = toobject(difference(asindices(R), ofcolor(R, ZERO)), R)
    U = combine(oL, oR)
    hp = hperiod(U)
    vp = vperiod(U)
    r = tojvec(hp)
    d = toivec(vp)
    K = interval(invert(EIGHT), add(EIGHT, ONE), ONE)
    HV = apply(lbind(multiply, r), K)
    DV = apply(lbind(multiply, d), K)
    OFF = prapply(add, HV, DV)
    S = merge(apply(lbind(shift, U), OFF))
    O = underpaint(I, S)
    return O
```