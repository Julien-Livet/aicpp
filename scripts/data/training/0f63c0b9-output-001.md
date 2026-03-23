```python
def dsl1(I):
    dims = shape(I)
    H = height(I)
    Z = canvas(ZERO, dims)
    objs = objects(I, T, F, T)

    idxs = asindices(I)
    jL = leftmost(idxs)
    jR = rightmost(idxs)
    vL = tojvec(jL)
    vR = tojvec(jR)

    rowvec = compose(toivec, uppermost)
    posL = compose(lbind(add, vL), rowvec)
    posR = compose(lbind(add, vR), rowvec)
    rowline = fork(connect, posL, posR)
    rowobj = fork(recolor, color, rowline)
    rowobjs = mapply(rowobj, objs)

    topobj = argmin(objs, uppermost)
    botobj = argmax(objs, lowermost)
    topL = astuple(ZERO, jL)
    topR = astuple(ZERO, jR)
    H1 = decrement(H)
    botL = astuple(H1, jL)
    botR = astuple(H1, jR)
    toprow = recolor(color(topobj), connect(topL, topR))
    botrow = recolor(color(botobj), connect(botL, botR))

    allobjs = combine(rowobjs, combine(toprow, botrow))
    O = paint(Z, allobjs)
    return O

def dsl2(I):
    dims = shape(I)
    H = height(I)
    Z = canvas(ZERO, dims)
    objs = objects(I, T, F, T)

    idxs = asindices(I)
    jL = leftmost(idxs)
    jR = rightmost(idxs)
    vL = tojvec(jL)
    vR = tojvec(jR)

    rvec = compose(toivec, uppermost)
    pL = compose(lbind(add, vL), rvec)
    pR = compose(lbind(add, vR), rvec)
    dotL = fork(connect, pL, pL)
    dotR = fork(connect, pR, pR)
    sides = fork(combine, dotL, dotR)
    sideobjs = mapply(fork(recolor, color, sides), objs)

    topobj = argmin(objs, uppermost)
    botobj = argmax(objs, lowermost)
    topL = astuple(ZERO, jL)
    topR = astuple(ZERO, jR)
    H1 = decrement(H)
    botL = astuple(H1, jL)
    botR = astuple(H1, jR)
    toprow = recolor(color(topobj), connect(topL, topR))
    botrow = recolor(color(botobj), connect(botL, botR))

    O = paint(Z, combine(sideobjs, combine(toprow, botrow)))
    return O

def dsl3(I):
    H = height(I)
    top = tophalf(I)
    bot = bottomhalf(I)
    objs = objects(I, T, F, T)
    topobj = argmin(objs, uppermost)
    botobj = argmax(objs, lowermost)
    ctop = color(topobj)
    cbot = color(botobj)
    topfilled = replace(top, ZERO, ctop)
    botfilled = replace(bot, ZERO, cbot)
    O = vconcat(topfilled, botfilled)
    return O

def dsl4(I):
    dims = shape(I)
    Z = canvas(ZERO, dims)
    frame = box(asindices(I))
    objs = objects(I, T, F, T)
    botobj = argmax(objs, lowermost)
    O = paint(Z, recolor(color(botobj), frame))
    return O

def dsl5(I):
    dims = shape(I)
    H = height(I)
    Z = canvas(ZERO, dims)
    objs = objects(I, T, F, T)

    idxs = asindices(I)
    jL = leftmost(idxs)
    jR = rightmost(idxs)
    vL = tojvec(jL)
    vR = tojvec(jR)

    # full rows at anchors
    rvec = compose(toivec, uppermost)
    pL = compose(lbind(add, vL), rvec)
    pR = compose(lbind(add, vR), rvec)
    rowline = fork(connect, pL, pR)
    rowobj = fork(recolor, color, rowline)
    rowobjs = mapply(rowobj, objs)

    # consecutive pairs of anchors
    ords = order(objs, uppermost)
    headless = remove(last(ords), ords)
    tailless = remove(first(ords), ords)
    pairs = pair(headless, tailless)

    ra = compose(uppermost, first)
    rb = compose(uppermost, last)
    ca = compose(color, first)
    cb = compose(color, last)
    mid = compose(halve, fork(add, ra, rb))

    aL = compose(lbind(add, vL), compose(toivec, ra))
    mL = compose(lbind(add, vL), compose(toivec, mid))
    bL = compose(lbind(add, vL), compose(toivec, rb))
    aR = compose(lbind(add, vR), compose(toivec, ra))
    mR = compose(lbind(add, vR), compose(toivec, mid))
    bR = compose(lbind(add, vR), compose(toivec, rb))

    top2midL = fork(connect, aL, mL)
    mid2botL = fork(connect, compose(lbind(add, vL), compose(toivec, compose(increment, mid))), bL)
    top2midR = fork(connect, aR, mR)
    mid2botR = fork(connect, compose(lbind(add, vR), compose(toivec, compose(increment, mid))), bR)

    segL = fork(combine, fork(recolor, ca, top2midL), fork(recolor, cb, mid2botL))
    segR = fork(combine, fork(recolor, ca, top2midR), fork(recolor, cb, mid2botR))
    segPair = fork(combine, segL, segR)
    borders = mapply(segPair, pairs)

    # top and bottom edge rows by extremes
    topobj = argmin(objs, uppermost)
    botobj = argmax(objs, lowermost)
    topL = astuple(ZERO, jL)
    topR = astuple(ZERO, jR)
    H1 = decrement(H)
    botL = astuple(H1, jL)
    botR = astuple(H1, jR)
    toprow = recolor(color(topobj), connect(topL, topR))
    botrow = recolor(color(botobj), connect(botL, botR))

    allobjs = combine(borders, combine(rowobjs, combine(toprow, botrow)))
    O = paint(Z, allobjs)
    return O
```