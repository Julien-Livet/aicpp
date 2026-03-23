```python
def dsl1(I):
    lc = leastcolor(I)
    Fs = frontiers(I)
    P = merge(mapply(toindices, Fs))
    O = fill(I, lc, P)
    return O

def dsl2(I):
    lc = leastcolor(I)
    inds = ofcolor(I, lc)
    rows = mapply(hfrontier, inds)
    cols = mapply(vfrontier, inds)
    RP = merge(rows)
    CP = merge(cols)
    P = combine(RP, CP)
    O = fill(I, lc, P)
    return O

def dsl3(I):
    R1 = rot90(I)
    R2 = rot270(I)
    O1 = underpaint(I, asobject(R1))
    O = underpaint(O1, asobject(R2))
    return O

def dsl4(I):
    Os = objects(I, T, F, T)
    S = argmin(Os, size)
    c = color(S)
    Cs = apply(center, Os)
    G = asindices(I)
    Cns = corners(G)
    P1 = prapply(connect, Cs, Cns)
    P = merge(P1)
    O = underfill(I, c, P)
    return O

def dsl5(I):
    Os = objects(I, T, F, T)
    S = argmin(Os, size)
    c = color(S)
    U = argmin(Os, uppermost)
    D = argmax(Os, lowermost)
    L = argmin(Os, leftmost)
    R = argmax(Os, rightmost)
    V = connect(center(U), center(D))
    H = connect(center(L), center(R))
    P = combine(V, H)
    O = underfill(I, c, P)
    return O
```