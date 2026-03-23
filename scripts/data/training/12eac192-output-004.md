```python
def dsl1(I):
    # Global reconstruct: recolor all nonzero objects of size 1 or 2 to 3
    objs = objects(I, T, F, T)
    small = combine(sizefilter(objs, 1), sizefilter(objs, 2))
    smallobj = merge(small)
    O = paint(I, recolor(THREE, smallobj))
    return O

def dsl2(I):
    # Object extraction via mask: fill indices of all small components with 3
    objs = objects(I, T, F, T)
    small = combine(sizefilter(objs, 1), sizefilter(objs, 2))
    mask = toindices(merge(small))
    O = fill(I, THREE, mask)
    return O

def dsl3(I):
    # Color filtering via partition: recolor small monochrome regions to 3
    parts = partition(I)
    nonbg = difference(parts, colorfilter(parts, ZERO))
    small = combine(sizefilter(nonbg, 1), sizefilter(nonbg, 2))
    smallobj = merge(small)
    O = paint(I, recolor(THREE, smallobj))
    return O

def dsl4(I):
    # Geometric filtering: recolor singles and 2-length lines (h or v) to 3
    objs = objects(I, T, F, T)
    ones = sizefilter(objs, 1)
    twos = sizefilter(objs, 2)
    isline = fork(either, hline, vline)
    twolines = sfilter(twos, isline)
    small = combine(ones, twolines)
    O = paint(I, recolor(THREE, merge(small)))
    return O

def dsl5(I):
    # Relational reconstruct: remove small components, then underpaint them as 3
    objs = objects(I, T, F, T)
    small = combine(sizefilter(objs, 1), sizefilter(objs, 2))
    smallobj = merge(small)
    base = cover(I, smallobj)
    O = underpaint(base, recolor(THREE, smallobj))
    return O
```