```python
def dsl1(I):
    p5 = ofcolor(I, FIVE)
    sl = shift(p5, LEFT)
    sr = shift(p5, RIGHT)
    su = shift(p5, UP)
    sd = shift(p5, DOWN)
    hcore = intersection(p5, intersection(sl, sr))
    vcore = intersection(p5, intersection(su, sd))
    mask = combine(hcore, vcore)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O

def dsl2(I):
    p5 = ofcolor(I, FIVE)
    c = centerofmass(p5)
    up = shoot(c, UP)
    down = shoot(c, DOWN)
    left = shoot(c, LEFT)
    right = shoot(c, RIGHT)
    axes = combine(combine(up, down), combine(left, right))
    mask = intersection(p5, axes)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O

def dsl3(I):
    p5 = ofcolor(I, FIVE)
    vcore = intersection(p5, vmirror(p5))
    hcore = intersection(p5, hmirror(p5))
    mask = combine(vcore, hcore)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O

def dsl4(I):
    p5 = ofcolor(I, FIVE)
    jL = leftmost(p5)
    jR = rightmost(p5)
    iU = uppermost(p5)
    iD = lowermost(p5)
    jM = divide(add(jL, jR), TWO)
    iM = divide(add(iU, iD), TWO)
    topc = astuple(iU, jM)
    botc = astuple(iD, jM)
    lefc = astuple(iM, jL)
    rigc = astuple(iM, jR)
    vline = connect(topc, botc)
    hline = connect(lefc, rigc)
    axes = combine(vline, hline)
    mask = intersection(p5, axes)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O

def dsl5(I):
    p5 = ofcolor(I, FIVE)
    sl = shift(p5, LEFT)
    su = shift(p5, UP)
    right_edge = difference(p5, sl)
    bottom_edge = difference(p5, su)
    mask = combine(right_edge, bottom_edge)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O
```