```python
def dsl1(I):
    O = I
    x8 = ofcolor(I, EIGHT)
    x4 = ofcolor(I, FOUR)
    x6 = ofcolor(I, SIX)
    x2 = ofcolor(I, TWO)
    x3 = ofcolor(I, THREE)
    x1 = ofcolor(I, ONE)

    # 4/8: complete both directions
    O = underpaint(O, recolor(FOUR, shift(x8, LEFT)))
    O = underpaint(O, recolor(FOUR, shift(x8, RIGHT)))
    O = underpaint(O, recolor(FOUR, shift(x8, UP)))
    O = underpaint(O, recolor(FOUR, shift(x8, DOWN)))
    mid4h = intersection(shift(x4, LEFT), shift(x4, RIGHT))
    mid4v = intersection(shift(x4, UP), shift(x4, DOWN))
    O = underpaint(O, recolor(EIGHT, mid4h))
    O = underpaint(O, recolor(EIGHT, mid4v))

    # 6/2 around 8 and between 8s (prefer 6 if present)
    has6 = greater(size(x6), ZERO)
    has2 = greater(size(x2), ZERO)
    mid88h = intersection(shift(x8, LEFT), shift(x8, RIGHT))
    mid88v = intersection(shift(x8, UP), shift(x8, DOWN))

    O6 = O
    O6 = underpaint(O6, recolor(EIGHT, shift(x6, LEFT)))
    O6 = underpaint(O6, recolor(EIGHT, shift(x6, RIGHT)))
    O6 = underpaint(O6, recolor(EIGHT, shift(x6, UP)))
    O6 = underpaint(O6, recolor(EIGHT, shift(x6, DOWN)))
    O6 = underpaint(O6, recolor(SIX, mid88h))
    O6 = underpaint(O6, recolor(SIX, mid88v))

    O2 = O
    O2 = underpaint(O2, recolor(EIGHT, shift(x2, LEFT)))
    O2 = underpaint(O2, recolor(EIGHT, shift(x2, RIGHT)))
    O2 = underpaint(O2, recolor(EIGHT, shift(x2, UP)))
    O2 = underpaint(O2, recolor(EIGHT, shift(x2, DOWN)))
    O2 = underpaint(O2, recolor(TWO, mid88h))
    O2 = underpaint(O2, recolor(TWO, mid88v))

    O = branch(has6, O6, branch(has2, O2, O))

    # 1/3: prefer vertical, else horizontal, else diagonals
    up1 = greater(size(intersection(shift(x3, UP), x1)), ZERO)
    dn1 = greater(size(intersection(shift(x3, DOWN), x1)), ZERO)
    lf1 = greater(size(intersection(shift(x3, LEFT), x1)), ZERO)
    rt1 = greater(size(intersection(shift(x3, RIGHT), x1)), ZERO)
    d1 = greater(size(intersection(shift(x3, NEG_UNITY), x1)), ZERO)
    d2 = greater(size(intersection(shift(x3, UP_RIGHT), x1)), ZERO)
    d3 = greater(size(intersection(shift(x3, DOWN_LEFT), x1)), ZERO)
    d4 = greater(size(intersection(shift(x3, UNITY), x1)), ZERO)
    haveV = either(up1, dn1)
    haveH = either(lf1, rt1)
    haveD = either(either(d1, d2), either(d3, d4))

    candV = O
    candV = underpaint(candV, recolor(ONE, shift(x3, UP)))
    candV = underpaint(candV, recolor(ONE, shift(x3, DOWN)))
    candH = O
    candH = underpaint(candH, recolor(ONE, shift(x3, LEFT)))
    candH = underpaint(candH, recolor(ONE, shift(x3, RIGHT)))
    candD = O
    candD = underpaint(candD, recolor(ONE, shift(x3, NEG_UNITY)))
    candD = underpaint(candD, recolor(ONE, shift(x3, UP_RIGHT)))
    candD = underpaint(candD, recolor(ONE, shift(x3, DOWN_LEFT)))
    candD = underpaint(candD, recolor(ONE, shift(x3, UNITY)))

    O = branch(haveV, candV, branch(haveH, candH, branch(haveD, candD, O)))
    return O

def dsl2(I):
    O = I
    x8 = ofcolor(I, EIGHT)
    x4 = ofcolor(I, FOUR)
    x6 = ofcolor(I, SIX)
    x2 = ofcolor(I, TWO)
    x3 = ofcolor(I, THREE)
    x1 = ofcolor(I, ONE)

    # Only complete midpoints
    mid4h = intersection(shift(x4, LEFT), shift(x4, RIGHT))
    mid4v = intersection(shift(x4, UP), shift(x4, DOWN))
    O = underpaint(O, recolor(EIGHT, mid4h))
    O = underpaint(O, recolor(EIGHT, mid4v))

    mid88h = intersection(shift(x8, LEFT), shift(x8, RIGHT))
    mid88v = intersection(shift(x8, UP), shift(x8, DOWN))
    has6 = greater(size(x6), ZERO)
    has2 = greater(size(x2), ZERO)
    O = branch(has6, underpaint(O, recolor(SIX, mid88h)), O)
    O = branch(has6, underpaint(O, recolor(SIX, mid88v)), O)
    O = branch(both(flip(has6), has2), underpaint(O, recolor(TWO, mid88h)), O)
    O = branch(both(flip(has6), has2), underpaint(O, recolor(TWO, mid88v)), O)

    # 1/3: replicate horizontally and vertically if present
    haveH = either(greater(size(intersection(shift(x3, LEFT), x1)), ZERO),
                   greater(size(intersection(shift(x3, RIGHT), x1)), ZERO))
    haveV = either(greater(size(intersection(shift(x3, UP), x1)), ZERO),
                   greater(size(intersection(shift(x3, DOWN), x1)), ZERO))
    O = branch(haveH, underpaint(O, recolor(ONE, shift(x3, LEFT))), O)
    O = branch(haveH, underpaint(O, recolor(ONE, shift(x3, RIGHT))), O)
    O = branch(haveV, underpaint(O, recolor(ONE, shift(x3, UP))), O)
    O = branch(haveV, underpaint(O, recolor(ONE, shift(x3, DOWN))), O)
    return O

def dsl3(I):
    O = I
    x8 = ofcolor(I, EIGHT)
    x4 = ofcolor(I, FOUR)
    x6 = ofcolor(I, SIX)
    x2 = ofcolor(I, TWO)
    x3 = ofcolor(I, THREE)
    x1 = ofcolor(I, ONE)

    # 4/8: horizontal only
    O = underpaint(O, recolor(FOUR, shift(x8, LEFT)))
    O = underpaint(O, recolor(FOUR, shift(x8, RIGHT)))
    mid4h = intersection(shift(x4, LEFT), shift(x4, RIGHT))
    O = underpaint(O, recolor(EIGHT, mid4h))

    # 6/2: prioritize 6, then 2; add siding 8s for both
    O = underpaint(O, recolor(EIGHT, shift(x6, LEFT)))
    O = underpaint(O, recolor(EIGHT, shift(x6, RIGHT)))
    O = underpaint(O, recolor(EIGHT, shift(x6, UP)))
    O = underpaint(O, recolor(EIGHT, shift(x6, DOWN)))
    O = underpaint(O, recolor(EIGHT, shift(x2, LEFT)))
    O = underpaint(O, recolor(EIGHT, shift(x2, RIGHT)))
    O = underpaint(O, recolor(EIGHT, shift(x2, UP)))
    O = underpaint(O, recolor(EIGHT, shift(x2, DOWN)))
    mid88h = intersection(shift(x8, LEFT), shift(x8, RIGHT))
    mid88v = intersection(shift(x8, UP), shift(x8, DOWN))
    O = underpaint(O, recolor(SIX, mid88h))
    O = underpaint(O, recolor(SIX, mid88v))
    O = underpaint(O, recolor(TWO, mid88h))
    O = underpaint(O, recolor(TWO, mid88v))

    # 1/3: if any adjacency exists, fill all eight directions
    haveH = either(greater(size(intersection(shift(x3, LEFT), x1)), ZERO),
                   greater(size(intersection(shift(x3, RIGHT), x1)), ZERO))
    haveV = either(greater(size(intersection(shift(x3, UP), x1)), ZERO),
                   greater(size(intersection(shift(x3, DOWN), x1)), ZERO))
    haveD = either(either(greater(size(intersection(shift(x3, NEG_UNITY), x1)), ZERO),
                          greater(size(intersection(shift(x3, UP_RIGHT), x1)), ZERO)),
                   either(greater(size(intersection(shift(x3, DOWN_LEFT), x1)), ZERO),
                          greater(size(intersection(shift(x3, UNITY), x1)), ZERO)))
    anyAdj = either(haveH, either(haveV, haveD))
    O = branch(anyAdj, underpaint(O, recolor(ONE, shift(x3, LEFT))), O)
    O = branch(anyAdj, underpaint(O, recolor(ONE, shift(x3, RIGHT))), O)
    O = branch(anyAdj, underpaint(O, recolor(ONE, shift(x3, UP))), O)
    O = branch(anyAdj, underpaint(O, recolor(ONE, shift(x3, DOWN))), O)
    O = branch(anyAdj, underpaint(O, recolor(ONE, shift(x3, NEG_UNITY))), O)
    O = branch(anyAdj, underpaint(O, recolor(ONE, shift(x3, UP_RIGHT))), O)
    O = branch(anyAdj, underpaint(O, recolor(ONE, shift(x3, DOWN_LEFT))), O)
    O = branch(anyAdj, underpaint(O, recolor(ONE, shift(x3, UNITY))), O)
    return O

def dsl4(I):
    O = I
    x8 = ofcolor(I, EIGHT)
    x4 = ofcolor(I, FOUR)
    x6 = ofcolor(I, SIX)
    x2 = ofcolor(I, TWO)
    x3 = ofcolor(I, THREE)
    x1 = ofcolor(I, ONE)

    # 4/8: horizontal completion only
    O = underpaint(O, recolor(FOUR, shift(x8, LEFT)))
    O = underpaint(O, recolor(FOUR, shift(x8, RIGHT)))
    mid4h = intersection(shift(x4, LEFT), shift(x4, RIGHT))
    O = underpaint(O, recolor(EIGHT, mid4h))

    # 8/center: fill centers in both orientations; prefer 6 over 2
    mid88h = intersection(shift(x8, LEFT), shift(x8, RIGHT))
    mid88v = intersection(shift(x8, UP), shift(x8, DOWN))
    has6 = greater(size(x6), ZERO)
    O = branch(has6, underpaint(O, recolor(SIX, mid88h)), O)
    O = branch(has6, underpaint(O, recolor(SIX, mid88v)), O)
    O = branch(flip(has6), underpaint(O, recolor(TWO, mid88h)), O)
    O = branch(flip(has6), underpaint(O, recolor(TWO, mid88v)), O)
    O = underpaint(O, recolor(EIGHT, shift(x6, LEFT)))
    O = underpaint(O, recolor(EIGHT, shift(x6, RIGHT)))
    O = underpaint(O, recolor(EIGHT, shift(x2, LEFT)))
    O = underpaint(O, recolor(EIGHT, shift(x2, RIGHT)))
    O = underpaint(O, recolor(EIGHT, shift(x6, UP)))
    O = underpaint(O, recolor(EIGHT, shift(x6, DOWN)))
    O = underpaint(O, recolor(EIGHT, shift(x2, UP)))
    O = underpaint(O, recolor(EIGHT, shift(x2, DOWN)))

    # 1/3: diagonals preferred; else vertical; no horizontal
    d1 = greater(size(intersection(shift(x3, NEG_UNITY), x1)), ZERO)
    d2 = greater(size(intersection(shift(x3, UP_RIGHT), x1)), ZERO)
    d3 = greater(size(intersection(shift(x3, DOWN_LEFT), x1)), ZERO)
    d4 = greater(size(intersection(shift(x3, UNITY), x1)), ZERO)
    haveDiag = either(either(d1, d2), either(d3, d4))
    haveV = either(greater(size(intersection(shift(x3, UP), x1)), ZERO),
                   greater(size(intersection(shift(x3, DOWN), x1)), ZERO))

    candD = O
    candD = underpaint(candD, recolor(ONE, shift(x3, NEG_UNITY)))
    candD = underpaint(candD, recolor(ONE, shift(x3, UP_RIGHT)))
    candD = underpaint(candD, recolor(ONE, shift(x3, DOWN_LEFT)))
    candD = underpaint(candD, recolor(ONE, shift(x3, UNITY)))
    candV = O
    candV = underpaint(candV, recolor(ONE, shift(x3, UP)))
    candV = underpaint(candV, recolor(ONE, shift(x3, DOWN)))

    O = branch(haveDiag, candD, branch(haveV, candV, O))
    return O

def dsl5(I):
    O = I
    x8 = ofcolor(I, EIGHT)
    x4 = ofcolor(I, FOUR)
    x6 = ofcolor(I, SIX)
    x2 = ofcolor(I, TWO)

    # Minimal: 4/8 horizontal completion
    O = underpaint(O, recolor(FOUR, shift(x8, LEFT)))
    O = underpaint(O, recolor(FOUR, shift(x8, RIGHT)))
    mid4h = intersection(shift(x4, LEFT), shift(x4, RIGHT))
    O = underpaint(O, recolor(EIGHT, mid4h))

    # 8/center: both orientations, prefer 6 then 2
    mid88h = intersection(shift(x8, LEFT), shift(x8, RIGHT))
    mid88v = intersection(shift(x8, UP), shift(x8, DOWN))
    O = underpaint(O, recolor(SIX, mid88h))
    O = underpaint(O, recolor(SIX, mid88v))
    O = underpaint(O, recolor(TWO, mid88h))
    O = underpaint(O, recolor(TWO, mid88v))
    return O
```