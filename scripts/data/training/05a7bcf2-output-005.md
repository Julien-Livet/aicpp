```python
def dsl1(I):
    E = ofcolor(I, EIGHT)
    T2 = ofcolor(I, TWO)
    c8 = centerofmass(E)
    c2 = centerofmass(T2)
    P = connect(c8, c2)
    B = inbox(P)
    O = underfill(I, EIGHT, B)
    return O

def dsl2(I):
    Os = fgpartition(I)
    F4s = colorfilter(Os, FOUR)
    Bs = apply(backdrop, F4s)
    B = merge(Bs)
    O = fill(I, THREE, B)
    return O

def dsl3(I):
    O = switch(I, FOUR, THREE)
    return O

def dsl4(I):
    Iv = vmirror(I)
    Ev = ofcolor(Iv, EIGHT)
    Obj = recolor(EIGHT, Ev)
    O = underpaint(I, Obj)
    return O

def dsl5(I):
    E = ofcolor(I, EIGHT)
    T2 = ofcolor(I, TWO)
    U = combine(E, T2)
    B = inbox(U)
    O = underfill(I, EIGHT, B)
    return O
```