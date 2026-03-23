```python
def dsl1(I):
    # Global downscale by 10 with nonzero cropping
    G = downscale(I, TEN)
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O

def dsl2(I):
    # Tilewise central 6x6 majority color
    z = ZERO; t = TEN; tt = double(TEN); U = UNITY
    d10 = astuple(TEN, TEN)
    d6 = astuple(SIX, SIX)
    off = astuple(TWO, TWO)
    def cmaj(r0, c0):
        T = crop(I, astuple(r0, c0), d10)
        C = crop(T, off, d6)
        return mostcolor(C)
    c00 = cmaj(z, z);   c01 = cmaj(z, t);   c02 = cmaj(z, tt)
    c10 = cmaj(t, z);   c11 = cmaj(t, t);   c12 = cmaj(t, tt)
    c20 = cmaj(tt, z);  c21 = cmaj(tt, t);  c22 = cmaj(tt, tt)
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O

def dsl3(I):
    # Tilewise largest object (object extraction)
    z = ZERO; t = TEN; tt = double(TEN); U = UNITY
    d10 = astuple(TEN, TEN)
    def largobjcol(r0, c0):
        T = crop(I, astuple(r0, c0), d10)
        OB = objects(T, T, F, T)
        B = argmax(OB, size)
        return color(B)
    c00 = largobjcol(z, z);   c01 = largobjcol(z, t);   c02 = largobjcol(z, tt)
    c10 = largobjcol(t, z);   c11 = largobjcol(t, t);   c12 = largobjcol(t, tt)
    c20 = largobjcol(tt, z);  c21 = largobjcol(tt, t);  c22 = largobjcol(tt, tt)
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O

def dsl4(I):
    # Geometric: 3x3 neighborhood vote around tile center
    z = ZERO; t = TEN; tt = double(TEN); U = UNITY
    d10 = astuple(TEN, TEN)
    def sample(T, p):
        return color(toobject(initset(p), T))
    def vote9(r0, c0):
        T = crop(I, astuple(r0, c0), d10)
        p = astuple(FIVE, FIVE)
        a = sample(T, p)
        b = sample(T, add(p, UP))
        c = sample(T, add(p, DOWN))
        d = sample(T, add(p, LEFT))
        e = sample(T, add(p, RIGHT))
        f = sample(T, add(p, UP_RIGHT))
        g = sample(T, add(p, UP_LEFT))
        h = sample(T, add(p, DOWN_RIGHT))
        i = sample(T, add(p, DOWN_LEFT))
        rA = hconcat(canvas(g,U), hconcat(canvas(b,U), canvas(f,U)))
        rB = hconcat(canvas(d,U), hconcat(canvas(a,U), canvas(e,U)))
        rC = hconcat(canvas(i,U), hconcat(canvas(c,U), canvas(h,U)))
        mix = vconcat(rA, vconcat(rB, rC))
        return mostcolor(mix)
    c00 = vote9(z, z);   c01 = vote9(z, t);   c02 = vote9(z, tt)
    c10 = vote9(t, z);   c11 = vote9(t, t);   c12 = vote9(t, tt)
    c20 = vote9(tt, z);  c21 = vote9(tt, t);  c22 = vote9(tt, tt)
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O

def dsl5(I):
    # Relational: color with max frequency on center cross within each tile
    z = ZERO; t = TEN; tt = double(TEN); U = UNITY
    d10 = astuple(TEN, TEN)
    def crosscol(r0, c0):
        T = crop(I, astuple(r0, c0), d10)
        p = astuple(FIVE, FIVE)
        up = shoot(p, UP); dn = shoot(p, DOWN); lf = shoot(p, LEFT); rt = shoot(p, RIGHT)
        X = merge(initset(up) | initset(dn) | initset(lf) | initset(rt))
        E = toobject(X, T)
        P = palette(T)
        comp = rbind(colorcount, E)
        return argmax(P, comp)
    c00 = crosscol(z, z);   c01 = crosscol(z, t);   c02 = crosscol(z, tt)
    c10 = crosscol(t, z);   c11 = crosscol(t, t);   c12 = crosscol(t, tt)
    c20 = crosscol(tt, z);  c21 = crosscol(tt, t);  c22 = crosscol(tt, tt)
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O
```