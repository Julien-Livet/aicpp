```python
def dsl1(I):
    p5 = ofcolor(I, FIVE)
    bb = backdrop(p5)
    c = center(bb)
    v = combine(shoot(c, UP), shoot(c, DOWN))
    h = combine(shoot(c, LEFT), shoot(c, RIGHT))
    axes = combine(v, h)
    mask = intersection(axes, p5)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O

def dsl2(I):
    objs = colorfilter(objects(I, T, F, T), FIVE)
    fV = compose(vfrontier, centerofmass)
    fH = compose(hfrontier, centerofmass)
    vsets = mapply(fV, objs)
    hsets = mapply(fH, objs)
    axes = merge(combine(vsets, hsets))
    mask = intersection(axes, ofcolor(I, FIVE))
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O

def dsl3(I):
    p5 = ofcolor(I, FIVE)
    frs = frontiers(I)
    boundary = intersection(p5, merge(frs))
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, boundary)
    return O

def dsl4(I):
    p5 = ofcolor(I, FIVE)
    ul = ulcorner(p5)
    ur = urcorner(p5)
    ll = llcorner(p5)
    lr = lrcorner(p5)
    d1 = connect(ul, lr)
    d2 = connect(ur, ll)
    mask = intersection(p5, combine(d1, d2))
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O

def dsl5(I):
    p5 = ofcolor(I, FIVE)
    void = delta(p5)
    c = centerofmass(void)
    v = combine(shoot(c, UP), shoot(c, DOWN))
    h = combine(shoot(c, LEFT), shoot(c, RIGHT))
    axes = combine(v, h)
    mask = intersection(axes, p5)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O
```