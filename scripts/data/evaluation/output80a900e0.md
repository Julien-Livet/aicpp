```python
def dsl1(I):
    # Extend along counter-diagonals for colors {2,3,4,8}, paint in ascending order so larger colors override.
    O = I
    inds = asindices(I)
    dirs = insert(UP_RIGHT, initset(DOWN_LEFT))
    s2 = ofcolor(I, TWO)
    r2 = merge(prapply(shoot, s2, dirs))
    p2 = intersection(inds, combine(s2, r2))
    O = paint(O, recolor(TWO, p2))
    s3 = ofcolor(I, THREE)
    r3 = merge(prapply(shoot, s3, dirs))
    p3 = intersection(inds, combine(s3, r3))
    O = paint(O, recolor(THREE, p3))
    s4 = ofcolor(I, FOUR)
    r4 = merge(prapply(shoot, s4, dirs))
    p4 = intersection(inds, combine(s4, r4))
    O = paint(O, recolor(FOUR, p4))
    s8 = ofcolor(I, EIGHT)
    r8 = merge(prapply(shoot, s8, dirs))
    p8 = intersection(inds, combine(s8, r8))
    O = paint(O, recolor(EIGHT, p8))
    return O

def dsl2(I):
    # Extend along counter-diagonals only for powers-of-two colors {2,4,8}, ascending order.
    O = I
    inds = asindices(I)
    dirs = insert(UP_RIGHT, initset(DOWN_LEFT))
    s2 = ofcolor(I, TWO)
    r2 = merge(prapply(shoot, s2, dirs))
    p2 = intersection(inds, combine(s2, r2))
    O = paint(O, recolor(TWO, p2))
    s4 = ofcolor(I, FOUR)
    r4 = merge(prapply(shoot, s4, dirs))
    p4 = intersection(inds, combine(s4, r4))
    O = paint(O, recolor(FOUR, p4))
    s8 = ofcolor(I, EIGHT)
    r8 = merge(prapply(shoot, s8, dirs))
    p8 = intersection(inds, combine(s8, r8))
    O = paint(O, recolor(EIGHT, p8))
    return O

def dsl3(I):
    # Like dsl1 but restrict painting to the bounding box of all seeds {2,3,4,8}.
    O = I
    dirs = insert(UP_RIGHT, initset(DOWN_LEFT))
    s2 = ofcolor(I, TWO)
    s3 = ofcolor(I, THREE)
    s4 = ofcolor(I, FOUR)
    s8 = ofcolor(I, EIGHT)
    sall = combine(combine(s2, s3), combine(s4, s8))
    bbox = backdrop(sall)
    r2 = merge(prapply(shoot, s2, dirs))
    p2 = intersection(bbox, combine(s2, r2))
    O = paint(O, recolor(TWO, p2))
    r3 = merge(prapply(shoot, s3, dirs))
    p3 = intersection(bbox, combine(s3, r3))
    O = paint(O, recolor(THREE, p3))
    r4 = merge(prapply(shoot, s4, dirs))
    p4 = intersection(bbox, combine(s4, r4))
    O = paint(O, recolor(FOUR, p4))
    r8 = merge(prapply(shoot, s8, dirs))
    p8 = intersection(bbox, combine(s8, r8))
    O = paint(O, recolor(EIGHT, p8))
    return O

def dsl4(I):
    # Extend {2,3,4} along counter-diagonals; extend {8} along both diagonals.
    O = I
    inds = asindices(I)
    dirs_ad = insert(UP_RIGHT, initset(DOWN_LEFT))
    dirs_d = insert(NEG_UNITY, initset(UNITY))
    # 2,3,4: counter-diagonal
    for c in (TWO, THREE, FOUR):
        s = ofcolor(I, c)
        r = merge(prapply(shoot, s, dirs_ad))
        p = intersection(inds, combine(s, r))
        O = paint(O, recolor(c, p))
    # 8: both diagonals
    s8 = ofcolor(I, EIGHT)
    r8a = merge(prapply(shoot, s8, dirs_ad))
    r8b = merge(prapply(shoot, s8, dirs_d))
    p8 = intersection(inds, combine(s8, combine(r8a, r8b)))
    O = paint(O, recolor(EIGHT, p8))
    return O

def dsl5(I):
    # Extend only the highest-valued present color among {8,4,2,3} along counter-diagonals.
    O = I
    inds = asindices(I)
    dirs = insert(UP_RIGHT, initset(DOWN_LEFT))
    s2 = ofcolor(I, TWO)
    r2 = merge(prapply(shoot, s2, dirs))
    p2 = intersection(inds, combine(s2, r2))
    s3 = ofcolor(I, THREE)
    r3 = merge(prapply(shoot, s3, dirs))
    p3 = intersection(inds, combine(s3, r3))
    s4 = ofcolor(I, FOUR)
    r4 = merge(prapply(shoot, s4, dirs))
    p4 = intersection(inds, combine(s4, r4))
    s8 = ofcolor(I, EIGHT)
    r8 = merge(prapply(shoot, s8, dirs))
    p8 = intersection(inds, combine(s8, r8))
    c8 = greater(colorcount(I, EIGHT), ZERO)
    c4 = greater(colorcount(I, FOUR), ZERO)
    c2 = greater(colorcount(I, TWO), ZERO)
    psel = branch(c8, p8, branch(c4, p4, branch(c2, p2, p3)))
    O = paint(O, recolor(branch(c8, EIGHT, branch(c4, FOUR, branch(c2, TWO, THREE))), psel))
    return O
```