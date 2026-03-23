```python
def dsl1(I):
    c = leastcolor(I)
    pts = ofcolor(I, c)
    rows = mapply(hfrontier, pts)
    cols = mapply(vfrontier, pts)
    cross = intersection(rows, cols)
    mask = difference(cross, pts)
    O = underfill(I, TWO, mask)
    return O

def dsl2(I):
    c = leastcolor(I)
    pts = ofcolor(I, c)
    up = mapply(rbind(shoot, UP), pts)
    down = mapply(rbind(shoot, DOWN), pts)
    lefts = mapply(rbind(shoot, LEFT), pts)
    rights = mapply(rbind(shoot, RIGHT), pts)
    hcover = combine(lefts, rights)
    vcover = combine(up, down)
    cross = intersection(hcover, vcover)
    mask = difference(cross, pts)
    O = underfill(I, TWO, mask)
    return O

def dsl3(I):
    objs = colorfilter(fgpartition(I), leastcolor(I))
    pts = mapply(toindices, objs)
    up = mapply(rbind(shoot, UP), pts)
    down = mapply(rbind(shoot, DOWN), pts)
    lefts = mapply(rbind(shoot, LEFT), pts)
    rights = mapply(rbind(shoot, RIGHT), pts)
    hcover = combine(lefts, rights)
    vcover = combine(up, down)
    cross = intersection(hcover, vcover)
    mask = difference(cross, pts)
    O = underfill(I, TWO, mask)
    return O

def dsl4(I):
    c = leastcolor(I)
    pts = ofcolor(I, c)
    lefts = mapply(rbind(shoot, LEFT), pts)
    rights = mapply(rbind(shoot, RIGHT), pts)
    ups = mapply(rbind(shoot, UP), pts)
    downs = mapply(rbind(shoot, DOWN), pts)
    hcover = combine(lefts, rights)
    vcover = combine(ups, downs)
    dims = shape(I)
    Z = canvas(ZERO, dims)
    H = fill(Z, ONE, hcover)
    V = fill(Z, ONE, vcover)
    Both = cellwise(H, V, ZERO)
    m = ofcolor(Both, ONE)
    mask = difference(m, pts)
    O = underfill(I, TWO, mask)
    return O

def dsl5(I):
    c = leastcolor(I)
    pts = ofcolor(I, c)
    rows = mapply(hfrontier, pts)
    cols = mapply(vfrontier, pts)
    cross = intersection(rows, cols)
    obj = recolor(TWO, cross)
    O = underpaint(I, obj)
    return O
```