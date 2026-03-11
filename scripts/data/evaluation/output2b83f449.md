```python
def dsl1(I):
    # 7 -> 8; put 6 at centers of 7-runs and one row above and below; keep 3s
    objs = objects(I, T, F, T)
    sev = colorfilter(objs, SEVEN)
    centers = merge(apply(initset, apply(center, sev)))
    up = shift(centers, UP)
    down = shift(centers, DOWN)
    p6 = combine(centers, combine(up, down))
    O0 = replace(I, SEVEN, EIGHT)
    O = fill(O0, SIX, p6)
    return O

def dsl2(I):
    # 7 -> 8; put 6 at centers and extend two rows up and down
    objs = objects(I, T, F, T)
    sev = colorfilter(objs, SEVEN)
    centers = merge(apply(initset, apply(center, sev)))
    up1 = shift(centers, UP)
    up2 = shift(up1, UP)
    dn1 = shift(centers, DOWN)
    dn2 = shift(dn1, DOWN)
    p6 = combine(centers, combine(up1, combine(up2, combine(dn1, dn2))))
    O0 = replace(I, SEVEN, EIGHT)
    O = fill(O0, SIX, p6)
    return O

def dsl3(I):
    # 7 -> 8; vertical shoots from each 7-center but only paint where original is non-zero
    objs = objects(I, T, F, T)
    sev = colorfilter(objs, SEVEN)
    centers = merge(apply(initset, apply(center, sev)))
    upshoots = merge(apply(lbind(shoot, UP), centers))
    downshoots = merge(apply(lbind(shoot, DOWN), centers))
    vcols = combine(upshoots, downshoots)
    nonzero = difference(asindices(I), ofcolor(I, ZERO))
    p6 = intersection(vcols, nonzero)
    O0 = replace(I, SEVEN, EIGHT)
    O = fill(O0, SIX, p6)
    return O

def dsl4(I):
    # 7 -> 8; put 6 at centers, one row up/down, and diagonal neighbors to connect between staggered centers
    objs = objects(I, T, F, T)
    sev = colorfilter(objs, SEVEN)
    centers = merge(apply(initset, apply(center, sev)))
    up = shift(centers, UP)
    down = shift(centers, DOWN)
    ul = shift(centers, UP_LEFT)
    ur = shift(centers, UP_RIGHT)
    dl = shift(centers, DOWN_LEFT)
    dr = shift(centers, DOWN_RIGHT)
    p6 = combine(centers, combine(up, combine(down, combine(ul, combine(ur, combine(dl, dr))))))
    O0 = replace(I, SEVEN, EIGHT)
    O = fill(O0, SIX, p6)
    return O

def dsl5(I):
    # 7 -> 8; put 6 at centers and one row up/down but avoid overwriting original 3s (preserve frame markers)
    objs = objects(I, T, F, T)
    sev = colorfilter(objs, SEVEN)
    centers = merge(apply(initset, apply(center, sev)))
    up = shift(centers, UP)
    down = shift(centers, DOWN)
    rawp = combine(centers, combine(up, down))
    threes = ofcolor(I, THREE)
    p6 = combine(difference(rawp, threes), centers)  # keep centers even if they were 3 (they aren't), skip painting on 3s elsewhere
    O0 = replace(I, SEVEN, EIGHT)
    O = fill(O0, SIX, p6)
    return O
```