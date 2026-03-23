```python
def dsl1(I):
    no5 = replace(I, FIVE, SEVEN)
    H = hmirror(no5)
    A = cellwise(no5, H, SEVEN)
    V = vmirror(A)
    O = cellwise(A, V, SEVEN)
    return O

def dsl2(I):
    threes = ofcolor(I, THREE)
    bbox = box(threes)
    edge3 = intersection(threes, bbox)
    cleared = fill(replace(I, FIVE, SEVEN), SEVEN, threes)
    O = fill(cleared, FIVE, edge3)
    return O

def dsl3(I):
    z = ofcolor(I, ZERO)
    diag = mapply(ineighbors, z)
    threes = ofcolor(I, THREE)
    mark = intersection(diag, threes)
    cleared = fill(replace(I, FIVE, SEVEN), SEVEN, difference(threes, mark))
    O = fill(cleared, FIVE, mark)
    return O

def dsl4(I):
    z = ofcolor(I, ZERO)
    rays = mapply(rbind(shoot, DOWN_LEFT), z)
    threes = ofcolor(I, THREE)
    hit = intersection(rays, threes)
    cleared = fill(replace(I, FIVE, SEVEN), SEVEN, threes)
    O = fill(cleared, FIVE, hit)
    return O

def dsl5(I):
    threes = ofcolor(I, THREE)
    rightedge = difference(threes, shift(threes, RIGHT))
    cleared = fill(replace(I, FIVE, SEVEN), SEVEN, threes)
    O = fill(cleared, FIVE, rightedge)
    return O
```