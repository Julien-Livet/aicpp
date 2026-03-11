```python
def dsl1(I):
    # Global bbox of all non-background; frame with most frequent non-bg; fill with 2nd-most, then restore dominant inside as corridors
    sh = shape(I)
    P = remove(EIGHT, palette(I))
    c1 = valmax(P, lbind(colorcount, I))  # dominant non-bg
    P2 = remove(c1, P)
    c2 = branch(greater(size(P2), ZERO), valmax(P2, lbind(colorcount, I)), c1)  # 2nd-most non-bg
    nb = difference(asindices(I), ofcolor(I, EIGHT))
    bb = backdrop(nb)
    brd = box(bb)
    inn = difference(bb, brd)
    O0 = canvas(EIGHT, sh)
    O1 = fill(O0, c1, brd)
    O2 = fill(O1, c2, inn)
    dom_inside = intersection(ofcolor(I, c1), inn)
    O3 = fill(O2, c1, dom_inside)
    return O3

def dsl2(I):
    # Draw separate rectangles around each non-dominant color at their original locations; border=dominant color; interior=that color
    sh = shape(I)
    P = remove(EIGHT, palette(I))
    cframe = valmax(P, lbind(colorcount, I))
    Pn = remove(cframe, P)
    cA = branch(greater(size(Pn), ZERO), valmax(Pn, lbind(colorcount, I)), cframe)
    Pn2 = remove(cA, Pn)
    cB = branch(greater(size(Pn2), ZERO), valmax(Pn2, lbind(colorcount, I)), cA)
    O = canvas(EIGHT, sh)
    iA = ofcolor(I, cA)
    bbA = backdrop(iA)
    brdA = box(bbA)
    innA = difference(bbA, brdA)
    O = fill(O, cframe, brdA)
    O = fill(O, cA, innA)
    iB = ofcolor(I, cB)
    bbB = backdrop(iB)
    brdB = box(bbB)
    innB = difference(bbB, brdB)
    O = fill(O, cframe, brdB)
    O = fill(O, cB, innB)
    return O

def dsl3(I):
    # Keep only top-2 non-bg colors in place and frame their combined bbox with the dominant color
    sh = shape(I)
    P = remove(EIGHT, palette(I))
    c1 = valmax(P, lbind(colorcount, I))
    P2 = remove(c1, P)
    c2 = branch(greater(size(P2), ZERO), valmax(P2, lbind(colorcount, I)), c1)
    idx1 = ofcolor(I, c1)
    idx2 = ofcolor(I, c2)
    idx12 = combine(idx1, idx2)
    bb = backdrop(idx12)
    brd = box(bb)
    O0 = canvas(EIGHT, sh)
    O1 = fill(O0, c1, idx1)
    O2 = fill(O1, c2, idx2)
    O3 = fill(O2, c1, brd)
    return O3

def dsl4(I):
    # Frame the two largest objects (by size) with a common frame color (global dominant non-bg), interior filled by each object's color
    sh = shape(I)
    OB = objects(I, T, F, T)
    o1 = argmax(OB, size)
    rem = remove(o1, OB)
    o2 = branch(greater(size(rem), ZERO), argmax(rem, size), o1)
    cframe = valmax(remove(EIGHT, palette(I)), lbind(colorcount, I))
    # First object rectangle
    bb1 = backdrop(toindices(o1))
    brd1 = box(bb1)
    inn1 = difference(bb1, brd1)
    col1 = color(o1)
    # Second object rectangle
    bb2 = backdrop(toindices(o2))
    brd2 = box(bb2)
    inn2 = difference(bb2, brd2)
    col2 = color(o2)
    O = canvas(EIGHT, sh)
    O = fill(O, cframe, brd1)
    O = fill(O, col1, inn1)
    O = fill(O, cframe, brd2)
    O = fill(O, col2, inn2)
    return O

def dsl5(I):
    # Global framed region: fill interior with dominant non-bg; then project second-most color from original as interior accents
    sh = shape(I)
    P = remove(EIGHT, palette(I))
    c1 = valmax(P, lbind(colorcount, I))
    P2 = remove(c1, P)
    c2 = branch(greater(size(P2), ZERO), valmax(P2, lbind(colorcount, I)), c1)
    nb = difference(asindices(I), ofcolor(I, EIGHT))
    bb = backdrop(nb)
    brd = box(bb)
    inn = difference(bb, brd)
    O0 = canvas(EIGHT, sh)
    O1 = fill(O0, c1, brd)
    O2 = fill(O1, c1, inn)
    accents = intersection(ofcolor(I, c2), inn)
    O3 = fill(O2, c2, accents)
    return O3
```