```python
def dsl1(I):
    # union of all non-bordering univalued objects; crop; add 1-thick frame of majority among {3,8}
    objs = objects(I, True, False, True)
    inner = sfilter(objs, compose(flip, rbind(bordering, I)))
    idxs = apply(toindices, inner)
    uni = merge(idxs)
    core = subgrid(uni, I)
    coreidx = normalize(uni)
    innerobj = toobject(coreidx, core)
    dims = add(shape(core), TWO_BY_TWO)
    base = canvas(ZERO, dims)
    G = paint(base, shift(innerobj, UNITY))
    c3 = colorcount(I, THREE)
    c8 = colorcount(I, EIGHT)
    C = branch(greater(c8, c3), EIGHT, THREE)
    O = fill(G, C, box(asindices(G)))
    return O

def dsl2(I):
    # largest non-bordering multicolor (univalued=False) component; crop; frame color = majority of {3,8}
    comps = objects(I, False, False, True)
    nb = sfilter(comps, compose(flip, rbind(bordering, I)))
    big = argmax(nb, size)
    uni = toindices(big)
    core = subgrid(uni, I)
    innerobj = toobject(normalize(uni), core)
    dims = add(shape(core), TWO_BY_TWO)
    base = canvas(ZERO, dims)
    G = paint(base, shift(innerobj, UNITY))
    c3 = colorcount(I, THREE)
    c8 = colorcount(I, EIGHT)
    C = branch(greater(c8, c3), EIGHT, THREE)
    O = fill(G, C, box(asindices(G)))
    return O

def dsl3(I):
    # suppress 1 and 2 first; take largest non-bordering multicolor component; crop; frame by majority {3,8}
    t1 = replace(I, ONE, ZERO)
    t2 = replace(t1, TWO, ZERO)
    comps = objects(t2, False, False, True)
    nb = sfilter(comps, compose(flip, rbind(bordering, t2)))
    big = argmax(nb, size)
    uni = toindices(big)
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

def dsl4(I):
    # non-bordering multicolor union; frame color chosen from colors on original bounding-box frame, preferring {3,8}
    comps = objects(I, False, False, True)
    nb = sfilter(comps, compose(flip, rbind(bordering, I)))
    idxs = apply(toindices, nb)
    uni = merge(idxs)
    core = subgrid(uni, I)
    innerobj = toobject(normalize(uni), core)
    dims = add(shape(core), TWO_BY_TWO)
    base = canvas(ZERO, dims)
    G = paint(base, shift(innerobj, UNITY))
    bb = backdrop(uni)
    frm = box(bb)
    edgeobj = toobject(frm, I)
    c3 = colorcount(edgeobj, THREE)
    c8 = colorcount(edgeobj, EIGHT)
    C = branch(greater(c8, c3), EIGHT, THREE)
    O = fill(G, C, box(asindices(G)))
    return O

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