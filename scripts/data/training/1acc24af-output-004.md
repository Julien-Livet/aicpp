```python
def dsl1(I):
    top = tophalf(I)
    ones = ofcolor(top, ONE)
    crn = corners(box(ones))
    rays = mapply(rbind(shoot, DOWN), crn)
    cols = merge(rays)
    S = ofcolor(I, FIVE)
    keep = intersection(S, cols)
    base = replace(I, FIVE, TWO)
    O = paint(base, toobject(keep, I))
    return O

def dsl2(I):
    top = tophalf(I)
    ones = ofcolor(top, ONE)
    col = shoot(centerofmass(ones), DOWN)
    fobjs = colorfilter(objects(I, T, F, T), FIVE)
    mind = valmin(fobjs, rbind(manhattan, col))
    near = sfilter(fobjs, matcher(rbind(manhattan, col), mind))
    others = difference(fobjs, near)
    recolored = mapply(lbind(recolor, TWO), others)
    O = paint(I, recolored)
    return O

def dsl3(I):
    fobjs = colorfilter(objects(I, T, F, T), FIVE)
    touch = sfilter(fobjs, rbind(bordering, I))
    others = difference(fobjs, touch)
    recolored = mapply(lbind(recolor, TWO), others)
    O = paint(I, recolored)
    return O

def dsl4(I):
    fobjs = colorfilter(objects(I, T, F, T), FIVE)
    borders = merge(mapply(box, fobjs))
    S = ofcolor(I, FIVE)
    keep = intersection(S, borders)
    base = replace(I, FIVE, TWO)
    O = paint(base, toobject(keep, I))
    return O

def dsl5(I):
    top = tophalf(I)
    ones = ofcolor(top, ONE)
    ray = shoot(urcorner(ones), DOWN)
    fobjs = colorfilter(objects(I, T, F, T), FIVE)
    onray = sfilter(fobjs, matcher(rbind(manhattan, ray), ZERO))
    others = difference(fobjs, onray)
    recolored = mapply(lbind(recolor, TWO), others)
    O = paint(I, recolored)
    return O
```