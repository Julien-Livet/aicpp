```python
def dsl1(I):
    p5 = ofcolor(I, FIVE)
    hasL = intersection(p5, shift(p5, LEFT))
    hasR = intersection(p5, shift(p5, RIGHT))
    hasU = intersection(p5, shift(p5, UP))
    hasD = intersection(p5, shift(p5, DOWN))
    core4 = intersection(intersection(hasL, hasR), intersection(hasU, hasD))
    border = difference(p5, core4)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, border)
    return O

def dsl2(I):
    p5 = ofcolor(I, FIVE)
    vcore = intersection(intersection(p5, shift(p5, UP)), intersection(p5, shift(p5, DOWN)))
    hcore = intersection(intersection(p5, shift(p5, LEFT)), intersection(p5, shift(p5, RIGHT)))
    mask = combine(vcore, hcore)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O

def dsl3(I):
    p5 = ofcolor(I, FIVE)
    c = centerofmass(p5)
    up = shoot(c, UP)
    down = shoot(c, DOWN)
    left = shoot(c, LEFT)
    right = shoot(c, RIGHT)
    axes = combine(combine(up, down), combine(left, right))
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
    hasL = intersection(p5, shift(p5, LEFT))
    hasR = intersection(p5, shift(p5, RIGHT))
    hasU = intersection(p5, shift(p5, UP))
    hasD = intersection(p5, shift(p5, DOWN))
    t1 = intersection(intersection(hasL, hasR), hasU)
    t2 = intersection(intersection(hasL, hasR), hasD)
    t3 = intersection(intersection(hasU, hasD), hasL)
    t4 = intersection(intersection(hasU, hasD), hasR)
    mask = combine(combine(t1, t2), combine(t3, t4))
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O
```