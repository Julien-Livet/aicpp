training 3c9b0459 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = rot180(I)
    return O
```
training 6150a2bd 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = rot180(I)
    return O
```
training ed36ccf7 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = rot270(I)
    return O
```
training 67a3c6ac 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = vmirror(I)
    return O
```
training 68b16354 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = hmirror(I)
    return O
```
training 74dd1130 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = dmirror(I)
    return O
```
training 9dfd6313 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = dmirror(I)
    return O
```
training a416b8f3 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = hconcat(I, I)
    return O
```
training c59eb873 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = upscale(I, TWO)
    return O
```
training 9172f3a0 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = upscale(I, THREE)
    return O
```
training b1948b0a 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = replace(I, SIX, TWO)
    return O
```
training 4c4377d9 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = vconcat(hmirror(I), I)
    return O
```
training 6d0aefbc 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = hconcat(I, vmirror(I))
    return O
```
training 6fa7a44f 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = vconcat(I, hmirror(I))
    return O
```
training 8be77c9e 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = vconcat(I, hmirror(I))
    return O
```
training d511f180 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = switch(I, FIVE, EIGHT)
    return O
```
training c8f0f002 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = replace(I, SEVEN, FIVE)
    return O
```
training d10ecb37 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = crop(I, ORIGIN, TWO_BY_TWO)
    return O
```
training c9e6f938 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    x1 = vmirror(I)
    O = hconcat(I, x1)
    return O
```
training 5bd6f4ac 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = crop(I, tojvec(SIX), THREE_BY_THREE)
    return O
```
training 5614dbcf 0.0 0.0 0.0 0.0 0.0
```python
def dsl2(I):
    x1 = replace(I, FIVE, ZERO)
    O = downscale(x1, THREE)
    return O
```
training 5582e5ca 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    x1 = mostcolor(I)
    x2 = shape(I)
    O = canvas(x1, x2)
    return O
```
training c909285e 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    b = leastcolor(I)
    P = ofcolor(I, b)
    O = subgrid(P, I)
    return O
```
training be94b721 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    x1 = objects(I, T, F, T)
    x2 = argmax(x1, size)
    O = subgrid(x2, I)
    return O
```
training b91ae062 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    p = palette(I)
    p2 = remove(ZERO, p)
    n = size(p2)
    O = upscale(I, n)
    return O
```
training 28bf18c6 0.0 0.0 0.0 0.0 0.0
```python
def dsl2(I):
    c = leastcolor(I)
    p = ofcolor(I, c)
    g = subgrid(p, I)
    O = hconcat(g, g)
    return O
```
training 1cf80156 0.0 0.0 0.0 0.0 0.0
```python
def dsl2(I):
    x1 = asindices(I)
    x2 = ofcolor(I, ZERO)
    x3 = difference(x1, x2)
    O = subgrid(x3, I)
    return O
```
training 25ff71a9 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    x0 = asobject(I)
    x1 = shift(x0, DOWN)
    x2 = canvas(ZERO, shape(I))
    O = paint(x2, x1)
    return O
```
training cd3c21df 0.0 0.0 0.0 0.0 0.0
```python
def dsl2(I):
    x1 = fgpartition(I)
    f = compose(size, backdrop)
    x2 = argmin(x1, f)
    O = subgrid(x2, I)
    return O
```
training 50cb2852 0.0 0.0 0.0 0.0 0.0
```python
def dsl2(I):
    x1 = objects(I, T, F, T)
    f = compose(delta, box)
    x2 = mapply(f, x1)
    O = fill(I, EIGHT, x2)
    return O
```
training d631b094 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    c = other(palette(I), ZERO)
    n = colorcount(I, c)
    dims = astuple(ONE, n)
    O = canvas(c, dims)
    return O
```
training 2dee498d 0.0 0.0 0.0 0.0 0.0
```python
def dsl2(I):
    h = height(I)
    w = width(I)
    w3 = divide(w, THREE)
    dims = astuple(h, w3)
    O = crop(I, ORIGIN, dims)
    return O
```
training 0d3d703e 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    x1 = switch(I, ONE, FIVE)
    x2 = switch(x1, TWO, SIX)
    x3 = switch(x2, THREE, FOUR)
    O = switch(x3, EIGHT, NINE)
    return O
```
training 67e8384a 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    a = vmirror(I)
    b = hmirror(I)
    c = rot180(I)
    top = hconcat(I, a)
    bottom = hconcat(b, c)
    O = vconcat(top, bottom)
    return O
```
training 32597951 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    x8 = ofcolor(I, EIGHT)
    bb = backdrop(x8)
    ones = ofcolor(I, ONE)
    tgt = intersection(bb, ones)
    O = fill(I, THREE, tgt)
    return O
```
training ed98d772 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    A = I
    B = rot270(I)
    C = rot180(I)
    D = rot90(I)
    top = hconcat(A, B)
    bottom = hconcat(C, D)
    O = vconcat(top, bottom)
    return O
```
training 9f236235 0.0 0.0 0.0 0.0 0.0
```python
def dsl4(I):
    x1 = compress(I)
    x2 = objects(x1, T, F, T)
    x3 = extract(x2, square)
    x4 = height(x3)
    x5 = downscale(x1, x4)
    O = vmirror(x5)
    return O
```
training 27a77e38 0.0 0.0 0.0 0.0 0.0
```python
def dsl2(I):
    w = width(I)
    h = height(I)
    top = tophalf(I)
    c = mostcolor(top)
    p = initset(astuple(subtract(h, ONE), halve(w)))
    O = fill(I, c, p)
    return O
```
training d037b0a7 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    x1 = objects(I, T, F, T)
    f1 = compose(rbind(shoot, DOWN), ulcorner)
    f2 = fork(recolor, color, f1)
    x2 = mapply(f2, x1)
    O = underpaint(I, x2)
    return O
```
training 94f9d214 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    a = tophalf(I)
    b = bottomhalf(I)
    z1 = ofcolor(a, ZERO)
    z2 = ofcolor(b, ZERO)
    z = intersection(z1, z2)
    O = fill(canvas(ZERO, shape(a)), TWO, z)
    return O
```
training a699fb00 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    a = ofcolor(I, ONE)
    b = shift(a, RIGHT)
    c = shift(a, LEFT)
    m = intersection(b, c)
    z = ofcolor(I, ZERO)
    p = intersection(m, z)
    O = fill(I, TWO, p)
    return O
```
training 44f52bb0 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    x1 = vmirror(I)
    x2 = hmirror(I)
    c1 = equality(I, x1)
    c2 = equality(I, x2)
    cond = either(c1, c2)
    val = branch(cond, ONE, SEVEN)
    O = canvas(val, UNITY)
    return O
```
training 017c7c7b 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    x0 = replace(I, ONE, TWO)
    a = crop(x0, ORIGIN, THREE_BY_THREE)
    b = crop(x0, astuple(THREE, ZERO), THREE_BY_THREE)
    c = branch(equality(a, b), a, vmirror(a))
    O = vconcat(a, vconcat(b, c))
    return O
```
training d5d6de2d 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    x0 = objects(I, T, F, T)
    x1 = colorfilter(x0, TWO)
    f = fork(equality, toindices, box)
    x2 = sfilter(x1, f)
    x3 = mapply(delta, x2)
    x4 = canvas(ZERO, shape(I))
    O = fill(x4, THREE, x3)
    return O
```
training cf5fd0ad 0.0 0.0 0.0 0.0 0.0
```python
def dsl2(I):
    a = rot180(I)
    b = rot90(I)
    c = rot270(I)
    top = hconcat(hconcat(a, a), hconcat(b, b))
    bottom = hconcat(hconcat(c, c), hconcat(I, I))
    O = vconcat(vconcat(top, top), vconcat(bottom, bottom))
    return O
```
training 87ab05b8 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    p = first(ofcolor(I, TWO))
    s = multiply(halve(p), TWO)
    a = initset(s)
    b = insert(add(s, RIGHT), a)
    c = insert(add(s, DOWN), b)
    d = insert(add(add(s, DOWN), RIGHT), c)
    base = canvas(SIX, shape(I))
    O = fill(base, TWO, d)
    return O
```
training 623ea044 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    c = leastcolor(I)
    s = first(ofcolor(I, c))
    l1 = shoot(s, UP_RIGHT)
    l2 = shoot(s, DOWN_LEFT)
    l3 = shoot(s, NEG_UNITY)
    l4 = shoot(s, UNITY)
    u1 = combine(l1, l2)
    u2 = combine(l3, l4)
    u = combine(u1, u2)
    O = fill(I, c, u)
    return O
```
training 37ce87bb 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    H = height(I)
    W = width(I)
    j = subtract(W, TWO)
    c8 = colorcount(I, EIGHT)
    c2 = colorcount(I, TWO)
    h = subtract(c8, c2)
    start_row = subtract(H, h)
    start = astuple(start_row, j)
    patch = shoot(start, DOWN)
    O = fill(I, FIVE, patch)
    return O
```
training 03560426 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    dims = shape(I)
    O = canvas(ZERO, dims)
    obs = objects(I, T, F, T)
    seq = order(obs, leftmost)
    cur = ORIGIN
    for obj in seq:
        norm = normalize(obj)
        placed = shift(norm, cur)
        O = paint(O, placed)
        cur = lrcorner(placed)
    return O
```
training 6f473927 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    x1 = vmirror(I)
    x2 = replace(x1, ZERO, EIGHT)
    x3 = replace(x2, TWO, ZERO)
    h = height(I)
    c = crop(I, ORIGIN, astuple(h, ONE))
    cond = greater(colorcount(c, TWO), ZERO)
    left = branch(cond, x3, I)
    right = branch(cond, I, x3)
    O = hconcat(left, right)
    return O
```
training d8c310e9 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    x1 = rbind(objects, T)
    x2 = rbind(x1, F)
    x3 = rbind(x2, T)
    x4 = compose(merge, x3)
    obj0 = x4(I)
    p = hperiod(obj0)
    dir = astuple(ZERO, p)
    sh = rbind(shift, dir)
    shobj = compose(sh, x4)
    f = fork(underpaint, identity, shobj)
    n = width(I)
    powf = power(f, n)
    O = powf(I)
    return O
```
training 00dbd492 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    x0 = objects(I, T, F, T)
    x1 = colorfilter(x0, TWO)
    s16 = sizefilter(x1, 16)
    p16 = mapply(delta, s16)
    O0 = underfill(I, EIGHT, p16)
    s24 = sizefilter(x1, 24)
    p24 = mapply(delta, s24)
    O1 = underfill(O0, FOUR, p24)
    s32 = sizefilter(x1, 32)
    p32 = mapply(delta, s32)
    O = underfill(O1, THREE, p32)
    return O
```
training dce56571 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    h = height(I)
    w = width(I)
    c = leastcolor(I)
    k = colorcount(I, c)
    r = halve(h)
    diff = subtract(w, k)
    s = halve(diff)
    ek = add(s, k)
    e = decrement(ek)
    p1 = astuple(r, s)
    p2 = astuple(r, e)
    seg = connect(p1, p2)
    dims = astuple(h, w)
    base = canvas(EIGHT, dims)
    O = fill(base, c, seg)
    return O
```
training 5c0a986e 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    objs = objects(I, T, F, T)
    ones = colorfilter(objs, ONE)
    twos = colorfilter(objs, TWO)
    o1 = first(ones)
    o2 = first(twos)
    s1 = ulcorner(o1)
    s2 = lrcorner(o2)
    r = asindices(I)
    l1 = intersection(shoot(s1, NEG_UNITY), r)
    l2 = intersection(shoot(s2, UNITY), r)
    x = fill(I, ONE, l1)
    O = fill(x, TWO, l2)
    return O
```
training 363442ee 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    s = shape(I)
    O = canvas(ZERO, s)
    obj5 = recolor(FIVE, ofcolor(I, FIVE))
    O = paint(O, obj5)
    src = crop(I, ORIGIN, THREE_BY_THREE)
    sobj = asobject(src)
    O = paint(O, sobj)
    centers = ofcolor(I, ONE)
    dirs = apply(rbind(subtract, UNITY), centers)
    copies = mapply(lbind(shift, sobj), dirs)
    O = paint(O, copies)
    return O
```
training cf98881b 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    A = crop(I, astuple(0, 0), astuple(4, 4))
    B = crop(I, astuple(0, 5), astuple(4, 4))
    C = crop(I, astuple(0, 10), astuple(4, 4))
    non4 = difference(asindices(A), ofcolor(A, FOUR))
    p9 = intersection(ofcolor(B, NINE), non4)
    Y = fill(A, NINE, p9)
    p1 = difference(intersection(ofcolor(C, ONE), non4), p9)
    O = fill(Y, ONE, p1)
    return O
```
training 99b1bc43 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    x4 = ofcolor(I, FOUR)
    r = uppermost(x4)
    h = height(I)
    w = width(I)
    t = crop(I, astuple(0, 0), astuple(r, w))
    b = crop(I, astuple(add(r, ONE), 0), astuple(subtract(h, add(r, ONE)), w))
    a = ofcolor(t, ONE)
    c = ofcolor(b, TWO)
    x = combine(difference(a, c), difference(c, a))
    O = fill(canvas(ZERO, shape(t)), THREE, x)
    return O
```
training f0afb749 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    U = upscale(I, TWO)
    OB = objects(I, T, F, T)
    P0 = apply(ulcorner, OB)
    P = apply(double, P0)
    DR = add(DOWN, RIGHT)
    UL = add(UP, LEFT)
    dr = rbind(shoot, DR)
    ul = rbind(shoot, UL)
    a = compose(lrcorner, dr)
    b = compose(ulcorner, ul)
    linefun = fork(connect, a, b)
    L = mapply(linefun, P)
    O = underfill(U, ONE, L)
    return O
```
training 6a11f6da 0.0 0.0 0.0 0.0 0.0
```python
def dsl3(I):
    top = crop(I, astuple(0, 0), astuple(5, 5))
    mid = crop(I, astuple(5, 0), astuple(5, 5))
    bot = crop(I, astuple(10, 0), astuple(5, 5))
    o1 = toobject(ofcolor(top, ONE), top)
    o8 = toobject(ofcolor(mid, EIGHT), mid)
    o6 = toobject(ofcolor(bot, SIX), bot)
    base = canvas(ZERO, astuple(5, 5))
    a = underpaint(base, o8)
    b = paint(a, o1)
    O = paint(b, o6)
    return O
```
training 7e02026e 0.0 0.0 0.0 0.0 0.0
```python
def dsl2(I):
    S0 = ofcolor(I, ZERO)
    Sh = intersection(intersection(S0, shift(S0, LEFT)), shift(S0, RIGHT))
    Sv = intersection(intersection(S0, shift(S0, UP)), shift(S0, DOWN))
    C = intersection(Sh, Sv)
    arms_h = combine(shift(C, LEFT), shift(C, RIGHT))
    arms_v = combine(shift(C, UP), shift(C, DOWN))
    P = combine(C, combine(arms_h, arms_v))
    Z = intersection(P, S0)
    O = fill(I, THREE, Z)
    return O
```
training a85d4709 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    f = ofcolor(I, FIVE)
    c0 = vfrontier(ORIGIN)
    c1 = vfrontier(tojvec(ONE))
    c2 = vfrontier(tojvec(TWO))
    f0 = intersection(f, c0)
    f1 = intersection(f, c1)
    f2 = intersection(f, c2)
    r0 = mapply(hfrontier, f0)
    r1 = mapply(hfrontier, f1)
    r2 = mapply(hfrontier, f2)
    O0 = canvas(ZERO, shape(I))
    O1 = fill(O0, TWO, r0)
    O2 = fill(O1, FOUR, r1)
    O = fill(O2, THREE, r2)
    return O
```
training db3e9e38 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    P = ofcolor(I, SEVEN)
    H = height(P)
    Ds = interval(ZERO, H, ONE)
    dirs = combine(initset(RIGHT), initset(LEFT))
    def fun(d, s):
        v1 = toivec(invert(d))
        v2 = multiply(s, d)
        dir = add(v1, v2)
        Sft = shift(P, dir)
        c = branch(even(d), SEVEN, EIGHT)
        return recolor(c, Sft)
    objs = prapply(fun, Ds, dirs)
    obj = merge(objs)
    O = paint(canvas(ZERO, shape(I)), obj)
    return O
```
training 23581191 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    p8 = first(totuple(ofcolor(I, EIGHT)))
    p7 = first(totuple(ofcolor(I, SEVEN)))
    r8 = hfrontier(p8)
    c8 = vfrontier(p8)
    cross8 = combine(r8, c8)
    r7 = hfrontier(p7)
    c7 = vfrontier(p7)
    cross7 = combine(r7, c7)
    ov = intersection(cross8, cross7)
    base = canvas(ZERO, shape(I))
    o8 = recolor(EIGHT, cross8)
    o7 = recolor(SEVEN, cross7)
    O1 = paint(base, o8)
    O2 = paint(O1, o7)
    O = fill(O2, TWO, ov)
    return O
```
training ba97ae07 0.0 0.0 0.0 0.0 0.0
```python
def dsl2(I):
    cols = remove(ZERO, palette(I))
    f = lbind(ofcolor, I)
    hfun = compose(height, f)
    wfun = compose(width, f)
    comp = fork(subtract, hfun, wfun)
    vcol = argmax(cols, comp)
    hcol = other(cols, vcol)
    vp = ofcolor(I, vcol)
    hp = ofcolor(I, hcol)
    vb = backdrop(vp)
    hb = backdrop(hp)
    intr = intersection(vb, hb)
    rv = intersection(intr, vp)
    rh = intersection(intr, hp)
    x1 = fill(I, hcol, rv)
    O = fill(x1, vcol, rh)
    return O
```
training 4258a5f9 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    a = ofcolor(I, FIVE)
    s1 = shift(a, UP)
    s2 = shift(a, DOWN)
    s3 = shift(a, LEFT)
    s4 = shift(a, RIGHT)
    s5 = shift(a, UP_RIGHT)
    s6 = shift(a, DOWN_LEFT)
    s7 = shift(a, NEG_UNITY)
    s8 = shift(a, UNITY)
    u1 = combine(s1, s2)
    u2 = combine(s3, s4)
    u3 = combine(s5, s6)
    u4 = combine(s7, s8)
    u12 = combine(u1, u2)
    u34 = combine(u3, u4)
    nbrs = combine(u12, u34)
    nb_in = intersection(nbrs, asindices(I))
    O = underfill(I, ONE, nb_in)
    return O
```
training bdad9b1f 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    rpatch = ofcolor(I, TWO)
    cpatch = ofcolor(I, EIGHT)
    r = uppermost(rpatch)
    c = leftmost(cpatch)
    w = width(I)
    h = height(I)
    p1 = astuple(r, ZERO)
    p2 = astuple(r, subtract(w, ONE))
    rowline = connect(p1, p2)
    q1 = astuple(ZERO, c)
    q2 = astuple(subtract(h, ONE), c)
    colline = connect(q1, q2)
    O = paint(I, recolor(TWO, rowline))
    O = paint(O, recolor(EIGHT, colline))
    inter = connect(astuple(r, c), astuple(r, c))
    O = fill(O, FOUR, inter)
    return O
```
training 1d61978c 0.0 0.0 0.0 0.0 0.0
```python
def dsl5(I):
    # Data-driven orientation choice: larger diagonal family -> 8, other -> 2
    S = ofcolor(I, FIVE)
    S_ur = shift(S, UP_RIGHT)
    S_dl = shift(S, DOWN_LEFT)
    S_dr = shift(S, UNITY)
    S_ul = shift(S, NEG_UNITY)
    neg_slope = intersection(S, combine(S_ur, S_dl))
    pos_slope = intersection(S, combine(S_dr, S_ul))
    cond = greater(size(pos_slope), size(neg_slope))
    eight_set = branch(cond, pos_slope, neg_slope)
    A = replace(I, FIVE, TWO)
    obj8 = recolor(EIGHT, eight_set)
    O = paint(A, obj8)
    return O
```
training 981add89 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    bg = mostcolor(I)
    W = width(I)
    rowG = crop(I, (0, 0), (1, W))
    colors = remove(bg, palette(rowG))
    O = I
    row0 = shoot((0, 0), RIGHT)
    for c in totuple(colors):
        starts = intersection(ofcolor(I, c), row0)
        colpath = mapply(rbind(shoot, DOWN), starts)
        samecol = intersection(colpath, ofcolor(I, c))
        samecol_no_starts = difference(samecol, starts)
        O = fill(O, bg, samecol_no_starts)
        paintset = difference(colpath, samecol_no_starts)
        O = fill(O, c, paintset)
    return O
```
training 4a1cacc2 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    objs = fgpartition(I)
    obj = first(objs)
    i = uppermost(obj)
    j = leftmost(obj)
    H = height(I)
    W = width(I)
    topd = i
    botd = subtract(H, increment(i))
    leftd = j
    rightd = subtract(W, increment(j))
    Hm1 = subtract(H, ONE)
    Wm1 = subtract(W, ONE)
    rstar = branch(greater(topd, botd), Hm1, ZERO)
    cstar = branch(greater(leftd, rightd), Wm1, ZERO)
    p = astuple(i, j)
    q = astuple(rstar, cstar)
    s0 = initset(p)
    s = insert(q, s0)
    R = backdrop(s)
    col = color(obj)
    O = fill(I, col, R)
    return O
```
training 19bb5feb 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    g = subgrid(ofcolor(I, EIGHT), I)
    L = lefthalf(g)
    R = righthalf(g)
    TL = tophalf(L)
    TR = tophalf(R)
    BL = bottomhalf(L)
    BR = bottomhalf(R)
    cTL = leastcolor(TL)
    cTR = leastcolor(TR)
    cBL = leastcolor(BL)
    cBR = leastcolor(BR)
    vTL = branch(equality(cTL, EIGHT), ZERO, cTL)
    vTR = branch(equality(cTR, EIGHT), ZERO, cTR)
    vBL = branch(equality(cBL, EIGHT), ZERO, cBL)
    vBR = branch(equality(cBR, EIGHT), ZERO, cBR)
    r1 = hconcat(canvas(vTL, UNITY), canvas(vTR, UNITY))
    r2 = hconcat(canvas(vBL, UNITY), canvas(vBR, UNITY))
    O = vconcat(r1, r2)
    return O
```
training 77fdfe62 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    h = height(I)
    w = width(I)
    rlast = decrement(h)
    clast = decrement(w)
    tlc = index(I, astuple(ZERO, ZERO))
    trc = index(I, astuple(ZERO, clast))
    blc = index(I, astuple(rlast, ZERO))
    brc = index(I, astuple(rlast, clast))
    P = ofcolor(I, EIGHT)
    C = subgrid(P, I)
    top = tophalf(C)
    bot = bottomhalf(C)
    tl = lefthalf(top)
    tr = righthalf(top)
    bl = lefthalf(bot)
    br = righthalf(bot)
    tl2 = replace(tl, EIGHT, tlc)
    tr2 = replace(tr, EIGHT, trc)
    bl2 = replace(bl, EIGHT, blc)
    br2 = replace(br, EIGHT, brc)
    top2 = hconcat(tl2, tr2)
    bot2 = hconcat(bl2, br2)
    O = vconcat(top2, bot2)
    return O
```
training 025d127b 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = canvas(ZERO, shape(I))
    objs = objects(I, T, T, T)
    for obj in objs:
        inds = toindices(obj)
        # bottom row of the object
        bottom = intersection(inds, hfrontier(llcorner(obj)))
        # all non-bottom indices
        upper = difference(inds, bottom)
        # right-edge indices (by object's rightmost column)
        rightedge = intersection(upper, vfrontier(urcorner(obj)))
        # shift upper non-rightedge to the right by 1
        upper_move = shift(difference(upper, rightedge), RIGHT)
        newinds = merge((bottom, rightedge, upper_move))
        newobj = recolor(color(obj), newinds)
        O = paint(O, newobj)
    return O
```
training 97999447 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    objs = objects(I, T, F, T)
    W = width(I)
    def patt(o):
        j0 = rightmost(o)
        maxoff = subtract(subtract(W, ONE), j0)
        base = toindices(o)
        evn_offs = interval(ZERO, add(maxoff, ONE), TWO)
        evn_vecs = apply(tojvec, evn_offs)
        evn_patch = mapply(lbind(shift, base), evn_vecs)
        evn_obj = recolor(color(o), evn_patch)
        odd_offs = interval(ONE, add(maxoff, ONE), TWO)
        odd_vecs = apply(tojvec, odd_offs)
        odd_patch = mapply(lbind(shift, base), odd_vecs)
        odd_obj = recolor(FIVE, odd_patch)
        return combine(evn_obj, odd_obj)
    obj = mapply(patt, objs)
    O = paint(canvas(ZERO, shape(I)), obj)
    return O
```
training ff72ca3e 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    allidx = asindices(I)
    fives = ofcolor(I, FIVE)
    fours = colorfilter(objects(I, True, False, True), FOUR)
    acc = difference(allidx, allidx)
    h = height(I)
    w = width(I)
    bound = add(h, w)
    for o in totuple(fours):
        c = ulcorner(o)
        best = difference(allidx, allidx)
        for r in interval(ONE, bound, ONE):
            rv = multiply(UNITY, r)
            s = add(c, invert(rv))
            e = add(c, rv)
            okb = both(contained(s, allidx), contained(e, allidx))
            bb = backdrop(connect(s, e))
            okf = equality(size(intersection(bb, fives)), ZERO)
            best = branch(both(okb, okf), difference(bb, toindices(o)), best)
        acc = combine(acc, best)
    O = underfill(I, TWO, acc)
    return O
```
training ec883f72 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    objs = objects(I, T, F, T)
    base = argmax(objs, fork(multiply, height, width))
    basecol = color(base)
    cols = remove(ZERO, palette(I))
    minor = other(cols, basecol)
    dul = add(UP, LEFT)
    dur = add(UP, RIGHT)
    dll = add(DOWN, LEFT)
    drr = add(DOWN, RIGHT)
    ul = ulcorner(base)
    ur = urcorner(base)
    ll = llcorner(base)
    lr = lrcorner(base)
    s_ul = add(ul, dul)
    s_ur = add(ur, dur)
    s_ll = add(ll, dll)
    s_lr = add(lr, drr)
    A = asindices(I)
    r_ul = intersection(A, shoot(s_ul, dul))
    r_ur = intersection(A, shoot(s_ur, dur))
    r_ll = intersection(A, shoot(s_ll, dll))
    r_lr = intersection(A, shoot(s_lr, drr))
    rays = combine(combine(r_ul, r_ur), combine(r_ll, r_lr))
    obj = recolor(minor, rays)
    O = underpaint(I, obj)
    return O
```
training c3e719e8 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    c = mostcolor(I)
    z = canvas(ZERO, shape(I))
    p00 = branch(equality(index(I, astuple(ZERO, ZERO)), c), I, z)
    p01 = branch(equality(index(I, astuple(ZERO, ONE)), c), I, z)
    p02 = branch(equality(index(I, astuple(ZERO, TWO)), c), I, z)
    r0 = hconcat(p00, hconcat(p01, p02))
    p10 = branch(equality(index(I, astuple(ONE, ZERO)), c), I, z)
    p11 = branch(equality(index(I, astuple(ONE, ONE)), c), I, z)
    p12 = branch(equality(index(I, astuple(ONE, TWO)), c), I, z)
    r1 = hconcat(p10, hconcat(p11, p12))
    p20 = branch(equality(index(I, astuple(TWO, ZERO)), c), I, z)
    p21 = branch(equality(index(I, astuple(TWO, ONE)), c), I, z)
    p22 = branch(equality(index(I, astuple(TWO, TWO)), c), I, z)
    r2 = hconcat(p20, hconcat(p21, p22))
    O = vconcat(r0, vconcat(r1, r2))
    return O
```
training 8403a5d5 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    objs = fgpartition(I)
    seed = first(objs)
    k = color(seed)
    j0 = leftmost(seed)
    H = height(I)
    lastrow = subtract(H, ONE)
    base = connect(astuple(ZERO, j0), astuple(lastrow, j0))
    c1 = shift(base, ZERO_BY_TWO)
    c2 = shift(c1, ZERO_BY_TWO)
    c3 = shift(c2, ZERO_BY_TWO)
    c4 = shift(c3, ZERO_BY_TWO)
    cols = combine(combine(base, c1), combine(c2, combine(c3, c4)))
    cols = intersection(cols, asindices(I))
    stripes = recolor(k, cols)
    j1 = add(j0, ONE)
    j3 = add(j0, THREE)
    j5 = add(j0, FIVE)
    j7 = add(j0, SEVEN)
    j9 = add(j0, NINE)
    p1 = initset(astuple(ZERO, j1))
    p2 = initset(astuple(lastrow, j3))
    p3 = initset(astuple(ZERO, j5))
    p4 = initset(astuple(lastrow, j7))
    p5 = initset(astuple(ZERO, j9))
    fivepatch = combine(combine(p1, p2), combine(p3, combine(p4, p5)))
    fivepatch = intersection(fivepatch, asindices(I))
    fives = recolor(FIVE, fivepatch)
    O = paint(canvas(ZERO, shape(I)), stripes)
    O = paint(O, fives)
    return O
```
training 8e1813be 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    five = ofcolor(I, FIVE)
    H = height(five)
    W = width(five)
    dims = astuple(H, W)
    base = canvas(ZERO, dims)
    allobjs = fgpartition(I)
    nozero = difference(allobjs, colorfilter(allobjs, ZERO))
    objs = difference(nozero, colorfilter(allobjs, FIVE))
    vset = mfilter(objs, vline)
    hset = mfilter(objs, hline)
    vb = size(vset)
    hb = size(hset)
    rowobjs = order(objs, uppermost)
    rowcolors = apply(color, rowobjs)
    is_ = interval(0, H, 1)
    fR = rbind(shoot, RIGHT)
    gR = compose(fR, toivec)
    rowpatches = apply(gR, is_)
    recolR = papply(recolor, rowcolors, rowpatches)
    objR = merge(recolR)
    Or = paint(base, objR)
    colobjs = order(objs, leftmost)
    colcolors = apply(color, colobjs)
    js = interval(0, W, 1)
    fC = rbind(shoot, DOWN)
    gC = compose(fC, tojvec)
    colpatches = apply(gC, js)
    recolC = papply(recolor, colcolors, colpatches)
    objC = merge(recolC)
    Oc = paint(base, objC)
    useCols = greater(vb, hb)
    O = branch(useCols, Oc, Or)
    return O
```
training 8d510a79 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    five = ofcolor(I, FIVE)
    above_all = mapply(rbind(shoot, UP), five)
    below_all = mapply(rbind(shoot, DOWN), five)
    above = difference(above_all, five)
    below = difference(below_all, five)
    ones = ofcolor(I, ONE)
    twos = ofcolor(I, TWO)
    ones_above = intersection(ones, above)
    ones_below = intersection(ones, below)
    twos_above = intersection(twos, above)
    twos_below = intersection(twos, below)
    ones_up = mapply(rbind(shoot, UP), ones_above)
    ones_down = mapply(rbind(shoot, DOWN), ones_below)
    twos_down = mapply(rbind(shoot, DOWN), twos_above)
    twos_up = mapply(rbind(shoot, UP), twos_below)
    ones_up = intersection(ones_up, above)
    ones_down = intersection(ones_down, below)
    twos_down = intersection(twos_down, above)
    twos_up = intersection(twos_up, below)
    ones_lines = combine(ones_up, ones_down)
    twos_lines = combine(twos_down, twos_up)
    obj1 = recolor(ONE, ones_lines)
    obj2 = recolor(TWO, twos_lines)
    O = paint(I, obj1)
    O = paint(O, obj2)
    return O
```
training 342ae2ed 0.0 0.0 0.0 0.0 0.0
```python
def dsl2(I):
    objs = objects(I, T, F, T)
    bgobj = toobject(ofcolor(I, SEVEN), I)
    E = difference(bgobj, bgobj)
    g = lambda a, b: branch(
        equality(color(a), color(b)),
        branch(
            equality(sign(position(a, b)), UNITY),
            recolor(color(a), connect(lrcorner(toindices(a)), ulcorner(toindices(b)))),
            branch(
                equality(sign(position(a, b)), DOWN_LEFT),
                recolor(color(a), connect(llcorner(toindices(a)), urcorner(toindices(b)))),
                branch(
                    equality(sign(position(a, b)), UP_RIGHT),
                    recolor(color(a), connect(urcorner(toindices(a)), llcorner(toindices(b)))),
                    branch(
                        equality(sign(position(a, b)), NEG_UNITY),
                        recolor(color(a), connect(ulcorner(toindices(a)), lrcorner(toindices(b)))),
                        recolor(color(a), connect(center(a), center(b)))
                    )
                )
            )
        ),
        E
    )
    pairs = prapply(g, objs, objs)
    lines = merge(pairs)
    O = underpaint(I, lines)
    return O
```
training baf41dbf 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    t = ofcolor(I, THREE)
    s = ofcolor(I, SIX)
    tl = leftmost(t); tr = rightmost(t); tt = uppermost(t); tb = lowermost(t)
    nl = minimum(insert(add(leftmost(s), ONE), initset(tl)))
    nr = maximum(insert(subtract(rightmost(s), ONE), initset(tr)))
    nu = minimum(insert(add(uppermost(s), ONE), initset(tt)))
    nd = maximum(insert(subtract(lowermost(s), ONE), initset(tb)))
    ul = astuple(nu, nl); lr = astuple(nd, nr)
    frame = box(insert(ul, initset(lr)))
    nbb = backdrop(frame)
    holes = delta(t)
    tinds = toindices(t)
    cols_all = mapply(vfrontier, tinds)
    cols_holes = mapply(vfrontier, holes)
    full_cols = difference(cols_all, cols_holes)
    edge_cols = combine(vfrontier(astuple(ZERO, tl)), vfrontier(astuple(ZERO, tr)))
    vints = intersection(difference(full_cols, edge_cols), nbb)
    rows_all = mapply(hfrontier, tinds)
    rows_holes = mapply(hfrontier, holes)
    full_rows = difference(rows_all, rows_holes)
    edge_rows = combine(hfrontier(astuple(tt, ZERO)), hfrontier(astuple(tb, ZERO)))
    hints = intersection(difference(full_rows, edge_rows), nbb)
    pattern = combine(frame, combine(vints, hints))
    base = replace(I, THREE, ZERO)
    O = paint(base, recolor(THREE, pattern))
    return O
```
training 93b581b8 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    allI = asindices(I)
    zeros = ofcolor(I, ZERO)
    P = difference(allI, zeros)
    r0 = uppermost(P)
    c0 = leftmost(P)
    r1 = lowermost(P)
    c1 = rightmost(P)
    a = index(I, astuple(r0, c0))
    b = index(I, astuple(r0, c1))
    c = index(I, astuple(r1, c0))
    d = index(I, astuple(r1, c1))
    r0m1 = subtract(r0, ONE)
    r0m2 = subtract(r0, TWO)
    c0m1 = subtract(c0, ONE)
    c0m2 = subtract(c0, TWO)
    r1p1 = add(r1, ONE)
    r1p2 = add(r1, TWO)
    c1p1 = add(c1, ONE)
    c1p2 = add(c1, TWO)
    pTLs = astuple(r0m2, c0m2)
    pTLe = astuple(r0m1, c0m1)
    pTRs = astuple(r0m2, c1p2)
    pTRe = astuple(r0m1, c1p1)
    pBLs = astuple(r1p2, c0m2)
    pBLe = astuple(r1p1, c0m1)
    pBRs = astuple(r1p2, c1p2)
    pBRe = astuple(r1p1, c1p1)
    lTL = connect(pTLs, pTLe)
    lTR = connect(pTRs, pTRe)
    lBL = connect(pBLs, pBLe)
    lBR = connect(pBRs, pBRe)
    rTL = intersection(backdrop(lTL), allI)
    rTR = intersection(backdrop(lTR), allI)
    rBL = intersection(backdrop(lBL), allI)
    rBR = intersection(backdrop(lBR), allI)
    oTL = recolor(d, rTL)
    oTR = recolor(c, rTR)
    oBL = recolor(b, rBL)
    oBR = recolor(a, rBR)
    G0 = underpaint(I, oTL)
    G1 = underpaint(G0, oTR)
    G2 = underpaint(G1, oBL)
    O = underpaint(G2, oBR)
    return O
```
training f83cb3f6 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    P = palette(I)
    P1 = remove(ZERO, P)
    P2 = remove(EIGHT, P1)
    C = first(P2)

    E = ofcolor(I, EIGHT)
    O0 = canvas(ZERO, shape(I))
    O0 = paint(O0, toobject(E, I))

    e0 = first(E)
    row_up = hfrontier(add(e0, UP))
    row_dn = hfrontier(add(e0, DOWN))
    col_lt = vfrontier(add(e0, LEFT))
    col_rt = vfrontier(add(e0, RIGHT))
    col8 = mapply(vfrontier, E)

    A = ofcolor(I, C)

    upRays = mapply(rbind(shoot, UP), E)
    dnRays = mapply(rbind(shoot, DOWN), E)
    ltRays = mapply(rbind(shoot, LEFT), E)
    rtRays = mapply(rbind(shoot, RIGHT), E)

    upHits = intersection(upRays, A)
    dnHits = intersection(dnRays, A)
    ltHits = intersection(ltRays, A)
    rtHits = intersection(rtRays, A)

    col_up = mapply(vfrontier, upHits)
    col_dn = mapply(vfrontier, dnHits)
    rows_lt = mapply(hfrontier, ltHits)
    rows_rt = mapply(hfrontier, rtHits)

    tgt_up = intersection(row_up, intersection(col_up, col8))
    tgt_dn = intersection(row_dn, intersection(col_dn, col8))
    tgt_lt = intersection(rows_lt, col_lt)
    tgt_rt = intersection(rows_rt, col_rt)

    Oh = paint(paint(O0, recolor(C, tgt_up)), recolor(C, tgt_dn))
    Ov = paint(paint(O0, recolor(C, tgt_lt)), recolor(C, tgt_rt))

    O = branch(equality(height(E), ONE), Oh, Ov)
    return O
```
training ddf7fa4f 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    w = width(I)
    top = crop(I, ORIGIN, astuple(1, w))
    objs = objects(I, T, F, T)
    fives = colorfilter(objs, FIVE)
    ds = rbind(shoot, DOWN)

    s1 = ofcolor(top, ONE)
    c1 = mapply(ds, s1)
    p1 = compose(positive, chain(size, rbind(intersection, c1), toindices))
    o1 = sfilter(fives, p1)
    i1 = mapply(toindices, o1)
    x1 = fill(I, ONE, i1)

    s2 = ofcolor(top, TWO)
    c2 = mapply(ds, s2)
    p2 = compose(positive, chain(size, rbind(intersection, c2), toindices))
    o2 = sfilter(fives, p2)
    i2 = mapply(toindices, o2)
    x2 = fill(x1, TWO, i2)

    s3 = ofcolor(top, THREE)
    c3 = mapply(ds, s3)
    p3 = compose(positive, chain(size, rbind(intersection, c3), toindices))
    o3 = sfilter(fives, p3)
    i3 = mapply(toindices, o3)
    x3 = fill(x2, THREE, i3)

    s4 = ofcolor(top, FOUR)
    c4 = mapply(ds, s4)
    p4 = compose(positive, chain(size, rbind(intersection, c4), toindices))
    o4 = sfilter(fives, p4)
    i4 = mapply(toindices, o4)
    x4 = fill(x3, FOUR, i4)

    s5 = ofcolor(top, FIVE)
    c5 = mapply(ds, s5)
    p5 = compose(positive, chain(size, rbind(intersection, c5), toindices))
    o5 = sfilter(fives, p5)
    i5 = mapply(toindices, o5)
    x5 = fill(x4, FIVE, i5)

    s6 = ofcolor(top, SIX)
    c6 = mapply(ds, s6)
    p6 = compose(positive, chain(size, rbind(intersection, c6), toindices))
    o6 = sfilter(fives, p6)
    i6 = mapply(toindices, o6)
    x6 = fill(x5, SIX, i6)

    s7 = ofcolor(top, SEVEN)
    c7 = mapply(ds, s7)
    p7 = compose(positive, chain(size, rbind(intersection, c7), toindices))
    o7 = sfilter(fives, p7)
    i7 = mapply(toindices, o7)
    x7 = fill(x6, SEVEN, i7)

    s8 = ofcolor(top, EIGHT)
    c8 = mapply(ds, s8)
    p8 = compose(positive, chain(size, rbind(intersection, c8), toindices))
    o8 = sfilter(fives, p8)
    i8 = mapply(toindices, o8)
    x8 = fill(x7, EIGHT, i8)

    s9 = ofcolor(top, NINE)
    c9 = mapply(ds, s9)
    p9 = compose(positive, chain(size, rbind(intersection, c9), toindices))
    o9 = sfilter(fives, p9)
    i9 = mapply(toindices, o9)
    O = fill(x8, NINE, i9)
    return O
```
training ecdecbb3 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    s8 = ofcolor(I, EIGHT)
    s2 = ofcolor(I, TWO)
    objs8 = colorfilter(objects(I, True, False, True), EIGHT)
    ex8 = first(objs8)
    is_vert = vline(ex8)
    rmin = uppermost(s8); rmax = lowermost(s8)
    cmin = leftmost(s8); cmax = rightmost(s8)
    gate = lambda p: combine(combine(neighbors(p), ineighbors(p)), initset(p))
    def contacts(p):
        rp = uppermost(initset(p)); cp = rightmost(initset(p))
        if is_vert:
            L = astuple(rp, cmin); R = astuple(rp, cmax)
            if equality(cmin, cmax): 
                return initset(L)
            dL = manhattan(initset(p), initset(L)); dR = manhattan(initset(p), initset(R))
            tie = equality(dL, dR)
            between = both(greater(cp, cmin), greater(cmax, cp))
            boths = either(tie, between)
            return branch(boths, combine(initset(L), initset(R)), branch(greater(dL, dR), initset(R), initset(L)))
        else:
            U = astuple(rmin, cp); D = astuple(rmax, cp)
            if equality(rmin, rmax):
                return initset(U)
            dU = manhattan(initset(p), initset(U)); dD = manhattan(initset(p), initset(D))
            tie = equality(dU, dD)
            between = both(greater(rp, rmin), greater(rmax, rp))
            boths = either(tie, between)
            return branch(boths, combine(initset(U), initset(D)), branch(greater(dU, dD), initset(D), initset(U)))
    def wires(p):
        rp = uppermost(initset(p)); cp = rightmost(initset(p))
        if is_vert:
            L = astuple(rp, cmin); R = astuple(rp, cmax)
            if equality(cmin, cmax):
                return connect(p, L)
            dL = manhattan(initset(p), initset(L)); dR = manhattan(initset(p), initset(R))
            tie = equality(dL, dR)
            between = both(greater(cp, cmin), greater(cmax, cp))
            boths = either(tie, between)
            return branch(boths, combine(connect(p, L), connect(p, R)), branch(greater(dL, dR), connect(p, R), connect(p, L)))
        else:
            U = astuple(rmin, cp); D = astuple(rmax, cp)
            if equality(rmin, rmax):
                return connect(p, U)
            dU = manhattan(initset(p), initset(U)); dD = manhattan(initset(p), initset(D))
            tie = equality(dU, dD)
            between = both(greater(rp, rmin), greater(rmax, rp))
            boths = either(tie, between)
            return branch(boths, combine(connect(p, U), connect(p, D)), branch(greater(dU, dD), connect(p, D), connect(p, U)))
    C = merge(apply(contacts, s2))
    W = merge(apply(wires, s2))
    G = merge(apply(gate, C))
    O = fill(fill(fill(I, TWO, W), EIGHT, G), TWO, C)
    return O
```
training fe45cba4 0.0 3.605551275463989 0.05078125 0.0 3.656332525463989
```python
def dsl1(I):
    h = height(I)
    w = width(I)
    half = divide(w, TWO)
    O0 = fill(I, SEVEN, asindices(lefthalf(I)))
    col0 = crop(I, ORIGIN, astuple(h, ONE))
    n9 = colorcount(col0, NINE)
    n2 = colorcount(col0, TWO)
    Rstart = astuple(ZERO, half)
    rw = subtract(w, half)
    top = asindices(crop(I, Rstart, astuple(n9, rw)))
    O1 = fill(O0, NINE, shift(top, Rstart))
    starti = subtract(h, n2)
    bot = asindices(crop(I, astuple(starti, half), astuple(n2, rw)))
    O = fill(O1, TWO, shift(bot, astuple(starti, half)))
    return O
```
training 465b7d93 0.0 8.48528137423857 0.18000000000000005 0.0 8.66528137423857
```python
def dsl1(I):
    # If payload is a filled rectangle (including 1x1), fill the inner hole; else draw an L (left and bottom) inside the frame.
    objs = objects(I, True, False, True)
    frame = argmax(colorfilter(objs, SIX), size)
    inner = delta(frame)
    c = leastcolor(I)
    payload = toobject(ofcolor(I, c), I)
    base = fill(I, SEVEN, toindices(payload))
    is_rect = equality(size(toindices(payload)), size(backdrop(payload)))
    tl = ulcorner(inner)
    bl = llcorner(inner)
    br = lrcorner(inner)
    L = combine(connect(tl, bl), connect(bl, br))
    O_fill = underfill(base, c, inner)
    O_L = fill(base, c, L)
    O = branch(is_rect, O_fill, O_L)
    return O
```
training d2abd087 0.0 10.933056446942715 0.44000000000000006 0.0 11.373056446942714
```python
def dsl1(I):
    T = tophalf(I)
    B = bottomhalf(I)
    TL = lefthalf(T)
    TR = righthalf(T)
    BL = lefthalf(B)
    BR = righthalf(B)
    TL2 = replace(TL, FIVE, TWO)
    TR1 = replace(TR, FIVE, ONE)
    BL1 = replace(BL, FIVE, ONE)
    BR2 = replace(BR, FIVE, TWO)
    TOP = hconcat(TL2, TR1)
    BOT = hconcat(BL1, BR2)
    base = vconcat(TOP, BOT)
    last = righthalf(righthalf(righthalf(righthalf(I))))
    last1 = replace(last, FIVE, ONE)
    O = paint(base, asobject(last1))
    return O
```
training a5313dff 0.0 11.260500271343561 0.4506172839506173 0.0 11.711117555294178
```python
def dsl1(I):
    comps = fgpartition(I)
    comps2 = colorfilter(comps, TWO)
    big = argmax(comps2, size)
    S = subgrid(big, I)
    parts = partition(S)
    zeros = colorfilter(parts, ZERO)
    inner = sfilter(zeros, compose(flip, rbind(bordering, S)))
    off = ulcorner(big)
    shifted = apply(rbind(shift, off), inner)
    ones = apply(lbind(recolor, ONE), shifted)
    fillobj = merge(ones)
    O = underpaint(I, fillobj)
    return O
```
training 351d6448 0.0 11.1104335791443 0.46153846153846145 0.17091113629777166 11.742883176980532
```python
def dsl3(I):
    # Overlay-union of all block-objects normalized to j=0, then center the union on the middle row.
    x1 = replace(I, FIVE, ZERO)
    objs = objects(x1, F, F, T)
    # Build a small canvas as wide as the maximum width
    omax = argmax(objs, width)
    wM = width(omax)
    small = canvas(ZERO, astuple(3, wM))
    # Paint all objects normalized at j=0 on the middle row
    t = totuple(objs)
    def place(o):
        return shift(normalize(o), astuple(1, 0))
    ps = apply(place, t)
    small2 = merge(apply(lbind(paint, small), ps))
    small2 = branch(equality(small2, ZERO), small, small2)
    W = width(I)
    joff = divide(subtract(W, wM), TWO)
    O = paint(canvas(ZERO, astuple(3, W)), shift(asobject(small2), astuple(0, joff)))
    return O
```
training 6e82a1ae 0.0 12.008755220257862 0.3900000000000001 0.0 12.398755220257861
```python
def dsl4(I):
    x1 = objects(I, T, F, T)
    x2 = colorfilter(x1, FIVE)
    x3 = sfilter(x2, rbind(bordering, I))
    x4 = difference(x2, x3)
    y1 = mapply(lbind(recolor, ONE), x3)
    y2 = mapply(lbind(recolor, TWO), x4)
    y = merge((y1, y2))
    O = paint(I, y)
    return O
```
training 60a26a3e 0.0 12.39635450163017 0.236084656084656 0.0 12.632439157714828
```python
def dsl4(I):
    S = ofcolor(I, TWO)
    # conservative: horizontal n=3..4, vertical n=2..3
    R1 = shift(S, RIGHT)
    R2 = shift(S, multiply(RIGHT, TWO))
    R3 = shift(S, multiply(RIGHT, THREE))
    L1 = shift(S, LEFT)
    L2 = shift(S, multiply(LEFT, TWO))
    L3 = shift(S, multiply(LEFT, THREE))
    H3 = combine(intersection(R1, L2), intersection(R2, L1))
    H4 = combine(combine(intersection(R1, L3), intersection(R2, L2)), intersection(R3, L1))
    H = combine(H3, H4)
    U1 = shift(S, UP)
    U2 = shift(S, multiply(UP, TWO))
    D1 = shift(S, DOWN)
    D2 = shift(S, multiply(DOWN, TWO))
    V2 = intersection(U1, D1)
    V3 = combine(intersection(U1, D2), intersection(U2, D1))
    V = combine(V2, V3)
    M = combine(H, V)
    O = underpaint(I, recolor(ONE, toobject(M, I)))
    return O
```
training b7999b51 0.0 11.916375287812984 0.8 0.0 12.716375287812985
```python
def dsl1(I):
    cols = remove(ZERO, palette(I))
    comp = compose(invert, lbind(colorcount, I))
    ordered = order(cols, comp)
    hfun = compose(height, lbind(ofcolor, I))
    nrows = valmax(ordered, hfun)
    ncols = size(ordered)
    base = canvas(ZERO, astuple(nrows, ncols))
    idxs = interval(ZERO, ncols, ONE)
    pairs = pair(idxs, ordered)
    get_j = first
    get_c = last
    startpt = compose(lbind(astuple, ZERO), get_j)
    endrow = compose(decrement, compose(hfun, get_c))
    endpt = fork(astuple, endrow, get_j)
    line = fork(connect, startpt, endpt)
    objfun = fork(recolor, get_c, line)
    objs = apply(objfun, pairs)
    merged = merge(objs)
    O = paint(base, merged)
    return O
```
training c8cbb738 0.0 12.649110640673518 0.16326530612244894 0.0 12.812375946795967
```python
def dsl1(I):
    bg = mostcolor(I)
    objs = fgpartition(I)
    hmax = valmax(objs, height)
    wmax = valmax(objs, width)
    n = maximum(combine(initset(hmax), initset(wmax)))
    O = canvas(bg, astuple(n, n))
    m = divide(n, TWO)
    l = subtract(n, ONE)
    l1 = subtract(l, ONE)
    cpatch = insert(astuple(ZERO, ZERO), insert(astuple(ZERO, l), insert(astuple(l, ZERO), initset(astuple(l, l)))))
    ppatch = insert(astuple(ZERO, m), insert(astuple(m, ZERO), insert(astuple(m, l), initset(astuple(l, m)))))
    intersz = compose(size, fork(intersection, toindices, corners))
    eqh = matcher(height, n)
    eqw = matcher(width, n)
    isfull = matcher(intersz, FOUR)
    iszero = matcher(intersz, ZERO)
    condc = fork(both, fork(both, eqh, eqw), isfull)
    oc = extract(objs, condc)
    colc = color(oc)
    condp = fork(both, fork(both, eqh, eqw), iszero)
    op = extract(objs, condp)
    colp = color(op)
    O1 = paint(O, recolor(colc, cpatch))
    O2 = paint(O1, recolor(colp, ppatch))
    top = crop(I, astuple(ZERO, ZERO), astuple(ONE, width(I)))
    left = crop(I, astuple(ZERO, ZERO), astuple(height(I), ONE))
    top_has_fg = positive(size(difference(palette(top), initset(bg))))
    left_has_fg = positive(size(difference(palette(left), initset(bg))))
    topbotcol = leastcolor(top)
    lrcol = leastcolor(left)
    tpatch = insert(astuple(ZERO, ONE), insert(astuple(ZERO, l1), insert(astuple(l, ONE), initset(astuple(l, l1)))))
    lpatch = insert(astuple(ONE, ZERO), insert(astuple(l1, ZERO), insert(astuple(ONE, l), initset(astuple(l1, l)))))
    O3 = branch(both(greater(n, THREE), top_has_fg), paint(O2, recolor(topbotcol, tpatch)), O2)
    O4 = branch(both(greater(n, THREE), left_has_fg), paint(O3, recolor(lrcol, lpatch)), O3)
    return O4
```
training 90f3ed37 0.0 13.33708496134517 0.41999999999999993 0.027735009803569147 13.78481997114874
```python
def dsl3(I):
    x1 = objects(I, T, F, T)
    x2 = sfilter(x1, hline)
    x3 = sizefilter(x2, ONE)
    x4 = difference(x2, x3)
    x5 = apply(urcorner, x4)
    x6 = apply(rbind(add, RIGHT), x5)
    x7 = mapply(rbind(shoot, RIGHT), x6)
    O = underfill(I, ONE, x7)
    return O
```
training 6e19193c 0.0 16.0 0.040000000000000036 0.07905694147625864 16.11905694147626
```python
def dsl1(I):
    K = other(palette(I), ZERO)
    S = ofcolor(I, K)
    OB = colorfilter(objects(I, T, F, T), K)
    Ls = sizefilter(OB, THREE)
    A = argmin(Ls, ulcorner)
    B = other(Ls, A)
    AI = toindices(A)
    BI = toindices(B)
    UA = urcorner(A)
    LA = llcorner(A)
    eA = branch(contained(UA, AI), UA, LA)
    dA = branch(equality(eA, UA), DOWN_LEFT, UP_RIGHT)
    PA = shoot(eA, dA)
    UB = urcorner(B)
    LB = llcorner(B)
    eB = branch(contained(UB, BI), UB, LB)
    dB = branch(equality(eB, UB), DOWN_LEFT, UP_RIGHT)
    PB = shoot(eB, dB)
    P = combine(PA, PB)
    N = mapply(neighbors, S)
    Q = difference(P, combine(S, N))
    R = recolor(K, Q)
    O = underpaint(I, R)
    return O
```
training d93c6891 0.0 17.788656935474513 0.10633680555555558 0.0 17.89499374103007
```python
def dsl5(I):
    x1 = replace(I, FIVE, FOUR)
    O = replace(x1, SEVEN, FIVE)
    return O
```
training 7d1f7ee8 0.0 18.211243569115616 0.06467797847108192 0.0 18.275921547586698
```python
def dsl1(I):
    objs = objects(I, T, F, T)
    z = ofcolor(I, ZERO)
    g = compose(rbind(difference, z), delta)
    f = fork(recolor, color, g)
    mo = mapply(f, objs)
    O = paint(I, mo)
    return O
```
training 73c3b0d8 0.0 21.65685424949238 0.16547619047619044 0.12862393880173456 21.950954378770305
```python
def dsl1(I):
    w = width(I)
    h = height(I)
    twos = ofcolor(I, TWO)
    two_obj = toobject(twos, I)
    R = lowermost(two_obj)
    top = crop(I, ORIGIN, astuple(R, w))
    bot = crop(I, astuple(R, ZERO), astuple(subtract(h, R), w))
    four_top = ofcolor(top, FOUR)
    top0 = replace(top, FOUR, ZERO)
    shifted_top = shift(four_top, DOWN)
    top1 = paint(top0, recolor(FOUR, shifted_top))
    four_bot = ofcolor(bot, FOUR)
    bot0 = replace(bot, FOUR, ZERO)
    shifted_bot = shift(four_bot, DOWN)
    bot1 = paint(bot0, recolor(FOUR, shifted_bot))
    apex_row = decrement(R)
    brow = hfrontier(astuple(apex_row, ZERO))
    apex = intersection(shifted_top, brow)
    upfun = rbind(shoot, UP_RIGHT)
    dnfun = rbind(shoot, DOWN_LEFT)
    upr = mapply(upfun, apex)
    dnl = mapply(dnfun, apex)
    diag = combine(upr, dnl)
    diag = intersection(diag, asindices(top))
    top2 = paint(top1, recolor(FOUR, diag))
    O = vconcat(top2, bot1)
    return O
```
training fc4aaf52 0.0 22.494443758403985 0.0625 0.0 22.556943758403985
```python
def dsl1(I):
    fg = difference(asindices(I), ofcolor(I, EIGHT))
    S = subgrid(fg, I)
    h = height(S)
    w = width(S)
    th = divide(h, 2)
    top = crop(S, ORIGIN, astuple(th, w))
    bot = crop(S, astuple(th, 0), astuple(subtract(h, th), w))
    cols = remove(EIGHT, palette(S))
    a = minimum(cols)
    b = maximum(cols)
    top2 = switch(top, a, b)
    bot2 = switch(bot, a, b)
    top_idx = difference(asindices(top2), ofcolor(top2, EIGHT))
    bot_idx = difference(asindices(bot2), ofcolor(bot2, EIGHT))
    top_obj = toobject(top_idx, top2)
    bot_obj = toobject(bot_idx, bot2)
    O = canvas(EIGHT, shape(I))
    ul = ulcorner(fg)
    O1 = paint(O, shift(top_obj, add(ul, tojvec(w))))
    O2 = paint(O1, shift(bot_obj, add(ul, toivec(th))))
    return O2
```
training 11dc524f 0.0 22.475029524988635 0.09467455621301779 0.0 22.569704081201653
```python
def dsl1(I):
    # Mirror the TWO-shape across the shared border with FIVE after making them adjacent.
    objs = objects(I, T, F, T)
    tobj = first(colorfilter(objs, TWO))
    fobj = first(colorfilter(objs, FIVE))
    p2 = toindices(tobj)
    pf = toindices(fobj)
    off = gravitate(p2, pf)
    p2m = shift(p2, off)
    w2 = width(p2)
    h2 = height(p2)
    righttouch = equality(subtract(leftmost(pf), rightmost(p2m)), ONE)
    lefttouch  = equality(subtract(leftmost(p2m), rightmost(pf)), ONE)
    downtouch  = equality(subtract(uppermost(pf), lowermost(p2m)), ONE)
    sR = astuple(ZERO, w2)
    sL = astuple(ZERO, invert(w2))
    sD = astuple(h2, ZERO)
    sU = astuple(invert(h2), ZERO)
    pv = vmirror(p2m)
    ph = hmirror(p2m)
    p5 = branch(righttouch, shift(pv, sR),
         branch(lefttouch,  shift(pv, sL),
         branch(downtouch,  shift(ph, sD), shift(ph, sU))))
    base = canvas(SEVEN, shape(I))
    O = paint(paint(base, recolor(TWO, p2m)), recolor(FIVE, p5))
    return O
```
training 516b51b7 0.0 25.705293981883216 0.4446475093533918 0.0 26.14994149123661
```python
def dsl1(I):
    objs = colorfilter(objects(I, T, F, T), ONE)
    inner1 = mapply(inbox, objs)
    O = fill(I, TWO, inner1)
    inner2 = mapply(inbox, apply(inbox, objs))
    O = fill(O, THREE, inner2)
    return O
```
training f0100645 0.0 28.69560344015403 0.33753086419753087 0.0 29.033134304351563
```python
def dsl1(I):
    w = width(I)
    leftc = index(I, astuple(ZERO, ZERO))
    rightc = index(I, astuple(ZERO, subtract(w, ONE)))
    leftcol = shoot(astuple(ZERO, ZERO), DOWN)
    rightcol = shoot(astuple(ZERO, subtract(w, ONE)), DOWN)
    # move left-internal toward left border
    allL = ofcolor(I, leftc)
    internalL = difference(allL, leftcol)
    objL = toobject(internalL, I)
    dirL = gravitate(objL, toobject(leftcol, I))
    g1 = move(I, objL, dirL)
    # then move right-internal toward right border
    allR = ofcolor(g1, rightc)
    internalR = difference(allR, rightcol)
    objR = toobject(internalR, g1)
    dirR = gravitate(objR, toobject(rightcol, g1))
    g2 = move(g1, objR, dirR)
    # final pass: left again
    allL2 = ofcolor(g2, leftc)
    internalL2 = difference(allL2, leftcol)
    objL2 = toobject(internalL2, g2)
    dirL2 = gravitate(objL2, toobject(leftcol, g2))
    O = move(g2, objL2, dirL2)
    return O
```
training 46c35fc7 0.0 30.814071796775533 0.6326530612244897 0.0 31.446724858000024
```python
def dsl1(I):
    O = I
    for obj in totuple(objects(I, F, T, T)):
        sub = subgrid(obj, I)
        idxs = asindices(sub)
        ring = box(idxs)
        crn = corners(idxs)
        edg = difference(ring, crn)
        cw = rot90(sub)
        ccw = rot270(sub)
        oc = toobject(crn, ccw)  # corners from CCW
        oe = toobject(edg, cw)   # edges from CW
        base = canvas(SEVEN, shape(sub))
        base = paint(base, oc)
        base = paint(base, oe)
        O = cover(O, obj)
        O = move(O, asobject(base), ulcorner(obj))
    return O
```
training 94414823 0.0 32.0 0.16000000000000003 0.0 32.16
```python
def dsl1(I):
    allobjs = fgpartition(I)
    obj5set = colorfilter(allobjs, FIVE)
    ring5 = first(obj5set)
    markers = difference(allobjs, obj5set)
    interior = delta(ring5)
    u0 = ulcorner(interior)
    sub = subgrid(interior, I)
    tlg = crop(sub, ORIGIN, TWO_BY_TWO)
    trg = crop(sub, astuple(ZERO, TWO), TWO_BY_TWO)
    blg = crop(sub, astuple(TWO, ZERO), TWO_BY_TWO)
    brg = crop(sub, TWO_BY_TWO, TWO_BY_TWO)
    tllocal = asindices(tlg)
    trlocal = asindices(trg)
    bllocal = asindices(blg)
    brlocal = asindices(brg)
    TL = shift(tllocal, u0)
    TR = shift(trlocal, add(u0, astuple(ZERO, TWO)))
    BL = shift(bllocal, add(u0, astuple(TWO, ZERO)))
    BR = shift(brlocal, add(u0, TWO_BY_TWO))
    aobj = argmin(markers, uppermost)
    bobj = other(markers, aobj)
    lobj = argmin(markers, leftmost)
    robj = other(markers, lobj)
    samecol = equality(leftmost(aobj), leftmost(bobj))
    r5 = rightmost(ring5)
    rside = greater(leftmost(aobj), r5)
    lt_v = branch(rside, color(bobj), color(aobj))
    rt_v = branch(rside, color(aobj), color(bobj))
    lt_h = color(lobj)
    rt_h = color(robj)
    lt = branch(samecol, lt_v, lt_h)
    rt = branch(samecol, rt_v, rt_h)
    lb = rt
    rb = lt
    O1 = fill(I, lt, TL)
    O2 = fill(O1, rt, TR)
    O3 = fill(O2, lb, BL)
    O = fill(O3, rb, BR)
    return O
```
training f9012d9b 1.4142135623730951 19.0 13.0 0.1999999997171573 33.61421356209025
```python
def dsl1(I):
    h = height(I)
    w = width(I)
    rmid = divide(h, TWO)
    cmid = divide(w, TWO)
    th = rmid
    bh = subtract(h, rmid)
    lw = cmid
    rw = subtract(w, cmid)
    TL = crop(I, astuple(ZERO, ZERO), astuple(th, lw))
    TR = crop(I, astuple(ZERO, cmid), astuple(th, rw))
    BL = crop(I, astuple(rmid, ZERO), astuple(bh, lw))
    BR = crop(I, astuple(rmid, cmid), astuple(bh, rw))
    f100 = multiply(TEN, TEN)
    f1000 = multiply(TEN, f100)
    pall = remove(ZERO, palette(I))
    scoreAll = fork(add, compose(rbind(multiply, f1000), lbind(colorcount, I)), identity)
    fallback = branch(greater(size(pall), ZERO), argmax(pall, scoreAll), ZERO)
    pTL = remove(ZERO, palette(TL))
    pTR = remove(ZERO, palette(TR))
    pBL = remove(ZERO, palette(BL))
    pBR = remove(ZERO, palette(BR))
    sTL = fork(add, compose(rbind(multiply, f1000), lbind(colorcount, TL)), identity)
    sTR = fork(add, compose(rbind(multiply, f1000), lbind(colorcount, TR)), identity)
    sBL = fork(add, compose(rbind(multiply, f1000), lbind(colorcount, BL)), identity)
    sBR = fork(add, compose(rbind(multiply, f1000), lbind(colorcount, BR)), identity)
    cTL = branch(greater(size(pTL), ZERO), argmax(pTL, sTL), fallback)
    cTR = branch(greater(size(pTR), ZERO), argmax(pTR, sTR), fallback)
    cBL = branch(greater(size(pBL), ZERO), argmax(pBL, sBL), fallback)
    cBR = branch(greater(size(pBR), ZERO), argmax(pBR, sBR), fallback)
    top = hconcat(canvas(cTL, UNITY), canvas(cTR, UNITY))
    bot = hconcat(canvas(cBL, UNITY), canvas(cBR, UNITY))
    tile = vconcat(top, bot)
    n0 = colorcount(I, ZERO)
    O = branch(equality(n0, ONE), canvas(mostcolor(tile), UNITY), tile)
    return O
```
training 2546ccf6 0.0 37.62842406718791 0.30667527235032965 0.0 37.93509933953824
```python
def dsl1(I):
    c = mostcolor(I)
    J = replace(I, c, ZERO)
    y = underpaint(J, asobject(vmirror(J)))
    O = underpaint(I, asobject(y))
    return O
```
training c4d1a9ae 0.0 40.24922359499622 0.5 0.0 40.74922359499622
```python
def dsl1(I):
    bg = mostcolor(I)
    P0 = palette(I)
    P1 = remove(bg, P0)
    f1 = lbind(ofcolor, I)
    f2 = compose(leftmost, f1)
    Ps = order(P1, f2)
    a = first(Ps)
    c = last(Ps)
    Ps2 = remove(c, Ps)
    b = last(Ps2)
    lb = leftmost(ofcolor(I, b))
    lc = leftmost(ofcolor(I, c))
    h = height(I)
    w = width(I)
    d1 = astuple(h, lb)
    d2 = astuple(h, subtract(lc, lb))
    d3 = astuple(h, subtract(w, lc))
    b1 = canvas(b, d1)
    b2 = canvas(c, d2)
    b3 = canvas(a, d3)
    tt = hconcat(hconcat(b1, b2), b3)
    idxAll = asindices(I)
    bgIdx = ofcolor(I, bg)
    NB = difference(idxAll, bgIdx)
    colsMask = mapply(vfrontier, NB)
    obj = toobject(colsMask, tt)
    I0 = replace(I, bg, ZERO)
    O = underpaint(I0, obj)
    return O
```
training 825aa9e9 0.0 40.30361529710298 0.6753968253968254 0.0 40.97901212249981
```python
def dsl1(I):
    bg = mostcolor(I)
    pal = palette(I)
    p2 = remove(bg, pal)
    comp = lbind(colorcount, I)
    c = valmin(p2, comp)
    cells = ofcolor(I, c)
    G = fill(I, bg, cells)
    obj = toobject(cells, I)
    sh = shift(obj, double(DOWN))
    O = underpaint(G, sh)
    return O
```
training 30f42897 0.0 44.055044581883124 0.6666666666666667 0.0 44.721711248549795
```python
def dsl3(I):
    c = leastcolor(I)
    src = ofcolor(I, c)
    n = size(src)
    h = height(I)
    w = width(I)
    start = divide(subtract(w, n), TWO)
    end = add(start, subtract(n, ONE))
    bottom = connect(astuple(subtract(h, ONE), start), astuple(subtract(h, ONE), end))
    wr = width(src)
    hr = height(src)
    top = connect(astuple(ZERO, subtract(w, wr)), astuple(ZERO, subtract(w, ONE)))
    right = connect(astuple(ZERO, subtract(w, ONE)), astuple(subtract(hr, ONE), subtract(w, ONE)))
    lines = combine(bottom, combine(top, right))
    O = underpaint(I, recolor(c, lines))
    return O
```
training 72322fa7 0.0 47.543620591175014 0.1414098367006954 0.032230128188518094 47.717260556064225
```python
def dsl1(I):
    O0 = I
    x8 = ofcolor(I, EIGHT)
    x4 = ofcolor(I, FOUR)
    x6 = ofcolor(I, SIX)
    x2 = ofcolor(I, TWO)
    x3 = ofcolor(I, THREE)
    x1 = ofcolor(I, ONE)

    # Pair: 4-8-4 (apply only if 4 present)
    cond4 = greater(size(x4), ZERO)
    a4l = recolor(FOUR, shift(x8, LEFT))
    a4r = recolor(FOUR, shift(x8, RIGHT))
    tmp = underpaint(O0, a4l)
    tmp = underpaint(tmp, a4r)
    mid4 = intersection(shift(x4, RIGHT), shift(x4, LEFT))
    tmp = underpaint(tmp, recolor(EIGHT, mid4))
    O1 = branch(cond4, tmp, O0)

    # Pair: 8-6-8 or 8-2-8 (choose by presence)
    cond6 = greater(size(x6), ZERO)
    cond2 = greater(size(x2), ZERO)
    a86l = recolor(EIGHT, shift(x6, LEFT))
    a86r = recolor(EIGHT, shift(x6, RIGHT))
    t6 = underpaint(O1, a86l)
    t6 = underpaint(t6, a86r)
    a82l = recolor(EIGHT, shift(x2, LEFT))
    a82r = recolor(EIGHT, shift(x2, RIGHT))
    t2 = underpaint(O1, a82l)
    t2 = underpaint(t2, a82r)
    O2 = branch(cond6, t6, branch(cond2, t2, O1))

    mid8 = intersection(shift(ofcolor(I, EIGHT), RIGHT), shift(ofcolor(I, EIGHT), LEFT))
    tmid6 = underpaint(O2, recolor(SIX, mid8))
    tmid2 = underpaint(O2, recolor(TWO, mid8))
    O3 = branch(cond6, tmid6, branch(cond2, tmid2, O2))

    # Pair: 1 and 3 (orientation from adjacency; else diagonals)
    up3 = shift(x3, UP)
    dn3 = shift(x3, DOWN)
    lf3 = shift(x3, LEFT)
    rt3 = shift(x3, RIGHT)
    v1 = greater(size(intersection(up3, x1)), ZERO)
    v2 = greater(size(intersection(dn3, x1)), ZERO)
    h1 = greater(size(intersection(lf3, x1)), ZERO)
    h2 = greater(size(intersection(rt3, x1)), ZERO)
    cvert = either(v1, v2)
    chorz = either(h1, h2)

    candV = underpaint(O3, recolor(ONE, up3))
    candV = underpaint(candV, recolor(ONE, dn3))
    candH = underpaint(O3, recolor(ONE, lf3))
    candH = underpaint(candH, recolor(ONE, rt3))
    ul3 = shift(x3, NEG_UNITY)
    ur3 = shift(x3, UP_RIGHT)
    dl3 = shift(x3, DOWN_LEFT)
    dr3 = shift(x3, UNITY)
    candD = underpaint(O3, recolor(ONE, ul3))
    candD = underpaint(candD, recolor(ONE, ur3))
    candD = underpaint(candD, recolor(ONE, dl3))
    candD = underpaint(candD, recolor(ONE, dr3))

    tmp2 = branch(cvert, candV, O3)
    tmp2 = branch(chorz, candH, tmp2)
    needD = both(greater(size(x3), ZERO), both(flip(cvert), flip(chorz)))
    O = branch(needD, candD, tmp2)
    return O
```
training ad38a9d0 0.0 48.30584272273025 0.962962962962963 0.0 49.26880568569321
```python
def dsl1(I):
    parts = fgpartition(I)
    sixparts = colorfilter(parts, SIX)
    base = replace(I, SIX, SEVEN)
    s2 = sizefilter(sixparts, TWO)
    h2 = mfilter(s2, hline)
    v2 = mfilter(s2, vline)
    s3 = sizefilter(sixparts, THREE)
    v3 = mfilter(s3, vline)
    h3 = mfilter(s3, hline)
    lh3 = combine(v3, h3)
    l3 = difference(s3, lh3)
    s4 = sizefilter(sixparts, FOUR)
    s5 = sizefilter(sixparts, FIVE)
    s6 = sizefilter(sixparts, SIX)
    o9 = mapply(lbind(recolor, NINE), v2)
    o8h = mapply(lbind(recolor, EIGHT), h2)
    o2v = mapply(lbind(recolor, TWO), v3)
    o2h = mapply(lbind(recolor, TWO), h3)
    o4 = mapply(lbind(recolor, FOUR), l3)
    o8s4 = mapply(lbind(recolor, EIGHT), s4)
    o3 = mapply(lbind(recolor, THREE), s5)
    o5 = mapply(lbind(recolor, FIVE), s6)
    r0 = combine(o9, o8h)
    r1 = combine(r0, o2v)
    r2 = combine(r1, o2h)
    r3 = combine(r2, o4)
    r4 = combine(r3, o8s4)
    r5 = combine(r4, o3)
    allc = combine(r5, o5)
    O = paint(base, allc)
    return O
```
training 7837ac64 0.0 44.49990517191746 2.8888888888888893 2.0 49.388794060806354
```python
def dsl2(I):
    x1 = replace(I, mostcolor(I), ZERO)
    x2 = trim(x1)
    x3 = downscale(x2, THREE)
    x4 = downscale(x3, THREE)
    O = rot90(x4)
    return O
```
training 14754a24 0.0 49.5004782034063 0.20207536384821712 0.0 49.70255356725452
```python
def dsl5(I):
    # End-capped second step: only second 5 in a direction if followed by a 0 (pattern 4-5-5-0 and symmetries)
    fives = ofcolor(I, FIVE)
    zeros = ofcolor(I, ZERO)
    fours = ofcolor(I, FOUR)
    r1 = intersection(shift(fours, RIGHT), fives)
    l1 = intersection(shift(fours, LEFT), fives)
    u1 = intersection(shift(fours, UP), fives)
    d1 = intersection(shift(fours, DOWN), fives)
    r2 = intersection(shift(r1, RIGHT), fives)
    l2 = intersection(shift(l1, LEFT), fives)
    u2 = intersection(shift(u1, UP), fives)
    d2 = intersection(shift(d1, DOWN), fives)
    # require a 0 just beyond the second step
    r2c = intersection(r2, shift(zeros, LEFT))
    l2c = intersection(l2, shift(zeros, RIGHT))
    u2c = intersection(u2, shift(zeros, DOWN))
    d2c = intersection(d2, shift(zeros, UP))
    targets = combine(combine(r2c, l2c), combine(u2c, d2c))
    O = paint(I, recolor(TWO, toobject(targets, I)))
    return O
```
training cb227835 0.0 50.1443299263566 0.4166858782243399 0.0 50.56101580458094
```python
def dsl1(I):
    objs = colorfilter(objects(I, T, F, T), EIGHT)
    t = totuple(objs)
    a = first(t)
    b = last(t)
    p = ulcorner(a)
    q = ulcorner(b)
    line = connect(p, q)
    O = underfill(I, THREE, line)
    return O
```
training d06dbe63 0.0 51.05551275463989 0.20710059171597628 0.09285436775832752 51.35546771411419
```python
def dsl1(I):
    s = first(totuple(ofcolor(I, EIGHT)))
    u2 = shoot(s, double(UP_RIGHT))
    d2 = shoot(s, double(DOWN_LEFT))
    u2e = difference(u2, initset(s))
    d2e = difference(d2, initset(s))
    tri_up = combine(u2e, combine(shift(u2e, LEFT), shift(u2e, double(LEFT))))
    tri_dn = combine(d2e, combine(shift(d2e, RIGHT), shift(d2e, double(RIGHT))))
    uo = shoot(add(s, UP_RIGHT), double(UP_RIGHT))
    do = shoot(add(s, DOWN_LEFT), double(DOWN_LEFT))
    singles = combine(shift(uo, LEFT), shift(do, RIGHT))
    buo = shift(initset(urcorner(uo)), double(UP_RIGHT))
    bdo = shift(initset(llcorner(do)), double(DOWN_LEFT))
    bue = shift(initset(urcorner(u2)), double(UP_RIGHT))
    bde = shift(initset(llcorner(d2)), double(DOWN_LEFT))
    extra_singles = combine(shift(buo, LEFT), shift(bdo, RIGHT))
    extra_tris = combine(combine(shift(bue, LEFT), shift(bue, double(LEFT))), combine(shift(bde, RIGHT), shift(bde, double(RIGHT))))
    p = combine(combine(tri_up, tri_dn), combine(singles, combine(extra_singles, extra_tris)))
    O = underpaint(I, recolor(FIVE, p))
    return O
```
training 712bf12e 0.0 50.74192633588899 0.9229360383206537 0.0 51.66486237420965
```python
def dsl1(I):
    x1 = ofcolor(I, FIVE)
    x2 = shift(x1, RIGHT)
    x3 = recolor(TWO, x2)
    O = underpaint(I, x3)
    return O
```
training ac0c5833 0.0 54.20301858130129 0.2608862590401053 0.13888242296550535 54.60278726330691
```python
def dsl1(I):
    x4 = ofcolor(I, FOUR)
    s1 = shift(x4, astuple(0, -2))
    s2 = shift(x4, astuple(0, -3))
    p = combine(s1, s2)
    O = underfill(I, TWO, p)
    return O
```
training b548a754 0.0 54.16164595166167 0.5040670285425529 0.40653907474987405 55.07225205495409
```python
def dsl4(I):
    base = replace(I, EIGHT, ZERO)
    pal = palette(base)
    pal1 = remove(ZERO, pal)
    bcol = argmax(pal1, lbind(colorcount, base))
    pal2 = remove(bcol, pal1)
    icol = argmax(pal2, lbind(colorcount, base))
    objs = objects(base, T, F, T)
    bset = colorfilter(objs, bcol)
    bobj = argmax(bset, size)
    band = backdrop(toindices(bobj))
    epatch = ofcolor(I, EIGHT)
    eloc = first(epatch)
    dir = gravitate(toindices(bobj), epatch)
    ish = either(equality(dir, RIGHT), equality(dir, LEFT))
    vcol = intersection(vfrontier(eloc), band)
    hrow = intersection(hfrontier(eloc), band)
    ext = branch(ish, vcol, hrow)
    seed = combine(band, shift(ext, dir))
    rect = backdrop(seed)
    bord = box(rect)
    inter = difference(rect, bord)
    x1 = fill(base, bcol, bord)
    O = fill(x1, icol, inter)
    return O
```
training 7447852a 0.0 54.676473614708115 0.94 0.0 55.61647361470812
```python
def dsl4(I):
    fr = frontiers(I)
    idx = mapply(toindices, fr)
    O = underfill(I, FOUR, idx)
    return O
```
training f8c80d96 0.0 54.89579519647377 0.96 0.0 55.85579519647377
```python
def dsl1(I):
    O = replace(I, ZERO, FIVE)
    return O
```
training 7c8af763 0.0 54.318215566183 1.74 0.0 56.058215566182994
```python
def dsl3(I):
    G = I
    steps = height(I) + width(I)
    for _ in range(steps):
        p2 = ofcolor(G, TWO)
        for d in (UP, DOWN, LEFT, RIGHT):
            G = underpaint(G, recolor(TWO, shift(p2, d)))
        p1 = ofcolor(G, ONE)
        for d in (UP, DOWN, LEFT, RIGHT):
            G = underpaint(G, recolor(ONE, shift(p1, d)))
    return G
```
training 6ffe8f07 0.0 57.3169756437209 0.15635580178516462 0.0 57.47333144550606
```python
def dsl1(I):
    idx8 = ofcolor(I, EIGHT)
    H = merge(apply(hfrontier, idx8))
    V = merge(apply(vfrontier, idx8))
    P = combine(H, V)
    forbid = combine(ofcolor(I, ONE), idx8)
    P2 = difference(P, forbid)
    obj = recolor(FOUR, toobject(P2, I))
    O = paint(I, obj)
    return O
```
training 4acc7107 0.0 57.444370971571516 0.48 0.07071067809365475 57.995081649665174
```python
def dsl2(I):
    # Same as dsl1 but reverse stack order within each color (top component at bottom, bottom component above)
    hI = height(I); wI = width(I); mid = divide(wI, TWO)
    cols = remove(ZERO, palette(I)); c1 = first(cols); c2 = other(cols, c1)
    p1 = ofcolor(I, c1); p2 = ofcolor(I, c2)
    l1 = leftmost(p1); l2 = leftmost(p2)
    cL = branch(greater(l1, l2), c2, c1); cR = branch(greater(l1, l2), c1, c2)
    allobjs = objects(I, T, F, T)
    oLset = colorfilter(allobjs, cL); oRset = colorfilter(allobjs, cR)
    topL = argmin(oLset, uppermost); botL = argmax(oLset, lowermost)
    topR = argmin(oRset, uppermost); botR = argmax(oRset, lowermost)
    hTopL = height(subgrid(topL, I)); hBotL = height(subgrid(botL, I))
    hTopR = height(subgrid(topR, I)); hBotR = height(subgrid(botR, I))
    off_bot_L = subtract(hI, hTopL)
    off_top_L = subtract(off_bot_L, add(hBotL, ONE))
    off_bot_R = subtract(hI, hTopR)
    off_top_R = subtract(off_bot_R, add(hBotR, ONE))
    base = canvas(ZERO, shape(I))
    tmp = paint(base, shift(normalize(botL), astuple(off_top_L, ZERO)))
    tmp = paint(tmp, shift(normalize(topL), astuple(off_bot_L, ZERO)))
    tmp = paint(tmp, shift(normalize(botR), astuple(off_top_R, mid)))
    O = paint(tmp, shift(normalize(topR), astuple(off_bot_R, mid)))
    return O
```
training f28a3cbb 0.0 57.00106909354186 1.6419753086419755 0.0 58.64304440218384
```python
def dsl2(I):
    O = hmirror(I)
    return O
```
training 13f06aa5 0.0 59.02074513441157 0.2904234654234653 0.0 59.31116859983504
```python
def dsl5(I):
    # Only fixed mapping to borders (no rays, no corner zeroing)
    inds = asindices(I)
    tlc = ulcorner(inds); trc = urcorner(inds); blc = llcorner(inds)
    top = hfrontier(tlc); bot = hfrontier(blc); lef = vfrontier(tlc); rig = vfrontier(trc)

    has1 = equality(colorcount(I, ONE), ONE)
    has3 = equality(colorcount(I, THREE), ONE)
    has2 = equality(colorcount(I, TWO), ONE)
    has8 = equality(colorcount(I, EIGHT), ONE)
    has6 = equality(colorcount(I, SIX), ONE)

    O = I
    # Prefer THREE over ONE for top
    O = branch(has1, fill(O, ONE, top), O)
    O = branch(has3, fill(O, THREE, top), O)
    O = branch(has2, fill(O, TWO, lef), O)
    O = branch(has8, fill(O, EIGHT, rig), O)
    O = branch(has6, fill(O, SIX, bot), O)
    return O
```
training 7468f01a 0.0 59.650549042666434 1.0558333333333334 0.0 60.706382375999766
```python
def dsl1(I):
    x1 = asindices(I)
    x2 = ofcolor(I, ZERO)
    x3 = difference(x1, x2)
    O = subgrid(x3, I)
    return O
```
training 67c52801 0.0 61.56551368514339 0.6920364357864358 0.2481952518630925 62.505745372792916
```python
def dsl1(I):
    H = height(I)
    W = width(I)
    top_h = subtract(H, THREE)
    top = canvas(ZERO, astuple(top_h, W))
    band3 = crop(I, astuple(subtract(H, THREE), ZERO), astuple(THREE, W))
    O = vconcat(top, band3)
    return O
```
training 4ff4c9da 0.0 67.42640687119285 0.09863776078239184 0.0 67.52504463197523
```python
def dsl4(I):
    # Replicate 8s across the 2D lattice formed by zero-periods (horizontal and vertical).
    Zobj = toobject(ofcolor(I, ZERO), I)
    P = hperiod(Zobj)
    Vp = vperiod(Zobj)
    seeds = ofcolor(I, EIGHT)
    l = shift(seeds, astuple(0, invert(P)))
    r = shift(seeds, astuple(0, P))
    u = shift(seeds, astuple(invert(Vp), 0))
    d = shift(seeds, astuple(Vp, 0))
    ul = shift(seeds, astuple(invert(Vp), invert(P)))
    ur = shift(seeds, astuple(invert(Vp), P))
    dl = shift(seeds, astuple(Vp, invert(P)))
    dr = shift(seeds, astuple(Vp, P))
    mask = combine(seeds, combine(l, combine(r, combine(u, combine(d, combine(ul, combine(ur, combine(dl, dr))))))))
    O = fill(I, EIGHT, mask)
    return O
```
training 5ffb2104 0.0 67.26871190922247 0.8099999999999999 2.390867979754965 70.46957988897744
```python
def dsl4(I):
    H = height(I)
    W = width(I)
    K = divide(W, THREE)
    S = astuple(0, subtract(W, K))
    R = crop(I, S, astuple(H, K))
    Z = canvas(ZERO, astuple(H, subtract(W, K)))
    O = hconcat(Z, R)
    return O
```
training df8cc377 0.0 72.44474058367854 0.28822404648491606 0.0 72.73296463016345
```python
def dsl2(I):
    objs = objects(I, T, F, T)
    singles = sizefilter(objs, ONE)
    singles_union = merge(singles)
    J = cover(I, singles_union)
    allobjs = objects(J, T, F, T)
    cond_ring = fork(equality, toindices, box)
    rings = sfilter(allobjs, cond_ring)
    h = height(J)
    mid = divide(h, TWO)
    gt_mid = rbind(greater, mid)
    is_bottom = compose(gt_mid, uppermost)
    is_top = compose(flip, is_bottom)
    rings_top = sfilter(rings, is_top)
    rings_bot = sfilter(rings, is_bottom)
    top_interior = mapply(delta, rings_top)
    bot_interior = mapply(delta, rings_bot)
    ctop = leastcolor(tophalf(I))
    cbot = leastcolor(bottomhalf(I))
    K = fill(J, ctop, top_interior)
    O = fill(K, cbot, bot_interior)
    return O
```
training 6855a6e4 0.0 79.12608191037563 0.2844444444444445 0.34991217162622335 79.7604385264463
```python
def dsl1(I):
    x2 = ofcolor(I, TWO)
    b2 = backdrop(x2)
    dest = center(b2)
    x5 = ofcolor(I, FIVE)
    o5 = toobject(x5, I)
    src = centerofmass(o5)
    off = subtract(dest, src)
    O = move(I, o5, off)
    return O
```
training b7955b3c 0.0 80.73645275695009 0.2771284271284272 0.0 81.01358118407853
```python
def dsl3(I):
    x1 = mostcolor(I)
    O = replace(I, EIGHT, x1)
    return O
```
training 50f325b5 0.0 82.33999264134957 0.21495062671533272 0.0 82.5549432680649
```python
def dsl5(I):
    idx3 = ofcolor(I, THREE)
    e = ofcolor(I, EIGHT)
    adj_e_orth = combine(combine(shift(e, UP), shift(e, DOWN)), combine(shift(e, LEFT), shift(e, RIGHT)))
    adj_e_diag = combine(combine(shift(e, UP_RIGHT), shift(e, DOWN_LEFT)), combine(shift(e, UNITY), shift(e, NEG_UNITY)))
    to_change = intersection(idx3, combine(adj_e_orth, adj_e_diag))
    O = fill(I, EIGHT, to_change)
    return O
```
training db118e2a 0.0 81.97294797806792 0.7911111111111111 0.0 82.76405908917904
```python
def dsl1(I):
    x1 = compress(I)
    x2 = asobject(x1)
    d = multiply(FIVE, THREE)
    base = canvas(SEVEN, astuple(d, d))
    off1 = astuple(TWO, TWO)
    off2 = astuple(add(THREE, FIVE), add(THREE, FIVE))
    y1 = shift(x2, off1)
    y2 = shift(x2, off2)
    z1 = paint(base, y1)
    O = paint(z1, y2)
    return O
```
training d6ad076f 0.0 83.0858185033641 0.38 0.0 83.46581850336409
```python
def dsl1(I):
    obs = objects(I, T, F, T)
    a = argmin(obs, leftmost)
    b = other(obs, a)
    # side-by-side if they don't share any column
    side = flip(vmatching(a, b))
    if side:
        # a is left, b is right
        j0 = increment(rightmost(a))
        j1 = decrement(leftmost(b))
        ua = uppermost(a)
        ub = uppermost(b)
        topov = branch(greater(ua, ub), ua, ub)  # max uppermost
        la = lowermost(a)
        lb = lowermost(b)
        botov = branch(greater(la, lb), lb, la)  # min lowermost
        i0 = increment(topov)
        i1 = decrement(botov)
    else:
        # stacked vertically
        topobj = argmin(obs, uppermost)
        botobj = other(obs, topobj)
        i0 = increment(lowermost(topobj))
        i1 = decrement(uppermost(botobj))
        la = leftmost(topobj)
        lb = leftmost(botobj)
        leftov = branch(greater(la, lb), la, lb)  # max leftmost
        ra = rightmost(topobj)
        rb = rightmost(botobj)
        rightov = branch(greater(ra, rb), rb, ra)  # min rightmost
        j0 = increment(leftov)
        j1 = decrement(rightov)
    p1 = astuple(i0, j0)
    p2 = astuple(i1, j1)
    line = connect(p1, p2)
    rect = backdrop(line)
    O = fill(I, EIGHT, rect)
    return O
```
training 94be5b80 0.0 83.13132635384568 0.41594962771433364 0.5411211944762473 84.08839717603627
```python
def dsl1(I):
    nz = difference(asindices(I), ofcolor(I, ZERO))
    r0 = uppermost(nz)
    W = width(I)
    lastc = subtract(W, ONE)
    row0 = connect(astuple(r0, 0), astuple(r0, lastc))
    row1 = connect(astuple(add(r0, ONE), 0), astuple(add(r0, ONE), lastc))
    row2 = connect(astuple(add(r0, TWO), 0), astuple(add(r0, TWO), lastc))
    patch = combine(row0, combine(row1, row2))
    O = fill(I, ZERO, patch)
    return O
```
training d753a70b 0.0 89.86266473669073 0.54296875 0.0 90.40563348669073
```python
def dsl5(I):
    O = I
    return O
```
training 292dd178 0.0 90.4976986718135 0.9681096681096681 0.0 91.46580833992316
```python
def dsl1(I):
    objs = colorfilter(fgpartition(I), ONE)
    U = merge(objs)
    P = delta(U)
    O = underfill(I, TWO, P)
    return O
```
training 20fb2937 0.0 91.28949501132425 1.6923076923076925 0.0 92.98180270363193
```python
def dsl4(I):
    bg = mostcolor(I)
    sqs = sizefilter(objects(I, T, F, T), 9)
    seq = order(sqs, leftmost)
    A = subgrid(first(seq), I)
    C = subgrid(last(seq), I)
    B = subgrid(first(remove(first(seq), remove(last(seq), seq))), I)
    sepcol = canvas(bg, astuple(height(A), 1))
    def row(X, Y, Z):
        return hconcat(hconcat(hconcat(X, sepcol), Y), hconcat(sepcol, Z))
    r1 = row(C, A, B)
    r2 = row(B, C, A)
    r3 = row(A, B, C)
    seprow = canvas(bg, astuple(1, width(r1)))
    O = vconcat(seprow, r1)
    O = vconcat(O, seprow)
    O = vconcat(O, r2)
    O = vconcat(O, seprow)
    O = vconcat(O, r3)
    O = vconcat(O, seprow)
    O = hmirror(O)
    return O
```
training d6542281 0.0 92.98433835033228 0.31195562900755336 0.0 93.29629397933982
```python
def dsl1(I):
    bg = mostcolor(I)
    P = palette(I)
    Pnb = remove(bg, P)
    a = minimum(Pnb)
    d = maximum(Pnb)
    Ptmp = remove(d, Pnb)
    b = maximum(Ptmp)
    idx_b = ofcolor(I, b)
    allidx = asindices(I)
    ul = shift(idx_b, NEG_UNITY)
    up = shift(idx_b, UP)
    left = shift(idx_b, LEFT)
    patch1 = combine(combine(ul, up), left)
    patch1 = intersection(patch1, allidx)
    O = underfill(I, a, patch1)
    right = shift(idx_b, RIGHT)
    down = shift(idx_b, DOWN)
    patch2a = combine(right, down)
    patch2a = intersection(patch2a, allidx)
    O = underfill(O, a, patch2a)
    dr = shift(idx_b, UNITY)
    patchd = intersection(dr, allidx)
    O = underfill(O, d, patchd)
    return O
```
training 264363fd 0.0 99.25749449904578 0.3188888888888889 0.0 99.57638338793465
```python
def dsl2(I):
    # Around each 4: paint onto 3-background only (diagonals -> 5, orthogonals -> 6)
    seeds4 = ofcolor(I, FOUR)
    diag = merge(apply(ineighbors, seeds4))
    ortho = merge(apply(neighbors, seeds4))
    on3d = intersection(diag, ofcolor(I, THREE))
    on3o = intersection(ortho, ofcolor(I, THREE))
    O = fill(I, FIVE, on3d)
    O = fill(O, SIX, on3o)
    O = fill(O, FOUR, seeds4)
    return O
```
training 9c1e755f 0.0 101.9327473075766 0.9600000000000001 0.0 102.8927473075766
```python
def dsl2(I):
    objs = objects(I, T, F, T)
    hls = sfilter(objs, hline)
    # use topmost wide row and bottommost wide row; recolor if uniform
    g1 = rbind(greater, ONE)
    pred_wide = compose(g1, width)
    wide = sfilter(hls, pred_wide)
    # build base from a seed
    def build_paint(seed):
        r = uppermost(seed)
        row_hls = sfilter(hls, matcher(uppermost, r))
        base = merge(row_hls)
        u = ulcorner(base)
        col = vfrontier(u)
        anchors = difference(col, ofcolor(I, ZERO))
        pal = palette(base)
        uniform = equality(size(pal), ONE)
        base_mask = toindices(base)
        g = rbind(subtract, u)
        sh_mask = lbind(shift, base_mask)
        mask_fn = compose(sh_mask, g)
        vals = lbind(index, I)
        recol_fn = fork(recolor, vals, mask_fn)
        paint_recolor = mapply(recol_fn, anchors)
        sh_obj = lbind(shift, base)
        obj_fn = compose(sh_obj, g)
        paint_obj = mapply(obj_fn, anchors)
        return branch(uniform, paint_recolor, paint_obj)
    top = argmin(wide, uppermost)
    bot = argmax(wide, uppermost)
    p_top = build_paint(top)
    p_bot = build_paint(bot)
    paints = combine(p_top, p_bot)
    O = underpaint(I, paints)
    return O
```
training 88207623 0.0 103.7344722646352 0.6158234126984127 0.26805454118056876 104.6183502185142
```python
def dsl2(I):
    t = tophalf(I)
    b = bottomhalf(I)
    b2 = vmirror(b)
    O = vconcat(t, b2)
    return O
```
training 281123b4 0.0 110.67827662859466 3.375 0.17677669514038685 114.23005332373504
```python
def dsl2(I):
    # Same precedence implemented via paint (last writer wins): B -> A -> D -> C
    dims = astuple(FOUR, FOUR)
    a = crop(I, astuple(ZERO, ZERO), dims)
    b = crop(I, astuple(ZERO, FIVE), dims)
    c = crop(I, astuple(ZERO, add(TEN, ZERO)), dims)
    d = crop(I, astuple(ZERO, add(TEN, FIVE)), dims)
    z = canvas(ZERO, dims)
    y = paint(z, asobject(b))
    y = paint(y, asobject(a))
    y = paint(y, asobject(d))
    O = paint(y, asobject(c))
    return O
```
training f9d67f8b 0.0 115.59611354740389 0.29000000000000004 0.0 115.88611354740391
```python
def dsl3(I):
    m = ofcolor(I, NINE)
    base = cover(I, m)
    J = rot90(I)
    obj = toobject(m, J)
    O = underpaint(base, obj)
    return O
```
training db93a21d 0.0 116.68463982884418 1.600277777777778 0.22964988986082804 118.51456749648278
```python
def dsl1(I):
    obs = objects(I, T, F, T)
    nines = colorfilter(obs, NINE)
    outs = mapply(outbox, nines)
    frame = recolor(THREE, outs)
    O = underpaint(I, frame)
    return O
```
training dc2e9a9d 0.0 129.54191363801957 0.38582319149620636 0.11665404613369268 130.04439087564947
```python
def dsl1(I):
    objs = colorfilter(objects(I, T, F, T), THREE)
    def interior(o):
        return flip(bordering(o, I))
    inobjs = sfilter(objs, interior)
    def onecopy(o):
        w1 = add(width(o), ONE)
        r = rightmost(o)
        l = leftmost(o)
        W = width(I)
        fitsR = flip(greater(add(r, w1), subtract(W, ONE)))
        fitsL = greater(subtract(l, w1), NEG_ONE)
        offR = tojvec(w1)
        offL = tojvec(invert(w1))
        off0 = tojvec(ZERO)
        off = branch(fitsR, offR, branch(fitsL, offL, off0))
        p = shift(toindices(o), off)
        return recolor(ONE, toobject(p, I))
    def isborder(o):
        return bordering(o, I)
    bords = sfilter(objs, isborder)
    def eightinward(o):
        H = height(I)
        W = width(I)
        h1 = add(height(o), ONE)
        w1 = add(width(o), ONE)
        top = equality(uppermost(o), ZERO)
        bot = equality(lowermost(o), subtract(H, ONE))
        lef = equality(leftmost(o), ZERO)
        rig = equality(rightmost(o), subtract(W, ONE))
        dy = branch(top, h1, branch(bot, invert(h1), ZERO))
        dx = branch(lef, w1, branch(rig, invert(w1), ZERO))
        off = add(toivec(dy), tojvec(dx))
        p = shift(toindices(o), off)
        return recolor(EIGHT, toobject(p, I))
    ones = merge(apply(onecopy, inobjs))
    eights = merge(apply(eightinward, bords))
    O = underpaint(I, eights)
    O = underpaint(O, ones)
    return O
```
training 278e5215 0.0 140.21858813703713 3.4571428571428573 2.3276927680733883 146.00342376225336
```python
def dsl1(I):
    p5 = ofcolor(I, FIVE)
    s5 = subgrid(p5, I)
    H = height(s5)
    W = width(s5)
    pal = trim(cover(I, toobject(p5, I)))
    r0 = crop(pal, ORIGIN, astuple(ONE, W))
    r1 = crop(pal, astuple(ONE, ZERO), astuple(ONE, W))
    r2 = crop(pal, astuple(TWO, ZERO), astuple(ONE, W))
    e01 = equality(r0, r1)
    e12 = equality(r1, r2)
    Arow = branch(e01, r0, branch(e12, r1, r0))
    Brow = branch(e01, r2, branch(e12, r0, r1))
    Agrid = vupscale(Arow, H)
    Bgrid = vupscale(Brow, H)
    mask = ofcolor(s5, FIVE)
    obj = toobject(mask, Agrid)
    O = paint(Bgrid, obj)
    return O
```
training db615bd4 0.0 152.8982222327197 0.5952 0.0 153.4934222327197
```python
def dsl1(I):
    O = hmirror(I)
    return O
```
training 9b5080bb 0.0 162.12312445309934 0.4535899191216701 0.0 162.576714372221
```python
def dsl4(I):
    x1 = ofcolor(I, EIGHT)
    x2 = toobject(x1, I)
    x3 = cmirror(x2)
    O = paint(I, x3)
    return O
```
training d22278a0 0.0 163.2207679369944 2.3417855015309295 0.6465131876019454 166.20906662612728
```python
def dsl2(I):
    O = rot180(I)
    return O
```
training 891232d6 0.0 171.89399475509546 2.7378725080429955 0.14315949947914336 174.7750267626176
```python
def dsl4(I):
    objs7 = colorfilter(objects(I, T, F, T), SEVEN)
    centers = apply(center, objs7)
    cols = apply(vfrontier, centers)
    twos = apply(lbind(recolor, TWO), cols)
    O = underpaint(I, merge(twos))
    return O
```
training 7bb29440 10.43650317030929 60.0 114.0 1.0108891104062114 185.44739228071552
```python
def dsl5(I):
    comps = objects(I, F, F, T)
    def is_filled(o):
        g = subgrid(o, I)
        return equality(colorcount(g, ZERO), 0)
    rects = sfilter(comps, is_filled)
    base = branch(equality(size(rects), 0), comps, rects)
    def minimize_tile(o):
        R = subgrid(o, I)
        w = width(R)
        h = height(R)
        S = combine(toobject(ofcolor(R, FOUR), R), toobject(ofcolor(R, SIX), R))
        hp = branch(equality(size(S), 0), w, hperiod(S))
        vp = branch(equality(size(S), 0), h, vperiod(S))
        return multiply(vp, hp)
    big = argmin(base, minimize_tile)
    R = subgrid(big, I)
    w = width(R)
    h = height(R)
    S = combine(toobject(ofcolor(R, FOUR), R), toobject(ofcolor(R, SIX), R))
    hp0 = branch(equality(size(S), 0), w, hperiod(S))
    vp0 = branch(equality(size(S), 0), h, vperiod(S))
    wdiv = divide(w, hp0)
    hdiv = divide(h, vp0)
    hp = branch(equality(multiply(wdiv, hp0), w), hp0, w)
    vp = branch(equality(multiply(hdiv, vp0), h), vp0, h)
    O = crop(R, ORIGIN, astuple(vp, hp))
    return O
```
training 39e1d7f9 0.0 204.73490455598045 0.917466713641902 0.08958883486333007 205.7419601044857
```python
def dsl4(I):
    x1 = mostcolor(I)
    O = replace(I, x1, ZERO)
    return O
```
training 305b1341 0.0 234.96534837368472 1.6125000000000003 0.7625692367266093 237.3404176104113
```python
def dsl5(I):
    x1 = downscale(I, TWO)
    x2 = vupscale(x1, TWO)
    O = hupscale(x2, TWO)
    return O
```
training 5c2c9af4 0.0 258.4323426587324 1.6306951892288106 0.08959392049839388 260.15263176845957
```python
def dsl1(I):
    c = leastcolor(I)
    S = ofcolor(I, c)
    G = asindices(I)
    B = box(G)
    L = prapply(connect, S, B)
    P = merge(L)
    Z = canvas(ZERO, shape(I))
    O = fill(Z, c, P)
    return O
```
training 2037f2c7 15.925879193046843 152.0 183.0 1.0117712373610235 351.93765043040787
```python
def dsl4(I):
    base = canvas(ZERO, shape(I))
    nz = difference(asindices(I), ofcolor(I, ZERO))
    bin8 = fill(base, EIGHT, nz)
    y = compress(bin8)
    x = trim(y)
    O = downscale(x, THREE)
    return O
```
training a644e277 15.099019513592784 341.0 309.0 0.7357923790952607 665.8348118926881
```python
def dsl1(I):
    x1 = compress(I)
    x2 = trim(x1)
    O = downscale(x2, THREE)
    return O
```
training 8731374e 14.123105625617661 444.0 404.0 0.7484787726780245 862.8715843982957
```python
def dsl3(I):
    bg = mostcolor(I)
    objs = objects(I, T, F, F)
    big = argmax(colorfilter(objs, bg), size)
    SG0 = subgrid(toindices(big), I)
    SG = compress(SG0)
    idxs = asindices(SG)
    intr = difference(idxs, ofcolor(SG, bg))
    colors = remove(bg, palette(SG))
    fg = branch(equality(size(colors), ZERO), leastcolor(SG), valmax(colors, lbind(colorcount, SG)))
    hf = compose(lbind(intersection, idxs), hfrontier)
    vf = compose(lbind(intersection, idxs), vfrontier)
    H = mapply(hf, intr)
    V = mapply(vf, intr)
    stripes = combine(H, V)
    O0 = canvas(bg, shape(SG))
    O = fill(O0, fg, stripes)
    return O
```
training ce8d95cc 34.555740781599376 118.0 711.0 1.4031890419815098 864.9589298235809
```python
def dsl1(I):
    x1 = rot90(I)
    x2 = compress(x1)
    O = rot270(x2)
    return O
```
training 4290ef0e 24.366430302876516 745.0 434.0 1.2187305956088847 1204.5851608984854
```python
def dsl2(I):
    p = merge(objects(I, True, False, True))
    s = add(ulcorner(p), astuple(0, 2))
    g = crop(I, s, astuple(7, 7))
    O = compress(g)
    return O
```
training 97a05b5b 21.474192049298324 118.0 1087.0 0.6490060297815327 1227.1231980790799
```python
def dsl3(I):
    x1 = compress(I)
    x2 = asindices(x1)
    O = underfill(x1, TWO, x2)
    return O
```
training a416fc5b 7.0710678118654755 993.3735464897914 378.3884297520661 0.18518518513668678 1379.0182292388595
```python
def dsl4(I):
    dims = shape(I)
    O = canvas(SEVEN, dims)
    return O
```
training 6cbe9eb8 28.36193007666084 1007.0 544.140625 1.2563471153160704 1580.7589021919766
```python
def dsl1(I):
    x1 = objects(I, T, T, F)
    x2 = sfilter(x1, fork(equality, toindices, compose(box, toindices)))
    x3 = argmax(x2, compose(size, box))
    O = subgrid(x3, I)
    return O
```
training 00576224 nan nan nan nan nan
```python

```
training 007bbfb7 nan nan nan nan nan
```python

```
training 009d5c81 nan nan nan nan nan
```python

```
training 00d62c1b nan nan nan nan nan
```python

```
training 045e512c nan nan nan nan nan
```python

```
training 0520fde7 nan nan nan nan nan
```python

```
training 05269061 nan nan nan nan nan
```python

```
training 05a7bcf2 nan nan nan nan nan
```python

```
training 05f2a901 nan nan nan nan nan
```python

```
training 0607ce86 nan nan nan nan nan
```python

```
training 0692e18c nan nan nan nan nan
```python

```
training 06df4c85 nan nan nan nan nan
```python

```
training 070dd51e nan nan nan nan nan
```python

```
training 08ed6ac7 nan nan nan nan nan
```python

```
training 09629e4f nan nan nan nan nan
```python

```
training 0962bcdd nan nan nan nan nan
```python

```
training 09c534e7 nan nan nan nan nan
```python

```
training 0a1d4ef5 nan nan nan nan nan
```python

```
training 0a2355a6 nan nan nan nan nan
```python

```
training 0a938d79 nan nan nan nan nan
```python

```
training 0b148d64 nan nan nan nan nan
```python

```
training 0b17323b nan nan nan nan nan
```python

```
training 0bb8deee nan nan nan nan nan
```python

```
training 0becf7df nan nan nan nan nan
```python

```
training 0c786b71 nan nan nan nan nan
```python

```
training 0c9aba6e nan nan nan nan nan
```python

```
training 0ca9ddb6 nan nan nan nan nan
```python

```
training 0d87d2a6 nan nan nan nan nan
```python

```
training 0e206a2e nan nan nan nan nan
```python

```
training 0e671a1a nan nan nan nan nan
```python

```
training 0f63c0b9 nan nan nan nan nan
```python

```
training 103eff5b nan nan nan nan nan
```python

```
training 10fcaaa3 nan nan nan nan nan
```python

```
training 11852cab nan nan nan nan nan
```python

```
training 1190bc91 nan nan nan nan nan
```python

```
training 1190e5a7 nan nan nan nan nan
```python

```
training 11e1fe23 nan nan nan nan nan
```python

```
training 12422b43 nan nan nan nan nan
```python

```
training 12997ef3 nan nan nan nan nan
```python

```
training 12eac192 nan nan nan nan nan
```python

```
training 13713586 nan nan nan nan nan
```python

```
training 137eaa0f nan nan nan nan nan
```python

```
training 137f0df0 nan nan nan nan nan
```python

```
training 140c817e nan nan nan nan nan
```python

```
training 1478ab18 nan nan nan nan nan
```python

```
training 14b8e18c nan nan nan nan nan
```python

```
training 150deff5 nan nan nan nan nan
```python

```
training 15113be4 nan nan nan nan nan
```python

```
training 15660dd6 nan nan nan nan nan
```python

```
training 15663ba9 nan nan nan nan nan
```python

```
training 15696249 nan nan nan nan nan
```python

```
training 17829a00 nan nan nan nan nan
```python

```
training 178fcbfb nan nan nan nan nan
```python

```
training 17b80ad2 nan nan nan nan nan
```python

```
training 17b866bd nan nan nan nan nan
```python

```
training 17cae0c1 nan nan nan nan nan
```python

```
training 18286ef8 nan nan nan nan nan
```python

```
training 182e5d0f nan nan nan nan nan
```python

```
training 18419cfa nan nan nan nan nan
```python

```
training 18447a8d nan nan nan nan nan
```python

```
training 184a9768 nan nan nan nan nan
```python

```
training 195ba7dc nan nan nan nan nan
```python

```
training 1990f7a8 nan nan nan nan nan
```python

```
training 1a07d186 nan nan nan nan nan
```python

```
training 1a244afd nan nan nan nan nan
```python

```
training 1a2e2828 nan nan nan nan nan
```python

```
training 1a6449f1 nan nan nan nan nan
```python

```
training 1acc24af nan nan nan nan nan
```python

```
training 1b2d62fb nan nan nan nan nan
```python

```
training 1b59e163 nan nan nan nan nan
```python

```
training 1b60fb0c nan nan nan nan nan
```python

```
training 1b8318e3 nan nan nan nan nan
```python

```
training 1be83260 nan nan nan nan nan
```python

```
training 1bfc4729 nan nan nan nan nan
```python

```
training 1c02dbbe nan nan nan nan nan
```python

```
training 1c0d0a4b nan nan nan nan nan
```python

```
training 1c56ad9f nan nan nan nan nan
```python

```
training 1c786137 nan nan nan nan nan
```python

```
training 1caeab9d nan nan nan nan nan
```python

```
training 1d0a4b61 nan nan nan nan nan
```python

```
training 1d398264 nan nan nan nan nan
```python

```
training 1da012fc nan nan nan nan nan
```python

```
training 1e0a9b12 nan nan nan nan nan
```python

```
training 1e32b0e9 nan nan nan nan nan
```python

```
training 1e5d6875 nan nan nan nan nan
```python

```
training 1e81d6f9 nan nan nan nan nan
```python

```
training 1efba499 nan nan nan nan nan
```python

```
training 1f0c79e5 nan nan nan nan nan
```python

```
training 1f642eb9 nan nan nan nan nan
```python

```
training 1f85a75f nan nan nan nan nan
```python

```
training 1f876c06 nan nan nan nan nan
```python

```
training 1fad071e nan nan nan nan nan
```python

```
training 2013d3e2 nan nan nan nan nan
```python

```
training 2072aba6 nan nan nan nan nan
```python

```
training 20818e16 nan nan nan nan nan
```python

```
training 20981f0e nan nan nan nan nan
```python

```
training 212895b5 nan nan nan nan nan
```python

```
training 21f83797 nan nan nan nan nan
```python

```
training 2204b7a8 nan nan nan nan nan
```python

```
training 22168020 nan nan nan nan nan
```python

```
training 22208ba4 nan nan nan nan nan
```python

```
training 22233c11 nan nan nan nan nan
```python

```
training 22425bda nan nan nan nan nan
```python

```
training 22806e14 nan nan nan nan nan
```python

```
training 2281f1f4 nan nan nan nan nan
```python

```
training 228f6490 nan nan nan nan nan
```python

```
training 22a4bbc2 nan nan nan nan nan
```python

```
training 22eb0ac0 nan nan nan nan nan
```python

```
training 230f2e48 nan nan nan nan nan
```python

```
training 234bbc79 nan nan nan nan nan
```python

```
training 239be575 nan nan nan nan nan
```python

```
training 23b5c85d nan nan nan nan nan
```python

```
training 25094a63 nan nan nan nan nan
```python

```
training 252143c9 nan nan nan nan nan
```python

```
training 253bf280 nan nan nan nan nan
```python

```
training 256b0a75 nan nan nan nan nan
```python

```
training 25c199f5 nan nan nan nan nan
```python

```
training 25d487eb nan nan nan nan nan
```python

```
training 25d8a9c8 nan nan nan nan nan
```python

```
training 25e02866 nan nan nan nan nan
```python

```
training 2601afb7 nan nan nan nan nan
```python

```
training 2685904e nan nan nan nan nan
```python

```
training 2697da3f nan nan nan nan nan
```python

```
training 272f95fa nan nan nan nan nan
```python

```
training 2753e76c nan nan nan nan nan
```python

```
training 27a28665 nan nan nan nan nan
```python

```
training 27f8ce4f nan nan nan nan nan
```python

```
training 28e73c20 nan nan nan nan nan
```python

```
training 29623171 nan nan nan nan nan
```python

```
training 29700607 nan nan nan nan nan
```python

```
training 29c11459 nan nan nan nan nan
```python

```
training 2a28add5 nan nan nan nan nan
```python

```
training 2a5f8217 nan nan nan nan nan
```python

```
training 2b01abd0 nan nan nan nan nan
```python

```
training 2b9ef948 nan nan nan nan nan
```python

```
training 2bcee788 nan nan nan nan nan
```python

```
training 2bee17df nan nan nan nan nan
```python

```
training 2c0b0aff nan nan nan nan nan
```python

```
training 2c608aff nan nan nan nan nan
```python

```
training 2c737e39 nan nan nan nan nan
```python

```
training 2ccd9fef nan nan nan nan nan
```python

```
training 2dc579da nan nan nan nan nan
```python

```
training 2dd70a9a nan nan nan nan nan
```python

```
training 2de01db2 nan nan nan nan nan
```python

```
training 2e65ae53 nan nan nan nan nan
```python

```
training 2f0c5170 nan nan nan nan nan
```python

```
training 2f767503 nan nan nan nan nan
```python

```
training 2faf500b nan nan nan nan nan
```python

```
training 310f3251 nan nan nan nan nan
```python

```
training 3194b014 nan nan nan nan nan
```python

```
training 319f2597 nan nan nan nan nan
```python

```
training 31aa019c nan nan nan nan nan
```python

```
training 31adaf00 nan nan nan nan nan
```python

```
training 31d5ba1a nan nan nan nan nan
```python

```
training 320afe60 nan nan nan nan nan
```python

```
training 321b1fc6 nan nan nan nan nan
```python

```
training 32e9702f nan nan nan nan nan
```python

```
training 33067df9 nan nan nan nan nan
```python

```
training 332202d5 nan nan nan nan nan
```python

```
training 332efdb3 nan nan nan nan nan
```python

```
training 3345333e nan nan nan nan nan
```python

```
training 337b420f nan nan nan nan nan
```python

```
training 3391f8c0 nan nan nan nan nan
```python

```
training 33b52de3 nan nan nan nan nan
```python

```
training 3428a4f5 nan nan nan nan nan
```python

```
training 342dd610 nan nan nan nan nan
```python

```
training 3490cc26 nan nan nan nan nan
```python

```
training 34b99a2b nan nan nan nan nan
```python

```
training 358ba94e nan nan nan nan nan
```python

```
training 3618c87e nan nan nan nan nan
```python

```
training 36d67576 nan nan nan nan nan
```python

```
training 36fdfd69 nan nan nan nan nan
```python

```
training 37d3e8b2 nan nan nan nan nan
```python

```
training 3906de3d nan nan nan nan nan
```python

```
training 396d80d7 nan nan nan nan nan
```python

```
training 3979b1a8 nan nan nan nan nan
```python

```
training 39a8645d nan nan nan nan nan
```python

```
training 3a301edc nan nan nan nan nan
```python

```
training 3aa6fb7a nan nan nan nan nan
```python

```
training 3ac3eb23 nan nan nan nan nan
```python

```
training 3ad05f52 nan nan nan nan nan
```python

```
training 3af2c5a8 nan nan nan nan nan
```python

```
training 3b4c2228 nan nan nan nan nan
```python

```
training 3bd292e8 nan nan nan nan nan
```python

```
training 3bd67248 nan nan nan nan nan
```python

```
training 3bdb4ada nan nan nan nan nan
```python

```
training 3befdf3e nan nan nan nan nan
```python

```
training 3cd86f4f nan nan nan nan nan
```python

```
training 3d31c5b3 nan nan nan nan nan
```python

```
training 3d6c6e23 nan nan nan nan nan
```python

```
training 3de23699 nan nan nan nan nan
```python

```
training 3e980e27 nan nan nan nan nan
```python

```
training 3eda0437 nan nan nan nan nan
```python

```
training 3ee1011a nan nan nan nan nan
```python

```
training 3f23242b nan nan nan nan nan
```python

```
training 3f7978a0 nan nan nan nan nan
```python

```
training 4093f84a nan nan nan nan nan
```python

```
training 40f6cd08 nan nan nan nan nan
```python

```
training 412b6263 nan nan nan nan nan
```python

```
training 414297c0 nan nan nan nan nan
```python

```
training 41ace6b5 nan nan nan nan nan
```python

```
training 41e4d17e nan nan nan nan nan
```python

```
training 423a55dc nan nan nan nan nan
```python

```
training 42918530 nan nan nan nan nan
```python

```
training 42a15761 nan nan nan nan nan
```python

```
training 42a50994 nan nan nan nan nan
```python

```
training 42f14c03 nan nan nan nan nan
```python

```
training 42f83767 nan nan nan nan nan
```python

```
training 4347f46a nan nan nan nan nan
```python

```
training 4364c1c4 nan nan nan nan nan
```python

```
training 444801d8 nan nan nan nan nan
```python

```
training 445eab21 nan nan nan nan nan
```python

```
training 447fd412 nan nan nan nan nan
```python

```
training 44d8ac46 nan nan nan nan nan
```python

```
training 4522001f nan nan nan nan nan
```python

```
training 456873bc nan nan nan nan nan
```python

```
training 45737921 nan nan nan nan nan
```python

```
training 458e3a53 nan nan nan nan nan
```python

```
training 45bbe264 nan nan nan nan nan
```python

```
training 4612dd53 nan nan nan nan nan
```python

```
training 46442a0e nan nan nan nan nan
```python

```
training 469497ad nan nan nan nan nan
```python

```
training 46f33fce nan nan nan nan nan
```python

```
training 470c91de nan nan nan nan nan
```python

```
training 47c1f68c nan nan nan nan nan
```python

```
training 48131b3c nan nan nan nan nan
```python

```
training 484b58aa nan nan nan nan nan
```python

```
training 4852f2fa nan nan nan nan nan
```python

```
training 48634b99 nan nan nan nan nan
```python

```
training 48d8fb45 nan nan nan nan nan
```python

```
training 48f8583b nan nan nan nan nan
```python

```
training 4938f0c2 nan nan nan nan nan
```python

```
training 494ef9d7 nan nan nan nan nan
```python

```
training 496994bd nan nan nan nan nan
```python

```
training 49d1d64f nan nan nan nan nan
```python

```
training 4b6b68e5 nan nan nan nan nan
```python

```
training 4be741c5 nan nan nan nan nan
```python

```
training 4c177718 nan nan nan nan nan
```python

```
training 4cd1b7b2 nan nan nan nan nan
```python

```
training 4df5b0ae nan nan nan nan nan
```python

```
training 4e45f183 nan nan nan nan nan
```python

```
training 4e469f39 nan nan nan nan nan
```python

```
training 4e7e0eb9 nan nan nan nan nan
```python

```
training 4f537728 nan nan nan nan nan
```python

```
training 5034a0b5 nan nan nan nan nan
```python

```
training 505fff84 nan nan nan nan nan
```python

```
training 506d28a5 nan nan nan nan nan
```python

```
training 50846271 nan nan nan nan nan
```python

```
training 508bd3b6 nan nan nan nan nan
```python

```
training 50a16a69 nan nan nan nan nan
```python

```
training 50aad11f nan nan nan nan nan
```python

```
training 50c07299 nan nan nan nan nan
```python

```
training 5117e062 nan nan nan nan nan
```python

```
training 5168d44c nan nan nan nan nan
```python

```
training 5207a7b5 nan nan nan nan nan
```python

```
training 522fdd07 nan nan nan nan nan
```python

```
training 52364a65 nan nan nan nan nan
```python

```
training 5289ad53 nan nan nan nan nan
```python

```
training 52df9849 nan nan nan nan nan
```python

```
training 52fd389e nan nan nan nan nan
```python

```
training 538b439f nan nan nan nan nan
```python

```
training 539a4f51 nan nan nan nan nan
```python

```
training 53b68214 nan nan nan nan nan
```python

```
training 543a7ed5 nan nan nan nan nan
```python

```
training 54d82841 nan nan nan nan nan
```python

```
training 54d9e175 nan nan nan nan nan
```python

```
training 54db823b nan nan nan nan nan
```python

```
training 54dc2872 nan nan nan nan nan
```python

```
training 55059096 nan nan nan nan nan
```python

```
training 551d5bf1 nan nan nan nan nan
```python

```
training 5521c0d9 nan nan nan nan nan
```python

```
training 5587a8d0 nan nan nan nan nan
```python

```
training 5623160b nan nan nan nan nan
```python

```
training 56dc2b01 nan nan nan nan nan
```python

```
training 56ff96f3 nan nan nan nan nan
```python

```
training 5751f35e nan nan nan nan nan
```python

```
training 575b1a71 nan nan nan nan nan
```python

```
training 5783df64 nan nan nan nan nan
```python

```
training 5792cb4d nan nan nan nan nan
```python

```
training 57aa92db nan nan nan nan nan
```python

```
training 57edb29d nan nan nan nan nan
```python

```
training 5833af48 nan nan nan nan nan
```python

```
training 58743b76 nan nan nan nan nan
```python

```
training 58c02a16 nan nan nan nan nan
```python

```
training 58e15b12 nan nan nan nan nan
```python

```
training 59341089 nan nan nan nan nan
```python

```
training 5a5a2103 nan nan nan nan nan
```python

```
training 5a719d11 nan nan nan nan nan
```python

```
training 5ad4f10b nan nan nan nan nan
```python

```
training 5ad8a7c0 nan nan nan nan nan
```python

```
training 5adee1b2 nan nan nan nan nan
```python

```
training 5af49b42 nan nan nan nan nan
```python

```
training 5b37cb25 nan nan nan nan nan
```python

```
training 5b526a93 nan nan nan nan nan
```python

```
training 5b692c0f nan nan nan nan nan
```python

```
training 5b6cbef5 nan nan nan nan nan
```python

```
training 5d2a5c43 nan nan nan nan nan
```python

```
training 5d588b4d nan nan nan nan nan
```python

```
training 5daaa586 nan nan nan nan nan
```python

```
training 5e6bbc0b nan nan nan nan nan
```python

```
training 5ecac7f7 nan nan nan nan nan
```python

```
training 60b61512 nan nan nan nan nan
```python

```
training 60c09cac nan nan nan nan nan
```python

```
training 60d73be6 nan nan nan nan nan
```python

```
training 6165ea8f nan nan nan nan nan
```python

```
training 626c0bcc nan nan nan nan nan
```python

```
training 62ab2642 nan nan nan nan nan
```python

```
training 62b74c02 nan nan nan nan nan
```python

```
training 62c24649 nan nan nan nan nan
```python

```
training 6350f1f4 nan nan nan nan nan
```python

```
training 63613498 nan nan nan nan nan
```python

```
training 639f5a19 nan nan nan nan nan
```python

```
training 642248e4 nan nan nan nan nan
```python

```
training 642d658d nan nan nan nan nan
```python

```
training 6430c8c4 nan nan nan nan nan
```python

```
training 6455b5f5 nan nan nan nan nan
```python

```
training 64a7c07e nan nan nan nan nan
```python

```
training 652646ff nan nan nan nan nan
```python

```
training 662c240a nan nan nan nan nan
```python

```
training 668eec9a nan nan nan nan nan
```python

```
training 66ac4c3b nan nan nan nan nan
```python

```
training 66e6c45b nan nan nan nan nan
```python

```
training 66f2d22f nan nan nan nan nan
```python

```
training 67385a82 nan nan nan nan nan
```python

```
training 673ef223 nan nan nan nan nan
```python

```
training 67636eac nan nan nan nan nan
```python

```
training 6773b310 nan nan nan nan nan
```python

```
training 67a423a3 nan nan nan nan nan
```python

```
training 681b3aeb nan nan nan nan nan
```python

```
training 689c358e nan nan nan nan nan
```python

```
training 68b67ca3 nan nan nan nan nan
```python

```
training 68bc2e87 nan nan nan nan nan
```python

```
training 692cd3b6 nan nan nan nan nan
```python

```
training 694f12f3 nan nan nan nan nan
```python

```
training 695367ec nan nan nan nan nan
```python

```
training 696d4842 nan nan nan nan nan
```python

```
training 69889d6e nan nan nan nan nan
```python

```
training 6a1e5592 nan nan nan nan nan
```python

```
training 6a980be1 nan nan nan nan nan
```python

```
training 6aa20dc0 nan nan nan nan nan
```python

```
training 6b9890af nan nan nan nan nan
```python

```
training 6bcdb01e nan nan nan nan nan
```python

```
training 6c434453 nan nan nan nan nan
```python

```
training 6ca952ad nan nan nan nan nan
```python

```
training 6cdd2623 nan nan nan nan nan
```python

```
training 6cf79266 nan nan nan nan nan
```python

```
training 6d0160f0 nan nan nan nan nan
```python

```
training 6d1d5c90 nan nan nan nan nan
```python

```
training 6d58a25d nan nan nan nan nan
```python

```
training 6d75e8bb nan nan nan nan nan
```python

```
training 6df30ad6 nan nan nan nan nan
```python

```
training 6e02f1e3 nan nan nan nan nan
```python

```
training 6ea4a07e nan nan nan nan nan
```python

```
training 6ecd11f4 nan nan nan nan nan
```python

```
training 6f8cd79b nan nan nan nan nan
```python

```
training 7039b2d7 nan nan nan nan nan
```python

```
training 705a3229 nan nan nan nan nan
```python

```
training 72207abc nan nan nan nan nan
```python

```
training 72ca375d nan nan nan nan nan
```python

```
training 73182012 nan nan nan nan nan
```python

```
training 73ccf9c2 nan nan nan nan nan
```python

```
training 746b3537 nan nan nan nan nan
```python

```
training 753ea09b nan nan nan nan nan
```python

```
training 758abdf0 nan nan nan nan nan
```python

```
training 759f3fd3 nan nan nan nan nan
```python

```
training 75b8110e nan nan nan nan nan
```python

```
training 760b3cac nan nan nan nan nan
```python

```
training 762cd429 nan nan nan nan nan
```python

```
training 770cc55f nan nan nan nan nan
```python

```
training 776ffc46 nan nan nan nan nan
```python

```
training 780d0b14 nan nan nan nan nan
```python

```
training 782b5218 nan nan nan nan nan
```python

```
training 78e78cff nan nan nan nan nan
```python

```
training 79369cc6 nan nan nan nan nan
```python

```
training 794b24be nan nan nan nan nan
```python

```
training 7953d61e nan nan nan nan nan
```python

```
training 79cce52d nan nan nan nan nan
```python

```
training 7acdf6d3 nan nan nan nan nan
```python

```
training 7b6016b9 nan nan nan nan nan
```python

```
training 7b7f7511 nan nan nan nan nan
```python

```
training 7c008303 nan nan nan nan nan
```python

```
training 7c9b52a0 nan nan nan nan nan
```python

```
training 7d18a6fb nan nan nan nan nan
```python

```
training 7d419a02 nan nan nan nan nan
```python

```
training 7d7772cc nan nan nan nan nan
```python

```
training 7ddcd7ec nan nan nan nan nan
```python

```
training 7df24a62 nan nan nan nan nan
```python

```
training 7e0986d6 nan nan nan nan nan
```python

```
training 7e2bad24 nan nan nan nan nan
```python

```
training 7e4d4f7c nan nan nan nan nan
```python

```
training 7e576d6e nan nan nan nan nan
```python

```
training 7ec998c9 nan nan nan nan nan
```python

```
training 7ee1c6ea nan nan nan nan nan
```python

```
training 7f4411dc nan nan nan nan nan
```python

```
training 7fe24cdd nan nan nan nan nan
```python

```
training 80214e03 nan nan nan nan nan
```python

```
training 80af3007 nan nan nan nan nan
```python

```
training 810b9b61 nan nan nan nan nan
```python

```
training 817e6c09 nan nan nan nan nan
```python

```
training 81c0276b nan nan nan nan nan
```python

```
training 82819916 nan nan nan nan nan
```python

```
training 83302e8f nan nan nan nan nan
```python

```
training 833966f4 nan nan nan nan nan
```python

```
training 833dafe3 nan nan nan nan nan
```python

```
training 834ec97d nan nan nan nan nan
```python

```
training 83b6b474 nan nan nan nan nan
```python

```
training 83eb0a57 nan nan nan nan nan
```python

```
training 84551f4c nan nan nan nan nan
```python

```
training 845d6e51 nan nan nan nan nan
```python

```
training 846bdb03 nan nan nan nan nan
```python

```
training 84ba50d3 nan nan nan nan nan
```python

```
training 84db8fc4 nan nan nan nan nan
```python

```
training 84f2aca1 nan nan nan nan nan
```python

```
training 855e0971 nan nan nan nan nan
```python

```
training 8597cfd7 nan nan nan nan nan
```python

```
training 85b81ff1 nan nan nan nan nan
```python

```
training 85c4e7cd nan nan nan nan nan
```python

```
training 85fa5666 nan nan nan nan nan
```python

```
training 8618d23e nan nan nan nan nan
```python

```
training 868de0fa nan nan nan nan nan
```python

```
training 8719f442 nan nan nan nan nan
```python

```
training 878187ab nan nan nan nan nan
```python

```
training 880c1354 nan nan nan nan nan
```python

```
training 8886d717 nan nan nan nan nan
```python

```
training 88a10436 nan nan nan nan nan
```python

```
training 88a62173 nan nan nan nan nan
```python

```
training 890034e9 nan nan nan nan nan
```python

```
training 896d5239 nan nan nan nan nan
```python

```
training 8a004b2b nan nan nan nan nan
```python

```
training 8a371977 nan nan nan nan nan
```python

```
training 8a6d367c nan nan nan nan nan
```python

```
training 8abad3cf nan nan nan nan nan
```python

```
training 8b28cd80 nan nan nan nan nan
```python

```
training 8ba14f53 nan nan nan nan nan
```python

```
training 8cb8642d nan nan nan nan nan
```python

```
training 8d5021e8 nan nan nan nan nan
```python

```
training 8dab14c2 nan nan nan nan nan
```python

```
training 8dae5dfc nan nan nan nan nan
```python

```
training 8e2edd66 nan nan nan nan nan
```python

```
training 8e301a54 nan nan nan nan nan
```python

```
training 8e5a5113 nan nan nan nan nan
```python

```
training 8eb1be9a nan nan nan nan nan
```python

```
training 8ee62060 nan nan nan nan nan
```python

```
training 8efcae92 nan nan nan nan nan
```python

```
training 8f2ea7aa nan nan nan nan nan
```python

```
training 8fbca751 nan nan nan nan nan
```python

```
training 8fff9e47 nan nan nan nan nan
```python

```
training 902510d5 nan nan nan nan nan
```python

```
training 90347967 nan nan nan nan nan
```python

```
training 90c28cc7 nan nan nan nan nan
```python

```
training 9110e3c5 nan nan nan nan nan
```python

```
training 913fb3ed nan nan nan nan nan
```python

```
training 91413438 nan nan nan nan nan
```python

```
training 91714a58 nan nan nan nan nan
```python

```
training 917bccba nan nan nan nan nan
```python

```
training 928ad970 nan nan nan nan nan
```python

```
training 92e50de0 nan nan nan nan nan
```python

```
training 9344f635 nan nan nan nan nan
```python

```
training 9356391f nan nan nan nan nan
```python

```
training 93c31fbe nan nan nan nan nan
```python

```
training 94133066 nan nan nan nan nan
```python

```
training 941d9a10 nan nan nan nan nan
```python

```
training 9473c6fb nan nan nan nan nan
```python

```
training 952a094c nan nan nan nan nan
```python

```
training 9565186b nan nan nan nan nan
```python

```
training 95990924 nan nan nan nan nan
```python

```
training 95a58926 nan nan nan nan nan
```python

```
training 963c33f8 nan nan nan nan nan
```python

```
training 963e52fc nan nan nan nan nan
```python

```
training 963f59bc nan nan nan nan nan
```python

```
training 96a8c0cd nan nan nan nan nan
```python

```
training 9720b24f nan nan nan nan nan
```python

```
training 97239e3d nan nan nan nan nan
```python

```
training 973e499e nan nan nan nan nan
```python

```
training 9772c176 nan nan nan nan nan
```python

```
training 97c75046 nan nan nan nan nan
```python

```
training 9841fdad nan nan nan nan nan
```python

```
training 984d8a3e nan nan nan nan nan
```python

```
training 985ae207 nan nan nan nan nan
```python

```
training 98c475bf nan nan nan nan nan
```python

```
training 98cf29f8 nan nan nan nan nan
```python

```
training 992798f6 nan nan nan nan nan
```python

```
training 99306f82 nan nan nan nan nan
```python

```
training 995c5fa3 nan nan nan nan nan
```python

```
training 9968a131 nan nan nan nan nan
```python

```
training 996ec1f3 nan nan nan nan nan
```python

```
training 99caaf76 nan nan nan nan nan
```python

```
training 99fa7670 nan nan nan nan nan
```python

```
training 9a4bb226 nan nan nan nan nan
```python

```
training 9aec4887 nan nan nan nan nan
```python

```
training 9af7a82c nan nan nan nan nan
```python

```
training 9b2a60aa nan nan nan nan nan
```python

```
training 9b30e358 nan nan nan nan nan
```python

```
training 9b365c51 nan nan nan nan nan
```python

```
training 9b4c17c4 nan nan nan nan nan
```python

```
training 9ba4a9aa nan nan nan nan nan
```python

```
training 9bebae7a nan nan nan nan nan
```python

```
training 9c56f360 nan nan nan nan nan
```python

```
training 9caba7c3 nan nan nan nan nan
```python

```
training 9caf5b84 nan nan nan nan nan
```python

```
training 9d9215db nan nan nan nan nan
```python

```
training 9ddd00f0 nan nan nan nan nan
```python

```
training 9def23fe nan nan nan nan nan
```python

```
training 9edfc990 nan nan nan nan nan
```python

```
training 9f27f097 nan nan nan nan nan
```python

```
training 9f41bd9c nan nan nan nan nan
```python

```
training 9f5f939b nan nan nan nan nan
```python

```
training 9f669b64 nan nan nan nan nan
```python

```
training 9f8de559 nan nan nan nan nan
```python

```
training a04b2602 nan nan nan nan nan
```python

```
training a096bf4d nan nan nan nan nan
```python

```
training a09f6c25 nan nan nan nan nan
```python

```
training a1570a43 nan nan nan nan nan
```python

```
training a1aa0c1e nan nan nan nan nan
```python

```
training a2d730bd nan nan nan nan nan
```python

```
training a2fd1cf0 nan nan nan nan nan
```python

```
training a3325580 nan nan nan nan nan
```python

```
training a3f84088 nan nan nan nan nan
```python

```
training a406ac07 nan nan nan nan nan
```python

```
training a48eeaf7 nan nan nan nan nan
```python

```
training a59b95c0 nan nan nan nan nan
```python

```
training a5f85a15 nan nan nan nan nan
```python

```
training a61ba2ce nan nan nan nan nan
```python

```
training a61f2674 nan nan nan nan nan
```python

```
training a64e4611 nan nan nan nan nan
```python

```
training a65b410d nan nan nan nan nan
```python

```
training a680ac02 nan nan nan nan nan
```python

```
training a68b268e nan nan nan nan nan
```python

```
training a6953f00 nan nan nan nan nan
```python

```
training a740d043 nan nan nan nan nan
```python

```
training a78176bb nan nan nan nan nan
```python

```
training a79310a0 nan nan nan nan nan
```python

```
training a834deea nan nan nan nan nan
```python

```
training a8610ef7 nan nan nan nan nan
```python

```
training a8c38be5 nan nan nan nan nan
```python

```
training a8d7556c nan nan nan nan nan
```python

```
training a934301b nan nan nan nan nan
```python

```
training a9f96cdd nan nan nan nan nan
```python

```
training aa18de87 nan nan nan nan nan
```python

```
training aa300dc3 nan nan nan nan nan
```python

```
training aa62e3f4 nan nan nan nan nan
```python

```
training aab50785 nan nan nan nan nan
```python

```
training aabf363d nan nan nan nan nan
```python

```
training aaecdb9a nan nan nan nan nan
```python

```
training aaef0977 nan nan nan nan nan
```python

```
training aba27056 nan nan nan nan nan
```python

```
training abbfd121 nan nan nan nan nan
```python

```
training ac0a08a4 nan nan nan nan nan
```python

```
training ac0c2ac3 nan nan nan nan nan
```python

```
training ac2e8ecf nan nan nan nan nan
```python

```
training ac3e2b04 nan nan nan nan nan
```python

```
training ac605cbb nan nan nan nan nan
```python

```
training ac6f9922 nan nan nan nan nan
```python

```
training ad173014 nan nan nan nan nan
```python

```
training ad3b40cf nan nan nan nan nan
```python

```
training ad7e01d0 nan nan nan nan nan
```python

```
training ae3edfdc nan nan nan nan nan
```python

```
training ae4f1146 nan nan nan nan nan
```python

```
training ae58858e nan nan nan nan nan
```python

```
training aedd82e4 nan nan nan nan nan
```python

```
training aee291af nan nan nan nan nan
```python

```
training af24b4cc nan nan nan nan nan
```python

```
training af902bf9 nan nan nan nan nan
```python

```
training afe3afe9 nan nan nan nan nan
```python

```
training b0722778 nan nan nan nan nan
```python

```
training b0c4d837 nan nan nan nan nan
```python

```
training b0f4d537 nan nan nan nan nan
```python

```
training b15fca0b nan nan nan nan nan
```python

```
training b190f7f5 nan nan nan nan nan
```python

```
training b1986d4b nan nan nan nan nan
```python

```
training b1fc8b8e nan nan nan nan nan
```python

```
training b20f7c8b nan nan nan nan nan
```python

```
training b230c067 nan nan nan nan nan
```python

```
training b25e450b nan nan nan nan nan
```python

```
training b27ca6d3 nan nan nan nan nan
```python

```
training b2862040 nan nan nan nan nan
```python

```
training b2bc3ffd nan nan nan nan nan
```python

```
training b457fec5 nan nan nan nan nan
```python

```
training b4a43f3b nan nan nan nan nan
```python

```
training b527c5c6 nan nan nan nan nan
```python

```
training b5bb5719 nan nan nan nan nan
```python

```
training b60334d2 nan nan nan nan nan
```python

```
training b6afb2da nan nan nan nan nan
```python

```
training b71a7747 nan nan nan nan nan
```python

```
training b7249182 nan nan nan nan nan
```python

```
training b7256dcd nan nan nan nan nan
```python

```
training b745798f nan nan nan nan nan
```python

```
training b74ca5d1 nan nan nan nan nan
```python

```
training b775ac94 nan nan nan nan nan
```python

```
training b782dc8a nan nan nan nan nan
```python

```
training b7cb93ac nan nan nan nan nan
```python

```
training b7f8a4d8 nan nan nan nan nan
```python

```
training b7fb29bc nan nan nan nan nan
```python

```
training b8825c91 nan nan nan nan nan
```python

```
training b8cdaf2b nan nan nan nan nan
```python

```
training b942fd60 nan nan nan nan nan
```python

```
training b94a9452 nan nan nan nan nan
```python

```
training b9630600 nan nan nan nan nan
```python

```
training b9b7f026 nan nan nan nan nan
```python

```
training ba1aa698 nan nan nan nan nan
```python

```
training ba26e723 nan nan nan nan nan
```python

```
training ba9d41b8 nan nan nan nan nan
```python

```
training bae5c565 nan nan nan nan nan
```python

```
training bb43febb nan nan nan nan nan
```python

```
training bb52a14b nan nan nan nan nan
```python

```
training bbb1b8b6 nan nan nan nan nan
```python

```
training bbc9ae5d nan nan nan nan nan
```python

```
training bc1d5164 nan nan nan nan nan
```python

```
training bc4146bd nan nan nan nan nan
```python

```
training bc93ec48 nan nan nan nan nan
```python

```
training bcb3040b nan nan nan nan nan
```python

```
training bd14c3bf nan nan nan nan nan
```python

```
training bd283c4a nan nan nan nan nan
```python

```
training bd4472b8 nan nan nan nan nan
```python

```
training bd5af378 nan nan nan nan nan
```python

```
training bda2d7a6 nan nan nan nan nan
```python

```
training be03b35f nan nan nan nan nan
```python

```
training beb8660c nan nan nan nan nan
```python

```
training bf32578f nan nan nan nan nan
```python

```
training bf699163 nan nan nan nan nan
```python

```
training bf89d739 nan nan nan nan nan
```python

```
training c074846d nan nan nan nan nan
```python

```
training c0f76784 nan nan nan nan nan
```python

```
training c1990cce nan nan nan nan nan
```python

```
training c1d99e64 nan nan nan nan nan
```python

```
training c3202e5a nan nan nan nan nan
```python

```
training c35c1b4c nan nan nan nan nan
```python

```
training c3fa4749 nan nan nan nan nan
```python

```
training c444b776 nan nan nan nan nan
```python

```
training c48954c1 nan nan nan nan nan
```python

```
training c6141b15 nan nan nan nan nan
```python

```
training c61be7dc nan nan nan nan nan
```python

```
training c62e2108 nan nan nan nan nan
```python

```
training c64f1187 nan nan nan nan nan
```python

```
training c658a4bd nan nan nan nan nan
```python

```
training c6e1b8da nan nan nan nan nan
```python

```
training c7d4e6ad nan nan nan nan nan
```python

```
training c803e39c nan nan nan nan nan
```python

```
training c87289bb nan nan nan nan nan
```python

```
training c8b7cc0f nan nan nan nan nan
```python

```
training c920a713 nan nan nan nan nan
```python

```
training c92b942c nan nan nan nan nan
```python

```
training c9680e90 nan nan nan nan nan
```python

```
training c97c0139 nan nan nan nan nan
```python

```
training c9f8e694 nan nan nan nan nan
```python

```
training ca8de6ea nan nan nan nan nan
```python

```
training caa06a1f nan nan nan nan nan
```python

```
training cad67732 nan nan nan nan nan
```python

```
training cbded52d nan nan nan nan nan
```python

```
training cc9053aa nan nan nan nan nan
```python

```
training ccd554ac nan nan nan nan nan
```python

```
training cce03e0d nan nan nan nan nan
```python

```
training cdecee7f nan nan nan nan nan
```python

```
training ce039d91 nan nan nan nan nan
```python

```
training ce22a75a nan nan nan nan nan
```python

```
training ce4f8723 nan nan nan nan nan
```python

```
training ce602527 nan nan nan nan nan
```python

```
training ce9e57f2 nan nan nan nan nan
```python

```
training cf133acc nan nan nan nan nan
```python

```
training cfb2ce5a nan nan nan nan nan
```python

```
training d017b73f nan nan nan nan nan
```python

```
training d07ae81c nan nan nan nan nan
```python

```
training d0f5fe59 nan nan nan nan nan
```python

```
training d13f3404 nan nan nan nan nan
```python

```
training d19f7514 nan nan nan nan nan
```python

```
training d23f8c26 nan nan nan nan nan
```python

```
training d255d7a7 nan nan nan nan nan
```python

```
training d282b262 nan nan nan nan nan
```python

```
training d2acf2cb nan nan nan nan nan
```python

```
training d304284e nan nan nan nan nan
```python

```
training d364b489 nan nan nan nan nan
```python

```
training d37a1ef5 nan nan nan nan nan
```python

```
training d406998b nan nan nan nan nan
```python

```
training d43fd935 nan nan nan nan nan
```python

```
training d4469b4b nan nan nan nan nan
```python

```
training d47aa2ff nan nan nan nan nan
```python

```
training d492a647 nan nan nan nan nan
```python

```
training d4a91cb9 nan nan nan nan nan
```python

```
training d4b1c2b1 nan nan nan nan nan
```python

```
training d4c90558 nan nan nan nan nan
```python

```
training d4f3cd78 nan nan nan nan nan
```python

```
training d56f2372 nan nan nan nan nan
```python

```
training d5c634a2 nan nan nan nan nan
```python

```
training d687bc17 nan nan nan nan nan
```python

```
training d6e50e54 nan nan nan nan nan
```python

```
training d749d46f nan nan nan nan nan
```python

```
training d89b689b nan nan nan nan nan
```python

```
training d90796e8 nan nan nan nan nan
```python

```
training d931c21c nan nan nan nan nan
```python

```
training d94c3b52 nan nan nan nan nan
```python

```
training d968ffd4 nan nan nan nan nan
```python

```
training d9f24cd1 nan nan nan nan nan
```python

```
training d9fac9be nan nan nan nan nan
```python

```
training da2b0fe3 nan nan nan nan nan
```python

```
training da6e95e5 nan nan nan nan nan
```python

```
training dae9d2b5 nan nan nan nan nan
```python

```
training db7260a4 nan nan nan nan nan
```python

```
training dbc1a6ce nan nan nan nan nan
```python

```
training dc1df850 nan nan nan nan nan
```python

```
training dc2aa30b nan nan nan nan nan
```python

```
training dc433765 nan nan nan nan nan
```python

```
training dc46ea44 nan nan nan nan nan
```python

```
training dd2401ed nan nan nan nan nan
```python

```
training de1cd16c nan nan nan nan nan
```python

```
training de493100 nan nan nan nan nan
```python

```
training ded97339 nan nan nan nan nan
```python

```
training df978a02 nan nan nan nan nan
```python

```
training df9fd884 nan nan nan nan nan
```python

```
training e048c9ed nan nan nan nan nan
```python

```
training e0fb7511 nan nan nan nan nan
```python

```
training e133d23d nan nan nan nan nan
```python

```
training e1baa8a4 nan nan nan nan nan
```python

```
training e1d2900e nan nan nan nan nan
```python

```
training e2092e0c nan nan nan nan nan
```python

```
training e21a174a nan nan nan nan nan
```python

```
training e21d9049 nan nan nan nan nan
```python

```
training e26a3af2 nan nan nan nan nan
```python

```
training e345f17b nan nan nan nan nan
```python

```
training e3497940 nan nan nan nan nan
```python

```
training e39e9282 nan nan nan nan nan
```python

```
training e3f79277 nan nan nan nan nan
```python

```
training e3fe1151 nan nan nan nan nan
```python

```
training e4075551 nan nan nan nan nan
```python

```
training e40b9e2f nan nan nan nan nan
```python

```
training e41c6fd3 nan nan nan nan nan
```python

```
training e45ef808 nan nan nan nan nan
```python

```
training e4888269 nan nan nan nan nan
```python

```
training e48d4e1a nan nan nan nan nan
```python

```
training e4941b18 nan nan nan nan nan
```python

```
training e5062a87 nan nan nan nan nan
```python

```
training e509e548 nan nan nan nan nan
```python

```
training e50d258f nan nan nan nan nan
```python

```
training e57337a4 nan nan nan nan nan
```python

```
training e5790162 nan nan nan nan nan
```python

```
training e5c44e8f nan nan nan nan nan
```python

```
training e619ca6e nan nan nan nan nan
```python

```
training e633a9e5 nan nan nan nan nan
```python

```
training e6721834 nan nan nan nan nan
```python

```
training e681b708 nan nan nan nan nan
```python

```
training e69241bd nan nan nan nan nan
```python

```
training e6de6e8f nan nan nan nan nan
```python

```
training e729b7be nan nan nan nan nan
```python

```
training e73095fd nan nan nan nan nan
```python

```
training e734a0e8 nan nan nan nan nan
```python

```
training e74e1818 nan nan nan nan nan
```python

```
training e7639916 nan nan nan nan nan
```python

```
training e76a88a6 nan nan nan nan nan
```python

```
training e78887d1 nan nan nan nan nan
```python

```
training e7a25a18 nan nan nan nan nan
```python

```
training e7b06bea nan nan nan nan nan
```python

```
training e7dd8335 nan nan nan nan nan
```python

```
training e84fef15 nan nan nan nan nan
```python

```
training e8593010 nan nan nan nan nan
```python

```
training e872b94a nan nan nan nan nan
```python

```
training e88171ec nan nan nan nan nan
```python

```
training e8dc4411 nan nan nan nan nan
```python

```
training e9614598 nan nan nan nan nan
```python

```
training e98196ab nan nan nan nan nan
```python

```
training e99362f0 nan nan nan nan nan
```python

```
training e9ac8c9e nan nan nan nan nan
```python

```
training e9afcf9a nan nan nan nan nan
```python

```
training e9b4f6fc nan nan nan nan nan
```python

```
training e9bb6954 nan nan nan nan nan
```python

```
training e9c9d9a1 nan nan nan nan nan
```python

```
training e9fc42f2 nan nan nan nan nan
```python

```
training ea32f347 nan nan nan nan nan
```python

```
training ea786f4a nan nan nan nan nan
```python

```
training ea959feb nan nan nan nan nan
```python

```
training ea9794b1 nan nan nan nan nan
```python

```
training eb281b96 nan nan nan nan nan
```python

```
training eb5a1d5d nan nan nan nan nan
```python

```
training ecaa0ec1 nan nan nan nan nan
```python

```
training ecb67b6d nan nan nan nan nan
```python

```
training ed74f2f2 nan nan nan nan nan
```python

```
training edcc2ff0 nan nan nan nan nan
```python

```
training ef135b50 nan nan nan nan nan
```python

```
training ef26cbf6 nan nan nan nan nan
```python

```
training f0df5ff0 nan nan nan nan nan
```python

```
training f0f8a26d nan nan nan nan nan
```python

```
training f15e1fac nan nan nan nan nan
```python

```
training f18ec8cc nan nan nan nan nan
```python

```
training f1bcbc2c nan nan nan nan nan
```python

```
training f1cefba8 nan nan nan nan nan
```python

```
training f21745ec nan nan nan nan nan
```python

```
training f25fbde4 nan nan nan nan nan
```python

```
training f25ffba3 nan nan nan nan nan
```python

```
training f2829549 nan nan nan nan nan
```python

```
training f341894c nan nan nan nan nan
```python

```
training f35d900a nan nan nan nan nan
```python

```
training f3b10344 nan nan nan nan nan
```python

```
training f3cdc58f nan nan nan nan nan
```python

```
training f3e14006 nan nan nan nan nan
```python

```
training f3e62deb nan nan nan nan nan
```python

```
training f45f5ca7 nan nan nan nan nan
```python

```
training f5aa3634 nan nan nan nan nan
```python

```
training f5b8619d nan nan nan nan nan
```python

```
training f5c89df1 nan nan nan nan nan
```python

```
training f76d97a5 nan nan nan nan nan
```python

```
training f823c43c nan nan nan nan nan
```python

```
training f8a8fe49 nan nan nan nan nan
```python

```
training f8b3ba0a nan nan nan nan nan
```python

```
training f8be4b64 nan nan nan nan nan
```python

```
training f8cc533f nan nan nan nan nan
```python

```
training f8f52ecc nan nan nan nan nan
```python

```
training f8ff0b80 nan nan nan nan nan
```python

```
training f9a67cb5 nan nan nan nan nan
```python

```
training fafd9572 nan nan nan nan nan
```python

```
training fafffa47 nan nan nan nan nan
```python

```
training fb791726 nan nan nan nan nan
```python

```
training fbf15a0b nan nan nan nan nan
```python

```
training fc10701f nan nan nan nan nan
```python

```
training fc754716 nan nan nan nan nan
```python

```
training fcb5c309 nan nan nan nan nan
```python

```
training fcc82909 nan nan nan nan nan
```python

```
training fd02da9e nan nan nan nan nan
```python

```
training fd096ab6 nan nan nan nan nan
```python

```
training fd4b2b02 nan nan nan nan nan
```python

```
training fe9372f3 nan nan nan nan nan
```python

```
training fea12743 nan nan nan nan nan
```python

```
training feca6190 nan nan nan nan nan
```python

```
training ff2825db nan nan nan nan nan
```python

```
training ff28f65a nan nan nan nan nan
```python

```
training ff805c23 nan nan nan nan nan
```python

```
training 4c5c2cf0 nan nan nan nan nan
```python

```
training 6ad5bdfd nan nan nan nan nan
```python

```
training 72a961c9 nan nan nan nan nan
```python

```
training 93b4f4b3 nan nan nan nan nan
```python

```
training 95755ff2 nan nan nan nan nan
```python

```
training a57f2f04 nan nan nan nan nan
```python

```
training a87f7484 nan nan nan nan nan
```python

```
training af726779 nan nan nan nan nan
```python

```
training e179c5f4 nan nan nan nan nan
```python

```
training e760a62e nan nan nan nan nan
```python

```
training 34cfa167 nan nan nan nan nan
```python
def dsl5(I):
    # Fill bg with 4; for each of colors 1,2,8 draw a line connecting first and last occurrences
    x0 = replace(I, ZERO, FOUR)
    p1 = ofcolor(I, ONE)
    b1 = positive(size(p1))
    a1 = branch(b1, first(p1), ORIGIN)
    z1 = branch(b1, last(p1), ORIGIN)
    l1 = connect(a1, z1)
    x1 = fill(x0, ONE, l1)
    p2 = ofcolor(I, TWO)
    b2 = positive(size(p2))
    a2 = branch(b2, first(p2), ORIGIN)
    z2 = branch(b2, last(p2), ORIGIN)
    l2 = connect(a2, z2)
    x2 = fill(x1, TWO, l2)
    p8 = ofcolor(I, EIGHT)
    b8 = positive(size(p8))
    a8 = branch(b8, first(p8), ORIGIN)
    z8 = branch(b8, last(p8), ORIGIN)
    l8 = connect(a8, z8)
    O  = fill(x2, EIGHT, l8)
    return O
```
training 3d588dc9 nan nan nan nan nan
```python
def dsl1(I):
    H = height(I)
    W = width(I)
    midr = halve(H)
    objs = objects(I, T, F, T)
    zeros = colorfilter(objs, ZERO)
    rowpatch = hfrontier(astuple(midr, 0))
    selr = extract(zeros, lbind(hmatching, rowpatch))
    sel = branch(equality(selr, F), argmax(zeros, size), selr)
    zinds = toindices(sel)
    midc = halve(W)
    lbord = intersection(zinds, vfrontier(ulcorner(zinds)))
    rbord = intersection(zinds, vfrontier(urcorner(zinds)))
    leftside = greater(midc, rightmost(sel))
    side = branch(leftside, rbord, lbord)
    fardir = branch(leftside, LEFT, RIGHT)
    k1 = intersection(zinds, shift(side, fardir))
    k2 = intersection(zinds, shift(k1, fardir))
    k3 = intersection(zinds, shift(k2, fardir))
    keep = combine(k1, combine(k2, k3))
    J = cover(I, sel)
    K = fill(J, SIX, side)
    O = paint(K, recolor(ZERO, keep))
    return O
```
