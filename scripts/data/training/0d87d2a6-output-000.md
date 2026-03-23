```python
def dsl1(I):
    # Geometric: draw a vertical line from the top 1-anchor and recolor adjacent 2-components to 1
    ones = ofcolor(I, ONE)
    toprow = hfrontier(ORIGIN)
    topanchors = intersection(ones, toprow)
    t = first(topanchors)
    vline = vfrontier(t)
    lineobj = recolor(ONE, vline)
    objs = objects(I, T, F, T)
    twos = colorfilter(objs, TWO)
    isadj = lbind(adjacent, vline)
    touching = sfilter(twos, isadj)
    fills = mapply(lbind(recolor, ONE), touching)
    O = paint(I, combine(lineobj, fills))
    return O

def dsl2(I):
    # Object extraction: recolor the largest 2-object to 1
    objs = objects(I, T, F, T)
    twos = colorfilter(objs, TWO)
    comp = compose(size, toindices)
    biggest = argmax(twos, comp)
    recol = recolor(ONE, biggest)
    O = paint(I, recol)
    return O

def dsl3(I):
    # Color filtering: recolor 2-objects that share any row or any column with a 1
    ones = ofcolor(I, ONE)
    objs = objects(I, T, F, T)
    twos = colorfilter(objs, TWO)
    c1 = lbind(vmatching, ones)
    c2 = lbind(hmatching, ones)
    cond = fork(either, c1, c2)
    sel = sfilter(twos, cond)
    fills = mapply(lbind(recolor, ONE), sel)
    O = paint(I, fills)
    return O

def dsl4(I):
    # Global/Geometric: draw only the vertical line through the top-row 1-anchor
    ones = ofcolor(I, ONE)
    t = first(intersection(ones, hfrontier(ORIGIN)))
    vline = vfrontier(t)
    O = paint(I, recolor(ONE, vline))
    return O

def dsl5(I):
    # Relational/structural: paint all rows/columns that pass through any 1
    ones = ofcolor(I, ONE)
    cols = mapply(vfrontier, ones)
    rows = mapply(hfrontier, ones)
    cross = combine(cols, rows)
    O = paint(I, recolor(ONE, cross))
    return O
```