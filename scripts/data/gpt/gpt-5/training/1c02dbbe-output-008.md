```python
def dsl1(I):
    # Global corners + pooled color anchors: for each color pool, take row/col through its center, pick nearest box corner, fill that corner-rectangle
    dims = shape(I)
    base = canvas(ZERO, dims)
    fidx = ofcolor(I, FIVE)
    fbase = fill(base, FIVE, fidx)

    objs = objects(I, T, F, T)
    seeds = difference(objs, colorfilter(objs, FIVE))

    # Corners of the 5-region bounding box as a container of singleton patches
    c1 = initset(initset(ulcorner(fidx)))
    c2 = initset(initset(urcorner(fidx)))
    c3 = initset(initset(llcorner(fidx)))
    c4 = initset(initset(lrcorner(fidx)))
    CORNERS = combine(combine(c1, c2), combine(c3, c4))

    pool = compose(merge, compose(lbind(colorfilter, seeds), color))
    hproj = compose(rbind(intersection, fidx), compose(hfrontier, compose(center, pool)))
    vproj = compose(rbind(intersection, fidx), compose(vfrontier, compose(center, pool)))
    ip = fork(intersection, hproj, vproj)

    fix = compose(initset, compose(center, pool))
    compCorner = compose(lbind(rbind, manhattan), fix)
    pickC = compose(lbind(argmin, CORNERS), compCorner)
    eC = compose(merge, pickC)

    quad = compose(backdrop, fork(combine, ip, eC))
    rect = fork(recolor, color, quad)

    rectobj = merge(apply(rect, seeds))
    O = paint(fbase, rectobj)
    return O

def dsl2(I):
    # Object extraction via frontiers with H/V pairing: pick nearest endpoints to respective seeds; fill rectangles
    dims = shape(I)
    base = canvas(ZERO, dims)
    fidx = ofcolor(I, FIVE)
    fbase = fill(base, FIVE, fidx)

    objs = objects(I, T, F, T)
    seeds = difference(objs, colorfilter(objs, FIVE))

    hin = compose(rbind(intersection, fidx), compose(hfrontier, center))
    vin = compose(rbind(intersection, fidx), compose(vfrontier, center))

    nonemptyH = compose(positive, compose(size, hin))
    nonemptyV = compose(positive, compose(size, vin))
    Hs = sfilter(seeds, nonemptyH)
    Vs = sfilter(seeds, nonemptyV)

    pairs = product(Hs, Vs)
    samec = fork(equality, compose(color, first), compose(color, last))
    pp = sfilter(pairs, samec)

    hmask = compose(hin, first)
    vmask = compose(vin, last)

    EH = fork(combine,
              compose(initset, compose(initset, compose(ulcorner, hmask))),
              compose(initset, compose(initset, compose(urcorner, hmask))))
    EV = fork(combine,
              compose(initset, compose(initset, compose(ulcorner, vmask))),
              compose(initset, compose(initset, compose(llcorner, vmask))))

    bindH = compose(lbind(rbind, manhattan), compose(initset, compose(center, first)))
    bindV = compose(lbind(rbind, manhattan), compose(initset, compose(center, last)))
    pickH = fork(argmin, EH, bindH)
    pickV = fork(argmin, EV, bindV)
    eH = compose(merge, pickH)
    eV = compose(merge, pickV)

    ip = fork(intersection, hmask, vmask)
    quad = compose(backdrop, fork(combine, ip, fork(combine, eH, eV)))
    rect = fork(recolor, compose(color, first), quad)

    rectobj = merge(apply(rect, pp))
    O = paint(fbase, rectobj)
    return O

def dsl3(I):
    # Geometric rays: shoot from seeds to get H/V segments on fives, pair by color, pick nearer endpoints, fill rectangles
    dims = shape(I)
    base = canvas(ZERO, dims)
    fidx = ofcolor(I, FIVE)
    fbase = fill(base, FIVE, fidx)

    objs = objects(I, T, F, T)
    seeds = difference(objs, colorfilter(objs, FIVE))

    sR = compose(rbind(shoot, RIGHT), center)
    sL = compose(rbind(shoot, LEFT), center)
    sU = compose(rbind(shoot, UP), center)
    sD = compose(rbind(shoot, DOWN), center)

    hproj = compose(rbind(intersection, fidx), fork(combine, sR, sL))
    vproj = compose(rbind(intersection, fidx), fork(combine, sU, sD))

    nonemptyH = compose(positive, compose(size, hproj))
    nonemptyV = compose(positive, compose(size, vproj))
    Hs = sfilter(seeds, nonemptyH)
    Vs = sfilter(seeds, nonemptyV)

    pairs = product(Hs, Vs)
    samec = fork(equality, compose(color, first), compose(color, last))
    pp = sfilter(pairs, samec)

    hmask = compose(hproj, first)
    vmask = compose(vproj, last)

    EH = fork(combine,
              compose(initset, compose(initset, compose(ulcorner, hmask))),
              compose(initset, compose(initset, compose(urcorner, hmask))))
    EV = fork(combine,
              compose(initset, compose(initset, compose(ulcorner, vmask))),
              compose(initset, compose(initset, compose(llcorner, vmask))))

    bindH = compose(lbind(rbind, manhattan), compose(initset, compose(center, first)))
    bindV = compose(lbind(rbind, manhattan), compose(initset, compose(center, last)))
    pickH = fork(argmin, EH, bindH)
    pickV = fork(argmin, EV, bindV)
    eH = compose(merge, pickH)
    eV = compose(merge, pickV)

    ip = fork(intersection, hmask, vmask)
    quad = compose(backdrop, fork(combine, ip, fork(combine, eH, eV)))
    rect = fork(recolor, compose(color, first), quad)

    rectobj = merge(apply(rect, pp))
    O = paint(fbase, rectobj)
    return O

def dsl4(I):
    # Relational nearest pairing: each H-seed selects nearest V-seed of same color; use their projections to build rectangles
    dims = shape(I)
    base = canvas(ZERO, dims)
    fidx = ofcolor(I, FIVE)
    fbase = fill(base, FIVE, fidx)

    objs = objects(I, T, F, T)
    seeds = difference(objs, colorfilter(objs, FIVE))

    hin = compose(rbind(intersection, fidx), compose(hfrontier, center))
    vin = compose(rbind(intersection, fidx), compose(vfrontier, center))

    nonemptyH = compose(positive, compose(size, hin))
    nonemptyV = compose(positive, compose(size, vin))
    Hs = sfilter(seeds, nonemptyH)
    Vs = sfilter(seeds, nonemptyV)

    Vsame = compose(lbind(colorfilter, Vs), color)
    d2h = compose(lbind(rbind, manhattan), compose(initset, center))
    nearestV = fork(argmin, Vsame, d2h)

    hmaskS = hin
    vmaskS = compose(vin, nearestV)

    EH = fork(combine,
              compose(initset, compose(initset, compose(ulcorner, hmaskS))),
              compose(initset, compose(initset, compose(urcorner, hmaskS))))
    EV = fork(combine,
              compose(initset, compose(initset, compose(ulcorner, vmaskS))),
              compose(initset, compose(initset, compose(llcorner, vmaskS))))

    bindH = compose(lbind(rbind, manhattan), compose(initset, center))
    bindV = compose(lbind(rbind, manhattan), compose(initset, compose(center, nearestV)))
    pickH = fork(argmin, EH, bindH)
    pickV = fork(argmin, EV, bindV)
    eH = compose(merge, pickH)
    eV = compose(merge, pickV)

    ip = fork(intersection, hmaskS, vmaskS)
    quad = compose(backdrop, fork(combine, ip, fork(combine, eH, eV)))
    rect = fork(recolor, color, quad)

    rectobj = merge(apply(rect, Hs))
    O = paint(fbase, rectobj)
    return O

def dsl5(I):
    # Color-filtered pooled anchors on box corners: per color pool choose nearest box corner and use pool's row/col to form rectangle
    dims = shape(I)
    base = canvas(ZERO, dims)
    fidx = ofcolor(I, FIVE)
    fbase = fill(base, FIVE, fidx)

    objs = objects(I, T, F, T)
    seeds = difference(objs, colorfilter(objs, FIVE))

    # Corner set of the 5-region
    k1 = initset(initset(ulcorner(fidx)))
    k2 = initset(initset(urcorner(fidx)))
    k3 = initset(initset(llcorner(fidx)))
    k4 = initset(initset(lrcorner(fidx)))
    K = combine(combine(k1, k2), combine(k3, k4))

    pool = compose(merge, compose(lbind(colorfilter, seeds), color))
    rowseg = compose(rbind(intersection, fidx), compose(hfrontier, compose(center, pool)))
    colseg = compose(rbind(intersection, fidx), compose(vfrontier, compose(center, pool)))
    cross = fork(intersection, rowseg, colseg)

    fixp = compose(initset, compose(center, pool))
    compK = compose(lbind(rbind, manhattan), fixp)
    pickK = compose(lbind(argmin, K), compK)
    eK = compose(merge, pickK)

    tile = compose(backdrop, fork(combine, cross, eK))
    rect = fork(recolor, color, tile)

    rectobj = merge(apply(rect, seeds))
    O = paint(fbase, rectobj)
    return O
```