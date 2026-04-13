```python
def dsl1(I):
    # Global edge-based summary: extract frontiers then downscale
    frs = frontiers(I)
    edges = merge(frs)
    base = canvas(ZERO, shape(I))
    edgegrid = paint(base, edges)
    D = downscale(edgegrid, TEN)
    O = trim(D)
    return O

def dsl2(I):
    # Object extraction: keep the smallest object, then downscale
    obs = objects(I, T, F, T)
    o = argmin(obs, size)
    base = canvas(ZERO, shape(I))
    pic = paint(base, o)
    D = downscale(pic, TEN)
    O = trim(D)
    return O

def dsl3(I):
    # Color filtering: keep only the least common color, then downscale
    lc = leastcolor(I)
    inds = ofcolor(I, lc)
    obj = toobject(inds, I)
    base = canvas(ZERO, shape(I))
    pic = paint(base, obj)
    D = downscale(pic, TEN)
    O = trim(D)
    return O

def dsl4(I):
    # Geometric reasoning: intersect with 180-degree rotation, then downscale
    R = rot180(I)
    S = cellwise(I, R, ZERO)
    D = downscale(S, TEN)
    O = trim(D)
    return O

def dsl5(I):
    # Relational reasoning: place a dot at the center of mass of each object, then downscale
    obs = objects(I, T, F, T)
    mkdot = fork(recolor, color, compose(initset, centerofmass))
    dots = merge(apply(mkdot, obs))
    base = canvas(ZERO, shape(I))
    pic = paint(base, dots)
    D = downscale(pic, TEN)
    O = trim(D)
    return O
```