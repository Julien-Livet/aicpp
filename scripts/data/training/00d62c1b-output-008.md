```python
def dsl1(I):
    A = ofcolor(I, THREE)
    Z = ofcolor(I, ZERO)
    B = box(A)
    shR = rbind(shoot, RIGHT)
    shL = rbind(shoot, LEFT)
    shU = rbind(shoot, UP)
    shD = rbind(shoot, DOWN)
    RR = merge(apply(shR, B))
    LL = merge(apply(shL, B))
    UU = merge(apply(shU, B))
    DD = merge(apply(shD, B))
    H = intersection(intersection(RR, LL), intersection(UU, DD))
    H = intersection(H, Z)
    O = underfill(I, FOUR, H)
    return O

def dsl2(I):
    O3 = colorfilter(objects(I, T, F, T), THREE)
    Hs = sfilter(O3, hline)
    Vs = sfilter(O3, vline)
    HB = merge(apply(backdrop, Hs))
    VB = merge(apply(backdrop, Vs))
    Z = ofcolor(I, ZERO)
    H = intersection(Z, intersection(HB, VB))
    O = underfill(I, FOUR, H)
    return O

def dsl3(I):
    A = ofcolor(I, THREE)
    Z = ofcolor(I, ZERO)
    BB = delta(A)
    H = intersection(BB, Z)
    O = underfill(I, FOUR, H)
    return O

def dsl4(I):
    A = ofcolor(I, THREE)
    Z = ofcolor(I, ZERO)
    C = centerofmass(A)
    U = shoot(C, UP)
    D = shoot(C, DOWN)
    L = shoot(C, LEFT)
    R = shoot(C, RIGHT)
    Cross = combine(combine(U, D), combine(L, R))
    H = intersection(Z, Cross)
    O = underfill(I, FOUR, H)
    return O

def dsl5(I):
    A = ofcolor(I, THREE)
    Z = ofcolor(I, ZERO)
    N = merge(apply(dneighbors, A))
    Adj0 = intersection(N, Z)
    HR = merge(apply(hfrontier, A))
    VR = merge(apply(vfrontier, A))
    M = intersection(HR, VR)
    H = intersection(Adj0, M)
    O = underfill(I, FOUR, H)
    return O
```