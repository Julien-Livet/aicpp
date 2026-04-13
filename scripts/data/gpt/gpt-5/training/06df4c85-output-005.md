```python
def dsl1(I):
    # Global per-color hulls: fill bounding rectangles of each non-background color
    s = mostcolor(I)
    dims = shape(I)
    cols = remove(s, palette(I))
    patches = apply(rbind(ofcolor, I), cols)
    objs = papply(recolor, cols, patches)
    rect = compose(backdrop, identity)
    can = compose(rbind(canvas, dims), color)
    mk = fork(toobject, rect, can)
    P = merge(apply(mk, objs))
    O = underpaint(I, P)
    return O

def dsl2(I):
    # Object extraction by color groups: interior rectangles for aligned pairs per color
    s = mostcolor(I)
    dims = shape(I)
    objs = objects(I, T, F, T)
    fg = sfilter(objs, compose(flip, matcher(color, s)))
    cols = apply(color, fg)
    groups = apply(lbind(colorfilter, fg), cols)
    pairsF = fork(product, identity, identity)
    same = fork(equality, compose(color, first), compose(color, last))
    hA = fork(hmatching, first, last)
    vA = fork(vmatching, first, last)
    aligned = fork(either, hA, vA)
    cond = fork(both, same, aligned)
    filtPairs = compose(rbind(sfilter, cond), pairsF)
    interior = compose(delta, compose(box, fork(combine, first, last)))
    can = compose(rbind(canvas, dims), compose(color, first))
    mk = fork(toobject, interior, can)
    perGroup = compose(merge, compose(lbind(apply, mk), filtPairs))
    P = merge(apply(perGroup, groups))
    O = underpaint(I, P)
    return O

def dsl3(I):
    # Geometric two-pass: vertical interior fill then horizontal full rectangles
    dims = shape(I)
    s0 = mostcolor(I)
    objs0 = objects(I, T, F, T)
    fg0 = sfilter(objs0, compose(flip, matcher(color, s0)))
    pairs0 = product(fg0, fg0)
    same0 = fork(equality, compose(color, first), compose(color, last))
    vcond0 = fork(both, same0, fork(vmatching, first, last))
    vfill = compose(delta, compose(box, fork(combine, first, last)))
    canV = compose(rbind(canvas, dims), compose(color, first))
    mkV = fork(toobject, vfill, canV)
    P1 = merge(apply(mkV, sfilter(pairs0, vcond0)))
    O1 = underpaint(I, P1)
    s1 = mostcolor(O1)
    objs1 = objects(O1, T, F, T)
    fg1 = sfilter(objs1, compose(flip, matcher(color, s1)))
    pairs1 = product(fg1, fg1)
    same1 = fork(equality, compose(color, first), compose(color, last))
    hcond1 = fork(both, same1, fork(hmatching, first, last))
    href = compose(backdrop, fork(combine, first, last))
    canH = compose(rbind(canvas, dims), compose(color, first))
    mkH = fork(toobject, href, canH)
    P2 = merge(apply(mkH, sfilter(pairs1, hcond1)))
    O = underpaint(O1, P2)
    return O

def dsl4(I):
    # Geometric line-bridging: connect centers of aligned same-colored objects
    dims = shape(I)
    s = mostcolor(I)
    objs = objects(I, T, F, T)
    fg = sfilter(objs, compose(flip, matcher(color, s)))
    pairs = product(fg, fg)
    same = fork(equality, compose(color, first), compose(color, last))
    hA = fork(hmatching, first, last)
    vA = fork(vmatching, first, last)
    aligned = fork(either, hA, vA)
    good = sfilter(pairs, fork(both, same, aligned))
    line = fork(connect, compose(centerofmass, first), compose(centerofmass, last))
    can = compose(rbind(canvas, dims), compose(color, first))
    mk = fork(toobject, line, can)
    P = merge(apply(mk, good))
    O = underpaint(I, P)
    return O

def dsl5(I):
    # Relational outlines: draw only the rectangle outlines for aligned same-colored pairs
    s = mostcolor(I)
    dims = shape(I)
    objs = objects(I, T, F, T)
    fg = sfilter(objs, compose(flip, matcher(color, s)))
    pairs = product(fg, fg)
    same = fork(equality, compose(color, first), compose(color, last))
    hA = fork(hmatching, first, last)
    vA = fork(vmatching, first, last)
    aligned = fork(either, hA, vA)
    good = sfilter(pairs, fork(both, same, aligned))
    outline = compose(box, fork(combine, first, last))
    can = compose(rbind(canvas, shape(I)), compose(color, first))
    mk = fork(toobject, outline, can)
    P = merge(apply(mk, good))
    O = underpaint(I, P)
    return O
```