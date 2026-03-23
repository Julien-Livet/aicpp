```python
def dsl1(I):
    z = ZERO; t = TEN; tt = double(TEN); U = UNITY
    d8 = astuple(EIGHT, EIGHT)
    def tilecol(r0, c0):
        return mostcolor(crop(I, add(astuple(r0, c0), U), d8))
    c00 = tilecol(z, z);   c01 = tilecol(z, t);   c02 = tilecol(z, tt)
    c10 = tilecol(t, z);   c11 = tilecol(t, t);   c12 = tilecol(t, tt)
    c20 = tilecol(tt, z);  c21 = tilecol(tt, t);  c22 = tilecol(tt, tt)
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O

def dsl2(I):
    z = ZERO; t = TEN; tt = double(TEN); U = UNITY
    d10 = astuple(TEN, TEN)
    def bestcolor(r0, c0):
        T = crop(I, astuple(r0, c0), d10)
        OB = objects(T, T, F, T)
        H = multiply(TEN, TEN)
        pen = compose(lbind(multiply, H), rbind(bordering, T))
        comp = fork(subtract, size, pen)
        B = argmax(OB, comp)
        return color(B)
    c00 = bestcolor(z, z);   c01 = bestcolor(z, t);   c02 = bestcolor(z, tt)
    c10 = bestcolor(t, z);   c11 = bestcolor(t, t);   c12 = bestcolor(t, tt)
    c20 = bestcolor(tt, z);  c21 = bestcolor(tt, t);  c22 = bestcolor(tt, tt)
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O

def dsl3(I):
    z = ZERO; t = TEN; tt = double(TEN); U = UNITY
    d10 = astuple(TEN, TEN)
    def maj_nonzero(r0, c0):
        T = crop(I, astuple(r0, c0), d10)
        P = palette(T)
        Pn = remove(ZERO, P)
        Cset = combine(Pn, initset(ZERO))
        comp = rbind(colorcount, T)
        return argmax(Cset, comp)
    c00 = maj_nonzero(z, z);   c01 = maj_nonzero(z, t);   c02 = maj_nonzero(z, tt)
    c10 = maj_nonzero(t, z);   c11 = maj_nonzero(t, t);   c12 = maj_nonzero(t, tt)
    c20 = maj_nonzero(tt, z);  c21 = maj_nonzero(tt, t);  c22 = maj_nonzero(tt, tt)
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O

def dsl4(I):
    z = ZERO; t = TEN; tt = double(TEN); U = UNITY
    r0 = add(z, FIVE); r1 = add(t, FIVE); r2 = add(tt, FIVE)
    c0 = add(z, FIVE); c1 = add(t, FIVE); c2 = add(tt, FIVE)
    def sample_color(r, c):
        pt = initset(astuple(r, c))
        return color(toobject(pt, I))
    def vote5(r, c):
        a = sample_color(r, c)
        b = sample_color(decrement(r), c)
        d = sample_color(increment(r), c)
        e = sample_color(r, decrement(c))
        f = sample_color(r, increment(c))
        row = hconcat(canvas(a,U), hconcat(canvas(b,U), canvas(d,U)))
        row2 = hconcat(canvas(e,U), canvas(f,U))
        mix = hconcat(row, row2)
        return mostcolor(mix)
    c00 = vote5(r0,c0); c01 = vote5(r0,c1); c02 = vote5(r0,c2)
    c10 = vote5(r1,c0); c11 = vote5(r1,c1); c12 = vote5(r1,c2)
    c20 = vote5(r2,c0); c21 = vote5(r2,c1); c22 = vote5(r2,c2)
    rA = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    rB = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    rC = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(rA, vconcat(rB, rC))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O

def dsl5(I):
    z = ZERO; t = TEN; tt = double(TEN); U = UNITY
    d10 = astuple(TEN, TEN)
    def nearcol(r0, c0):
        T = crop(I, astuple(r0, c0), d10)
        p = astuple(FIVE, FIVE)
        up = shoot(p, UP); dn = shoot(p, DOWN); lf = shoot(p, LEFT); rt = shoot(p, RIGHT)
        X = merge(initset(up) | initset(dn) | initset(lf) | initset(rt))
        OB = objects(T, T, F, T)
        dfunc = rbind(manhattan, X)
        Osel = argmin(OB, dfunc)
        return color(Osel)
    c00 = nearcol(z, z);   c01 = nearcol(z, t);   c02 = nearcol(z, tt)
    c10 = nearcol(t, z);   c11 = nearcol(t, t);   c12 = nearcol(t, tt)
    c20 = nearcol(tt, z);  c21 = nearcol(tt, t);  c22 = nearcol(tt, tt)
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O
```