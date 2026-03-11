```python
def dsl1(I):
    H = height(I)
    W = width(I)
    grid = asindices(I)
    non7 = difference(grid, ofcolor(I, SEVEN))
    up5 = subtract(ZERO, FIVE)
    tgt = intersection(shift(non7, astuple(up5, ZERO)), grid)
    O = fill(I, NINE, tgt)
    return O

def dsl2(I):
    H = height(I)
    W = width(I)
    grid = asindices(I)
    z = ofcolor(I, ZERO)
    t = ofcolor(I, TWO)
    n = ofcolor(I, NINE)
    up5 = subtract(ZERO, FIVE)
    up = astuple(up5, ZERO)
    move_02 = intersection(shift(combine(z, t), up), grid)
    move_9 = intersection(shift(n, up), grid)
    O1 = fill(I, NINE, move_02)
    O = fill(O1, ONE, move_9)
    return O

def dsl3(I):
    H = height(I)
    W = width(I)
    grid = asindices(I)
    non7 = difference(grid, ofcolor(I, SEVEN))
    halfH = divide(H, TWO)
    bot_rel = asindices(crop(I, astuple(halfH, ZERO), astuple(subtract(H, halfH), W)))
    bot_abs = shift(bot_rel, astuple(halfH, ZERO))
    src = intersection(non7, bot_abs)
    up5 = subtract(ZERO, FIVE)
    tgt = intersection(shift(src, astuple(up5, ZERO)), grid)
    O = fill(I, NINE, tgt)
    return O

def dsl4(I):
    H = height(I)
    W = width(I)
    grid = asindices(I)
    nine = ofcolor(I, NINE)
    bot2_rel = asindices(crop(I, astuple(subtract(H, TWO), ZERO), astuple(TWO, W)))
    bot2_abs = shift(bot2_rel, astuple(subtract(H, TWO), ZERO))
    src = intersection(nine, bot2_abs)
    up5 = subtract(ZERO, FIVE)
    tgt = intersection(shift(src, astuple(up5, ZERO)), grid)
    O = fill(I, ONE, tgt)
    return O

def dsl5(I):
    H = height(I)
    W = width(I)
    grid = asindices(I)
    z = ofcolor(I, ZERO)
    t = ofcolor(I, TWO)
    up5 = subtract(ZERO, FIVE)
    vec = astuple(up5, up5)
    src = combine(z, t)
    tgt = intersection(shift(src, vec), grid)
    O = fill(I, NINE, tgt)
    return O
```