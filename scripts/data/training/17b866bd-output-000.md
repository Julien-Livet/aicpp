```python
def dsl1(I):
    objs = objects(I, T, F, T)
    eight = colorfilter(objs, EIGHT)
    non8 = difference(objs, eight)
    zeros = colorfilter(objs, ZERO)
    seeds = difference(non8, zeros)
    seeds_idx = mapply(toindices, seeds)
    adj8 = mfilter(eight, lbind(adjacent, seeds_idx))
    seedcolors = apply(color, seeds)
    mc = mostcommon(seedcolors)
    recolobjs = apply(lbind(recolor, mc), adj8)
    recolmerged = merge(recolobjs)
    base = fill(I, ZERO, seeds_idx)
    O = paint(base, recolmerged)
    return O

def dsl2(I):
    objs = objects(I, T, F, T)
    eight = colorfilter(objs, EIGHT)
    non8 = difference(objs, eight)
    zeros = colorfilter(objs, ZERO)
    seeds = difference(non8, zeros)
    pairs = product(seeds, eight)
    cond_h = fork(hmatching, first, last)
    cond_v = fork(vmatching, first, last)
    cond = fork(either, cond_h, cond_v)
    vhpairs = sfilter(pairs, cond)
    recol = apply(fork(recolor, compose(color, first), last), vhpairs)
    recolmerged = merge(recol)
    seeds_idx = mapply(toindices, seeds)
    base = fill(I, ZERO, seeds_idx)
    O = paint(base, recolmerged)
    return O

def dsl3(I):
    objs = objects(I, T, F, T)
    eight = colorfilter(objs, EIGHT)
    non8 = difference(objs, eight)
    zeros = colorfilter(objs, ZERO)
    seeds = difference(non8, zeros)
    seeds_idx = mapply(toindices, seeds)
    O = fill(I, ZERO, seeds_idx)
    return O

def dsl4(I):
    objs = objects(I, T, F, T)
    eight = colorfilter(objs, EIGHT)
    non8 = difference(objs, eight)
    zeros = colorfilter(objs, ZERO)
    seeds = difference(non8, zeros)
    seeds_idx = mapply(toindices, seeds)
    dfunc = lbind(manhattan, seeds_idx)
    nearest8 = argmin(eight, dfunc)
    seedcolors = apply(color, seeds)
    mc = mostcommon(seedcolors)
    recol1 = recolor(mc, nearest8)
    base = fill(I, ZERO, seeds_idx)
    O = paint(base, recol1)
    return O

def dsl5(I):
    objs = objects(I, T, F, T)
    eight = colorfilter(objs, EIGHT)
    non8 = difference(objs, eight)
    zeros = colorfilter(objs, ZERO)
    seeds = difference(non8, zeros)
    seeds_idx = mapply(toindices, seeds)
    adj8 = mfilter(eight, lbind(adjacent, seeds_idx))
    pairs = product(seeds, adj8)
    adjpairs = sfilter(pairs, fork(adjacent, first, last))
    recol = apply(fork(recolor, compose(color, first), last), adjpairs)
    recolmerged = merge(recol)
    base = fill(I, ZERO, seeds_idx)
    O = paint(base, recolmerged)
    return O
```