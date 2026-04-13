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

    sr = rbind(shoot, RIGHT)
    rvec = compose(toivec, uppermost)
    pL = compose(lbind(add, vL), rvec)
    fullrow = fork(recolor, color, compose(sr, pL))
    rows = mapply(fullrow, objs)

    ords = order(objs, uppermost)
    headless = remove(last(ords), ords)
    tailless = remove(first(ords), ords)
    pairs = pair(headless, tailless)

    ra = compose(uppermost, first)
    rb = compose(uppermost, last)
    ca = compose(color, first)
    cb = compose(color, last)
    mid = compose(halve, fork(add, ra, rb))
    mid1 = compose(increment, mid)

    aL = compose(lbind(add, vL), compose(toivec, ra))
    aR = compose(lbind(add, vR), compose(toivec, ra))
    bL = compose(lbind(add, vL), compose(toivec, rb))
    bR = compose(lbind(add, vR), compose(toivec, rb))
    mL = compose(lbind(add, vL), compose(toivec, mid))
    mR = compose(lbind(add, vR), compose(toivec, mid))
    mL1 = compose(lbind(add, vL), compose(toivec, mid1))
    mR1 = compose(lbind(add, vR), compose(toivec, mid1))

    leftUp = fork(recolor, ca, fork(connect, aL, mL))
    leftDn = fork(recolor, cb, fork(connect, mL1, bL))
    rightUp = fork(recolor, ca, fork(connect, aR, mR))
    rightDn = fork(recolor, cb, fork(connect, mR1, bR))
    bands = mapply(fork(combine, fork(combine, leftUp, leftDn), fork(combine, rightUp, rightDn)), pairs)

    topobj = argmin(objs, uppermost)
    botobj = argmax(objs, lowermost)
    H1 = decrement(H)
    TL = astuple(ZERO, jL)
    TR = astuple(ZERO, jR)
    BL = astuple(H1, jL)
    topfull = recolor(color(topobj), shoot(TL, RIGHT))
    botfull = recolor(color(botobj), shoot(BL, RIGHT))

    O = paint(Z, combine(rows, combine(bands, combine(topfull, botfull))))
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

    ords = order(objs, uppermost)
    headless = remove(last(ords), ords)
    tailless = remove(first(ords), ords)
    pairs = pair(headless, tailless)

    ra = compose(uppermost, first)
    rb = compose(uppermost, last)
    ca = compose(color, first)
    cb = compose(color, last)
    mid = compose(halve, fork(add, ra, rb))
    mid1 = compose(increment, mid)

    aL = compose(lbind(add, vL), compose(toivec, ra))
    aR = compose(lbind(add, vR), compose(toivec, ra))
    bL = compose(lbind(add, vL), compose(toivec, rb))
    bR = compose(lbind(add, vR), compose(toivec, rb))
    mL = compose(lbind(add, vL), compose(toivec, mid))
    mR = compose(lbind(add, vR), compose(toivec, mid))
    mL1 = compose(lbind(add, vL), compose(toivec, mid1))
    mR1 = compose(lbind(add, vR), compose(toivec, mid1))

    cross = fork(combine, fork(connect, aL, bR), fork(connect, aR, bL))
    rectarea = compose(backdrop, cross)
    outline = compose(box, rectarea)
    frameA = fork(recolor, ca, fork(combine, fork(connect, aL, aR), fork(combine, fork(connect, aL, mL), fork(connect, aR, mR))))
    frameB = fork(recolor, cb, fork(combine, fork(connect, bL, bR), fork(combine, fork(connect, mL1, bL), fork(connect, mR1, bR))))
    framed = mapply(fork(combine, outline, fork(combine, frameA, frameB)), pairs)

    topobj = argmin(objs, uppermost)
    botobj = argmax(objs, lowermost)
    H1 = decrement(H)
    TL = astuple(ZERO, jL)
    TR = astuple(ZERO, jR)
    BL = astuple(H1, jL)
    BR = astuple(H1, jR)
    topedge = recolor(color(topobj), connect(TL, TR))
    botedge = recolor(color(botobj), connect(BL, BR))

    O = paint(Z, combine(framed, combine(topedge, botedge)))
    return O

def dsl3(I):
    dims = shape(I)
    H = height(I)
    Z = canvas(ZERO, dims)

    idxs = asindices(I)
    jL = leftmost(idxs)
    jR = rightmost(idxs)
    vL = tojvec(jL)
    vR = tojvec(jR)

    P = palette(I)
    colors = remove(ZERO, P)
    getcells = lbind(ofcolor, I)
    patches = apply(getcells, colors)
    ords = order(patches, uppermost)

    sr = rbind(shoot, RIGHT)
    rvec = compose(toivec, uppermost)
    pL = compose(lbind(add, vL), rvec)
    rowfull = fork(recolor, compose(mapply(color, initset), identity), compose(sr, pL))
    rows = mapply(fork(recolor, color, compose(sr, pL)), ords)

    headless = remove(last(ords), ords)
    tailless = remove(first(ords), ords)
    pairs = pair(headless, tailless)

    ra = compose(uppermost, first)
    rb = compose(uppermost, last)
    ca = compose(color, first)
    cb = compose(color, last)
    mid = compose(halve, fork(add, ra, rb))
    mid1 = compose(increment, mid)

    aL = compose(lbind(add, vL), compose(toivec, ra))
    aR = compose(lbind(add, vR), compose(toivec, ra))
    bL = compose(lbind(add, vL), compose(toivec, rb))
    bR = compose(lbind(add, vR), compose(toivec, rb))
    mL = compose(lbind(add, vL), compose(toivec, mid))
    mR = compose(lbind(add, vR), compose(toivec, mid))
    mL1 = compose(lbind(add, vL), compose(toivec, mid1))
    mR1 = compose(lbind(add, vR), compose(toivec, mid1))

    leftUp = fork(recolor, ca, fork(connect, aL, mL))
    leftDn = fork(recolor, cb, fork(connect, mL1, bL))
    rightUp = fork(recolor, ca, fork(connect, aR, mR))
    rightDn = fork(recolor, cb, fork(connect, mR1, bR))
    sides = mapply(fork(combine, fork(combine, leftUp, leftDn), fork(combine, rightUp, rightDn)), pairs)

    topc = color(first(ords))
    botc = color(last(ords))
    H1 = decrement(H)
    TL = astuple(ZERO, jL)
    TR = astuple(ZERO, jR)
    BL = astuple(H1, jL)
    topfull = recolor(topc, shoot(TL, RIGHT))
    botfull = recolor(botc, shoot(BL, RIGHT))

    O = paint(Z, combine(rows, combine(sides, combine(topfull, botfull))))
    return O

def dsl4(I):
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
    anchors = mapply(fork(recolor, color, fork(connect, pL, pR)), objs)

    ords = order(objs, uppermost)
    headless = remove(last(ords), ords)
    tailless = remove(first(ords), ords)
    pairs = pair(headless, tailless)

    ra = compose(uppermost, first)
    rb = compose(uppermost, last)
    ca = compose(color, first)
    cb = compose(color, last)
    mid = compose(halve, fork(add, ra, rb))
    mid1 = compose(increment, mid)

    aL = compose(lbind(add, vL), compose(toivec, ra))
    aR = compose(lbind(add, vR), compose(toivec, ra))
    bL = compose(lbind(add, vL), compose(toivec, rb))
    bR = compose(lbind(add, vR), compose(toivec, rb))
    mL = compose(lbind(add, vL), compose(toivec, mid))
    mR = compose(lbind(add, vR), compose(toivec, mid))
    mL1 = compose(lbind(add, vL), compose(toivec, mid1))
    mR1 = compose(lbind(add, vR), compose(toivec, mid1))

    vsegA = fork(combine, fork(recolor, ca, fork(connect, aL, mL)), fork(recolor, ca, fork(connect, aR, mR)))
    vsegB = fork(combine, fork(recolor, cb, fork(connect, mL1, bL)), fork(recolor, cb, fork(connect, mR1, bR)))
    pillars = mapply(fork(combine, vsegA, vsegB), pairs)

    border = box(asindices(I))
    topobj = argmin(objs, uppermost)
    botobj = argmax(objs, lowermost)
    topborder = recolor(color(topobj), intersection(border, connect(astuple(ZERO, jL), astuple(ZERO, jR))))
    botborder = recolor(color(botobj), intersection(border, connect(astuple(decrement(H), jL), astuple(decrement(H), jR))))

    O = paint(Z, combine(anchors, combine(pillars, combine(topborder, botborder))))
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

    ords = order(objs, uppermost)
    headless = remove(last(ords), ords)
    tailless = remove(first(ords), ords)
    pairs = pair(headless, tailless)

    ra = compose(uppermost, first)
    rb = compose(uppermost, last)
    ca = compose(color, first)
    cb = compose(color, last)
    mid = compose(halve, fork(add, ra, rb))
    mid1 = compose(increment, mid)

    aL = compose(lbind(add, vL), compose(toivec, ra))
    aR = compose(lbind(add, vR), compose(toivec, ra))
    bL = compose(lbind(add, vL), compose(toivec, rb))
    bR = compose(lbind(add, vR), compose(toivec, rb))
    mL = compose(lbind(add, vL), compose(toivec, mid))
    mR = compose(lbind(add, vR), compose(toivec, mid))
    mL1 = compose(lbind(add, vL), compose(toivec, mid1))
    mR1 = compose(lbind(add, vR), compose(toivec, mid1))

    htop = fork(recolor, ca, fork(connect, aL, aR))
    hbot = fork(recolor, cb, fork(connect, bL, bR))
    vleft = fork(combine, fork(recolor, ca, fork(connect, aL, mL)), fork(recolor, cb, fork(connect, mL1, bL)))
    vright = fork(combine, fork(recolor, ca, fork(connect, aR, mR)), fork(recolor, cb, fork(connect, mR1, bR)))
    frames = mapply(fork(combine, fork(combine, htop, hbot), fork(combine, vleft, vright)), pairs)

    rvec = compose(toivec, uppermost)
    pL = compose(lbind(add, vL), rvec)
    pR = compose(lbind(add, vR), rvec)
    spans = mapply(fork(recolor, color, fork(connect, pL, pR)), objs)

    topobj = argmin(objs, uppermost)
    botobj = argmax(objs, lowermost)
    H1 = decrement(H)
    TL = astuple(ZERO, jL)
    TR = astuple(ZERO, jR)
    BL = astuple(H1, jL)
    BR = astuple(H1, jR)
    toprow = recolor(color(topobj), connect(TL, TR))
    botrow = recolor(color(botobj), connect(BL, BR))

    O = underpaint(Z, combine(frames, combine(spans, combine(toprow, botrow))))
    return O
```