```python
def dsl1(I):
    p5 = ofcolor(I, FIVE)
    symv = vmirror(p5)
    mask = intersection(p5, symv)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O

def dsl2(I):
    p5 = ofcolor(I, FIVE)
    outline = box(p5)
    mask = intersection(p5, outline)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O

def dsl3(I):
    p5 = ofcolor(I, FIVE)
    f = frontiers(I)
    ff = merge(f)
    mask = intersection(p5, ff)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O

def dsl4(I):
    p5 = ofcolor(I, FIVE)
    c = center(p5)
    up = shoot(c, UP)
    down = shoot(c, DOWN)
    left = shoot(c, LEFT)
    right = shoot(c, RIGHT)
    axes = combine(combine(up, down), combine(left, right))
    mask = intersection(p5, axes)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O

def dsl5(I):
    p5 = ofcolor(I, FIVE)
    hasL = intersection(p5, shift(p5, LEFT))
    hasR = intersection(p5, shift(p5, RIGHT))
    hasU = intersection(p5, shift(p5, UP))
    hasD = intersection(p5, shift(p5, DOWN))
    hbridge = intersection(hasL, hasR)
    vbridge = intersection(hasU, hasD)
    noV = difference(hbridge, combine(hasU, hasD))
    noH = difference(vbridge, combine(hasL, hasR))
    mask = combine(noV, noH)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O
```