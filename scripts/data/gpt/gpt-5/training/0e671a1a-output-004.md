```python
def dsl1(I):
    p4 = toobject(ofcolor(I, FOUR), I)
    p3 = toobject(ofcolor(I, THREE), I)
    p2 = toobject(ofcolor(I, TWO), I)
    l4 = ulcorner(p4)
    l3 = ulcorner(p3)
    l2 = ulcorner(p2)
    cols_band = backdrop(combine(vfrontier(l4), vfrontier(l3)))
    rows_band = backdrop(combine(hfrontier(l4), hfrontier(l2)))
    top = intersection(hfrontier(l4), cols_band)
    bottom = intersection(hfrontier(l2), cols_band)
    left = intersection(vfrontier(l4), rows_band)
    right = intersection(vfrontier(l3), rows_band)
    edges = combine(top, combine(bottom, combine(left, right)))
    O = underpaint(I, recolor(FIVE, edges))
    return O

def dsl2(I):
    p4 = toobject(ofcolor(I, FOUR), I)
    p3 = toobject(ofcolor(I, THREE), I)
    p2 = toobject(ofcolor(I, TWO), I)
    l4 = ulcorner(p4)
    l3 = ulcorner(p3)
    l2 = ulcorner(p2)
    a = first(intersection(hfrontier(l4), vfrontier(l3)))
    c = first(intersection(hfrontier(l2), vfrontier(l4)))
    top = connect(l4, a)
    left = connect(l4, c)
    right = connect(a, l3)
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
    rows = combine(hfrontier(l4), hfrontier(l2))
    cols = combine(vfrontier(l4), vfrontier(l3))
    corners = intersection(rows, cols)
    rect = box(backdrop(corners))
    O = underpaint(I, recolor(FIVE, rect))
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
    s_right = intersection(shoot(l3, DOWN), Q)
    s_bottom = intersection(shoot(l2, RIGHT), Q)
    edges = combine(s_top, combine(s_left, combine(s_right, s_bottom)))
    O = underpaint(I, recolor(FIVE, edges))
    return O

def dsl5(I):
    p4 = toobject(ofcolor(I, FOUR), I)
    p3 = toobject(ofcolor(I, THREE), I)
    p2 = toobject(ofcolor(I, TWO), I)
    l4 = ulcorner(p4)
    l3 = ulcorner(p3)
    l2 = ulcorner(p2)
    cols_band = backdrop(combine(vfrontier(l4), vfrontier(l3)))
    rows_band = backdrop(combine(hfrontier(l4), hfrontier(l2)))
    R = intersection(rows_band, cols_band)
    edges = box(R)
    O = underpaint(I, recolor(FIVE, edges))
    return O
```