```python
def dsl1(I):
    dims = shape(I)
    bg = canvas(SEVEN, dims)
    rI = rot180(I)
    s2 = ofcolor(I, TWO)
    r2 = ofcolor(rI, TWO)
    O = paint(paint(bg, recolor(TWO, s2)), recolor(FIVE, r2))
    return O

def dsl2(I):
    dims = shape(I)
    bg = canvas(SEVEN, dims)
    s2 = ofcolor(I, TWO)
    s5 = ofcolor(I, FIVE)
    c2 = center(s2)
    c5 = center(s5)
    off = add(subtract(c5, c2), LEFT)
    s2p = shift(s2, off)
    O = paint(paint(bg, recolor(FIVE, s5)), recolor(TWO, s2p))
    return O

def dsl3(I):
    dims = shape(I)
    bg = canvas(SEVEN, dims)
    s2 = ofcolor(I, TWO)
    s5 = ofcolor(I, FIVE)
    c2 = centerofmass(s2)
    c5 = centerofmass(s5)
    line = connect(c2, c5)
    O = paint(paint(bg, recolor(FIVE, s5)), recolor(TWO, line))
    return O

def dsl4(I):
    dims = shape(I)
    bg = canvas(SEVEN, dims)
    s2 = ofcolor(I, TWO)
    s5 = ofcolor(I, FIVE)
    c2 = centerofmass(s2)
    c5 = centerofmass(s5)
    delta = subtract(c5, c2)
    s2p = shift(s2, multiply(delta, TWO))
    O = paint(paint(bg, recolor(FIVE, s5)), recolor(TWO, s2p))
    return O

def dsl5(I):
    dims = shape(I)
    bg = canvas(SEVEN, dims)
    s2 = ofcolor(I, TWO)
    s5 = ofcolor(I, FIVE)
    v = gravitate(s2, s5)
    s2p = shift(s2, v)
    O = paint(paint(bg, recolor(FIVE, s5)), recolor(TWO, s2p))
    return O
```