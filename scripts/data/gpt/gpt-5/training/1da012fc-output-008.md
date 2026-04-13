```python
def dsl1(I):
    # Relational nearest-seed (manhattan) with proper seed filtering (exclude 1 and 8; adjacent to largest object)
    S = objects(I, T, F, T)
    L = argmax(S, size)
    R = remove(L, S)
    T1 = colorfilter(S, ONE)
    T8 = colorfilter(S, EIGHT)
    Targets = combine(T1, T8)
    NonT = difference(R, Targets)
    Seeds0 = sizefilter(NonT, 1)
    AdjF = rbind(adjacent, L)
    Seeds = sfilter(Seeds0, AdjF)
    M0 = lbind(lbind, manhattan)
    Q = compose(M0, toindices)
    Rb = rbind(compose, toindices)
    J = compose(Rb, Q)                   # J(t)(s) = manhattan(toindices(t), toindices(s))
    N = compose(lbind(argmin, Seeds), J) # nearest seed for each target
    CF = fork(recolor, compose(color, N), toindices)
    U = merge(apply(CF, Targets))
    O = paint(I, U)
    return O

def dsl2(I):
    # Geometric nearest-seed by outline distance (use box outlines instead of raw indices)
    S = objects(I, T, F, T)
    L = argmax(S, size)
    R = remove(L, S)
    T1 = colorfilter(S, ONE)
    T8 = colorfilter(S, EIGHT)
    Targets = combine(T1, T8)
    NonT = difference(R, Targets)
    Seeds0 = sizefilter(NonT, 1)
    AdjF = rbind(adjacent, L)
    Seeds = sfilter(Seeds0, AdjF)
    M0 = lbind(lbind, manhattan)
    Q = compose(M0, box)
    Rb = rbind(compose, box)
    J = compose(Rb, Q)                   # J(t)(s) = manhattan(box(t), box(s))
    N = compose(lbind(argmin, Seeds), J)
    CF = fork(recolor, compose(color, N), toindices)
    U = merge(apply(CF, Targets))
    O = paint(I, U)
    return O

def dsl3(I):
    # Pure color filtering baseline: direct remap 1->2, 8->3
    A = replace(I, ONE, TWO)
    O = replace(A, EIGHT, THREE)
    return O

def dsl4(I):
    # Geometric propagation along seed's row/column restricted to target mask (1 or 8)
    S = objects(I, T, F, T)
    L = argmax(S, size)
    R = remove(L, S)
    T1 = colorfilter(S, ONE)
    T8 = colorfilter(S, EIGHT)
    Targets = combine(T1, T8)
    Tind = merge(apply(toindices, Targets))
    NonT = difference(R, Targets)
    Seeds0 = sizefilter(NonT, 1)
    AdjF = rbind(adjacent, L)
    Seeds = sfilter(Seeds0, AdjF)
    HR = compose(hfrontier, center)
    VR = compose(vfrontier, center)
    Lines = fork(combine, HR, VR)                # full row ∪ column through the seed
    Mask = compose(lbind(intersection, Tind), Lines)  # only keep target cells on those lines
    CF = fork(recolor, color, Mask)
    U = merge(apply(CF, Seeds))
    O = paint(I, U)
    return O

def dsl5(I):
    # Structural nearest-seed without size-1 restriction: any non-(1,8) object adjacent to largest object
    S = objects(I, T, F, T)
    L = argmax(S, size)
    R = remove(L, S)
    T1 = colorfilter(S, ONE)
    T8 = colorfilter(S, EIGHT)
    Targets = combine(T1, T8)
    NonT = difference(R, Targets)
    AdjF = rbind(adjacent, L)
    Seeds = sfilter(NonT, AdjF)                  # allow any size
    M0 = lbind(lbind, manhattan)
    Q = compose(M0, toindices)
    Rb = rbind(compose, toindices)
    J = compose(Rb, Q)                           # J(t)(s) = manhattan(toindices(t), toindices(s))
    N = compose(lbind(argmin, Seeds), J)
    CF = fork(recolor, compose(color, N), toindices)
    U = merge(apply(CF, Targets))
    O = paint(I, U)
    return O
```