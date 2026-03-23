```python
def dsl1(I):
    Ih = hmirror(I)
    Iv = vmirror(I)
    Eh = ofcolor(Ih, EIGHT)
    Ev = ofcolor(Iv, EIGHT)
    G = underfill(I, EIGHT, Eh)
    O = underfill(G, EIGHT, Ev)
    return O

def dsl2(I):
    F4 = ofcolor(I, FOUR)
    bb4 = inbox(F4)
    O = underfill(I, THREE, bb4)
    return O

def dsl3(I):
    O = replace(I, FOUR, THREE)
    return O

def dsl4(I):
    E = ofcolor(I, EIGHT)
    fR = rbind(shoot, RIGHT)
    fD = rbind(shoot, DOWN)
    raysR = apply(fR, E)
    raysD = apply(fD, E)
    PR = merge(raysR)
    PD = merge(raysD)
    G = fill(I, EIGHT, PR)
    O = fill(G, EIGHT, PD)
    return O

def dsl5(I):
    T2 = ofcolor(I, TWO)
    E = ofcolor(I, EIGHT)
    dir = gravitate(T2, E)
    f = rbind(shoot, dir)
    rays = apply(f, T2)
    P = merge(rays)
    O = fill(I, TWO, P)
    return O
```