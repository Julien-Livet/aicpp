```python
def dsl1(I):
    S0 = ofcolor(I, ZERO)
    hleft = shift(S0, LEFT)
    hright = shift(S0, RIGHT)
    vup = shift(S0, UP)
    vdown = shift(S0, DOWN)
    Sh = intersection(intersection(S0, hleft), hright)
    Sv = intersection(intersection(S0, vup), vdown)
    C = intersection(Sh, Sv)
    P1 = combine(C, shift(C, LEFT))
    P2 = combine(P1, shift(C, RIGHT))
    P3 = combine(P2, shift(C, UP))
    P = combine(P3, shift(C, DOWN))
    A = asindices(I)
    Pin = intersection(P, A)
    O = underfill(I, THREE, Pin)
    return O

def dsl2(I):
    S0 = ofcolor(I, ZERO)
    Sh = intersection(intersection(S0, shift(S0, LEFT)), shift(S0, RIGHT))
    Sv = intersection(intersection(S0, shift(S0, UP)), shift(S0, DOWN))
    C = intersection(Sh, Sv)
    arms_h = combine(shift(C, LEFT), shift(C, RIGHT))
    arms_v = combine(shift(C, UP), shift(C, DOWN))
    P = combine(C, combine(arms_h, arms_v))
    Z = intersection(P, S0)
    O = fill(I, THREE, Z)
    return O

def dsl3(I):
    Z = ofcolor(I, ZERO)
    HL = intersection(Z, shift(Z, LEFT))
    HR = intersection(Z, shift(Z, RIGHT))
    VL = intersection(Z, shift(Z, UP))
    VR = intersection(Z, shift(Z, DOWN))
    C = intersection(intersection(HL, HR), intersection(VL, VR))
    Cross = combine(C, combine(combine(shift(C, LEFT), shift(C, RIGHT)), combine(shift(C, UP), shift(C, DOWN))))
    O = underfill(I, THREE, Cross)
    return O
```