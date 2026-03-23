training 3c9b0459 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = rot180(I)
    return O
```
training 6150a2bd test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = rot180(I)
    return O
```
training ed36ccf7 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = rot270(I)
    return O
```
training 67a3c6ac test 0.0 0.0 0.0 0.0 0.0
```python
def dsl4(I):
    O = vmirror(I)
    return O
```
training 68b16354 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = hmirror(I)
    return O
```
training 9dfd6313 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = dmirror(I)
    return O
```
training a416b8f3 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = hconcat(I, I)
    return O
```
training c59eb873 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = upscale(I, TWO)
    return O
```
training 74dd1130 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl4(I):
    O = rot90(hmirror(I))
    return O
```
training 9172f3a0 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = upscale(I, THREE)
    return O
```
training b1948b0a test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = replace(I, SIX, TWO)
    return O
```
training 6d0aefbc test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = hconcat(I, vmirror(I))
    return O
```
training 6fa7a44f test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = vconcat(I, hmirror(I))
    return O
```
training 8be77c9e test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = vconcat(I, hmirror(I))
    return O
```
training c9e6f938 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = hconcat(I, vmirror(I))
    return O
```
training d511f180 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl3(I):
    O = switch(I, FIVE, EIGHT)
    return O
```
training c8f0f002 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = replace(I, SEVEN, FIVE)
    return O
```
training d10ecb37 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = crop(I, ORIGIN, TWO_BY_TWO)
    return O
```
training 4c4377d9 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    top = hmirror(I)
    O = vconcat(top, I)
    return O
```
training 5582e5ca test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    c = mostcolor(I)
    O = canvas(c, shape(I))
    return O
```
training 5614dbcf test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    G = replace(I, FIVE, ZERO)
    O = downscale(G, THREE)
    return O
```
training 1cf80156 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl2(I):
    P = mapply(toindices, fgpartition(I))
    O = subgrid(P, I)
    return O
```
training 2dee498d test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = crop(I, ORIGIN, astuple(height(I), divide(width(I), THREE)))
    return O
```
training 00576224 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    V = vconcat(vconcat(I, vmirror(I)), I)
    O = hconcat(hconcat(V, V), V)
    return O
```
training 5bd6f4ac test 0.0 0.0 0.0 0.0 0.0
```python
def dsl4(I):
    J = vmirror(I)
    B = crop(J, ORIGIN, THREE_BY_THREE)
    O = vmirror(B)
    return O
```
training 25ff71a9 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl2(I):
    base = canvas(ZERO, shape(I))
    obj = asobject(I)
    O = move(base, obj, DOWN)
    return O
```
training 0c786b71 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl5(I):
    right = vconcat(hmirror(I), I)
    left = vmirror(right)
    O = hconcat(left, right)
    return O
```
training 0b148d64 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl4(I):
    lc = leastcolor(I)
    P = ofcolor(I, lc)
    G = fill(canvas(ZERO, shape(I)), lc, P)
    O = subgrid(P, G)
    return O
```
training c909285e test 0.0 0.0 0.0 0.0 0.0
```python
def dsl3(I):
    C = leastcolor(I)
    P = ofcolor(I, C)
    G = subgrid(P, I)
    B = box(asobject(G))
    O = fill(G, C, B)
    return O
```
training 0d3d703e test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    A = switch(I, ONE, FIVE)
    B = switch(A, TWO, SIX)
    C = switch(B, THREE, FOUR)
    O = switch(C, EIGHT, NINE)
    return O
```
training 1c786137 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl4(I):
    OBJS = objects(I, T, F, T)
    perim = compose(size, box)
    A = argmax(OBJS, perim)
    O = subgrid(delta(A), I)
    return O
```
training 32597951 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl3(I):
    p8 = ofcolor(I, EIGHT)
    rect = backdrop(p8)
    target = intersection(rect, ofcolor(I, ONE))
    O = fill(I, THREE, target)
    return O
```
training 0ca9ddb6 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    ones = ofcolor(I, ONE)
    twos = ofcolor(I, TWO)
    one_n = mapply(dneighbors, ones)
    two_n = mapply(ineighbors, twos)
    O = underfill(I, SEVEN, one_n)
    O = underfill(O, FOUR, two_n)
    return O
```
training 1c0d0a4b test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    c = leastcolor(I)
    pts = ofcolor(I, c)
    rows = mapply(hfrontier, pts)
    cols = mapply(vfrontier, pts)
    cross = intersection(rows, cols)
    mask = difference(cross, pts)
    O = fill(canvas(ZERO, shape(I)), TWO, mask)
    return O
```
training 12eac192 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl2(I):
    # Object extraction via mask: fill indices of all small components with 3
    objs = objects(I, T, F, T)
    small = combine(sizefilter(objs, 1), sizefilter(objs, 2))
    mask = toindices(merge(small))
    O = fill(I, THREE, mask)
    return O
```
training 178fcbfb test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    S1 = ofcolor(I, ONE)
    S3 = ofcolor(I, THREE)
    S2 = ofcolor(I, TWO)
    R1 = mapply(hfrontier, S1)
    R3 = mapply(hfrontier, S3)
    C2 = mapply(vfrontier, S2)
    G0 = fill(I, TWO, C2)
    G1 = fill(G0, THREE, R3)
    O = fill(G1, ONE, R1)
    return O
```
training 007bbfb7 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl4(I):
    H1 = hconcat(I, I)
    H = hconcat(H1, I)
    V1 = vconcat(H, H)
    tiled = vconcat(V1, H)
    zidx = ofcolor(I, ZERO)
    zoffs = apply(rbind(multiply, THREE), zidx)
    base = asindices(I)
    zmask = mapply(lbind(shift, base), zoffs)
    O = fill(tiled, ZERO, zmask)
    return O
```
training 08ed6ac7 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    objs = objects(I, T, F, T)
    fives = colorfilter(objs, FIVE)
    ord5 = order(fives, uppermost)
    n = size(ord5)
    cols = interval(ONE, add(n, ONE), ONE)
    recol = papply(recolor, cols, ord5)
    union = merge(recol)
    base = canvas(ZERO, shape(I))
    O = paint(base, union)
    return O
```
training 009d5c81 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl4(I):
    # Geometric: use outline box corners of the 1-set; recolor 8; remove 1
    P = ofcolor(I, ONE)
    crn = corners(box(P))
    k = size(intersection(P, crn))
    col = branch(equality(k, FOUR), THREE, branch(equality(k, TWO), SEVEN, TWO))
    O = replace(switch(I, EIGHT, col), ONE, ZERO)
    return O
```
training 05f2a901 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # Relational (gravitate + move): move color-2 object until adjacent to color-8
    objs = objects(I, T, F, T)
    twos = colorfilter(objs, TWO)
    eights = colorfilter(objs, EIGHT)
    two = first(twos)
    eight = first(eights)
    off = gravitate(two, eight)
    O = move(I, two, off)
    return O
```
training 0520fde7 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    f = ofcolor(I, FIVE)
    c = leftmost(f)
    h = height(I)
    startL = astuple(ZERO, subtract(c, THREE))
    startR = astuple(ZERO, increment(c))
    dims = astuple(h, THREE)
    L = crop(I, startL, dims)
    R = crop(I, startR, dims)
    E = cellwise(L, R, ZERO)
    O = replace(E, ONE, TWO)
    return O
```
training 1a2e2828 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl2(I):
    OB = objects(I, T, F, T)
    wi = width(I)
    hi = height(I)
    eqw = rbind(equality, wi)
    eqh = rbind(equality, hi)
    fullw = compose(eqw, width)
    fullh = compose(eqh, height)
    cond = fork(either, fullw, fullh)
    obj = extract(OB, cond)
    c = color(obj)
    O = canvas(c, UNITY)
    return O
```
training 0692e18c test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    dims = shape(I)
    z = ofcolor(I, ZERO)
    p_obj = recolor(ONE, z)
    p = paint(canvas(ZERO, dims), p_obj)
    row = hconcat(p, hconcat(p, p))
    t = vconcat(row, vconcat(row, row))
    b = upscale(I, THREE)
    s = ofcolor(t, ONE)
    obj = toobject(s, b)
    O = paint(canvas(ZERO, shape(b)), obj)
    return O
```
training 017c7c7b test 0.0 0.0 0.0 0.0 0.0
```python
def dsl3(I):
    A = replace(I, ONE, TWO)
    H = height(I)
    W = width(I)
    O2 = toobject(ofcolor(A, TWO), A)
    P = vperiod(O2)
    Mid1 = crop(A, toivec(decrement(halve(H))), astuple(THREE, W))
    Mid2 = crop(A, toivec(halve(H)), astuple(THREE, W))
    B = branch(equality(P, THREE), Mid2, Mid1)
    O = vconcat(A, B)
    return O
```
training 0c9aba6e test 0.0 0.0 0.0 0.0 0.0
```python
def dsl2(I):
    s7 = ofcolor(I, SEVEN)
    r = uppermost(s7)
    w = width(I)
    h = r
    dims = astuple(h, w)
    top = crop(I, ORIGIN, dims)
    bot = crop(I, astuple(add(r, ONE), ZERO), astuple(subtract(height(I), add(r, ONE)), w))
    A = replace(top, ZERO, EIGHT)
    B = replace(bot, ZERO, EIGHT)
    O = cellwise(A, B, ZERO)
    return O
```
training 140c817e test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    bg = mostcolor(I)
    dims = shape(I)
    anchors = ofcolor(I, ONE)
    rows = merge(apply(hfrontier, anchors))
    cols = merge(apply(vfrontier, anchors))
    cross = combine(rows, cols)
    diag = merge(apply(ineighbors, anchors))
    O = canvas(bg, dims)
    O = fill(O, ONE, cross)
    O = fill(O, THREE, diag)
    O = fill(O, TWO, anchors)
    return O
```
training 1190e5a7 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    SC = leastcolor(I)
    BG = mostcolor(I)
    H = height(I)
    W = width(I)
    RH = astuple(ONE, W)
    CH = astuple(H, ONE)
    Rg = canvas(SC, RH)
    Cg = canvas(SC, CH)
    RO = asobject(Rg)
    CO = asobject(Cg)
    RC = size(occurrences(I, RO))
    CC = size(occurrences(I, CO))
    HD = add(RC, ONE)
    WD = add(CC, ONE)
    D = astuple(HD, WD)
    O = canvas(BG, D)
    return O
```
training 0becf7df test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    c00 = index(I, ORIGIN)
    c01 = index(I, RIGHT)
    c10 = index(I, DOWN)
    c11 = index(I, add(RIGHT, DOWN))
    r0 = shoot(ORIGIN, RIGHT)
    r1 = shoot(DOWN, RIGHT)
    c0 = shoot(ORIGIN, DOWN)
    c1 = shoot(RIGHT, DOWN)
    M = intersection(combine(r0, r1), combine(c0, c1))
    Sw = switch(switch(I, c00, c01), c10, c11)
    G = cover(Sw, M)
    O = paint(G, toobject(M, I))
    return O
```
training 12997ef3 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    S = subgrid(ofcolor(I, ONE), I)
    P = ofcolor(S, ONE)
    K = compress(replace(I, ONE, ZERO))
    Kh = hupscale(K, width(S))
    Kbig = vupscale(Kh, height(S))
    dims = multiply(shape(S), shape(K))
    pos = toindices(asobject(K))
    off = apply(rbind(multiply, shape(S)), pos)
    tiles = prapply(add, off, P)
    M = toobject(tiles, Kbig)
    O = paint(canvas(ZERO, dims), M)
    return O
```
training 195ba7dc test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    p2 = ofcolor(I, TWO)
    j = leftmost(p2)
    h = height(I)
    w = width(I)
    j1 = increment(j)
    left = crop(I, astuple(ZERO, ZERO), astuple(h, j))
    right = crop(I, astuple(ZERO, j1), astuple(h, subtract(w, j1)))
    left1 = replace(left, SEVEN, ONE)
    right1 = replace(right, SEVEN, ONE)
    LL = ofcolor(left1, ONE)
    RR = ofcolor(right1, ONE)
    U = combine(LL, RR)
    O = fill(canvas(ZERO, astuple(h, j)), ONE, U)
    return O
```
training 070dd51e test 0.0 0.0 0.0 0.0 0.0
```python
def dsl2(I):
    colors = remove(ZERO, palette(I))
    pts = apply(lbind(ofcolor, I), colors)
    vsets = sfilter(pts, fork(equality, leftmost, rightmost))
    hsets = sfilter(pts, fork(equality, uppermost, lowermost))
    col = compose(color, rbind(toobject, I))
    seg = backdrop
    tint = fork(recolor, col, seg)
    vobj = mapply(tint, vsets)
    hobj = mapply(tint, hsets)
    O0 = canvas(ZERO, shape(I))
    O1 = paint(O0, vobj)
    O = underpaint(O1, hobj)
    return O
```
training 19bb5feb test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    G = compress(trim(I))
    G0 = replace(G, EIGHT, ZERO)
    tl = leastcolor(lefthalf(tophalf(G0)))
    tr = leastcolor(righthalf(tophalf(G0)))
    bl = leastcolor(lefthalf(bottomhalf(G0)))
    br = leastcolor(righthalf(bottomhalf(G0)))
    base = canvas(ZERO, TWO_BY_TWO)
    idx = asindices(base)
    a = fill(base, tl, initset(ulcorner(idx)))
    b = fill(a, tr, initset(urcorner(idx)))
    c = fill(b, bl, initset(llcorner(idx)))
    O = fill(c, br, initset(lrcorner(idx)))
    return O
```
training 1478ab18 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl5(I):
    five = ofcolor(I, FIVE)
    c = corners(five)
    miss = first(difference(c, five))
    rowpeerset = difference(intersection(hfrontier(miss), c), initset(miss))
    colpeerset = difference(intersection(vfrontier(miss), c), initset(miss))
    rowpeer = first(rowpeerset)
    colpeer = first(colpeerset)
    borders = combine(connect(miss, rowpeer), connect(miss, colpeer))
    diag = connect(rowpeer, colpeer)
    patch = combine(borders, diag)
    O = underfill(I, EIGHT, patch)
    return O
```
training 025d127b test 0.0 0.0 0.0 0.0 0.0
```python
def dsl5(I):
    objs = objects(I, T, F, T)
    samecolor = compose(lbind(colorfilter, objs), color)
    rmap = lbind(apply, rightmost)
    maxright_in_color = compose(maximum, rmap)
    Rc = compose(maxright_in_color, samecolor)
    is_blocked = fork(equality, rightmost, Rc)
    blocked = sfilter(objs, is_blocked)
    allowed = difference(objs, blocked)
    shifted = apply(rbind(shift, RIGHT), allowed)
    merged = merge(combine(shifted, blocked))
    O = paint(canvas(ZERO, shape(I)), merged)
    return O
```
training 0e671a1a test 0.0 0.0 0.0 0.0 0.0
```python
def dsl2(I):
    p4 = toobject(ofcolor(I, FOUR), I)
    p3 = toobject(ofcolor(I, THREE), I)
    p2 = toobject(ofcolor(I, TWO), I)
    l4 = ulcorner(p4)
    l3 = ulcorner(p3)
    l2 = ulcorner(p2)
    a = first(intersection(hfrontier(l4), vfrontier(l3)))
    c = first(intersection(hfrontier(l2), vfrontier(l4)))
    top = connect(l4, a)
    left = connect(l4, c)
    right = connect(a, l3)
    bottom = connect(c, l2)
    edges = combine(top, combine(left, combine(right, bottom)))
    O = underpaint(I, recolor(FIVE, edges))
    return O
```
training 1b2d62fb test 0.0 0.0 0.0 0.0 0.0
```python
def dsl2(I):
    axis = ofcolor(I, ONE)
    L1 = shift(axis, LEFT)
    L2 = shift(axis, multiply(LEFT, TWO))
    L3 = shift(axis, multiply(LEFT, THREE))
    leftarea = combine(L1, combine(L2, L3))
    R1 = shift(axis, RIGHT)
    R2 = shift(axis, multiply(RIGHT, TWO))
    R3 = shift(axis, multiply(RIGHT, THREE))
    rightarea = combine(R1, combine(R2, R3))
    dims = astuple(height(I), THREE)
    L = crop(I, ulcorner(leftarea), dims)
    R = crop(I, ulcorner(rightarea), dims)
    L8 = replace(replace(L, ZERO, EIGHT), NINE, ZERO)
    R8 = replace(replace(R, ZERO, EIGHT), NINE, ZERO)
    O = cellwise(L8, R8, ZERO)
    return O
```
training 00dbd492 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl5(I):
    twos = colorfilter(objects(I, T, F, T), TWO)
    gt2 = rbind(greater, TWO)
    rings = sfilter(twos, fork(both, compose(gt2, height), compose(gt2, width)))
    isin9 = compose(rbind(equality, 9), compose(size, delta))
    isin25 = compose(rbind(equality, 25), compose(size, delta))
    set5 = sfilter(rings, isin9)
    set7 = sfilter(rings, isin25)
    rest = difference(rings, combine(set5, set7))
    obj = merge((
        mapply(compose(lbind(recolor, EIGHT), delta), set5),
        mapply(compose(lbind(recolor, FOUR), delta), set7),
        mapply(compose(lbind(recolor, THREE), delta), rest)
    ))
    O = underpaint(I, obj)
    return O
```
training 05269061 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl3(I):
    NZ = difference(asindices(I), ofcolor(I, ZERO))
    COL = lbind(index, I)
    SUP = rbind(shoot, UP_RIGHT)
    SDL = rbind(shoot, DOWN_LEFT)
    DIAG = fork(combine, SUP, SDL)
    OBJF = fork(recolor, COL, DIAG)
    BASE = merge(apply(OBJF, NZ))
    H = height(I)
    W = width(I)
    RO = interval(0, H, THREE)
    CO = interval(0, W, THREE)
    DV = apply(toivec, RO)
    DH = apply(tojvec, CO)
    NDV = apply(invert, DV)
    NDH = apply(invert, DH)
    VOFFS = combine(DV, NDV)
    HOFFS = combine(DH, NDH)
    OFFS = prapply(add, VOFFS, HOFFS)
    SH = apply(lbind(shift, BASE), OFFS)
    BIG = merge(SH)
    O = paint(canvas(ZERO, shape(I)), BIG)
    return O
```
training 14b8e18c test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # Geometric (shifts of corners): put 2s at outbox-adjacent orthogonal neighbors of non-singleton square corners
    objs = objects(I, T, F, T)
    eqhw = fork(equality, height, width)
    sq0 = sfilter(objs, eqhw)
    size1 = compose(lbind(equality, ONE), size)
    nonsing = compose(flip, size1)
    sqs = sfilter(sq0, nonsing)
    c = corners
    u = compose(rbind(shift, UP), c)
    d = compose(rbind(shift, DOWN), c)
    l = compose(rbind(shift, LEFT), c)
    r = compose(rbind(shift, RIGHT), c)
    ud = fork(combine, u, d)
    lr = fork(combine, l, r)
    alln = fork(combine, ud, lr)
    ext = fork(intersection, alln, outbox)
    obj2 = mapply(compose(lbind(recolor, TWO), ext), sqs)
    O = underpaint(I, obj2)
    return O
```
training 1a244afd test 0.0 0.0 0.0 0.0 0.0
```python
def dsl3(I):
    P = asindices(I)
    base = replace(I, SIX, EIGHT)
    ones = ofcolor(I, ONE)
    sixes = ofcolor(I, SIX)
    def per(o):
        p = initset(o)
        predh = compose(lbind(hmatching, p), initset)
        predv = compose(lbind(vmatching, p), initset)
        cond = fork(either, predh, predv)
        aligned = sfilter(sixes, cond)
        comp = compose(lbind(manhattan, p), initset)
        q = argmin(aligned, comp)
        dirv = sign(subtract(q, o))
        orth = branch(equality(dirv, UP), LEFT, branch(equality(dirv, DOWN), RIGHT, branch(equality(dirv, LEFT), DOWN, UP)))
        dist = manhattan(p, initset(q))
        t = add(o, multiply(orth, dist))
        return intersection(initset(t), P)
    T = merge(apply(per, ones))
    O = fill(base, SEVEN, T)
    return O
```
training 0962bcdd test 0.0 0.0 0.0 0.0 0.0
```python
def dsl3(I):
    # Color filtering + morphology: mask growth; diagonals via diagonal expansions minus plus
    c = leastcolor(I)
    a = other(remove(ZERO, palette(I)), c)
    centers = ofcolor(I, c)
    r1 = combine(combine(centers, mapply(neighbors, centers)), mapply(ineighbors, centers))
    r2 = combine(combine(r1, mapply(neighbors, r1)), mapply(ineighbors, r1))
    plus = intersection(combine(mapply(hfrontier, centers), mapply(vfrontier, centers)), r2)
    dstep1 = mapply(ineighbors, centers)
    dstep2 = mapply(ineighbors, dstep1)
    diagcand = combine(combine(centers, dstep1), dstep2)
    diag = intersection(diagcand, r2)
    diag = difference(diag, plus)
    diag = combine(diag, centers)
    O = canvas(ZERO, shape(I))
    O = fill(O, a, plus)
    O = fill(O, c, diag)
    return O
```
training 15696249 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl3(I):
    P0 = partition(I)
    sz = compose(size, toindices)
    is3 = compose(rbind(equality, THREE), sz)
    condH = fork(both, hline, is3)
    hasH0 = greater(size(mfilter(P0, condH)), ZERO)
    Irot = branch(hasH0, I, rot90(I))
    P = partition(Irot)
    H3x9 = hconcat(Irot, hconcat(Irot, Irot))
    Z3x9 = canvas(ZERO, astuple(THREE, NINE))
    top = vconcat(H3x9, vconcat(Z3x9, Z3x9))
    mid = vconcat(Z3x9, vconcat(H3x9, Z3x9))
    bot = vconcat(Z3x9, vconcat(Z3x9, H3x9))
    topset = mfilter(P, fork(both, condH, compose(rbind(equality, ZERO), uppermost)))
    midset = mfilter(P, fork(both, condH, compose(rbind(equality, ONE), uppermost)))
    bTop = greater(size(topset), ZERO)
    bMid = greater(size(midset), ZERO)
    GHrot = branch(bTop, top, branch(bMid, mid, bot))
    O = branch(hasH0, GHrot, rot270(GHrot))
    return O
```
training 1bfc4729 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    A = asindices(I)
    L = leftmost(A)
    R = rightmost(A)
    B = lowermost(A)
    OB = objects(I, T, F, T)
    U = argmin(OB, uppermost)
    D = argmax(OB, uppermost)
    RU = uppermost(U)
    RD = uppermost(D)
    MID = halve(add(RU, RD))
    MIDP = increment(MID)
    CU = color(U)
    CD = color(D)
    RTOP = connect(astuple(0, L), astuple(0, R))
    RRU = connect(astuple(RU, L), astuple(RU, R))
    RRD = connect(astuple(RD, L), astuple(RD, R))
    RBOT = connect(astuple(B, L), astuple(B, R))
    CLT = connect(astuple(0, L), astuple(MID, L))
    CRT = connect(astuple(0, R), astuple(MID, R))
    CLB = connect(astuple(MIDP, L), astuple(B, L))
    CRB = connect(astuple(MIDP, R), astuple(B, R))
    PTOP = combine(combine(RTOP, RRU), combine(CLT, CRT))
    PBOT = combine(combine(RRD, RBOT), combine(CLB, CRB))
    OT = recolor(CU, PTOP)
    OBJ = recolor(CD, PBOT)
    O0 = canvas(ZERO, shape(I))
    O1 = paint(O0, OT)
    O2 = paint(O1, OBJ)
    return O2
```
training 0a938d79 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl4(I):
    # Geometric alignment: assemble both colored rays into one seed band; replicate as a whole
    OS = objects(I, T, F, T)
    o1 = first(OS); o2 = last(OS)
    c1 = color(o1); c2 = color(o2)
    l1 = first(toindices(o1)); l2 = first(toindices(o2))
    P = combine(toindices(o1), toindices(o2))
    dv = subtract(lowermost(P), uppermost(P))
    dh = subtract(rightmost(P), leftmost(P))
    H = height(I); W = width(I)
    baseR = branch(equality(dv, ZERO), ONE, dv)
    baseC = branch(equality(dh, ZERO), ONE, dh)
    stepR = double(baseR)
    stepC = double(baseC)
    offsR = apply(toivec, interval(ZERO, H, stepR))
    offsC = apply(tojvec, interval(ZERO, W, stepC))
    HR = combine(recolor(c1, combine(shoot(l1, LEFT), shoot(l1, RIGHT))),
                 recolor(c2, combine(shoot(l2, LEFT), shoot(l2, RIGHT))))
    VR = combine(recolor(c1, combine(shoot(l1, UP), shoot(l1, DOWN))),
                 recolor(c2, combine(shoot(l2, UP), shoot(l2, DOWN))))
    HOBJ = merge(prapply(shift, initset(HR), offsR))
    VOBJ = merge(prapply(shift, initset(VR), offsC))
    hsel = either(equality(dh, ZERO), flip(greater(dv, dh)))
    O = paint(canvas(ZERO, shape(I)), branch(hsel, HOBJ, VOBJ))
    return O
```
training 90f3ed37 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl3(I):
    E = ofcolor(I, EIGHT)
    Z = ofcolor(I, ZERO)
    OE = toobject(E, I)
    HP = hperiod(OE)
    AboveE = shift(E, UP)
    R = difference(E, shift(E, LEFT))
    L8 = intersection(E, shift(E, RIGHT))
    Diag = combine(shift(E, UP_RIGHT), shift(E, DOWN_LEFT))
    A = shift(intersection(R, L8), RIGHT)
    B = shift(shift(intersection(R, Diag), RIGHT), RIGHT)
    C = shift(difference(R, combine(L8, Diag)), RIGHT)
    Af = difference(intersection(A, Z), AboveE)
    Bf = difference(intersection(B, Z), AboveE)
    Cf = difference(intersection(C, Z), AboveE)
    RaysA = mapply(rbind(shoot, RIGHT), totuple(Af))
    RaysB = mapply(rbind(shoot, RIGHT), totuple(Bf))
    RaysC = mapply(rbind(shoot, RIGHT), totuple(Cf))
    RaysP1 = combine(RaysA, combine(RaysB, shift(RaysC, DOWN)))
    RR = difference(E, shift(E, RIGHT))
    S0 = difference(intersection(shift(shift(RR, RIGHT), RIGHT), Z), AboveE)
    T1 = shift(S0, ZERO_BY_TWO)
    T2 = shift(T1, ZERO_BY_TWO)
    T3 = shift(T2, ZERO_BY_TWO)
    T4 = shift(T3, ZERO_BY_TWO)
    T5 = shift(T4, ZERO_BY_TWO)
    Points = combine(combine(S0, T1), combine(combine(T2, T3), combine(T4, T5)))
    Patch = branch(equality(HP, TWO), Points, RaysP1)
    O = underfill(I, ONE, Patch)
    return O
```
training 13713586 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl4(I):
    objs = objects(I, T, F, T)
    b5s = colorfilter(objs, FIVE)
    b5 = first(b5s)
    B = toindices(b5)
    is_v = vline(B)
    is_left = equality(leftmost(B), ZERO)
    is_top = equality(uppermost(B), ZERO)
    dir_h = branch(is_left, LEFT, RIGHT)
    dir_v = branch(is_top, UP, DOWN)
    dirn = branch(is_v, dir_h, dir_v)
    pal = remove(FIVE, remove(ZERO, palette(I)))
    S = mapply(lbind(ofcolor, I), pal)
    stops = combine(S, B)
    f_pair = compose(rbind(product, stops), initset)
    f_ifst = compose(initset, first)
    f_ilast = compose(initset, last)
    pred_h = fork(hmatching, f_ifst, f_ilast)
    pred_v = fork(vmatching, f_ifst, f_ilast)
    align = branch(is_v, pred_h, pred_v)
    pos = fork(position, f_ifst, f_ilast)
    sgn = compose(sign, pos)
    pred_dir = compose(lbind(equality, dirn), sgn)
    dist = fork(manhattan, f_ifst, f_ilast)
    nz = compose(flip, compose(lbind(equality, ZERO), dist))
    ok = fork(both, fork(both, align, pred_dir), nz)
    pairs_ok = compose(rbind(sfilter, ok), f_pair)
    nearest = compose(rbind(argmin, dist), pairs_ok)
    seg = compose(fork(connect, first, last), identity)
    col = compose(lbind(index, I), first)
    recol = fork(recolor, compose(col, identity), compose(seg, identity))
    rects = mapply(compose(recol, nearest), S)
    O = underpaint(I, rects)
    return O
```
training 1d398264 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl5(I):
    # Relational: build masks relative to center via shifts; underpaint to stabilize layering
    nz = difference(asindices(I), ofcolor(I, ZERO))
    ctr = center(nz)
    UL = add(UP, LEFT); UR = add(UP, RIGHT); DL = add(DOWN, LEFT); DR = add(DOWN, RIGHT)
    lcol = color(toobject(shift(initset(ctr), LEFT), I))
    rcol = color(toobject(shift(initset(ctr), RIGHT), I))
    ucol = color(toobject(shift(initset(ctr), UP), I))
    dcol = color(toobject(shift(initset(ctr), DOWN), I))
    ulc = color(toobject(shift(initset(ctr), UL), I))
    urc = color(toobject(shift(initset(ctr), UR), I))
    dlc = color(toobject(shift(initset(ctr), DL), I))
    drc = color(toobject(shift(initset(ctr), DR), I))
    ccol = color(toobject(initset(ctr), I))
    leftmask = shoot(ctr, LEFT)
    rightmask = shoot(ctr, RIGHT)
    upmask = shoot(ctr, UP)
    downmask = shoot(ctr, DOWN)
    ulmask = difference(shoot(ctr, UL), initset(ctr))
    urmask = difference(shoot(ctr, UR), initset(ctr))
    dlmask = difference(shoot(ctr, DL), initset(ctr))
    drmask = difference(shoot(ctr, DR), initset(ctr))
    O = canvas(ZERO, shape(I))
    O = underfill(O, lcol, leftmask)
    O = underfill(O, rcol, rightmask)
    O = underfill(O, ucol, upmask)
    O = underfill(O, dcol, downmask)
    O = underfill(O, ulc, ulmask)
    O = underfill(O, urc, urmask)
    O = underfill(O, dlc, dlmask)
    O = underfill(O, drc, drmask)
    O = fill(O, ccol, initset(ctr))
    return O
```
training 0f63c0b9 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl2(I):
    dims = shape(I)
    H = height(I)
    Z = canvas(ZERO, dims)

    idxs = asindices(I)
    jL = leftmost(idxs)
    jR = rightmost(idxs)
    vL = tojvec(jL)
    vR = tojvec(jR)
    TL = astuple(ZERO, jL)
    TR = astuple(ZERO, jR)
    BL = astuple(decrement(H), jL)
    BR = astuple(decrement(H), jR)

    objs = objects(I, T, F, T)
    ords = order(objs, uppermost)
    headless = remove(last(ords), ords)
    tailless = remove(first(ords), ords)
    pairs = pair(headless, tailless)

    ra = compose(uppermost, first)
    rb = compose(uppermost, last)
    ca = compose(color, first)
    cb = compose(color, last)
    mid = compose(halve, fork(add, ra, rb))
    mid1 = compose(increment, mid)

    aL = compose(lbind(add, vL), compose(toivec, ra))
    aR = compose(lbind(add, vR), compose(toivec, ra))
    bL = compose(lbind(add, vL), compose(toivec, rb))
    bR = compose(lbind(add, vR), compose(toivec, rb))
    mL = compose(lbind(add, vL), compose(toivec, mid))
    mR = compose(lbind(add, vR), compose(toivec, mid))
    mL1 = compose(lbind(add, vL), compose(toivec, mid1))
    mR1 = compose(lbind(add, vR), compose(toivec, mid1))

    leftUp = fork(recolor, ca, fork(connect, aL, mL))
    leftDn = fork(recolor, cb, fork(connect, mL1, bL))
    rightUp = fork(recolor, ca, fork(connect, aR, mR))
    rightDn = fork(recolor, cb, fork(connect, mR1, bR))
    bands = mapply(fork(combine, fork(combine, leftUp, leftDn), fork(combine, rightUp, rightDn)), pairs)

    rvec = compose(toivec, uppermost)
    pL = compose(lbind(add, vL), rvec)
    pR = compose(lbind(add, vR), rvec)
    rows = mapply(fork(recolor, color, fork(connect, pL, pR)), ords)

    topobj = first(ords)
    botobj = last(ords)
    topc = color(topobj)
    botc = color(botobj)

    topL = recolor(topc, connect(TL, pL(topobj)))
    topR = recolor(topc, connect(TR, pR(topobj)))
    botL = recolor(botc, connect(pL(botobj), BL))
    botR = recolor(botc, connect(pR(botobj), BR))

    topfull = recolor(topc, connect(TL, TR))
    botfull = recolor(botc, connect(BL, BR))

    O = paint(Z, combine(rows, combine(bands, combine(topL, combine(topR, combine(botL, combine(botR, combine(topfull, botfull))))))))
    return O
```
training 0d87d2a6 test 0.0 3.4641016151377544 0.02086956521739125 0.0 3.4849711803551457
```python
def dsl1(I):
    # Global: draw axis lines from border-1s, then recolor 2-objects intersecting these axes
    ones = ofcolor(I, ONE)
    allidx = asindices(I)
    br = lrcorner(allidx)
    toprow = hfrontier(ORIGIN)
    botrow = hfrontier(br)
    leftcol = vfrontier(ORIGIN)
    rightcol = vfrontier(br)
    rowborder = combine(toprow, botrow)
    colborder = combine(leftcol, rightcol)
    topbot = intersection(ones, rowborder)
    lrside = intersection(ones, colborder)
    vaxes = mapply(vfrontier, topbot)
    haxes = mapply(hfrontier, lrside)
    cross = combine(vaxes, haxes)
    lineobj = recolor(ONE, cross)
    J = paint(I, lineobj)
    twos = colorfilter(objects(I, T, F, T), TWO)
    dist = lbind(manhattan, cross)
    ishit = compose(lbind(equality, ZERO), dist)
    sel = sfilter(twos, ishit)
    fills = mapply(lbind(recolor, ONE), sel)
    O = paint(J, fills)
    return O
```
training 11852cab test 0.0 5.656854249492381 0.020000000000000018 0.0 5.676854249492381
```python
def dsl4(I):
    P = difference(asindices(I), ofcolor(I, ZERO))
    O = toobject(P, I)
    N = normalize(O)
    V = vmirror(N)
    H = hmirror(N)
    VH = vmirror(H)
    U1 = combine(N, V)
    U2 = combine(U1, H)
    U3 = combine(U2, VH)
    start = ulcorner(P)
    Ug = shift(U3, start)
    base = canvas(ZERO, shape(I))
    return paint(base, Ug)
```
training 18286ef8 train 0.0 5.656854249492381 0.03125 0.0 5.688104249492381
```python
def dsl1(I):
    # Global centers: move internal 9 one step toward center of external 9/6; also 6->9
    G = replace(I, SIX, NINE)
    P5 = ofcolor(I, FIVE)
    B = inbox(P5)
    J = intersection(ofcolor(G, NINE), B)
    Ext = difference(ofcolor(G, NINE), B)
    D = sign(subtract(centerofmass(Ext), center(B)))
    O = fill(fill(G, FIVE, J), NINE, shift(J, D))
    return O
```
training 1caeab9d test 0.0 6.48074069840786 0.06000000000000005 0.035355339046827375 6.576096037454688
```python
def dsl1(I):
    # Relational alignment by upper row of color-1 object; preserve columns
    objs = objects(I, T, F, T)
    oneobj = first(colorfilter(objs, ONE))
    top1v = toivec(uppermost(oneobj))
    dirfun = compose(lbind(subtract, top1v), compose(toivec, uppermost))
    shifter = fork(shift, identity, dirfun)
    shifted = apply(shifter, objs)
    merged = merge(shifted)
    O = paint(canvas(ZERO, shape(I)), merged)
    return O
```
training 0b17323b train 0.0 6.82842712474619 0.026666666666666616 0.09999999997642978 6.955093791389286
```python
def dsl4(I):
    ones = ofcolor(I, ONE)
    ul = ulcorner(ones)
    lr = lrcorner(ones)
    k = decrement(size(ones))
    step = divide(subtract(lr, ul), k)
    start = add(lr, step)
    br = lrcorner(asindices(I))
    rect = backdrop(combine(initset(start), initset(br)))
    path = intersection(shoot(start, step), rect)
    O = underpaint(I, recolor(TWO, path))
    return O
```
training 1a07d186 train 0.0 7.0 0.011852548036758503 0.09276262180803119 7.10461516984479
```python
def dsl4(I):
    dims = shape(I)
    blank = canvas(ZERO, dims)
    objs = objects(I, T, F, T)
    isline = fork(either, hline, vline)
    cols = apply(color, sfilter(objs, isline))
    def per_color(c):
        cobjs = colorfilter(objs, c)
        lns = sfilter(cobjs, isline)
        anch = argmax(lns, size)
        ai = toindices(anch)
        extras = remove(anch, cobjs)
        def per_extra(e):
            ce = centerofmass(e)
            d = gravitate(toindices(e), ai)
            pt = connect(ce, ce)
            tgt = shift(pt, d)
            return recolor(c, tgt)
        moved = merge(apply(per_extra, extras))
        return combine(anch, moved)
    parts = apply(per_color, cols)
    O = paint(blank, merge(parts))
    return O
```
training 137f0df0 train 0.0 7.277916867529369 0.18000000000000005 0.16123724351257346 7.619154111041942
```python
def dsl3(I):
    # Axis-wise removal: box-lines minus 5-lines per axis, then combine
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    rb = mapply(hfrontier, b)
    cb = mapply(vfrontier, b)
    r5 = mapply(hfrontier, p5)
    c5 = mapply(vfrontier, p5)
    rbelts = intersection(b, difference(rb, r5))
    cbelts = intersection(b, difference(cb, c5))
    belts = combine(rbelts, cbelts)
    O0 = underfill(I, TWO, belts)
    axes = combine(difference(rb, r5), difference(cb, c5))
    ring = intersection(outbox(b), axes)
    O = underfill(O0, ONE, ring)
    return O
```
training 1b60fb0c train 0.0 7.483314773547883 0.14 0.04999999998232233 7.673314773530205
```python
def dsl2(I):
    M = ofcolor(I, ONE)
    O1 = toobject(M, I)
    UL = ulcorner(O1)
    G = subgrid(O1, I)
    K = vmirror(G)
    MK = shift(ofcolor(K, ONE), UL)
    C1 = intersection(M, shift(M, UP))
    C2 = intersection(M, shift(M, DOWN))
    C = intersection(C1, C2)
    Agrid = paint(canvas(ZERO, shape(I)), recolor(ONE, toobject(C, I)))
    Aobjs = objects(Agrid, T, F, T)
    AO = argmax(Aobjs, size)
    CA = center(AO)
    CO = center(O1)
    D = multiply(TWO, subtract(CA, CO))
    SA = shift(MK, D)
    P = difference(SA, M)
    O = underpaint(I, recolor(TWO, P))
    return O
```
training 11dc524f train 0.0 8.485281374238571 0.035502958579881505 0.0 8.520784332818453
```python
def dsl3(I):
    # O = use B’s bounding-box outline as attractor; underfill shifted A
    A = ofcolor(I, TWO)
    B = ofcolor(I, FIVE)
    v = gravitate(A, box(B))
    base = replace(I, TWO, SEVEN)
    O = underfill(base, TWO, shift(A, v))
    return O
```
training 1da012fc train 0.0 14.26528819162068 0.09659945317840057 0.0 14.361887644799081
```python
def dsl4(I):
    S = objects(I, T, F, T)
    L = argmax(S, size)
    R = remove(L, S)
    Seeds = sizefilter(R, 1)
    T1 = colorfilter(S, ONE)
    T8 = colorfilter(S, EIGHT)
    Targets = combine(T1, T8)
    M0 = lbind(lbind, manhattan)
    BT = compose(box, toindices)
    Dist = compose(M0, BT)  # Dist(target) -> (seed -> manhattan(box(target), seed))
    N = compose(lbind(argmin, Seeds), Dist)
    CF = fork(recolor, compose(color, N), toindices)
    U = merge(apply(CF, Targets))
    O = paint(I, U)
    return O
```
training 1acc24af train 0.0 18.727922061357855 0.09722222222222221 0.0 18.825144283580077
```python
def dsl4(I):
    # Geometric: keep 5s only on the densest 5-column (max overlap of a vertical frontier with the 5s)
    S = ofcolor(I, FIVE)
    lines = apply(vfrontier, S)
    best = argmax(lines, compose(size, rbind(intersection, S)))
    keep = intersection(S, best)
    O = paint(replace(I, FIVE, TWO), toobject(keep, I))
    return O
```
training 1d61978c train 0.0 22.44994432064365 0.0546875 0.0 22.50463182064365
```python
def dsl1(I):
    # relational selection: choose between the two bbox diagonals by max overlap with 5, recolor chosen as 2 and the rest as 8
    S5 = ofcolor(I, FIVE)
    A1 = connect(urcorner(S5), llcorner(S5))
    A2 = connect(ulcorner(S5), lrcorner(S5))
    Axes = insert(A2, initset(A1))
    score = chain(size, lbind(intersection, S5), identity)
    Best = argmax(Axes, score)
    S2 = intersection(S5, Best)
    S8 = difference(S5, S2)
    O = fill(fill(I, EIGHT, S8), TWO, S2)
    return O
```
training 0a2355a6 train 0.0 25.85408803659051 0.6950937950937951 0.0 26.549181831684308
```python
def dsl2(I):
    # Objectwise COM vs 8-box center: TL=1, TR=2, BL=3, BR(+axes/center)=1
    P = ofcolor(I, EIGHT)
    l = leftmost(P); r = rightmost(P)
    u = uppermost(P); d = lowermost(P)
    gc = astuple(halve(add(u, d)), halve(add(l, r)))
    objs = colorfilter(objects(I, T, F, T), EIGHT)
    vec = compose(rbind(subtract, gc), centerofmass)
    sgn = compose(sign, vec)
    is_tl = compose(lbind(equality, NEG_UNITY), sgn)
    is_tr = compose(lbind(equality, UP_RIGHT), sgn)
    is_bl = compose(lbind(equality, DOWN_LEFT), sgn)
    is_br = compose(lbind(equality, UNITY), sgn)
    is_up = compose(lbind(equality, UP), sgn)
    is_dn = compose(lbind(equality, DOWN), sgn)
    is_lf = compose(lbind(equality, LEFT), sgn)
    is_rt = compose(lbind(equality, RIGHT), sgn)
    is_ct = compose(lbind(equality, ORIGIN), sgn)
    tl = sfilter(objs, is_tl)
    tr = combine(sfilter(objs, is_tr), sfilter(objs, is_up))
    bl = sfilter(objs, is_bl)
    br = combine(sfilter(objs, is_br), combine(sfilter(objs, is_rt), combine(sfilter(objs, is_dn), sfilter(objs, is_ct))))
    tl_r = merge(apply(lbind(recolor, ONE), tl))
    tr_r = merge(apply(lbind(recolor, TWO), tr))
    bl_r = merge(apply(lbind(recolor, THREE), bl))
    br_r = merge(apply(lbind(recolor, ONE), br))
    base = replace(I, EIGHT, ZERO)
    O = paint(paint(paint(paint(base, tl_r), tr_r), bl_r), br_r)
    return O
```
training 17829a00 train 0.0 26.35676541901522 0.21875 0.0 26.57551541901522
```python
def dsl4(I):
    # Geometric bounding frame: outline bounding boxes of interior content in each half with border colors; redraw borders
    BG = mostcolor(I)
    H = height(I)
    Half = halve(H)
    TT = interval(ZERO, Half, ONE)
    TB = interval(Half, H, ONE)
    FT = merge(mapply(hfrontier, apply(toivec, TT)))
    FB = merge(mapply(hfrontier, apply(toivec, TB)))
    OB = objects(I, T, F, T)
    BOR = sfilter(OB, rbind(bordering, I))
    TopB = argmin(BOR, uppermost)
    BotB = argmax(BOR, lowermost)
    cT = color(TopB)
    cB = color(BotB)
    R0 = hfrontier(astuple(ZERO, ZERO))
    Rb = hfrontier(astuple(subtract(H, ONE), ZERO))
    NB = difference(asindices(I), ofcolor(I, BG))
    TNB = intersection(NB, FT)
    BNB = intersection(NB, FB)
    Tbox = box(TNB)
    Bbox = box(BNB)
    Tmask = difference(intersection(Tbox, FT), R0)
    Bmask = difference(intersection(Bbox, FB), Rb)
    C = canvas(BG, shape(I))
    O0 = fill(C, cT, Tmask)
    O1 = fill(O0, cB, Bmask)
    O2 = fill(O1, cT, R0)
    O = fill(O2, cB, Rb)
    return O
```
training 137eaa0f train 0.0 25.86747618042385 2.1111111111111107 0.0 27.978587291534964
```python
def dsl2(I):
    OB = objects(I, T, F, T)
    O1 = argmax(OB, size)
    R1 = remove(O1, OB)
    O2 = argmax(R1, size)
    R2 = remove(O2, R1)
    O3 = argmax(R2, size)
    T3 = insert(O3, insert(O2, initset(O1)))
    Top = argmin(T3, uppermost)
    Rm1 = remove(Top, T3)
    Mid = argmin(Rm1, uppermost)
    Rm2 = remove(Mid, Rm1)
    Bot = first(Rm2)
    def row_of(c):
        return hconcat(hconcat(canvas(c, UNITY), canvas(c, UNITY)), canvas(c, UNITY))
    O = vconcat(vconcat(row_of(color(Top)), row_of(color(Mid))), row_of(color(Bot)))
    return O
```
training 03560426 train 0.0 27.318968132709657 0.2699999999999999 0.39039432750857245 27.979362460218223
```python
def dsl3(I):
    A = objects(I, T, F, T)
    LM = compose(leftmost, toindices)
    AO = order(A, LM)
    O1 = first(AO)
    AO2 = remove(O1, AO)
    O2 = first(AO2)
    AO3 = remove(O2, AO2)
    O3 = first(AO3)
    I1 = toindices(O1)
    I2 = toindices(O2)
    I3 = toindices(O3)
    ul1 = ulcorner(I1)
    ul2 = ulcorner(I2)
    ul3 = ulcorner(I3)
    lr1 = lrcorner(I1)
    lr2 = lrcorner(I2)
    P1 = shift(I1, invert(ul1))
    off2 = add(subtract(lr1, ul1), invert(ul2))
    P2 = shift(I2, off2)
    off3 = add(add(subtract(lr1, ul1), subtract(lr2, ul2)), invert(ul3))
    P3 = shift(I3, off3)
    Q1 = recolor(color(O1), P1)
    Q2 = recolor(color(O2), P2)
    Q3 = recolor(color(O3), P3)
    U = merge(insert(Q3, insert(Q2, initset(Q1))))
    IU = toindices(U)
    B = inbox(IU)
    HB = height(B)
    WB = width(B)
    Z = canvas(ZERO, astuple(HB, WB))
    G = paint(Z, U)
    H = height(I)
    W = width(I)
    Zb = canvas(ZERO, astuple(subtract(H, HB), WB))
    V = vconcat(G, Zb)
    Zr = canvas(ZERO, astuple(H, subtract(W, WB)))
    O = hconcat(V, Zr)
    return O
```
training 17b866bd train 0.0 28.844410203711913 0.038690476190476164 0.0 28.883100679902387
```python
def dsl2(I):
    # Object extraction: for each non-0, non-8 object, stamp a 4x4 diamond of its color at incremented ul-corner; erase seeds
    objs = objects(I, T, F, F)
    non0 = difference(objs, colorfilter(objs, ZERO))
    seeds = difference(non0, colorfilter(non0, EIGHT))
    ul = compose(increment, ulcorner)
    dims = double(TWO_BY_TWO)
    off = decrement(dims)
    lr = compose(rbind(add, off), ul)
    cset = fork(combine, compose(initset, ul), compose(initset, lr))
    rect = compose(backdrop, cset)
    diamond = fork(difference, rect, compose(corners, rect))
    col = compose(color, identity)
    recol = apply(fork(recolor, col, diamond), seeds)
    obj = merge(recol)
    sidxs = apply(toindices, seeds)
    spatch = merge(sidxs)
    base = fill(I, ZERO, spatch)
    O = paint(base, obj)
    return O
```
training 1b59e163 train 0.0 29.56330848354861 0.17592592592592593 0.0 29.739234409474534
```python
def dsl1(I):
    # Global: shift cropped foreground so its right edge aligns to grid's right edge
    J = replace(I, FIVE, FOUR)
    allidx = asindices(J)
    fg = difference(allidx, ofcolor(J, FOUR))
    S = subgrid(fg, J)
    sidx = asindices(S)
    sfg = difference(sidx, ofcolor(S, FOUR))
    src = toobject(sfg, S)
    v = subtract(urcorner(allidx), lrcorner(sfg))
    O = move(canvas(FOUR, shape(J)), src, v)
    return O
```
training 182e5d0f train 0.0 31.796228906028478 0.20758912265322516 0.0 32.00381802868171
```python
def dsl1(I):
    z = ofcolor(I, ZERO)
    th = ofcolor(I, THREE)
    fives = ofcolor(I, FIVE)
    orth = merge(mapply(neighbors, z))
    diag = merge(mapply(ineighbors, z))
    keep3 = intersection(th, orth)
    mark5_from3 = difference(intersection(th, diag), keep3)
    keep5 = intersection(fives, combine(orth, diag))
    base = replace(replace(I, FIVE, SEVEN), THREE, SEVEN)
    with3 = fill(base, THREE, keep3)
    with5a = fill(with3, FIVE, mark5_from3)
    O = fill(with5a, FIVE, keep5)
    return O
```
training 14754a24 train 0.0 33.29554569091714 0.13029448621553885 0.0 33.425840177132685
```python
def dsl2(I):
    # 5s strictly between two 4s along pure axial segments (only 4/5 on the path)
    fou = ofcolor(I, FOUR)
    fiv = ofcolor(I, FIVE)
    segs = prapply(connect, fou, fou)
    axial = sfilter(segs, fork(either, hline, vline))
    allowed = combine(fou, fiv)
    pure = sfilter(axial, matcher(compose(size, rbind(difference, allowed)), ZERO))
    mask = intersection(merge(pure), fiv)
    O = fill(I, TWO, mask)
    return O
```
training 15663ba9 train 0.0 37.831760318526534 0.3358739551047243 0.0 38.167634273631265
```python
def dsl1(I):
    # Global: frontier pixels of leastcolor get 4; their neighbors inside S get 2
    c = leastcolor(I)
    S = ofcolor(I, c)
    frobjs = frontiers(I)
    frparts = apply(toindices, frobjs)
    Fr = merge(frparts)
    E = intersection(S, Fr)
    N1 = combine(shift(E, LEFT), shift(E, RIGHT))
    N2 = combine(shift(E, UP), shift(E, DOWN))
    N = intersection(combine(N1, N2), S)
    G = fill(I, FOUR, E)
    O = fill(G, TWO, N)
    return O
```
training 15113be4 train 0.0 41.39513950544653 0.056710775047258966 0.0 41.45185028049379
```python
def dsl3(I):
    # Color filtering: recolor ones on the outline (box) of the least-color region
    val = leastcolor(I)
    ring = box(ofcolor(I, val))
    target = intersection(ring, ofcolor(I, ONE))
    O = fill(I, val, target)
    return O
```
training 09c534e7 train 0.0 42.05826595696517 0.2059567901234568 0.0 42.26422274708863
```python
def dsl4(I):
    FG = fgpartition(I)
    Seeds = difference(FG, colorfilter(FG, ONE))
    ones = ofcolor(I, ONE)
    outline = compose(box, toindices)
    maskf = compose(lbind(intersection, ones), outline)
    recolorf = fork(recolor, color, maskf)
    Paints = mapply(recolorf, Seeds)
    O = paint(I, Paints)
    return O
```
training 1b8318e3 train 0.0 43.204440451644146 0.14555555555555555 0.08249579111481943 43.432491798314516
```python
def dsl3(I):
    # O = keep all objects whose colors occur within the per-5 inbox area
    objs = objects(I, T, F, T)
    fives = colorfilter(objs, FIVE)
    perin = merge(apply(compose(inbox, toindices), fives))
    cols = palette(toobject(perin, I))
    isok = compose(rbind(contained, cols), color)
    keep = sfilter(objs, isok)
    O = paint(canvas(ZERO, shape(I)), merge(keep))
    return O
```
training 13f06aa5 train 0.0 44.74143209076087 0.45379342879342877 0.0 45.19522551955429
```python
def dsl2(I):
    Os = objects(I, T, F, T)
    S = argmin(Os, size)
    P = box(toindices(S))
    c = color(S)
    O = paint(I, recolor(c, P))
    return O
```
training 150deff5 train 0.0 46.970562748477136 0.2464646464646465 0.0 47.21702739494179
```python
def dsl5(I):
    p5 = ofcolor(I, FIVE)
    hasL = intersection(p5, shift(p5, LEFT))
    hasR = intersection(p5, shift(p5, RIGHT))
    hasU = intersection(p5, shift(p5, UP))
    hasD = intersection(p5, shift(p5, DOWN))
    hbridge = intersection(hasL, hasR)
    vbridge = intersection(hasU, hasD)
    noV = difference(hbridge, combine(hasU, hasD))
    noH = difference(vbridge, combine(hasL, hasR))
    mask = combine(noV, noH)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O
```
training 00d62c1b train 0.0 51.00519409487307 0.31305555555555553 0.0 51.31824965042862
```python
def dsl5(I):
    # Relational/structural: zeros inside any 3-object bbox but not near bbox border
    O3 = colorfilter(objects(I, T, F, T), THREE)
    BBs = merge(apply(backdrop, O3))
    Boxes = merge(apply(box, O3))
    NearBorder = merge(apply(dneighbors, Boxes))
    Z = ofcolor(I, ZERO)
    InBBoxes = intersection(Z, BBs)
    Deep = difference(InBBoxes, NearBorder)
    A = ofcolor(I, THREE)
    H = intersection(Deep, delta(A))
    O = underfill(I, FOUR, H)
    return O
```
training 1c02dbbe train 0.0 53.271497669750204 0.7955555555555555 0.0 54.06705322530576
```python
def dsl1(I):
    # Global (crop + remap): solve inside FIVE-bbox, then shift back to original coords
    dims = shape(I)
    base = canvas(ZERO, dims)
    fidx = ofcolor(I, FIVE)
    fbase = fill(base, FIVE, fidx)
    sub = subgrid(fidx, I)
    sdim = shape(sub)
    sbase = fill(canvas(ZERO, sdim), FIVE, ofcolor(sub, FIVE))
    sobjs = objects(sub, T, F, T)
    seeds = difference(sobjs, colorfilter(sobjs, FIVE))
    hin5 = compose(rbind(intersection, ofcolor(sub, FIVE)), compose(hfrontier, center))
    vin5 = compose(rbind(intersection, ofcolor(sub, FIVE)), compose(vfrontier, center))
    hseg = fork(recolor, color, hin5)
    vseg = fork(recolor, color, vin5)
    nonempty = compose(positive, compose(size, toindices))
    H = sfilter(apply(hseg, seeds), nonempty)
    V = sfilter(apply(vseg, seeds), nonempty)
    pairs = product(H, V)
    samec = fork(equality, compose(color, first), compose(color, last))
    ip = fork(intersection, compose(toindices, first), compose(toindices, last))
    cross = compose(positive, size)
    match = fork(both, samec, compose(cross, ip))
    pp = sfilter(pairs, match)
    tf = compose(toindices, first)
    tl = compose(toindices, last)
    bboxuv = compose(backdrop, fork(combine, tf, tl))
    cfirst = compose(color, first)
    rectpair = fork(recolor, cfirst, bboxuv)
    rectobj = merge(apply(rectpair, pp))
    Osub = paint(sbase, rectobj)
    non5 = difference(objects(Osub, T, F, T), colorfilter(objects(Osub, T, F, T), FIVE))
    ul = ulcorner(fidx)
    shifter = rbind(shift, ul)
    lift = fork(recolor, color, compose(shifter, toindices))
    lifted = merge(apply(lift, non5))
    O = paint(fbase, lifted)
    return O
```
training 045e512c train 0.0 54.10422280336664 0.22448979591836737 0.6444139582387098 54.97312655752371
```python
def dsl2(I):
    # O = fill each object's bounding box with the object's color (object extraction)
    objs = objects(I, T, F, T)
    bb = compose(backdrop, toindices)
    stamped = apply(fork(recolor, color, bb), objs)
    O = paint(canvas(ZERO, shape(I)), merge(stamped))
    return O
```
training 0a1d4ef5 train 1.0 43.08078929078196 16.11111111111111 0.12803687976896155 60.319937281662035
```python
def dsl2(I):
    # Object extraction: per tile, choose largest filled rectangle object (delta size == 0), else 0; assemble and crop
    U = UNITY; z = ZERO
    d10 = astuple(TEN, TEN); d8 = astuple(EIGHT, EIGHT); off = UNITY
    def tile_rect(r0, c0):
        X = crop(I, astuple(r0, c0), d10)
        C = crop(X, off, d8)
        Os = objects(C, T, F, T)
        rrect = compose(lbind(equality, z), compose(size, delta))
        R = sfilter(Os, rrect)
        pick = branch(equality(size(R), z), z, color(argmax(R, size)))
        return pick
    c00 = tile_rect(z, z);      c01 = tile_rect(z, TEN);      c02 = tile_rect(z, double(TEN))
    c10 = tile_rect(TEN, z);    c11 = tile_rect(TEN, TEN);    c12 = tile_rect(TEN, double(TEN))
    c20 = tile_rect(double(TEN), z); c21 = tile_rect(double(TEN), TEN); c22 = tile_rect(double(TEN), double(TEN))
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O
```
training 18447a8d train 0.0 64.05900585427788 0.580556698203757 0.0 64.63956255248164
```python
def dsl3(I):
    E = ofcolor(I, EIGHT)
    OA = objects(I, T, F, T)
    ON = difference(OA, colorfilter(OA, EIGHT))
    VE = vfrontier(urcorner(inbox(E)))
    G = rbind(gravitate, VE)
    D = apply(G, ON)
    M = papply(shift, ON, D)
    U = merge(M)
    B = cover(I, merge(ON))
    O = underpaint(B, U)
    return O
```
training 12422b43 train 0.0 63.96214177009765 0.7647252747252747 0.24355718058517115 64.9704242254081
```python
def dsl1(I):
    # Global: crop the FIVE band, erase FIVE via replace, and tile its nonzero content downward by its height
    A = ofcolor(I, FIVE)
    top = uppermost(A)
    bot = lowermost(A)
    k = add(subtract(bot, top), ONE)
    W = width(I)
    B = crop(I, astuple(top, ZERO), astuple(k, W))
    Clean = replace(B, FIVE, ZERO)
    Sel = difference(asindices(Clean), ofcolor(Clean, ZERO))
    P = toobject(Sel, Clean)
    Base = shift(P, toivec(top))
    vec = multiply(DOWN, k)
    n = divide(height(I), k)
    Offs = apply(lbind(multiply, vec), interval(ONE, n, ONE))
    U = mapply(lbind(shift, Base), Offs)
    O = underpaint(I, U)
    return O
```
training 1d0a4b61 train 0.0 74.00842223237059 0.3408000000000001 0.0 74.3492222323706
```python
def dsl4(I):
    # Geometric: anchor at UL corner on pattern-only mask to read row/col periods, then tile
    BG = mostcolor(I)
    NZ = difference(asindices(I), combine(ofcolor(I, ZERO), ofcolor(I, BG)))
    U = toobject(NZ, I)
    V = toindices(U)
    ul = ulcorner(U)
    row = hfrontier(ul)
    col = vfrontier(ul)
    rp = intersection(V, row)
    cp = intersection(V, col)
    orow = toobject(rp, I)
    ocol = toobject(cp, I)
    hp = hperiod(orow)
    vp = vperiod(ocol)
    r = tojvec(hp)
    d = toivec(vp)
    K = interval(invert(EIGHT), add(EIGHT, ONE), ONE)
    HV = apply(lbind(multiply, r), K)
    DV = apply(lbind(multiply, d), K)
    OFF = prapply(add, HV, DV)
    S = merge(apply(lbind(shift, U), OFF))
    O = underpaint(I, S)
    return O
```
training 1190bc91 train 0.0 79.68975381188855 1.335 0.0 81.02475381188856
```python
def dsl5(I):
    # Relational: from each object's center, shoot toward UL and LR corners
    FG = fgpartition(I)
    GRID = asindices(I)
    UL = ulcorner(GRID)
    LR = lrcorner(GRID)
    PUL = initset(UL)
    PLR = initset(LR)
    DIR_UL = compose(sign, rbind(position, PUL))
    DIR_LR = compose(sign, rbind(position, PLR))
    SD0 = compose(initset, DIR_UL)
    DIRS = fork(insert, DIR_LR, SD0)
    START = compose(initset, compose(center, toindices))
    R0 = lbind(prapply, shoot)
    RAW = fork(R0, START, DIRS)
    PFN = compose(merge, RAW)
    RC = fork(recolor, color, PFN)
    PARTS = apply(RC, FG)
    OBJ = merge(PARTS)
    O = underpaint(I, OBJ)
    return O
```
training 1be83260 train 0.0 82.73136007600414 2.0 0.6830324584321766 85.41439253443633
```python
def dsl3(I):
    # Color filtering: remove the dominant color and keep only non-dominant objects on a zero canvas
    NZI = difference(asindices(I), ofcolor(I, ZERO))
    A = subgrid(NZI, I)
    OBJS = objects(A, T, F, T)
    DOM = mostcolor(merge(OBJS))
    OTH = difference(OBJS, colorfilter(OBJS, DOM))
    O = paint(canvas(ZERO, shape(A)), merge(OTH))
    return O
```
training 09629e4f train 0.0 88.04519379887188 1.115702479338843 0.0 89.16089627821071
```python
def dsl3(I):
    G = replace(I, EIGHT, ZERO)
    C = compress(G)
    TT = astuple(THREE, THREE)
    P2 = ofcolor(C, TWO)
    P3 = ofcolor(C, THREE)
    P4 = ofcolor(C, FOUR)
    P6 = ofcolor(C, SIX)
    M2 = divide(center(P2), TT)
    M3 = divide(center(P3), TT)
    M4 = divide(center(P4), TT)
    M6 = divide(center(P6), TT)
    PIX = asindices(canvas(ZERO, astuple(ONE, ONE)))
    S2 = recolor(TWO, shift(PIX, M2))
    S3 = recolor(THREE, shift(PIX, M3))
    S4 = recolor(FOUR, shift(PIX, M4))
    S6 = recolor(SIX, shift(PIX, M6))
    ALL = combine(combine(S2, S3), combine(S4, S6))
    A3 = paint(canvas(ZERO, TT), ALL)
    U9 = hupscale(vupscale(A3, THREE), THREE)
    UL = crop(U9, astuple(ZERO, ZERO), TT)
    UM = crop(U9, astuple(ZERO, THREE), TT)
    UR = crop(U9, astuple(ZERO, SIX), TT)
    ML = crop(U9, astuple(THREE, ZERO), TT)
    MM = crop(U9, astuple(THREE, THREE), TT)
    MR = crop(U9, astuple(THREE, SIX), TT)
    BL = crop(U9, astuple(SIX, ZERO), TT)
    BM = crop(U9, astuple(SIX, THREE), TT)
    BR = crop(U9, astuple(SIX, SIX), TT)
    VBAR = canvas(FIVE, astuple(THREE, ONE))
    R1 = hconcat(hconcat(UL, VBAR), hconcat(UM, hconcat(VBAR, UR)))
    R2 = hconcat(hconcat(ML, VBAR), hconcat(MM, hconcat(VBAR, MR)))
    R3 = hconcat(hconcat(BL, VBAR), hconcat(BM, hconcat(VBAR, BR)))
    W = width(R1)
    HBAR = canvas(FIVE, astuple(ONE, W))
    O = vconcat(vconcat(R1, HBAR), vconcat(R2, vconcat(HBAR, R3)))
    return O
```
training 1c56ad9f train 0.0 88.87615686537718 0.4121611721611721 0.138140602982528 89.42645864052088
```python
def dsl1(I):
    u = merge(objects(I, T, F, T))
    ui = toindices(u)
    bd = backdrop(ui)
    inside = difference(bd, ui)
    col = color(u)
    ul = ulcorner(inside)
    ur = urcorner(inside)
    ll = llcorner(inside)
    lr = lrcorner(inside)
    dmain = connect(ul, lr)
    danti = connect(ur, ll)
    mask = intersection(combine(dmain, danti), inside)
    O = underpaint(I, recolor(col, mask))
    return O
```
training 0607ce86 train 0.0 91.15847539096545 0.5331861814075253 0.17753431043641554 91.86919588280938
```python
def dsl3(I):
    O = replace(I, THREE, ZERO)
    return O
```
training 184a9768 train 0.0 105.10653954156172 0.9095915678524374 2.139031999557692 108.15516310897183
```python
def dsl2(I):
    # Keep only edge-touching objects and rectangularize them (fixed bordering binding)
    I2 = replace(I, FIVE, ZERO)
    objs = objects(I2, T, F, T)
    keep = sfilter(objs, rbind(bordering, I2))
    rects = apply(fork(recolor, color, inbox), keep)
    O = paint(canvas(ZERO, shape(I)), merge(rects))
    return O
```
training 10fcaaa3 train 0.0 127.169398093881 1.3041666666666667 0.27290152574878 128.74646628629645
```python
def dsl5(I):
    T0 = hconcat(I, I)
    TT = vconcat(T0, T0)
    h = height(I)
    w = width(I)
    offR = tojvec(w)
    offD = toivec(h)
    offRD = add(offR, offD)
    C11 = crop(TT, ORIGIN, astuple(h, w))
    C12 = crop(TT, offR, astuple(h, w))
    C21 = crop(TT, offD, astuple(h, w))
    C22 = crop(TT, offRD, astuple(h, w))
    B11 = box(asindices(C11))
    B12 = shift(box(asindices(C12)), offR)
    B21 = shift(box(asindices(C21)), offD)
    B22 = shift(box(asindices(C22)), offRD)
    c11 = center(B11)
    c12 = center(B12)
    c21 = center(B21)
    c22 = center(B22)
    Lh1 = connect(c11, c12)
    Lh2 = connect(c21, c22)
    Lv1 = connect(c11, c21)
    Lv2 = connect(c12, c22)
    L = combine(combine(Lh1, Lh2), combine(Lv1, Lv2))
    Z = ofcolor(TT, ZERO)
    M = intersection(L, Z)
    O = fill(TT, EIGHT, M)
    return O
```
training 0e206a2e train 0.0 128.01837663381397 0.6024801587301586 0.4673445197186872 129.0882013122628
```python
def dsl1(I):
    # Global: draw the bounding box of the entire foreground with the dominant nonzero color
    colors = remove(ZERO, palette(I))
    L = argmax(colors, lbind(colorcount, I))
    objs = objects(I, T, F, T)
    fg = merge(objs)
    edge = box(fg)
    base = replace(I, L, ZERO)
    O = underfill(base, L, edge)
    return O
```
training 17b80ad2 train 0.0 138.20066244322436 1.4559948878031315 0.0 139.65665733102753
```python
def dsl5(I):
    # Relational/propagation: initialize top segments, then propagate colors downward via repeated underpaint of shifted objects
    idx = asindices(I)
    nz = difference(idx, ofcolor(I, ZERO))
    toobj = rbind(toobject, I)
    getc = compose(color, compose(toobj, initset))
    vcol = vfrontier
    topcol = compose(ulcorner, vcol)
    colnz = compose(lbind(intersection, nz), vcol)
    topnz = compose(ulcorner, colnz)
    seg_up = fork(connect, topcol, topnz)
    col_topc = compose(getc, topnz)
    obj_up = fork(recolor, col_topc, seg_up)
    topobjs = merge(apply(obj_up, nz))
    G0 = underpaint(I, topobjs)
    # Define one downward-propagation step on a grid
    idxf = asindices
    zerof = rbind(ofcolor, ZERO)
    nzindsf = fork(difference, idxf, zerof)
    nzobjf = fork(toobject, nzindsf, identity)
    shiftd = rbind(shift, DOWN)
    objdownf = compose(shiftd, nzobjf)
    step = fork(underpaint, identity, objdownf)
    relax = power(step, 30)
    O = relax(G0)
    return O
```
training 05a7bcf2 train 0.0 313.1782182682616 0.9255555555555556 0.16499158225741664 314.2687654060746
```python
def dsl4(I):
    J = hmirror(I)
    Obj = asobject(J)
    O = underpaint(I, Obj)
    return O
```
training 0bb8deee train 10.70820393249937 0 304 0.527392727891763 315.23559666039114
```python
def dsl1(I):
    P = remove(ZERO, palette(I))
    mc = argmax(P, lbind(colorcount, I))
    crossobj = toobject(ofcolor(I, mc), I)
    O = compress(cover(I, crossobj))
    return O
```
training 15660dd6 train 27.82705496754701 215 703 0.6632308266158871 946.4902857941629
```python
def dsl1(I):
    # Global: compress both axes via rotation
    A = compress(I)
    B = rot90(A)
    C = compress(B)
    O = rot270(C)
    return O
```
training 1a6449f1 train 30.480087153127815 470 513 1.1366732267849335 1014.6167603799126
```python
def dsl4(I):
    # Geometric: union of border-touching dominant-color objects, crop away 1-pixel frame, then trim
    mc = argmax(remove(ZERO, palette(I)), lbind(colorcount, I))
    os = colorfilter(objects(I, T, F, T), mc)
    bord = sfilter(os, rbind(bordering, I))
    frame = merge(bord)
    bbgrid = subgrid(backdrop(frame), I)
    core = crop(bbgrid, UNITY, subtract(shape(bbgrid), TWO_BY_TWO))
    O = trim(core)
    return O
```
training 06df4c85 train nan nan nan nan nan
```python
def dsl1(I):
    D = downscale(I, TWO)
    lcd = mostcolor(D)
    obs = objects(D, T, F, T)
    seeds = sizefilter(difference(obs, colorfilter(obs, lcd)), ONE)
    prs = product(seeds, seeds)
    samec = fork(equality, compose(color, first), compose(color, last))
    samerow = fork(equality, compose(uppermost, first), compose(uppermost, last))
    samecol = fork(equality, compose(leftmost, first), compose(leftmost, last))
    hprs = sfilter(prs, fork(both, samec, samerow))
    vprs = sfilter(prs, fork(both, samec, samecol))
    hseg = mapply(fork(recolor, compose(color, first), compose(connect, compose(center, first), compose(center, last))), hprs)
    vseg = mapply(fork(recolor, compose(color, first), compose(connect, compose(center, first), compose(center, last))), vprs)
    J = underpaint(D, combine(hseg, vseg))
    U = upscale(J, TWO)
    O = underpaint(I, asobject(U))
    return O
```
training 103eff5b train nan nan nan nan nan
```python
def dsl1(I):
    pix8 = ofcolor(I, EIGHT)
    base = cover(I, pix8)
    ul8 = ulcorner(pix8)
    tile8 = asobject(crop(I, ul8, THREE_BY_THREE))
    bbox3 = backdrop(tile8)
    small = downscale(I, THREE)
    small8 = ofcolor(small, EIGHT)
    objs_small = objects(small, T, F, T)
    seeds_small = difference(objs_small, colorfilter(objs_small, EIGHT))
    cen_obj = compose(rbind(toobject, small), compose(initset, identity))
    comp_builder = compose(lbind(rbind, manhattan), cen_obj)
    nearest_seed = chain(lbind(argmin, seeds_small), comp_builder, identity)
    to_ul = compose(lbind(multiply, THREE_BY_THREE), identity)
    place = compose(lbind(shift, bbox3), to_ul)
    recol = fork(recolor, compose(color, nearest_seed), place)
    recolored = apply(recol, small8)
    O = paint(base, merge(recolored))
    return O
```
training 11e1fe23 test nan nan nan nan nan
```python
def dsl3(I):
    objs = objects(I, T, F, T)
    P = merge(objs)
    C = centerofmass(P)
    f = lambda o: shift(o, multiply(TWO, sign(subtract(C, center(o)))))
    shifted = apply(f, objs)
    Sobj = merge(shifted)
    G1 = underpaint(I, Sobj)
    centers = apply(center, shifted)
    conns = prapply(connect, centers, centers)
    lines3 = sizefilter(conns, 3)
    diagcond = fork(both, compose(flip, hline), compose(flip, vline))
    dline = first(sfilter(lines3, diagcond))
    mid = centerofmass(dline)
    O = fill(G1, FIVE, initset(mid))
    return O
```
training 17cae0c1 train nan nan nan nan nan
```python
def dsl1(I):
    a, b, c = vsplit(I, THREE)
    def classify(p):
        r1, r2, r3 = hsplit(p, THREE)
        c1, c2, c3 = vsplit(p, THREE)
        n1 = colorcount(r1, FIVE)
        n2 = colorcount(r2, FIVE)
        n3 = colorcount(r3, FIVE)
        m1 = colorcount(c1, FIVE)
        m2 = colorcount(c2, FIVE)
        m3 = colorcount(c3, FIVE)
        A = ofcolor(p, FIVE)
        s = size(A)
        ring = both(equality(s, EIGHT), both(equality(n1, THREE), both(equality(n3, THREE), equality(m2, TWO))))
        topline = both(equality(n1, THREE), both(equality(n2, ZERO), equality(n3, ZERO)))
        bottomline = both(equality(n3, THREE), both(equality(n2, ZERO), equality(n1, ZERO)))
        diag3 = both(equality(s, THREE), both(both(equality(n1, ONE), both(equality(n2, ONE), equality(n3, ONE))),
                                             both(equality(m1, ONE), both(equality(m2, ONE), equality(m3, ONE))))))
        single = equality(s, ONE)
        return branch(ring, THREE, branch(topline, SIX, branch(bottomline, ONE, branch(diag3, NINE, branch(single, FOUR, THREE)))))
    O = hconcat(hconcat(canvas(classify(a), shape(a)), canvas(classify(b), shape(b))), canvas(classify(c), shape(c)))
    return O
```
training 18419cfa train nan nan nan nan nan
```python
def dsl1(I):
    # Object extraction: mirror 2s left-right inside each 8-enclosed interior and reproject
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    Ifn = fork(difference, inbox, box)
    Gint = compose(rbind(subgrid, I), Ifn)
    Vm = compose(vmirror, Gint)
    Tw = compose(rbind(ofcolor, TWO), Vm)
    Ul = compose(ulcorner, Ifn)
    Sr = fork(shift, Tw, Ul)
    P = merge(mapply(Sr, EO))
    O = underpaint(I, recolor(TWO, P))
    return O
```
training 1990f7a8 test nan nan nan nan nan
```python
def dsl1(I):
    # Global transformation via bbox crop and quadrant halving
    m = ofcolor(I, TWO)
    bb = subgrid(m, I)
    top = tophalf(bb)
    bottom = bottomhalf(bb)
    tl = lefthalf(top)
    tr = righthalf(top)
    bl = lefthalf(bottom)
    br = righthalf(bottom)
    gtl = subgrid(ofcolor(tl, TWO), tl)
    gtr = subgrid(ofcolor(tr, TWO), tr)
    gbl = subgrid(ofcolor(bl, TWO), bl)
    gbr = subgrid(ofcolor(br, TWO), br)
    zcolT = canvas(ZERO, astuple(height(gtl), ONE))
    zcolB = canvas(ZERO, astuple(height(gbl), ONE))
    top7 = hconcat(hconcat(gtl, zcolT), gtr)
    bot7 = hconcat(hconcat(gbl, zcolB), gbr)
    mid = canvas(ZERO, astuple(ONE, width(top7)))
    O = vconcat(vconcat(top7, mid), bot7)
    return O
```
