```python
def dsl1(I):
    H = height(I)
    W = width(I)
    C = canvas(ZERO, shape(I))
    # safe centers: seed is the (1,1) inside the 4x4 frame
    safeC = shift(asindices(canvas(ZERO, astuple(subtract(H, TWO), subtract(W, TWO)))), UNITY)
    pf = fork(combine, compose(rbind(shift, NEG_UNITY), initset), compose(rbind(shift, astuple(TWO, TWO)), initset))
    # 2->4
    S2 = intersection(ofcolor(I, TWO), safeC)
    R2 = mapply(backdrop, apply(pf, S2))
    O2 = recolor(FOUR, box(R2))
    X = paint(C, O2)
    # 3->1
    S3 = intersection(ofcolor(I, THREE), safeC)
    R3 = mapply(backdrop, apply(pf, S3))
    O3 = recolor(ONE, box(R3))
    X = paint(X, O3)
    # 5->6
    S5 = intersection(ofcolor(I, FIVE), safeC)
    R5 = mapply(backdrop, apply(pf, S5))
    O5 = recolor(SIX, box(R5))
    X = paint(X, O5)
    # 8->7
    S8 = intersection(ofcolor(I, EIGHT), safeC)
    R8 = mapply(backdrop, apply(pf, S8))
    O8 = recolor(SEVEN, box(R8))
    X = paint(X, O8)
    # 6->1 (optional)
    S6 = intersection(ofcolor(I, SIX), safeC)
    R6 = mapply(backdrop, apply(pf, S6))
    O6 = recolor(ONE, box(R6))
    X = paint(X, O6)
    return X

def dsl2(I):
    H = height(I)
    W = width(I)
    C = canvas(ZERO, shape(I))
    safeU = asindices(canvas(ZERO, astuple(subtract(H, THREE), subtract(W, THREE))))
    pf = fork(combine, initset, compose(rbind(shift, astuple(THREE, THREE)), initset))
    # 2->4
    S2 = intersection(ofcolor(I, TWO), safeU)
    R2 = mapply(backdrop, apply(pf, S2))
    O2 = recolor(FOUR, box(R2))
    X = paint(C, O2)
    # 3->1
    S3 = intersection(ofcolor(I, THREE), safeU)
    R3 = mapply(backdrop, apply(pf, S3))
    O3 = recolor(ONE, box(R3))
    X = paint(X, O3)
    # 5->6
    S5 = intersection(ofcolor(I, FIVE), safeU)
    R5 = mapply(backdrop, apply(pf, S5))
    O5 = recolor(SIX, box(R5))
    X = paint(X, O5)
    # 8->7
    S8 = intersection(ofcolor(I, EIGHT), safeU)
    R8 = mapply(backdrop, apply(pf, S8))
    O8 = recolor(SEVEN, box(R8))
    X = paint(X, O8)
    # mirror-replication across both axes inside the same canvas
    VX = vmirror(X)
    HX = hmirror(X)
    RX = rot180(X)
    O = paint(paint(paint(X, asobject(VX)), asobject(HX)), asobject(RX))
    return O

def dsl3(I):
    # detect 2x2 same-color seeds and stamp 4x4 hollow squares at their UL with mapping
    H = height(I)
    W = width(I)
    C = canvas(ZERO, shape(I))
    safeU = asindices(canvas(ZERO, astuple(subtract(H, THREE), subtract(W, THREE))))
    def stamp_for_color(X, cin, cout):
        S = ofcolor(I, cin)
        S_ul = intersection(intersection(intersection(S, shift(S, RIGHT)), shift(S, DOWN)), shift(S, DOWN_LEFT))
        S_ul = intersection(S_ul, safeU)
        pf = fork(combine, initset, compose(rbind(shift, astuple(THREE, THREE)), initset))
        R = mapply(backdrop, apply(pf, S_ul))
        return recolor(cout, box(R))
    O = C
    O = paint(O, stamp_for_color(I, TWO, FOUR))
    O = paint(O, stamp_for_color(I, THREE, ONE))
    O = paint(O, stamp_for_color(I, FIVE, SIX))
    O = paint(O, stamp_for_color(I, EIGHT, SEVEN))
    return O

def dsl4(I):
    # 3x3 filled squares centered on each seed with mapping
    H = height(I)
    W = width(I)
    C = canvas(ZERO, shape(I))
    safeC = shift(asindices(canvas(ZERO, astuple(subtract(H, TWO), subtract(W, TWO)))), UNITY)
    pf = fork(combine, compose(rbind(shift, NEG_UNITY), initset), compose(rbind(shift, astuple(TWO, TWO)), initset))
    def place(cin, cout, X):
        S = intersection(ofcolor(I, cin), safeC)
        R = mapply(backdrop, apply(pf, S))
        return paint(X, recolor(cout, R))
    X = C
    X = place(TWO, FOUR, X)
    X = place(THREE, ONE, X)
    X = place(FIVE, SIX, X)
    X = place(EIGHT, SEVEN, X)
    return X

def dsl5(I):
    # 2x2 filled blocks at each nonzero seed with simple mapping and mirrored replication
    H = height(I)
    W = width(I)
    C = canvas(ZERO, shape(I))
    safeB = asindices(canvas(ZERO, astuple(subtract(H, ONE), subtract(W, ONE))))
    def stamp2x2(cin, cout, X):
        S = intersection(ofcolor(I, cin), safeB)
        pf = fork(combine, initset, compose(rbind(shift, UNITY), initset))
        R = mapply(backdrop, apply(pf, S))
        return paint(X, recolor(cout, R))
    X = C
    X = stamp2x2(TWO, FOUR, X)
    X = stamp2x2(THREE, ONE, X)
    X = stamp2x2(FIVE, SIX, X)
    X = stamp2x2(EIGHT, SEVEN, X)
    # optional: include 6->1
    X = stamp2x2(SIX, ONE, X)
    # mirror-replicate
    O = paint(paint(paint(X, asobject(vmirror(X))), asobject(hmirror(X))), asobject(rot180(X)))
    return O
```