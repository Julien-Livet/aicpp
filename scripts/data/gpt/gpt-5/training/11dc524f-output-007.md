```python
def dsl1(I):
    dims = shape(I)
    bg = canvas(SEVEN, dims)
    s2 = ofcolor(I, TWO)
    s5 = ofcolor(I, FIVE)
    v = gravitate(s2, s5)
    s2p = shift(s2, v)
    hv = either(equality(sign(v), LEFT), equality(sign(v), RIGHT))
    corner = branch(hv, urcorner(s5), lrcorner(s5))
    cset = initset(corner)
    s5rest = difference(toindices(s5), cset)
    moved = shift(cset, branch(hv, UP, LEFT))
    O = paint(bg, recolor(FIVE, s5rest))
    O = paint(O, recolor(FIVE, moved))
    O = paint(O, recolor(TWO, s2p))
    return O

def dsl2(I):
    dims = shape(I)
    bg = canvas(SEVEN, dims)
    s2 = ofcolor(I, TWO)
    s5 = ofcolor(I, FIVE)
    off = subtract(ulcorner(s5), lrcorner(s2))
    s2p = shift(s2, off)
    O = paint(bg, recolor(FIVE, s5))
    O = paint(O, recolor(TWO, s2p))
    return O

def dsl3(I):
    dims = shape(I)
    bg = canvas(SEVEN, dims)
    s2 = ofcolor(I, TWO)
    s5 = ofcolor(I, FIVE)
    c2 = centerofmass(s2)
    c5 = centerofmass(s5)
    d = sign(subtract(c2, c5))
    step = shift(initset(c5), d)
    s5p = combine(toindices(s5), step)
    O = paint(bg, recolor(FIVE, s5p))
    O = paint(O, recolor(TWO, s2))
    return O

def dsl4(I):
    dims = shape(I)
    bg = canvas(SEVEN, dims)
    s2 = ofcolor(I, TWO)
    s5 = ofcolor(I, FIVE)
    s2m = vmirror(s2)
    O = paint(bg, recolor(FIVE, s5))
    O = paint(O, recolor(TWO, s2m))
    return O

def dsl5(I):
    dims = shape(I)
    bg = canvas(SEVEN, dims)
    rI = rot180(I)
    s2r = ofcolor(rI, TWO)
    s5 = ofcolor(I, FIVE)
    O = paint(bg, recolor(FIVE, s5))
    O = paint(O, recolor(TWO, s2r))
    return O
```