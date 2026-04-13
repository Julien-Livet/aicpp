```python
def dsl1(I):
    # Quadrant fill via nearest-corner from pooled color centers using row/col frontiers
    dims = shape(I)
    base = canvas(ZERO, dims)
    fidx = ofcolor(I, FIVE)
    fbase = fill(base, FIVE, fidx)

    objs = objects(I, T, F, T)
    seeds = difference(objs, colorfilter(objs, FIVE))

    c1 = initset(ulcorner(fidx))
    c2 = initset(urcorner(fidx))
    c3 = initset(llcorner(fidx))
    c4 = initset(lrcorner(fidx))
    CORNERS = combine(combine(c1, c2), combine(c3, c4))

    pool = compose(merge, compose(lbind(colorfilter, seeds), color))
    cent = compose(center, pool)

    hr = compose(rbind(intersection, fidx), compose(hfrontier, cent))
    vr = compose(rbind(intersection, fidx), compose(vfrontier, cent))
    ip = fork(intersection, hr, vr)

    compCorner = compose(lbind(rbind, manhattan), compose(initset, cent))
    pickC = compose(lbind(argmin, CORNERS), compCorner)

    quad = compose(backdrop, fork(combine, ip, pickC))
    rect = fork(recolor, color, quad)

    rectobj = merge(apply(rect, seeds))
    O = paint(fbase, rectobj)
    return O

def dsl2(I):
    # Global nearest-corner rectangles from pooled color centers, clipped to the 5-region
    dims = shape(I)
    base = canvas(ZERO, dims)
    fidx = ofcolor(I, FIVE)
    fbase = fill(base, FIVE, fidx)

    objs = objects(I, T, F, T)
    seeds = difference(objs, colorfilter(objs, FIVE))

    c1 = initset(ulcorner(fidx))
    c2 = initset(urcorner(fidx))
    c3 = initset(llcorner(fidx))
    c4 = initset(lrcorner(fidx))
    CORNERS = combine(combine(c1, c2), combine(c3, c4))

    pool = compose(merge, compose(lbind(colorfilter, seeds), color))
    cent = compose(center, pool)

    compCorner = compose(lbind(rbind, manhattan), compose(initset, cent))
    pickC = compose(lbind(argmin, CORNERS), compCorner)

    anchor = compose(initset, cent)
    rawrect = compose(backdrop, fork(combine, anchor, pickC))
    cliprect = compose(rbind(intersection, fidx), rawrect)
    rect = fork(recolor, color, cliprect)

    rectobj = merge(apply(rect, seeds))
    O = paint(fbase, rectobj)
    return O

def dsl3(I):
    # Geometric rays (shoot) to build H/V segments on 5s, then nearest-corner rectangles per color
    dims = shape(I)
    base = canvas(ZERO, dims)
    fidx = ofcolor(I, FIVE)
    fbase = fill(base, FIVE, fidx)

    objs = objects(I, T, F, T)
    seeds = difference(objs, colorfilter(objs, FIVE))

    c1 = initset(ulcorner(fidx))
    c2 = initset(urcorner(fidx))
    c3 = initset(llcorner(fidx))
    c4 = initset(lrcorner(fidx))
    CORNERS = combine(combine(c1, c2), combine(c3, c4))

    pool = compose(merge, compose(lbind(colorfilter, seeds), color))
    cent = compose(center, pool)

    sR = compose(rbind(shoot, RIGHT), cent)
    sL = compose(rbind(shoot, LEFT), cent)
    sU = compose(rbind(shoot, UP), cent)
    sD = compose(rbind(shoot, DOWN), cent)

    hproj = compose(rbind(intersection, fidx), fork(combine, sR, sL))
    vproj = compose(rbind(intersection, fidx), fork(combine, sU, sD))
    ip = fork(intersection, hproj, vproj)

    compCorner = compose(lbind(rbind, manhattan), compose(initset, cent))
    pickC = compose(lbind(argmin, CORNERS), compCorner)

    quad = compose(backdrop, fork(combine, ip, pickC))
    rect = fork(recolor, color, quad)

    rectobj = merge(apply(rect, seeds))
    O = paint(fbase, rectobj)
    return O

def dsl4(I):
    # Object extraction via pooled center-of-mass with H/V frontiers and nearest-corner fill
    dims = shape(I)
    base = canvas(ZERO, dims)
    fidx = ofcolor(I, FIVE)
    fbase = fill(base, FIVE, fidx)

    objs = objects(I, T, F, T)
    seeds = difference(objs, colorfilter(objs, FIVE))

    c1 = initset(ulcorner(fidx))
    c2 = initset(urcorner(fidx))
    c3 = initset(llcorner(fidx))
    c4 = initset(lrcorner(fidx))
    CORNERS = combine(combine(c1, c2), combine(c3, c4))

    pool = compose(merge, compose(lbind(colorfilter, seeds), color))
    cent = compose(centerofmass, pool)

    hr = compose(rbind(intersection, fidx), compose(hfrontier, cent))
    vr = compose(rbind(intersection, fidx), compose(vfrontier, cent))
    ip = fork(intersection, hr, vr)

    compCorner = compose(lbind(rbind, manhattan), compose(initset, cent))
    pickC = compose(lbind(argmin, CORNERS), compCorner)

    quad = compose(backdrop, fork(combine, ip, pickC))
    rect = fork(recolor, color, quad)

    rectobj = merge(apply(rect, seeds))
    O = paint(fbase, rectobj)
    return O

def dsl5(I):
    # Relational nearest-corner rectangles from pooled color centers; rectangle is bbox(cp, corner) ∩ five
    dims = shape(I)
    base = canvas(ZERO, dims)
    fidx = ofcolor(I, FIVE)
    fbase = fill(base, FIVE, fidx)

    objs = objects(I, T, F, T)
    seeds = difference(objs, colorfilter(objs, FIVE))

    c1 = initset(ulcorner(fidx))
    c2 = initset(urcorner(fidx))
    c3 = initset(llcorner(fidx))
    c4 = initset(lrcorner(fidx))
    CORNERS = combine(combine(c1, c2), combine(c3, c4))

    pool = compose(merge, compose(lbind(colorfilter, seeds), color))
    cent = compose(center, pool)

    compCorner = compose(lbind(rbind, manhattan), compose(initset, cent))
    pickC = compose(lbind(argmin, CORNERS), compCorner)

    cp = compose(initset, cent)
    bbox = compose(backdrop, fork(combine, cp, pickC))
    clipped = compose(rbind(intersection, fidx), bbox)
    rect = fork(recolor, color, clipped)

    rectobj = merge(apply(rect, seeds))
    O = paint(fbase, rectobj)
    return O
```