```python
def dsl1(I):
    bg = mostcolor(I)
    objs = fgpartition(I)
    # size from max extent
    hmax = valmax(objs, height)
    wmax = valmax(objs, width)
    n = maximum(combine(initset(hmax), initset(wmax)))
    l = subtract(n, ONE)
    l1 = subtract(l, ONE)
    m = divide(n, TWO)
    # patches: corners, side midpoints, near-corner edge cells
    cpatch = insert(astuple(ZERO, ZERO), insert(astuple(ZERO, l), insert(astuple(l, ZERO), initset(astuple(l, l)))))
    ppatch = insert(astuple(ZERO, m), insert(astuple(m, ZERO), insert(astuple(m, l), initset(astuple(l, m)))))
    tpatch = insert(astuple(ZERO, ONE), insert(astuple(ZERO, l1), insert(astuple(l, ONE), initset(astuple(l, l1)))))
    lpatch = insert(astuple(ONE, ZERO), insert(astuple(l1, ZERO), insert(astuple(ONE, l), initset(astuple(l1, l)))))
    # choose colors
    intersz = compose(size, fork(intersection, toindices, corners))
    oc = argmax(objs, intersz)  # object most likely rectangular corners -> corners color
    op = argmin(objs, intersz)  # object least cornered -> plus color
    # edge colors from borders
    top = crop(I, astuple(ZERO, ZERO), astuple(ONE, width(I)))
    left = crop(I, astuple(ZERO, ZERO), astuple(height(I), ONE))
    ctop = leastcolor(top)
    cleft = leastcolor(left)
    # paint
    O = canvas(bg, astuple(n, n))
    O1 = branch(greater(n, THREE), paint(O, recolor(ctop, tpatch)), O)
    O2 = branch(greater(n, THREE), paint(O1, recolor(cleft, lpatch)), O1)
    O3 = paint(O2, recolor(color(oc), cpatch))
    O4 = paint(O3, recolor(color(op), ppatch))
    return O4

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

def dsl3(I):
    bg = mostcolor(I)
    objs = fgpartition(I)
    # size
    n = maximum(combine(initset(valmax(objs, height)), initset(valmax(objs, width))))
    l = subtract(n, ONE)
    l1 = subtract(l, ONE)
    m = divide(n, TWO)
    # patches
    cpatch = insert(astuple(ZERO, ZERO), insert(astuple(ZERO, l), insert(astuple(l, ZERO), initset(astuple(l, l)))))
    ppatch = insert(astuple(ZERO, m), insert(astuple(m, ZERO), insert(astuple(m, l), initset(astuple(l, m)))))
    tpatch = insert(astuple(ZERO, ONE), insert(astuple(ZERO, l1), insert(astuple(l, ONE), initset(astuple(l, l1)))))
    lpatch = insert(astuple(ONE, ZERO), insert(astuple(l1, ZERO), insert(astuple(ONE, l), initset(astuple(l1, l)))))
    # colors by corner-intersection heuristic
    intersz = compose(size, fork(intersection, toindices, corners))
    oc = argmax(objs, intersz)
    op = argmin(objs, intersz)
    # edge colors from opposite borders (bottom and right)
    br = subtract(height(I), ONE)
    bc = subtract(width(I), ONE)
    bottom = crop(I, astuple(br, ZERO), astuple(ONE, width(I)))
    right = crop(I, astuple(ZERO, bc), astuple(height(I), ONE))
    O = canvas(bg, astuple(n, n))
    O1 = branch(greater(n, THREE), paint(O, recolor(leastcolor(bottom), tpatch)), O)
    O2 = branch(greater(n, THREE), paint(O1, recolor(leastcolor(right), lpatch)), O1)
    O3 = paint(O2, recolor(color(oc), cpatch))
    O4 = paint(O3, recolor(color(op), ppatch))
    return O4

def dsl4(I):
    bg = mostcolor(I)
    # use full objects API; diagonal=False, without_bg=True
    objs = objects(I, T, F, T)
    # size from extent; force odd if even
    n0 = maximum(combine(initset(valmax(objs, height)), initset(valmax(objs, width))))
    n = branch(even(n0), increment(n0), n0)
    l = subtract(n, ONE)
    l1 = subtract(l, ONE)
    m = divide(n, TWO)
    # patches
    cpatch = insert(astuple(ZERO, ZERO), insert(astuple(ZERO, l), insert(astuple(l, ZERO), initset(astuple(l, l)))))
    ppatch = insert(astuple(ZERO, m), insert(astuple(m, ZERO), insert(astuple(m, l), initset(astuple(l, m)))))
    tpatch = insert(astuple(ZERO, ONE), insert(astuple(ZERO, l1), insert(astuple(l, ONE), initset(astuple(l, l1)))))
    lpatch = insert(astuple(ONE, ZERO), insert(astuple(l1, ZERO), insert(astuple(ONE, l), initset(astuple(l1, l)))))
    # select by corner occupancy
    intersz = compose(size, fork(intersection, toindices, corners))
    oc = argmax(objs, intersz)
    op = argmin(objs, intersz)
    # edge colors from halves (robust to noise)
    thalf = tophalf(I)
    lhalf = lefthalf(I)
    O = canvas(bg, astuple(n, n))
    O1 = branch(greater(n, THREE), paint(O, recolor(leastcolor(thalf), tpatch)), O)
    O2 = branch(greater(n, THREE), paint(O1, recolor(leastcolor(lhalf), lpatch)), O1)
    O3 = paint(O2, recolor(color(oc), cpatch))
    O4 = paint(O3, recolor(color(op), ppatch))
    return O4

def dsl5(I):
    bg = mostcolor(I)
    objs = fgpartition(I)
    # size from max of heights/widths
    n = maximum(combine(initset(valmax(objs, height)), initset(valmax(objs, width))))
    l = subtract(n, ONE)
    l1 = subtract(l, ONE)
    m = divide(n, TWO)
    # patches
    cpatch = insert(astuple(ZERO, ZERO), insert(astuple(ZERO, l), insert(astuple(l, ZERO), initset(astuple(l, l)))))
    ppatch = insert(astuple(ZERO, m), insert(astuple(m, ZERO), insert(astuple(m, l), initset(astuple(l, m)))))
    tpatch = insert(astuple(ZERO, ONE), insert(astuple(ZERO, l1), insert(astuple(l, ONE), initset(astuple(l, l1)))))
    lpatch = insert(astuple(ONE, ZERO), insert(astuple(l1, ZERO), insert(astuple(ONE, l), initset(astuple(l1, l)))))
    # corner-rich vs corner-poor objects
    intersz = compose(size, fork(intersection, toindices, corners))
    oc = argmax(objs, intersz)
    op = argmin(objs, intersz)
    # for richer palettes, take edge colors from top/left; otherwise keep bg
    top = crop(I, astuple(ZERO, ZERO), astuple(ONE, width(I)))
    left = crop(I, astuple(ZERO, ZERO), astuple(height(I), ONE))
    pal = difference(palette(I), initset(bg))
    et = branch(greater(size(pal), TWO), leastcolor(top), bg)
    el = branch(greater(size(pal), TWO), leastcolor(left), bg)
    O = canvas(bg, astuple(n, n))
    O1 = branch(greater(n, THREE), paint(O, recolor(et, tpatch)), O)
    O2 = branch(greater(n, THREE), paint(O1, recolor(el, lpatch)), O1)
    O3 = paint(O2, recolor(color(oc), cpatch))
    O4 = paint(O3, recolor(color(op), ppatch))
    return O4
```