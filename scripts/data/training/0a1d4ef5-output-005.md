```python
def dsl1(I):
    # Global: per-tile central 8x8 majority color
    z = ZERO; t = TEN; tt = double(TEN); U = UNITY
    d10 = astuple(TEN, TEN)
    off = astuple(ONE, ONE)
    d8 = astuple(EIGHT, EIGHT)
    def cenmaj(r0, c0):
        T = crop(I, astuple(r0, c0), d10)
        C = crop(T, off, d8)
        return mostcolor(C)
    c00 = cenmaj(z, z);   c01 = cenmaj(z, t);   c02 = cenmaj(z, tt)
    c10 = cenmaj(t, z);   c11 = cenmaj(t, t);   c12 = cenmaj(t, tt)
    c20 = cenmaj(tt, z);  c21 = cenmaj(tt, t);  c22 = cenmaj(tt, tt)
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O

def dsl2(I):
    # Object extraction: choose the object that maximizes overlap with the center cross
    z = ZERO; t = TEN; tt = double(TEN); U = UNITY
    d10 = astuple(TEN, TEN)
    def crossobj(r0, c0):
        T = crop(I, astuple(r0, c0), d10)
        p = astuple(FIVE, FIVE)
        up = shoot(p, UP); dn = shoot(p, DOWN); lf = shoot(p, LEFT); rt = shoot(p, RIGHT)
        X = merge(initset(up) | initset(dn) | initset(lf) | initset(rt))
        OB = objects(T, T, F, T)
        h = compose(lbind(intersection, X), toindices)
        comp = compose(size, h)
        B = argmax(OB, comp)
        return color(B)
    c00 = crossobj(z, z);   c01 = crossobj(z, t);   c02 = crossobj(z, tt)
    c10 = crossobj(t, z);   c11 = crossobj(t, t);   c12 = crossobj(t, tt)
    c20 = crossobj(tt, z);  c21 = crossobj(tt, t);  c22 = crossobj(tt, tt)
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O

def dsl3(I):
    # Color filtering: per-tile nonzero most frequent color
    z = ZERO; t = TEN; tt = double(TEN); U = UNITY
    d10 = astuple(TEN, TEN)
    def nzmode(r0, c0):
        T = crop(I, astuple(r0, c0), d10)
        E = asobject(T)
        P = palette(T)
        Pnz = difference(P, initset(ZERO))
        comp = rbind(colorcount, E)
        return argmax(Pnz, comp)
    c00 = nzmode(z, z);   c01 = nzmode(z, t);   c02 = nzmode(z, tt)
    c10 = nzmode(t, z);   c11 = nzmode(t, t);   c12 = nzmode(t, tt)
    c20 = nzmode(tt, z);  c21 = nzmode(tt, t);  c22 = nzmode(tt, tt)
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O

def dsl4(I):
    # Geometric: sample the center pixel color of each 10x10 tile
    z = ZERO; t = TEN; tt = double(TEN); U = UNITY
    d10 = astuple(TEN, TEN)
    def centersample(r0, c0):
        T = crop(I, astuple(r0, c0), d10)
        p = astuple(FIVE, FIVE)
        return color(toobject(initset(p), T))
    c00 = centersample(z, z);   c01 = centersample(z, t);   c02 = centersample(z, tt)
    c10 = centersample(t, z);   c11 = centersample(t, t);   c12 = centersample(t, tt)
    c20 = centersample(tt, z);  c21 = centersample(tt, t);  c22 = centersample(tt, tt)
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O

def dsl5(I):
    # Relational: pick object nearest to tile center by Manhattan distance
    z = ZERO; t = TEN; tt = double(TEN); U = UNITY
    d10 = astuple(TEN, TEN)
    def nearcenter(r0, c0):
        T = crop(I, astuple(r0, c0), d10)
        p = astuple(FIVE, FIVE)
        P = toobject(initset(p), T)
        OB = objects(T, T, F, T)
        comp = lbind(manhattan, P)
        B = argmin(OB, comp)
        return color(B)
    c00 = nearcenter(z, z);   c01 = nearcenter(z, t);   c02 = nearcenter(z, tt)
    c10 = nearcenter(t, z);   c11 = nearcenter(t, t);   c12 = nearcenter(t, tt)
    c20 = nearcenter(tt, z);  c21 = nearcenter(tt, t);  c22 = nearcenter(tt, tt)
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O
```