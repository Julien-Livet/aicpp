```python
def dsl1(I):
    # Choose the 1-object whose bbox projection has the smallest positive overlap with 5s; keep only that overlap as 5
    top = tophalf(I)
    ones = colorfilter(objects(top, T, F, T), ONE)
    perbox = apply(compose(lbind(mapply, rbind(shoot, DOWN)), compose(backdrop, toindices)), ones)
    S = ofcolor(I, FIVE)
    meas = compose(size, rbind(intersection, S))
    cand = mfilter(perbox, compose(positive, meas))
    best = argmin(cand, meas)
    keep = intersection(S, best)
    base = replace(I, FIVE, TWO)
    O = paint(base, toobject(keep, I))
    return O

def dsl2(I):
    # Global: keep 5s only on the vertical frontier through the center-of-mass of all top-half 1s
    P = ofcolor(tophalf(I), ONE)
    col = vfrontier(centerofmass(P))
    keep = intersection(ofcolor(I, FIVE), col)
    O = paint(replace(I, FIVE, TWO), toobject(keep, I))
    return O

def dsl3(I):
    # Geometric: pick the narrowest 1-object and keep 5s under its bbox projection
    top = tophalf(I)
    ones = colorfilter(objects(top, T, F, T), ONE)
    narrow = argmin(ones, compose(width, toindices))
    proj = mapply(rbind(shoot, DOWN), backdrop(toindices(narrow)))
    S = ofcolor(I, FIVE)
    keep = intersection(S, proj)
    O = paint(replace(I, FIVE, TWO), toobject(keep, I))
    return O

def dsl4(I):
    # Relational: per-object center-line; choose the center column whose projection overlaps 5s most
    top = tophalf(I)
    ones = colorfilter(objects(top, T, F, T), ONE)
    centers = apply(compose(center, toindices), ones)
    lines = apply(vfrontier, centers)
    S = ofcolor(I, FIVE)
    best = argmax(lines, compose(size, rbind(intersection, S)))
    keep = intersection(S, best)
    O = paint(replace(I, FIVE, TWO), toobject(keep, I))
    return O

def dsl5(I):
    # Color filtering via global borders of top 1s: keep 5s under leftmost and rightmost 1-columns; others to 2
    P = ofcolor(tophalf(I), ONE)
    lj = leftmost(P)
    rj = rightmost(P)
    L = vfrontier(astuple(ZERO, lj))
    R = vfrontier(astuple(ZERO, rj))
    S = ofcolor(I, FIVE)
    keepL = intersection(S, L)
    keepR = intersection(S, R)
    base = replace(I, FIVE, TWO)
    O = paint(paint(base, toobject(keepL, I)), toobject(keepR, I))
    return O
```