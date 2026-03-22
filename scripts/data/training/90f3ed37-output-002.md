```python
def dsl1(I):
    E = ofcolor(I, EIGHT)
    Rightmost = difference(E, shift(E, LEFT))
    Lowermost = difference(E, shift(E, UP))
    Corners = intersection(Rightmost, Lowermost)
    HAdj = combine(shift(E, LEFT), shift(E, RIGHT))
    IsoH = difference(E, HAdj)
    A = intersection(Corners, IsoH)
    B = difference(Corners, A)
    SA = shift(A, RIGHT)
    SB = shift(B, RIGHT)
    RaysA = mapply(rbind(shoot, RIGHT), totuple(SA))
    RaysB = mapply(rbind(shoot, RIGHT), totuple(SB))
    Rays = combine(shift(RaysA, DOWN), RaysB)
    O = underfill(I, ONE, Rays)
    return O

def dsl2(I):
    E = ofcolor(I, EIGHT)
    Z = ofcolor(I, ZERO)
    S0 = intersection(shift(E, RIGHT), Z)
    DownHasE = shift(E, UP)
    S = difference(S0, DownHasE)
    Rays = mapply(rbind(shoot, RIGHT), totuple(S))
    O = underfill(I, ONE, Rays)
    return O

def dsl3(I):
    E = ofcolor(I, EIGHT)
    Z = ofcolor(I, ZERO)
    S0 = intersection(shift(E, RIGHT), Z)
    UpHasE = shift(E, DOWN)
    S = difference(S0, UpHasE)
    Rays = mapply(rbind(shoot, RIGHT), totuple(S))
    O = underfill(I, ONE, Rays)
    return O

def dsl4(I):
    E = ofcolor(I, EIGHT)
    Rightmost = difference(E, shift(E, LEFT))
    Topmost = difference(E, shift(E, DOWN))
    Lowermost = difference(E, shift(E, UP))
    Corners = combine(intersection(Rightmost, Topmost), intersection(Rightmost, Lowermost))
    S = shift(Corners, RIGHT)
    Rays = mapply(rbind(shoot, RIGHT), totuple(S))
    O = underfill(I, ONE, Rays)
    return O

def dsl5(I):
    E = ofcolor(I, EIGHT)
    Rightmost = difference(E, shift(E, LEFT))
    HasLeftNbr = shift(E, RIGHT)
    Ends = intersection(Rightmost, HasLeftNbr)
    S = shift(Ends, RIGHT)
    Rays = mapply(rbind(shoot, RIGHT), totuple(S))
    O = underfill(I, ONE, Rays)
    return O
```