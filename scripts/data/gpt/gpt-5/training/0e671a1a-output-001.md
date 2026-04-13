```python
def dsl1(I):
    nz = difference(asindices(I), ofcolor(I, ZERO))
    R = backdrop(nz)
    u = ulcorner(R)
    ur = urcorner(R)
    lr = lrcorner(R)
    top = connect(u, ur)
    right = connect(ur, lr)
    edges = combine(top, right)
    obj = recolor(FIVE, edges)
    O = underpaint(I, obj)
    return O

def dsl2(I):
    p4 = toobject(ofcolor(I, FOUR), I)
    p3 = toobject(ofcolor(I, THREE), I)
    p2 = toobject(ofcolor(I, TWO), I)
    l4 = ulcorner(p4)
    l3 = ulcorner(p3)
    l2 = ulcorner(p2)
    P = combine(initset(l4), combine(initset(l3), initset(l2)))
    R = backdrop(P)
    outline = box(R)
    obj = recolor(FIVE, outline)
    O = underpaint(I, obj)
    return O

def dsl3(I):
    p4 = toobject(ofcolor(I, FOUR), I)
    p3 = toobject(ofcolor(I, THREE), I)
    p2 = toobject(ofcolor(I, TWO), I)
    l4 = ulcorner(p4)
    l3 = ulcorner(p3)
    l2 = ulcorner(p2)
    lines = combine(vfrontier(l4), combine(vfrontier(l3), combine(hfrontier(l4), hfrontier(l2))))
    O = underfill(I, FIVE, lines)
    return O

def dsl4(I):
    p4 = toobject(ofcolor(I, FOUR), I)
    p3 = toobject(ofcolor(I, THREE), I)
    p2 = toobject(ofcolor(I, TWO), I)
    l4 = ulcorner(p4)
    l3 = ulcorner(p3)
    l2 = ulcorner(p2)
    a = first(intersection(hfrontier(l4), vfrontier(l3)))
    b = first(intersection(vfrontier(l4), hfrontier(l2)))
    d = first(intersection(hfrontier(l2), vfrontier(l3)))
    s1 = connect(l4, a)
    s2 = connect(l4, b)
    s3 = connect(a, d)
    s4 = connect(b, d)
    edges = combine(s1, combine(s2, combine(s3, s4)))
    obj = recolor(FIVE, edges)
    O = underpaint(I, obj)
    return O

def dsl5(I):
    p4 = toobject(ofcolor(I, FOUR), I)
    p3 = toobject(ofcolor(I, THREE), I)
    p2 = toobject(ofcolor(I, TWO), I)
    l4 = ulcorner(p4)
    l3 = ulcorner(p3)
    l2 = ulcorner(p2)
    P = combine(initset(l4), combine(initset(l3), initset(l2)))
    R = backdrop(P)
    lines = combine(vfrontier(l4), combine(vfrontier(l3), combine(hfrontier(l4), hfrontier(l2))))
    clipped = intersection(lines, R)
    O = underfill(I, FIVE, clipped)
    return O
```