```python
def dsl1(I):
    J = vmirror(I)
    M = ofcolor(J, ONE)
    S = shift(M, RIGHT)
    B = backdrop(ofcolor(I, ONE))
    P = intersection(S, B)
    O = underpaint(I, recolor(TWO, P))
    return O

def dsl2(I):
    J = rot90(I)
    M = ofcolor(J, ONE)
    S = shift(M, RIGHT)
    G = fill(J, TWO, S)
    R = rot270(G)
    K = ofcolor(R, TWO)
    O = underpaint(I, recolor(TWO, K))
    return O

def dsl3(I):
    M = ofcolor(I, ONE)
    P = shift(M, LEFT)
    O = underpaint(I, recolor(TWO, P))
    return O

def dsl4(I):
    M = ofcolor(I, ONE)
    L = shift(M, LEFT)
    R = shift(M, RIGHT)
    N = combine(L, R)
    Z = difference(asindices(I), M)
    P = intersection(N, Z)
    O = underpaint(I, recolor(TWO, P))
    return O

def dsl5(I):
    M = ofcolor(I, ONE)
    B = backdrop(M)
    E = difference(B, M)
    O = underpaint(I, recolor(TWO, E))
    return O
```