```python
def dsl1(I):
    # Align blue (2) flush to red (5) along the axis where they already share rows/columns; then mirror 2 to make 5.
    objs = objects(I, T, F, T)
    t = first(colorfilter(objs, TWO))
    f = first(colorfilter(objs, FIVE))
    p2 = toindices(t)
    pf = toindices(f)
    isH = hmatching(p2, pf)
    # horizontal offsets (place p2 just left/right of pf)
    goR = greater(leftmost(pf), rightmost(p2))
    goL = greater(leftmost(p2), rightmost(pf))
    dxR = subtract(subtract(leftmost(pf), ONE), rightmost(p2))         # pf.left - 1 - p2.right
    dxL = subtract(add(rightmost(pf), ONE), leftmost(p2))              # pf.right + 1 - p2.left (negative)
    offH = branch(goR, astuple(ZERO, dxR),
            branch(goL, astuple(ZERO, dxL), astuple(ZERO, ZERO)))
    # vertical offsets (place p2 just above/below pf)
    goD = greater(uppermost(pf), lowermost(p2))
    goU = greater(uppermost(p2), lowermost(pf))
    dyD = subtract(subtract(uppermost(pf), ONE), lowermost(p2))        # pf.top - 1 - p2.bottom
    dyU = subtract(add(lowermost(pf), ONE), uppermost(p2))             # pf.bottom + 1 - p2.top (negative)
    offV = branch(goD, astuple(dyD, ZERO),
            branch(goU, astuple(dyU, ZERO), astuple(ZERO, ZERO)))
    off = branch(isH, offH, offV)
    p2m = shift(p2, off)
    w = width(p2m)
    h = height(p2m)
    p5hR = shift(vmirror(p2m), astuple(ZERO, w))
    p5hL = shift(vmirror(p2m), astuple(ZERO, invert(w)))
    p5vD = shift(hmirror(p2m), astuple(h, ZERO))
    p5vU = shift(hmirror(p2m), astuple(invert(h), ZERO))
    p5 = branch(isH, branch(goR, p5hR, p5hL), branch(goD, p5vD, p5vU))
    base = canvas(SEVEN, shape(I))
    O1 = paint(base, recolor(TWO, p2m))
    O = paint(O1, recolor(FIVE, p5))
    return O

def dsl2(I):
    # Choose the smaller of horizontal vs vertical moves to make p2 adjacent to pf; then mirror across the contact frontier.
    objs = objects(I, T, F, T)
    t = first(colorfilter(objs, TWO))
    f = first(colorfilter(objs, FIVE))
    p2 = toindices(t)
    pf = toindices(f)
    goR = greater(leftmost(pf), rightmost(p2))
    goL = greater(leftmost(p2), rightmost(pf))
    dxR = subtract(subtract(leftmost(pf), ONE), rightmost(p2))
    dxL = subtract(add(rightmost(pf), ONE), leftmost(p2))  # negative
    sH = branch(goR, dxR, invert(dxL))  # positive magnitude
    goD = greater(uppermost(pf), lowermost(p2))
    goU = greater(uppermost(p2), lowermost(pf))
    dyD = subtract(subtract(uppermost(pf), ONE), lowermost(p2))
    dyU = subtract(add(lowermost(pf), ONE), uppermost(p2))  # negative
    sV = branch(goD, dyD, invert(dyU))  # positive magnitude
    isH = flip(greater(sV, sH))  # pick axis with smaller required move (tie -> horizontal)
    offH = branch(goR, astuple(ZERO, dxR),
           branch(goL, astuple(ZERO, dxL), astuple(ZERO, ZERO)))
    offV = branch(goD, astuple(dyD, ZERO),
           branch(goU, astuple(dyU, ZERO), astuple(ZERO, ZERO)))
    off = branch(isH, offH, offV)
    p2m = shift(p2, off)
    w = width(p2m)
    h = height(p2m)
    p5hR = shift(vmirror(p2m), astuple(ZERO, w))
    p5hL = shift(vmirror(p2m), astuple(ZERO, invert(w)))
    p5vD = shift(hmirror(p2m), astuple(h, ZERO))
    p5vU = shift(hmirror(p2m), astuple(invert(h), ZERO))
    # use original direction choice to place mirror
    p5 = branch(isH, branch(goR, p5hR, p5hL), branch(goD, p5vD, p5vU))
    base = canvas(SEVEN, shape(I))
    O1 = paint(base, recolor(TWO, p2m))
    O = paint(O1, recolor(FIVE, p5))
    return O

def dsl3(I):
    # Use center-of-mass to pick side; align p2 exactly flush to that side; mirror across the shared edge.
    objs = objects(I, T, F, T)
    t = first(colorfilter(objs, TWO))
    f = first(colorfilter(objs, FIVE))
    p2 = toindices(t)
    pf = toindices(f)
    d = sign(subtract(centerofmass(pf), centerofmass(p2)))
    isR = equality(d, RIGHT)
    isL = equality(d, LEFT)
    isD = equality(d, DOWN)
    # precise edge-to-edge offset to become adjacent
    dxR = subtract(subtract(leftmost(pf), ONE), rightmost(p2))
    dxL = subtract(add(rightmost(pf), ONE), leftmost(p2))
    dyD = subtract(subtract(uppermost(pf), ONE), lowermost(p2))
    dyU = subtract(add(lowermost(pf), ONE), uppermost(p2))
    off = branch(isR, astuple(ZERO, dxR),
          branch(isL, astuple(ZERO, dxL),
          branch(isD, astuple(dyD, ZERO), astuple(dyU, ZERO))))
    p2m = shift(p2, off)
    w = width(p2m)
    h = height(p2m)
    p5hR = shift(vmirror(p2m), astuple(ZERO, w))
    p5hL = shift(vmirror(p2m), astuple(ZERO, invert(w)))
    p5vD = shift(hmirror(p2m), astuple(h, ZERO))
    p5vU = shift(hmirror(p2m), astuple(invert(h), ZERO))
    p5 = branch(isR, p5hR, branch(isL, p5hL, branch(isD, p5vD, p5vU)))
    base = canvas(SEVEN, shape(I))
    O1 = paint(base, recolor(TWO, p2m))
    O = paint(O1, recolor(FIVE, p5))
    return O

def dsl4(I):
    # Snap p2 to the nearest side of pf by targeting exact edge coordinates; reflect p2 to form p5.
    objs = objects(I, T, F, T)
    t = first(colorfilter(objs, TWO))
    f = first(colorfilter(objs, FIVE))
    p2 = toindices(t)
    pf = toindices(f)
    # Which side is closer: compare horizontal vs vertical needed shifts
    dxR = subtract(subtract(leftmost(pf), ONE), rightmost(p2))
    dxL = subtract(add(rightmost(pf), ONE), leftmost(p2))
    sH = branch(greater(ZERO, dxR), invert(dxL), dxR)  # if dxR<0 use |dxL| else |dxR|
    dyD = subtract(subtract(uppermost(pf), ONE), lowermost(p2))
    dyU = subtract(add(lowermost(pf), ONE), uppermost(p2))
    sV = branch(greater(ZERO, dyD), invert(dyU), dyD)
    isH = flip(greater(sV, sH))
    goR = greater(leftmost(pf), rightmost(p2))
    goD = greater(uppermost(pf), lowermost(p2))
    offH = branch(goR, astuple(ZERO, dxR), astuple(ZERO, dxL))
    offV = branch(goD, astuple(dyD, ZERO), astuple(dyU, ZERO))
    off = branch(isH, offH, offV)
    p2m = shift(p2, off)
    w = width(p2m)
    h = height(p2m)
    p5h = shift(vmirror(p2m), astuple(ZERO, branch(goR, w, invert(w))))
    p5v = shift(hmirror(p2m), astuple(branch(goD, h, invert(h)), ZERO))
    p5 = branch(isH, p5h, p5v)
    base = canvas(SEVEN, shape(I))
    O1 = paint(base, recolor(TWO, p2m))
    O = paint(O1, recolor(FIVE, p5))
    return O

def dsl5(I):
    # Use bounding-box contact: place p2 so its bbox edge equals pf bbox edge ±1; then mirror across that contacted edge.
    objs = objects(I, T, F, T)
    t = first(colorfilter(objs, TWO))
    f = first(colorfilter(objs, FIVE))
    p2 = toindices(t)
    pf = toindices(f)
    # Decide contact axis by overlap (rows -> horizontal contact, else vertical)
    isH = hmatching(backdrop(p2), backdrop(pf))
    # compute exact snap-to-edge offsets
    trgR = subtract(leftmost(pf), ONE)
    dxR = subtract(trgR, rightmost(p2))
    trgL = add(rightmost(pf), ONE)
    dxL = subtract(trgL, leftmost(p2))
    offH = branch(greater(leftmost(pf), rightmost(p2)), astuple(ZERO, dxR), astuple(ZERO, dxL))
    trgD = subtract(uppermost(pf), ONE)
    dyD = subtract(trgD, lowermost(p2))
    trgU = add(lowermost(pf), ONE)
    dyU = subtract(trgU, uppermost(p2))
    offV = branch(greater(uppermost(pf), lowermost(p2)), astuple(dyD, ZERO), astuple(dyU, ZERO))
    off = branch(isH, offH, offV)
    p2m = shift(p2, off)
    w = width(p2m)
    h = height(p2m)
    p5h = shift(vmirror(p2m), astuple(ZERO, branch(greater(leftmost(pf), rightmost(p2)), w, invert(w))))
    p5v = shift(hmirror(p2m), astuple(branch(greater(uppermost(pf), lowermost(p2)), h, invert(h)), ZERO))
    p5 = branch(isH, p5h, p5v)
    base = canvas(SEVEN, shape(I))
    O1 = paint(base, recolor(TWO, p2m))
    O = paint(O1, recolor(FIVE, p5))
    return O
```