```python
def dsl1(I):
    # Separate 4x4 objects into hollow (left column) and solid (right column), keep raster order, pack into 4x4 tiles
    allobjs = objects(I, T, F, T)
    dims44 = astuple(FOUR, FOUR)
    is44 = matcher(shape, dims44)
    objs44 = sfilter(allobjs, is44)
    ordered = order(objs44, ulcorner)
    isHollow = compose(positive, compose(size, delta))
    hollows = sfilter(ordered, isHollow)
    solids = sfilter(ordered, compose(flip, isHollow))
    # build 4x4 tile objects from source
    tilefunc = compose(asobject, rbind(subgrid, I))
    htiles = apply(tilefunc, hollows)
    stiles = apply(tilefunc, solids)
    # layout
    lenH = size(hollows)
    lenS = size(solids)
    nrows = branch(greater(lenH, lenS), lenH, lenS)
    H = multiply(nrows, FOUR)
    W = multiply(TWO, FOUR)
    O = canvas(ZERO, astuple(H, W))
    # offsets for left column (hollows)
    rowsH = interval(ZERO, multiply(lenH, FOUR), FOUR)
    vH = apply(toivec, rowsH)
    offH = apply(lbind(add, tojvec(ZERO)), vH)
    # offsets for right column (solids)
    rowsS = interval(ZERO, multiply(lenS, FOUR), FOUR)
    vS = apply(toivec, rowsS)
    offS = apply(lbind(add, tojvec(FOUR)), vS)
    # place hollows
    placedH = merge(papply(shift, htiles, offH))
    O = paint(O, placedH)
    # place solids
    placedS = merge(papply(shift, stiles, offS))
    O = paint(O, placedS)
    return O

def dsl2(I):
    # Same as dsl1 but swap columns: solids on left, hollows on right
    allobjs = objects(I, T, F, T)
    dims44 = astuple(FOUR, FOUR)
    is44 = matcher(shape, dims44)
    objs44 = sfilter(allobjs, is44)
    ordered = order(objs44, ulcorner)
    isHollow = compose(positive, compose(size, delta))
    hollows = sfilter(ordered, isHollow)
    solids = sfilter(ordered, compose(flip, isHollow))
    tilefunc = compose(asobject, rbind(subgrid, I))
    htiles = apply(tilefunc, hollows)
    stiles = apply(tilefunc, solids)
    lenH = size(hollows)
    lenS = size(solids)
    nrows = branch(greater(lenH, lenS), lenH, lenS)
    H = multiply(nrows, FOUR)
    W = multiply(TWO, FOUR)
    O = canvas(ZERO, astuple(H, W))
    # solids on left
    rowsS = interval(ZERO, multiply(lenS, FOUR), FOUR)
    vS = apply(toivec, rowsS)
    offS = apply(lbind(add, tojvec(ZERO)), vS)
    placedS = merge(papply(shift, stiles, offS))
    O = paint(O, placedS)
    # hollows on right
    rowsH = interval(ZERO, multiply(lenH, FOUR), FOUR)
    vH = apply(toivec, rowsH)
    offH = apply(lbind(add, tojvec(FOUR)), vH)
    placedH = merge(papply(shift, htiles, offH))
    O = paint(O, placedH)
    return O

def dsl3(I):
    # Pack all 4x4 tiles (hollow or solid) in raster order into a single vertical column
    allobjs = objects(I, T, F, T)
    dims44 = astuple(FOUR, FOUR)
    is44 = matcher(shape, dims44)
    objs44 = sfilter(allobjs, is44)
    ordered = order(objs44, ulcorner)
    tilefunc = compose(asobject, rbind(subgrid, I))
    tiles = apply(tilefunc, ordered)
    n = size(tiles)
    H = multiply(n, FOUR)
    W = FOUR
    O = canvas(ZERO, astuple(H, W))
    rows = interval(ZERO, multiply(n, FOUR), FOUR)
    v = apply(toivec, rows)
    off = apply(lbind(add, tojvec(ZERO)), v)
    placed = merge(papply(shift, tiles, off))
    O = paint(O, placed)
    return O

def dsl4(I):
    # Separate 4x4 objects into hollow/solid, but order each column by color instead of raster order
    allobjs = objects(I, T, F, T)
    dims44 = astuple(FOUR, FOUR)
    is44 = matcher(shape, dims44)
    objs44 = sfilter(allobjs, is44)
    isHollow = compose(positive, compose(size, delta))
    hollows = sfilter(objs44, isHollow)
    solids = sfilter(objs44, compose(flip, isHollow))
    hollows_sorted = order(hollows, color)
    solids_sorted = order(solids, color)
    tilefunc = compose(asobject, rbind(subgrid, I))
    htiles = apply(tilefunc, hollows_sorted)
    stiles = apply(tilefunc, solids_sorted)
    lenH = size(htiles)
    lenS = size(stiles)
    nrows = branch(greater(lenH, lenS), lenH, lenS)
    H = multiply(nrows, FOUR)
    W = multiply(TWO, FOUR)
    O = canvas(ZERO, astuple(H, W))
    rowsH = interval(ZERO, multiply(lenH, FOUR), FOUR)
    offH = apply(lbind(add, tojvec(ZERO)), apply(toivec, rowsH))
    rowsS = interval(ZERO, multiply(lenS, FOUR), FOUR)
    offS = apply(lbind(add, tojvec(FOUR)), apply(toivec, rowsS))
    O = paint(O, merge(papply(shift, htiles, offH)))
    O = paint(O, merge(papply(shift, stiles, offS)))
    return O

def dsl5(I):
    # Only collect hollow 4x4 frames in raster order and stack them in the left column; ignore solids
    allobjs = objects(I, T, F, T)
    dims44 = astuple(FOUR, FOUR)
    is44 = matcher(shape, dims44)
    objs44 = sfilter(allobjs, is44)
    ordered = order(objs44, ulcorner)
    isHollow = compose(positive, compose(size, delta))
    hollows = sfilter(ordered, isHollow)
    htiles = apply(compose(asobject, rbind(subgrid, I)), hollows)
    n = size(htiles)
    H = multiply(n, FOUR)
    W = FOUR
    O = canvas(ZERO, astuple(H, W))
    rowsH = interval(ZERO, multiply(n, FOUR), FOUR)
    offH = apply(lbind(add, tojvec(ZERO)), apply(toivec, rowsH))
    O = paint(O, merge(papply(shift, htiles, offH)))
    return O
```