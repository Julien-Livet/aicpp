```python
def dsl1(I):
    ones = ofcolor(I, ONE)
    vlines = apply(vfrontier, ones)
    twocells = ofcolor(I, TWO)
    comp = chain(size, lbind(intersection, twocells), identity)
    bestline = argmax(vlines, comp)
    J = fill(I, ONE, bestline)
    objs = objects(I, T, F, T)
    twos = colorfilter(objs, TWO)
    sel = sfilter(twos, rbind(vmatching, bestline))
    recol = apply(lbind(recolor, ONE), sel)
    O = paint(J, merge(recol))
    return O

def dsl2(I):
    gridcells = asindices(I)
    anchor = center(gridcells)
    vline = vfrontier(anchor)
    J = fill(I, ONE, vline)
    objs = objects(I, T, F, T)
    twos = colorfilter(objs, TWO)
    sel = sfilter(twos, rbind(vmatching, vline))
    recol = apply(lbind(recolor, ONE), sel)
    O = paint(J, merge(recol))
    return O

def dsl3(I):
    objs = objects(I, T, F, T)
    twos = colorfilter(objs, TWO)
    main2 = argmax(twos, size)
    anchor = center(main2)
    vline = vfrontier(anchor)
    J = fill(I, ONE, vline)
    sel = sfilter(twos, rbind(vmatching, vline))
    recol = apply(lbind(recolor, ONE), sel)
    O = paint(J, merge(recol))
    return O

def dsl4(I):
    ones = ofcolor(I, ONE)
    vlines = apply(vfrontier, ones)
    comp = chain(size, lbind(intersection, ones), identity)
    bestline = argmax(vlines, comp)
    J = fill(I, ONE, bestline)
    objs = objects(I, T, F, T)
    twos = colorfilter(objs, TWO)
    sel = sfilter(twos, rbind(vmatching, bestline))
    recol = apply(lbind(recolor, ONE), sel)
    O = paint(J, merge(recol))
    return O

def dsl5(I):
    ones = ofcolor(I, ONE)
    twos = ofcolor(I, TWO)
    union = combine(ones, twos)
    anchor = centerofmass(union)
    vline = vfrontier(anchor)
    J = fill(I, ONE, vline)
    objs = objects(I, T, F, T)
    twos_objs = colorfilter(objs, TWO)
    sel = sfilter(twos_objs, rbind(vmatching, vline))
    recol = apply(lbind(recolor, ONE), sel)
    O = paint(J, merge(recol))
    return O
```