```python
def dsl1(I):
    obj = asobject(I)
    allidx = asindices(I)
    nzidx = difference(allidx, ofcolor(I, ZERO))
    offsets = apply(rbind(multiply, THREE), nzidx)
    uobj = mapply(lbind(shift, obj), offsets)
    dims = multiply(THREE_BY_THREE, THREE)
    O = paint(canvas(ZERO, dims), uobj)
    return O

def dsl2(I):
    dims = multiply(THREE_BY_THREE, THREE)
    steps = interval(ZERO, multiply(THREE, THREE), THREE)
    roffs = apply(toivec, steps)
    coffs = apply(tojvec, steps)
    blockoffsets = prapply(add, roffs, coffs)
    baseobj = asobject(I)
    tiledobj = mapply(lbind(shift, baseobj), blockoffsets)
    tiled = paint(canvas(ZERO, dims), tiledobj)
    nzidx = difference(asindices(I), ofcolor(I, ZERO))
    p3 = apply(rbind(multiply, THREE), nzidx)
    base = asindices(I)
    mask = mapply(lbind(shift, base), p3)
    colored = toobject(mask, tiled)
    O = paint(canvas(ZERO, dims), colored)
    return O

def dsl3(I):
    H1 = hconcat(I, I)
    H = hconcat(H1, I)
    V1 = vconcat(H, H)
    tiled = vconcat(V1, H)
    nzidx = difference(asindices(I), ofcolor(I, ZERO))
    p3 = apply(rbind(multiply, THREE), nzidx)
    q = asindices(I)
    mask = mapply(lbind(shift, p3), q)
    colored = toobject(mask, tiled)
    O = paint(canvas(ZERO, multiply(THREE_BY_THREE, THREE)), colored)
    return O

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

def dsl5(I):
    nzidx = difference(asindices(I), ofcolor(I, ZERO))
    p3 = apply(rbind(multiply, THREE), nzidx)
    cells = toobject(nzidx, I)
    F = fork(recolor, color, compose(lbind(shift, p3), last))
    uobj = mapply(F, cells)
    O = paint(canvas(ZERO, multiply(THREE_BY_THREE, THREE)), uobj)
    return O
```