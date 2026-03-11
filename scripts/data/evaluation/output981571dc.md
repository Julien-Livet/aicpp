```python
def dsl1(I):
    O = I
    H = hmirror(I)
    O = underpaint(O, asobject(H))
    V = vmirror(I)
    O = underpaint(O, asobject(V))
    R90 = rot90(I)
    O = underpaint(O, asobject(R90))
    R180 = rot180(I)
    O = underpaint(O, asobject(R180))
    R270 = rot270(I)
    O = underpaint(O, asobject(R270))
    D = dmirror(I)
    O = underpaint(O, asobject(D))
    C = cmirror(I)
    O = underpaint(O, asobject(C))
    return O

def dsl2(I):
    L = lefthalf(I)
    R = hmirror(L)
    O = hconcat(L, R)
    return O

def dsl3(I):
    R = righthalf(I)
    L = hmirror(R)
    O = hconcat(L, R)
    return O

def dsl4(I):
    A, B, C = vsplit(I, 3)
    AB = hconcat(A, A)
    O = hconcat(AB, C)
    return O

def dsl5(I):
    X, Y, Z = hsplit(I, 3)
    XX = vconcat(X, X)
    O = vconcat(XX, Z)
    return O
```