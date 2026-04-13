```python
def dsl1(I):
    E = ofcolor(I, EIGHT)
    S = shift(E, RIGHT)
    Rays = mapply(rbind(shoot, RIGHT), totuple(S))
    O = underfill(I, ONE, Rays)
    return O

def dsl2(I):
    E = ofcolor(I, EIGHT)
    RightNeighbors = shift(E, LEFT)
    Rightmost = difference(E, RightNeighbors)
    S = shift(Rightmost, RIGHT)
    Rays = mapply(rbind(shoot, RIGHT), totuple(S))
    O = underfill(I, ONE, Rays)
    return O

def dsl3(I):
    E = ofcolor(I, EIGHT)
    L = shift(E, LEFT)
    R = shift(E, RIGHT)
    U = shift(E, UP)
    D = shift(E, DOWN)
    Adj = combine(combine(L, R), combine(U, D))
    Isolated = difference(E, Adj)
    S = shift(Isolated, RIGHT)
    Rays = mapply(rbind(shoot, RIGHT), totuple(S))
    RaysD = shift(Rays, DOWN)
    O = underfill(I, ONE, RaysD)
    return O

def dsl4(I):
    E = ofcolor(I, EIGHT)
    Above = shift(E, UP)
    Topmost = difference(E, Above)
    S = shift(Topmost, RIGHT)
    Rays = mapply(rbind(shoot, RIGHT), totuple(S))
    O = underfill(I, ONE, Rays)
    return O

def dsl5(I):
    Objs = colorfilter(objects(I, T, F, T), EIGHT)
    BorderObjs = sfilter(Objs, rbind(bordering, I))
    BorderIdx = mapply(toindices, totuple(BorderObjs))
    S = shift(BorderIdx, RIGHT)
    Rays = mapply(rbind(shoot, RIGHT), totuple(S))
    O = underfill(I, ONE, Rays)
    return O
```