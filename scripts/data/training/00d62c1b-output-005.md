```python
def dsl1(I):
    Zobjs = colorfilter(objects(I, F, F, F), ZERO)
    notb = compose(flip, rbind(bordering, I))
    Holes = sfilter(Zobjs, notb)
    H = merge(apply(toindices, Holes))
    O = underfill(I, FOUR, H)
    return O

def dsl2(I):
    Z = ofcolor(I, ZERO)
    Zobjs = colorfilter(objects(I, F, F, F), ZERO)
    Bcomps = sfilter(Zobjs, rbind(bordering, I))
    B = merge(apply(toindices, Bcomps))
    H = difference(Z, B)
    O = underfill(I, FOUR, H)
    return O

def dsl3(I):
    Parts = partition(I)
    isZ = compose(rbind(equality, ZERO), color)
    notb = compose(flip, rbind(bordering, I))
    Zparts = sfilter(Parts, isZ)
    Holes = sfilter(Zparts, notb)
    H = merge(apply(toindices, Holes))
    O = underfill(I, FOUR, H)
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
    M = intersection(HB, VB)
    Zobjs = colorfilter(objects(I, F, F, F), ZERO)
    Bcomps = sfilter(Zobjs, rbind(bordering, I))
    BZ = merge(apply(toindices, Bcomps))
    Cand = intersection(M, Z)
    H = difference(Cand, BZ)
    O = underfill(I, FOUR, H)
    return O

def dsl5(I):
    Zobjs = colorfilter(objects(I, F, F, F), ZERO)
    keepf = compose(flip, rbind(bordering, I))
    Holes = sfilter(Zobjs, keepf)
    HoleObjs = apply(toobject, apply(toindices, Holes), repeat(I, size(Holes)))
    Painted = merge(apply(rbind(recolor, FOUR), HoleObjs))
    O = paint(I, Painted)
    return O
```