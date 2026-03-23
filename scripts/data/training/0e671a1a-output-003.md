```python
def dsl1(I):
    nz = difference(asindices(I), ofcolor(I, ZERO))
    R = backdrop(nz)
    outline = box(R)
    p2 = toobject(ofcolor(I, TWO), I)
    p3 = toobject(ofcolor(I, THREE), I)
    l2 = ulcorner(p2)
    l3 = ulcorner(p3)
    top = intersection(outline, hfrontier(ulcorner(R)))
    left = intersection(outline, vfrontier(ulcorner(R)))
    right_full = intersection(outline, vfrontier(urcorner(R)))
    band_above3 = backdrop(combine(hfrontier(ulcorner(R)), hfrontier(l3)))
    right = intersection(right_full, band_above3)
    bottom_full = intersection(outline, hfrontier(lrcorner(R)))
    band_left2 = backdrop(combine(vfrontier(ulcorner(R)), vfrontier(l2)))
    bottom = intersection(bottom_full, band_left2)
    edges = combine(top, combine(left, combine(right, bottom)))
    O = underpaint(I, recolor(FIVE, edges))
    return O

def dsl2(I):
    p4 = toobject(ofcolor(I, FOUR), I)
    p3 = toobject(ofcolor(I, THREE), I)
    p2 = toobject(ofcolor(I, TWO), I)
    l4 = ulcorner(p4)
    l3 = ulcorner(p3)
    l2 = ulcorner(p2)
    a = first(intersection(hfrontier(l4), vfrontier(l2)))
    b = first(intersection(hfrontier(l4), vfrontier(l3)))
    c = first(intersection(hfrontier(l2), vfrontier(l4)))
    top = connect(a, l4)
    left = connect(l4, c)
    right = connect(b, l3)
    bottom = connect(c, l2)
    edges = combine(top, combine(left, combine(right, bottom)))
    O = underpaint(I, recolor(FIVE, edges))
    return O

def dsl3(I):
    p4 = toobject(ofcolor(I, FOUR), I)
    p3 = toobject(ofcolor(I, THREE), I)
    p2 = toobject(ofcolor(I, TWO), I)
    l4 = ulcorner(p4)
    l3 = ulcorner(p3)
    l2 = ulcorner(p2)
    nz = difference(asindices(I), ofcolor(I, ZERO))
    R = backdrop(nz)
    rect = box(R)
    lines = combine(hfrontier(l4), combine(hfrontier(l2), combine(vfrontier(l4), vfrontier(l3))))
    edges = intersection(rect, lines)
    O = underpaint(I, recolor(FIVE, edges))
    return O

def dsl4(I):
    p4 = toobject(ofcolor(I, FOUR), I)
    p3 = toobject(ofcolor(I, THREE), I)
    p2 = toobject(ofcolor(I, TWO), I)
    l4 = ulcorner(p4)
    l3 = ulcorner(p3)
    l2 = ulcorner(p2)
    Q = backdrop(combine(initset(l4), combine(initset(l3), initset(l2))))
    s_top = intersection(shoot(l4, RIGHT), Q)
    s_left = intersection(shoot(l4, DOWN), Q)
    a = first(intersection(hfrontier(l4), vfrontier(l3)))
    s_right = intersection(shoot(a, DOWN), Q)
    b = first(intersection(hfrontier(l2), vfrontier(l4)))
    s_bottom = intersection(shoot(b, RIGHT), Q)
    edges = combine(s_top, combine(s_left, combine(s_right, s_bottom)))
    O = underpaint(I, recolor(FIVE, edges))
    return O

def dsl5(I):
    J = dmirror(I)
    nz = difference(asindices(J), ofcolor(J, ZERO))
    R = backdrop(nz)
    outline = box(R)
    OJ = underpaint(J, recolor(FIVE, outline))
    O = dmirror(OJ)
    return O
```