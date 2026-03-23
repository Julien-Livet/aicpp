```python
def dsl1(I):
    K = vmirror(I)
    Mk = ofcolor(K, ONE)
    M = ofcolor(I, ONE)
    L = asindices(lefthalf(I))
    LI = intersection(L, shift(L, RIGHT))
    P = difference(intersection(Mk, LI), M)
    O = underpaint(I, recolor(TWO, P))
    return O

def dsl2(I):
    M = ofcolor(I, ONE)
    O1 = toobject(M, I)
    C = center(toindices(O1))
    V = vfrontier(C)
    V1 = combine(V, shift(V, LEFT))
    V2 = combine(V1, shift(V, double(LEFT)))
    B = backdrop(toindices(O1))
    L = asindices(lefthalf(I))
    LI = intersection(L, shift(L, RIGHT))
    P = difference(intersection(V2, intersection(B, LI)), M)
    O = underpaint(I, recolor(TWO, P))
    return O

def dsl3(I):
    M = ofcolor(I, ONE)
    S1 = shift(M, LEFT)
    S2 = shift(M, double(LEFT))
    L = asindices(lefthalf(I))
    LI = intersection(L, shift(L, RIGHT))
    P = intersection(intersection(S1, S2), LI)
    O = underpaint(I, recolor(TWO, difference(P, M)))
    return O

def dsl4(I):
    J = rot90(I)
    K = rot270(cmirror(J))
    Mk = ofcolor(K, ONE)
    M = ofcolor(I, ONE)
    L = asindices(lefthalf(I))
    LI = intersection(L, shift(L, RIGHT))
    P = difference(intersection(Mk, LI), M)
    O = underpaint(I, recolor(TWO, P))
    return O

def dsl5(I):
    M = ofcolor(I, ONE)
    O1 = toobject(M, I)
    GAP = delta(toindices(O1))
    Adj = shift(M, LEFT)
    L = asindices(lefthalf(I))
    LI = intersection(L, shift(L, RIGHT))
    P = intersection(GAP, intersection(Adj, LI))
    O = underpaint(I, recolor(TWO, P))
    return O
```