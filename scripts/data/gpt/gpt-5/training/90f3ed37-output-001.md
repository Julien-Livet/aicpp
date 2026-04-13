```python
def dsl1(I):
    E = ofcolor(I, EIGHT)
    RightNbr = shift(E, LEFT)
    Rightmost = difference(E, RightNbr)
    BelowNbr = shift(E, UP)
    Lowermost = difference(E, BelowNbr)
    Anch = intersection(Rightmost, Lowermost)
    S = shift(Anch, RIGHT)
    Rays = mapply(rbind(shoot, RIGHT), totuple(S))
    O = underfill(I, ONE, Rays)
    return O

def dsl2(I):
    E = ofcolor(I, EIGHT)
    L = shift(E, LEFT)
    R = shift(E, RIGHT)
    HAdj = combine(L, R)
    IsoH = difference(E, HAdj)
    S = shift(IsoH, RIGHT)
    Rays = mapply(rbind(shoot, RIGHT), totuple(S))
    RaysD = shift(Rays, DOWN)
    O = underfill(I, ONE, RaysD)
    return O

def dsl3(I):
    E = ofcolor(I, EIGHT)
    Topmost = difference(E, shift(E, UP))
    Rightmost = difference(E, shift(E, LEFT))
    Corners = intersection(Topmost, Rightmost)
    S = shift(Corners, RIGHT)
    Rays = mapply(rbind(shoot, RIGHT), totuple(S))
    O = underfill(I, ONE, Rays)
    return O

def dsl4(I):
    E = ofcolor(I, EIGHT)
    Z = ofcolor(I, ZERO)
    S = intersection(shift(E, RIGHT), Z)
    Rays = mapply(rbind(shoot, RIGHT), totuple(S))
    O = underfill(I, ONE, Rays)
    return O

def dsl5(I):
    E = ofcolor(I, EIGHT)
    Rightmost = difference(E, shift(E, LEFT))
    VAdj = combine(shift(E, UP), shift(E, DOWN))
    VertIso = difference(E, VAdj)
    A = intersection(Rightmost, VertIso)
    B = difference(Rightmost, A)
    SA = shift(A, RIGHT)
    SB = shift(B, RIGHT)
    RaysA = mapply(rbind(shoot, RIGHT), totuple(SA))
    RaysB = mapply(rbind(shoot, RIGHT), totuple(SB))
    Rays = combine(shift(RaysA, DOWN), RaysB)
    O = underfill(I, ONE, Rays)
    return O
```