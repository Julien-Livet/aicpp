```python
def dsl1(I):
    # Object extraction: recolor all non-zero objects of size 1 or 2 to 3
    objs = objects(I, T, F, T)
    small = combine(sizefilter(objs, 1), sizefilter(objs, 2))
    mask = merge(mapply(toindices, small))
    O = fill(I, THREE, mask)
    return O

def dsl2(I):
    # Color-centric via partition: recolor small foreground components to 3
    parts = partition(I)
    nonbg = difference(parts, colorfilter(parts, ZERO))
    small = combine(sizefilter(nonbg, 1), sizefilter(nonbg, 2))
    recol = mapply(lbind(recolor, THREE), small)
    O = paint(I, merge(recol))
    return O

def dsl3(I):
    # Global reconstruct: remove small objects, then add them back recolored to 3
    objs = fgpartition(I)
    small = combine(sizefilter(objs, 1), sizefilter(objs, 2))
    base = cover(I, merge(small))
    reobj = recolor(THREE, merge(small))
    O = paint(base, reobj)
    return O

def dsl4(I):
    # Geometric filtering: recolor singles and 2-length lines (h or v) to 3
    objs = objects(I, T, F, T)
    ones = sizefilter(objs, 1)
    twos = sizefilter(objs, 2)
    isline = fork(either, hline, vline)
    twolines = sfilter(twos, isline)
    small = combine(ones, twolines)
    mask = merge(mapply(toindices, small))
    O = fill(I, THREE, mask)
    return O

def dsl5(I):
    # Structural mask: unify indices of all small components and fill with 3
    objs = objects(I, T, F, T)
    small = combine(sizefilter(objs, 1), sizefilter(objs, 2))
    mask = merge(mapply(toindices, small))
    O = fill(I, THREE, mask)
    return O
```