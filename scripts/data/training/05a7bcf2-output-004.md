```python
def dsl1(I):
    Ih = hmirror(I)
    Iv = vmirror(I)
    E0 = ofcolor(I, EIGHT)
    E1 = ofcolor(Ih, EIGHT)
    E2 = ofcolor(Iv, EIGHT)
    EM = combine(combine(E0, E1), E2)
    B = inbox(EM)
    O = underfill(I, EIGHT, B)
    return O

def dsl2(I):
    Os = fgpartition(I)
    F4s = colorfilter(Os, FOUR)
    B = merge(apply(inbox, F4s))
    O = fill(I, THREE, B)
    return O

def dsl3(I):
    P4 = ofcolor(I, FOUR)
    O = fill(I, THREE, P4)
    return O

def dsl4(I):
    E = ofcolor(I, EIGHT)
    T2 = ofcolor(I, TWO)
    c8 = centerofmass(E)
    c2 = centerofmass(T2)
    P = connect(c8, c2)
    O = underfill(I, EIGHT, P)
    return O

def dsl5(I):
    T2 = ofcolor(I, TWO)
    E = ofcolor(I, EIGHT)
    D = gravitate(T2, E)
    S = shift(T2, D)
    O = underfill(I, EIGHT, S)
    return O
```