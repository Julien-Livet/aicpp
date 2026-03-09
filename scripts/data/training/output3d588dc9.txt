```python
def dsl1(I):
    objs = objects(I, T, F, T)
    zeros = colorfilter(objs, ZERO)
    others = difference(objs, zeros)
    otherinds = mapply(toindices, others)
    # select the zero object closest to any nonzero object
    sel = argmin(zeros, compose(rbind(manhattan, otherinds), toindices))
    zinds = toindices(sel)
    lbord = intersection(zinds, vfrontier(ulcorner(zinds)))
    rbord = intersection(zinds, vfrontier(urcorner(zinds)))
    # choose the side (left/right border) closer to the nonzero mass
    ldist = manhattan(lbord, otherinds)
    rdist = manhattan(rbord, otherinds)
    side = branch(greater(ldist, rdist), rbord, lbord)
    fardir = branch(equality(side, lbord), RIGHT, LEFT)
    # keep up to three columns inward from the chosen side
    k1 = intersection(zinds, shift(side, fardir))
    k2 = intersection(zinds, shift(k1, fardir))
    k3 = intersection(zinds, shift(k2, fardir))
    keep = combine(k1, combine(k2, k3))
    J = cover(I, sel)
    K = fill(J, SIX, side)
    O = paint(K, recolor(ZERO, keep))
    return O

def dsl2(I):
    objs = objects(I, T, F, T)
    zeros = colorfilter(objs, ZERO)
    others = difference(objs, zeros)
    otherinds = mapply(toindices, others)
    # prefer a zero object that horizontally overlaps any nonzero object; else closest to nonzero
    pref = extract(zeros, lbind(hmatching, otherinds))
    sel = branch(equality(pref, F), argmin(zeros, compose(rbind(manhattan, otherinds), toindices)), pref)
    zinds = toindices(sel)
    lbord = intersection(zinds, vfrontier(ulcorner(zinds)))
    rbord = intersection(zinds, vfrontier(urcorner(zinds)))
    ldist = manhattan(lbord, otherinds)
    rdist = manhattan(rbord, otherinds)
    side = branch(greater(ldist, rdist), rbord, lbord)
    fardir = branch(equality(side, lbord), RIGHT, LEFT)
    k1 = intersection(zinds, shift(side, fardir))
    k2 = intersection(zinds, shift(k1, fardir))
    k3 = intersection(zinds, shift(k2, fardir))
    keep = combine(k1, combine(k2, k3))
    J = cover(I, sel)
    K = fill(J, SIX, side)
    O = paint(K, recolor(ZERO, keep))
    return O

def dsl3(I):
    H = height(I)
    midr = halve(H)
    crow = hfrontier(astuple(midr, 0))
    # widen the central band to three rows (mid-1, mid, mid+1) if possible
    band = combine(shift(crow, UP), combine(crow, shift(crow, DOWN)))
    objs = objects(I, T, F, T)
    zeros = colorfilter(objs, ZERO)
    others = difference(objs, zeros)
    otherinds = mapply(toindices, others)
    # pick zero object intersecting the central band; else nearest to nonzero objects
    zhit = extract(zeros, lbind(hmatching, band))
    sel = branch(equality(zhit, F), argmin(zeros, compose(rbind(manhattan, otherinds), toindices)), zhit)
    zinds = toindices(sel)
    lbord = intersection(zinds, vfrontier(ulcorner(zinds)))
    rbord = intersection(zinds, vfrontier(urcorner(zinds)))
    ldist = manhattan(lbord, otherinds)
    rdist = manhattan(rbord, otherinds)
    side = branch(greater(ldist, rdist), rbord, lbord)
    fardir = branch(equality(side, lbord), RIGHT, LEFT)
    k1 = intersection(zinds, shift(side, fardir))
    k2 = intersection(zinds, shift(k1, fardir))
    k3 = intersection(zinds, shift(k2, fardir))
    keep = combine(k1, combine(k2, k3))
    J = cover(I, sel)
    K = fill(J, SIX, side)
    O = paint(K, recolor(ZERO, keep))
    return O

def dsl4(I):
    objs = objects(I, T, F, T)
    zeros = colorfilter(objs, ZERO)
    others = difference(objs, zeros)
    otherinds = mapply(toindices, others)
    # select the zero object closest to any nonzero object
    sel = argmin(zeros, compose(rbind(manhattan, otherinds), toindices))
    zinds = toindices(sel)
    # side by comparing centers: if nonzero COM is to the right of zero COM -> use right border, else left
    otherobj = toobject(otherinds, I)
    oc = centerofmass(otherobj)
    zc = centerofmass(sel)
    side = branch(greater(subtract(tojvec(last(oc))[1], tojvec(last(zc))[1]), ZERO), intersection(zinds, vfrontier(urcorner(zinds))), intersection(zinds, vfrontier(ulcorner(zinds))))
    fardir = branch(equality(side, intersection(zinds, vfrontier(ulcorner(zinds)))), RIGHT, LEFT)
    k1 = intersection(zinds, shift(side, fardir))
    k2 = intersection(zinds, shift(k1, fardir))
    k3 = intersection(zinds, shift(k2, fardir))
    keep = combine(k1, combine(k2, k3))
    J = cover(I, sel)
    K = fill(J, SIX, side)
    O = paint(K, recolor(ZERO, keep))
    return O

def dsl5(I):
    objs = objects(I, T, F, T)
    zeros = colorfilter(objs, ZERO)
    others = difference(objs, zeros)
    otherinds = mapply(toindices, others)
    # choose the widest zero object by its bounding subgrid width
    compw = compose(width, rbind(subgrid, I))
    sel = argmax(zeros, compw)
    zinds = toindices(sel)
    lbord = intersection(zinds, vfrontier(ulcorner(zinds)))
    rbord = intersection(zinds, vfrontier(urcorner(zinds)))
    ldist = manhattan(lbord, otherinds)
    rdist = manhattan(rbord, otherinds)
    side = branch(greater(ldist, rdist), rbord, lbord)
    fardir = branch(equality(side, lbord), RIGHT, LEFT)
    k1 = intersection(zinds, shift(side, fardir))
    k2 = intersection(zinds, shift(k1, fardir))
    k3 = intersection(zinds, shift(k2, fardir))
    keep = combine(k1, combine(k2, k3))
    J = cover(I, sel)
    K = fill(J, SIX, side)
    O = paint(K, recolor(ZERO, keep))
    return O
```