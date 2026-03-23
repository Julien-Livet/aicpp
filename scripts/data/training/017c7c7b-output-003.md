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
    I1 = size(intersection(ofcolor(Mid1, TWO), Xtop))
    I2 = size(intersection(ofcolor(Mid2, TWO), Xtop))
    B = branch(greater(I2, I1), Mid2, Mid1)
    O = vconcat(A, B)
    return O

def dsl2(I):
    A = switch(I, ONE, TWO)
    H = height(I)
    W = width(I)
    Top = crop(A, ORIGIN, astuple(THREE, W))
    Mid2 = crop(A, toivec(halve(H)), astuple(THREE, W))
    Mid1 = crop(A, toivec(decrement(halve(H))), astuple(THREE, W))
    B = branch(equality(Top, Mid2), Mid2, Mid1)
    C = canvas(ZERO, astuple(add(H, THREE), W))
    O = paint(paint(C, asobject(A)), shift(asobject(B), toivec(H)))
    return O

def dsl3(I):
    A = replace(I, ONE, TWO)
    H = height(I)
    W = width(I)
    O2 = toobject(ofcolor(A, TWO), A)
    P = vperiod(O2)
    Mid1 = crop(A, toivec(decrement(halve(H))), astuple(THREE, W))
    Mid2 = crop(A, toivec(halve(H)), astuple(THREE, W))
    B = branch(equality(P, THREE), Mid2, Mid1)
    O = vconcat(A, B)
    return O

def dsl4(I):
    A = replace(I, ONE, TWO)
    W = width(I)
    Top = crop(A, ORIGIN, astuple(THREE, W))
    O = vconcat(A, Top)
    return O

def dsl5(I):
    A = switch(I, ONE, TWO)
    S = toivec(increment(increment(uppermost(ofcolor(I, ONE)))))
    B = crop(A, S, astuple(THREE, width(I)))
    O = vconcat(A, B)
    return O
```