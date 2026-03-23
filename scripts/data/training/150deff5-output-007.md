```python
def dsl1(I):
    p5 = ofcolor(I, FIVE)
    bb = backdrop(p5)
    c = center(bb)
    axes = combine(hfrontier(c), vfrontier(c))
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, intersection(p5, axes))
    return O

def dsl2(I):
    p5 = ofcolor(I, FIVE)
    hasL = shift(p5, LEFT)
    hasR = shift(p5, RIGHT)
    hasU = shift(p5, UP)
    hasD = shift(p5, DOWN)
    hcore = intersection(hasL, hasR)
    vcore = intersection(hasU, hasD)
    bars = combine(hcore, vcore)
    bulk = intersection(intersection(hcore, vcore), p5)
    mask = difference(intersection(p5, bars), bulk)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O

def dsl3(I):
    p5 = ofcolor(I, FIVE)
    cm = centerofmass(p5)
    axes = combine(hfrontier(cm), vfrontier(cm))
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, intersection(p5, axes))
    return O

def dsl4(I):
    p5 = ofcolor(I, FIVE)
    diag = intersection(p5, dmirror(p5))
    cdiag = intersection(p5, cmirror(p5))
    mask = combine(diag, cdiag)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O

def dsl5(I):
    p5 = ofcolor(I, FIVE)
    c = center(backdrop(p5))
    up = shoot(c, UP)
    down = shoot(c, DOWN)
    left = shoot(c, LEFT)
    right = shoot(c, RIGHT)
    axes = combine(combine(up, down), combine(left, right))
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, intersection(p5, axes))
    return O
```