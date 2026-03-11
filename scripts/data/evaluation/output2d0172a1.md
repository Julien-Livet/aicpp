```python
def dsl1(I):
    x1 = compress(I)
    x2 = downscale(x1, TWO)
    lc = leastcolor(I)
    b = box(asindices(x2))
    O = fill(x2, lc, b)
    return O

def dsl2(I):
    x0 = trim(I)
    x1 = compress(x0)
    x2 = downscale(x1, TWO)
    lc = leastcolor(I)
    b = box(asindices(x2))
    O = fill(x2, lc, b)
    return O

def dsl3(I):
    lc = leastcolor(I)
    fg = ofcolor(I, lc)
    obj = toobject(fg, I)
    crop = subgrid(obj, I)
    x1 = compress(crop)
    x2 = downscale(x1, TWO)
    b = box(asindices(x2))
    O = fill(x2, lc, b)
    return O

def dsl4(I):
    x = downscale(compress(I), TWO)
    lc = leastcolor(I)
    mc = mostcolor(I)
    base = canvas(mc, shape(x))
    border = box(asindices(base))
    O1 = fill(base, lc, border)
    frs = frontiers(x)
    recolored = mapply(lbind(recolor, lc), frs)
    obj = merge(recolored)
    O = paint(O1, obj)
    return O

def dsl5(I):
    x = downscale(compress(trim(I)), TWO)
    lc = leastcolor(I)
    b = box(asindices(x))
    O = fill(x, lc, b)
    return O
```