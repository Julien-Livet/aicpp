```python
def dsl1(I):
    # Relational on frontiers: pair horizontal/vertical seeds of same color, choose nearer endpoints, fill rectangle to their crosspoint
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

    EH = fork(combine, compose(initset, compose(ulcorner, hmask)),
                        compose(initset, compose(urcorner, hmask)))
    EV = fork(combine, compose(initset, compose(ulcorner, vmask)),
                        compose(initset, compose(llcorner, vmask)))

    bindH = compose(lbind(rbind, manhattan), compose(initset, compose(center, first)))
    bindV = compose(lbind(rbind, manhattan), compose(initset, compose(center, last)))
    pickH = fork(argmin, EH, bindH)
    pickV = fork(argmin, EV, bindV)

    ip = fork(intersection, hmask, vmask)
    quad = compose(backdrop, fork(combine, ip, fork(combine, pickH, pickV)))
    rect = fork(recolor, compose(color, first), quad)

    rectobj = merge(apply(rect, pp))
    O = paint(fbase, rectobj)
    return O

def dsl2(I):
    # Object extraction via rays: shoot from seeds to get H/V segments on fives, pair by color, pick nearer endpoints, fill rectangles
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

    EH = fork(combine, compose(initset, compose(ulcorner, hmask)),
                        compose(initset, compose(urcorner, hmask)))
    EV = fork(combine, compose(initset, compose(ulcorner, vmask)),
                        compose(initset, compose(llcorner, vmask)))

    bindH = compose(lbind(rbind, manhattan), compose(initset, compose(center, first)))
    bindV = compose(lbind(rbind, manhattan), compose(initset, compose(center, last)))
    pickH = fork(argmin, EH, bindH)
    pickV = fork(argmin, EV, bindV)

    ip = fork(intersection, hmask, vmask)
    quad = compose(backdrop, fork(combine, ip, fork(combine, pickH, pickV)))
    rect = fork(recolor, compose(color, first), quad)

    rectobj = merge(apply(rect, pp))
    O = paint(fbase, rectobj)
    return O

def dsl3(I):
    # Color filtering with pooled anchors: choose endpoints nearest to pooled same-color seeds
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

    EH = fork(combine, compose(initset, compose(ulcorner, hmask)),
                        compose(initset, compose(urcorner, hmask)))
    EV = fork(combine, compose(initset, compose(ulcorner, vmask)),
                        compose(initset, compose(llcorner, vmask)))

    cf = lbind(colorfilter, seeds)
    pool = compose(merge, compose(cf, compose(color, first)))

    bindP = compose(lbind(rbind, manhattan), pool)
    pickH = fork(argmin, EH, bindP)
    pickV = fork(argmin, EV, bindP)

    ip = fork(intersection, hmask, vmask)
    quad = compose(backdrop, fork(combine, ip, fork(combine, pickH, pickV)))
    rect = fork(recolor, compose(color, first), quad)

    rectobj = merge(apply(rect, pp))
    O = paint(fbase, rectobj)
    return O

def dsl4(I):
    # Geometric rays + endpoints: rays from seeds define H/V segments on 5s; pick endpoints closer to seeds; fill rectangles
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

    Hseg = compose(rbind(intersection, fidx), fork(combine, sR, sL))
    Vseg = compose(rbind(intersection, fidx), fork(combine, sU, sD))

    nonemptyH = compose(positive, compose(size, Hseg))
    nonemptyV = compose(positive, compose(size, Vseg))
    Hs = sfilter(seeds, nonemptyH)
    Vs = sfilter(seeds, nonemptyV)

    pairs = product(Hs, Vs)
    samec = fork(equality, compose(color, first), compose(color, last))
    pp = sfilter(pairs, samec)

    hmask = compose(Hseg, first)
    vmask = compose(Vseg, last)

    EH = fork(combine, compose(initset, compose(ulcorner, hmask)),
                        compose(initset, compose(urcorner, hmask)))
    EV = fork(combine, compose(initset, compose(ulcorner, vmask)),
                        compose(initset, compose(llcorner, vmask)))

    bindH = compose(lbind(rbind, manhattan), compose(initset, compose(center, first)))
    bindV = compose(lbind(rbind, manhattan), compose(initset, compose(center, last)))
    pickH = fork(argmin, EH, bindH)
    pickV = fork(argmin, EV, bindV)

    ip = fork(intersection, hmask, vmask)
    quad = compose(backdrop, fork(combine, ip, fork(combine, pickH, pickV)))
    rect = fork(recolor, compose(color, first), quad)

    rectobj = merge(apply(rect, pp))
    O = paint(fbase, rectobj)
    return O

def dsl5(I):
    # Relational nearest pairing: for each horizontal seed pick nearest vertical seed of same color, then build its rectangle
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

    EH = fork(combine, compose(initset, compose(ulcorner, hmaskS)),
                        compose(initset, compose(urcorner, hmaskS)))
    EV = fork(combine, compose(initset, compose(ulcorner, vmaskS)),
                        compose(initset, compose(llcorner, vmaskS)))

    bindH = compose(lbind(rbind, manhattan), compose(initset, center))
    bindV = compose(lbind(rbind, manhattan), compose(initset, compose(center, nearestV)))
    pickH = fork(argmin, EH, bindH)
    pickV = fork(argmin, EV, bindV)

    ip = fork(intersection, hmaskS, vmaskS)
    quad = compose(backdrop, fork(combine, ip, fork(combine, pickH, pickV)))
    rect = fork(recolor, color, quad)

    rectobj = merge(apply(rect, Hs))
    O = paint(fbase, rectobj)
    return O
```