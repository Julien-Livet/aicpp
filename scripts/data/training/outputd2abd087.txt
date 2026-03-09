```python
def dsl1(I):
    T = tophalf(I)
    B = bottomhalf(I)
    TL = lefthalf(T)
    TR = righthalf(T)
    BL = lefthalf(B)
    BR = righthalf(B)
    TL2 = replace(TL, FIVE, TWO)
    TR1 = replace(TR, FIVE, ONE)
    BL1 = replace(BL, FIVE, ONE)
    BR2 = replace(BR, FIVE, TWO)
    O = vconcat(hconcat(TL2, TR1), hconcat(BL1, BR2))
    return O

def dsl2(I):
    T = tophalf(I)
    B = bottomhalf(I)
    TL = lefthalf(T)
    TR = righthalf(T)
    BL = lefthalf(B)
    BR = righthalf(B)
    TL1 = replace(TL, FIVE, ONE)
    TR2 = replace(TR, FIVE, TWO)
    BL2 = replace(BL, FIVE, TWO)
    BR1 = replace(BR, FIVE, ONE)
    O = vconcat(hconcat(TL1, TR2), hconcat(BL2, BR1))
    return O

def dsl3(I):
    OBJS = objects(I, T, F, T)
    HCOND = fork(greater, width, height)
    HOR = sfilter(OBJS, HCOND)
    O0 = canvas(ZERO, shape(I))
    O1 = fill(O0, TWO, mapply(toindices, HOR))
    OTHER = difference(OBJS, HOR)
    O2 = fill(O1, ONE, mapply(toindices, OTHER))
    return O2

def dsl4(I):
    OBJS = objects(I, T, F, T)
    Wm1 = subtract(width(I), ONE)
    Hm1 = subtract(height(I), ONE)
    isRight = compose(rbind(equality, Wm1), rightmost)
    isBottom = compose(rbind(equality, Hm1), lowermost)
    RB = sfilter(OBJS, fork(either, isRight, isBottom))
    OTHER = difference(OBJS, RB)
    O0 = canvas(ZERO, shape(I))
    O1 = fill(O0, TWO, mapply(toindices, RB))
    O2 = fill(O1, ONE, mapply(toindices, OTHER))
    return O2

def dsl5(I):
    L = lefthalf(I)
    R = righthalf(I)
    L1 = replace(L, FIVE, ONE)
    R2 = replace(R, FIVE, TWO)
    O = hconcat(L1, R2)
    return O
```