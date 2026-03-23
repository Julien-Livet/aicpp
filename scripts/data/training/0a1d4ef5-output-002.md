```python
def dsl1(I):
    # Global coarse summary: per 10x10 tile, vote among central 8x8, center row, and center col, then crop zero-only rows/cols
    z = ZERO; o = ONE; t = TEN; tt = double(TEN)
    U = UNITY
    d8 = astuple(EIGHT, EIGHT)
    drow = astuple(ONE, TEN)
    dcol = astuple(TEN, ONE)
    # starts per tile
    r0 = z; r1 = t; r2 = tt
    c0 = z; c1 = t; c2 = tt
    # central 8x8 starts
    s00 = astuple(add(r0,o), add(c0,o)); s01 = astuple(add(r0,o), add(c1,o)); s02 = astuple(add(r0,o), add(c2,o))
    s10 = astuple(add(r1,o), add(c0,o)); s11 = astuple(add(r1,o), add(c1,o)); s12 = astuple(add(r1,o), add(c2,o))
    s20 = astuple(add(r2,o), add(c0,o)); s21 = astuple(add(r2,o), add(c1,o)); s22 = astuple(add(r2,o), add(c2,o))
    # center row starts
    rr00 = astuple(add(r0,FIVE), c0); rr01 = astuple(add(r0,FIVE), c1); rr02 = astuple(add(r0,FIVE), c2)
    rr10 = astuple(add(r1,FIVE), c0); rr11 = astuple(add(r1,FIVE), c1); rr12 = astuple(add(r1,FIVE), c2)
    rr20 = astuple(add(r2,FIVE), c0); rr21 = astuple(add(r2,FIVE), c1); rr22 = astuple(add(r2,FIVE), c2)
    # center col starts
    cc00 = astuple(r0, add(c0,FIVE)); cc01 = astuple(r0, add(c1,FIVE)); cc02 = astuple(r0, add(c2,FIVE))
    cc10 = astuple(r1, add(c0,FIVE)); cc11 = astuple(r1, add(c1,FIVE)); cc12 = astuple(r1, add(c2,FIVE))
    cc20 = astuple(r2, add(c0,FIVE)); cc21 = astuple(r2, add(c1,FIVE)); cc22 = astuple(r2, add(c2,FIVE))
    # votes per tile (mode of three samples)
    def vote(s, sr, sc):
        c8 = mostcolor(crop(I, s, d8))
        cr = mostcolor(crop(I, sr, drow))
        cc = mostcolor(crop(I, sc, dcol))
        row = hconcat(canvas(c8,U), hconcat(canvas(cr,U), canvas(cc,U)))
        return mostcolor(row)
    v00 = vote(s00, rr00, cc00); v01 = vote(s01, rr01, cc01); v02 = vote(s02, rr02, cc02)
    v10 = vote(s10, rr10, cc10); v11 = vote(s11, rr11, cc11); v12 = vote(s12, rr12, cc12)
    v20 = vote(s20, rr20, cc20); v21 = vote(s21, rr21, cc21); v22 = vote(s22, rr22, cc22)
    # assemble and crop zero-only margins
    rA = hconcat(canvas(v00,U), hconcat(canvas(v01,U), canvas(v02,U)))
    rB = hconcat(canvas(v10,U), hconcat(canvas(v11,U), canvas(v12,U)))
    rC = hconcat(canvas(v20,U), hconcat(canvas(v21,U), canvas(v22,U)))
    G = vconcat(rA, vconcat(rB, rC))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O

def dsl2(I):
    # Object extraction per tile: pick the largest non-background object in each 10x10 tile
    z = ZERO; t = TEN; tt = double(TEN); U = UNITY
    d10 = astuple(TEN, TEN)
    # tiles
    T00 = crop(I, astuple(z,z), d10); T01 = crop(I, astuple(z,t), d10); T02 = crop(I, astuple(z,tt), d10)
    T10 = crop(I, astuple(t,z), d10); T11 = crop(I, astuple(t,t), d10); T12 = crop(I, astuple(t,tt), d10)
    T20 = crop(I, astuple(tt,z), d10); T21 = crop(I, astuple(tt,t), d10); T22 = crop(I, astuple(tt,tt), d10)
    # largest object color per tile
    def largerc(T):
        OB = objects(T, T, F, T)
        B = argmax(OB, size)
        return color(B)
    c00 = largerc(T00); c01 = largerc(T01); c02 = largerc(T02)
    c10 = largerc(T10); c11 = largerc(T11); c12 = largerc(T12)
    c20 = largerc(T20); c21 = largerc(T21); c22 = largerc(T22)
    # assemble coarse grid (no cropping)
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    O = vconcat(r0, vconcat(r1, r2))
    return O

def dsl3(I):
    # Color filtering via morphology: remove single-pixel noise, keep larger objects, then downscale and crop zero-only margins
    U = UNITY
    OB = objects(I, T, F, T)
    bigger = sfilter(OB, compose(rbind(greater, ONE), size))
    MER = merge(bigger)
    ZC = canvas(ZERO, shape(I))
    Filt = paint(ZC, MER)
    D = downscale(Filt, TEN)
    nz = difference(asindices(D), ofcolor(D, ZERO))
    O = subgrid(nz, D)
    return O

def dsl4(I):
    # Geometric sampling per tile: 5-point cross vote around tile center
    z = ZERO; t = TEN; tt = double(TEN); U = UNITY
    # centers
    r0 = add(z, FIVE); r1 = add(t, FIVE); r2 = add(tt, FIVE)
    c0 = add(z, FIVE); c1 = add(t, FIVE); c2 = add(tt, FIVE)
    def at(r,c): return index(I, astuple(r,c))
    def vote5(r,c):
        a = at(r, c)
        b = at(decrement(r), c)
        d = at(increment(r), c)
        e = at(r, decrement(c))
        f = at(r, increment(c))
        row = hconcat(canvas(a,U), hconcat(canvas(b,U), canvas(d,U)))
        row2 = hconcat(canvas(e,U), canvas(f,U))
        mix = hconcat(row, row2)
        return mostcolor(mix)
    c00 = vote5(r0, c0); c01 = vote5(r0, c1); c02 = vote5(r0, c2)
    c10 = vote5(r1, c0); c11 = vote5(r1, c1); c12 = vote5(r1, c2)
    c20 = vote5(r2, c0); c21 = vote5(r2, c1); c22 = vote5(r2, c2)
    rA = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    rB = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    rC = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(rA, vconcat(rB, rC))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O

def dsl5(I):
    # Relational/structural: per tile, choose the object closest to the tile's center cross (argmin manhattan), use its color
    z = ZERO; t = TEN; tt = double(TEN); U = UNITY
    d10 = astuple(TEN, TEN)
    # tiles and center-cross patches
    def tile_and_cross(r0, c0):
        T = crop(I, astuple(r0,c0), d10)
        cr = add(r0, FIVE); cc = add(c0, FIVE)
        p = astuple(cr, cc)
        up = shoot(p, UP); dn = shoot(p, DOWN); lf = shoot(p, LEFT); rt = shoot(p, RIGHT)
        cross = merge(initset(up) | initset(dn) | initset(lf) | initset(rt))
        return T, cross
    T00, X00 = tile_and_cross(z, z); T01, X01 = tile_and_cross(z, t); T02, X02 = tile_and_cross(z, tt)
    T10, X10 = tile_and_cross(t, z); T11, X11 = tile_and_cross(t, t); T12, X12 = tile_and_cross(t, tt)
    T20, X20 = tile_and_cross(tt, z); T21, X21 = tile_and_cross(tt, t); T22, X22 = tile_and_cross(tt, tt)
    # nearest-to-cross object color per tile
    def nearcol(T, X):
        OB = objects(T, T, F, T)
        dfunc = rbind(manhattan, X)
        Osel = argmin(OB, dfunc)
        return color(Osel)
    c00 = nearcol(T00, X00); c01 = nearcol(T01, X01); c02 = nearcol(T02, X02)
    c10 = nearcol(T10, X10); c11 = nearcol(T11, X11); c12 = nearcol(T12, X12)
    c20 = nearcol(T20, X20); c21 = nearcol(T21, X21); c22 = nearcol(T22, X22)
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    O = vconcat(r0, vconcat(r1, r2))
    return O
```