```python
def dsl1(I):
    nz = difference(asindices(I), ofcolor(I, ZERO))
    R = backdrop(nz)
    outline = box(R)
    obj = recolor(FIVE, outline)
    O = underpaint(I, obj)
    return O

def dsl2(I):
    p3 = toobject(ofcolor(I, THREE), I)
    p2 = toobject(ofcolor(I, TWO), I)
    l3 = ulcorner(p3)
    l2 = ulcorner(p2)
    R = backdrop(combine(vfrontier(l3), hfrontier(l2)))
    outline = box(R)
    O = underpaint(I, recolor(FIVE, outline))
    return O

def dsl3(I):
    p4 = toobject(ofcolor(I, FOUR), I)
    p3 = toobject(ofcolor(I, THREE), I)
    p2 = toobject(ofcolor(I, TWO), I)
    l4 = ulcorner(p4)
    l3 = ulcorner(p3)
    l2 = ulcorner(p2)
    R = backdrop(combine(initset(l4), combine(initset(l3), initset(l2))))
    outline = box(R)
    e_top = intersection(outline, hfrontier(l4))
    e_bot = intersection(outline, hfrontier(l2))
    e_left = intersection(outline, vfrontier(l4))
    e_right = intersection(outline, vfrontier(l3))
    edges = combine(e_top, combine(e_bot, combine(e_left, e_right)))
    O = underpaint(I, recolor(FIVE, edges))
    return O

def dsl4(I):
    nz = difference(asindices(I), ofcolor(I, ZERO))
    R = backdrop(nz)
    ul = ulcorner(R)
    ur = urcorner(R)
    lr = lrcorner(R)
    ll = llcorner(R)
    top = connect(ul, ur)
    right = connect(ur, lr)
    bottom = connect(lr, ll)
    left = connect(ll, ul)
    edges = combine(top, combine(right, combine(bottom, left)))
    O = underpaint(I, recolor(FIVE, edges))
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
    Q = backdrop(combine(initset(l4), combine(initset(a), combine(initset(b), initset(d)))))
    s_top = intersection(shoot(l4, RIGHT), Q)
    s_left = intersection(shoot(l4, DOWN), Q)
    s_right = intersection(shoot(a, DOWN), Q)
    s_bottom = intersection(shoot(b, RIGHT), Q)
    edges = combine(s_top, combine(s_left, combine(s_right, s_bottom)))
    O = underpaint(I, recolor(FIVE, edges))
    return O
```