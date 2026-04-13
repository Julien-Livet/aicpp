```python
def dsl1(I):
    # Global symmetry normalization: mirror so that 2 is up-left of 5, apply a canonical edit, mirror back
    s2 = ofcolor(I, TWO)
    s5 = ofcolor(I, FIVE)
    condV = greater(leftmost(s2), leftmost(s5))
    Iv = branch(condV, vmirror(I), I)
    s2v = ofcolor(Iv, TWO)
    s5v = ofcolor(Iv, FIVE)
    condH = greater(uppermost(s2v), uppermost(s5v))
    Ir = branch(condH, hmirror(Iv), Iv)

    dims = shape(Ir)
    bg = canvas(SEVEN, dims)
    s2r = ofcolor(Ir, TWO)
    s5r = ofcolor(Ir, FIVE)
    v = gravitate(s2r, s5r)
    s2p = shift(s2r, v)

    cUL = ulcorner(s5r)
    cUR = urcorner(s5r)
    s5rest = difference(toindices(s5r), initset(cUR))
    addpt = shift(initset(cUL), UP)
    s5p = combine(s5rest, addpt)

    Or = paint(bg, recolor(FIVE, s5p))
    Or = paint(Or, recolor(TWO, s2p))
    Ovh = branch(condH, hmirror(Or), Or)
    O = branch(condV, vmirror(Ovh), Ovh)
    return O

def dsl2(I):
    # Object extraction: move 2 to adjacency; move nearest 5-corner one step toward 2; drop farthest corner
    dims = shape(I)
    bg = canvas(SEVEN, dims)
    s2 = ofcolor(I, TWO)
    s5 = ofcolor(I, FIVE)

    v = gravitate(s2, s5)
    s2p = shift(s2, v)

    crn = corners(s5)
    comp = compose(lbind(manhattan, s2), initset)
    nearc = argmin(crn, comp)
    farc = argmax(crn, comp)

    vnear = gravitate(initset(nearc), s2)
    dnear = sign(vnear)
    moved = shift(initset(nearc), dnear)

    s5rest = difference(toindices(s5), initset(farc))
    s5p = combine(s5rest, moved)

    O = paint(bg, recolor(FIVE, s5p))
    O = paint(O, recolor(TWO, s2p))
    return O

def dsl3(I):
    # Color-filtered side choice: extend the nearer side of the 5 toward the 2; drop opposite far corner
    dims = shape(I)
    bg = canvas(SEVEN, dims)
    s2 = ofcolor(I, TWO)
    s5 = ofcolor(I, FIVE)

    v = gravitate(s2, s5)
    s2p = shift(s2, v)

    topRow = connect(ulcorner(s5), urcorner(s5))
    botRow = connect(llcorner(s5), lrcorner(s5))
    leftCol = connect(ulcorner(s5), llcorner(s5))
    rightCol = connect(urcorner(s5), lrcorner(s5))

    rows = insert(botRow, initset(topRow))
    cols = insert(rightCol, initset(leftCol))
    nearRow = argmin(rows, lbind(manhattan, s2))
    farRow = other(rows, nearRow)
    nearCol = argmin(cols, lbind(manhattan, s2))
    farCol = other(cols, nearCol)

    # Choose which side (row vs col) is closer to the 2
    sides = insert(nearRow, initset(nearCol))
    nearSide = argmin(sides, lbind(manhattan, s2))
    isRow = equality(nearSide, nearRow)

    condLeft = greater(leftmost(s5), leftmost(s2))
    condUp = greater(uppermost(s5), uppermost(s2))
    stepCol = branch(condLeft, LEFT, RIGHT)
    stepRow = branch(condUp, UP, DOWN)

    endNearH = branch(equality(nearRow, topRow),
                      branch(condLeft, ulcorner(s5), urcorner(s5)),
                      branch(condLeft, llcorner(s5), lrcorner(s5)))
    endNearV = branch(equality(nearCol, leftCol),
                      branch(condUp, ulcorner(s5), llcorner(s5)),
                      branch(condUp, urcorner(s5), lrcorner(s5)))
    endNear = branch(isRow, endNearH, endNearV)
    step = branch(isRow, stepCol, stepRow)

    endFar = branch(equality(farRow, topRow),
                    branch(equality(farCol, rightCol), urcorner(s5), ulcorner(s5)),
                    branch(equality(farCol, rightCol), lrcorner(s5), llcorner(s5)))

    new = shift(initset(endNear), step)
    s5rest = difference(toindices(s5), initset(endFar))
    s5p = combine(s5rest, new)

    O = paint(bg, recolor(FIVE, s5p))
    O = paint(O, recolor(TWO, s2p))
    return O

def dsl4(I):
    # Geometric orientation by adjacency vector: choose row vs col by v, extend on that side toward 2, drop opposite corner
    dims = shape(I)
    bg = canvas(SEVEN, dims)
    s2 = ofcolor(I, TWO)
    s5 = ofcolor(I, FIVE)

    v = gravitate(s2, s5)
    d = sign(v)
    s2p = shift(s2, v)
    hv = either(equality(d, LEFT), equality(d, RIGHT))

    topRow = connect(ulcorner(s5), urcorner(s5))
    botRow = connect(llcorner(s5), lrcorner(s5))
    leftCol = connect(ulcorner(s5), llcorner(s5))
    rightCol = connect(urcorner(s5), lrcorner(s5))

    rows = insert(botRow, initset(topRow))
    cols = insert(rightCol, initset(leftCol))
    nearRow = argmin(rows, lbind(manhattan, s2))
    farRow = other(rows, nearRow)
    nearCol = argmin(cols, lbind(manhattan, s2))
    farCol = other(cols, nearCol)

    condLeft = greater(leftmost(s5), leftmost(s2))
    condUp = greater(uppermost(s5), uppermost(s2))
    stepH = branch(condLeft, LEFT, RIGHT)
    stepV = branch(condUp, UP, DOWN)

    endNearH = branch(equality(nearRow, topRow),
                      branch(condLeft, ulcorner(s5), urcorner(s5)),
                      branch(condLeft, llcorner(s5), lrcorner(s5)))
    endNearV = branch(equality(nearCol, leftCol),
                      branch(condUp, ulcorner(s5), llcorner(s5)),
                      branch(condUp, urcorner(s5), lrcorner(s5)))
    endNear = branch(hv, endNearH, endNearV)
    step = branch(hv, stepH, stepV)

    endFar = branch(equality(farRow, topRow),
                    branch(equality(farCol, rightCol), urcorner(s5), ulcorner(s5)),
                    branch(equality(farCol, rightCol), lrcorner(s5), llcorner(s5)))

    new = shift(initset(endNear), step)
    s5rest = difference(toindices(s5), initset(endFar))
    s5p = combine(s5rest, new)

    O = paint(bg, recolor(FIVE, s5p))
    O = paint(O, recolor(TWO, s2p))
    return O

def dsl5(I):
    # Relational: remove farthest 5-corner; add one step from the nearest corner in the outward-from-center direction
    dims = shape(I)
    bg = canvas(SEVEN, dims)
    s2 = ofcolor(I, TWO)
    s5 = ofcolor(I, FIVE)

    v = gravitate(s2, s5)
    s2p = shift(s2, v)

    crn = corners(s5)
    comp = compose(lbind(manhattan, s2), initset)
    nearc = argmin(crn, comp)
    farc = argmax(crn, comp)

    c5 = centerofmass(s5)
    d_out = invert(sign(subtract(c5, nearc)))  # direction away from s5 center through the nearest corner
    moved = shift(initset(nearc), d_out)

    s5rest = difference(toindices(s5), initset(farc))
    s5p = combine(s5rest, moved)

    O = paint(bg, recolor(FIVE, s5p))
    O = paint(O, recolor(TWO, s2p))
    return O
```