```python
def dsl1(I):
    # Global: neutralize holes to background, compress motif, then upscale back
    BG = mostcolor(I)
    J = replace(I, ZERO, BG)
    C = compress(J)
    fw = divide(width(I), width(C))
    fh = divide(height(I), height(C))
    O = vupscale(hupscale(C, fw), fh)
    return O

def dsl2(I):
    # Object extraction: union of pattern cells (exclude ZERO and background), infer periods, tile
    BG = mostcolor(I)
    NZ = difference(asindices(I), combine(ofcolor(I, ZERO), ofcolor(I, BG)))
    U = toobject(NZ, I)
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
    # Color filtering: tile every non-(ZERO,BG) object across the inferred lattice and underpaint
    BG = mostcolor(I)
    OB = objects(I, T, F, F)
    ZB = colorfilter(OB, ZERO)
    BB = colorfilter(OB, BG)
    POB = difference(difference(OB, ZB), BB)
    INDS = merge(apply(toindices, POB))
    RU = recolor(ONE, INDS)
    hp = hperiod(RU)
    vp = vperiod(RU)
    r = tojvec(hp)
    d = toivec(vp)
    K = interval(invert(EIGHT), add(EIGHT, ONE), ONE)
    HV = apply(lbind(multiply, r), K)
    DV = apply(lbind(multiply, d), K)
    OFF = prapply(add, HV, DV)
    TILED = merge(prapply(shift, POB, OFF))
    O = underpaint(I, TILED)
    return O

def dsl4(I):
    # Geometric: anchor at UL corner on pattern-only mask to read row/col periods, then tile
    BG = mostcolor(I)
    NZ = difference(asindices(I), combine(ofcolor(I, ZERO), ofcolor(I, BG)))
    U = toobject(NZ, I)
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
    # Relational: infer horizontal and vertical offsets from halves alignment on pattern-only content
    BG = mostcolor(I)
    # horizontal relation from halves
    L = lefthalf(I)
    R = righthalf(I)
    NZL = difference(asindices(L), combine(ofcolor(L, ZERO), ofcolor(L, mostcolor(L))))
    NZR = difference(asindices(R), combine(ofcolor(R, ZERO), ofcolor(R, mostcolor(R))))
    oL = toobject(NZL, L)
    oR = toobject(NZR, R)
    offH = position(oL, oR)
    K = interval(invert(EIGHT), add(EIGHT, ONE), ONE)
    HV = apply(lbind(multiply, offH), K)
    # base pattern object on full grid
    NZ0 = difference(asindices(I), combine(ofcolor(I, ZERO), ofcolor(I, BG)))
    U0 = toobject(NZ0, I)
    SH = merge(apply(lbind(shift, U0), HV))
    O1 = underpaint(I, SH)
    # vertical relation from top/bottom halves after horizontal propagation
    T = tophalf(O1)
    B = bottomhalf(O1)
    NZT = difference(asindices(T), combine(ofcolor(T, ZERO), ofcolor(T, mostcolor(T))))
    NZB = difference(asindices(B), combine(ofcolor(B, ZERO), ofcolor(B, mostcolor(B))))
    oT = toobject(NZT, T)
    oB = toobject(NZB, B)
    offV = position(oT, oB)
    DV = apply(lbind(multiply, offV), K)
    NZ1 = difference(asindices(O1), combine(ofcolor(O1, ZERO), ofcolor(O1, mostcolor(O1))))
    U1 = toobject(NZ1, O1)
    SV = merge(apply(lbind(shift, U1), DV))
    O = underpaint(O1, SV)
    return O
```