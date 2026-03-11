```python
def dsl1(I):
    # Fill inner zero holes with 8, then flip both 4- and 8-neighbor ring around 8 between the two FG colors
    objs = objects(I, T, F, F)
    zeros = colorfilter(objs, ZERO)
    inner_zeros = sfilter(zeros, compose(flip, rbind(bordering, I)))
    holes = merge(inner_zeros)
    G = fill(I, EIGHT, holes)
    eidx = ofcolor(G, EIGHT)
    nnei = mapply(neighbors, eidx)
    inei = mapply(ineighbors, eidx)
    ring = difference(combine(nnei, inei), eidx)
    pal = palette(I)
    pal1 = remove(ZERO, pal)
    pal2 = remove(EIGHT, pal1)
    cmin = minimum(pal2)
    cmax = maximum(pal2)
    rmin = intersection(ring, ofcolor(I, cmin))
    rmax = intersection(ring, ofcolor(I, cmax))
    H = fill(G, cmax, rmin)
    O = fill(H, cmin, rmax)
    return O

def dsl2(I):
    # Fill inner zero holes with 8, then flip only 4-neighbor ring around 8
    objs = objects(I, T, F, F)
    zeros = colorfilter(objs, ZERO)
    inner_zeros = sfilter(zeros, compose(flip, rbind(bordering, I)))
    holes = merge(inner_zeros)
    G = fill(I, EIGHT, holes)
    eidx = ofcolor(G, EIGHT)
    ring = difference(mapply(neighbors, eidx), eidx)
    pal = palette(I)
    pal1 = remove(ZERO, pal)
    pal2 = remove(EIGHT, pal1)
    cmin = minimum(pal2)
    cmax = maximum(pal2)
    rmin = intersection(ring, ofcolor(I, cmin))
    rmax = intersection(ring, ofcolor(I, cmax))
    H = fill(G, cmax, rmin)
    O = fill(H, cmin, rmax)
    return O

def dsl3(I):
    # Fill inner zero holes with 8, then flip a thicker (radius<=2, Chebyshev) band around 8
    objs = objects(I, T, F, F)
    zeros = colorfilter(objs, ZERO)
    inner_zeros = sfilter(zeros, compose(flip, rbind(bordering, I)))
    holes = merge(inner_zeros)
    G = fill(I, EIGHT, holes)
    eidx = ofcolor(G, EIGHT)
    ring1 = difference(combine(mapply(neighbors, eidx), mapply(ineighbors, eidx)), eidx)
    expand = combine(mapply(neighbors, ring1), mapply(ineighbors, ring1))
    ring2 = difference(expand, combine(ring1, eidx))
    band = combine(ring1, ring2)
    pal = palette(I)
    pal1 = remove(ZERO, pal)
    pal2 = remove(EIGHT, pal1)
    cmin = minimum(pal2)
    cmax = maximum(pal2)
    bmin = intersection(band, ofcolor(I, cmin))
    bmax = intersection(band, ofcolor(I, cmax))
    H = fill(G, cmax, bmin)
    O = fill(H, cmin, bmax)
    return O

def dsl4(I):
    # Fill inner zero holes with 8, then flip frontier cells that are adjacent to any 8
    objs = objects(I, T, F, F)
    zeros = colorfilter(objs, ZERO)
    inner_zeros = sfilter(zeros, compose(flip, rbind(bordering, I)))
    holes = merge(inner_zeros)
    G = fill(I, EIGHT, holes)
    eidx = ofcolor(G, EIGHT)
    frs = frontiers(G)
    allf = merge(frs)
    adj8 = difference(combine(mapply(neighbors, eidx), mapply(ineighbors, eidx)), eidx)
    band = intersection(allf, adj8)
    pal = palette(I)
    pal1 = remove(ZERO, pal)
    pal2 = remove(EIGHT, pal1)
    cmin = minimum(pal2)
    cmax = maximum(pal2)
    bmin = intersection(band, ofcolor(I, cmin))
    bmax = intersection(band, ofcolor(I, cmax))
    H = fill(G, cmax, bmin)
    O = fill(H, cmin, bmax)
    return O

def dsl5(I):
    # Fill inner zero holes with 8, then flip only diagonal-neighbor ring around 8
    objs = objects(I, T, F, F)
    zeros = colorfilter(objs, ZERO)
    inner_zeros = sfilter(zeros, compose(flip, rbind(bordering, I)))
    holes = merge(inner_zeros)
    G = fill(I, EIGHT, holes)
    eidx = ofcolor(G, EIGHT)
    ring = difference(mapply(ineighbors, eidx), eidx)
    pal = palette(I)
    pal1 = remove(ZERO, pal)
    pal2 = remove(EIGHT, pal1)
    cmin = minimum(pal2)
    cmax = maximum(pal2)
    rmin = intersection(ring, ofcolor(I, cmin))
    rmax = intersection(ring, ofcolor(I, cmax))
    H = fill(G, cmax, rmin)
    O = fill(H, cmin, rmax)
    return O
```