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
    objs = objects(I, T, F, T)
    ones_objs = colorfilter(objs, ONE)
    cols = apply(rightmost, ones_objs)
    majcol = mostcommon(cols)
    sel = sfilter(ones_objs, matcher(rightmost, majcol))
    anchor = ulcorner(first(sel))
    vline = vfrontier(anchor)
    J = fill(I, ONE, vline)
    twos = colorfilter(objs, TWO)
    sel2 = sfilter(twos, rbind(vmatching, vline))
    recol = apply(lbind(recolor, ONE), sel2)
    O = paint(J, merge(recol))
    return O

def dsl3(I):
    ones = ofcolor(I, ONE)
    anchor = centerofmass(ones)
    vline = vfrontier(anchor)
    J = fill(I, ONE, vline)
    objs = objects(I, T, F, T)
    twos = colorfilter(objs, TWO)
    sel = sfilter(twos, rbind(vmatching, vline))
    recol = apply(lbind(recolor, ONE), sel)
    O = paint(J, merge(recol))
    return O

def dsl4(I):
    ones = ofcolor(I, ONE)
    hrows = merge(apply(hfrontier, ones))
    twocells = ofcolor(I, TWO)
    focus = intersection(twocells, hrows)
    anchor = centerofmass(focus)
    vline = vfrontier(anchor)
    J = fill(I, ONE, vline)
    objs = objects(I, T, F, T)
    twos = colorfilter(objs, TWO)
    sel = sfilter(twos, rbind(vmatching, vline))
    recol = apply(lbind(recolor, ONE), sel)
    O = paint(J, merge(recol))
    return O

def dsl5(I):
    objs = objects(I, T, F, T)
    ones_objs = colorfilter(objs, ONE)
    twos_objs = colorfilter(objs, TWO)
    twos_union = merge(twos_objs)
    comp = rbind(manhattan, twos_union)
    nearest_one = argmin(ones_objs, comp)
    anchor = ulcorner(nearest_one)
    vline = vfrontier(anchor)
    J = fill(I, ONE, vline)
    sel = sfilter(twos_objs, rbind(vmatching, vline))
    recol = apply(lbind(recolor, ONE), sel)
    O = paint(J, merge(recol))
    return O
```