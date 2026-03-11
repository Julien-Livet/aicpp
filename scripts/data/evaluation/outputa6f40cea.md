```python
def dsl1(I):
    bg = mostcolor(I)
    keep = difference(asindices(I), ofcolor(I, bg))
    O = subgrid(keep, I)
    return O

def dsl2(I):
    bg = mostcolor(I)
    pals = palette(I)
    pals_nb = remove(bg, pals)
    fgmax = argmax(pals_nb, lbind(colorcount, I))
    x = replace(I, fgmax, bg)
    keep = difference(asindices(x), ofcolor(x, bg))
    O = subgrid(keep, x)
    return O

def dsl3(I):
    objs = objects(I, T, F, T)
    interior = sfilter(objs, compose(flip, rbind(bordering, I)))
    merged = merge(interior)
    O = subgrid(toindices(merged), I)
    return O

def dsl4(I):
    bg = mostcolor(I)
    objs = objects(I, T, F, T)
    norm = apply(normalize, objs)
    merged = merge(norm)
    dims = shape(merged)
    O = paint(canvas(bg, dims), merged)
    return O

def dsl5(I):
    O = downscale(I, TWO)
    return O
```