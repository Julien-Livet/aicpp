```python
def dsl1(I):
    J = vmirror(I)
    M = ofcolor(J, ONE)
    L = asindices(lefthalf(I))
    LI = intersection(L, shift(L, RIGHT))
    P = intersection(M, LI)
    O = underpaint(I, recolor(TWO, P))
    return O

def dsl2(I):
    M = ofcolor(I, ONE)
    RH = asindices(righthalf(I))
    S = intersection(M, RH)
    O1 = toobject(S, I)
    R = vmirror(O1)
    L = asindices(lefthalf(I))
    LI = intersection(L, shift(L, RIGHT))
    P = intersection(toindices(R), LI)
    O = underpaint(I, recolor(TWO, P))
    return O

def dsl3(I):
    J = vmirror(I)
    A = ofcolor(J, ONE)
    B = ofcolor(I, ONE)
    D = difference(A, B)
    L = asindices(lefthalf(I))
    LI = intersection(L, shift(L, RIGHT))
    P = intersection(D, LI)
    O = underpaint(I, recolor(TWO, P))
    return O

def dsl4(I):
    J = rot180(I)
    M = ofcolor(J, ONE)
    L = asindices(lefthalf(I))
    LI = intersection(L, shift(L, RIGHT))
    P = intersection(M, LI)
    O = underpaint(I, recolor(TWO, P))
    return O

def dsl5(I):
    M = ofcolor(I, ONE)
    S1 = shift(M, LEFT)
    S2 = shift(S1, LEFT)
    C = difference(combine(S1, S2), M)
    L = asindices(lefthalf(I))
    LI = intersection(L, shift(L, RIGHT))
    P = intersection(C, LI)
    O = underpaint(I, recolor(TWO, P))
    return O
```