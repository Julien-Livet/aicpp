```python
def dsl1(I):
    fg = difference(asindices(I), ofcolor(I, ZERO))
    C = centerofmass(fg)
    objs = objects(I, T, F, T)
    f = lambda o: shift(o, multiply(TWO, sign(subtract(C, center(o)))))
    shifted = apply(f, objs)
    Sobj = merge(shifted)
    G1 = underpaint(I, Sobj)
    Sp = toindices(Sobj)
    conns = prapply(connect, Sp, Sp)
    lines3 = sizefilter(conns, 3)
    diagcond = fork(both, compose(flip, hline), compose(flip, vline))
    diaglines = sfilter(lines3, diagcond)
    dline = first(diaglines)
    O = underfill(G1, FIVE, dline)
    return O

def dsl2(I):
    fg = difference(asindices(I), ofcolor(I, ZERO))
    C = centerofmass(fg)
    Cpatch = initset(C)
    objs = objects(I, T, F, T)
    gdir = lambda o: gravitate(toindices(o), Cpatch)
    f = lambda o: shift(o, multiply(TWO, gdir(o)))
    shifted = apply(f, objs)
    Sobj = merge(shifted)
    G1 = underpaint(I, Sobj)
    Sp = toindices(Sobj)
    conns = prapply(connect, Sp, Sp)
    lines3 = sizefilter(conns, 3)
    diagcond = fork(both, compose(flip, hline), compose(flip, vline))
    dline = first(sfilter(lines3, diagcond))
    O = underfill(G1, FIVE, dline)
    return O

def dsl3(I):
    objs = objects(I, T, F, T)
    P = merge(objs)
    C = centerofmass(P)
    f = lambda o: shift(o, multiply(TWO, sign(subtract(C, center(o)))))
    shifted = apply(f, objs)
    Sobj = merge(shifted)
    G1 = underpaint(I, Sobj)
    centers = apply(center, shifted)
    conns = prapply(connect, centers, centers)
    lines3 = sizefilter(conns, 3)
    diagcond = fork(both, compose(flip, hline), compose(flip, vline))
    dline = first(sfilter(lines3, diagcond))
    mid = centerofmass(dline)
    O = fill(G1, FIVE, initset(mid))
    return O

def dsl4(I):
    objs = objects(I, T, F, T)
    P = merge(objs)
    C = centerofmass(P)
    # shift all objects two steps toward centroid
    base_shift = lambda o: shift(o, multiply(TWO, sign(subtract(C, center(o)))))
    shifted_all = apply(base_shift, objs)
    Sobj = merge(shifted_all)
    G1 = underpaint(I, Sobj)
    # also derive the diagonal pair from originals and reinforce midpoint
    pts = apply(center, objs)
    conns0 = prapply(connect, pts, pts)
    lines3_0 = sizefilter(conns0, 3)
    diagcond = fork(both, compose(flip, hline), compose(flip, vline))
    dline0 = first(sfilter(lines3_0, diagcond))
    O = underfill(G1, FIVE, dline0)
    return O

def dsl5(I):
    fg = difference(asindices(I), ofcolor(I, ZERO))
    C = centerofmass(fg)
    objs = objects(I, T, F, T)
    f = lambda o: shift(o, multiply(TWO, sign(subtract(C, center(o)))))
    shifted = apply(f, objs)
    Sobj = merge(shifted)
    G1 = underpaint(I, Sobj)
    Sp = toindices(Sobj)
    crn = corners(Sp)
    extremals = intersection(crn, Sp)
    conns = prapply(connect, extremals, extremals)
    lines3 = sizefilter(conns, 3)
    diagcond = fork(both, compose(flip, hline), compose(flip, vline))
    dline = first(sfilter(lines3, diagcond))
    O = underfill(G1, FIVE, dline)
    return O
```