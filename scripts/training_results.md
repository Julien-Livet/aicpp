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
training 7468f01a 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    x1 = asindices(I)
    x2 = ofcolor(I, mostcolor(I))
    x3 = difference(x1, x2)
    x4 = subgrid(x3, I)
    O = vmirror(x4)
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
training a87f7484 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    colors = remove(ZERO, palette(I))
    best = argmax(colors, lambda c: colorcount(I, c))
    P = ofcolor(I, best)
    O = subgrid(P, I)
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
training a5313dff 0.0 0.0 0.0 0.0 0.0
```python
def dsl3(I):
    objs = objects(I, T, F, F)
    zeros = colorfilter(objs, ZERO)
    inner = sfilter(zeros, compose(flip, rbind(bordering, I)))
    ones_objs = merge(apply(lbind(recolor, ONE), inner))
    O = underpaint(I, ones_objs)
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
training 6e82a1ae 0.0 0.0 0.0 0.0 0.0
```python
def dsl2(I):
    # By component size: 4 -> 1, 3 -> 2, rest -> 3
    x1 = objects(I, T, F, T)
    x2 = colorfilter(x1, FIVE)
    s4 = sizefilter(x2, 4)
    s3 = sizefilter(x2, 3)
    rest = difference(x2, combine(s4, s3))
    y1 = mapply(lbind(recolor, ONE), s4)
    y2 = mapply(lbind(recolor, TWO), s3)
    y3 = mapply(lbind(recolor, THREE), rest)
    y = merge((y1, y2, y3))
    O = paint(I, y)
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
training 7c8af763 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # Fill each zero-component with the majority color (1 or 2) among its 4-neighborhood ring
    G = I
    comps = colorfilter(objects(I, True, False, False), ZERO)
    for comp in totuple(comps):
        rim = difference(mapply(neighbors, toindices(comp)), toindices(comp))
        rim_obj = toobject(rim, I)
        c1 = colorcount(rim_obj, ONE)
        c2 = colorcount(rim_obj, TWO)
        chosen = branch(greater(c2, c1), TWO, ONE)
        G = fill(G, chosen, toindices(comp))
    return G
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
training b7999b51 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    cols = remove(ZERO, palette(I))
    hfun = compose(height, lbind(ofcolor, I))
    ordered = order(cols, compose(invert, hfun))  # sort by vertical height (desc)
    nrows = valmax(ordered, hfun)
    ncols = size(ordered)
    base = canvas(ZERO, astuple(nrows, ncols))
    js = interval(ZERO, ncols, ONE)
    pairs = pair(js, ordered)
    start = compose(lbind(astuple, ZERO), first)
    endrow = compose(decrement, compose(hfun, last))
    endpt = fork(astuple, endrow, first)
    seg = fork(connect, start, endpt)
    colobj = fork(recolor, last, seg)
    merged = merge(apply(colobj, pairs))
    O = paint(base, merged)
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
training 72a961c9 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    O = I
    A = asindices(I)
    p8 = ofcolor(I, EIGHT)
    p2 = ofcolor(I, TWO)
    u1 = UP
    u2 = add(UP, UP)
    u3 = add(u2, UP)
    u4 = add(u3, UP)
    # 8-columns: fill ones then top 8
    s81 = intersection(A, shift(p8, u1))
    s82 = intersection(A, shift(p8, u2))
    s83 = intersection(A, shift(p8, u3))
    O = fill(O, ONE, s81)
    O = fill(O, ONE, s82)
    O = fill(O, EIGHT, s83)
    # 2-columns: fill ones then top 2
    s21 = intersection(A, shift(p2, u1))
    s22 = intersection(A, shift(p2, u2))
    s23 = intersection(A, shift(p2, u3))
    s24 = intersection(A, shift(p2, u4))
    O = fill(O, ONE, s21)
    O = fill(O, ONE, s22)
    O = fill(O, ONE, s23)
    O = fill(O, TWO, s24)
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
training 281123b4 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # Fixed-position tiles: [0..3], [5..8], [10..13], [15..18]
    t1 = crop(I, ORIGIN, (4, 4))                 # mostly 8
    t2 = crop(I, (0, 5), (4, 4))                 # mostly 5
    t3 = crop(I, (0, 10), (4, 4))                # mostly 9
    t4 = crop(I, (0, 15), (4, 4))                # mostly 4
    # Nonzero patches per tile
    p1 = difference(asindices(t1), ofcolor(t1, ZERO))
    p2 = difference(asindices(t2), ofcolor(t2, ZERO))
    p3 = difference(asindices(t3), ofcolor(t3, ZERO))
    p4 = difference(asindices(t4), ofcolor(t4, ZERO))
    # Convert to objects with original colors
    o1 = toobject(p1, t1)
    o2 = toobject(p2, t2)
    o3 = toobject(p3, t3)
    o4 = toobject(p4, t4)
    # Overlay by priority using paint: lowest -> highest (5,8,4,9)
    O = canvas(ZERO, (4, 4))
    O = paint(O, o2)  # 5
    O = paint(O, o1)  # 8
    O = paint(O, o4)  # 4
    O = paint(O, o3)  # 9
    return O
```
training c4d1a9ae 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # Column-wise cycle: replace background (most common color) by the "next" color among the other three,
    # where "other" is the (first-encountered) non-background color present in that column.
    bg = mostcolor(I)
    P = palette(I)
    P1 = remove(bg, P)
    f1 = lbind(ofcolor, I)
    f2 = compose(leftmost, f1)
    Ss = order(P1, f2)  # ordered cycle of non-bg colors
    a = first(Ss)
    c = last(Ss)
    tmp = remove(a, P1)
    b = first(remove(c, tmp))  # middle color
    colsa = mapply(vfrontier, ofcolor(I, a))
    colsb = mapply(vfrontier, ofcolor(I, b))
    colsc = mapply(vfrontier, ofcolor(I, c))
    Bg = ofcolor(I, bg)
    ta = intersection(Bg, colsa)
    tb = intersection(Bg, colsb)
    tc = intersection(Bg, colsc)
    obj1 = recolor(b, ta)  # a -> b
    obj2 = recolor(c, tb)  # b -> c
    obj3 = recolor(a, tc)  # c -> a
    obj = combine(combine(obj1, obj2), obj3)
    O = paint(I, obj)
    return O
```
training b548a754 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # Extend the rectangle to include the 8 by taking the backdrop of union with the 8-cell
    base = replace(I, EIGHT, ZERO)
    # get the two-color rectangle area via border-color object
    pal = palette(base)
    pal1 = remove(ZERO, pal)
    bcol = argmax(pal1, lbind(colorcount, base))
    objs = objects(base, T, F, T)
    bset = colorfilter(objs, bcol)
    bobj = argmax(bset, size)
    band = backdrop(toindices(bobj))
    # colors by sampling border and interior
    bord0 = box(band)
    inter0 = difference(band, bord0)
    bsample = first(bord0)
    isample = first(inter0)
    bclr = index(base, bsample)
    iclr = index(base, isample)
    # enlarge by including the 8's cell in the seed, then take its bounding box
    epatch = ofcolor(I, EIGHT)
    seed = combine(band, epatch)
    rect = backdrop(seed)
    bord = box(rect)
    inter = difference(rect, bord)
    x1 = fill(base, bclr, bord)
    O = fill(x1, iclr, inter)
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
training 73c3b0d8 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    w = width(I)
    h = height(I)
    R = lowermost(toobject(ofcolor(I, TWO), I))
    top = crop(I, ORIGIN, astuple(R, w))
    bot = crop(I, astuple(R, ZERO), astuple(subtract(h, R), w))
    # shift 4s down within regions
    st = intersection(shift(ofcolor(top, FOUR), DOWN), asindices(top))
    sb_local = intersection(shift(ofcolor(bot, FOUR), DOWN), asindices(bot))
    # apex: downshifted top 4s on the last row above the 2-bar
    last_top = decrement(R)
    rowline_top = hfrontier(astuple(last_top, ZERO))
    apex = intersection(st, rowline_top)
    # diagonals from apex within top: up-right and up-left
    upr = mapply(rbind(shoot, UP_RIGHT), apex)
    upl = mapply(rbind(shoot, NEG_UNITY), apex)
    lines = intersection(combine(upr, upl), asindices(top))
    # assemble
    top_out = paint(replace(top, FOUR, ZERO), recolor(FOUR, combine(st, lines)))
    sb = shift(sb_local, astuple(R, ZERO))
    base = replace(I, FOUR, ZERO)
    O = paint(base, recolor(FOUR, sb))
    O = paint(O, toobject(asindices(top), O))  # ensure top region preserved
    O = vconcat(top_out, crop(O, astuple(R, ZERO), astuple(subtract(h, R), w)))
    return O
```
training a57f2f04 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # Tile the smallest non-zero seed inside each 0-colored rectangular area across that area (modulus tiling).
    H, W = shape(I)
    O = [list(row) for row in I]
    zero_objs = colorfilter(objects(I, True, False, True), ZERO)
    for zobj in zero_objs:
        r0, c0 = ulcorner(zobj)
        Gh, Gw = shape(subgrid(zobj, I))
        G = crop(I, (r0, c0), (Gh, Gw))
        # find seed bounding box (colors not in {0,8})
        rmin = cmin = None
        rmax = cmax = None
        for (ri, rj) in asindices(G):
            v = index(G, (ri, rj))
            if v != ZERO and v != EIGHT:
                if rmin is None or ri < rmin: rmin = ri
                if rmax is None or ri > rmax: rmax = ri
                if cmin is None or rj < cmin: cmin = rj
                if cmax is None or rj > cmax: cmax = rj
        if rmin is None:
            continue  # no seed inside this zero region
        Th, Tw = (rmax - rmin + 1), (cmax - cmin + 1)
        T = crop(G, (rmin, cmin), (Th, Tw))
        for i in range(Gh):
            for j in range(Gw):
                O[r0 + i][c0 + j] = index(T, (i % Th, j % Tw))
    return tuple(tuple(row) for row in O)
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
training af726779 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # Iterative alternating propagation downwards:
    # +2 rows: place SIX at columns where source row has THREE flanked by SEVENs
    # +4 rows: place SEVEN at columns where source row has SEVEN flanked by THREEs (both in previous THREE-set)
    # +6 rows: repeat alternation until set becomes empty or bottom reached
    H = height(I)
    W = width(I)
    O = I
    idx7 = ofcolor(I, SEVEN)
    if size(idx7) == 0:
        return O
    rsrc = minimum(apply(lambda x: x[0], idx7))
    # initial set of 7-columns in source row
    S = set([j for (i, j) in idx7 if i == rsrc])
    if len(S) == 0:
        return O
    offset = 2
    # step 1: from 7-set to 3-set (A)
    while True:
        if rsrc + offset >= H:
            break
        # from S -> A (THREE positions between two 7s)
        A = set()
        for j in range(W):
            if j-1 in S and j+1 in S and index(I, (rsrc, j)) == THREE:
                A.add(j)
        if len(A) == 0:
            break
        patchA = frozenset({(rsrc + offset, j) for j in A})
        O = fill(O, SIX, patchA)
        offset += 2
        if rsrc + offset >= H:
            break
        # from A -> S (SEVEN positions between two THREEs of A)
        S2 = set()
        for j in range(W):
            if j-1 in A and j+1 in A and index(I, (rsrc, j)) == SEVEN:
                S2.add(j)
        if len(S2) == 0:
            break
        patchS2 = frozenset({(rsrc + offset, j) for j in S2})
        O = fill(O, SEVEN, patchS2)
        S = S2
        offset += 2
    return O
```
training 465b7d93 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # Replicate which bbox edges of the payload are fully covered; fill inner if all four are covered.
    objs = objects(I, True, False, True)
    frame = argmax(colorfilter(objs, SIX), size)
    inner = delta(frame)
    c = leastcolor(I)
    payload = toobject(ofcolor(I, c), I)
    base = fill(I, SEVEN, toindices(payload))

    # Payload bbox edges
    pul = ulcorner(payload)
    pll = llcorner(payload)
    pur = urcorner(payload)
    plr = lrcorner(payload)
    left_src = connect(pul, pll)
    right_src = connect(pur, plr)
    top_src = connect(pul, pur)
    bottom_src = connect(pll, plr)
    Pidx = toindices(payload)

    lf = equality(size(intersection(Pidx, left_src)), size(left_src))
    rf = equality(size(intersection(Pidx, right_src)), size(right_src))
    tf = equality(size(intersection(Pidx, top_src)), size(top_src))
    bf = equality(size(intersection(Pidx, bottom_src)), size(bottom_src))
    allfull = both(both(lf, rf), both(tf, bf))

    # Inner bbox edges
    iul = ulcorner(inner)
    ill = llcorner(inner)
    iur = urcorner(inner)
    ilr = lrcorner(inner)
    left_dst = connect(iul, ill)
    right_dst = connect(iur, ilr)
    top_dst = connect(iul, iur)
    bottom_dst = connect(ill, ilr)
    empty = difference(left_dst, left_dst)

    patch = branch(lf, left_dst, empty)
    patch = combine(patch, branch(rf, right_dst, empty))
    patch = combine(patch, branch(tf, top_dst, empty))
    patch = combine(patch, branch(bf, bottom_dst, empty))

    O_edges = fill(base, c, patch)
    O_fill = underfill(base, c, inner)
    O = branch(allfull, O_fill, O_edges)
    return O
```
training 4c5c2cf0 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # Mirror all non-anchor colors across the X-anchor's center (both axes) using ghost-bbox trick
    objs_diag = objects(I, T, T, T)
    anch = initset(None)
    for o in totuple(objs_diag):
        if size(o) == 5 and height(o) == 3 and width(o) == 3:
            anch = o
            break
    if size(anch) == 0:
        return I
    r0, c0 = center(anch)
    anch_col = color(anch)
    O = I
    for v in totuple(palette(I)):
        if v == ZERO or v == anch_col:
            continue
        S = ofcolor(I, v)
        if size(S) == 0:
            continue
        # prepare vertical ghosts so bbox center column is c0
        l = leftmost(S)
        r = rightmost(S)
        dl = subtract(c0, l)
        dr = subtract(r, c0)
        Dv = maximum(insert(dl, initset(dr)))
        gl = astuple(r0, subtract(c0, Dv))
        gr = astuple(r0, add(c0, Dv))
        Gv = insert(gl, initset(gr))
        Pv = combine(S, Gv)
        Sv = difference(vmirror(Pv), Gv)
        # prepare horizontal ghosts so bbox center row is r0
        u = uppermost(S)
        d = lowermost(S)
        du = subtract(r0, u)
        dd = subtract(d, r0)
        Dh = maximum(insert(du, initset(dd)))
        gt = astuple(subtract(r0, Dh), c0)
        gb = astuple(add(r0, Dh), c0)
        Gh = insert(gt, initset(gb))
        Ph = combine(S, Gh)
        Sh = difference(hmirror(Ph), Gh)
        # both reflections: apply horizontal on Sv with same row ghosts
        Q = combine(Sv, Gh)
        Sb = difference(hmirror(Q), Gh)
        inds = combine(S, combine(Sv, combine(Sh, Sb)))
        O = fill(O, v, inds)
    return O
```
training 94414823 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # Rule: Choose which marker colors go to the TL+BR vs TR+BL diagonals
    # by comparing each marker’s nearest distance to corners {TL,BR} vs {TR,BL}.
    allobjs = fgpartition(I)
    ring5 = first(colorfilter(allobjs, FIVE))
    interior = delta(ring5)
    u0 = ulcorner(interior)
    sub = subgrid(interior, I)
    TL = shift(asindices(crop(sub, ORIGIN, TWO_BY_TWO)), u0)
    TR = shift(asindices(crop(sub, astuple(ZERO, TWO), TWO_BY_TWO)), add(u0, astuple(ZERO, TWO)))
    BL = shift(asindices(crop(sub, astuple(TWO, ZERO), TWO_BY_TWO)), add(u0, astuple(TWO, ZERO)))
    BR = shift(asindices(crop(sub, TWO_BY_TWO, TWO_BY_TWO)), add(u0, TWO_BY_TWO))
    d1 = combine(TL, BR)
    d2 = combine(TR, BL)

    markers = difference(allobjs, colorfilter(allobjs, FIVE))
    a = first(markers)
    b = other(markers, a)

    pTL = ulcorner(interior)
    pTR = urcorner(interior)
    pBL = llcorner(interior)
    pBR = lrcorner(interior)

    A = toindices(a); B = toindices(b)
    aTL = manhattan(A, initset(pTL)); aBR = manhattan(A, initset(pBR))
    aTR = manhattan(A, initset(pTR)); aBL = manhattan(A, initset(pBL))
    bTL = manhattan(B, initset(pTL)); bBR = manhattan(B, initset(pBR))
    bTR = manhattan(B, initset(pTR)); bBL = manhattan(B, initset(pBL))

    aMinDiag1 = minimum(insert(aTL, initset(aBR)))
    aMinDiag2 = minimum(insert(aTR, initset(aBL)))
    aToDiag1 = flip(greater(aMinDiag1, aMinDiag2))  # True if a closer to {TL,BR}

    diagA = branch(aToDiag1, d1, d2)
    OA = fill(I, color(a), diagA)
    otherDiag = branch(equality(diagA, d1), d2, d1)
    O = fill(OA, color(b), otherDiag)
    return O
```
training 6ffe8f07 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    idx8 = ofcolor(I, EIGHT)
    rmin = uppermost(idx8)
    rmax = lowermost(idx8)
    cmin = leftmost(idx8)
    cmax = rightmost(idx8)

    rows = interval(rmin, increment(rmax), 1)
    cols = interval(cmin, increment(cmax), 1)
    ones = ofcolor(I, ONE)

    # vertical arms (up)
    up_starts = prapply(astuple, initset(decrement(rmin)), cols)
    up_rays = merge(prapply(shoot, up_starts, initset(UP)))
    up_barriers = intersection(ones, up_rays)
    up_shadows = merge(prapply(shoot, up_barriers, initset(UP)))
    fill_up = difference(up_rays, up_shadows)

    # vertical arms (down)
    down_starts = prapply(astuple, initset(increment(rmax)), cols)
    down_rays = merge(prapply(shoot, down_starts, initset(DOWN)))
    down_barriers = intersection(ones, down_rays)
    down_shadows = merge(prapply(shoot, down_barriers, initset(DOWN)))
    fill_down = difference(down_rays, down_shadows)

    # horizontal arms (left)
    left_starts = prapply(astuple, rows, initset(decrement(cmin)))
    left_rays = merge(prapply(shoot, left_starts, initset(LEFT)))
    left_barriers = intersection(ones, left_rays)
    left_shadows = merge(prapply(shoot, left_barriers, initset(LEFT)))
    fill_left = difference(left_rays, left_shadows)

    # horizontal arms (right)
    right_starts = prapply(astuple, rows, initset(increment(cmax)))
    right_rays = merge(prapply(shoot, right_starts, initset(RIGHT)))
    right_barriers = intersection(ones, right_rays)
    right_shadows = merge(prapply(shoot, right_barriers, initset(RIGHT)))
    fill_right = difference(right_rays, right_shadows)

    band = combine(combine(fill_up, fill_down), combine(fill_left, fill_right))

    allow = combine(ofcolor(I, ZERO), ofcolor(I, TWO))
    targets = intersection(band, allow)
    obj = recolor(FOUR, toobject(targets, I))
    O = paint(I, obj)
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
training 90f3ed37 0.0 5.830951894845301 0.22666666666666668 0.027735009803569147 6.085353571315537
```python
def dsl2(I):
    # Like dsl1, plus "repair" on the next row when the diagonal continuation is missing and the source row has no adjacency
    s = ofcolor(I, EIGHT)
    adj = intersection(s, shift(s, RIGHT))
    rowsR = mapply(rbind(shoot, RIGHT), adj)
    rowsL = mapply(rbind(shoot, LEFT), adj)
    rows_with_adj = combine(rowsR, rowsL)
    rows_all = asindices(I)
    rows_wo_adj = difference(rows_all, rows_with_adj)
    b1 = difference(shift(s, RIGHT), s)
    block = shift(s, UP)
    # current row continuous fill (only if row has adjacency and no diagonal continuation)
    starts_curr = difference(intersection(b1, rows_with_adj), block)
    rays_curr = mapply(rbind(shoot, RIGHT), starts_curr)
    # next row repair (only if row has no adjacency and no diagonal continuation)
    starts_next = shift(difference(intersection(b1, rows_wo_adj), block), DOWN)
    rays_next = mapply(rbind(shoot, RIGHT), starts_next)
    F = combine(rays_curr, rays_next)
    O = underfill(I, ONE, F)
    return O
```
training 46c35fc7 0.0 7.615773105863909 0.08163265306122447 0.0 7.697405758925133
```python
def dsl1(I):
    O = I
    for obj in totuple(objects(I, F, F, T)):
        sub = subgrid(obj, I)
        idxs = asindices(sub)
        ring = box(idxs)
        crn = corners(idxs)
        cw = rot90(sub)
        ccw = rot270(sub)
        O = move(O, toobject(ring, cw), ulcorner(obj))
        O = move(O, toobject(crn, ccw), ulcorner(obj))
    return O
```
training 351d6448 0.0 9.1104335791443 0.3589743589743589 0.06491134833686076 9.534319286455519
```python
def dsl4(I):
    x = replace(I, FIVE, ZERO)
    objs = objects(x, F, F, T)
    t = totuple(objs)
    rows = order(apply(uppermost, t), identity)
    rk = last(rows)
    rp = last(remove(rk, rows))
    o_last = merge(sfilter(objs, matcher(uppermost, rk)))
    o_prev = merge(sfilter(objs, matcher(uppermost, rp)))
    jl_last = leftmost(o_last)
    jr_last = rightmost(o_last)
    jl_prev = leftmost(o_prev)
    jr_prev = rightmost(o_prev)
    dl = subtract(jl_last, jl_prev)
    dr = subtract(jr_last, jr_prev)
    start_base = add(jl_last, dl)
    W = width(I)
    base = canvas(ZERO, astuple(3, W))
    p = shift(normalize(o_last), astuple(1, start_base))
    O = paint(base, p)
    extR = subtract(dr, dl)
    row_last = uppermost(o_last)
    cR = index(x, astuple(row_last, jr_last))
    r_moved = add(start_base, subtract(width(o_last), ONE))
    jR_ext_start = add(r_moved, ONE)
    jR_ext_end = add(r_moved, extR)
    segR = recolor(cR, connect(astuple(1, jR_ext_start), astuple(1, jR_ext_end)))
    O = branch(greater(extR, ZERO), paint(O, segR), O)
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
    O = vconcat(hconcat(TL2, TR1), hconcat(BL1, BR2))
    return O
```
training 516b51b7 0.0 11.874342087037917 0.2705882352941177 0.0 12.144930322332035
```python
def dsl2(I):
    comps = colorfilter(objects(I, True, False, True), ONE)
    erode = fork(difference, toindices, box)
    shrink2 = compose(erode, erode)
    inner1 = merge(apply(erode, comps))
    inner2_list = apply(shrink2, comps)
    ring2 = merge(apply(box, inner2_list))
    O = fill(I, TWO, inner1)
    O = fill(O, THREE, ring2)
    return O
```
training c8cbb738 0.0 12.649110640673518 0.16326530612244894 0.0 12.812375946795967
```python
def dsl2(I):
    bg = mostcolor(I)
    objs = fgpartition(I)
    # size from max extent
    n = maximum(combine(initset(valmax(objs, height)), initset(valmax(objs, width))))
    l = subtract(n, ONE)
    l1 = subtract(l, ONE)
    m = divide(n, TWO)
    # patches
    cpatch = insert(astuple(ZERO, ZERO), insert(astuple(ZERO, l), insert(astuple(l, ZERO), initset(astuple(l, l)))))
    ppatch = insert(astuple(ZERO, m), insert(astuple(m, ZERO), insert(astuple(m, l), initset(astuple(l, m)))))
    tpatch = insert(astuple(ZERO, ONE), insert(astuple(ZERO, l1), insert(astuple(l, ONE), initset(astuple(l, l1)))))
    lpatch = insert(astuple(ONE, ZERO), insert(astuple(l1, ZERO), insert(astuple(ONE, l), initset(astuple(l1, l)))))
    # selection by geometric signature
    intersz = compose(size, fork(intersection, toindices, corners))
    sqcond = fork(both, matcher(height, n), matcher(width, n))
    oc = extract(objs, fork(both, sqcond, matcher(intersz, FOUR)))
    op = extract(objs, fork(both, sqcond, matcher(intersz, ZERO)))
    # fallbacks if not found
    oc = branch(equality(oc, oc), oc, argmax(objs, intersz))
    op = branch(equality(op, op), op, argmin(objs, intersz))
    # edge colors
    top = crop(I, astuple(ZERO, ZERO), astuple(ONE, width(I)))
    left = crop(I, astuple(ZERO, ZERO), astuple(height(I), ONE))
    O = canvas(bg, astuple(n, n))
    O1 = branch(greater(n, THREE), paint(O, recolor(leastcolor(top), tpatch)), O)
    O2 = branch(greater(n, THREE), paint(O1, recolor(leastcolor(left), lpatch)), O1)
    O3 = paint(O2, recolor(color(oc), cpatch))
    O4 = paint(O3, recolor(color(op), ppatch))
    return O4
```
training f28a3cbb 0.0 14.485281374238568 0.12345679012345678 0.0 14.608738164362027
```python
def dsl1(I):
    bg = mostcolor(I)
    p = palette(I)
    pnbg = remove(bg, p)
    a = first(pnbg)
    b = other(pnbg, a)
    oa = ofcolor(I, a)
    ob = ofcolor(I, b)
    sca = add(uppermost(oa), leftmost(oa))
    scb = add(uppermost(ob), leftmost(ob))
    ctl = branch(greater(sca, scb), b, a)
    cbr = other(pnbg, ctl)
    ntl = colorcount(I, ctl)
    nbr = colorcount(I, cbr)
    stl = branch(greater(ntl, multiply(EIGHT, EIGHT)), NINE,
          branch(greater(ntl, multiply(SEVEN, SEVEN)), EIGHT,
          branch(greater(ntl, multiply(SIX, SIX)), SEVEN,
          branch(greater(ntl, multiply(FIVE, FIVE)), SIX,
          branch(greater(ntl, multiply(FOUR, FOUR)), FIVE,
          branch(greater(ntl, multiply(THREE, THREE)), FOUR,
          branch(greater(ntl, multiply(TWO, TWO)), THREE,
          branch(greater(ntl, multiply(ONE, ONE)), TWO, ONE))))))))
    sbr = branch(greater(nbr, multiply(EIGHT, EIGHT)), NINE,
          branch(greater(nbr, multiply(SEVEN, SEVEN)), EIGHT,
          branch(greater(nbr, multiply(SIX, SIX)), SEVEN,
          branch(greater(nbr, multiply(FIVE, FIVE)), SIX,
          branch(greater(nbr, multiply(FOUR, FOUR)), FIVE,
          branch(greater(nbr, multiply(THREE, THREE)), FOUR,
          branch(greater(nbr, multiply(TWO, TWO)), THREE,
          branch(greater(nbr, multiply(ONE, ONE)), TWO, ONE))))))))
    qtl = divide(ntl, stl)
    rtl = subtract(ntl, multiply(qtl, stl))
    qbr = divide(nbr, sbr)
    rbr = subtract(nbr, multiply(qbr, sbr))
    H = height(I)
    W = width(I)
    base = canvas(bg, shape(I))
    # TL row-major: full rows + partial row
    full_tl = asindices(canvas(ZERO, astuple(qtl, stl)))
    part_tl = asindices(canvas(ZERO, astuple(ONE, rtl)))
    part_tl = shift(part_tl, astuple(qtl, ZERO))
    base = fill(base, ctl, combine(full_tl, part_tl))
    # BR column-major: full cols + partial col from bottom
    full_br = asindices(canvas(ZERO, astuple(sbr, qbr)))
    full_br = shift(full_br, astuple(subtract(H, sbr), subtract(W, qbr)))
    part_br = asindices(canvas(ZERO, astuple(rbr, ONE)))
    part_br = shift(part_br, astuple(subtract(H, rbr), decrement(subtract(W, qbr))))
    O = fill(base, cbr, combine(full_br, part_br))
    return O
```
training 95755ff2 0.0 15.231546211727817 0.04132231404958675 0.0 15.272868525777405
```python
def dsl1(I):
    # Four-direction border projection:
    # - Top/bottom seeds project vertically inside H-interior (between 2s horizontally), blocked by 3s.
    # - Left/right seeds project horizontally inside V-interior (between 2s vertically), blocked by 3s.
    g = lbind(index, I)
    H = height(I)
    W = width(I)

    nz = compose(flip, matcher(g, ZERO))
    n2 = compose(flip, matcher(g, TWO))
    n3 = compose(flip, matcher(g, THREE))
    keepEdge = fork(both, nz, fork(both, n2, n3))

    # Borders
    top = hfrontier(astuple(ZERO, ZERO))
    bot = hfrontier(astuple(subtract(H, ONE), ZERO))
    lef = vfrontier(astuple(ZERO, ZERO))
    rig = vfrontier(astuple(ZERO, subtract(W, ONE)))

    topSeeds = sfilter(top, keepEdge)
    botSeeds = sfilter(bot, keepEdge)
    leftSeeds = sfilter(lef, keepEdge)
    rightSeeds = sfilter(rig, keepEdge)

    # Interiors from 2-walls
    twos = ofcolor(I, TWO)
    leftRays = mapply(rbind(shoot, LEFT), twos)
    rightRays = mapply(rbind(shoot, RIGHT), twos)
    interH = intersection(leftRays, rightRays)
    upRays = mapply(rbind(shoot, UP), twos)
    downRays = mapply(rbind(shoot, DOWN), twos)
    interV = intersection(upRays, downRays)

    # 3s as blockers
    threes = ofcolor(I, THREE)
    blockDown = mapply(rbind(shoot, DOWN), threes)
    blockUp = mapply(rbind(shoot, UP), threes)
    blockRight = mapply(rbind(shoot, RIGHT), threes)
    blockLeft = mapply(rbind(shoot, LEFT), threes)

    # Rays
    rayDown = rbind(shoot, DOWN)
    rayUp = rbind(shoot, UP)
    rayRight = rbind(shoot, RIGHT)
    rayLeft = rbind(shoot, LEFT)

    # Allowed sets
    topAllowed = compose(rbind(difference, blockDown), compose(lbind(intersection, interH), rayDown))
    botAllowed = compose(rbind(difference, blockUp), compose(lbind(intersection, interH), rayUp))
    leftAllowed = compose(rbind(difference, blockRight), compose(lbind(intersection, interV), rayRight))
    rightAllowed = compose(rbind(difference, blockLeft), compose(lbind(intersection, interV), rayLeft))

    makeT = fork(recolor, g, topAllowed)
    makeB = fork(recolor, g, botAllowed)
    makeL = fork(recolor, g, leftAllowed)
    makeR = fork(recolor, g, rightAllowed)

    objT = mapply(makeT, topSeeds)
    objB = mapply(makeB, botSeeds)
    objL = mapply(makeL, leftSeeds)
    objR = mapply(makeR, rightSeeds)
    obj = combine(combine(objT, objB), combine(objL, objR))

    O = underpaint(I, obj)
    return O
```
training 60a26a3e 0.0 15.618711689061186 0.3588756613756615 0.1848531306423995 16.162440481079244
```python
def dsl3(I):
    S = ofcolor(I, TWO)
    R_has2 = merge(apply(hfrontier, S))
    R_no2 = difference(asindices(I), R_has2)
    # vertical-only hypothesis (fill through rows that never contain a 2)
    V1e = intersection(S, shift(S, multiply(DOWN, ONE)))
    V2e = intersection(S, shift(S, multiply(DOWN, TWO)))
    V3e = intersection(S, shift(S, multiply(DOWN, THREE)))
    V4e = intersection(S, shift(S, multiply(DOWN, FOUR)))
    V5e = intersection(S, shift(S, multiply(DOWN, FIVE)))
    V6e = intersection(S, shift(S, multiply(DOWN, SIX)))
    V7e = intersection(S, shift(S, multiply(DOWN, SEVEN)))
    V8e = intersection(S, shift(S, multiply(DOWN, EIGHT)))
    V1 = merge(prapply(connect, V1e, shift(V1e, multiply(DOWN, ONE))))
    V2 = merge(prapply(connect, V2e, shift(V2e, multiply(DOWN, TWO))))
    V3 = merge(prapply(connect, V3e, shift(V3e, multiply(DOWN, THREE))))
    V4 = merge(prapply(connect, V4e, shift(V4e, multiply(DOWN, FOUR))))
    V5 = merge(prapply(connect, V5e, shift(V5e, multiply(DOWN, FIVE))))
    V6 = merge(prapply(connect, V6e, shift(V6e, multiply(DOWN, SIX))))
    V7 = merge(prapply(connect, V7e, shift(V7e, multiply(DOWN, SEVEN))))
    V8 = merge(prapply(connect, V8e, shift(V8e, multiply(DOWN, EIGHT))))
    Vall = combine(combine(combine(V1, V2), combine(V3, V4)), combine(combine(V5, V6), combine(V7, V8)))
    Vin_ok = intersection(difference(Vall, S), R_no2)
    O = underpaint(I, recolor(ONE, toobject(Vin_ok, I)))
    return O
```
training d93c6891 0.0 17.788656935474513 0.10633680555555558 0.0 17.89499374103007
```python
def dsl1(I):
    x1 = switch(I, FIVE, SEVEN)
    O = replace(x1, SEVEN, FOUR)
    return O
```
training 6e19193c 0.0 19.595917942265423 0.06000000000000005 0.07905694147625864 19.734974883741682
```python
def dsl1(I):
    K = other(palette(I), ZERO)
    OB = colorfilter(objects(I, T, F, T), K)
    Ls = sizefilter(OB, THREE)
    A = first(Ls)
    B = other(Ls, A)
    TA = toindices(A)
    TB = toindices(B)
    MA = first(delta(A))
    MB = first(delta(B))
    dA = branch(contained(add(MA, RIGHT), TA), DOWN_LEFT, UP_RIGHT)
    dB = branch(contained(add(MB, RIGHT), TB), DOWN_LEFT, UP_RIGHT)
    PA = shoot(add(MA, dA), dA)
    PB = shoot(add(MB, dB), dB)
    Q = combine(PA, PB)
    O = underfill(I, K, Q)
    return O
```
training 67c52801 0.0 21.52783357107331 0.33806818181818177 0.08254242323229061 21.94844417612378
```python
def dsl2(I):
    H = height(I)
    W = width(I)
    top = canvas(ZERO, astuple(subtract(H, THREE), W))
    band = crop(I, astuple(subtract(H, THREE), ZERO), astuple(TWO, W))
    bottom = crop(I, astuple(subtract(H, ONE), ZERO), astuple(ONE, W))
    G = vconcat(vconcat(top, band), bottom)

    base = mostcolor(bottom)
    upper = crop(I, ORIGIN, astuple(subtract(H, THREE), W))
    nobase_upper = replace(upper, base, ZERO)
    ups = objects(nobase_upper, T, F, T)
    # order objects by area ascending (tie-breaking left-to-right implicit)
    ups_ord = order(ups, size)
    cols = apply(color, ups_ord)

    row_top = crop(band, ORIGIN, astuple(ONE, W))
    row_bot = crop(band, astuple(ONE, ZERO), astuple(ONE, W))
    free_top = paint(canvas(ZERO, astuple(ONE, W)), recolor(ONE, ofcolor(row_top, ZERO)))
    free_bot = paint(canvas(ZERO, astuple(ONE, W)), recolor(ONE, ofcolor(row_bot, ZERO)))
    both = cellwise(free_top, free_bot, ZERO)
    both2 = vupscale(both, TWO)

    segs_rel = colorfilter(objects(both2, T, F, T), ONE)
    # map gaps strictly left-to-right
    segs_ord = order(segs_rel, leftmost)
    segs_idx = apply(toindices, segs_ord)

    down_vec = astuple(subtract(H, THREE), ZERO)
    abs_segs = apply(rbind(shift, down_vec), segs_idx)
    seg_colored = papply(recolor, cols, abs_segs)
    union = merge(seg_colored)
    O = paint(G, union)
    return O
```
training 11dc524f 0.0 24.08318915758459 0.11834319526627213 0.0 24.201532352850865
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
```
training 3d588dc9 0.0 27.712812921102035 0.06640625 0.0 27.779219171102035
```python
def dsl3(I):
    H = height(I)
    midr = halve(H)
    crow = hfrontier(astuple(midr, 0))
    # widen the central band to three rows (mid-1, mid, mid+1) if possible
    band = combine(shift(crow, UP), combine(crow, shift(crow, DOWN)))
    objs = objects(I, T, F, T)
    zeros = colorfilter(objs, ZERO)
    others = difference(objs, zeros)
    otherinds = mapply(toindices, others)
    # pick zero object intersecting the central band; else nearest to nonzero objects
    zhit = extract(zeros, lbind(hmatching, band))
    sel = branch(equality(zhit, F), argmin(zeros, compose(rbind(manhattan, otherinds), toindices)), zhit)
    zinds = toindices(sel)
    lbord = intersection(zinds, vfrontier(ulcorner(zinds)))
    rbord = intersection(zinds, vfrontier(urcorner(zinds)))
    ldist = manhattan(lbord, otherinds)
    rdist = manhattan(rbord, otherinds)
    side = branch(greater(ldist, rdist), rbord, lbord)
    fardir = branch(equality(side, lbord), RIGHT, LEFT)
    k1 = intersection(zinds, shift(side, fardir))
    k2 = intersection(zinds, shift(k1, fardir))
    k3 = intersection(zinds, shift(k2, fardir))
    keep = combine(k1, combine(k2, k3))
    J = cover(I, sel)
    K = fill(J, SIX, side)
    O = paint(K, recolor(ZERO, keep))
    return O
```
training f0100645 0.0 28.69560344015403 0.33753086419753087 0.0 29.033134304351563
```python
def dsl1(I):
    # Full gravitate of interior left/right colors to their respective border columns
    w = width(I)
    leftc = index(I, astuple(ZERO, ZERO))
    rightc = index(I, astuple(ZERO, subtract(w, ONE)))
    leftcol = shoot(astuple(ZERO, ZERO), DOWN)
    rightcol = shoot(astuple(ZERO, subtract(w, ONE)), DOWN)
    # move all interior left-color cells fully toward the left column
    allL = ofcolor(I, leftc)
    internalL = difference(allL, leftcol)
    objL = toobject(internalL, I)
    dirL = gravitate(internalL, leftcol)
    g1 = move(I, objL, dirL)
    # then move all interior right-color cells fully toward the right column
    allR = ofcolor(g1, rightc)
    internalR = difference(allR, rightcol)
    objR = toobject(internalR, g1)
    dirR = gravitate(internalR, rightcol)
    O = move(g1, objR, dirR)
    return O
```
training 30f42897 0.0 29.02002883216378 0.7555555555555555 0.0 29.775584387719334
```python
def dsl4(I):
    # Draw top and bottom horizontal segments of the least color.
    # If that color appears on the right border, place segments from the left;
    # otherwise place them from the right.
    c = leastcolor(I)
    n = colorcount(I, c)
    h = height(I)
    w = width(I)
    leftcol = vfrontier(ORIGIN)
    jright = subtract(w, ONE)
    rightcol = vfrontier(astuple(ZERO, jright))
    leftn = size(intersection(ofcolor(I, c), leftcol))
    rightn = size(intersection(ofcolor(I, c), rightcol))
    startj = branch(greater(rightn, ZERO), ZERO, subtract(w, n))
    endj = subtract(add(startj, n), ONE)
    topseg = connect(astuple(ZERO, startj), astuple(ZERO, endj))
    botseg = connect(astuple(subtract(h, ONE), startj), astuple(subtract(h, ONE), endj))
    segs = combine(topseg, botseg)
    O = underpaint(I, recolor(c, segs))
    return O
```
training 825aa9e9 0.0 32.834266053633414 0.5153968253968254 0.0 33.34966287903024
```python
def dsl1(I):
    # Move all foreground objects downward until adjacent to the last two rows (leave a 1-row buffer above the floor)
    h = height(I)
    w = width(I)
    row_m1 = subtract(h, ONE)
    row_m2 = subtract(h, TWO)
    lastrow = shoot(astuple(row_m1, ZERO), RIGHT)
    above_last = shoot(astuple(row_m2, ZERO), RIGHT)
    barrier = combine(lastrow, above_last)

    objs = fgpartition(I)
    movable = []
    for o in objs:
        if size(intersection(toindices(o), barrier)) == 0:
            movable.append(o)

    G = I
    for o in movable:
        G = cover(G, o)
    for o in movable:
        v = gravitate(o, barrier)
        G = move(G, o, v)
    return G
```
training 13f06aa5 0.0 38.8599735902272 0.15983101865454807 0.0 39.01980460888174
```python
def dsl4(I):
    # Simpler hypothesis: for each non-bg singleton, paint only the chosen border (no step-2 ray), with ULRD clear-path priority;
    # zero any border-intersection corners.
    inds = asindices(I)
    tlc = ulcorner(inds); trc = urcorner(inds); blc = llcorner(inds)
    top = hfrontier(tlc); bot = hfrontier(blc); lef = vfrontier(tlc); rig = vfrontier(trc)
    bg = mostcolor(I)
    singles = sizefilter(objects(I, T, F, T), ONE)
    nonbg = difference(singles, colorfilter(singles, bg))

    def proc(O, o, gate):
        p = first(toindices(o)); c = color(o)
        bu = difference(intersection(shoot(p, UP), inds), initset(p))
        bd = difference(intersection(shoot(p, DOWN), inds), initset(p))
        bl = difference(intersection(shoot(p, LEFT), inds), initset(p))
        br = difference(intersection(shoot(p, RIGHT), inds), initset(p))
        cu = equality(bu, intersection(bu, ofcolor(I, bg)))
        cd = equality(bd, intersection(bd, ofcolor(I, bg)))
        cl = equality(bl, intersection(bl, ofcolor(I, bg)))
        cr = equality(br, intersection(br, ofcolor(I, bg)))

        su = cu
        sl = both(flip(su), cl)
        sr = both(flip(either(su, sl)), cr)
        sd = both(flip(either(either(su, sl), sr)), cd)

        O = branch(both(gate, su), fill(O, c, top), O)
        O = branch(both(gate, sl), fill(O, c, lef), O)
        O = branch(both(gate, sr), fill(O, c, rig), O)
        O = branch(both(gate, sd), fill(O, c, bot), O)
        return O, su, sd, sl, sr

    O = I
    o1 = first(nonbg); o2 = last(nonbg)
    two = flip(equality(o1, o2))
    O, su1, sd1, sl1, sr1 = proc(O, o1, T)
    O, su2, sd2, sl2, sr2 = proc(O, o2, two)

    bt = either(su1, su2); bb = either(sd1, sd2)
    blf = either(sl1, sl2); brg = either(sr1, sr2)
    O = branch(both(bt, blf), fill(O, ZERO, intersection(top, lef)), O)
    O = branch(both(bt, brg), fill(O, ZERO, intersection(top, rig)), O)
    O = branch(both(bb, blf), fill(O, ZERO, intersection(bot, lef)), O)
    O = branch(both(bb, brg), fill(O, ZERO, intersection(bot, rig)), O)
    return O
```
training 94be5b80 0.0 40.33608806019741 0.2518518518518519 0.2790499102773244 40.86698982232659
```python
def dsl1(I):
    # Remove 3-row banner at its first nonzero row; add copies of the largest shape layer above and below
    nz = difference(asindices(I), ofcolor(I, ZERO))
    r0 = uppermost(nz)
    W = width(I)
    lastc = subtract(W, ONE)
    row0 = connect(astuple(r0, 0), astuple(r0, lastc))
    row1 = connect(astuple(add(r0, ONE), 0), astuple(add(r0, ONE), lastc))
    row2 = connect(astuple(add(r0, TWO), 0), astuple(add(r0, TWO), lastc))
    banner = combine(row0, combine(row1, row2))
    O0 = fill(I, ZERO, banner)

    # Banner extremes by left-to-right order
    bannerCrop = crop(I, astuple(r0, 0), astuple(3, W))
    bparts = fgpartition(bannerCrop)
    bsorted = order(bparts, leftmost)
    cL = color(first(bsorted))
    cR = color(last(bsorted))

    # Template and spacing
    objs = objects(O0, T, F, T)
    templ = argmax(objs, size)
    samesize = sizefilter(objs, size(templ))
    topcand = argmin(samesize, uppermost)
    botcand = argmax(samesize, lowermost)
    H = height(templ)

    # Add extremes
    upmask = shift(toindices(topcand), invert(toivec(H)))
    downmask = shift(toindices(botcand), toivec(H))
    O1 = paint(O0, recolor(cL, upmask))
    O2 = paint(O1, recolor(cR, downmask))
    return O2
```
training d06dbe63 0.0 41.180339887498945 0.13609467455621316 0.09285436775832752 41.40928892981349
```python
def dsl2(I):
    s = first(totuple(ofcolor(I, EIGHT)))
    # direct offset-start method (no explicit shift): centers already biased toward the 8
    up_sing = shoot(add(s, UP), double(UP_RIGHT))                      # singles centers (rows: s+UP, s+UP+2*UR, ...)
    up_tri_c = shoot(add(add(s, UP), UP_RIGHT), double(UP_RIGHT))      # triple centers (rows between singles)
    dn_sing = shoot(add(s, DOWN), double(DOWN_LEFT))                   # singles centers
    dn_tri_c = shoot(add(add(s, DOWN), DOWN_LEFT), double(DOWN_LEFT))  # triple centers
    tri_up = combine(up_tri_c, combine(shift(up_tri_c, LEFT), shift(up_tri_c, RIGHT)))
    tri_dn = combine(dn_tri_c, combine(shift(dn_tri_c, LEFT), shift(dn_tri_c, RIGHT)))
    p = combine(combine(up_sing, dn_sing), combine(tri_up, tri_dn))
    p = intersection(p, asindices(I))
    O = underpaint(I, recolor(FIVE, p))
    return O
```
training f9012d9b 1.4142135623730951 25.928203230275507 14.5 0.1999999997171573 42.042416792365756
```python
def dsl5(I):
    # Sample-biased quadrant selection: prefer each quadrant's top-left sample if nonzero; otherwise use nonzero-mode. Collapse to tile mode on exactly one zero.
    h = height(I); w = width(I)
    rmid = divide(h, TWO); cmid = divide(w, TWO)
    TL = crop(I, astuple(ZERO, ZERO), astuple(rmid, cmid))
    TR = crop(I, astuple(ZERO, cmid), astuple(rmid, subtract(w, cmid)))
    BL = crop(I, astuple(rmid, ZERO), astuple(subtract(h, rmid), cmid))
    BR = crop(I, astuple(rmid, cmid), astuple(subtract(h, rmid), subtract(w, cmid)))
    f1000 = multiply(TEN, multiply(TEN, TEN))
    m = lambda G: branch(
        greater(size(remove(ZERO, palette(G))), ZERO),
        valmax(remove(ZERO, palette(G)), fork(add, compose(rbind(multiply, f1000), lbind(colorcount, G)), identity)),
        ZERO
    )
    sTL = index(TL, astuple(ZERO, ZERO))
    sTR = index(TR, astuple(ZERO, ZERO))
    sBL = index(BL, astuple(ZERO, ZERO))
    sBR = index(BR, astuple(ZERO, ZERO))
    a = branch(greater(sTL, ZERO), sTL, m(TL))
    b = branch(greater(sTR, ZERO), sTR, m(TR))
    c = branch(greater(sBL, ZERO), sBL, m(BL))
    d = branch(greater(sBR, ZERO), sBR, m(BR))
    tile = vconcat(hconcat(canvas(a, UNITY), canvas(b, UNITY)),
                   hconcat(canvas(c, UNITY), canvas(d, UNITY)))
    O = branch(equality(colorcount(I, ZERO), ONE), canvas(mostcolor(tile), UNITY), tile)
    return O
```
training 14754a24 0.0 43.6878505363304 0.16353548344545576 0.0 43.85138601977586
```python
def dsl4(I):
    # 5s that are strictly between two 4s along rows or columns (arbitrary gap)
    fives = ofcolor(I, FIVE)
    fours = ofcolor(I, FOUR)

    # Horizontal shadows from left and right 4s through contiguous 5s
    L1 = intersection(shift(fours, LEFT), fives)
    L2 = intersection(shift(L1, LEFT), fives)
    L3 = intersection(shift(L2, LEFT), fives)
    L4 = intersection(shift(L3, LEFT), fives)
    L5 = intersection(shift(L4, LEFT), fives)
    L6 = intersection(shift(L5, LEFT), fives)
    L7 = intersection(shift(L6, LEFT), fives)
    L8 = intersection(shift(L7, LEFT), fives)
    L9 = intersection(shift(L8, LEFT), fives)
    L10 = intersection(shift(L9, LEFT), fives)
    L11 = intersection(shift(L10, LEFT), fives)
    L12 = intersection(shift(L11, LEFT), fives)
    Lshadow = combine(combine(combine(L1, L2), combine(L3, L4)), combine(combine(combine(L5, L6), combine(L7, L8)), combine(combine(L9, L10), combine(L11, L12))))

    R1 = intersection(shift(fours, RIGHT), fives)
    R2 = intersection(shift(R1, RIGHT), fives)
    R3 = intersection(shift(R2, RIGHT), fives)
    R4 = intersection(shift(R3, RIGHT), fives)
    R5 = intersection(shift(R4, RIGHT), fives)
    R6 = intersection(shift(R5, RIGHT), fives)
    R7 = intersection(shift(R6, RIGHT), fives)
    R8 = intersection(shift(R7, RIGHT), fives)
    R9 = intersection(shift(R8, RIGHT), fives)
    R10 = intersection(shift(R9, RIGHT), fives)
    R11 = intersection(shift(R10, RIGHT), fives)
    R12 = intersection(shift(R11, RIGHT), fives)
    Rshadow = combine(combine(combine(R1, R2), combine(R3, R4)), combine(combine(combine(R5, R6), combine(R7, R8)), combine(combine(R9, R10), combine(R11, R12))))

    H_between = intersection(Lshadow, Rshadow)

    # Vertical shadows from up and down 4s through contiguous 5s
    U1 = intersection(shift(fours, UP), fives)
    U2 = intersection(shift(U1, UP), fives)
    U3 = intersection(shift(U2, UP), fives)
    U4 = intersection(shift(U3, UP), fives)
    U5 = intersection(shift(U4, UP), fives)
    U6 = intersection(shift(U5, UP), fives)
    U7 = intersection(shift(U6, UP), fives)
    U8 = intersection(shift(U7, UP), fives)
    U9 = intersection(shift(U8, UP), fives)
    U10 = intersection(shift(U9, UP), fives)
    U11 = intersection(shift(U10, UP), fives)
    U12 = intersection(shift(U11, UP), fives)
    Ushadow = combine(combine(combine(U1, U2), combine(U3, U4)), combine(combine(combine(U5, U6), combine(U7, U8)), combine(combine(U9, U10), combine(U11, U12))))

    D1 = intersection(shift(fours, DOWN), fives)
    D2 = intersection(shift(D1, DOWN), fives)
    D3 = intersection(shift(D2, DOWN), fives)
    D4 = intersection(shift(D3, DOWN), fives)
    D5 = intersection(shift(D4, DOWN), fives)
    D6 = intersection(shift(D5, DOWN), fives)
    D7 = intersection(shift(D6, DOWN), fives)
    D8 = intersection(shift(D7, DOWN), fives)
    D9 = intersection(shift(D8, DOWN), fives)
    D10 = intersection(shift(D9, DOWN), fives)
    D11 = intersection(shift(D10, DOWN), fives)
    D12 = intersection(shift(D11, DOWN), fives)
    Dshadow = combine(combine(combine(D1, D2), combine(D3, D4)), combine(combine(combine(D5, D6), combine(D7, D8)), combine(combine(D9, D10), combine(D11, D12))))

    V_between = intersection(Ushadow, Dshadow)

    targets = combine(H_between, V_between)
    O = paint(I, recolor(TWO, toobject(targets, I)))
    return O
```
training 88207623 0.0 45.16635916254486 0.1875 0.020761369959124646 45.37462053250398
```python
def dsl4(I):
    # per-half: align vmirrored 4s using centers of mass; paint with least frequent seed color per half
    h = height(I)
    th = divide(h, 2)
    T = tophalf(I)
    B = bottomhalf(I)

    # top half
    S2t = ofcolor(T, TWO)
    S2tm = ofcolor(vmirror(T), TWO)
    oj_t = subtract(centerofmass(S2t), centerofmass(S2tm))
    Mt = move(canvas(ZERO, shape(T)), recolor(ONE, ofcolor(vmirror(T), FOUR)), oj_t)
    St = ofcolor(Mt, ONE)
    ct = leastcolor(replace(replace(replace(T, ZERO, TEN), TWO, TEN), FOUR, TEN))

    # bottom half
    S2b = ofcolor(B, TWO)
    S2bm = ofcolor(vmirror(B), TWO)
    oj_b = subtract(centerofmass(S2b), centerofmass(S2bm))
    Mb = move(canvas(ZERO, shape(B)), recolor(ONE, ofcolor(vmirror(B), FOUR)), oj_b)
    Sb = ofcolor(Mb, ONE)
    cb = leastcolor(replace(replace(replace(B, ZERO, TEN), TWO, TEN), FOUR, TEN))

    G = underpaint(I, recolor(ct, St))
    O = underpaint(G, recolor(cb, shift(Sb, astuple(th, 0))))
    return O
```
training ad38a9d0 0.0 48.30584272273025 0.962962962962963 0.0 49.26880568569321
```python
def dsl2(I):
    parts = partition(I)
    six = colorfilter(parts, SIX)
    base = replace(I, SIX, SEVEN)
    s2 = sizefilter(six, TWO)
    h2 = mfilter(s2, hline)
    v2 = mfilter(s2, vline)
    s3 = sizefilter(six, THREE)
    h3 = mfilter(s3, hline)
    v3 = mfilter(s3, vline)
    line3 = combine(h3, v3)
    l3 = difference(s3, line3)
    s4 = sizefilter(six, FOUR)
    s5 = sizefilter(six, FIVE)
    s6 = sizefilter(six, SIX)
    o8h2 = mapply(lbind(recolor, EIGHT), h2)
    o9v2 = mapply(lbind(recolor, NINE), v2)
    o2line3 = mapply(lbind(recolor, TWO), line3)
    o4l3 = mapply(lbind(recolor, FOUR), l3)
    o8s4 = mapply(lbind(recolor, EIGHT), s4)
    o3s5 = mapply(lbind(recolor, THREE), s5)
    o5s6 = mapply(lbind(recolor, FIVE), s6)
    recol = combine(combine(combine(o8h2, o9v2), combine(o2line3, o4l3)), combine(o8s4, combine(o3s5, o5s6)))
    O = paint(base, recol)
    return O
```
training cb227835 0.0 50.1443299263566 0.4166858782243399 0.0 50.56101580458094
```python
def dsl1(I):
    objs = colorfilter(objects(I, T, F, T), EIGHT)
    t = totuple(objs)
    a = first(t)
    b = last(t)
    p = center(a)
    q = center(b)
    l = connect(add(p, LEFT), add(q, LEFT))
    r = connect(add(p, RIGHT), add(q, RIGHT))
    band = combine(l, r)
    O = underfill(I, THREE, band)
    return O
```
training 712bf12e 0.0 52.30701315044279 0.9750774866159482 0.0 53.282090637058744
```python
def dsl3(I):
    # From existing 2's, draw vertical rays up and down (entire columns through those 2's)
    x2 = ofcolor(I, TWO)
    t2 = toindices(x2)
    up = mapply(rbind(shoot, UP), t2)
    dn = mapply(rbind(shoot, DOWN), t2)
    col = combine(combine(up, dn), t2)
    xpaint = recolor(TWO, col)
    O = underpaint(I, xpaint)
    return O
```
training 93b4f4b3 0.0 53.422581302344256 1.1156108597285068 0.0 54.53819216207276
```python
def dsl2(I):
    H = height(I)
    W = width(I)
    half = divide(W, TWO)
    L = crop(I, astuple(ZERO, ZERO), astuple(H, half))
    R = crop(I, astuple(ZERO, half), astuple(H, half))
    c = mostcolor(L)
    O = canvas(c, astuple(H, half))
    K = trim(R)
    S = rot90(K)
    nz = difference(asindices(S), ofcolor(S, ZERO))
    obj = toobject(nz, S)
    hi = height(S)
    offi = divide(subtract(H, hi), TWO)
    O = paint(O, shift(obj, astuple(offi, ZERO)))
    return O
```
training ac0c5833 0.0 54.308119851415356 0.259029481903556 0.09370370369123283 54.66085303701015
```python
def dsl3(I):
    # Fill the single-cell gaps between pairs of FOURS separated by one cell (all 8 directions)
    x4 = ofcolor(I, FOUR)
    # Horizontal gaps
    hr = shift(x4, astuple(0, 1))
    hl = shift(x4, astuple(0, -1))
    hgap = intersection(hr, hl)
    # Vertical gaps
    hd = shift(x4, astuple(1, 0))
    hu = shift(x4, astuple(-1, 0))
    vgap = intersection(hd, hu)
    # Diagonal gaps (main)
    d1p = shift(x4, astuple(1, 1))
    d1m = shift(x4, astuple(-1, -1))
    dgap1 = intersection(d1p, d1m)
    # Diagonal gaps (counter)
    d2p = shift(x4, astuple(1, -1))
    d2m = shift(x4, astuple(-1, 1))
    dgap2 = intersection(d2p, d2m)
    p = combine(combine(hgap, vgap), combine(dgap1, dgap2))
    O = underfill(I, TWO, p)
    return O
```
training fe45cba4 0.0 57.42799324232979 0.86328125 0.0 58.29127449232979
```python
def dsl1(I):
    h = height(I)
    w = width(I)
    half = divide(w, TWO)
    rw = subtract(w, half)
    col0 = crop(I, ORIGIN, astuple(h, ONE))
    n9 = colorcount(col0, NINE)
    n2 = colorcount(col0, TWO)
    # build right half on its own canvas
    R = canvas(SEVEN, astuple(h, rw))
    topR = asindices(crop(R, ORIGIN, astuple(n9, rw)))
    botR = asindices(crop(R, astuple(subtract(h, n2), ZERO), astuple(n2, rw)))
    R1 = fill(R, NINE, topR)
    R2 = fill(R1, TWO, botR)
    # left half is all 7
    L = canvas(SEVEN, astuple(h, half))
    O = hconcat(L, R2)
    return O
```
training 6855a6e4 0.0 59.16162018939174 0.16000000000000003 0.0 59.32162018939174
```python
def dsl1(I):
    # Center all FIVE pixels inside the inner rectangle (of TWOs) both horizontally and vertically.
    x2 = ofcolor(I, TWO)
    o2 = toobject(x2, I)
    interior = delta(o2)
    iU = uppermost(interior)
    iL = leftmost(interior)
    HI = height(interior)
    WI = width(interior)
    x5 = ofcolor(I, FIVE)
    o5 = toobject(x5, I)
    h5 = height(o5)
    w5 = width(o5)
    offi = subtract(add(iU, divide(subtract(HI, h5), TWO)), uppermost(o5))
    offj = subtract(add(iL, divide(subtract(WI, w5), TWO)), leftmost(o5))
    shifted = shift(toindices(o5), astuple(offi, offj))
    inside = intersection(shifted, interior)
    base = cover(I, o5)
    O = paint(base, recolor(FIVE, inside))
    return O
```
training 7d1f7ee8 0.0 60.73978146324287 0.11856589742646706 0.0 60.85834736066934
```python
def dsl2(I):
    # Same rule as dsl1 but via sorted order (ascending perimeter), sequentially painted
    a = objects(I, T, F, T)
    isframe = fork(equality, toindices, box)
    frames = sfilter(a, isframe)
    perim = compose(size, toindices)
    ords = order(frames, perim)
    nz = difference(asindices(I), ofcolor(I, ZERO))
    inter_nz = lbind(intersection, nz)
    f = fork(recolor, color, compose(inter_nz, delta))
    mo1 = f(first(ords))
    mo2 = f(last(ords))
    O = paint(paint(I, mo1), mo2)
    return O
```
training 7447852a 0.0 61.183868141149674 1.1785185185185185 0.0 62.362386659668196
```python
def dsl4(I):
    # Diagonal centers between opposing diagonals of 2s, then expand to adjacent horizontals
    x = ofcolor(I, TWO)
    c1 = shift(x, add(UP, RIGHT))
    c2 = shift(x, add(DOWN, LEFT))
    centers = intersection(c1, c2)
    l = shift(centers, LEFT)
    r = shift(centers, RIGHT)
    idx = combine(centers, combine(l, r))
    O = underfill(I, FOUR, idx)
    return O
```
training 6ad5bdfd 0.0 65.30223141817427 0.563939393939394 0.3471332898573677 66.21330410197103
```python
def dsl3(I):
    # Gravitate per color-group (treat all cells of a color as one rigid object), except color 2
    g = I
    base = paint(canvas(ZERO, shape(g)), first(colorfilter(objects(g, T, F, T), TWO)))
    objs = objects(g, T, F, T)
    wall = first(colorfilter(objs, TWO))
    cols = remove(TWO, palette(g))
    def place_color(c):
        patch = ofcolor(g, c)
        objc = toobject(patch, g)
        shifted = shift(toindices(objc), gravitate(objc, wall))
        return recolor(c, shifted)
    moved = mapply(place_color, cols)
    O = paint(base, moved)
    return O
```
training 72322fa7 0.0 67.19943181359608 0.1845522898154477 0.056276865348038885 67.44026096875957
```python
def dsl4(I):
    O = I
    x8 = ofcolor(I, EIGHT)
    x4 = ofcolor(I, FOUR)
    x6 = ofcolor(I, SIX)
    x2 = ofcolor(I, TWO)
    x3 = ofcolor(I, THREE)
    x1 = ofcolor(I, ONE)

    # 4/8: horizontal completion only
    O = underpaint(O, recolor(FOUR, shift(x8, LEFT)))
    O = underpaint(O, recolor(FOUR, shift(x8, RIGHT)))
    mid4h = intersection(shift(x4, LEFT), shift(x4, RIGHT))
    O = underpaint(O, recolor(EIGHT, mid4h))

    # 8/center: fill centers in both orientations; prefer 6 over 2
    mid88h = intersection(shift(x8, LEFT), shift(x8, RIGHT))
    mid88v = intersection(shift(x8, UP), shift(x8, DOWN))
    has6 = greater(size(x6), ZERO)
    O = branch(has6, underpaint(O, recolor(SIX, mid88h)), O)
    O = branch(has6, underpaint(O, recolor(SIX, mid88v)), O)
    O = branch(flip(has6), underpaint(O, recolor(TWO, mid88h)), O)
    O = branch(flip(has6), underpaint(O, recolor(TWO, mid88v)), O)
    O = underpaint(O, recolor(EIGHT, shift(x6, LEFT)))
    O = underpaint(O, recolor(EIGHT, shift(x6, RIGHT)))
    O = underpaint(O, recolor(EIGHT, shift(x2, LEFT)))
    O = underpaint(O, recolor(EIGHT, shift(x2, RIGHT)))
    O = underpaint(O, recolor(EIGHT, shift(x6, UP)))
    O = underpaint(O, recolor(EIGHT, shift(x6, DOWN)))
    O = underpaint(O, recolor(EIGHT, shift(x2, UP)))
    O = underpaint(O, recolor(EIGHT, shift(x2, DOWN)))

    # 1/3: diagonals preferred; else vertical; no horizontal
    d1 = greater(size(intersection(shift(x3, NEG_UNITY), x1)), ZERO)
    d2 = greater(size(intersection(shift(x3, UP_RIGHT), x1)), ZERO)
    d3 = greater(size(intersection(shift(x3, DOWN_LEFT), x1)), ZERO)
    d4 = greater(size(intersection(shift(x3, UNITY), x1)), ZERO)
    haveDiag = either(either(d1, d2), either(d3, d4))
    haveV = either(greater(size(intersection(shift(x3, UP), x1)), ZERO),
                   greater(size(intersection(shift(x3, DOWN), x1)), ZERO))

    candD = O
    candD = underpaint(candD, recolor(ONE, shift(x3, NEG_UNITY)))
    candD = underpaint(candD, recolor(ONE, shift(x3, UP_RIGHT)))
    candD = underpaint(candD, recolor(ONE, shift(x3, DOWN_LEFT)))
    candD = underpaint(candD, recolor(ONE, shift(x3, UNITY)))
    candV = O
    candV = underpaint(candV, recolor(ONE, shift(x3, UP)))
    candV = underpaint(candV, recolor(ONE, shift(x3, DOWN)))

    O = branch(haveDiag, candD, branch(haveV, candV, O))
    return O
```
training db118e2a 0.0 69.23054168039394 0.6577777777777778 0.0 69.88831945817171
```python
def dsl5(I):
    objs = objects(I, T, F, T)
    ring = argmax(objs, size)
    c = color(ring)
    d = multiply(FIVE, THREE)
    base = canvas(SEVEN, astuple(d, d))
    t1 = connect(astuple(TWO, TWO), astuple(TWO, FOUR))
    t2 = connect(astuple(FOUR, TWO), astuple(FOUR, FOUR))
    t3 = connect(astuple(TWO, TWO), astuple(FOUR, TWO))
    t4 = connect(astuple(TWO, FOUR), astuple(FOUR, FOUR))
    tl = combine(combine(t1, t2), combine(t3, t4))
    o_tl = recolor(c, tl)
    b1 = connect(astuple(TEN, TEN), astuple(TEN, add(TEN, TWO)))
    b2 = connect(astuple(add(TEN, TWO), TEN), astuple(add(TEN, TWO), add(TEN, TWO)))
    b3 = connect(astuple(TEN, TEN), astuple(add(TEN, TWO), TEN))
    b4 = connect(astuple(TEN, add(TEN, TWO)), astuple(add(TEN, TWO), add(TEN, TWO)))
    br = combine(combine(b1, b2), combine(b3, b4))
    o_br = recolor(c, br)
    z = paint(base, o_tl)
    O = paint(z, o_br)
    return O
```
training e179c5f4 0.0 71.11815309265624 0.8833333333333333 0.0 72.00148642598957
```python
def dsl1(I):
    base = canvas(EIGHT, shape(I))
    start = first(ofcolor(I, ONE))
    dUL = astuple(NEG_ONE, NEG_ONE)
    p1 = shoot(start, UP_RIGHT)
    s2 = urcorner(p1)
    p2 = shoot(s2, dUL)
    s3 = ulcorner(p2)
    p3 = shoot(s3, UP_RIGHT)
    s4 = urcorner(p3)
    p4 = shoot(s4, dUL)
    s5 = ulcorner(p4)
    p5 = shoot(s5, UP_RIGHT)
    s6 = urcorner(p5)
    p6 = shoot(s6, dUL)
    s7 = ulcorner(p6)
    p7 = shoot(s7, UP_RIGHT)
    s8 = urcorner(p7)
    p8 = shoot(s8, dUL)
    s9 = ulcorner(p8)
    p9 = shoot(s9, UP_RIGHT)
    path = combine(p1, combine(p2, combine(p3, combine(p4, combine(p5, combine(p6, combine(p7, combine(p8, p9))))))))
    O = fill(base, ONE, path)
    return O
```
training f8c80d96 0.0 76.99861967150991 2.05 0.0 79.04861967150993
```python
def dsl2(I):
    ps = remove(ZERO, palette(I))
    seeds = mapply(lbind(ofcolor, I), ps)
    r = mapply(rbind(shoot, RIGHT), seeds)
    d = mapply(rbind(shoot, DOWN), seeds)
    lines = combine(r, d)
    c = maximum(ps)
    O = canvas(FIVE, shape(I))
    O = fill(O, c, lines)
    return O
```
training 5ffb2104 0.0 77.77432592263492 1.2106837606837608 0.6150657608390382 79.60007544415771
```python
def dsl1(I):
    O = vmirror(I)
    return O
```
training d6ad076f 0.0 83.0858185033641 0.38 0.0 83.46581850336409
```python
def dsl1(I):
    # Decide orientation by row/column overlap, then bridge with 1-cell margin on the overlap axis.
    obs = objects(I, T, F, T)
    a = argmin(obs, leftmost)
    b = other(obs, a)
    side = both(hmatching(a, b), flip(vmatching(a, b)))  # side-by-side if rows overlap but columns don't
    if side:
        lefto = a
        righto = b
        topov = branch(greater(uppermost(lefto), uppermost(righto)), uppermost(lefto), uppermost(righto))
        botov = branch(greater(lowermost(lefto), lowermost(righto)), lowermost(righto), lowermost(lefto))
        i0 = increment(topov)
        i1 = decrement(botov)
        j0 = increment(rightmost(lefto))
        j1 = decrement(leftmost(righto))
    else:
        topo = argmin(obs, uppermost)
        boto = other(obs, topo)
        leftov = branch(greater(leftmost(topo), leftmost(boto)), leftmost(topo), leftmost(boto))
        rightov = branch(greater(rightmost(topo), rightmost(boto)), rightmost(boto), rightmost(topo))
        j0 = increment(leftov)
        j1 = decrement(rightov)
        i0 = increment(lowermost(topo))
        i1 = decrement(uppermost(boto))
    rect = backdrop(connect(astuple(i0, j0), astuple(i1, j1)))
    O = underfill(I, EIGHT, rect)
    return O
```
training 292dd178 0.0 86.2550579846942 0.9363636363636364 0.0 87.19142162105784
```python
def dsl2(I):
    # Interior fill + directed spills from rows/cols that contain exactly one 1 (per object via edge-unions)
    objs = colorfilter(fgpartition(I), ONE)
    U = merge(objs)
    S = toindices(U)

    # Interior (per object)
    interior = merge(apply(delta, objs))

    # Row-singletons (compute across all 1s, then direct by object edge unions)
    row_sets = apply(compose(rbind(intersection, S), hfrontier), S)
    row_single_cells = merge(sizefilter(row_sets, ONE))  # indices of rows having exactly one 1

    # Union of all objects' left and right edge columns
    Lcols = merge(apply(vfrontier, apply(ulcorner, objs)))
    Rcols = merge(apply(vfrontier, apply(urcorner, objs)))

    row_leftedge_cells = intersection(row_single_cells, Lcols)
    row_rightedge_cells = intersection(row_single_cells, Rcols)

    spill_right = merge(apply(rbind(shoot, RIGHT), row_leftedge_cells))
    spill_left  = merge(apply(rbind(shoot, LEFT),  row_rightedge_cells))

    # Column-singletons (compute across all 1s, then direct by object top/bottom edge rows)
    col_sets = apply(compose(rbind(intersection, S), vfrontier), S)
    col_single_cells = merge(sizefilter(col_sets, ONE))  # indices of cols having exactly one 1

    TopRows = merge(apply(hfrontier, apply(ulcorner, objs)))
    BotRows = merge(apply(hfrontier, apply(llcorner, objs)))

    col_top_cells = intersection(col_single_cells, TopRows)
    col_bot_cells = intersection(col_single_cells, BotRows)

    spill_up   = merge(apply(rbind(shoot, UP),   col_top_cells))
    spill_down = merge(apply(rbind(shoot, DOWN), col_bot_cells))

    P = combine(interior, combine(spill_left, combine(spill_right, combine(spill_up, spill_down))))
    O = underfill(I, TWO, P)
    return O
```
training 50f325b5 0.0 88.75512461566507 0.24824187250657836 0.0 89.00336648817164
```python
def dsl3(I):
    # Recolor 3s that have zeros above and below (vertical sandwich)
    three = ofcolor(I, THREE)
    z = ofcolor(I, ZERO)
    up_zero = shift(z, DOWN)   # cells with a zero above
    down_zero = shift(z, UP)   # cells with a zero below
    to_change = intersection(three, intersection(up_zero, down_zero))
    O = fill(I, EIGHT, to_change)
    return O
```
training d753a70b 0.0 89.08566784493138 0.73828125 0.0 89.82394909493138
```python
def dsl4(I):
    O = cmirror(I)
    return O
```
training 20fb2937 0.0 89.47722544760302 1.8671328671328673 0.0 91.34435831473587
```python
def dsl1(I):
    bg = mostcolor(I)
    # extract the three 3x3 header blocks left-to-right
    sqs = sizefilter(objects(I, True, False, True), 9)
    seq = order(sqs, leftmost)
    A = first(seq)
    rest1 = remove(A, seq)
    B = first(rest1)
    rest2 = remove(B, rest1)
    C = first(rest2)
    Ag = subgrid(A, I)
    Bg = subgrid(B, I)
    Cg = subgrid(C, I)
    # 1-col separators to keep width 11
    sepcol = canvas(bg, astuple(3, 1))
    rowBAC = hconcat(Bg, hconcat(sepcol, hconcat(Ag, hconcat(sepcol, Cg))))
    rowCBA = hconcat(Cg, hconcat(sepcol, hconcat(Bg, hconcat(sepcol, Ag))))
    rowACB = hconcat(Ag, hconcat(sepcol, hconcat(Cg, hconcat(sepcol, Bg))))
    seprow = canvas(bg, astuple(1, width(rowBAC)))
    big = vconcat(rowBAC, vconcat(seprow, vconcat(rowCBA, vconcat(seprow, vconcat(rowACB, vconcat(seprow, rowBAC))))))
    O = crop(big, ORIGIN, astuple(13, width(big)))
    return O
```
training 4ff4c9da 0.0 92.77519037188927 0.12573095099965526 0.0 92.90092132288893
```python
def dsl4(I):
    # Use full bounding box outline (box) of the largest 8-object as the matching context
    O = I
    domain = asindices(I)
    comps = objects(I, True, False, True)
    eights = colorfilter(comps, EIGHT)
    if size(eights) == 0:
        return O
    seed = argmax(eights, size)
    outline = box(seed)
    if size(outline) == 0:
        return O
    ctx = normalize(toobject(outline, I))
    occs = occurrences(I, ctx)
    pat = toindices(normalize(seed))
    mask = difference(domain, domain)
    for p in totuple(occs):
        mask = combine(mask, shift(pat, p))
    O = fill(O, EIGHT, mask)
    return O
```
training d6542281 0.0 93.25657626829349 0.40906017689356233 0.0 93.66563644518703
```python
def dsl3(I):
    # Fill the bounding rectangle of all 3-cells with 3 (if any 3s exist)
    idx3 = ofcolor(I, THREE)
    rect = backdrop(idx3)
    O = underfill(I, THREE, rect)
    return O
```
training 891232d6 0.0 95.12210720000817 0.5527444347019079 0.06763735376182832 95.7424889884719
```python
def dsl4(I):
    sev = colorfilter(objects(I, T, F, T), SEVEN)
    boxes = apply(box, sev)
    uls = apply(ulcorner, boxes)
    urs = apply(urcorner, boxes)
    cents = apply(center, sev)
    obj4 = recolor(FOUR, merge(apply(initset, uls)))
    obj3 = recolor(THREE, merge(apply(initset, urs)))
    obj8 = recolor(EIGHT, merge(apply(initset, cents)))
    parts = merge(combine(initset(obj4), combine(initset(obj3), initset(obj8))))
    O = underpaint(I, parts)
    return O
```
training db93a21d 0.0 96.81686514811322 1.8591666666666666 0.21609297527318183 98.89212479005306
```python
def dsl4(I):
    # For each 9-rectangle: 3 on the one-pixel ring just outside it, 1 on the next outside ring
    obs = colorfilter(objects(I, T, F, T), NINE)
    ring1_list = apply(compose(outbox, backdrop), obs)
    ring2_list = apply(outbox, ring1_list)
    threes = recolor(THREE, merge(ring1_list))
    ones = recolor(ONE, merge(ring2_list))
    O = underpaint(I, combine(threes, ones))
    return O
```
training fc4aaf52 0.0 101.96006943264422 0.56640625 0.0 102.52647568264422
```python
def dsl1(I):
    # Swap the two foreground colors; place full swapped subgrid to the right and below the original
    fg = difference(asindices(I), ofcolor(I, EIGHT))
    S = subgrid(fg, I)
    cols = remove(EIGHT, palette(S))
    a = minimum(cols)
    b = maximum(cols)
    S2 = switch(S, a, b)
    idx = difference(asindices(S2), ofcolor(S2, EIGHT))
    obj = toobject(idx, S2)
    h = height(S)
    w = width(S)
    ul = ulcorner(fg)
    O = canvas(EIGHT, shape(I))
    O = paint(O, shift(obj, add(ul, tojvec(w))))   # to the right
    O = paint(O, shift(obj, add(ul, toivec(h))))   # below
    return O
```
training 264363fd 0.0 103.37436847118542 0.6088888888888888 0.0 103.9832573600743
```python
def dsl2(I):
    # Draw plus only through non-background (mostcolor is background), recolor to 3
    bg = mostcolor(I)
    seeds4 = ofcolor(I, FOUR)
    H = merge(apply(hfrontier, seeds4))
    V = merge(apply(vfrontier, seeds4))
    L = combine(H, V)
    nb = difference(asindices(I), ofcolor(I, bg))
    draw = intersection(L, nb)
    O = fill(I, THREE, draw)
    O = fill(O, FOUR, seeds4)
    return O
```
training d22278a0 0.0 104.94037436578125 1.1342179593730983 0.035355339046827375 106.1099476642012
```python
def dsl3(I):
    # Nearest-corner assignment with vertical stripe gating by corner's column parity
    h = height(I)
    w = width(I)
    O = canvas(ZERO, shape(I))
    # collect present corners
    cs = []
    corners = [(0, 0), (0, subtract(w, ONE)), (subtract(h, ONE), 0), (subtract(h, ONE), subtract(w, ONE))]
    for (r, c) in corners:
        col = index(I, astuple(r, c))
        if positive(col):
            cs.append((r, c, col))
    if not cs:
        return O
    # fill by nearest corner (Manhattan), break ties to background, then keep only columns matching corner col-parity
    grid = [list(row) for row in O]
    for i in range(h):
        for j in range(w):
            best = None
            bestd = None
            tie = False
            for (cr, cc, col) in cs:
                d = abs(i - cr) + abs(j - cc)
                if (bestd is None) or (d < bestd):
                    bestd = d
                    best = (cr, cc, col)
                    tie = False
                elif d == bestd:
                    tie = True
            if not tie and best is not None:
                cr, cc, col = best
                if (j % 2) == (cc % 2):
                    grid[i][j] = col
    return tuple(tuple(row) for row in grid)
```
training df8cc377 0.0 108.08184619650477 0.4020052532009054 0.4400779399345128 108.9239293896402
```python
def dsl5(I):
    # Fill interiors of all rings with the color of the singleton closest (by Manhattan) to the union of rings
    objs = objects(I, T, F, T)
    cond_ring = fork(equality, toindices, box)
    rings = sfilter(objs, cond_ring)
    interiors = mapply(delta, rings)
    singles = sizefilter(objs, ONE)
    ru = merge(rings)
    closest_single = argmin(singles, lbind(manhattan, ru))
    cfill = color(closest_single)
    O = fill(I, cfill, interiors)
    return O
```
training f9d67f8b 0.0 111.05217042823207 0.28555555555555556 0.0 111.33772598378764
```python
def dsl4(I):
    # Two-step fill: first from rot90, then from rot270 for any remaining 9s
    m = ofcolor(I, NINE)
    base = cover(I, m)
    J1 = rot90(I)
    obj1 = toobject(m, J1)
    O1 = underpaint(base, obj1)
    m2 = ofcolor(O1, NINE)
    base2 = cover(O1, m2)
    J2 = rot270(I)
    obj2 = toobject(m2, J2)
    O = underpaint(base2, obj2)
    return O
```
training 305b1341 0.0 113.79088032266583 0.3075000000000001 0.035355339053077375 114.13373566171892
```python
def dsl1(I):
    # Hypothesis A: Use a one-cell expanded bounding box per stripe color (via backdrop(outbox(P))),
    # fill bases first, then repaint the dot lattice at the original seed positions.
    H = height(I); W = width(I)
    OFF = tojvec(2)
    J = crop(I, astuple(0, 2), astuple(H, subtract(W, 2)))
    # Legend pairs (stripe, base)
    s1 = index(I, ORIGIN);       b1 = index(I, tojvec(1))
    s2 = index(I, toivec(1));    b2 = index(I, add(toivec(1), tojvec(1)))
    s3 = index(I, toivec(2));    b3 = index(I, add(toivec(2), tojvec(1)))
    O = canvas(ZERO, shape(I))
    # Prepare patches
    P1 = ofcolor(J, s1); R1 = shift(backdrop(outbox(P1)), OFF)
    P2 = ofcolor(J, s2); R2 = shift(backdrop(outbox(P2)), OFF)
    P3 = ofcolor(J, s3); R3 = shift(backdrop(outbox(P3)), OFF)
    # Fill all bases first
    O = branch(both(positive(s1), positive(b1)), fill(O, b1, R1), O)
    O = branch(both(positive(s2), positive(b2)), fill(O, b2, R2), O)
    O = branch(both(positive(s3), positive(b3)), fill(O, b3, R3), O)
    # Repaint dot-lattice stripes
    O = branch(positive(s1), paint(O, recolor(s1, shift(P1, OFF))), O)
    O = branch(positive(s2), paint(O, recolor(s2, shift(P2, OFF))), O)
    O = branch(positive(s3), paint(O, recolor(s3, shift(P3, OFF))), O)
    return O
```
training 9c1e755f 0.0 113.08294629982846 1.1400000000000001 0.0 114.22294629982846
```python
def dsl1(I):
    # Dual completion: horizontal extrusion from a header row + vertical tiling from a bottom sample row
    objs = objects(I, T, F, T)

    # Horizontal extrusion across the widest horizontal nonzero band
    hls = sfilter(objs, hline)
    baseh = argmax(hls, width)
    uh = ulcorner(baseh)
    row_mask = difference(hfrontier(uh), ofcolor(I, ZERO))
    anchors_h = difference(vfrontier(uh), ofcolor(I, ZERO))
    sh_row = lbind(shift, row_mask)
    g_row = rbind(subtract, uh)
    mask_fn = compose(sh_row, g_row)
    vals = lbind(index, I)
    recol_fn = fork(recolor, vals, mask_fn)
    paints_h = mapply(recol_fn, anchors_h)

    # Vertical tiling using the bottommost row that intersects the leftmost tall vertical bar
    vls = sfilter(objs, vline)
    tall = sfilter(vls, compose(rbind(greater, ONE), height))
    basev = argmin(tall, leftmost)
    uv = ulcorner(basev)
    anchors_v = difference(vfrontier(uv), ofcolor(I, ZERO))
    ordered_v = order(anchors_v, first)
    sample_cross = last(ordered_v)
    sample_row_inds = difference(hfrontier(sample_cross), ofcolor(I, ZERO))
    sample_obj = toobject(sample_row_inds, I)
    sh_sample = lbind(shift, sample_obj)
    g_sample = rbind(subtract, sample_cross)
    place_sample = compose(sh_sample, g_sample)
    paints_v = mapply(place_sample, anchors_v)

    paints = combine(paints_h, paints_v)
    O = underpaint(I, paints)
    return O
```
training 4acc7107 0.0 114.43852762570089 1.1800000000000002 0.3560660170520938 115.97459364275298
```python
def dsl2(I):
    h = height(I)
    w = width(I)
    mid = halve(w)
    objs = fgpartition(I)
    allfg = merge(objs)
    cols = palette(allfg)
    c1 = first(cols)
    c2 = other(cols, c1)
    oc1 = merge(colorfilter(objs, c1))
    oc2 = merge(colorfilter(objs, c2))
    l1 = leftmost(oc1)
    l2 = leftmost(oc2)
    left_is_oc1 = greater(l2, l1)
    ocL = branch(left_is_oc1, oc1, oc2)
    ocR = branch(left_is_oc1, oc2, oc1)
    sL = subgrid(ocL, I)
    sR = subgrid(ocR, I)
    ul = uppermost(ocL)
    ur = uppermost(ocR)
    ll = leftmost(ocL)
    lr = leftmost(ocR)
    hl = height(sL)
    hr = height(sR)
    blank = canvas(ZERO, astuple(h, w))
    offrowL = subtract(subtract(h, hl), ul)
    offcolL = subtract(ZERO, ll)
    G1 = move(blank, ocL, astuple(offrowL, offcolL))
    offrowR = subtract(subtract(h, hr), ur)
    offcolR = subtract(mid, lr)
    O = move(G1, ocR, astuple(offrowR, offcolR))
    return O
```
training e760a62e 0.0 118.33819996954456 0.7683750752244758 0.0 119.10657504476904
```python
def dsl2(I):
    # Fine-grid: fill full columns for 2 and full rows for 3; intersections -> 6; restore 8s.
    eight_idx = ofcolor(I, EIGHT)
    non8 = difference(asindices(I), eight_idx)
    rows3 = mapply(hfrontier, ofcolor(I, THREE))
    cols2 = mapply(vfrontier, ofcolor(I, TWO))
    base = canvas(ZERO, shape(I))
    g = fill(base, TWO, intersection(cols2, non8))
    g = fill(g, THREE, intersection(rows3, non8))
    inter = intersection(rows3, cols2)
    g = fill(g, SIX, intersection(inter, non8))
    O = fill(g, EIGHT, eight_idx)
    return O
```
training 2546ccf6 0.0 127.09827366379926 0.5381681628821218 0.0 127.63644182668139
```python
def dsl5(I):
    # Rotate non-border content by 180 degrees and underpaint
    c = mostcolor(I)
    J = replace(I, c, ZERO)
    R = rot180(J)
    O = underpaint(I, asobject(R))
    return O
```
training db615bd4 0.0 131.45910234503276 0.40800000000000003 0.0 131.86710234503275
```python
def dsl4(I):
    # Hypothesis: emphasize the frame/outline around the 4-region
    O = I
    p = backdrop(ofcolor(I, FOUR))
    border = box(p)
    O = fill(O, FOUR, border)
    return O
```
training dc2e9a9d 0.0 136.27883810815806 0.3123193941608263 0.15695890244619315 136.74811640476509
```python
def dsl2(I):
    # Only ring-like gray objects (equal to their outline) duplicate:
    # - 1-copy horizontally to the right by width+1
    # - 8-copy vertically downward by height+1
    objs = colorfilter(objects(I, True, False, True), THREE)
    def is_ring(o):
        return equality(size(toindices(o)), size(box(o)))
    rings = sfilter(objs, is_ring)
    def hcopy(o):
        off = tojvec(add(width(o), ONE))
        return recolor(ONE, toobject(shift(toindices(o), off), I))
    def vcopy(o):
        off = toivec(add(height(o), ONE))
        return recolor(EIGHT, toobject(shift(toindices(o), off), I))
    ones = merge(apply(hcopy, rings))
    eights = merge(apply(vcopy, rings))
    O = underpaint(I, ones)
    O = underpaint(O, eights)
    return O
```
training 7837ac64 4.242640687119286 56.06785706919441 76.0 4.142857142712836 140.45335489902652
```python
def dsl1(I):
    x1 = replace(I, mostcolor(I), ZERO)
    O = downscale(x1, NINE)
    return O
```
training 278e5215 0.0 153.72334442342603 3.7714285714285714 2.3276927680733883 159.82246576292798
```python
def dsl1(I):
    # Robust: find bbox of 'on' object (color FIVE), extract 3-row palette by trimming the covered grid,
    # pick the duplicated non-uniform row as foreground and the uniform row as background.
    p5 = ofcolor(I, FIVE)
    s5 = subgrid(p5, I)
    H = height(s5)
    W = width(s5)
    base = cover(I, toobject(p5, I))
    pal = trim(base)
    r0 = crop(pal, ORIGIN, astuple(ONE, W))
    r1 = crop(pal, astuple(ONE, ZERO), astuple(ONE, W))
    r2 = crop(pal, astuple(TWO, ZERO), astuple(ONE, W))
    v0 = index(r0, ORIGIN)
    v1 = index(r1, ORIGIN)
    v2 = index(r2, ORIGIN)
    u0 = equality(r0, canvas(v0, astuple(ONE, W)))
    u1 = equality(r1, canvas(v1, astuple(ONE, W)))
    u2 = equality(r2, canvas(v2, astuple(ONE, W)))
    e01 = equality(r0, r1)
    e02 = equality(r0, r2)
    e12 = equality(r1, r2)
    # Foreground pattern row = duplicated non-uniform row (fallback: first non-uniform)
    prow = branch(e01, r0, branch(e02, r0, branch(e12, r1, branch(flip(u0), r0, branch(flip(u1), r1, r2)))))
    # Background row = the uniform row (fallback: r2)
    brow = branch(u0, r0, branch(u1, r1, branch(u2, r2, r2)))
    Agrid = vupscale(prow, H)
    Bgrid = vupscale(brow, H)
    onmask = ofcolor(s5, FIVE)
    O = paint(Bgrid, toobject(onmask, Agrid))
    return O
```
training b7955b3c 0.0 213.816202812844 2.0115911865911866 0.0 215.8277939994352
```python
def dsl1(I):
    # Replace 8 with the most common color within each quadrant (2x2 split)
    hs = hsplit(I, TWO)
    top = first(hs)
    bottom = last(hs)

    vs_top = vsplit(top, TWO)
    tl = first(vs_top)
    tr = last(vs_top)

    vs_bot = vsplit(bottom, TWO)
    bl = first(vs_bot)
    br = last(vs_bot)

    tl2 = replace(tl, EIGHT, mostcolor(tl))
    tr2 = replace(tr, EIGHT, mostcolor(tr))
    top2 = hconcat(tl2, tr2)

    bl2 = replace(bl, EIGHT, mostcolor(bl))
    br2 = replace(br, EIGHT, mostcolor(br))
    bottom2 = hconcat(bl2, br2)

    O = vconcat(top2, bottom2)
    return O
```
training 39e1d7f9 0.0 235.2783993232523 1.007897711425258 0.0 236.28629703467757
```python
def dsl4(I):
    O = rot180(I)
    return O
```
training 5c2c9af4 0.0 240.41807998482153 1.463702210562864 0.08959392049839388 241.9713761158828
```python
def dsl2(I):
    # Diagonal stripe lattice from seeds, offset by multiples of period
    c = leastcolor(I)
    S = ofcolor(I, c)
    Obj = toobject(S, I)
    pv = vperiod(Obj)
    ph = hperiod(Obj)
    p = branch(positive(pv), pv, ph)
    p = branch(positive(p), p, ONE)
    off1 = astuple(p, invert(p))
    off2 = astuple(invert(p), p)
    off3 = astuple(double(p), invert(double(p)))
    off4 = astuple(invert(double(p)), double(p))
    E = S
    E = combine(E, shift(S, off1))
    E = combine(E, shift(S, off2))
    E = combine(E, shift(S, off3))
    E = combine(E, shift(S, off4))
    UL = add(UP, LEFT)
    UR = UP_RIGHT
    DL = DOWN_LEFT
    DR = add(DOWN, RIGHT)
    D = initset(UR)
    D = insert(DL, D)
    D = insert(UL, D)
    D = insert(DR, D)
    R = prapply(shoot, E, D)
    P = merge(R)
    Z = canvas(ZERO, shape(I))
    O = fill(Z, c, P)
    return O
```
training 34cfa167 0.0 265.31288486354913 2.391484889379626 0.11320902606375158 267.81757877899247
```python
def dsl4(I):
    # Replace bg by 4 and overlay six symmetries (original + H + V + 180 + both diagonals)
    bg = mostcolor(I)
    O = replace(I, bg, FOUR)
    Gs = (I, hmirror(I), vmirror(I), rot180(I), dmirror(I), cmirror(I))
    # inline expansion without loops
    g = Gs[0]
    P = difference(asindices(g), ofcolor(g, ZERO))
    Obj = toobject(P, g)
    O = paint(O, Obj)
    g = Gs[1]
    P = difference(asindices(g), ofcolor(g, ZERO))
    Obj = toobject(P, g)
    O = paint(O, Obj)
    g = Gs[2]
    P = difference(asindices(g), ofcolor(g, ZERO))
    Obj = toobject(P, g)
    O = paint(O, Obj)
    g = Gs[3]
    P = difference(asindices(g), ofcolor(g, ZERO))
    Obj = toobject(P, g)
    O = paint(O, Obj)
    g = Gs[4]
    P = difference(asindices(g), ofcolor(g, ZERO))
    Obj = toobject(P, g)
    O = paint(O, Obj)
    g = Gs[5]
    P = difference(asindices(g), ofcolor(g, ZERO))
    Obj = toobject(P, g)
    O = paint(O, Obj)
    return O
```
training 4290ef0e 5.656854249492381 122.28293356355219 172.51256535672118 0.2222222221349251 300.6745753919007
```python
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
```
training 9b5080bb 0.0 305.3005361569587 0.9731852227849217 0.0 306.27372137974356
```python
def dsl2(I):
    # For each object's bbox: where it's TWO, paint bbox-on-8 as ONE; where it's FOUR, paint bbox-on-8 as TWO
    # Also turn original background 1-cells into 8 (but keep newly created 1s intact)
    x8 = ofcolor(I, EIGHT)
    x2 = toobject(ofcolor(I, TWO), I)
    x4 = toobject(ofcolor(I, FOUR), I)
    b2 = box(x2)
    b4 = box(x4)
    m21 = intersection(b2, x8)
    m42 = intersection(b4, x8)
    y1 = fill(I, ONE, m21)
    y2 = fill(y1, TWO, m42)
    bg1 = ofcolor(I, ONE)
    O = fill(y2, EIGHT, bg1)
    return O
```
training 8731374e 9.255832815336873 186.0 458.0 0.4446960452528722 653.7005288605898
```python
def dsl2(I):
    # Extract frontiers, binarize to least/most color, then downscale by 3
    bg = mostcolor(I)
    fg = leastcolor(I)
    sh = shape(I)
    C = canvas(bg, sh)
    Fs = frontiers(I)
    idx = mapply(toindices, Fs)
    G = fill(C, fg, idx)
    O = downscale(G, THREE)
    return O
```
training ce8d95cc 34.555740781599376 118.0 711.0 1.4031890419815098 864.9589298235809
```python
def dsl2(I):
    x1 = hmirror(I)
    x2 = compress(x1)
    O = hmirror(x2)
    return O
```
training a644e277 37.75439630694861 645.0 232.0 2.3062399865113656 917.06063629346
```python
def dsl3(I):
    # Two tiles vertically, one horizontally; include left border by shifting left.
    bg = mostcolor(I)
    mk = leastcolor(I)
    sep = first(remove(mk, remove(bg, palette(I))))
    obj = toobject(ofcolor(I, sep), I)
    hp = hperiod(obj)
    vp = vperiod(obj)
    start = subtract(ulcorner(obj), tojvec(ONE))  # shift left to include border
    hdim = add(ONE, multiply(vp, TWO))            # two vertical tiles + borders
    wdim = add(ONE, hp)                            # one horizontal tile + borders
    O = crop(I, start, astuple(hdim, wdim))
    return O
```
training 97a05b5b 16.338984404224732 302.0 692.0 0.6151470785154105 1010.9541314827402
```python
def dsl4(I):
    non2 = difference(asindices(I), ofcolor(I, TWO))
    region = subgrid(non2, I)
    rr = replace(region, ZERO, TWO)
    O = downscale(rr, 2)
    return O
```
training a416fc5b 7.0710678118654755 1042.2469533506767 377.3636363636363 0.18518518513668678 1426.8668427113153
```python
def dsl2(I):
    # Orthogonal propagation from TWO-shape: left as 8, down as 5 (only onto background)
    P2 = ofcolor(I, TWO)
    L = astuple(ZERO, subtract(ZERO, FOUR))
    D = astuple(FOUR, ZERO)
    SL = shift(P2, L)
    SD = shift(P2, D)
    O1 = underfill(I, EIGHT, SL)
    O = underfill(O1, FIVE, SD)
    return O
```
training 2037f2c7 73.30493457992179 336.0 1353.0 3.5127585671038015 1765.8176931470257
```python
def dsl5(I):
    # Keep only horizontal frontiers inside the fundamental tile
    nz_idx = difference(asindices(I), ofcolor(I, ZERO))
    nz_obj = toobject(nz_idx, I)
    hp = hperiod(nz_obj)
    vp = vperiod(nz_obj)
    start = ulcorner(nz_obj)
    tile = crop(I, start, astuple(vp, hp))
    frs = frontiers(tile)
    hfrs = sfilter(frs, hline)
    hfobj = merge(hfrs)
    hfidx = toindices(hfobj)
    base = canvas(ZERO, shape(tile))
    O = fill(base, EIGHT, hfidx)
    return O
```
training 7bb29440 51.15815417986803 913.0 953.0 1.8953935444938896 1919.0535477243618
```python
def dsl5(I):
    # Pick the largest unified nonzero connected tile (by area)
    R = trim(I)
    J = replace(replace(R, FOUR, ONE), SIX, ONE)
    comps = objects(J, T, F, T)
    best = argmax(comps, lambda o: size(toindices(o)))
    Rb = subgrid(best, R)
    O = replace(Rb, ZERO, ONE)
    return O
```
training 6cbe9eb8 36.4766672300848 1388.0 1619.0 0.9166151159215742 3044.3932823460063
```python
def dsl5(I):
    # union of non-bordering univalued objects after zeroing 1 and 2; crop; frame by dominant of {3,8}
    t1 = replace(I, ONE, ZERO)
    t2 = replace(t1, TWO, ZERO)
    objs = objects(t2, True, False, True)
    nb = sfilter(objs, compose(flip, rbind(bordering, t2)))
    idxs = apply(toindices, nb)
    uni = merge(idxs)
    core = subgrid(uni, t2)
    innerobj = toobject(normalize(uni), core)
    dims = add(shape(core), TWO_BY_TWO)
    base = canvas(ZERO, dims)
    G = paint(base, shift(innerobj, UNITY))
    c3 = colorcount(I, THREE)
    c8 = colorcount(I, EIGHT)
    C = branch(greater(c8, c3), EIGHT, THREE)
    O = fill(G, C, box(asindices(G)))
    return O
```
