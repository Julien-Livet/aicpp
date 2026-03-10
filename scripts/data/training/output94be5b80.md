```python
def dsl1(I):
    # Remove 3-row banner at its first nonzero row; add copies of the largest shape layer above and below
    nz = difference(asindices(I), ofcolor(I, ZERO))
    r0 = uppermost(nz)
    W = width(I)
    lastc = subtract(W, ONE)
    row0 = connect(astuple(r0, 0), astuple(r0, lastc))
    row1 = connect(astuple(add(r0, ONE), 0), astuple(add(r0, ONE), lastc))
    row2 = connect(astuple(add(r0, TWO), 0), astuple(add(r0, TWO), lastc))
    banner = combine(row0, combine(row1, row2))
    O0 = fill(I, ZERO, banner)

    # Banner extremes by left-to-right order
    bannerCrop = crop(I, astuple(r0, 0), astuple(3, W))
    bparts = fgpartition(bannerCrop)
    bsorted = order(bparts, leftmost)
    cL = color(first(bsorted))
    cR = color(last(bsorted))

    # Template and spacing
    objs = objects(O0, T, F, T)
    templ = argmax(objs, size)
    samesize = sizefilter(objs, size(templ))
    topcand = argmin(samesize, uppermost)
    botcand = argmax(samesize, lowermost)
    H = height(templ)

    # Add extremes
    upmask = shift(toindices(topcand), invert(toivec(H)))
    downmask = shift(toindices(botcand), toivec(H))
    O1 = paint(O0, recolor(cL, upmask))
    O2 = paint(O1, recolor(cR, downmask))
    return O2


def dsl2(I):
    # Remove banner; compute vertical spacing from positions of adjacent layers
    nz = difference(asindices(I), ofcolor(I, ZERO))
    r0 = uppermost(nz)
    W = width(I)
    row0 = connect(astuple(r0, 0), astuple(r0, subtract(W, ONE)))
    row1 = connect(astuple(add(r0, ONE), 0), astuple(add(r0, ONE), subtract(W, ONE)))
    row2 = connect(astuple(add(r0, TWO), 0), astuple(add(r0, TWO), subtract(W, ONE)))
    banner = combine(row0, combine(row1, row2))
    O0 = fill(I, ZERO, banner)

    bannerCrop = crop(I, astuple(r0, 0), astuple(3, W))
    bsorted = order(fgpartition(bannerCrop), leftmost)
    cL = color(first(bsorted))
    cR = color(last(bsorted))

    objs = objects(O0, T, F, T)
    templ = argmax(objs, size)
    samesize = sizefilter(objs, size(templ))
    topcand = argmin(samesize, uppermost)
    botcand = argmax(samesize, lowermost)
    # Spacing as delta of top rows between layers
    H = subtract(uppermost(botcand), uppermost(topcand))

    upmask = shift(toindices(topcand), invert(toivec(H)))
    downmask = shift(toindices(botcand), toivec(H))
    O1 = paint(O0, recolor(cL, upmask))
    O2 = paint(O1, recolor(cR, downmask))
    return O2


def dsl3(I):
    # Remove banner; add only missing extremes (skip if already present at edges)
    nz = difference(asindices(I), ofcolor(I, ZERO))
    r0 = uppermost(nz)
    W = width(I)
    row0 = connect(astuple(r0, 0), astuple(r0, subtract(W, ONE)))
    row1 = connect(astuple(add(r0, ONE), 0), astuple(add(r0, ONE), subtract(W, ONE)))
    row2 = connect(astuple(add(r0, TWO), 0), astuple(add(r0, TWO), subtract(W, ONE)))
    banner = combine(row0, combine(row1, row2))
    O0 = fill(I, ZERO, banner)

    bannerCrop = crop(I, astuple(r0, 0), astuple(3, W))
    bsorted = order(fgpartition(bannerCrop), leftmost)
    cL = color(first(bsorted))
    cR = color(last(bsorted))

    objs = objects(O0, T, F, T)
    templ = argmax(objs, size)
    samesize = sizefilter(objs, size(templ))
    topcand = argmin(samesize, uppermost)
    botcand = argmax(samesize, lowermost)
    H = height(templ)

    upmask = shift(toindices(topcand), invert(toivec(H)))
    downmask = shift(toindices(botcand), toivec(H))
    upobj = recolor(cL, upmask)
    downobj = recolor(cR, downmask)

    # Conditionally add extremes if not already the edge colors
    O1 = branch(equality(color(topcand), cL), O0, paint(O0, upobj))
    O2 = branch(equality(color(botcand), cR), O1, paint(O1, downobj))
    return O2


def dsl4(I):
    # Remove banner; for 4-color banner normalize middle layers to match banner inner colors; add extremes conditionally
    nz = difference(asindices(I), ofcolor(I, ZERO))
    r0 = uppermost(nz)
    W = width(I)
    lastc = subtract(W, ONE)
    row0 = connect(astuple(r0, 0), astuple(r0, lastc))
    row1 = connect(astuple(add(r0, ONE), 0), astuple(add(r0, ONE), lastc))
    row2 = connect(astuple(add(r0, TWO), 0), astuple(add(r0, TWO), lastc))
    banner = combine(row0, combine(row1, row2))
    O0 = fill(I, ZERO, banner)

    bannerCrop = crop(I, astuple(r0, 0), astuple(3, W))
    bsorted = order(fgpartition(bannerCrop), leftmost)
    leftB = first(bsorted)
    rightB = last(bsorted)
    tmp = remove(leftB, bsorted)
    mid = remove(rightB, tmp)
    cL = color(leftB)
    cR = color(rightB)
    cML = color(first(mid)) if contained(first(mid), mid) else cL
    cMR = color(last(mid)) if contained(last(mid), mid) else cR

    objs = objects(O0, T, F, T)
    templ = argmax(objs, size)
    samesize = sizefilter(objs, size(templ))
    topcand = argmin(samesize, uppermost)
    botcand = argmax(samesize, lowermost)
    H = height(templ)

    # Optional recolor middle layers for 4-color case
    Oa = branch(equality(size(bsorted), FOUR),
                paint(paint(O0, recolor(cML, toindices(topcand))),
                      recolor(cMR, toindices(botcand))),
                O0)

    upmask = shift(toindices(topcand), invert(toivec(H)))
    downmask = shift(toindices(botcand), toivec(H))
    upobj = recolor(cL, upmask)
    downobj = recolor(cR, downmask)

    Ob = branch(equality(color(topcand), cL), Oa, paint(Oa, upobj))
    Oc = branch(equality(color(botcand), cR), Ob, paint(Ob, downobj))
    return Oc


def dsl5(I):
    # Remove banner; derive extremes; compute spacing from centers; add extremes
    nz = difference(asindices(I), ofcolor(I, ZERO))
    r0 = uppermost(nz)
    W = width(I)
    row0 = connect(astuple(r0, 0), astuple(r0, subtract(W, ONE)))
    row1 = connect(astuple(add(r0, ONE), 0), astuple(add(r0, ONE), subtract(W, ONE)))
    row2 = connect(astuple(add(r0, TWO), 0), astuple(add(r0, TWO), subtract(W, ONE)))
    banner = combine(row0, combine(row1, row2))
    O0 = fill(I, ZERO, banner)

    bsorted = order(fgpartition(crop(I, astuple(r0, 0), astuple(3, W))), leftmost)
    cL = color(first(bsorted))
    cR = color(last(bsorted))

    objs = objects(O0, T, F, T)
    templ = argmax(objs, size)
    samesize = sizefilter(objs, size(templ))
    topcand = argmin(samesize, uppermost)
    botcand = argmax(samesize, lowermost)

    # Spacing from centers (robust to slight thickness variations)
    ct = center(topcand)
    cb = center(botcand)
    H = subtract(first(cb), first(ct))

    upmask = shift(toindices(topcand), invert(toivec(H)))
    downmask = shift(toindices(botcand), toivec(H))
    O1 = paint(O0, recolor(cL, upmask))
    O2 = paint(O1, recolor(cR, downmask))
    return O2
```