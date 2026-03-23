```python
def dsl1(I):
    A = replace(I, ONE, TWO)
    H = height(I)
    W = width(I)
    Top = crop(A, ORIGIN, astuple(THREE, W))
    S1 = toivec(decrement(halve(H)))
    S2 = toivec(halve(H))
    Mid1 = crop(A, S1, astuple(THREE, W))
    Mid2 = crop(A, S2, astuple(THREE, W))
    Xtop = ofcolor(Top, TWO)
    X1 = ofcolor(Mid1, TWO)
    X2 = ofcolor(Mid2, TWO)
    I1 = size(intersection(X1, Xtop))
    I2 = size(intersection(X2, Xtop))
    B = branch(greater(I1, I2), Mid1, Mid2)
    O = vconcat(A, B)
    return O

def dsl2(I):
    A = switch(I, ONE, TWO)
    H = height(I)
    W = width(I)
    S = toivec(decrement(halve(H)))
    Mid = crop(A, S, astuple(THREE, W))
    C = canvas(ZERO, astuple(add(H, THREE), W))
    O1 = paint(C, asobject(A))
    O = paint(O1, shift(asobject(Mid), toivec(H)))
    return O

def dsl3(I):
    A = replace(I, ONE, TWO)
    Top = tophalf(A)
    Bot = bottomhalf(A)
    Ct = colorcount(Top, TWO)
    Cb = colorcount(Bot, TWO)
    B = branch(greater(Cb, Ct), Bot, Top)
    O = vconcat(A, B)
    return O

def dsl4(I):
    A = replace(I, ONE, TWO)
    M = hmirror(A)
    B = crop(M, ORIGIN, astuple(THREE, width(I)))
    O = vconcat(A, B)
    return O

def dsl5(I):
    A = replace(I, ONE, TWO)
    X = ofcolor(I, ONE)
    U = uppermost(X)
    S = toivec(increment(increment(U)))
    B = crop(A, S, astuple(THREE, width(I)))
    O = vconcat(A, B)
    return O
```