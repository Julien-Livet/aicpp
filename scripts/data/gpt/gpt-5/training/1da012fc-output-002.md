```python
def dsl1(I):
    S = objects(I, T, F, T)
    L = argmax(S, size)
    R = remove(L, S)
    Seeds = sizefilter(R, 1)
    Targets = difference(R, Seeds)
    TI = merge(apply(toindices, Targets))
    AO = recolor(leastcolor(I), TI)
    O = paint(I, AO)
    return O

def dsl2(I):
    S = objects(I, T, F, T)
    L = argmax(S, size)
    R = remove(L, S)
    Seeds = sizefilter(R, 1)
    Targets = difference(R, Seeds)
    B = lbind(lbind, manhattan)
    A = compose(lbind(order, Seeds), B)
    N = compose(first, A)
    CF = fork(recolor, compose(color, N), toindices)
    C = apply(CF, Targets)
    U = merge(C)
    O = paint(I, U)
    return O

def dsl3(I):
    A = replace(I, ONE, leastcolor(I))
    O = replace(A, EIGHT, leastcolor(I))
    return O

def dsl4(I):
    S = objects(I, T, F, T)
    L = argmax(S, size)
    R = remove(L, S)
    Seeds = sizefilter(R, 1)
    Targets = difference(R, Seeds)
    TI = merge(apply(toindices, Targets))
    H = compose(hfrontier, center)
    V = compose(vfrontier, center)
    Cross = fork(combine, H, V)
    Mask = compose(lbind(intersection, TI), Cross)
    RF = fork(recolor, color, Mask)
    C = apply(RF, Seeds)
    U = merge(C)
    O = paint(I, U)
    return O

def dsl5(I):
    F = merge(frontiers(I))
    O = cover(I, F)
    return O
```