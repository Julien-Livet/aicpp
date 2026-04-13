```python
def dsl1(I):
    top = tophalf(I)
    ones = ofcolor(top, ONE)
    edge = box(ones)
    rays = mapply(rbind(shoot, DOWN), edge)
    cols = merge(rays)
    S = ofcolor(I, FIVE)
    keep = intersection(S, cols)
    base = replace(I, FIVE, TWO)
    O = paint(base, toobject(keep, I))
    return O

def dsl2(I):
    objs = objects(I, T, F, T)
    fives = colorfilter(objs, FIVE)
    keep = argmax(fives, rightmost)
    others = remove(keep, fives)
    recolored = mapply(lbind(recolor, TWO), others)
    O = paint(I, recolored)
    return O

def dsl3(I):
    top = tophalf(I)
    ones = ofcolor(top, ONE)
    cols = merge(mapply(rbind(shoot, DOWN), ones))
    fobjs = colorfilter(objects(I, T, F, T), FIVE)
    keep = argmin(fobjs, rbind(manhattan, cols))
    others = remove(keep, fobjs)
    recolored = mapply(lbind(recolor, TWO), others)
    O = paint(I, recolored)
    return O

def dsl4(I):
    fobjs = colorfilter(objects(I, T, F, T), FIVE)
    bordersets = mapply(fork(intersection, toindices, box), fobjs)
    border = merge(bordersets)
    base = replace(I, FIVE, TWO)
    O = fill(base, FIVE, border)
    return O

def dsl5(I):
    fobjs = colorfilter(objects(I, T, F, T), FIVE)
    touching = sfilter(fobjs, rbind(bordering, I))
    keep = merge(mapply(toindices, touching))
    base = replace(I, FIVE, TWO)
    O = fill(base, FIVE, keep)
    return O
```