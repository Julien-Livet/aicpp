```python
def dsl1(I):
    P = ofcolor(I, FIVE)
    Fs = frontiers(I)
    V = merge(mfilter(Fs, vline))
    H = merge(mfilter(Fs, hline))
    B = combine(V, H)
    base = replace(I, FIVE, EIGHT)
    R = intersection(P, B)
    O = fill(base, TWO, R)
    return O

def dsl2(I):
    P = ofcolor(I, FIVE)
    T = difference(P, shift(P, UP))
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, T)
    return O

def dsl3(I):
    P = ofcolor(I, FIVE)
    H = combine(difference(P, shift(P, LEFT)), difference(P, shift(P, RIGHT)))
    V = combine(difference(P, shift(P, UP)), difference(P, shift(P, DOWN)))
    R = intersection(H, V)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, R)
    return O

def dsl4(I):
    P = ofcolor(I, FIVE)
    B = box(P)
    R = intersection(P, B)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, R)
    return O

def dsl5(I):
    P = ofcolor(I, FIVE)
    Pd = shift(P, DOWN)
    LBd = difference(Pd, shift(Pd, LEFT))
    U = shift(LBd, UP)
    R = intersection(P, U)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, R)
    return O
```