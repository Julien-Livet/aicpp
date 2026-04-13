```python
def dsl1(I):
    A = replace(I, ONE, TWO)
    H2 = halve(height(I))
    S = toivec(decrement(H2))
    B = crop(A, S, astuple(THREE, width(I)))
    O = vconcat(A, B)
    return O

def dsl2(I):
    A = replace(I, ONE, TWO)
    H = height(I)
    W = width(I)
    S = toivec(decrement(halve(H)))
    Mid = crop(A, S, astuple(THREE, W))
    Pobj = asobject(Mid)
    Qobj = shift(Pobj, toivec(H))
    C = canvas(ZERO, astuple(add(H, THREE), W))
    O = underpaint(underpaint(C, asobject(A)), Qobj)
    return O

def dsl3(I):
    H = height(I)
    W = width(I)
    C = canvas(ZERO, astuple(add(H, THREE), W))
    X = ofcolor(I, ONE)
    O1 = paint(C, recolor(TWO, X))
    S = toivec(decrement(halve(H)))
    T = crop(I, S, astuple(THREE, W))
    Xmid = ofcolor(T, ONE)
    O = paint(O1, recolor(TWO, shift(Xmid, toivec(H))))
    return O

def dsl4(I):
    A = replace(I, ONE, TWO)
    W = width(I)
    Top = tophalf(A)
    Bot = bottomhalf(A)
    R1 = crop(Top, toivec(decrement(THREE)), astuple(ONE, W))
    R2 = crop(Bot, ORIGIN, astuple(TWO, W))
    B = vconcat(R1, R2)
    O = vconcat(A, B)
    return O

def dsl5(I):
    A = replace(I, ONE, TWO)
    W = width(I)
    Parts = hsplit(A, 2)
    Top = first(Parts)
    Bot = last(Parts)
    R1 = crop(Top, toivec(decrement(THREE)), astuple(ONE, W))
    R2 = crop(Bot, ORIGIN, astuple(TWO, W))
    B = vconcat(R1, R2)
    O = vconcat(A, B)
    return O
```