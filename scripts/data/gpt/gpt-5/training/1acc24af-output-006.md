```python
def dsl1(I):
    S = ofcolor(I, FIVE)
    c = center(S)
    col = shoot(c, DOWN)
    base = replace(I, FIVE, TWO)
    keep = intersection(S, col)
    O = paint(base, toobject(keep, I))
    return O

def dsl2(I):
    S = ofcolor(I, FIVE)
    cands = apply(rbind(shoot, DOWN), S)
    best = argmax(cands, compose(size, rbind(intersection, S)))
    base = replace(I, FIVE, TWO)
    O = paint(base, toobject(intersection(S, best), I))
    return O

def dsl3(I):
    S = ofcolor(I, FIVE)
    j = rightmost(S)
    start = astuple(0, j)
    col = shoot(start, DOWN)
    keep = intersection(S, col)
    base = replace(I, FIVE, TWO)
    O = paint(base, toobject(keep, I))
    return O

def dsl4(I):
    top = tophalf(I)
    ones = ofcolor(top, ONE)
    proj = mapply(rbind(shoot, DOWN), ones)
    S = ofcolor(I, FIVE)
    keep = intersection(S, proj)
    base = replace(I, FIVE, TWO)
    O = paint(base, toobject(keep, I))
    return O

def dsl5(I):
    top = tophalf(I)
    ones_objs = colorfilter(objects(top, T, F, T), ONE)
    centers = apply(centerofmass, ones_objs)
    rays = apply(rbind(shoot, DOWN), centers)
    S = ofcolor(I, FIVE)
    best = argmax(rays, compose(size, rbind(intersection, S)))
    base = replace(I, FIVE, TWO)
    O = paint(base, toobject(intersection(S, best), I))
    return O
```