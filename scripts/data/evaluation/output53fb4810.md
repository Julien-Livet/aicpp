```python
def dsl1(I):
    # Orientation-aware column fill to the lowest non-8 in each involved column; preserve 1s.
    l4 = first(ofcolor(I, FOUR))
    adj2 = first(intersection(neighbors(l4), ofcolor(I, TWO)))
    ones = ofcolor(I, ONE)
    non8 = difference(asindices(I), ofcolor(I, EIGHT))

    isvert = vmatching(initset(l4), initset(adj2))

    c4 = vfrontier(l4)
    c4_non8 = intersection(c4, non8)
    top4 = ulcorner(c4)
    bot4 = llcorner(c4_non8)
    seg4 = connect(top4, bot4)

    O = fill(I, FOUR, difference(seg4, ones))

    if not isvert:
        c2 = vfrontier(adj2)
        c2_non8 = intersection(c2, non8)
        top2 = ulcorner(c2)
        bot2 = llcorner(c2_non8)
        seg2 = connect(top2, bot2)
        O = fill(O, TWO, difference(seg2, ones))
    return O

def dsl2(I):
    # Full-height column fill (from top to bottom of grid) in the columns of the discovered pair; preserve 1s.
    l4 = first(ofcolor(I, FOUR))
    adj2 = first(intersection(neighbors(l4), ofcolor(I, TWO)))
    ones = ofcolor(I, ONE)
    isvert = vmatching(initset(l4), initset(adj2))

    c4 = vfrontier(l4)
    seg4 = connect(ulcorner(c4), llcorner(c4))
    O = fill(I, FOUR, difference(seg4, ones))

    if not isvert:
        c2 = vfrontier(adj2)
        seg2 = connect(ulcorner(c2), llcorner(c2))
        O = fill(O, TWO, difference(seg2, ones))
    return O

def dsl3(I):
    # Upward-only propagation: fill from top down to the first non-8 encountered (per involved column); preserve 1s.
    l4 = first(ofcolor(I, FOUR))
    adj2 = first(intersection(neighbors(l4), ofcolor(I, TWO)))
    ones = ofcolor(I, ONE)
    non8 = difference(asindices(I), ofcolor(I, EIGHT))
    isvert = vmatching(initset(l4), initset(adj2))

    c4 = vfrontier(l4)
    c4_non8 = intersection(c4, non8)
    top4 = ulcorner(c4)
    upstop4 = ulcorner(c4_non8)
    seg4 = connect(top4, upstop4)
    O = fill(I, FOUR, difference(seg4, ones))

    if not isvert:
        c2 = vfrontier(adj2)
        c2_non8 = intersection(c2, non8)
        top2 = ulcorner(c2)
        upstop2 = ulcorner(c2_non8)
        seg2 = connect(top2, upstop2)
        O = fill(O, TWO, difference(seg2, ones))
    return O

def dsl4(I):
    # Recolor existing 2s in the 4's column to 4; if horizontal pair, also paint the 2's column fully; preserve 1s.
    l4 = first(ofcolor(I, FOUR))
    adj2 = first(intersection(neighbors(l4), ofcolor(I, TWO)))
    ones = ofcolor(I, ONE)
    non8 = difference(asindices(I), ofcolor(I, EIGHT))
    isvert = vmatching(initset(l4), initset(adj2))

    c4 = vfrontier(l4)
    # Turn existing 2s in this column into 4s
    twos_in_c4 = intersection(c4, ofcolor(I, TWO))
    O = fill(I, FOUR, difference(twos_in_c4, ones))

    if not isvert:
        # For horizontal pair, also fill the 2's column down to its lowest non-8
        c2 = vfrontier(adj2)
        c2_non8 = intersection(c2, non8)
        seg2 = connect(ulcorner(c2), llcorner(c2_non8))
        O = fill(O, TWO, difference(seg2, ones))
    return O

def dsl5(I):
    # Stop at 1-barriers: extend only to the lowest 1 in each involved column (or full column if none).
    l4 = first(ofcolor(I, FOUR))
    adj2 = first(intersection(neighbors(l4), ofcolor(I, TWO)))
    ones = ofcolor(I, ONE)
    isvert = vmatching(initset(l4), initset(adj2))

    c4 = vfrontier(l4)
    o4 = intersection(c4, ones)
    top4 = ulcorner(c4)
    bot4 = branch(greater(size(o4), ZERO), llcorner(o4), llcorner(c4))
    seg4 = connect(top4, bot4)
    O = fill(I, FOUR, difference(seg4, ones))

    if not isvert:
        c2 = vfrontier(adj2)
        o2 = intersection(c2, ones)
        top2 = ulcorner(c2)
        bot2 = branch(greater(size(o2), ZERO), llcorner(o2), llcorner(c2))
        seg2 = connect(top2, bot2)
        O = fill(O, TWO, difference(seg2, ones))
    return O
```