```python
def dsl1(I):
    # Geometric ray-to-largest: shoot from each target toward the largest object; pick nearest seed to that ray
    S = objects(I, T, F, T)
    L = argmax(S, size)
    R = remove(L, S)
    T1 = colorfilter(S, ONE)
    T8 = colorfilter(S, EIGHT)
    Targets = combine(T1, T8)
    NonT = difference(R, Targets)
    AdjF = rbind(adjacent, L)
    Seeds = sfilter(NonT, AdjF)
    G = rbind(gravitate, L)
    Ray = fork(shoot, center, G)                        # Ray(t) from center(t) toward L
    M0 = lbind(lbind, manhattan)
    Q = compose(M0, Ray)                                # Q(t) = lbind(manhattan, Ray(t))
    Rb = rbind(compose, toindices)
    J = compose(Rb, Q)                                  # J(t)(s) = manhattan(Ray(t), toindices(s))
    N = compose(lbind(argmin, Seeds), J)                # nearest seed for each target
    CF = fork(recolor, compose(color, N), toindices)
    U = merge(apply(CF, Targets))
    O = paint(I, U)
    return O

def dsl2(I):
    # Object-extraction via ring sampling: recolor each target by most common seed color in its outbox ring
    S = objects(I, T, F, T)
    L = argmax(S, size)
    R = remove(L, S)
    T1 = colorfilter(S, ONE)
    T8 = colorfilter(S, EIGHT)
    Targets = combine(T1, T8)
    NonT = difference(R, Targets)
    AdjF = rbind(adjacent, L)
    Seeds = sfilter(NonT, AdjF)
    SeedInd = merge(apply(toindices, Seeds))
    Mask = compose(lbind(intersection, SeedInd), outbox)          # ring ∩ seeds
    RingObj = compose(rbind(toobject, I), Mask)                    # seed-colored ring-as-object
    Ccol = compose(mostcolor, RingObj)                             # dominant seed color on ring
    CF = fork(recolor, Ccol, toindices)
    U = merge(apply(CF, Targets))
    O = paint(I, U)
    return O

def dsl3(I):
    # Cross alignment: choose seed nearest to the target's row∪column cross
    S = objects(I, T, F, T)
    L = argmax(S, size)
    R = remove(L, S)
    T1 = colorfilter(S, ONE)
    T8 = colorfilter(S, EIGHT)
    Targets = combine(T1, T8)
    NonT = difference(R, Targets)
    AdjF = rbind(adjacent, L)
    Seeds = sfilter(NonT, AdjF)
    HR = compose(hfrontier, center)
    VR = compose(vfrontier, center)
    Cross = fork(combine, HR, VR)                                   # row ∪ column through target center
    M0 = lbind(lbind, manhattan)
    Q = compose(M0, Cross)                                          # Q(t) = lbind(manhattan, Cross(t))
    Rb = rbind(compose, toindices)
    J = compose(Rb, Q)                                              # J(t)(s) = manhattan(Cross(t), toindices(s))
    N = compose(lbind(argmin, Seeds), J)
    CF = fork(recolor, compose(color, N), toindices)
    U = merge(apply(CF, Targets))
    O = paint(I, U)
    return O

def dsl4(I):
    # Global propagation: from every non-(1,8) seed, paint along its row/column onto target cells
    S = objects(I, T, F, T)
    T1 = colorfilter(S, ONE)
    T8 = colorfilter(S, EIGHT)
    Targets = combine(T1, T8)
    Tind = merge(apply(toindices, Targets))
    NonT = difference(S, Targets)
    HR = compose(hfrontier, center)
    VR = compose(vfrontier, center)
    Lines = fork(combine, HR, VR)                                   # row ∪ column through seed center
    Mask = compose(lbind(intersection, Tind), Lines)                 # restrict to target cells
    CF = fork(recolor, color, Mask)
    U = merge(apply(CF, NonT))
    O = paint(I, U)
    return O

def dsl5(I):
    # Seed-centric alignment: nearest seed by distance to its own row∪column lines
    S = objects(I, T, F, T)
    L = argmax(S, size)
    R = remove(L, S)
    T1 = colorfilter(S, ONE)
    T8 = colorfilter(S, EIGHT)
    Targets = combine(T1, T8)
    NonT = difference(R, Targets)
    AdjF = rbind(adjacent, L)
    Seeds = sfilter(NonT, AdjF)
    HRs = compose(hfrontier, center)
    VRs = compose(vfrontier, center)
    SL = fork(combine, HRs, VRs)                                    # row ∪ column through seed center
    M0 = lbind(lbind, manhattan)
    Q = compose(M0, toindices)                                      # Q(t) = lbind(manhattan, toindices(t))
    Rb = rbind(compose, SL)
    J = compose(Rb, Q)                                              # J(t)(s) = manhattan(toindices(t), SL(s))
    N = compose(lbind(argmin, Seeds), J)
    CF = fork(recolor, compose(color, N), toindices)
    U = merge(apply(CF, Targets))
    O = paint(I, U)
    return O
```