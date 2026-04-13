```python
def dsl1(I):
    J = vmirror(I)
    M = ofcolor(J, ONE)
    L = asindices(lefthalf(I))
    Z = difference(L, ofcolor(I, ONE))
    P = intersection(M, Z)
    O = underpaint(I, recolor(TWO, P))
    return O

def dsl2(I):
    M = ofcolor(I, ONE)
    B = backdrop(M)
    E = difference(B, M)
    L = asindices(lefthalf(I))
    P = intersection(E, L)
    O = underpaint(I, recolor(TWO, P))
    return O

def dsl3(I):
    M = ofcolor(I, ONE)
    L1 = shift(M, LEFT)
    L2 = shift(L1, LEFT)
    N = combine(L1, L2)
    Z = difference(N, M)
    O = underpaint(I, recolor(TWO, Z))
    return O

def dsl4(I):
    J = rot180(I)
    M = ofcolor(J, ONE)
    L = asindices(lefthalf(I))
    Z = difference(L, ofcolor(I, ONE))
    P = intersection(M, Z)
    O = underpaint(I, recolor(TWO, P))
    return O

def dsl5(I):
    M = ofcolor(I, ONE)
    O1 = toobject(M, I)
    DX = subtract(TWO, leftmost(M))
    V = tojvec(DX)
    G = move(I, O1, V)
    K = ofcolor(G, ONE)
    Z = difference(K, ofcolor(I, ONE))
    O = underpaint(I, recolor(TWO, Z))
    return O
```