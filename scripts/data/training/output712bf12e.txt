```python
def dsl1(I):
    # Paint 2 on all orthogonal neighbors of every 5
    x5 = ofcolor(I, FIVE)
    xR = shift(x5, RIGHT)
    xL = shift(x5, LEFT)
    xU = shift(x5, UP)
    xD = shift(x5, DOWN)
    xN = combine(combine(xR, xL), combine(xU, xD))
    x2 = recolor(TWO, xN)
    O = underpaint(I, x2)
    return O

def dsl2(I):
    # Paint 2 on all diagonal neighbors of every 5
    x5 = ofcolor(I, FIVE)
    xUR = shift(x5, UP_RIGHT)
    xUL = shift(x5, add(UP, LEFT))
    xDR = shift(x5, add(DOWN, RIGHT))
    xDL = shift(x5, DOWN_LEFT)
    xN = combine(combine(xUR, xUL), combine(xDR, xDL))
    x2 = recolor(TWO, xN)
    O = underpaint(I, x2)
    return O

def dsl3(I):
    # From existing 2's, draw vertical rays up and down (entire columns through those 2's)
    x2 = ofcolor(I, TWO)
    t2 = toindices(x2)
    up = mapply(rbind(shoot, UP), t2)
    dn = mapply(rbind(shoot, DOWN), t2)
    col = combine(combine(up, dn), t2)
    xpaint = recolor(TWO, col)
    O = underpaint(I, xpaint)
    return O

def dsl4(I):
    # From each 5, draw horizontal rays to the right with 2's
    x5 = ofcolor(I, FIVE)
    t5 = toindices(x5)
    rays = mapply(rbind(shoot, RIGHT), t5)
    xpaint = recolor(TWO, rays)
    O = underpaint(I, xpaint)
    return O

def dsl5(I):
    # Paint a 2 immediately to the left of every 5 (without overwriting non-background)
    x5 = ofcolor(I, FIVE)
    xL = shift(x5, LEFT)
    x2 = recolor(TWO, xL)
    O = underpaint(I, x2)
    return O
```