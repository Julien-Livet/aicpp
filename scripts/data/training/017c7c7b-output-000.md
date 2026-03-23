```python
def dsl1(I):
    A = replace(I, ONE, TWO)
    T = first(hsplit(A, 2))
    O = vconcat(A, T)
    return O

def dsl2(I):
    H = height(I)
    W = width(I)
    D = astuple(add(H, THREE), W)
    C = canvas(ZERO, D)
    X1 = ofcolor(I, ONE)
    O1 = paint(C, recolor(TWO, X1))
    T = first(hsplit(I, 2))
    Xtop = ofcolor(T, ONE)
    Sh = toivec(H)
    O = paint(O1, recolor(TWO, shift(Xtop, Sh)))
    return O

def dsl3(I):
    A = replace(I, ONE, TWO)
    H2 = halve(height(I))
    B = crop(A, ORIGIN, astuple(H2, width(I)))
    O = vconcat(A, B)
    return O

def dsl4(I):
    A = replace(I, ONE, TWO)
    B = replace(tophalf(I), ONE, TWO)
    O = vconcat(A, B)
    return O

def dsl5(I):
    A = replace(I, ONE, TWO)
    P = crop(A, ORIGIN, astuple(THREE, width(I)))
    Pobj = asobject(P)
    Qobj = shift(Pobj, toivec(height(I)))
    D = astuple(add(height(I), THREE), width(I))
    C = canvas(ZERO, D)
    O = underpaint(underpaint(C, asobject(A)), Qobj)
    return O
```