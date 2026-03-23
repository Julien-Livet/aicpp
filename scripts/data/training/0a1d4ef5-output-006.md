```python
def dsl1(I):
    # Color filtering on center cross per 10x10 tile: nonzero mode on the union of four rays from center
    z = ZERO; t = TEN; tt = double(TEN); U = UNITY
    d10 = astuple(TEN, TEN)
    def cross_nzmode(r0, c0):
        T = crop(I, astuple(r0, c0), d10)
        p = astuple(FIVE, FIVE)
        up = shoot(p, UP); dn = shoot(p, DOWN); lf = shoot(p, LEFT); rt = shoot(p, RIGHT)
        X = merge(initset(up) | initset(dn) | initset(lf) | initset(rt))
        P = toobject(X, T)
        Pnz = difference(palette(P), initset(ZERO))
        comp = lbind(colorcount, P)
        return argmax(Pnz, comp)
    c00 = cross_nzmode(z, z);   c01 = cross_nzmode(z, t);   c02 = cross_nzmode(z, tt)
    c10 = cross_nzmode(t, z);   c11 = cross_nzmode(t, t);   c12 = cross_nzmode(t, tt)
    c20 = cross_nzmode(tt, z);  c21 = cross_nzmode(tt, t);  c22 = cross_nzmode(tt, tt)
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O

def dsl2(I):
    # Object extraction: choose object with maximum overlap with central 8x8 window in each tile
    z = ZERO; t = TEN; tt = double(TEN); U = UNITY
    d10 = astuple(TEN, TEN); off = astuple(ONE, ONE); d8 = astuple(EIGHT, EIGHT)
    def max_overlap_center8(r0, c0):
        T = crop(I, astuple(r0, c0), d10)
        C = crop(T, off, d8)
        X = shift(asindices(C), off)  # central 8x8 indices in tile coords
        OB = objects(T, T, F, T)
        comp = chain(size, lbind(intersection, X), toindices)
        B = argmax(OB, comp)
        return color(B)
    c00 = max_overlap_center8(z, z);   c01 = max_overlap_center8(z, t);   c02 = max_overlap_center8(z, tt)
    c10 = max_overlap_center8(t, z);   c11 = max_overlap_center8(t, t);   c12 = max_overlap_center8(t, tt)
    c20 = max_overlap_center8(tt, z);  c21 = max_overlap_center8(tt, t);  c22 = max_overlap_center8(tt, tt)
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O

def dsl3(I):
    # Geometric line sampling: center horizontal row per tile, nonzero mode
    z = ZERO; t = TEN; tt = double(TEN); U = UNITY
    d10 = astuple(TEN, TEN)
    def center_row_mode(r0, c0):
        T = crop(I, astuple(r0, c0), d10)
        p = astuple(FIVE, FIVE)
        lf = shoot(p, LEFT); rt = shoot(p, RIGHT)
        R = merge(initset(lf) | initset(rt))
        P = toobject(R, T)
        Pnz = difference(palette(P), initset(ZERO))
        comp = lbind(colorcount, P)
        return argmax(Pnz, comp)
    c00 = center_row_mode(z, z);   c01 = center_row_mode(z, t);   c02 = center_row_mode(z, tt)
    c10 = center_row_mode(t, z);   c11 = center_row_mode(t, t);   c12 = center_row_mode(t, tt)
    c20 = center_row_mode(tt, z);  c21 = center_row_mode(tt, t);  c22 = center_row_mode(tt, tt)
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O

def dsl4(I):
    # Relational: pick the object whose center-of-mass is closest to the tile center
    z = ZERO; t = TEN; tt = double(TEN); U = UNITY
    d10 = astuple(TEN, TEN)
    def nearest_com(r0, c0):
        T = crop(I, astuple(r0, c0), d10)
        p = astuple(FIVE, FIVE)
        Pc = toobject(initset(p), T)
        OB = objects(T, T, F, T)
        g = compose(initset, centerofmass)                 # B -> {com(B)}
        h = lbind(toobject, T)                             # S -> toobject(S, T)
        comp = chain(lbind(manhattan, Pc), h, g)           # distance from Pc to com-object
        B = argmin(OB, comp)
        return color(B)
    c00 = nearest_com(z, z);   c01 = nearest_com(z, t);   c02 = nearest_com(z, tt)
    c10 = nearest_com(t, z);   c11 = nearest_com(t, t);   c12 = nearest_com(t, tt)
    c20 = nearest_com(tt, z);  c21 = nearest_com(tt, t);  c22 = nearest_com(tt, tt)
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O

def dsl5(I):
    # Global sampling: central 8x8 nonzero mode per 10x10 tile
    z = ZERO; t = TEN; tt = double(TEN); U = UNITY
    d10 = astuple(TEN, TEN); off = astuple(ONE, ONE); d8 = astuple(EIGHT, EIGHT)
    def inner8_nzmode(r0, c0):
        T = crop(I, astuple(r0, c0), d10)
        C = crop(T, off, d8)
        E = asobject(C)
        Pnz = difference(palette(C), initset(ZERO))
        comp = lbind(colorcount, E)
        return argmax(Pnz, comp)
    c00 = inner8_nzmode(z, z);   c01 = inner8_nzmode(z, t);   c02 = inner8_nzmode(z, tt)
    c10 = inner8_nzmode(t, z);   c11 = inner8_nzmode(t, t);   c12 = inner8_nzmode(t, tt)
    c20 = inner8_nzmode(tt, z);  c21 = inner8_nzmode(tt, t);  c22 = inner8_nzmode(tt, tt)
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O
```