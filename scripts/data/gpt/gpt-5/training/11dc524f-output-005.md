```python
def dsl1(I):
    dims = shape(I)
    bg = canvas(SEVEN, dims)
    s2 = ofcolor(I, TWO)
    s5 = ofcolor(I, FIVE)
    v = gravitate(s2, s5)
    s2p = shift(s2, multiply(v, TWO))
    c5 = centerofmass(s5)
    cg = center(asindices(I))
    s2c = shift(s2p, subtract(cg, c5))
    g = paint(bg, recolor(TWO, s2c))
    grot = rot180(g)
    r2 = ofcolor(grot, TWO)
    r2b = shift(r2, subtract(c5, cg))
    O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, r2b))
    return O

def dsl2(I):
    dims = shape(I)
    bg = canvas(SEVEN, dims)
    objs = objects(I, T, F, T)
    o2 = first(colorfilter(objs, TWO))
    o5 = first(colorfilter(objs, FIVE))
    s2 = toindices(o2)
    s5 = toindices(o5)
    v = gravitate(s2, s5)
    s2p = shift(s2, multiply(v, TWO))
    c2p = centerofmass(s2p)
    c5 = centerofmass(s5)
    best = shift(s2p, subtract(c5, c2p))
    O = underpaint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
    return O

def dsl3(I):
    dims = shape(I)
    bg = canvas(SEVEN, dims)
    s2 = ofcolor(I, TWO)
    s5 = ofcolor(I, FIVE)
    v = gravitate(s2, s5)
    s2p = shift(s2, multiply(v, TWO))
    mh = hmirror(s2p)
    mv = vmirror(s2p)
    dh = gravitate(mh, s5)
    dv = gravitate(mv, s5)
    ah = shift(mh, dh)
    av = shift(mv, dv)
    chooser = lbind(manhattan, s5)
    best = branch(greater(chooser(ah), chooser(av)), av, ah)
    O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
    return O

def dsl4(I):
    dims = shape(I)
    bg = canvas(SEVEN, dims)
    s2 = ofcolor(I, TWO)
    s5 = ofcolor(I, FIVE)
    v = gravitate(s2, s5)
    s2p = shift(s2, multiply(v, TWO))
    n2 = normalize(s2p)
    lr = lrcorner(n2)
    ul5 = ulcorner(s5)
    off = subtract(ul5, lr)
    best = shift(n2, off)
    O = paint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
    return O

def dsl5(I):
    dims = shape(I)
    bg = canvas(SEVEN, dims)
    s2 = ofcolor(I, TWO)
    s5 = ofcolor(I, FIVE)
    v = gravitate(s2, s5)
    s2p = shift(s2, multiply(v, TWO))
    c5 = centerofmass(s5)
    mh = hmirror(s2p)
    mv = vmirror(s2p)
    ah = shift(mh, subtract(c5, centerofmass(mh)))
    av = shift(mv, subtract(c5, centerofmass(mv)))
    cset = insert(av, initset(ah))
    best = merge(cset)
    O = underpaint(paint(bg, recolor(TWO, s2p)), recolor(FIVE, best))
    return O
```