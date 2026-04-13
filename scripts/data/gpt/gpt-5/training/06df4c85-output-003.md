```python
def dsl1(I):
    # Relational: connect same-colored tiles along rows or columns with filled rectangles
    s = mostcolor(I)
    dims = shape(I)
    objs = objects(I, T, F, T)
    fg = sfilter(objs, compose(flip, matcher(color, s)))

    pairs = product(fg, fg)
    sameCol = fork(equality, compose(color, first), compose(color, last))
    condV = fork(vmatching, first, last)
    condH = fork(hmatching, first, last)
    aligned = fork(either, condV, condH)
    good = sfilter(pairs, fork(both, sameCol, aligned))

    rectIdx = compose(backdrop, fork(combine, first, last))
    colP = compose(color, first)
    canP = compose(rbind(canvas, dims), colP)
    objP = fork(toobject, rectIdx, canP)

    rects = apply(objP, good)
    P = merge(rects)
    O = underpaint(I, P)
    return O

def dsl2(I):
    # Object extraction by color groups; build horizontal and vertical fills via interior of bounding boxes
    s = mostcolor(I)
    dims = shape(I)
    objs = objects(I, T, F, T)
    fg = sfilter(objs, compose(flip, matcher(color, s)))

    cols = apply(color, fg)
    groups = apply(lbind(colorfilter, fg), cols)

    pairsF = fork(product, identity, identity)
    same = fork(equality, compose(color, first), compose(color, last))

    # Horizontal
    hcond = fork(both, same, fork(hmatching, first, last))
    hPairs = compose(lbind(sfilter, hcond), pairsF)
    hFillIdx = compose(delta, compose(box, fork(combine, first, last)))
    hCol = compose(color, first)
    hCan = compose(rbind(canvas, dims), hCol)
    hObj = fork(toobject, hFillIdx, hCan)
    hPerGroup = compose(merge, compose(lbind(apply, hObj), hPairs))
    PH = merge(apply(hPerGroup, groups))

    # Vertical
    vcond = fork(both, same, fork(vmatching, first, last))
    vPairs = compose(lbind(sfilter, vcond), pairsF)
    vFillIdx = compose(delta, compose(box, fork(combine, first, last)))
    vCol = compose(color, first)
    vCan = compose(rbind(canvas, dims), vCol)
    vObj = fork(toobject, vFillIdx, vCan)
    vPerGroup = compose(merge, compose(lbind(apply, vObj), vPairs))
    PV = merge(apply(vPerGroup, groups))

    P = combine(PH, PV)
    O = underpaint(I, P)
    return O

def dsl3(I):
    # Two-pass geometric: first fill horizontally, then recompute and fill vertically
    dims = shape(I)
    s0 = mostcolor(I)
    objs0 = objects(I, T, F, T)
    fg0 = sfilter(objs0, compose(flip, matcher(color, s0)))

    pairs0 = product(fg0, fg0)
    same0 = fork(equality, compose(color, first), compose(color, last))
    hcond0 = fork(both, same0, fork(hmatching, first, last))
    goodH0 = sfilter(pairs0, hcond0)
    rectIdxH0 = compose(backdrop, fork(combine, first, last))
    colH0 = compose(color, first)
    canH0 = compose(rbind(canvas, dims), colH0)
    objH0 = fork(toobject, rectIdxH0, canH0)
    rectsH0 = apply(objH0, goodH0)
    P1 = merge(rectsH0)
    O1 = underpaint(I, P1)

    s1 = mostcolor(O1)
    objs1 = objects(O1, T, F, T)
    fg1 = sfilter(objs1, compose(flip, matcher(color, s1)))

    pairs1 = product(fg1, fg1)
    same1 = fork(equality, compose(color, first), compose(color, last))
    vcond1 = fork(both, same1, fork(vmatching, first, last))
    goodV1 = sfilter(pairs1, vcond1)
    rectIdxV1 = compose(backdrop, fork(combine, first, last))
    colV1 = compose(color, first)
    canV1 = compose(rbind(canvas, dims), colV1)
    objV1 = fork(toobject, rectIdxV1, canV1)
    rectsV1 = apply(objV1, goodV1)
    P2 = merge(rectsV1)
    O = underpaint(O1, P2)
    return O

def dsl4(I):
    # Geometric (orientation split): vertical rectangles via full backdrop, horizontal via interior; union
    s = mostcolor(I)
    dims = shape(I)
    objs = objects(I, T, F, T)
    fg = sfilter(objs, compose(flip, matcher(color, s)))

    pairs = product(fg, fg)
    same = fork(equality, compose(color, first), compose(color, last))

    # Vertical (use full backdrop)
    vcond = fork(both, same, fork(vmatching, first, last))
    vPairs = sfilter(pairs, vcond)
    vIdx = compose(backdrop, fork(combine, first, last))
    vCol = compose(color, first)
    vCan = compose(rbind(canvas, dims), vCol)
    vObj = fork(toobject, vIdx, vCan)
    vRects = apply(vObj, vPairs)
    PV = merge(vRects)

    # Horizontal (use interior via delta(box))
    hcond = fork(both, same, fork(hmatching, first, last))
    hPairs = sfilter(pairs, hcond)
    hIdx = compose(delta, compose(box, fork(combine, first, last)))
    hCol = compose(color, first)
    hCan = compose(rbind(canvas, dims), hCol)
    hObj = fork(toobject, hIdx, hCan)
    hRects = apply(hObj, hPairs)
    PH = merge(hRects)

    P = combine(PV, PH)
    O = underpaint(I, P)
    return O

def dsl5(I):
    # Color-filtered relational: per-color, unify H and V connections using shared rectangle builder
    s = mostcolor(I)
    dims = shape(I)
    objs = objects(I, T, F, T)
    fg = sfilter(objs, compose(flip, matcher(color, s)))

    cols = apply(color, fg)
    groups = apply(lbind(colorfilter, fg), cols)

    pairsF = fork(product, identity, identity)
    same = fork(equality, compose(color, first), compose(color, last))
    condV = fork(both, same, fork(vmatching, first, last))
    condH = fork(both, same, fork(hmatching, first, last))
    condE = fork(either, condV, condH)

    filtPairs = compose(lbind(sfilter, condE), pairsF)
    rectIdx = compose(backdrop, fork(combine, first, last))
    colG = compose(color, first)
    canG = compose(rbind(canvas, dims), colG)
    mk = fork(toobject, rectIdx, canG)

    perGroup = compose(merge, compose(lbind(apply, mk), filtPairs))
    P = merge(apply(perGroup, groups))
    O = underpaint(I, P)
    return O
```