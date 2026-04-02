```python
def dsl1(I):
    a = ofcolor(I, TWO)
    b = ofcolor(I, FOUR)
    anchors = combine(a, b)
    l = leftmost(anchors)
    r = rightmost(anchors)
    locl = astuple(ZERO, l)
    locr = astuple(ZERO, r)
    colL = vfrontier(locl)
    colR = vfrontier(locr)
    region = inbox(combine(colL, colR))
    O = underfill(I, EIGHT, region)
    return O

def dsl2(I):
    b4 = inbox(ofcolor(I, FOUR))
    b2 = inbox(ofcolor(I, TWO))
    o4 = recolor(FOUR, b4)
    o2 = recolor(TWO, b2)
    both = combine(o4, o2)
    O = underpaint(I, both)
    return O

def dsl3(I):
    e = ofcolor(I, EIGHT)
    j = rightmost(e)
    loc = astuple(ZERO, j)
    col = vfrontier(loc)
    O = underfill(I, EIGHT, col)
    return O

def dsl4(I):
    p4 = ofcolor(I, FOUR)
    p2 = ofcolor(I, TWO)
    start = ulcorner(p4)
    end = urcorner(p2)
    path = connect(start, end)
    O = fill(I, EIGHT, path)
    return O

def dsl5(I):
    anchors = combine(ofcolor(I, TWO), ofcolor(I, FOUR))
    u = uppermost(anchors)
    v = lowermost(anchors)
    r1 = hfrontier(astuple(u, ZERO))
    r2 = hfrontier(astuple(v, ZERO))
    region = inbox(combine(r1, r2))
    O = underfill(I, EIGHT, region)
    return O
```