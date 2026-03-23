```python
def dsl1(I):
    Id = dmirror(I)
    Ic = cmirror(I)
    E1 = ofcolor(Id, EIGHT)
    E2 = ofcolor(Ic, EIGHT)
    G = underfill(I, EIGHT, E1)
    O = underfill(G, EIGHT, E2)
    return O

def dsl2(I):
    Os = fgpartition(I)
    F4s = colorfilter(Os, FOUR)
    Bxs = apply(inbox, F4s)
    B = merge(Bxs)
    O = underfill(I, THREE, B)
    return O

def dsl3(I):
    O = switch(I, FOUR, THREE)
    return O

def dsl4(I):
    E = ofcolor(I, EIGHT)
    fR = rbind(shoot, RIGHT)
    fL = rbind(shoot, LEFT)
    fU = rbind(shoot, UP)
    fD = rbind(shoot, DOWN)
    PR = merge(apply(fR, E))
    PL = merge(apply(fL, E))
    PU = merge(apply(fU, E))
    PD = merge(apply(fD, E))
    M1 = combine(PR, PL)
    M2 = combine(PU, PD)
    M = combine(M1, M2)
    O = fill(I, EIGHT, M)
    return O

def dsl5(I):
    T2 = ofcolor(I, TWO)
    E = ofcolor(I, EIGHT)
    c2 = centerofmass(T2)
    c8 = centerofmass(E)
    P = connect(c2, c8)
    O = underfill(I, TWO, P)
    return O
```