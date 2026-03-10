```python
def dsl1(I):
    a = ofcolor(I, FIVE)
    s1 = shift(a, UP)
    s2 = shift(a, DOWN)
    s3 = shift(a, LEFT)
    s4 = shift(a, RIGHT)
    s5 = shift(a, UP_RIGHT)
    s6 = shift(a, DOWN_LEFT)
    s7 = shift(a, NEG_UNITY)
    s8 = shift(a, UNITY)
    u1 = combine(s1, s2)
    u2 = combine(s3, s4)
    u3 = combine(s5, s6)
    u4 = combine(s7, s8)
    u12 = combine(u1, u2)
    u34 = combine(u3, u4)
    nbrs = combine(u12, u34)
    nb_in = intersection(nbrs, asindices(I))
    O = underfill(I, ONE, nb_in)
    return O

def dsl2(I):
    objs = objects(I, T, F, T)
    fives = colorfilter(objs, FIVE)
    rings = mapply(outbox, fives)
    nb_in = intersection(rings, asindices(I))
    O = underfill(I, ONE, nb_in)
    return O

def dsl3(I):
    locs = ofcolor(I, FIVE)
    n4 = mapply(neighbors, locs)
    d4 = mapply(ineighbors, locs)
    nbrs = combine(n4, d4)
    nb_in = intersection(nbrs, asindices(I))
    O = underfill(I, ONE, nb_in)
    return O

def dsl4(I):
    a = ofcolor(I, FIVE)
    s1 = shift(a, UP)
    s2 = shift(a, DOWN)
    s3 = shift(a, LEFT)
    s4 = shift(a, RIGHT)
    s5 = shift(a, UP_RIGHT)
    s6 = shift(a, DOWN_LEFT)
    s7 = shift(a, NEG_UNITY)
    s8 = shift(a, UNITY)
    u1 = combine(s1, s2)
    u2 = combine(s3, s4)
    u3 = combine(s5, s6)
    u4 = combine(s7, s8)
    u12 = combine(u1, u2)
    u34 = combine(u3, u4)
    nbrs = combine(u12, u34)
    nb_in = intersection(nbrs, asindices(I))
    x1 = fill(I, ONE, nb_in)
    fobj = toobject(a, I)
    O = paint(x1, fobj)
    return O

def dsl5(I):
    locs = ofcolor(I, FIVE)
    n4 = mapply(neighbors, locs)
    d4 = mapply(ineighbors, locs)
    nbrs = combine(n4, d4)
    nb_in = intersection(nbrs, asindices(I))
    onesobj = recolor(ONE, nb_in)
    O = underpaint(I, onesobj)
    return O
```