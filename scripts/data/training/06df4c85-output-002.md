```python
def dsl1(I):
    s = mostcolor(I)
    dims = shape(I)
    objs = objects(I, T, F, T)
    fg = mfilter(objs, compose(flip, matcher(color, s)))

    colors = apply(color, fg)
    groups = apply(lbind(colorfilter, fg), colors)

    pairsF = fork(product, identity, identity)

    # Vertical rectangles (same column)
    vPairs = compose(lbind(mfilter, fork(vmatching, first, last)), pairsF)
    vRectIdx = compose(backdrop, fork(combine, first, last))
    vCol = compose(color, first)
    vCan = compose(rbind(canvas, dims), vCol)
    vObj = fork(toobject, vRectIdx, vCan)
    vPairObjs = compose(lbind(apply, vObj), vPairs)
    perGroupV = compose(merge, vPairObjs)
    PVset = apply(perGroupV, groups)
    PV = merge(PVset)

    # Horizontal rectangles (same row)
    hPairs = compose(lbind(mfilter, fork(hmatching, first, last)), pairsF)
    hRectIdx = compose(backdrop, fork(combine, first, last))
    hCol = compose(color, first)
    hCan = compose(rbind(canvas, dims), hCol)
    hObj = fork(toobject, hRectIdx, hCan)
    hPairObjs = compose(lbind(apply, hObj), hPairs)
    perGroupH = compose(merge, hPairObjs)
    PHset = apply(perGroupH, groups)
    PH = merge(PHset)

    P = combine(PV, PH)
    O = underpaint(I, P)
    return O

def dsl2(I):
    s = mostcolor(I)
    dims = shape(I)
    objs = objects(I, T, F, T)
    fg = mfilter(objs, compose(flip, matcher(color, s)))

    colors = apply(color, fg)
    groups = apply(lbind(colorfilter, fg), colors)

    pairsF = fork(product, identity, identity)

    # Vertical via rectangles
    vPairs = compose(lbind(mfilter, fork(vmatching, first, last)), pairsF)
    vRectIdx = compose(backdrop, fork(combine, first, last))
    vCol = compose(color, first)
    vCan = compose(rbind(canvas, dims), vCol)
    vObj = fork(toobject, vRectIdx, vCan)
    vPairObjs = compose(lbind(apply, vObj), vPairs)
    perGroupV = compose(merge, vPairObjs)
    PV = merge(apply(perGroupV, groups))

    # Horizontal via interior of bounding box (delta(box))
    hPairs = compose(lbind(mfilter, fork(hmatching, first, last)), pairsF)
    hEdge = compose(box, fork(combine, first, last))
    hFillIdx = compose(delta, hEdge)
    hCol = compose(color, first)
    hCan = compose(rbind(canvas, dims), hCol)
    hObj = fork(toobject, hFillIdx, hCan)
    hPairObjs = compose(lbind(apply, hObj), hPairs)
    perGroupH = compose(merge, hPairObjs)
    PH = merge(apply(perGroupH, groups))

    P = combine(PV, PH)
    O = underpaint(I, P)
    return O

def dsl3(I):
    s = mostcolor(I)
    dims = shape(I)
    objs = objects(I, T, F, T)
    fg = mfilter(objs, compose(flip, matcher(color, s)))

    # All pairs across foreground, filtered by same color
    pairs = product(fg, fg)
    sameCol = fork(equality, compose(color, first), compose(color, last))
    eqPairs = mfilter(pairs, sameCol)

    # Build rectangles for vertical and horizontal matches
    condV = fork(vmatching, first, last)
    condH = fork(hmatching, first, last)
    cond = fork(either, condV, condH)

    rectIdx = compose(backdrop, fork(combine, first, last))
    colP = compose(color, first)
    canP = compose(rbind(canvas, dims), colP)
    objP = fork(toobject, rectIdx, canP)

    goodPairs = mfilter(eqPairs, cond)
    rectObjs = apply(objP, goodPairs)
    P = merge(rectObjs)

    O = underpaint(I, P)
    return O

def dsl4(I):
    s = mostcolor(I)
    dims = shape(I)
    objs = objects(I, T, F, T)
    fg = mfilter(objs, compose(flip, matcher(color, s)))

    colors = apply(color, fg)
    groups = apply(lbind(colorfilter, fg), colors)

    pairsF = fork(product, identity, identity)

    # Use interior of the bounding box via delta(box) for both alignments
    # Vertical
    vPairs = compose(lbind(mfilter, fork(vmatching, first, last)), pairsF)
    vEdge = compose(box, fork(combine, first, last))
    vFillIdx = compose(delta, vEdge)
    vCol = compose(color, first)
    vCan = compose(rbind(canvas, dims), vCol)
    vObj = fork(toobject, vFillIdx, vCan)
    vPerGroup = compose(merge, compose(lbind(apply, vObj), vPairs))
    PV = merge(apply(vPerGroup, groups))

    # Horizontal
    hPairs = compose(lbind(mfilter, fork(hmatching, first, last)), pairsF)
    hEdge = compose(box, fork(combine, first, last))
    hFillIdx = compose(delta, hEdge)
    hCol = compose(color, first)
    hCan = compose(rbind(canvas, dims), hCol)
    hObj = fork(toobject, hFillIdx, hCan)
    hPerGroup = compose(merge, compose(lbind(apply, hObj), hPairs))
    PH = merge(apply(hPerGroup, groups))

    P = combine(PV, PH)
    O = underpaint(I, P)
    return O

def dsl5(I):
    s = mostcolor(I)
    dims = shape(I)
    objs = objects(I, T, F, T)
    fg = mfilter(objs, compose(flip, matcher(color, s)))

    colors = apply(color, fg)
    groups = apply(lbind(colorfilter, fg), colors)

    pairsF = fork(product, identity, identity)

    # Unified: for each color group, connect any pair that shares row or column
    condV = fork(vmatching, first, last)
    condH = fork(hmatching, first, last)
    cond = fork(either, condV, condH)

    filtPairs = compose(lbind(mfilter, cond), pairsF)
    rectIdx = compose(backdrop, fork(combine, first, last))
    colG = compose(color, first)
    canG = compose(rbind(canvas, dims), colG)
    obj = fork(toobject, rectIdx, canG)

    pairObjs = compose(lbind(apply, obj), filtPairs)
    perGroup = compose(merge, pairObjs)

    P = merge(apply(perGroup, groups))
    O = underpaint(I, P)
    return O
```