```python
def dsl1(I):
    # Global anchored-period lattice fill: infer periods from a single nonzero row/column and propagate the full nonzero object
    idx = asindices(I)
    nz = difference(idx, ofcolor(I, ZERO))
    o = toobject(nz, I)
    a = first(nz)
    row = hfrontier(a)
    col = vfrontier(a)
    rp = intersection(nz, row)
    cp = intersection(nz, col)
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
    S = merge(apply(lbind(shift, o), OFF))
    O = underpaint(I, S)
    return O

def dsl2(I):
    # Object extraction with global compression guidance: estimate periods on compressed grid then tile the original object
    J = compress(I)
    o = toobject(difference(asindices(I), ofcolor(I, ZERO)), I)
    oj = asobject(J)
    hp = hperiod(oj)
    vp = vperiod(oj)
    r = tojvec(hp)
    d = toivec(vp)
    K = interval(invert(EIGHT), add(EIGHT, ONE), ONE)
    HV = apply(lbind(multiply, r), K)
    DV = apply(lbind(multiply, d), K)
    OFF = prapply(add, HV, DV)
    S = merge(apply(lbind(shift, o), OFF))
    O = underpaint(I, S)
    return O

def dsl3(I):
    # Color-filtered lattice fill via palette: propagate only non-background, non-zero colors
    P = palette(I)
    B = mostcolor(I)
    P1 = remove(ZERO, P)
    P2 = remove(B, P1)
    patches = apply(lbind(ofcolor, I), P2)
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
    # Geometric symmetry closure: union of all four rotations and both mirrors to fill gaps
    H = hmirror(I)
    V = vmirror(I)
    R90 = rot90(I)
    R180 = rot180(I)
    R270 = rot270(I)
    def nzobj(G):
        return toobject(difference(asindices(G), ofcolor(G, ZERO)), G)
    U = combine(combine(nzobj(I), nzobj(H)), combine(nzobj(V), combine(nzobj(R90), combine(nzobj(R180), nzobj(R270)))))
    O = underpaint(I, U)
    return O

def dsl5(I):
    # Relational propagation via inter-part offsets: use positions of halves to derive horizontal and vertical lattice vectors
    L, R = vsplit(I, 2)
    oL = toobject(difference(asindices(L), ofcolor(L, ZERO)), L)
    oR = toobject(difference(asindices(R), ofcolor(R, ZERO)), R)
    U = combine(oL, oR)
    offH = position(oL, oR)
    K = interval(invert(EIGHT), add(EIGHT, ONE), ONE)
    HV = apply(lbind(multiply, offH), K)
    SH = merge(apply(lbind(shift, U), HV))
    O1 = underpaint(I, SH)
    T, B = hsplit(O1, 2)
    oT = toobject(difference(asindices(T), ofcolor(T, ZERO)), T)
    oB = toobject(difference(asindices(B), ofcolor(B, ZERO)), B)
    offV = position(oT, oB)
    DV = apply(lbind(multiply, offV), K)
    oAll = toobject(difference(asindices(O1), ofcolor(O1, ZERO)), O1)
    SV = merge(apply(lbind(shift, oAll), DV))
    O2 = underpaint(O1, SV)
    return O2
```