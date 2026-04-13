```python
def dsl1(I):
    # Global: compress to minimal motif, then upscale to full size
    C = compress(I)
    fw = divide(width(I), width(C))
    fh = divide(height(I), height(C))
    H = hupscale(C, fw)
    O = vupscale(H, fh)
    return O

def dsl2(I):
    # Object extraction: infer periods directly from union of nonzeros, then tile
    U = toobject(difference(asindices(I), ofcolor(I, ZERO)), I)
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

def dsl3(I):
    # Color filtering: collapse all nonzeros to one color to get lattice, then tile original colors
    U = toobject(difference(asindices(I), ofcolor(I, ZERO)), I)
    RU = recolor(ONE, toindices(U))
    hp = hperiod(RU)
    vp = vperiod(RU)
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
    # Geometric: anchor at upper-left corner cross to read periods, then tile
    U = toobject(difference(asindices(I), ofcolor(I, ZERO)), I)
    V = toindices(U)
    ul = ulcorner(U)
    row = hfrontier(ul)
    col = vfrontier(ul)
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
    # Relational: infer offsets from halves alignment horizontally and vertically, then propagate
    L = lefthalf(I)
    R = righthalf(I)
    oL = toobject(difference(asindices(L), ofcolor(L, ZERO)), L)
    oR = toobject(difference(asindices(R), ofcolor(R, ZERO)), R)
    offH = position(oL, oR)
    K = interval(invert(EIGHT), add(EIGHT, ONE), ONE)
    HV = apply(lbind(multiply, offH), K)
    U0 = toobject(difference(asindices(I), ofcolor(I, ZERO)), I)
    SH = merge(apply(lbind(shift, U0), HV))
    O1 = underpaint(I, SH)
    T = tophalf(O1)
    B = bottomhalf(O1)
    oT = toobject(difference(asindices(T), ofcolor(T, ZERO)), T)
    oB = toobject(difference(asindices(B), ofcolor(B, ZERO)), B)
    offV = position(oT, oB)
    DV = apply(lbind(multiply, offV), K)
    U1 = toobject(difference(asindices(O1), ofcolor(O1, ZERO)), O1)
    SV = merge(apply(lbind(shift, U1), DV))
    O = underpaint(O1, SV)
    return O
```