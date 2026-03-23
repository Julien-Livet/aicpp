```python
def dsl1(I):
    G = asindices(I)
    Os = objects(I, T, F, T)
    U = argmin(Os, uppermost)
    S = argmin(Os, size)
    Top = hfrontier(ulcorner(G))
    Right = vfrontier(urcorner(G))
    O1 = fill(I, color(U), Top)
    O = fill(O1, color(S), Right)
    return O

def dsl2(I):
    Os = objects(I, T, F, T)
    S = argmin(Os, size)
    c = color(S)
    C = center(S)
    L = combine(shoot(C, LEFT), shoot(C, RIGHT))
    P = combine(L, initset(C))
    O = fill(I, c, P)
    return O

def dsl3(I):
    bg = mostcolor(I)
    lc = leastcolor(I)
    O = switch(I, bg, lc)
    return O

def dsl4(I):
    D = dmirror(I)
    C = cmirror(I)
    OD = asobject(D)
    OC = asobject(C)
    O1 = underpaint(I, OD)
    O = underpaint(O1, OC)
    return O

def dsl5(I):
    Os = objects(I, T, F, T)
    U = argmin(Os, uppermost)
    R = argmax(Os, rightmost)
    c = color(R)
    PU = center(U)
    PR = center(R)
    P = connect(PU, PR)
    O = fill(I, c, P)
    return O
```