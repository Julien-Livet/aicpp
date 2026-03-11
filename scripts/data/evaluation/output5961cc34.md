```python
def dsl1(I):
    h, w = shape(I)
    O = canvas(EIGHT, astuple(h, w))
    p4 = first(ofcolor(I, FOUR))
    H = hfrontier(p4)
    V = vfrontier(p4)
    cross = combine(H, V)
    O = fill(O, TWO, cross)
    return O

def dsl2(I):
    h, w = shape(I)
    O = canvas(EIGHT, astuple(h, w))
    p4 = first(ofcolor(I, FOUR))
    col = vfrontier(p4)
    O = fill(O, TWO, col)
    return O

def dsl3(I):
    h, w = shape(I)
    O = canvas(EIGHT, astuple(h, w))
    s1 = ofcolor(I, ONE)
    s3 = ofcolor(I, THREE)
    fg = combine(s1, s3)
    rect = backdrop(fg)
    border = box(rect)
    O = fill(O, TWO, border)
    return O

def dsl4(I):
    h, w = shape(I)
    O = canvas(EIGHT, astuple(h, w))
    s1 = ofcolor(I, ONE)
    s3 = ofcolor(I, THREE)
    fg = combine(s1, s3)
    rows = merge(apply(hfrontier, fg))
    cols = merge(apply(vfrontier, fg))
    stripes = combine(rows, cols)
    bbox = backdrop(fg)
    core = intersection(stripes, bbox)
    O = fill(O, TWO, core)
    return O

def dsl5(I):
    h, w = shape(I)
    O = canvas(EIGHT, astuple(h, w))
    s2 = ofcolor(I, TWO)
    s4 = ofcolor(I, FOUR)
    anchors = combine(s2, s4)
    cols = merge(apply(vfrontier, anchors))
    O = fill(O, TWO, cols)
    return O
```