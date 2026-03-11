```python
def dsl1(I):
    # detect accent color (non-7)
    accent = leastcolor(I)

    # build row stripes: rows with indices 1-2,4-5,7-8,10-11,13-14 are 7; others 0
    r0 = canvas(ZERO, (1, 16))
    r7 = canvas(SEVEN, (1, 16))
    tR = vconcat(r0, vconcat(r7, r7))
    rr1 = vconcat(tR, tR)
    rr2 = vconcat(rr1, tR)
    rr3 = vconcat(rr2, tR)
    rr4 = vconcat(rr3, tR)       # 15 rows
    RS = vconcat(rr4, r0)        # 16 rows

    # build column stripes: columns with indices 1-2,4-5,7-8,10-11,13-14 are 7; others 0
    c0 = canvas(ZERO, (16, 1))
    c7 = canvas(SEVEN, (16, 1))
    tC = hconcat(c0, hconcat(c7, c7))
    cc1 = hconcat(tC, tC)
    cc2 = hconcat(cc1, tC)
    cc3 = hconcat(cc2, tC)
    cc4 = hconcat(cc3, tC)       # 15 cols
    CS = hconcat(cc4, c0)        # 16 cols

    # delta-columns (col % 3 == 0 is 7)
    tDC = hconcat(c7, hconcat(c0, c0))
    dc1 = hconcat(tDC, tDC)
    dc2 = hconcat(dc1, tDC)
    dc3 = hconcat(dc2, tDC)
    dc4 = hconcat(dc3, tDC)      # 15 cols
    DC = hconcat(dc4, c7)        # 16 cols

    # delta-rows (row % 3 == 0 is 7)
    tDR = vconcat(r7, vconcat(r0, r0))
    dr1 = vconcat(tDR, tDR)
    dr2 = vconcat(dr1, tDR)
    dr3 = vconcat(dr2, tDR)
    dr4 = vconcat(dr3, tDR)      # 15 rows
    DR = vconcat(dr4, r7)        # 16 rows

    # base patterns
    squares = cellwise(RS, CS, ZERO)    # 2x2 blocks
    vbars = cellwise(RS, DC, ZERO)      # vertical bars
    hbars = cellwise(DR, CS, ZERO)      # horizontal bars

    is_one = equality(accent, ONE)
    is_six = equality(accent, SIX)
    base = branch(is_one, vbars, branch(is_six, hbars, squares))

    # central cross of 9s, clipped to window
    # vertical segments at cols 6 and 9, rows 5..11
    vlines = combine(shoot(astuple(0, 6), DOWN), shoot(astuple(0, 9), DOWN))
    rowwin = backdrop(connect(astuple(5, 0), astuple(11, 15)))
    vseg = intersection(vlines, rowwin)

    # horizontal segments at rows 6 and 9, cols 5..10
    hlines = combine(shoot(astuple(6, 0), RIGHT), shoot(astuple(9, 0), RIGHT))
    colwin = backdrop(connect(astuple(0, 5), astuple(15, 10)))
    hseg = intersection(hlines, colwin)

    cross = combine(vseg, hseg)
    O = fill(base, NINE, cross)
    return O

def dsl2(I):
    # accent-driven base selection, with 9 painted only on background
    accent = leastcolor(I)

    r0 = canvas(ZERO, (1, 16))
    r7 = canvas(SEVEN, (1, 16))
    tR = vconcat(r0, vconcat(r7, r7))
    rr1 = vconcat(tR, tR)
    rr2 = vconcat(rr1, tR)
    rr3 = vconcat(rr2, tR)
    rr4 = vconcat(rr3, tR)
    RS = vconcat(rr4, r0)

    c0 = canvas(ZERO, (16, 1))
    c7 = canvas(SEVEN, (16, 1))
    tC = hconcat(c0, hconcat(c7, c7))
    cc1 = hconcat(tC, tC)
    cc2 = hconcat(cc1, tC)
    cc3 = hconcat(cc2, tC)
    cc4 = hconcat(cc3, tC)
    CS = hconcat(cc4, c0)

    tDC = hconcat(c7, hconcat(c0, c0))
    dc1 = hconcat(tDC, tDC)
    dc2 = hconcat(dc1, tDC)
    dc3 = hconcat(dc2, tDC)
    dc4 = hconcat(dc3, tDC)
    DC = hconcat(dc4, c7)

    tDR = vconcat(r7, vconcat(r0, r0))
    dr1 = vconcat(tDR, tDR)
    dr2 = vconcat(dr1, tDR)
    dr3 = vconcat(dr2, tDR)
    dr4 = vconcat(dr3, tDR)
    DR = vconcat(dr4, r7)

    squares = cellwise(RS, CS, ZERO)
    vbars = cellwise(RS, DC, ZERO)
    hbars = cellwise(DR, CS, ZERO)

    base0 = branch(equality(accent, THREE), squares, squares)
    base1 = branch(equality(accent, ONE), vbars, base0)
    base = branch(equality(accent, SIX), hbars, base1)

    vlines = combine(shoot(astuple(0, 6), DOWN), shoot(astuple(0, 9), DOWN))
    rowwin = backdrop(connect(astuple(5, 0), astuple(11, 15)))
    vseg = intersection(vlines, rowwin)

    hlines = combine(shoot(astuple(6, 0), RIGHT), shoot(astuple(9, 0), RIGHT))
    colwin = backdrop(connect(astuple(0, 5), astuple(15, 10)))
    hseg = intersection(hlines, colwin)

    cross = combine(vseg, hseg)
    bg = ofcolor(base, ZERO)
    p9 = intersection(cross, bg)
    O = fill(base, NINE, p9)
    return O

def dsl3(I):
    # start from squares, then morph orientation by intersecting with delta rows/cols
    accent = leastcolor(I)

    r0 = canvas(ZERO, (1, 16))
    r7 = canvas(SEVEN, (1, 16))
    tR = vconcat(r0, vconcat(r7, r7))
    rr1 = vconcat(tR, tR)
    rr2 = vconcat(rr1, tR)
    rr3 = vconcat(rr2, tR)
    rr4 = vconcat(rr3, tR)
    RS = vconcat(rr4, r0)

    c0 = canvas(ZERO, (16, 1))
    c7 = canvas(SEVEN, (16, 1))
    tC = hconcat(c0, hconcat(c7, c7))
    cc1 = hconcat(tC, tC)
    cc2 = hconcat(cc1, tC)
    cc3 = hconcat(cc2, tC)
    cc4 = hconcat(cc3, tC)
    CS = hconcat(cc4, c0)

    tDC = hconcat(c7, hconcat(c0, c0))
    dc1 = hconcat(tDC, tDC)
    dc2 = hconcat(dc1, tDC)
    dc3 = hconcat(dc2, tDC)
    dc4 = hconcat(dc3, tDC)
    DC = hconcat(dc4, c7)

    tDR = vconcat(r7, vconcat(r0, r0))
    dr1 = vconcat(tDR, tDR)
    dr2 = vconcat(dr1, tDR)
    dr3 = vconcat(dr2, tDR)
    dr4 = vconcat(dr3, tDR)
    DR = vconcat(dr4, r7)

    squares = cellwise(RS, CS, ZERO)
    # morph squares to desired orientation
    base_v = cellwise(squares, DC, ZERO)   # keep only cols %3==0 within squares -> vertical bars
    base_h = cellwise(DR, squares, ZERO)   # keep only rows %3==0 within squares -> horizontal bars
    base = branch(equality(accent, ONE), base_v, branch(equality(accent, SIX), base_h, squares))

    vlines = combine(shoot(astuple(0, 6), DOWN), shoot(astuple(0, 9), DOWN))
    rowwin = backdrop(connect(astuple(5, 0), astuple(11, 15)))
    vseg = intersection(vlines, rowwin)

    hlines = combine(shoot(astuple(6, 0), RIGHT), shoot(astuple(9, 0), RIGHT))
    colwin = backdrop(connect(astuple(0, 5), astuple(15, 10)))
    hseg = intersection(hlines, colwin)

    cross = combine(vseg, hseg)
    O = fill(base, NINE, cross)
    return O

def dsl4(I):
    # map accent to orientation (swap SIX/ONE vs dsl1), and draw a slightly fatter central window
    accent = leastcolor(I)

    r0 = canvas(ZERO, (1, 16))
    r7 = canvas(SEVEN, (1, 16))
    tR = vconcat(r0, vconcat(r7, r7))
    rr1 = vconcat(tR, tR)
    rr2 = vconcat(rr1, tR)
    rr3 = vconcat(rr2, tR)
    rr4 = vconcat(rr3, tR)
    RS = vconcat(rr4, r0)

    c0 = canvas(ZERO, (16, 1))
    c7 = canvas(SEVEN, (16, 1))
    tC = hconcat(c0, hconcat(c7, c7))
    cc1 = hconcat(tC, tC)
    cc2 = hconcat(cc1, tC)
    cc3 = hconcat(cc2, tC)
    cc4 = hconcat(cc3, tC)
    CS = hconcat(cc4, c0)

    tDC = hconcat(c7, hconcat(c0, c0))
    dc1 = hconcat(tDC, tDC)
    dc2 = hconcat(dc1, tDC)
    dc3 = hconcat(dc2, tDC)
    dc4 = hconcat(dc3, tDC)
    DC = hconcat(dc4, c7)

    tDR = vconcat(r7, vconcat(r0, r0))
    dr1 = vconcat(tDR, tDR)
    dr2 = vconcat(dr1, tDR)
    dr3 = vconcat(dr2, tDR)
    dr4 = vconcat(dr3, tDR)
    DR = vconcat(dr4, r7)

    squares = cellwise(RS, CS, ZERO)
    vbars = cellwise(RS, DC, ZERO)
    hbars = cellwise(DR, CS, ZERO)

    base = branch(equality(accent, SIX), vbars, branch(equality(accent, ONE), hbars, squares))

    vlines = combine(shoot(astuple(0, 6), DOWN), shoot(astuple(0, 9), DOWN))
    rowwin = backdrop(connect(astuple(5, 0), astuple(11, 15)))
    vseg = intersection(vlines, rowwin)

    hlines = combine(shoot(astuple(6, 0), RIGHT), shoot(astuple(9, 0), RIGHT))
    # slightly different horizontal clipping (rows same, cols 5..10 unchanged)
    colwin = backdrop(connect(astuple(0, 5), astuple(15, 10)))
    hseg = intersection(hlines, colwin)

    p9 = combine(vseg, hseg)
    O = fill(base, NINE, p9)
    return O

def dsl5(I):
    # boolean palette-based selection; overlay 9 only where base has ZERO
    has_one = contained(ONE, palette(I))
    has_six = contained(SIX, palette(I))

    r0 = canvas(ZERO, (1, 16))
    r7 = canvas(SEVEN, (1, 16))
    tR = vconcat(r0, vconcat(r7, r7))
    rr1 = vconcat(tR, tR)
    rr2 = vconcat(rr1, tR)
    rr3 = vconcat(rr2, tR)
    rr4 = vconcat(rr3, tR)
    RS = vconcat(rr4, r0)

    c0 = canvas(ZERO, (16, 1))
    c7 = canvas(SEVEN, (16, 1))
    tC = hconcat(c0, hconcat(c7, c7))
    cc1 = hconcat(tC, tC)
    cc2 = hconcat(cc1, tC)
    cc3 = hconcat(cc2, tC)
    cc4 = hconcat(cc3, tC)
    CS = hconcat(cc4, c0)

    tDC = hconcat(c7, hconcat(c0, c0))
    dc1 = hconcat(tDC, tDC)
    dc2 = hconcat(dc1, tDC)
    dc3 = hconcat(dc2, tDC)
    dc4 = hconcat(dc3, tDC)
    DC = hconcat(dc4, c7)

    tDR = vconcat(r7, vconcat(r0, r0))
    dr1 = vconcat(tDR, tDR)
    dr2 = vconcat(dr1, tDR)
    dr3 = vconcat(dr2, tDR)
    dr4 = vconcat(dr3, tDR)
    DR = vconcat(dr4, r7)

    squares = cellwise(RS, CS, ZERO)
    vbars = cellwise(RS, DC, ZERO)
    hbars = cellwise(DR, CS, ZERO)

    base_a = branch(has_one, vbars, squares)
    base = branch(has_six, hbars, base_a)

    vlines = combine(shoot(astuple(0, 6), DOWN), shoot(astuple(0, 9), DOWN))
    rowwin = backdrop(connect(astuple(5, 0), astuple(11, 15)))
    vseg = intersection(vlines, rowwin)

    hlines = combine(shoot(astuple(6, 0), RIGHT), shoot(astuple(9, 0), RIGHT))
    colwin = backdrop(connect(astuple(0, 5), astuple(15, 10)))
    hseg = intersection(hlines, colwin)

    cross = combine(vseg, hseg)
    bg = ofcolor(base, ZERO)
    p9 = intersection(cross, bg)
    O = fill(base, NINE, p9)
    return O
```