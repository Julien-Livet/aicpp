```python
def dsl1(I):
    # Bridge only gaps of exact length 2 (distance 3) between same-colored cells (rows/columns), across the whole grid, using the singleton/least color
    s = leastcolor(I)
    pals = palette(I)
    colors = remove(ZERO, remove(s, pals))
    def lines_for_c(c):
        idxs = ofcolor(I, c)
        pairs = product(idxs, idxs)
        p1 = compose(initset, first)
        p2 = compose(initset, last)
        aligned = fork(either, fork(hmatching, p1, p2), fork(vmatching, p1, p2))
        noteq = compose(flip, fork(equality, first, last))
        dist = fork(manhattan, p1, p2)
        eq3 = compose(rbind(equality, THREE), dist)
        seg = fork(connect, first, last)
        sel = sfilter(pairs, fork(both, fork(both, aligned, noteq), eq3))
        segs = apply(seg, sel)
        return merge(segs)
    lines = mapply(lines_for_c, colors)
    O = underfill(I, s, lines)
    return O

def dsl2(I):
    # Like dsl1 but explicitly require the two in-between cells to be empty (background) before bridging
    s = leastcolor(I)
    fg = difference(asindices(I), ofcolor(I, ZERO))
    colors = remove(ZERO, remove(s, palette(I)))
    p1 = compose(initset, first)
    p2 = compose(initset, last)
    aligned = fork(either, fork(hmatching, p1, p2), fork(vmatching, p1, p2))
    noteq = compose(flip, fork(equality, first, last))
    dist = fork(manhattan, p1, p2)
    eq3 = compose(rbind(equality, THREE), dist)
    seg = fork(connect, first, last)
    endpoints = fork(combine, p1, p2)
    between = fork(difference, seg, endpoints)
    empty_between = compose(rbind(equality, ZERO), compose(size, compose(rbind(intersection, fg), between)))
    def lines_for_c(c):
        idxs = ofcolor(I, c)
        pairs = product(idxs, idxs)
        cond = fork(both, fork(both, aligned, noteq), fork(both, eq3, empty_between))
        sel = sfilter(pairs, cond)
        segs = apply(seg, sel)
        return merge(segs)
    lines = mapply(lines_for_c, colors)
    O = underfill(I, s, lines)
    return O

def dsl3(I):
    # Bridge only gaps of exact length 2 (distance 3) between any two non-background cells (rows/columns), regardless of color, using the singleton/least color
    s = leastcolor(I)
    fg = difference(asindices(I), ofcolor(I, ZERO))
    pairs = product(fg, fg)
    p1 = compose(initset, first)
    p2 = compose(initset, last)
    aligned = fork(either, fork(hmatching, p1, p2), fork(vmatching, p1, p2))
    noteq = compose(flip, fork(equality, first, last))
    dist = fork(manhattan, p1, p2)
    eq3 = compose(rbind(equality, THREE), dist)
    seg = fork(connect, first, last)
    sel = sfilter(pairs, fork(both, fork(both, aligned, noteq), eq3))
    segs = apply(seg, sel)
    lines = merge(segs)
    O = underfill(I, s, lines)
    return O

def dsl4(I):
    # Identify the singleton color by finding a size-1 object; bridge same-color gaps of length 2 using that color
    singletons = sizefilter(fgpartition(I), ONE)
    s = branch(equality(size(singletons), ZERO), leastcolor(I), color(first(singletons)))
    pals = palette(I)
    colors = remove(ZERO, remove(s, pals))
    def lines_for_c(c):
        idxs = ofcolor(I, c)
        pairs = product(idxs, idxs)
        p1 = compose(initset, first)
        p2 = compose(initset, last)
        aligned = fork(either, fork(hmatching, p1, p2), fork(vmatching, p1, p2))
        noteq = compose(flip, fork(equality, first, last))
        dist = fork(manhattan, p1, p2)
        eq3 = compose(rbind(equality, THREE), dist)
        seg = fork(connect, first, last)
        sel = sfilter(pairs, fork(both, fork(both, aligned, noteq), eq3))
        segs = apply(seg, sel)
        return merge(segs)
    lines = mapply(lines_for_c, colors)
    O = underfill(I, s, lines)
    return O

def dsl5(I):
    # Strict row/column scan: connect endpoints distance 3 for same color, but forbid bridging if any non-zero lies in the 2-gap
    s = leastcolor(I)
    colors = remove(ZERO, remove(s, palette(I)))
    fg = difference(asindices(I), ofcolor(I, ZERO))
    p1 = compose(initset, first)
    p2 = compose(initset, last)
    aligned = fork(either, fork(hmatching, p1, p2), fork(vmatching, p1, p2))
    noteq = compose(flip, fork(equality, first, last))
    dist = fork(manhattan, p1, p2)
    eq3 = compose(rbind(equality, THREE), dist)
    seg = fork(connect, first, last)
    endpoints = fork(combine, p1, p2)
    between = fork(difference, seg, endpoints)
    clear = compose(rbind(equality, ZERO), compose(size, compose(rbind(intersection, fg), between)))
    def lines_for_c(c):
        idxs = ofcolor(I, c)
        pairs = product(idxs, idxs)
        sel = sfilter(pairs, fork(both, fork(both, aligned, noteq), fork(both, eq3, clear)))
        segs = apply(seg, sel)
        return merge(segs)
    lines = mapply(lines_for_c, colors)
    O = underfill(I, s, lines)
    return O
```