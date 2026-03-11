```python
def dsl1(I):
    # Remove separators, coarse-grain by factor chosen from palette, then outline each block
    x1 = switch(I, FIVE, ZERO)
    fac = branch(contained(EIGHT, palette(I)), FIVE, THREE)
    x2 = downscale(x1, fac)
    x3 = upscale(x2, fac)
    xs = objects(x3, T, F, T)
    b = mapply(box, xs)
    o = mapply(lbind(toobject, x3), b)
    u = merge(o)
    Z = canvas(ZERO, shape(x3))
    O = paint(Z, u)
    return O

def dsl2(I):
    # Remove separators, compress, coarse-grain by width heuristic, then outline each block
    x1 = replace(I, FIVE, ZERO)
    x2 = compress(x1)
    fac = branch(greater(width(x2), 12), FIVE, THREE)
    x3 = downscale(x2, fac)
    x4 = upscale(x3, fac)
    xs = objects(x4, T, F, T)
    b = mapply(box, xs)
    o = mapply(lbind(toobject, x4), b)
    u = merge(o)
    Z = canvas(ZERO, shape(x4))
    O = paint(Z, u)
    return O

def dsl3(I):
    # Simple: strip separators and outline all remaining objects in-place
    x1 = replace(I, FIVE, ZERO)
    x2 = compress(x1)
    xs = objects(x2, T, F, T)
    b = mapply(box, xs)
    o = mapply(lbind(toobject, x2), b)
    u = merge(o)
    Z = canvas(ZERO, shape(x2))
    O = paint(Z, u)
    return O

def dsl4(I):
    # Map source colors to target palette from bottom half (legend), then build outlined meta-grid
    x0 = replace(I, FIVE, ZERO)
    # source colors (exclude 0 and 5)
    sset = remove(FIVE, remove(ZERO, palette(x0)))
    smin = minimum(sset)
    srem = remove(smin, sset)
    smax = maximum(srem)
    smid = other(srem, smax)
    # target colors from bottom half (exclude 0 and 5)
    bh = bottomhalf(I)
    tset = remove(FIVE, remove(ZERO, palette(bh)))
    tmin = minimum(tset)
    trem = remove(tmin, tset)
    tmax = maximum(trem)
    tmid = other(trem, tmax)
    y1 = replace(x0, smin, tmin)
    y2 = replace(y1, smid, tmid)
    y3 = replace(y2, smax, tmax)
    fac = branch(contained(EIGHT, palette(I)), FIVE, THREE)
    g1 = downscale(y3, fac)
    g2 = upscale(g1, fac)
    xs = objects(g2, T, F, T)
    b = mapply(box, xs)
    o = mapply(lbind(toobject, g2), b)
    u = merge(o)
    Z = canvas(ZERO, shape(g2))
    O = paint(Z, u)
    return O

def dsl5(I):
    # Coarse-grain and use frontiers as outlines
    x1 = switch(I, FIVE, ZERO)
    fac = branch(greater(width(I), 12), FIVE, THREE)
    x2 = downscale(x1, fac)
    x3 = upscale(x2, fac)
    fr = frontiers(x3)
    u = merge(fr)
    Z = canvas(ZERO, shape(x3))
    O = paint(Z, u)
    return O
```