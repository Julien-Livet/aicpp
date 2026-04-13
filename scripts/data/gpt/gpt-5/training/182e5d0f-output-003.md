```python
def dsl1(I):
    z = ofcolor(I, ZERO)
    th = ofcolor(I, THREE)
    ne = shift(z, DOWN_LEFT)
    se = shift(z, NEG_UNITY)
    rightpair = intersection(ne, se)
    nw = shift(z, UNITY)
    sw = shift(z, UP_RIGHT)
    leftpair = intersection(nw, sw)
    pair = combine(rightpair, leftpair)
    marks = intersection(th, pair)
    cleared = replace(I, FIVE, SEVEN)
    O = fill(cleared, FIVE, marks)
    return O

def dsl2(I):
    z = ofcolor(I, ZERO)
    r1 = mapply(rbind(shoot, DOWN_LEFT), z)
    r2 = mapply(rbind(shoot, UNITY), z)
    rays = combine(r1, r2)
    th = ofcolor(I, THREE)
    ledge = difference(th, shift(th, LEFT))
    redge = difference(th, shift(th, RIGHT))
    atleft = intersection(rays, ledge)
    atright = intersection(rays, redge)
    marks = combine(atleft, atright)
    cleared = replace(I, FIVE, SEVEN)
    O = fill(cleared, FIVE, marks)
    return O

def dsl3(I):
    objs = colorfilter(objects(I, T, F, T), THREE)
    th = mapply(toindices, objs)
    diag = mapply(ineighbors, ofcolor(I, ZERO))
    edges = combine(difference(th, shift(th, LEFT)), difference(th, shift(th, RIGHT)))
    marks = intersection(diag, edges)
    cleared = replace(I, FIVE, SEVEN)
    O = fill(cleared, FIVE, marks)
    return O

def dsl4(I):
    z = ofcolor(I, ZERO)
    rows = mapply(hfrontier, z)
    th = ofcolor(I, THREE)
    inrows = intersection(th, rows)
    redge = difference(inrows, shift(inrows, RIGHT))
    cleared = replace(I, FIVE, SEVEN)
    O = fill(cleared, FIVE, redge)
    return O

def dsl5(I):
    z = ofcolor(I, ZERO)
    near = combine(mapply(ineighbors, z), mapply(dneighbors, z))
    th = ofcolor(I, THREE)
    marks = intersection(th, near)
    cleared = replace(I, FIVE, SEVEN)
    O = fill(cleared, FIVE, marks)
    return O
```