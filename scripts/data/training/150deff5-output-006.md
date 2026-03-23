```python
def dsl1(I):
    p5 = ofcolor(I, FIVE)
    fr = frontiers(I)
    fringes = merge(apply(toindices, fr))
    edge = intersection(p5, fringes)
    core = difference(p5, edge)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, core)
    return O

def dsl2(I):
    p5 = ofcolor(I, FIVE)
    cm = centerofmass(p5)
    up = shoot(cm, UP)
    down = shoot(cm, DOWN)
    left = shoot(cm, LEFT)
    right = shoot(cm, RIGHT)
    vline = combine(up, down)
    hline = combine(left, right)
    axes = combine(vline, hline)
    onaxes = intersection(p5, axes)
    lr_both = intersection(shift(p5, LEFT), shift(p5, RIGHT))
    ud_both = intersection(shift(p5, UP), shift(p5, DOWN))
    vmask = difference(intersection(onaxes, vline), lr_both)
    hmask = difference(intersection(onaxes, hline), ud_both)
    mask = combine(vmask, hmask)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O

def dsl3(I):
    p5 = ofcolor(I, FIVE)
    hm = hmirror(p5)
    vm = vmirror(p5)
    hfix = intersection(p5, hm)
    vfix = intersection(p5, vm)
    mask = combine(hfix, vfix)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O

def dsl4(I):
    p5 = ofcolor(I, FIVE)
    hasU = shift(p5, UP)
    hasD = shift(p5, DOWN)
    hasL = shift(p5, LEFT)
    hasR = shift(p5, RIGHT)
    vert_cont = intersection(hasU, hasD)
    horz_cont = intersection(hasL, hasR)
    noL = difference(p5, hasL)
    noR = difference(p5, hasR)
    noH = intersection(noL, noR)
    noU = difference(p5, hasU)
    noD = difference(p5, hasD)
    noV = intersection(noU, noD)
    vthin = intersection(p5, intersection(vert_cont, noH))
    hthin = intersection(p5, intersection(horz_cont, noV))
    mask = combine(vthin, hthin)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O

def dsl5(I):
    p5 = ofcolor(I, FIVE)
    hbar = intersection(shift(p5, LEFT), shift(p5, RIGHT))
    vbar = intersection(shift(p5, UP), shift(p5, DOWN))
    mask = intersection(p5, combine(hbar, vbar))
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O
```