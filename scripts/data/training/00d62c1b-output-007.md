```python
def dsl1(I):
    A = ofcolor(I, THREE)
    Z = ofcolor(I, ZERO)
    shR = rbind(shoot, RIGHT)
    shL = rbind(shoot, LEFT)
    shU = rbind(shoot, UP)
    shD = rbind(shoot, DOWN)
    RR = merge(apply(shR, A))
    LL = merge(apply(shL, A))
    UU = merge(apply(shU, A))
    DD = merge(apply(shD, A))
    HB = intersection(RR, LL)
    VB = intersection(UU, DD)
    H = intersection(Z, intersection(HB, VB))
    O = underfill(I, FOUR, H)
    return O

def dsl2(I):
    A = ofcolor(I, THREE)
    Z = ofcolor(I, ZERO)
    HR = merge(apply(hfrontier, A))
    VR = merge(apply(vfrontier, A))
    M = intersection(HR, VR)
    H = intersection(Z, M)
    O = underfill(I, FOUR, H)
    return O

def dsl3(I):
    A = ofcolor(I, THREE)
    Z = ofcolor(I, ZERO)
    shR = rbind(shoot, RIGHT)
    shL = rbind(shoot, LEFT)
    shU = rbind(shoot, UP)
    shD = rbind(shoot, DOWN)
    RR = merge(apply(shR, A))
    LL = merge(apply(shL, A))
    UU = merge(apply(shU, A))
    DD = merge(apply(shD, A))
    HB = intersection(RR, LL)
    VB = intersection(UU, DD)
    BB = backdrop(A)
    Outline = box(A)
    Interior = difference(BB, Outline)
    H = intersection(Interior, intersection(Z, intersection(HB, VB)))
    Obj = recolor(FOUR, toobject(H, I))
    O = paint(I, Obj)
    return O

def dsl4(I):
    A = ofcolor(I, THREE)
    Z = ofcolor(I, ZERO)
    shR = rbind(shoot, RIGHT)
    shL = rbind(shoot, LEFT)
    shU = rbind(shoot, UP)
    shD = rbind(shoot, DOWN)
    RR = merge(apply(shR, A))
    LL = merge(apply(shL, A))
    UU = merge(apply(shU, A))
    DD = merge(apply(shD, A))
    HB = intersection(RR, LL)
    VB = intersection(UU, DD)
    UM = combine(HB, VB)
    H = intersection(Z, UM)
    O = underfill(I, FOUR, H)
    return O

def dsl5(I):
    A = ofcolor(I, THREE)
    Z = ofcolor(I, ZERO)
    HR = merge(apply(hfrontier, A))
    VR = merge(apply(vfrontier, A))
    M = intersection(HR, VR)
    BB = delta(A)
    H = intersection(BB, intersection(Z, M))
    O = underfill(I, FOUR, H)
    return O
```