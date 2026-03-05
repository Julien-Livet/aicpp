```python
def dsl1(I):
    c = leastcolor(I)
    s = first(ofcolor(I, c))
    l1 = shoot(s, UP_RIGHT)
    l2 = shoot(s, DOWN_LEFT)
    l3 = shoot(s, NEG_UNITY)
    l4 = shoot(s, UNITY)
    u1 = combine(l1, l2)
    u2 = combine(l3, l4)
    u = combine(u1, u2)
    O = fill(I, c, u)
    return O

def dsl2(I):
    o = first(objects(I, T, F, T))
    c = color(o)
    s = first(toindices(o))
    l1 = shoot(s, UP_RIGHT)
    l2 = shoot(s, DOWN_LEFT)
    l3 = shoot(s, NEG_UNITY)
    l4 = shoot(s, UNITY)
    u1 = combine(l1, l2)
    u2 = combine(l3, l4)
    u = combine(u1, u2)
    O = fill(I, c, u)
    return O

def dsl3(I):
    p = palette(I)
    cset = remove(ZERO, p)
    c = first(cset)
    s = first(ofcolor(I, c))
    l1 = shoot(s, UP_RIGHT)
    l2 = shoot(s, DOWN_LEFT)
    l3 = shoot(s, NEG_UNITY)
    l4 = shoot(s, UNITY)
    u1 = combine(l1, l2)
    u2 = combine(l3, l4)
    u = combine(u1, u2)
    O = fill(I, c, u)
    return O

def dsl4(I):
    c = leastcolor(I)
    s = first(ofcolor(I, c))
    l1 = shoot(s, UP_RIGHT)
    l2 = shoot(s, DOWN_LEFT)
    l3 = shoot(s, NEG_UNITY)
    l4 = shoot(s, UNITY)
    ctr = initset(s)
    u12 = combine(l1, l2)
    u34 = combine(l3, l4)
    u1234 = combine(u12, u34)
    u = combine(u1234, ctr)
    base = canvas(ZERO, shape(I))
    O = fill(base, c, u)
    return O
```