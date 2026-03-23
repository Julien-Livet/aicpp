```python
def dsl1(I):
    ones = ofcolor(I, ONE)
    twos = ofcolor(I, TWO)
    one_n = mapply(dneighbors, ones)
    two_n = mapply(ineighbors, twos)
    O = underfill(I, SEVEN, one_n)
    O = underfill(O, FOUR, two_n)
    return O

def dsl2(I):
    ones = ofcolor(I, ONE)
    twos = ofcolor(I, TWO)
    plus1 = combine(shift(ones, UP), shift(ones, DOWN))
    plus2 = combine(shift(ones, LEFT), shift(ones, RIGHT))
    one_n = combine(plus1, plus2)
    diag1 = combine(shift(twos, UNITY), shift(twos, NEG_UNITY))
    diag2 = combine(shift(twos, UP_RIGHT), shift(twos, DOWN_LEFT))
    two_n = combine(diag1, diag2)
    idx = asindices(I)
    one_n = intersection(one_n, idx)
    two_n = intersection(two_n, idx)
    O = underfill(I, SEVEN, one_n)
    O = underfill(O, FOUR, two_n)
    return O

def dsl3(I):
    objs = fgpartition(I)
    ones_objs = colorfilter(objs, ONE)
    twos_objs = colorfilter(objs, TWO)
    ones_idx = mapply(toindices, ones_objs)
    twos_idx = mapply(toindices, twos_objs)
    one_n = mapply(dneighbors, ones_idx)
    two_n = mapply(ineighbors, twos_idx)
    obj7 = recolor(SEVEN, one_n)
    obj4 = recolor(FOUR, two_n)
    O = underpaint(I, obj7)
    O = underpaint(O, obj4)
    return O

def dsl4(I):
    ones = ofcolor(I, ONE)
    twos = ofcolor(I, TWO)
    lr = mapply(hfrontier, ones)
    ud = mapply(vfrontier, ones)
    one_n = combine(lr, ud)
    two_n = mapply(ineighbors, twos)
    O = underfill(I, SEVEN, one_n)
    O = underfill(O, FOUR, two_n)
    return O

def dsl5(I):
    idx = asindices(I)
    ones = ofcolor(I, ONE)
    twos = ofcolor(I, TWO)
    r = apply(lbind(add, RIGHT), ones)
    l = apply(lbind(add, LEFT), ones)
    u = apply(lbind(add, UP), ones)
    d = apply(lbind(add, DOWN), ones)
    one_n = combine(combine(l, r), combine(u, d))
    one_n = intersection(one_n, idx)
    dr = apply(lbind(add, UNITY), twos)
    ul = apply(lbind(add, NEG_UNITY), twos)
    ur = apply(lbind(add, UP_RIGHT), twos)
    dl = apply(lbind(add, DOWN_LEFT), twos)
    two_n = combine(combine(dr, ul), combine(ur, dl))
    two_n = intersection(two_n, idx)
    g7 = fill(canvas(ZERO, shape(I)), SEVEN, one_n)
    g4 = fill(canvas(ZERO, shape(I)), FOUR, two_n)
    o7 = asobject(g7)
    o4 = asobject(g4)
    O = underpaint(I, o7)
    O = underpaint(O, o4)
    return O
```