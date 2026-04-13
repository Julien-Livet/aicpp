```python
def dsl1(I):
    nz = difference(asindices(I), ofcolor(I, ZERO))
    rect = backdrop(nz)
    outline = box(rect)
    obj = recolor(FIVE, outline)
    O = underpaint(I, obj)
    return O

def dsl2(I):
    p4 = toobject(ofcolor(I, FOUR), I)
    p3 = toobject(ofcolor(I, THREE), I)
    p2 = toobject(ofcolor(I, TWO), I)
    l4 = ulcorner(p4)
    l3 = ulcorner(p3)
    l2 = ulcorner(p2)
    r4 = hfrontier(l4)
    c4 = vfrontier(l4)
    c3 = vfrontier(l3)
    r2 = hfrontier(l2)
    a = first(intersection(r4, c3))
    b = first(intersection(c4, r2))
    P = combine(initset(l4), combine(initset(a), initset(b)))
    R = backdrop(P)
    lines = combine(r4, combine(c4, combine(c3, r2)))
    clipped = intersection(lines, R)
    obj = recolor(FIVE, clipped)
    O = underpaint(I, obj)
    return O

def dsl3(I):
    p4 = toobject(ofcolor(I, FOUR), I)
    p3 = toobject(ofcolor(I, THREE), I)
    p2 = toobject(ofcolor(I, TWO), I)
    l4 = ulcorner(p4)
    l3 = ulcorner(p3)
    l2 = ulcorner(p2)
    lines = combine(hfrontier(l4), combine(vfrontier(l4), combine(vfrontier(l3), hfrontier(l2))))
    O = underfill(I, FIVE, lines)
    return O

def dsl4(I):
    nz = difference(asindices(I), ofcolor(I, ZERO))
    R = backdrop(nz)
    u = ulcorner(R)
    ur = urcorner(R)
    ll = llcorner(R)
    top = connect(u, ur)
    left = connect(u, ll)
    edges = combine(top, left)
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
    a = first(intersection(hfrontier(l4), vfrontier(l3)))
    b = first(intersection(vfrontier(l4), hfrontier(l2)))
    d = first(intersection(hfrontier(l2), vfrontier(l3)))
    s1 = connect(l4, a)
    s2 = connect(l4, b)
    s3 = connect(a, d)
    s4 = connect(b, l2)
    lines = combine(s1, combine(s2, combine(s3, s4)))
    O = underfill(I, FIVE, lines)
    return O
```