```python
def dsl1(I):
    # Crop to the fundamental repeating tile, then keep its internal frontiers as 8s
    nz_idx = difference(asindices(I), ofcolor(I, ZERO))
    nz_obj = toobject(nz_idx, I)
    hp = hperiod(nz_obj)
    vp = vperiod(nz_obj)
    start = ulcorner(nz_obj)
    tile = crop(I, start, astuple(vp, hp))
    frs = frontiers(tile)
    fobj = merge(frs)
    fidx = toindices(fobj)
    base = canvas(ZERO, shape(tile))
    O = fill(base, EIGHT, fidx)
    return O

def dsl2(I):
    # Tile frontiers plus the tile border (box) emphasized as 8s
    nz_idx_full = difference(asindices(I), ofcolor(I, ZERO))
    nz_obj_full = toobject(nz_idx_full, I)
    hp = hperiod(nz_obj_full)
    vp = vperiod(nz_obj_full)
    start = ulcorner(nz_obj_full)
    tile = crop(I, start, astuple(vp, hp))
    frs = frontiers(tile)
    fobj = merge(frs)
    fidx = toindices(fobj)
    tile_nz = difference(asindices(tile), ofcolor(tile, ZERO))
    border = box(tile_nz)
    edges = combine(fidx, border)
    base = canvas(ZERO, shape(tile))
    O = fill(base, EIGHT, edges)
    return O

def dsl3(I):
    # Within the fundamental tile, mark the minimal nonzero color positions with 8
    nz_idx = difference(asindices(I), ofcolor(I, ZERO))
    nz_obj = toobject(nz_idx, I)
    hp = hperiod(nz_obj)
    vp = vperiod(nz_obj)
    start = ulcorner(nz_obj)
    tile = crop(I, start, astuple(vp, hp))
    pal = palette(tile)
    pal_nz = remove(ZERO, pal)
    cmin = minimum(pal_nz)
    idx = ofcolor(tile, cmin)
    base = canvas(ZERO, shape(tile))
    O = fill(base, EIGHT, idx)
    return O

def dsl4(I):
    # Keep only vertical frontiers inside the fundamental tile (plus implicit cropping)
    nz_idx = difference(asindices(I), ofcolor(I, ZERO))
    nz_obj = toobject(nz_idx, I)
    hp = hperiod(nz_obj)
    vp = vperiod(nz_obj)
    start = ulcorner(nz_obj)
    tile = crop(I, start, astuple(vp, hp))
    frs = frontiers(tile)
    vfrs = sfilter(frs, vline)
    vfobj = merge(vfrs)
    vfidx = toindices(vfobj)
    base = canvas(ZERO, shape(tile))
    O = fill(base, EIGHT, vfidx)
    return O

def dsl5(I):
    # Keep only horizontal frontiers inside the fundamental tile
    nz_idx = difference(asindices(I), ofcolor(I, ZERO))
    nz_obj = toobject(nz_idx, I)
    hp = hperiod(nz_obj)
    vp = vperiod(nz_obj)
    start = ulcorner(nz_obj)
    tile = crop(I, start, astuple(vp, hp))
    frs = frontiers(tile)
    hfrs = sfilter(frs, hline)
    hfobj = merge(hfrs)
    hfidx = toindices(hfobj)
    base = canvas(ZERO, shape(tile))
    O = fill(base, EIGHT, hfidx)
    return O
```