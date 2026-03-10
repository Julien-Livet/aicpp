```python
def dsl1(I):
    # Axis-aligned grid lines from seeds expanded by estimated period
    c = leastcolor(I)
    S = ofcolor(I, c)
    Obj = toobject(S, I)
    pv = vperiod(Obj)
    ph = hperiod(Obj)
    p = branch(positive(pv), pv, ph)
    p = branch(positive(p), p, ONE)
    E = S
    E = combine(E, shift(S, astuple(0, p)))
    E = combine(E, shift(S, astuple(0, invert(p))))
    E = combine(E, shift(S, astuple(0, double(p))))
    E = combine(E, shift(S, astuple(0, invert(double(p)))))
    E = combine(E, shift(S, astuple(p, 0)))
    E = combine(E, shift(S, astuple(invert(p), 0)))
    E = combine(E, shift(S, astuple(double(p), 0)))
    E = combine(E, shift(S, astuple(invert(double(p)), 0)))
    D = initset(UP)
    D = insert(DOWN, D)
    D = insert(LEFT, D)
    D = insert(RIGHT, D)
    R = prapply(shoot, E, D)
    P = merge(R)
    Z = canvas(ZERO, shape(I))
    O = fill(Z, c, P)
    return O

def dsl2(I):
    # Diagonal stripe lattice from seeds, offset by multiples of period
    c = leastcolor(I)
    S = ofcolor(I, c)
    Obj = toobject(S, I)
    pv = vperiod(Obj)
    ph = hperiod(Obj)
    p = branch(positive(pv), pv, ph)
    p = branch(positive(p), p, ONE)
    off1 = astuple(p, invert(p))
    off2 = astuple(invert(p), p)
    off3 = astuple(double(p), invert(double(p)))
    off4 = astuple(invert(double(p)), double(p))
    E = S
    E = combine(E, shift(S, off1))
    E = combine(E, shift(S, off2))
    E = combine(E, shift(S, off3))
    E = combine(E, shift(S, off4))
    UL = add(UP, LEFT)
    UR = UP_RIGHT
    DL = DOWN_LEFT
    DR = add(DOWN, RIGHT)
    D = initset(UR)
    D = insert(DL, D)
    D = insert(UL, D)
    D = insert(DR, D)
    R = prapply(shoot, E, D)
    P = merge(R)
    Z = canvas(ZERO, shape(I))
    O = fill(Z, c, P)
    return O

def dsl3(I):
    # Lattice of rectangular outlines based on bounding box, replicated by period shifts
    c = leastcolor(I)
    S = ofcolor(I, c)
    Obj = toobject(S, I)
    pv = vperiod(Obj)
    ph = hperiod(Obj)
    p = branch(positive(pv), pv, ph)
    p = branch(positive(p), p, ONE)
    B = backdrop(S)
    Out = box(B)
    P = Out
    P = combine(P, shift(Out, astuple(p, 0)))
    P = combine(P, shift(Out, astuple(invert(p), 0)))
    P = combine(P, shift(Out, astuple(0, p)))
    P = combine(P, shift(Out, astuple(0, invert(p))))
    P = combine(P, shift(Out, astuple(p, p)))
    P = combine(P, shift(Out, astuple(p, invert(p))))
    P = combine(P, shift(Out, astuple(invert(p), p)))
    P = combine(P, shift(Out, astuple(invert(p), invert(p))))
    Z = canvas(ZERO, shape(I))
    O = fill(Z, c, P)
    return O

def dsl4(I):
    # Limited starburst from seeds (4 axis + 2 diagonals), without full 8-direction spread
    c = leastcolor(I)
    S = ofcolor(I, c)
    UL = add(UP, LEFT)
    UR = UP_RIGHT
    D = initset(UP)
    D = insert(DOWN, D)
    D = insert(LEFT, D)
    D = insert(RIGHT, D)
    D = insert(UL, D)
    D = insert(UR, D)
    R = prapply(shoot, S, D)
    P = merge(R)
    Z = canvas(ZERO, shape(I))
    O = fill(Z, c, P)
    return O

def dsl5(I):
    # Periodic axis lines generated from the object's center, shifted by multiples of period
    c = leastcolor(I)
    S = ofcolor(I, c)
    Obj = toobject(S, I)
    pv = vperiod(Obj)
    ph = hperiod(Obj)
    p = branch(positive(pv), pv, ph)
    p = branch(positive(p), p, ONE)
    s = centerofmass(Obj)
    Dh = initset(LEFT)
    Dh = insert(RIGHT, Dh)
    Dv = initset(UP)
    Dv = insert(DOWN, Dv)
    H0 = merge(prapply(shoot, initset(s), Dh))
    V0 = merge(prapply(shoot, initset(s), Dv))
    H = H0
    H = combine(H, shift(H0, astuple(p, 0)))
    H = combine(H, shift(H0, astuple(invert(p), 0)))
    H = combine(H, shift(H0, astuple(double(p), 0)))
    H = combine(H, shift(H0, astuple(invert(double(p)), 0)))
    V = V0
    V = combine(V, shift(V0, astuple(0, p)))
    V = combine(V, shift(V0, astuple(0, invert(p))))
    V = combine(V, shift(V0, astuple(0, double(p))))
    V = combine(V, shift(V0, astuple(0, invert(double(p)))))
    P = combine(H, V)
    Z = canvas(ZERO, shape(I))
    O = fill(Z, c, P)
    return O
```