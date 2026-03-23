```python
def dsl1(I):
    # Geometric (directional shifts): build plus and diagonals by shifting centers by step 1 and 2
    pal = palette(I)
    c = leastcolor(I)
    a = other(remove(ZERO, pal), c)
    centers = ofcolor(I, c)
    plus1 = combine(shift(centers, RIGHT), shift(centers, LEFT))
    plus2 = combine(shift(centers, UP), shift(centers, DOWN))
    plus3 = combine(shift(centers, double(RIGHT)), shift(centers, double(LEFT)))
    plus4 = combine(shift(centers, double(UP)), shift(centers, double(DOWN)))
    plus = combine(combine(centers, combine(plus1, plus2)), combine(plus3, plus4))
    diag1 = combine(shift(centers, UNITY), shift(centers, NEG_UNITY))
    diag2 = combine(shift(centers, UP_RIGHT), shift(centers, DOWN_LEFT))
    diag3 = combine(shift(centers, double(UNITY)), shift(centers, double(NEG_UNITY)))
    diag4 = combine(shift(centers, double(UP_RIGHT)), shift(centers, double(DOWN_LEFT)))
    diag = combine(combine(centers, combine(diag1, diag2)), combine(diag3, diag4))
    O = canvas(ZERO, shape(I))
    O = fill(O, a, plus)
    O = fill(O, c, diag)
    return O

def dsl2(I):
    # Object extraction: per-center local mask via expansion, lines via frontiers/shoot, layered with paint
    c = leastcolor(I)
    a = other(remove(ZERO, palette(I)), c)
    cobjs = colorfilter(partition(I), c)
    centers = mapply(toindices, cobjs)
    n1 = mapply(neighbors, centers)
    d1 = mapply(ineighbors, centers)
    r1 = combine(combine(centers, n1), d1)
    n2 = mapply(neighbors, r1)
    d2 = mapply(ineighbors, r1)
    mask = combine(combine(r1, n2), d2)
    h = mapply(hfrontier, centers)
    v = mapply(vfrontier, centers)
    plus = intersection(combine(h, v), mask)
    dirs1 = insert(NEG_UNITY, initset(UNITY))
    dirs2 = insert(DOWN_LEFT, initset(UP_RIGHT))
    diag = intersection(combine(prapply(shoot, centers, dirs1), prapply(shoot, centers, dirs2)), mask)
    O = canvas(ZERO, shape(I))
    O = paint(O, recolor(a, plus))
    O = paint(O, recolor(c, diag))
    return O

def dsl3(I):
    # Color filtering + morphology: mask growth; diagonals via diagonal expansions minus plus
    c = leastcolor(I)
    a = other(remove(ZERO, palette(I)), c)
    centers = ofcolor(I, c)
    r1 = combine(combine(centers, mapply(neighbors, centers)), mapply(ineighbors, centers))
    r2 = combine(combine(r1, mapply(neighbors, r1)), mapply(ineighbors, r1))
    plus = intersection(combine(mapply(hfrontier, centers), mapply(vfrontier, centers)), r2)
    dstep1 = mapply(ineighbors, centers)
    dstep2 = mapply(ineighbors, dstep1)
    diagcand = combine(combine(centers, dstep1), dstep2)
    diag = intersection(diagcand, r2)
    diag = difference(diag, plus)
    diag = combine(diag, centers)
    O = canvas(ZERO, shape(I))
    O = fill(O, a, plus)
    O = fill(O, c, diag)
    return O

def dsl4(I):
    # Global mask + geometric shooting: build radius-2 mask then clip long lines
    c = leastcolor(I)
    a = other(remove(ZERO, palette(I)), c)
    centers = ofcolor(I, c)
    r1 = combine(combine(centers, mapply(neighbors, centers)), mapply(ineighbors, centers))
    r2 = combine(combine(r1, mapply(neighbors, r1)), mapply(ineighbors, r1))
    hLines = prapply(shoot, centers, insert(LEFT, initset(RIGHT)))
    vLines = prapply(shoot, centers, insert(UP, initset(DOWN)))
    plus = intersection(combine(hLines, vLines), r2)
    dLines1 = prapply(shoot, centers, insert(NEG_UNITY, initset(UNITY)))
    dLines2 = prapply(shoot, centers, insert(DOWN_LEFT, initset(UP_RIGHT)))
    diag = intersection(combine(dLines1, dLines2), r2)
    O = canvas(ZERO, shape(I))
    O = fill(O, a, plus)
    O = fill(O, c, diag)
    return O

def dsl5(I):
    # Relational/structural layering: derive colors, grow local mask, get plus by alignment, diagonals morphologically
    pal = palette(I)
    c = leastcolor(I)
    a = other(remove(ZERO, pal), c)
    centers = ofcolor(I, c)
    r1 = combine(combine(centers, mapply(neighbors, centers)), mapply(ineighbors, centers))
    r2 = combine(combine(r1, mapply(neighbors, r1)), mapply(ineighbors, r1))
    plus = intersection(combine(mapply(hfrontier, centers), mapply(vfrontier, centers)), r2)
    d1 = mapply(ineighbors, centers)
    d2 = mapply(ineighbors, d1)
    diag = difference(combine(combine(centers, d1), d2), plus)
    diag = intersection(diag, r2)
    O = canvas(ZERO, shape(I))
    O = underpaint(O, recolor(a, plus))
    O = paint(O, recolor(c, diag))
    return O
```