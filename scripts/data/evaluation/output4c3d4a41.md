```python
def dsl1(I):
    # Keep only the top edge, bottom edge, and right edge of the right-side rectangle; restore non-FIVE digits
    dims = shape(I)
    objs = objects(I, T, F, T)
    fiveobjs = colorfilter(objs, FIVE)
    non5objs = difference(objs, fiveobjs)
    non5 = merge(non5objs)

    topRow = hfrontier(astuple(0, 0))
    topFives = intersection(ofcolor(I, FIVE), topRow)
    j0 = leftmost(topFives)

    topRight = shoot(astuple(0, j0), RIGHT)
    rightPlane = merge(apply(vfrontier, topRight))
    rect = backdrop(rightPlane)

    ul = ulcorner(rect)
    ur = urcorner(rect)
    ll = llcorner(rect)
    lr = lrcorner(rect)

    topEdge = connect(ul, ur)
    bottomEdge = connect(ll, lr)
    rightEdge = connect(ur, lr)
    edges = combine(combine(topEdge, bottomEdge), rightEdge)

    O0 = canvas(ZERO, dims)
    O1 = fill(O0, FIVE, edges)
    O = paint(O1, non5)
    return O

def dsl2(I):
    # Frame (top, bottom, right) of the right-side rectangle + vertical columns at columns containing non-FIVEs within their box
    dims = shape(I)
    objs = objects(I, T, F, T)
    fiveobjs = colorfilter(objs, FIVE)
    non5objs = difference(objs, fiveobjs)
    non5 = merge(non5objs)
    n5idx = toindices(non5)

    topRow = hfrontier(astuple(0, 0))
    topFives = intersection(ofcolor(I, FIVE), topRow)
    j0 = leftmost(topFives)

    topRight = shoot(astuple(0, j0), RIGHT)
    rightPlane = merge(apply(vfrontier, topRight))
    rect = backdrop(rightPlane)

    ul = ulcorner(rect)
    ur = urcorner(rect)
    ll = llcorner(rect)
    lr = lrcorner(rect)

    topEdge = connect(ul, ur)
    bottomEdge = connect(ll, lr)
    rightEdge = connect(ur, lr)
    edges = combine(combine(topEdge, bottomEdge), rightEdge)

    colsMask = merge(apply(vfrontier, n5idx))
    n5box = backdrop(n5idx)
    colsInBox = intersection(colsMask, n5box)
    colsInRight = intersection(colsInBox, rightPlane)

    allowed = combine(edges, colsInRight)

    O0 = canvas(ZERO, dims)
    O1 = fill(O0, FIVE, allowed)
    O = paint(O1, non5)
    return O

def dsl3(I):
    # Frame (top, bottom, right) + keep 5s only in the top half on columns that contain non-FIVEs
    dims = shape(I)
    objs = objects(I, T, F, T)
    fiveobjs = colorfilter(objs, FIVE)
    non5objs = difference(objs, fiveobjs)
    non5 = merge(non5objs)
    n5idx = toindices(non5)

    topRow = hfrontier(astuple(0, 0))
    topFives = intersection(ofcolor(I, FIVE), topRow)
    j0 = leftmost(topFives)

    topRight = shoot(astuple(0, j0), RIGHT)
    rightPlane = merge(apply(vfrontier, topRight))
    rect = backdrop(rightPlane)

    ul = ulcorner(rect)
    ur = urcorner(rect)
    ll = llcorner(rect)
    lr = lrcorner(rect)

    topEdge = connect(ul, ur)
    bottomEdge = connect(ll, lr)
    rightEdge = connect(ur, lr)
    edges = combine(combine(topEdge, bottomEdge), rightEdge)

    colsMask = merge(apply(vfrontier, n5idx))
    topHalf = asindices(tophalf(I))
    colsTop = intersection(colsMask, topHalf)
    colsTopRight = intersection(colsTop, rightPlane)

    allowed = combine(edges, colsTopRight)

    O0 = canvas(ZERO, dims)
    O1 = fill(O0, FIVE, allowed)
    O = paint(O1, non5)
    return O

def dsl4(I):
    # Frame (top, bottom, right) + keep 5s that are adjacent to any non-FIVE (restricted to right plane)
    dims = shape(I)
    objs = objects(I, T, F, T)
    fiveobjs = colorfilter(objs, FIVE)
    non5objs = difference(objs, fiveobjs)
    non5 = merge(non5objs)
    n5idx = toindices(non5)

    topRow = hfrontier(astuple(0, 0))
    topFives = intersection(ofcolor(I, FIVE), topRow)
    j0 = leftmost(topFives)

    topRight = shoot(astuple(0, j0), RIGHT)
    rightPlane = merge(apply(vfrontier, topRight))
    rect = backdrop(rightPlane)

    ul = ulcorner(rect)
    ur = urcorner(rect)
    ll = llcorner(rect)
    lr = lrcorner(rect)

    topEdge = connect(ul, ur)
    bottomEdge = connect(ll, lr)
    rightEdge = connect(ur, lr)
    edges = combine(combine(topEdge, bottomEdge), rightEdge)

    nbrs = merge(apply(neighbors, n5idx))
    adj5 = intersection(nbrs, ofcolor(I, FIVE))
    adj5right = intersection(adj5, rightPlane)

    allowed = combine(edges, adj5right)

    O0 = canvas(ZERO, dims)
    O1 = fill(O0, FIVE, allowed)
    O = paint(O1, non5)
    return O

def dsl5(I):
    # Frame (top, bottom, right) + horizontal 5-lines at rows that contain any non-FIVE (clipped to right plane)
    dims = shape(I)
    objs = objects(I, T, F, T)
    fiveobjs = colorfilter(objs, FIVE)
    non5objs = difference(objs, fiveobjs)
    non5 = merge(non5objs)
    n5idx = toindices(non5)

    topRow = hfrontier(astuple(0, 0))
    topFives = intersection(ofcolor(I, FIVE), topRow)
    j0 = leftmost(topFives)

    topRight = shoot(astuple(0, j0), RIGHT)
    rightPlane = merge(apply(vfrontier, topRight))
    rect = backdrop(rightPlane)

    ul = ulcorner(rect)
    ur = urcorner(rect)
    ll = llcorner(rect)
    lr = lrcorner(rect)

    topEdge = connect(ul, ur)
    bottomEdge = connect(ll, lr)
    rightEdge = connect(ur, lr)
    edges = combine(combine(topEdge, bottomEdge), rightEdge)

    rowsMask = merge(apply(hfrontier, n5idx))
    rowsInRight = intersection(rowsMask, rightPlane)

    allowed = combine(edges, rowsInRight)

    O0 = canvas(ZERO, dims)
    O1 = fill(O0, FIVE, allowed)
    O = paint(O1, non5)
    return O
```