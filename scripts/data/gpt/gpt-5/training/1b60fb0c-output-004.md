```python
def dsl1(I):
    J = vmirror(I)
    M = ofcolor(J, ONE)
    A = ofcolor(I, ONE)
    L = asindices(lefthalf(I))
    B = box(L)
    LI = difference(L, B)
    D = difference(M, A)
    P = intersection(D, LI)
    O = underpaint(I, recolor(TWO, P))
    return O

def dsl2(I):
    J = rot180(I)
    D = difference(ofcolor(J, ONE), ofcolor(I, ONE))
    L = asindices(lefthalf(I))
    LI = intersection(L, shift(L, RIGHT))
    P = intersection(D, LI)
    O = underpaint(I, recolor(TWO, P))
    return O

def dsl3(I):
    K = rot270(dmirror(rot90(I)))
    D = difference(ofcolor(K, ONE), ofcolor(I, ONE))
    L = asindices(lefthalf(I))
    LI = intersection(L, shift(L, RIGHT))
    P = intersection(D, LI)
    O = underpaint(I, recolor(TWO, P))
    return O

def dsl4(I):
    RH = asindices(righthalf(I))
    M = ofcolor(I, ONE)
    S = intersection(M, RH)
    O1 = toobject(S, I)
    DIR = gravitate(toindices(O1), asindices(lefthalf(I)))
    N = shift(toindices(O1), DIR)
    D = difference(N, M)
    L = asindices(lefthalf(I))
    LI = intersection(L, shift(L, RIGHT))
    P = intersection(D, LI)
    O = underpaint(I, recolor(TWO, P))
    return O

def dsl5(I):
    M = ofcolor(I, ONE)
    O1 = toobject(M, I)
    BX = inbox(O1)
    L = asindices(lefthalf(I))
    LI = intersection(L, shift(L, RIGHT))
    C = intersection(BX, LI)
    P = difference(C, M)
    O = underpaint(I, recolor(TWO, P))
    return O
```