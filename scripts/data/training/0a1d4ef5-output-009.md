```python
def dsl1(I):
    # Global resampling per 10x10 tile: downscale inner 8x8 to 1x1 (majority), assemble and crop
    U = UNITY
    d10 = astuple(TEN, TEN); d8 = astuple(EIGHT, EIGHT); off = UNITY
    def tile_majority(r0, c0):
        X = crop(I, astuple(r0, c0), d10)
        C = crop(X, off, d8)
        D = downscale(C, EIGHT)
        return mostcolor(D)
    c00 = tile_majority(ZERO, ZERO);      c01 = tile_majority(ZERO, TEN);      c02 = tile_majority(ZERO, double(TEN))
    c10 = tile_majority(TEN, ZERO);       c11 = tile_majority(TEN, TEN);       c12 = tile_majority(TEN, double(TEN))
    c20 = tile_majority(double(TEN), ZERO); c21 = tile_majority(double(TEN), TEN); c22 = tile_majority(double(TEN), double(TEN))
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O

def dsl2(I):
    # Object extraction: per tile, choose largest filled rectangle object (delta size == 0), else 0; assemble and crop
    U = UNITY; z = ZERO
    d10 = astuple(TEN, TEN); d8 = astuple(EIGHT, EIGHT); off = UNITY
    def tile_rect(r0, c0):
        X = crop(I, astuple(r0, c0), d10)
        C = crop(X, off, d8)
        Os = objects(C, T, F, T)
        rrect = compose(lbind(equality, z), compose(size, delta))
        R = sfilter(Os, rrect)
        pick = branch(equality(size(R), z), z, color(argmax(R, size)))
        return pick
    c00 = tile_rect(z, z);      c01 = tile_rect(z, TEN);      c02 = tile_rect(z, double(TEN))
    c10 = tile_rect(TEN, z);    c11 = tile_rect(TEN, TEN);    c12 = tile_rect(TEN, double(TEN))
    c20 = tile_rect(double(TEN), z); c21 = tile_rect(double(TEN), TEN); c22 = tile_rect(double(TEN), double(TEN))
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O

def dsl3(I):
    # Color filtering: per tile, exclude colors on inner-8x8 border, choose dominant remaining; fallback 0; assemble and crop
    U = UNITY; z = ZERO
    d10 = astuple(TEN, TEN); d8 = astuple(EIGHT, EIGHT); off = UNITY
    def tile_no_inner_border(r0, c0):
        X = crop(I, astuple(r0, c0), d10)
        C = crop(X, off, d8)
        EC = asobject(C)
        BIDX = box(asindices(C))
        BOBJ = toobject(BIDX, C)
        PcC = difference(palette(EC), initset(z))
        PcB = difference(palette(BOBJ), initset(z))
        use = difference(PcC, PcB)
        comp = lbind(colorcount, EC)
        pick = branch(equality(size(use), z), z, argmax(use, comp))
        return pick
    c00 = tile_no_inner_border(z, z);      c01 = tile_no_inner_border(z, TEN);      c02 = tile_no_inner_border(z, double(TEN))
    c10 = tile_no_inner_border(TEN, z);    c11 = tile_no_inner_border(TEN, TEN);    c12 = tile_no_inner_border(TEN, double(TEN))
    c20 = tile_no_inner_border(double(TEN), z); c21 = tile_no_inner_border(double(TEN), TEN); c22 = tile_no_inner_border(double(TEN), double(TEN))
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O

def dsl4(I):
    # Geometric filtering: per tile, keep components with width>3 or height>3; pick largest; else 0; assemble and crop
    U = UNITY; z = ZERO
    d10 = astuple(TEN, TEN); d8 = astuple(EIGHT, EIGHT); off = UNITY
    gt3_w = compose(rbind(greater, THREE), width)
    gt3_h = compose(rbind(greater, THREE), height)
    cond = fork(either, gt3_w, gt3_h)
    def tile_dim(r0, c0):
        X = crop(I, astuple(r0, c0), d10)
        C = crop(X, off, d8)
        Os = objects(C, T, F, T)
        R = sfilter(Os, cond)
        pick = branch(equality(size(R), z), z, color(argmax(R, size)))
        return pick
    c00 = tile_dim(z, z);      c01 = tile_dim(z, TEN);      c02 = tile_dim(z, double(TEN))
    c10 = tile_dim(TEN, z);    c11 = tile_dim(TEN, TEN);    c12 = tile_dim(TEN, double(TEN))
    c20 = tile_dim(double(TEN), z); c21 = tile_dim(double(TEN), TEN); c22 = tile_dim(double(TEN), double(TEN))
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O

def dsl5(I):
    # Relational: per tile, intersect colors present in all four 4x4 quadrants; pick dominant; fallback to inner palette; assemble and crop
    U = UNITY; z = ZERO
    d10 = astuple(TEN, TEN); d8 = astuple(EIGHT, EIGHT); off = UNITY
    def tile_quads(r0, c0):
        X = crop(I, astuple(r0, c0), d10)
        C = crop(X, off, d8)
        TH = tophalf(C); BH = bottomhalf(C)
        TL = lefthalf(TH); TR = righthalf(TH)
        BL = lefthalf(BH); BR = righthalf(BH)
        P1 = palette(TL); P2 = palette(TR); P3 = palette(BL); P4 = palette(BR)
        I12 = intersection(P1, P2); I34 = intersection(P3, P4)
        Iall = difference(intersection(I12, I34), initset(z))
        EC = asobject(C)
        PcF = difference(palette(EC), initset(z))
        use = branch(equality(size(Iall), z), PcF, Iall)
        comp = lbind(colorcount, EC)
        return argmax(use, comp)
    c00 = tile_quads(z, z);      c01 = tile_quads(z, TEN);      c02 = tile_quads(z, double(TEN))
    c10 = tile_quads(TEN, z);    c11 = tile_quads(TEN, TEN);    c12 = tile_quads(TEN, double(TEN))
    c20 = tile_quads(double(TEN), z); c21 = tile_quads(double(TEN), TEN); c22 = tile_quads(double(TEN), double(TEN))
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O
```