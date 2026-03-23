```python
def dsl1(I):
    p5 = ofcolor(I, FIVE)
    vcore = intersection(p5, vmirror(p5))
    hcore = intersection(p5, hmirror(p5))
    mask = merge(combine(vcore, hcore))
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O

def dsl2(I):
    objs = colorfilter(objects(I, T, F, T), FIVE)
    centers = mapply(centerofmass, objs)
    up = mapply(rbind(shoot, UP), centers)
    down = mapply(rbind(shoot, DOWN), centers)
    left = mapply(rbind(shoot, LEFT), centers)
    right = mapply(rbind(shoot, RIGHT), centers)
    axes = merge(combine(merge(combine(up, down)), merge(combine(left, right))))
    p5 = ofcolor(I, FIVE)
    mask = intersection(axes, p5)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O

def dsl3(I):
    p5 = ofcolor(I, FIVE)
    sl = shift(p5, LEFT)
    sr = shift(p5, RIGHT)
    su = shift(p5, UP)
    sd = shift(p5, DOWN)
    hcore = intersection(p5, intersection(sl, sr))
    vcore = intersection(p5, intersection(su, sd))
    mask = merge(combine(hcore, vcore))
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O

def dsl4(I):
    p5 = ofcolor(I, FIVE)
    ul = ulcorner(p5)
    ur = urcorner(p5)
    ll = llcorner(p5)
    lr = lrcorner(p5)
    top = connect(ul, ur)
    bot = connect(ll, lr)
    lef = connect(ul, ll)
    rig = connect(ur, lr)
    ctop = center(top)
    cbot = center(bot)
    clef = center(lef)
    crig = center(rig)
    vline = connect(ctop, cbot)
    hline = connect(clef, crig)
    axes = merge(combine(vline, hline))
    mask = intersection(axes, p5)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O

def dsl5(I):
    p5 = ofcolor(I, FIVE)
    boundary = box(p5)
    interior = difference(p5, boundary)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, interior)
    return O
```