```python
def dsl1(I):
    V = vmirror(I)
    O = cellwise(I, V, SEVEN)
    return O

def dsl2(I):
    objs = objects(I, T, F, T)
    threes = colorfilter(objs, THREE)
    ulcs = mapply(ulcorner, threes)
    cleared = fill(I, SEVEN, ofcolor(I, THREE))
    O = fill(cleared, FIVE, ulcs)
    return O

def dsl3(I):
    threes = ofcolor(I, THREE)
    shifted = shift(threes, DOWN)
    with_above = intersection(threes, shifted)
    topmost = difference(threes, with_above)
    cleared = fill(I, SEVEN, threes)
    O = fill(cleared, FIVE, topmost)
    return O

def dsl4(I):
    rightcol = vfrontier(urcorner(asindices(I)))
    rb3 = intersection(ofcolor(I, THREE), rightcol)
    cleared = fill(I, SEVEN, ofcolor(I, THREE))
    O = fill(cleared, FIVE, rb3)
    return O

def dsl5(I):
    zeros = ofcolor(I, ZERO)
    nbrs = mapply(dneighbors, zeros)
    threes = ofcolor(I, THREE)
    adj = intersection(nbrs, threes)
    cleared = fill(I, SEVEN, threes)
    O = fill(cleared, FIVE, adj)
    return O
```