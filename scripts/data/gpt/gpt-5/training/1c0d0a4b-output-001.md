```python
def dsl1(I):
    c = leastcolor(I)
    pts = ofcolor(I, c)
    rows = mapply(hfrontier, pts)
    cols = mapply(vfrontier, pts)
    cross = intersection(rows, cols)
    mask = difference(cross, pts)
    O = fill(canvas(ZERO, shape(I)), TWO, mask)
    return O

def dsl2(I):
    c = leastcolor(I)
    pts = ofcolor(I, c)
    lefts = mapply(rbind(shoot, LEFT), pts)
    rights = mapply(rbind(shoot, RIGHT), pts)
    ups = mapply(rbind(shoot, UP), pts)
    downs = mapply(rbind(shoot, DOWN), pts)
    hcover = combine(lefts, rights)
    vcover = combine(ups, downs)
    cross = intersection(hcover, vcover)
    mask = difference(cross, pts)
    O = fill(canvas(ZERO, shape(I)), TWO, mask)
    return O

def dsl3(I):
    objs = colorfilter(fgpartition(I), leastcolor(I))
    pts = mapply(toindices, objs)
    rows = mapply(hfrontier, pts)
    cols = mapply(vfrontier, pts)
    cross = intersection(rows, cols)
    mask = difference(cross, pts)
    O = fill(canvas(ZERO, shape(I)), TWO, mask)
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
    Z = canvas(ZERO, shape(I))
    H = fill(Z, ONE, hcover)
    V = fill(Z, ONE, vcover)
    Both = cellwise(H, V, ZERO)
    m = ofcolor(Both, ONE)
    mask = difference(m, pts)
    O = fill(canvas(ZERO, shape(I)), TWO, mask)
    return O

def dsl5(I):
    c = leastcolor(I)
    pts = ofcolor(I, c)
    rows = mapply(hfrontier, pts)
    cols = mapply(vfrontier, pts)
    Z = canvas(ZERO, shape(I))
    H = fill(Z, ONE, rows)
    V = fill(Z, ONE, cols)
    Both = cellwise(H, V, ZERO)
    m = ofcolor(Both, ONE)
    mask = difference(m, pts)
    O = fill(canvas(ZERO, shape(I)), TWO, mask)
    return O
```