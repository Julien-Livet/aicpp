```python
def dsl1(I):
    # Global: intersect horizontal mirror and 90° rotation
    O = cellwise(hmirror(I), rot90(I), ZERO)
    return O

def dsl2(I):
    # Object extraction: fill the interior (inbox) of the 5-object's bbox with 5
    fidx = ofcolor(I, FIVE)
    fobj = toobject(fidx, I)
    area = inbox(fobj)
    O = fill(canvas(ZERO, shape(I)), FIVE, area)
    return O

def dsl3(I):
    # Color filtering: recolor all 5s to the least common color in the grid
    c = leastcolor(I)
    O = replace(I, FIVE, c)
    return O

def dsl4(I):
    # Geometric: paint rows/cols through seeds inside the 5-region with the dominant seed color
    dims = shape(I)
    base = canvas(ZERO, dims)
    fidx = ofcolor(I, FIVE)
    fbase = fill(base, FIVE, fidx)
    allidx = asindices(I)
    zeroidx = ofcolor(I, ZERO)
    seedidx = difference(allidx, combine(zeroidx, fidx))
    rows = mapply(hfrontier, seedidx)
    cols = mapply(vfrontier, seedidx)
    cross = combine(rows, cols)
    mask = intersection(cross, fidx)
    objs = objects(I, T, F, T)
    others = difference(objs, colorfilter(objs, FIVE))
    seedcolors = apply(color, others)
    c = mostcommon(totuple(seedcolors))
    O = fill(fbase, c, mask)
    return O

def dsl5(I):
    # Relational/structural: recolor the boundary of the 5-object by the largest seed color
    fidx = ofcolor(I, FIVE)
    fobj = toobject(fidx, I)
    edge = box(fobj)
    objs = objects(I, T, F, T)
    others = difference(objs, colorfilter(objs, FIVE))
    big = argmax(others, size)
    c = color(big)
    O = fill(I, c, edge)
    return O
```