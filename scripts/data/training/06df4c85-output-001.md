```python
def dsl1(I):
    s = mostcolor(I)
    objs = objects(I, T, F, T)
    fg = mfilter(objs, compose(flip, matcher(color, s)))
    colors = apply(color, fg)
    groups = apply(lbind(colorfilter, fg), colors)
    dims = shape(I)

    unionObjs = apply(merge, groups)

    idxF = toindices
    upF = compose(merge, lbind(apply, rbind(shoot, UP)))
    dnF = compose(merge, lbind(apply, rbind(shoot, DOWN)))
    lfF = compose(merge, lbind(apply, rbind(shoot, LEFT)))
    rtF = compose(merge, lbind(apply, rbind(shoot, RIGHT)))
    upIdx = compose(upF, idxF)
    dnIdx = compose(dnF, idxF)
    lfIdx = compose(lfF, idxF)
    rtIdx = compose(rtF, idxF)

    hlines = fork(combine, lfIdx, rtIdx)
    vlines = fork(combine, upIdx, dnIdx)
    lines = fork(combine, hlines, vlines)
    bbox = backdrop
    mask = fork(intersection, lines, bbox)

    canF = compose(rbind(canvas, dims), color)
    objFromG = fork(toobject, mask, canF)

    Pset = apply(objFromG, unionObjs)
    P = merge(Pset)
    O = underpaint(I, P)
    return O

def dsl2(I):
    s = mostcolor(I)
    objs = objects(I, T, F, T)
    fg = mfilter(objs, compose(flip, matcher(color, s)))
    colors = apply(color, fg)
    groups = apply(lbind(colorfilter, fg), colors)
    dims = shape(I)

    aF = first
    bF = last
    colA = compose(color, aF)
    canF = compose(rbind(canvas, dims), colA)
    uF = fork(combine, aF, bF)
    rectIdx = compose(backdrop, uF)
    ia = compose(toindices, aF)
    emptyIdx = fork(difference, ia, ia)
    condH = fork(hmatching, aF, bF)
    mask = fork(branch, condH, rectIdx, emptyIdx)
    obj = fork(toobject, mask, canF)

    pairsF = fork(product, identity, identity)
    pairObjs = compose(lbind(apply, obj), pairsF)
    perColor = compose(merge, pairObjs)

    P = mapply(perColor, groups)
    O = underpaint(I, P)
    return O

def dsl3(I):
    s = mostcolor(I)
    objs = objects(I, T, F, T)
    fg = mfilter(objs, compose(flip, matcher(color, s)))
    colors = apply(color, fg)
    groups = apply(lbind(colorfilter, fg), colors)
    dims = shape(I)

    aF = first
    bF = last
    colA = compose(color, aF)
    canF = compose(rbind(canvas, dims), colA)
    uF = fork(combine, aF, bF)
    rectIdx = compose(backdrop, uF)
    ia = compose(toindices, aF)
    emptyIdx = fork(difference, ia, ia)
    condV = fork(vmatching, aF, bF)
    mask = fork(branch, condV, rectIdx, emptyIdx)
    obj = fork(toobject, mask, canF)

    pairsF = fork(product, identity, identity)
    pairObjs = compose(lbind(apply, obj), pairsF)
    perColor = compose(merge, pairObjs)

    P = mapply(perColor, groups)
    O = underpaint(I, P)
    return O

def dsl4(I):
    s = mostcolor(I)
    objs = objects(I, T, F, T)
    fg = mfilter(objs, compose(flip, matcher(color, s)))
    colors = apply(color, fg)
    groups = apply(lbind(colorfilter, fg), colors)
    dims = shape(I)

    aF = first
    bF = last
    colA = compose(color, aF)
    canF = compose(rbind(canvas, dims), colA)
    ca = compose(center, aF)
    cb = compose(center, bF)
    lineIdx = fork(connect, ca, cb)
    ia = compose(toindices, aF)
    emptyIdx = fork(difference, ia, ia)
    condH = fork(hmatching, aF, bF)
    condV = fork(vmatching, aF, bF)
    cond = fork(either, condH, condV)
    mask = fork(branch, cond, lineIdx, emptyIdx)
    obj = fork(toobject, mask, canF)

    pairsF = fork(product, identity, identity)
    pairObjs = compose(lbind(apply, obj), pairsF)
    perColor = compose(merge, pairObjs)

    P = mapply(perColor, groups)
    O = underpaint(I, P)
    return O

def dsl5(I):
    s = mostcolor(I)
    objs = objects(I, T, F, T)
    fg = mfilter(objs, compose(flip, matcher(color, s)))
    colors = apply(color, fg)
    groups = apply(lbind(colorfilter, fg), colors)
    dims = shape(I)

    aF = first
    bF = last
    colA = compose(color, aF)
    canF = compose(rbind(canvas, dims), colA)
    uF = fork(combine, aF, bF)
    rectIdx = compose(backdrop, uF)
    ia = compose(toindices, aF)
    emptyIdx = fork(difference, ia, ia)
    condH = fork(hmatching, aF, bF)
    condV = fork(vmatching, aF, bF)
    cond = fork(either, condH, condV)
    mask = fork(branch, cond, rectIdx, emptyIdx)
    obj = fork(toobject, mask, canF)

    pairsF = fork(product, identity, identity)
    pairObjs = compose(lbind(apply, obj), pairsF)
    perColor = compose(merge, pairObjs)

    P = mapply(perColor, groups)
    O = underpaint(I, P)
    return O
```