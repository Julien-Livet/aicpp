```python
def dsl1(I):
    H = hmirror(I)
    A = cellwise(I, H, SEVEN)
    V = vmirror(A)
    O = cellwise(A, V, SEVEN)
    return O

def dsl2(I):
    threes = ofcolor(I, THREE)
    leftedge = difference(threes, shift(threes, LEFT))
    cleared = fill(I, SEVEN, threes)
    O = fill(cleared, FIVE, leftedge)
    return O

def dsl3(I):
    objs = objects(I, T, F, T)
    threes = colorfilter(objs, THREE)
    centers = mapply(centerofmass, threes)
    cleared = fill(I, SEVEN, ofcolor(I, THREE))
    O = fill(cleared, FIVE, centers)
    return O

def dsl4(I):
    idx = asindices(I)
    rightcol = vfrontier(urcorner(idx))
    bottomrow = hfrontier(lrcorner(idx))
    border = combine(rightcol, bottomrow)
    rb3 = intersection(ofcolor(I, THREE), border)
    cleared = fill(I, SEVEN, ofcolor(I, THREE))
    O = fill(cleared, FIVE, rb3)
    return O

def dsl5(I):
    threes = ofcolor(I, THREE)
    sevens = ofcolor(I, SEVEN)
    n3 = mapply(dneighbors, threes)
    boundary7 = intersection(n3, sevens)
    n7 = mapply(dneighbors, boundary7)
    edge3 = intersection(n7, threes)
    cleared = fill(I, SEVEN, threes)
    O = fill(cleared, FIVE, edge3)
    return O
```