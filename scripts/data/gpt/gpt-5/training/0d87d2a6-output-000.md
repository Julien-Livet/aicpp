```python
def dsl1(I):
    ones = ofcolor(I, ONE)
    vparts = apply(vfrontier, ones)
    vline = merge(vparts)
    J = fill(I, ONE, vline)
    objs = objects(I, T, F, T)
    twos = colorfilter(objs, TWO)
    cond = rbind(vmatching, vline)
    sel = sfilter(twos, cond)
    recol = apply(lbind(recolor, ONE), sel)
    union = merge(recol)
    O = paint(J, union)
    return O

def dsl2(I):
    ones = ofcolor(I, ONE)
    objs = objects(I, T, F, T)
    twos = colorfilter(objs, TWO)
    cond = fork(either, rbind(hmatching, ones), rbind(vmatching, ones))
    sel = sfilter(twos, cond)
    recol = apply(lbind(recolor, ONE), sel)
    union = merge(recol)
    O = paint(I, union)
    return O

def dsl3(I):
    O = replace(I, TWO, ONE)
    return O

def dsl4(I):
    ones = ofcolor(I, ONE)
    c = centerofmass(ones)
    vline = vfrontier(c)
    hline = hfrontier(c)
    mask = combine(vline, hline)
    J = fill(I, ONE, mask)
    objs = objects(I, T, F, T)
    twos = colorfilter(objs, TWO)
    cond = fork(either, rbind(hmatching, mask), rbind(vmatching, mask))
    sel = sfilter(twos, cond)
    recol = apply(lbind(recolor, ONE), sel)
    union = merge(recol)
    O = paint(J, union)
    return O

def dsl5(I):
    ones = ofcolor(I, ONE)
    outline = box(ones)
    J = fill(I, ONE, outline)
    objs = objects(I, T, F, T)
    twos = colorfilter(objs, TWO)
    cond = fork(either, rbind(hmatching, outline), rbind(vmatching, outline))
    sel = sfilter(twos, cond)
    recol = apply(lbind(recolor, ONE), sel)
    union = merge(recol)
    O = paint(J, union)
    return O
```