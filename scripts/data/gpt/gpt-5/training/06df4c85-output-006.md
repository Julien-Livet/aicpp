```python
def dsl1(I):
    # Global per-color hulls (excluding most frequent color and background), underpaint
    s = mostcolor(I)
    dims = shape(I)
    cols = remove(ZERO, remove(s, palette(I)))
    patches = apply(lbind(ofcolor, I), cols)
    objs = papply(recolor, cols, patches)
    rect = compose(backdrop, identity)
    can = compose(rbind(canvas, dims), color)
    mk = fork(toobject, rect, can)
    P = merge(apply(mk, objs))
    O = underpaint(I, P)
    return O

def dsl2(I):
    # Pairwise interior fill for same-colored aligned objects (horizontal or vertical), underpaint
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
    interior = compose(delta, compose(box, fork(combine, first, last)))
    can = compose(rbind(canvas, dims), compose(color, first))
    mk = fork(toobject, interior, can)
    P = merge(apply(mk, good))
    O = underpaint(I, P)
    return O

def dsl3(I):
    # Vertical bridging: full rectangle fill between vertically aligned same-colored pairs, underpaint
    s = mostcolor(I)
    dims = shape(I)
    objs = objects(I, T, F, T)
    fg = sfilter(objs, compose(flip, matcher(color, s)))
    pairs = product(fg, fg)
    same = fork(equality, compose(color, first), compose(color, last))
    vcond = fork(both, same, fork(vmatching, first, last))
    fill = compose(backdrop, fork(combine, first, last))
    can = compose(rbind(canvas, dims), compose(color, first))
    mk = fork(toobject, fill, can)
    P = merge(apply(mk, sfilter(pairs, vcond)))
    O = underpaint(I, P)
    return O

def dsl4(I):
    # Geometric line connections: connect centers of aligned same-colored pairs, underpaint
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
    seg = fork(connect, compose(centerofmass, first), compose(centerofmass, last))
    can = compose(rbind(canvas, dims), compose(color, first))
    mk = fork(toobject, seg, can)
    P = merge(apply(mk, good))
    O = underpaint(I, P)
    return O

def dsl5(I):
    # Two-pass bridging: vertical rectangles then horizontal rectangles, both underpaint
    dims = shape(I)
    s0 = mostcolor(I)
    objs0 = objects(I, T, F, T)
    fg0 = sfilter(objs0, compose(flip, matcher(color, s0)))
    pairs0 = product(fg0, fg0)
    same0 = fork(equality, compose(color, first), compose(color, last))
    vcond0 = fork(both, same0, fork(vmatching, first, last))
    vfill = compose(backdrop, fork(combine, first, last))
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
    hfill = compose(backdrop, fork(combine, first, last))
    canH = compose(rbind(canvas, dims), compose(color, first))
    mkH = fork(toobject, hfill, canH)
    P2 = merge(apply(mkH, sfilter(pairs1, hcond1)))
    O = underpaint(O1, P2)
    return O
```