```python
def dsl1(I):
    K = rot90(cmirror(I))
    D = difference(ofcolor(K, ONE), ofcolor(I, ONE))
    L = asindices(lefthalf(I))
    LI = intersection(L, shift(L, RIGHT))
    P = intersection(D, LI)
    O = underpaint(I, recolor(TWO, P))
    return O

def dsl2(I):
    M = ofcolor(I, ONE)
    O1 = toobject(M, I)
    C = center(toindices(O1))
    H = hfrontier(C)
    V = vfrontier(C)
    AX = combine(H, V)
    B = backdrop(toindices(O1))
    L = asindices(lefthalf(I))
    LI = intersection(L, shift(L, RIGHT))
    S = intersection(B, AX)
    P = difference(intersection(S, LI), M)
    O = underpaint(I, recolor(TWO, P))
    return O

def dsl3(I):
    M = ofcolor(I, ONE)
    O1 = toobject(M, I)
    GAP = delta(toindices(O1))
    L = asindices(lefthalf(I))
    LI = intersection(L, shift(L, RIGHT))
    P = intersection(GAP, LI)
    O = underpaint(I, recolor(TWO, P))
    return O

def dsl4(I):
    L = asindices(lefthalf(I))
    RH = asindices(righthalf(I))
    M = ofcolor(I, ONE)
    S = intersection(M, RH)
    DIR = gravitate(S, L)
    N = shift(S, DIR)
    D = difference(N, M)
    LI = intersection(L, shift(L, RIGHT))
    P = intersection(D, LI)
    O = underpaint(I, recolor(TWO, P))
    return O

def dsl5(I):
    M = ofcolor(I, ONE)
    S1 = shift(M, LEFT)
    S2 = shift(M, double(LEFT))
    U = combine(S1, S2)
    L = asindices(lefthalf(I))
    LI = intersection(L, shift(L, RIGHT))
    P = difference(intersection(U, LI), M)
    O = underpaint(I, recolor(TWO, P))
    return O
```