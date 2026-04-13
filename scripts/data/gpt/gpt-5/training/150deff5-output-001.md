```python
def dsl1(I):
    P = ofcolor(I, FIVE)
    Fs = frontiers(I)
    V = mfilter(Fs, vline)
    base = replace(I, FIVE, EIGHT)
    R = intersection(P, V)
    O = fill(base, TWO, R)
    return O

def dsl2(I):
    P = ofcolor(I, FIVE)
    L = difference(P, shift(P, LEFT))
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, L)
    return O

def dsl3(I):
    P = ofcolor(I, FIVE)
    B = difference(P, shift(P, DOWN))
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, B)
    return O

def dsl4(I):
    P = ofcolor(I, FIVE)
    L = difference(P, shift(P, LEFT))
    Rr = difference(P, shift(P, RIGHT))
    B = combine(L, Rr)
    Top = asindices(tophalf(I))
    R = intersection(B, Top)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, R)
    return O

def dsl5(I):
    P = ofcolor(I, FIVE)
    Hr = intersection(P, shift(P, RIGHT))
    Vd = intersection(P, shift(P, DOWN))
    R = intersection(Hr, Vd)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, R)
    return O
```