```python
def dsl1(I):
    dims = shape(I)
    bg = canvas(SEVEN, dims)
    s2 = ofcolor(I, TWO)
    s5 = ofcolor(I, FIVE)
    # move 2 until adjacent to 5
    v = gravitate(s2, s5)
    s2p = shift(s2, v)
    # choose nearest and farthest 5-corners w.r.t. the 2-object
    crn = corners(s5)
    comp = compose(lbind(manhattan, s2), initset)
    nearc = argmin(crn, comp)
    farc = argmax(crn, comp)
    # move nearest corner one step toward 2 (by centroid direction), drop farthest corner
    d = sign(subtract(centerofmass(s2), centerofmass(s5)))
    s5rest = difference(toindices(s5), initset(farc))
    step = shift(initset(nearc), d)
    s5p = combine(s5rest, step)
    O = paint(bg, recolor(FIVE, s5p))
    O = paint(O, recolor(TWO, s2p))
    return O

def dsl2(I):
    dims = shape(I)
    bg = canvas(SEVEN, dims)
    s2 = ofcolor(I, TWO)
    s5 = ofcolor(I, FIVE)
    # move 2 until adjacent to 5
    v = gravitate(s2, s5)
    s2p = shift(s2, v)
    # centroid-directed corner selection and movement
    d = sign(subtract(centerofmass(s2), centerofmass(s5)))
    upl = add(UP, LEFT)
    upr = UP_RIGHT
    dwr = add(DOWN, RIGHT)
    dwl = DOWN_LEFT
    cUL = ulcorner(s5)
    cUR = urcorner(s5)
    cLL = llcorner(s5)
    cLR = lrcorner(s5)
    corner = branch(equality(d, upr), cUR,
             branch(equality(d, upl), cUL,
             branch(equality(d, dwr), cLR,
             branch(equality(d, dwl), cLL,
             branch(equality(d, UP), cUR,
             branch(equality(d, DOWN), cLR,
             branch(equality(d, LEFT), cUL, cUR)))))))
    s5rest = difference(toindices(s5), initset(corner))
    moved = shift(initset(corner), d)
    s5p = combine(s5rest, moved)
    O = paint(bg, recolor(FIVE, s5p))
    O = paint(O, recolor(TWO, s2p))
    return O

def dsl3(I):
    # Global symmetry normalization: mirror if 2 is to the right of 5, apply a simple rule, mirror back
    left2 = leftmost(ofcolor(I, TWO))
    left5 = leftmost(ofcolor(I, FIVE))
    cond = greater(left2, left5)
    Ir = branch(cond, vmirror(I), I)
    dims = shape(Ir)
    bg = canvas(SEVEN, dims)
    s2 = ofcolor(Ir, TWO)
    s5 = ofcolor(Ir, FIVE)
    v = gravitate(s2, s5)
    s2p = shift(s2, v)
    hv = either(equality(sign(v), LEFT), equality(sign(v), RIGHT))
    corner = branch(hv, urcorner(s5), lrcorner(s5))
    s5rest = difference(toindices(s5), initset(corner))
    moved = shift(initset(corner), branch(hv, UP, LEFT))
    Or = paint(bg, recolor(FIVE, s5rest))
    Or = paint(Or, recolor(FIVE, moved))
    Or = paint(Or, recolor(TWO, s2p))
    O = branch(cond, vmirror(Or), Or)
    return O

def dsl4(I):
    # Side-based extension of the 5-object toward the 2-object, and removal on the far side
    dims = shape(I)
    bg = canvas(SEVEN, dims)
    s2 = ofcolor(I, TWO)
    s5 = ofcolor(I, FIVE)
    v = gravitate(s2, s5)
    d = sign(v)
    s2p = shift(s2, v)
    hv = either(equality(d, LEFT), equality(d, RIGHT))

    # rows and cols of the 5 square
    topRow = connect(ulcorner(s5), urcorner(s5))
    botRow = connect(llcorner(s5), lrcorner(s5))
    leftCol = connect(ulcorner(s5), llcorner(s5))
    rightCol = connect(urcorner(s5), lrcorner(s5))

    # choose nearer side (row/col) to the 2-object
    rows = insert(botRow, initset(topRow))
    cols = insert(rightCol, initset(leftCol))
    nearRow = argmin(rows, lbind(manhattan, s2))
    farRow = other(rows, nearRow)
    nearCol = argmin(cols, lbind(manhattan, s2))
    farCol = other(cols, nearCol)

    # decide endpoints per direction and side
    isTop = equality(nearRow, topRow)
    isBot = equality(farRow, botRow)
    isLeft = equality(nearCol, leftCol)
    isRight = equality(farCol, rightCol)

    endNearH = branch(equality(d, RIGHT), branch(isTop, urcorner(s5), lrcorner(s5)),
                                   branch(isTop, ulcorner(s5), llcorner(s5)))
    endFarH  = branch(equality(d, RIGHT), branch(isBot, lrcorner(s5), urcorner(s5)),
                                   branch(isBot, llcorner(s5), ulcorner(s5)))

    endNearV = branch(equality(d, DOWN), branch(isLeft, llcorner(s5), lrcorner(s5)),
                                   branch(isLeft, ulcorner(s5), urcorner(s5)))
    endFarV  = branch(equality(d, DOWN), branch(isRight, lrcorner(s5), llcorner(s5)),
                                   branch(isRight, urcorner(s5), ulcorner(s5)))

    endNear = branch(hv, endNearH, endNearV)
    endFar  = branch(hv, endFarH, endFarV)

    new = shift(initset(endNear), d)
    s5rest = difference(toindices(s5), initset(endFar))
    s5p = combine(s5rest, new)

    O = paint(bg, recolor(FIVE, s5p))
    O = paint(O, recolor(TWO, s2p))
    return O

def dsl5(I):
    # Only relocate the 2-object to be adjacent to the 5-object; keep 5 unchanged
    dims = shape(I)
    bg = canvas(SEVEN, dims)
    s2 = ofcolor(I, TWO)
    s5 = ofcolor(I, FIVE)
    v = gravitate(s2, s5)
    s2p = shift(s2, v)
    O = paint(bg, recolor(FIVE, s5))
    O = paint(O, recolor(TWO, s2p))
    return O
```