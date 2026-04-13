```python
def dsl1(I):
    # Global: build H/V lines per seed, pair by color, choose nearer endpoints to each seed, fill corner-rect to the crosspoint
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
    hline = fork(connect, compose(ulcorner, hmask), compose(urcorner, hmask))
    vline = fork(connect, compose(ulcorner, vmask), compose(llcorner, vmask))
    ip = fork(intersection, compose(toindices, hline), compose(toindices, vline))

    EH = fork(combine, compose(initset, compose(ulcorner, hmask)), compose(initset, compose(urcorner, hmask)))
    EV = fork(combine, compose(initset, compose(ulcorner, vmask)), compose(initset, compose(llcorner, vmask)))

    bindH = compose(compose(rbind, manhattan), first)
    bindV = compose(compose(rbind, manhattan), last)
    pickH = fork(argmin, EH, bindH)
    pickV = fork(argmin, EV, bindV)

    quad = compose(backdrop, fork(combine, ip, fork(combine, pickH, pickV)))
    rect = fork(recolor, compose(color, first), quad)
    rectobj = merge(apply(rect, pp))
    O = paint(fbase, rectobj)
    return O

def dsl2(I):
    # Object extraction: form colored H/V masks from seeds, pair them, use nearest endpoints to seeds to make rectangles
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
    Hsrc = sfilter(seeds, nonemptyH)
    Vsrc = sfilter(seeds, nonemptyV)

    # recolored endpoint masks (no connect before filtering)
    Hm = apply(fork(recolor, color, hin), Hsrc)
    Vm = apply(fork(recolor, color, vin), Vsrc)

    pairs = product(Hsrc, Vsrc)
    samec = fork(equality, compose(color, first), compose(color, last))
    pp = sfilter(pairs, samec)

    hmask = compose(hin, first)
    vmask = compose(vin, last)
    hline = fork(connect, compose(ulcorner, hmask), compose(urcorner, hmask))
    vline = fork(connect, compose(ulcorner, vmask), compose(llcorner, vmask))
    ip = fork(intersection, compose(toindices, hline), compose(toindices, vline))

    EH = fork(combine, compose(initset, compose(ulcorner, hmask)), compose(initset, compose(urcorner, hmask)))
    EV = fork(combine, compose(initset, compose(ulcorner, vmask)), compose(initset, compose(llcorner, vmask)))

    bindH = compose(compose(rbind, manhattan), first)
    bindV = compose(compose(rbind, manhattan), last)
    pickH = fork(argmin, EH, bindH)
    pickV = fork(argmin, EV, bindV)

    quad = compose(backdrop, fork(combine, ip, fork(combine, pickH, pickV)))
    rect = fork(recolor, compose(color, first), quad)
    rectobj = merge(apply(rect, pp))
    O = paint(fbase, rectobj)
    return O

def dsl3(I):
    # Color filtering on H/V grid: build H/V lines, group by color via seed pool, choose endpoints nearest to pooled seeds
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

    # Build full H/V lines for all qualifying seeds
    hline_seed = fork(connect, compose(ulcorner, hin), compose(urcorner, hin))
    vline_seed = fork(connect, compose(ulcorner, vin), compose(llcorner, vin))
    Hlines = apply(fork(recolor, color, hline_seed), Hs)
    Vlines = apply(fork(recolor, color, vline_seed), Vs)

    pairs = product(Hlines, Vlines)
    samec = fork(equality, compose(color, first), compose(color, last))
    pp = sfilter(pairs, samec)

    # Seed pool by color (for direction bias)
    cf = lbind(colorfilter, seeds)
    pool = compose(merge, compose(cf, compose(color, first)))

    ip = fork(intersection, compose(toindices, first), compose(toindices, last))

    # Endpoints from the H/V line objects
    HE = fork(combine, compose(initset, compose(ulcorner, compose(toindices, first))),
                        compose(initset, compose(urcorner, compose(toindices, first))))
    VE = fork(combine, compose(initset, compose(ulcorner, compose(toindices, last))),
                        compose(initset, compose(llcorner, compose(toindices, last))))

    bindP = compose(compose(rbind, manhattan), pool)
    pickH = fork(argmin, HE, bindP)
    pickV = fork(argmin, VE, bindP)

    quad = compose(backdrop, fork(combine, ip, fork(combine, pickH, pickV)))
    rect = fork(recolor, compose(color, first), quad)
    rectobj = merge(apply(rect, pp))
    O = paint(fbase, rectobj)
    return O

def dsl4(I):
    # Geometric via ray casting: shoot from seeds, build H/V lines on fives, choose nearer endpoints to seeds, fill rectangles
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

    # Intersections of rays with FIVE region
    hproj = compose(rbind(intersection, fidx), fork(combine, sR, sL))
    vproj = compose(rbind(intersection, fidx), fork(combine, sU, sD))

    nonemptyH = compose(positive, compose(size, hproj))
    nonemptyV = compose(positive, compose(size, vproj))
    Hs = sfilter(seeds, nonemptyH)
    Vs = sfilter(seeds, nonemptyV)

    # Build H/V lines by connecting extrema of the projections
    hline = fork(connect, compose(ulcorner, hproj), compose(urcorner, hproj))
    vline = fork(connect, compose(ulcorner, vproj), compose(llcorner, vproj))

    Hp = apply(fork(recolor, color, hline), Hs)
    Vp = apply(fork(recolor, color, vline), Vs)

    pairs = product(Hs, Vs)
    samec = fork(equality, compose(color, first), compose(color, last))
    pp = sfilter(pairs, samec)

    hmask = compose(hproj, first)
    vmask = compose(vproj, last)
    hseg = fork(connect, compose(ulcorner, hmask), compose(urcorner, hmask))
    vseg = fork(connect, compose(ulcorner, vmask), compose(llcorner, vmask))
    ip = fork(intersection, compose(toindices, hseg), compose(toindices, vseg))

    EH = fork(combine, compose(initset, compose(ulcorner, hmask)), compose(initset, compose(urcorner, hmask)))
    EV = fork(combine, compose(initset, compose(ulcorner, vmask)), compose(initset, compose(llcorner, vmask)))

    bindH = compose(compose(rbind, manhattan), first)
    bindV = compose(compose(rbind, manhattan), last)
    pickH = fork(argmin, EH, bindH)
    pickV = fork(argmin, EV, bindV)

    quad = compose(backdrop, fork(combine, ip, fork(combine, pickH, pickV)))
    rect = fork(recolor, compose(color, first), quad)
    rectobj = merge(apply(rect, pp))
    O = paint(fbase, rectobj)
    return O

def dsl5(I):
    # Relational: pair seeds with horizontal/vertical availability, align endpoints nearest to each seed, paint per-color rectangles
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
    hline = fork(connect, compose(ulcorner, hmask), compose(urcorner, hmask))
    vline = fork(connect, compose(ulcorner, vmask), compose(llcorner, vmask))
    ip = fork(intersection, compose(toindices, hline), compose(toindices, vline))

    EH = fork(combine, compose(initset, compose(ulcorner, hmask)), compose(initset, compose(urcorner, hmask)))
    EV = fork(combine, compose(initset, compose(ulcorner, vmask)), compose(initset, compose(llcorner, vmask)))

    bindH = compose(compose(rbind, manhattan), first)
    bindV = compose(compose(rbind, manhattan), last)
    pickH = fork(argmin, EH, bindH)
    pickV = fork(argmin, EV, bindV)

    quad = compose(backdrop, fork(combine, ip, fork(combine, pickH, pickV)))
    rect = fork(recolor, compose(color, first), quad)
    rectobj = merge(apply(rect, pp))
    O = paint(fbase, rectobj)
    return O
```