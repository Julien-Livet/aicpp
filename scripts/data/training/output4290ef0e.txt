```python
def dsl1(I):
    # Concentric rings without cross; ring order by topmost occurrence (outermost = highest color)
    g = I
    bg = mostcolor(g)
    cols = palette(g)
    nonbg = remove(bg, cols)
    nnb = size(nonbg)
    side = branch(greater(nnb, THREE), add(double(FIVE), ONE), add(double(THREE), ONE))  # 11 if many colors, else 7
    dims = astuple(side, side)
    base = canvas(bg, dims)
    full = asobject(canvas(ONE, dims))

    # frames
    r0 = box(full)
    i1 = inbox(full);  r1 = box(i1)
    i2 = inbox(i1);    r2 = box(i2)
    i3 = inbox(i2);    r3 = box(i3)
    i4 = inbox(i3);    r4 = box(i4)

    # center color: singleton non-bg if exists else background
    cnt = lbind(colorcount, g)
    cenCand = valmin(nonbg, cnt)
    sc = colorcount(g, cenCand)
    single = equality(sc, ONE)
    cen = branch(single, cenCand, bg)

    # ring colors from remaining non-bg (remove center if singleton)
    rset = branch(single, remove(cenCand, nonbg), nonbg)
    ordf = compose(uppermost, lbind(ofcolor, g))

    # safe iterative selection with fallbacks
    c1 = valmin(rset, ordf)
    s1 = remove(c1, rset)
    c2 = branch(equality(size(s1), ZERO), c1, valmin(s1, ordf))
    s2 = remove(c2, s1)
    c3 = branch(equality(size(s2), ZERO), c2, valmin(s2, ordf))
    s3 = remove(c3, s2)
    c4 = branch(equality(size(s3), ZERO), c3, valmin(s3, ordf))
    s4 = remove(c4, s3)
    c5 = branch(equality(size(s4), ZERO), c4, valmin(s4, ordf))

    # paint rings (7x7 uses 3, 11x11 uses 5)
    out = fill(base, c1, r0)
    out = fill(out,  c2, r1)
    out = fill(out,  c3, r2)
    big = greater(nnb, THREE)
    out = branch(big, fill(fill(out, c4, r3), c5, r4), out)

    # center point
    ctr = center(full)
    cp = connect(ctr, ctr)
    O = fill(out, cen, cp)
    return O

def dsl2(I):
    # Concentric rings with cross cut to background except innermost; order by leftmost occurrence
    g = I
    bg = mostcolor(g)
    cols = palette(g)
    nonbg = remove(bg, cols)
    nnb = size(nonbg)
    side = branch(greater(nnb, THREE), add(double(FIVE), ONE), add(double(THREE), ONE))
    dims = astuple(side, side)
    base = canvas(bg, dims)
    full = asobject(canvas(ONE, dims))

    r0 = box(full)
    i1 = inbox(full);  r1 = box(i1)
    i2 = inbox(i1);    r2 = box(i2)
    i3 = inbox(i2);    r3 = box(i3)
    i4 = inbox(i3);    r4 = box(i4)

    cnt = lbind(colorcount, g)
    cenCand = valmin(nonbg, cnt)
    sc = colorcount(g, cenCand)
    cen = branch(equality(sc, ONE), cenCand, bg)

    rset = branch(equality(sc, ONE), remove(cenCand, nonbg), nonbg)
    ordf = compose(leftmost, lbind(ofcolor, g))

    c1 = valmin(rset, ordf)
    s1 = remove(c1, rset)
    c2 = branch(equality(size(s1), ZERO), c1, valmin(s1, ordf))
    s2 = remove(c2, s1)
    c3 = branch(equality(size(s2), ZERO), c2, valmin(s2, ordf))
    s3 = remove(c3, s2)
    c4 = branch(equality(size(s3), ZERO), c3, valmin(s3, ordf))
    s4 = remove(c4, s3)
    c5 = branch(equality(size(s4), ZERO), c4, valmin(s4, ordf))

    ctr = center(full)
    cross = combine(hfrontier(ctr), vfrontier(ctr))
    # remove cross from all but innermost frame
    p0 = difference(r0, cross)
    p1 = difference(r1, cross)
    p2 = r2
    p3 = r3
    p4 = r4

    out = fill(base, c1, p0)
    out = fill(out,  c2, p1)
    out = fill(out,  c3, p2)
    big = greater(nnb, THREE)
    out = branch(big, fill(fill(out, c4, p3), c5, p4), out)

    cp = connect(ctr, ctr)
    O = fill(out, cen, cp)
    return O

def dsl3(I):
    # Rings ordered by frequency ascending (outer=rarest, inner=most); full cross to background
    g = I
    bg = mostcolor(g)
    cols = palette(g)
    nonbg = remove(bg, cols)
    nnb = size(nonbg)
    side = branch(greater(nnb, THREE), add(double(FIVE), ONE), add(double(THREE), ONE))
    dims = astuple(side, side)
    base = canvas(bg, dims)
    full = asobject(canvas(ONE, dims))

    r0 = box(full)
    i1 = inbox(full);  r1 = box(i1)
    i2 = inbox(i1);    r2 = box(i2)
    i3 = inbox(i2);    r3 = box(i3)
    i4 = inbox(i3);    r4 = box(i4)

    cnt = lbind(colorcount, g)
    cenCand = valmin(nonbg, cnt)
    sc = colorcount(g, cenCand)
    cen = branch(equality(sc, ONE), cenCand, bg)
    rset = branch(equality(sc, ONE), remove(cenCand, nonbg), nonbg)

    # ascending by frequency
    c1 = valmin(rset, cnt)
    s1 = remove(c1, rset)
    c2 = branch(equality(size(s1), ZERO), c1, valmin(s1, cnt))
    s2 = remove(c2, s1)
    c3 = branch(equality(size(s2), ZERO), c2, valmin(s2, cnt))
    s3 = remove(c3, s2)
    c4 = branch(equality(size(s3), ZERO), c3, valmin(s3, cnt))
    s4 = remove(c4, s3)
    c5 = branch(equality(size(s4), ZERO), c4, valmin(s4, cnt))

    ctr = center(full)
    cross = combine(hfrontier(ctr), vfrontier(ctr))
    p0 = difference(r0, cross)
    p1 = difference(r1, cross)
    p2 = difference(r2, cross)
    p3 = difference(r3, cross)
    p4 = difference(r4, cross)

    out = fill(base, c1, p0)
    out = fill(out,  c2, p1)
    out = fill(out,  c3, p2)
    big = greater(nnb, THREE)
    out = branch(big, fill(fill(out, c4, p3), c5, p4), out)

    cp = connect(ctr, ctr)
    O = fill(out, cen, cp)
    return O

def dsl4(I):
    # Corner-marked frames only; colors ordered by bottommost occurrence (outer=lowest)
    g = I
    bg = mostcolor(g)
    cols = palette(g)
    nonbg = remove(bg, cols)
    nnb = size(nonbg)
    side = branch(greater(nnb, THREE), add(double(FIVE), ONE), add(double(THREE), ONE))
    dims = astuple(side, side)
    base = canvas(bg, dims)
    full = asobject(canvas(ONE, dims))

    r0 = corners(full)
    i1 = inbox(full);  r1 = corners(i1)
    i2 = inbox(i1);    r2 = corners(i2)
    i3 = inbox(i2);    r3 = corners(i3)
    i4 = inbox(i3);    r4 = corners(i4)

    cnt = lbind(colorcount, g)
    cenCand = valmin(nonbg, cnt)
    sc = colorcount(g, cenCand)
    cen = branch(equality(sc, ONE), cenCand, bg)
    rset = branch(equality(sc, ONE), remove(cenCand, nonbg), nonbg)

    ordf = compose(lowermost, lbind(ofcolor, g))
    c1 = valmin(rset, ordf)
    s1 = remove(c1, rset)
    c2 = branch(equality(size(s1), ZERO), c1, valmin(s1, ordf))
    s2 = remove(c2, s1)
    c3 = branch(equality(size(s2), ZERO), c2, valmin(s2, ordf))
    s3 = remove(c3, s2)
    c4 = branch(equality(size(s3), ZERO), c3, valmin(s3, ordf))
    s4 = remove(c4, s3)
    c5 = branch(equality(size(s4), ZERO), c4, valmin(s4, ordf))

    out = fill(base, c1, r0)
    out = fill(out,  c2, r1)
    out = fill(out,  c3, r2)
    big = greater(nnb, THREE)
    out = branch(big, fill(fill(out, c4, r3), c5, r4), out)

    ctr = center(full)
    cp = connect(ctr, ctr)
    O = fill(out, cen, cp)
    return O

def dsl5(I):
    # Concentric rings with full cross; ring order by rightmost occurrence (outer=rightmost), center = most common non-bg
    g = I
    bg = mostcolor(g)
    cols = palette(g)
    nonbg = remove(bg, cols)
    nnb = size(nonbg)
    side = branch(greater(nnb, THREE), add(double(FIVE), ONE), add(double(THREE), ONE))
    dims = astuple(side, side)
    base = canvas(bg, dims)
    full = asobject(canvas(ONE, dims))

    r0 = box(full)
    i1 = inbox(full);  r1 = box(i1)
    i2 = inbox(i1);    r2 = box(i2)
    i3 = inbox(i2);    r3 = box(i3)
    i4 = inbox(i3);    r4 = box(i4)

    cnt = lbind(colorcount, g)
    cen = valmax(nonbg, cnt)
    rset = remove(cen, nonbg)

    ordf = compose(rightmost, lbind(ofcolor, g))
    c1 = valmax(rset, ordf)
    s1 = remove(c1, rset)
    c2 = branch(equality(size(s1), ZERO), c1, valmax(s1, ordf))
    s2 = remove(c2, s1)
    c3 = branch(equality(size(s2), ZERO), c2, valmax(s2, ordf))
    s3 = remove(c3, s2)
    c4 = branch(equality(size(s3), ZERO), c3, valmax(s3, ordf))
    s4 = remove(c4, s3)
    c5 = branch(equality(size(s4), ZERO), c4, valmax(s4, ordf))

    ctr = center(full)
    cross = combine(hfrontier(ctr), vfrontier(ctr))

    p0 = difference(r0, cross)
    p1 = difference(r1, cross)
    p2 = difference(r2, cross)
    p3 = difference(r3, cross)
    p4 = difference(r4, cross)

    out = fill(base, c1, p0)
    out = fill(out,  c2, p1)
    out = fill(out,  c3, p2)
    big = greater(nnb, THREE)
    out = branch(big, fill(fill(out, c4, p3), c5, p4), out)

    cp = connect(ctr, ctr)
    O = fill(out, cen, cp)
    return O
```