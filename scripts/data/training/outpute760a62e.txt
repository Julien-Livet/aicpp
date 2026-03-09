```python
def dsl1(I):
    # Coarse-grid propagation via detected lattice period (min positive of h/v period).
    eight_idx = ofcolor(I, EIGHT)
    eight_obj = toobject(eight_idx, I)
    ph = hperiod(eight_obj)
    pv = vperiod(eight_obj)
    cands = insert(pv, insert(ph, initset(ZERO)))
    pos = sfilter(cands, rbind(greater, ONE))
    fac = branch(greater(size(pos), ZERO), valmin(pos, identity), THREE)
    base0 = replace(I, EIGHT, ZERO)
    s = downscale(base0, fac)
    shp = shape(s)
    coarse = canvas(ZERO, shp)
    rpatch = mapply(hfrontier, ofcolor(s, THREE))
    cpatch = mapply(vfrontier, ofcolor(s, TWO))
    g1 = fill(coarse, THREE, rpatch)
    g2 = fill(g1, TWO, cpatch)
    inter = intersection(rpatch, cpatch)
    g3 = fill(g2, SIX, inter)
    u1 = hupscale(g3, fac)
    u2 = vupscale(u1, fac)
    O = fill(u2, EIGHT, eight_idx)
    return O

def dsl2(I):
    # Fine-grid: fill full columns for 2 and full rows for 3; intersections -> 6; restore 8s.
    eight_idx = ofcolor(I, EIGHT)
    non8 = difference(asindices(I), eight_idx)
    rows3 = mapply(hfrontier, ofcolor(I, THREE))
    cols2 = mapply(vfrontier, ofcolor(I, TWO))
    base = canvas(ZERO, shape(I))
    g = fill(base, TWO, intersection(cols2, non8))
    g = fill(g, THREE, intersection(rows3, non8))
    inter = intersection(rows3, cols2)
    g = fill(g, SIX, intersection(inter, non8))
    O = fill(g, EIGHT, eight_idx)
    return O

def dsl3(I):
    # Coarse-grid with swapped propagation roles (2 -> horizontal, 3 -> vertical); intersections -> 6.
    eight_idx = ofcolor(I, EIGHT)
    eight_obj = toobject(eight_idx, I)
    ph = hperiod(eight_obj)
    pv = vperiod(eight_obj)
    fac = branch(greater(pv, ONE), pv, branch(greater(ph, ONE), ph, THREE))
    base0 = replace(I, EIGHT, ZERO)
    s = downscale(base0, fac)
    shp = shape(s)
    coarse = canvas(ZERO, shp)
    rpatch = mapply(hfrontier, ofcolor(s, TWO))
    cpatch = mapply(vfrontier, ofcolor(s, THREE))
    g1 = fill(coarse, TWO, rpatch)
    g2 = fill(g1, THREE, cpatch)
    inter = intersection(rpatch, cpatch)
    g3 = fill(g2, SIX, inter)
    u1 = hupscale(g3, fac)
    u2 = vupscale(u1, fac)
    O = fill(u2, EIGHT, eight_idx)
    return O

def dsl4(I):
    # Band expansion by shifting within cells: expand rows with 3 up/down, columns with 2 left/right.
    eight_idx = ofcolor(I, EIGHT)
    non8 = difference(asindices(I), eight_idx)
    rows3 = mapply(hfrontier, ofcolor(I, THREE))
    rows3_u = shift(rows3, UP)
    rows3_d = shift(rows3, DOWN)
    rows3_u2 = shift(rows3, double(UP))
    rows3_d2 = shift(rows3, double(DOWN))
    rows_band = combine(rows3, combine(rows3_u, combine(rows3_d, combine(rows3_u2, rows3_d2))))
    cols2 = mapply(vfrontier, ofcolor(I, TWO))
    cols2_l = shift(cols2, LEFT)
    cols2_r = shift(cols2, RIGHT)
    cols2_l2 = shift(cols2, double(LEFT))
    cols2_r2 = shift(cols2, double(RIGHT))
    cols_band = combine(cols2, combine(cols2_l, combine(cols2_r, combine(cols2_l2, cols2_r2))))
    base = canvas(ZERO, shape(I))
    g = fill(base, TWO, intersection(cols_band, non8))
    g = fill(g, THREE, intersection(rows_band, non8))
    inter = intersection(rows_band, cols_band)
    g = fill(g, SIX, intersection(inter, non8))
    O = fill(g, EIGHT, eight_idx)
    return O

def dsl5(I):
    # Pixel-level union-first strategy: make separate 2-band and 3-band layers, merge with 6 at overlaps, then reapply 8s.
    eight_idx = ofcolor(I, EIGHT)
    base = canvas(ZERO, shape(I))
    rows3 = mapply(hfrontier, ofcolor(I, THREE))
    cols2 = mapply(vfrontier, ofcolor(I, TWO))
    layer2 = fill(base, TWO, cols2)
    layer3 = fill(base, THREE, rows3)
    inter = intersection(rows3, cols2)
    merged = cellwise(layer2, layer3, ZERO)
    merged = fill(merged, SIX, inter)
    O = fill(merged, EIGHT, eight_idx)
    return O
```