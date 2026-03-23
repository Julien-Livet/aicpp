```python
def dsl1(I):
    top = tophalf(I)
    ones_objs = colorfilter(objects(top, T, F, T), ONE)
    centers = mapply(centerofmass, ones_objs)
    rays = mapply(rbind(shoot, DOWN), centers)
    S = ofcolor(I, FIVE)
    best = argmax(rays, compose(size, rbind(intersection, S)))
    base = replace(I, FIVE, TWO)
    O = paint(base, toobject(intersection(S, best), I))
    return O

def dsl2(I):
    top = tophalf(I)
    ones_objs = colorfilter(objects(top, T, F, T), ONE)
    boxes = mapply(box, ones_objs)
    crns = mapply(corners, boxes)
    rays = mapply(rbind(shoot, DOWN), crns)
    S = ofcolor(I, FIVE)
    best = argmax(rays, compose(size, rbind(intersection, S)))
    base = replace(I, FIVE, TWO)
    O = paint(base, toobject(intersection(S, best), I))
    return O

def dsl3(I):
    S = ofcolor(I, FIVE)
    borders = box(S)
    keep = intersection(S, borders)
    base = replace(I, FIVE, TWO)
    O = paint(base, toobject(keep, I))
    return O

def dsl4(I):
    top = tophalf(I)
    ones = ofcolor(top, ONE)
    ctr = center(ones)
    col = shoot(ctr, DOWN)
    S = ofcolor(I, FIVE)
    keep = intersection(S, col)
    base = replace(I, FIVE, TWO)
    O = paint(base, toobject(keep, I))
    return O

def dsl5(I):
    S = ofcolor(I, FIVE)
    cands = mapply(rbind(shoot, DOWN), S)
    best = argmax(cands, compose(size, rbind(intersection, S)))
    base = replace(I, FIVE, TWO)
    O = paint(base, toobject(intersection(S, best), I))
    return O
```