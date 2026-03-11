```python
def dsl1(I):
    bg = mostcolor(I)
    cols = remove(bg, palette(I))
    oc = lbind(ofcolor, I)
    tobj = rbind(toobject, I)
    corner = compose(initset, ulcorner)
    f = chain(corner, tobj, oc)
    uls = mapply(f, cols)
    O = fill(I, bg, uls)
    return O

def dsl2(I):
    bg = mostcolor(I)
    objs = objects(I, T, F, T)
    singles = sizefilter(objs, ONE)
    inds = mapply(toindices, singles)
    O = fill(I, bg, inds)
    return O

def dsl3(I):
    bg = mostcolor(I)
    objs = objects(I, T, F, T)
    crns = mapply(corners, objs)
    O = fill(I, bg, crns)
    return O

def dsl4(I):
    bg = mostcolor(I)
    cols = remove(bg, palette(I))
    rare = valmin(cols, lbind(colorcount, I))
    patch = ofcolor(I, rare)
    O = fill(I, bg, patch)
    return O

def dsl5(I):
    bg = mostcolor(I)
    objs = objects(I, T, F, T)
    outls = mapply(box, objs)
    O = fill(I, bg, outls)
    return O
```