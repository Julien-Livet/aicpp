```python
def dsl1(I):
    # Global: downscale by 10 and crop to nonzero bbox
    D = downscale(I, TEN)
    nz = difference(asindices(D), ofcolor(D, ZERO))
    O = subgrid(nz, D)
    return O

def dsl2(I):
    # Object extraction: per tile, pick color of largest object (by area)
    z = ZERO; t = TEN; tt = double(TEN); U = UNITY
    d10 = astuple(TEN, TEN)
    def largest_obj_color(r0, c0):
        T = crop(I, astuple(r0, c0), d10)
        OBJS = objects(T, T, F, T)
        B = argmax(OBJS, compose(size, toindices))
        return color(B)
    c00 = largest_obj_color(z, z);   c01 = largest_obj_color(z, t);   c02 = largest_obj_color(z, tt)
    c10 = largest_obj_color(t, z);   c11 = largest_obj_color(t, t);   c12 = largest_obj_color(t, tt)
    c20 = largest_obj_color(tt, z);  c21 = largest_obj_color(tt, t);  c22 = largest_obj_color(tt, tt)
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O

def dsl3(I):
    # Color filtering: intersect colors from center cross and inner 8x8; fallback to inner if empty
    z = ZERO; t = TEN; tt = double(TEN); U = UNITY
    d10 = astuple(TEN, TEN); off = astuple(ONE, ONE); d8 = astuple(EIGHT, EIGHT)
    def cross_inner_mode(r0, c0):
        T = crop(I, astuple(r0, c0), d10)
        p = astuple(FIVE, FIVE)
        up = shoot(p, UP); dn = shoot(p, DOWN); lf = shoot(p, LEFT); rt = shoot(p, RIGHT)
        X = merge(initset(up) | initset(dn) | initset(lf) | initset(rt))
        PX = toobject(X, T)
        Cx = difference(palette(PX), initset(ZERO))
        C = crop(T, off, d8)
        EC = asobject(C)
        Pc = difference(palette(C), initset(ZERO))
        Cint = intersection(Cx, Pc)
        use = branch(equality(size(Cint), ZERO), Pc, Cint)
        comp = lbind(colorcount, EC)
        return argmax(use, comp)
    c00 = cross_inner_mode(z, z);   c01 = cross_inner_mode(z, t);   c02 = cross_inner_mode(z, tt)
    c10 = cross_inner_mode(t, z);   c11 = cross_inner_mode(t, t);   c12 = cross_inner_mode(t, tt)
    c20 = cross_inner_mode(tt, z);  c21 = cross_inner_mode(tt, t);  c22 = cross_inner_mode(tt, tt)
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O

def dsl4(I):
    # Geometric/relational: pick object whose center-of-mass is closest to tile center
    z = ZERO; t = TEN; tt = double(TEN); U = UNITY
    d10 = astuple(TEN, TEN)
    def nearest_com(r0, c0):
        T = crop(I, astuple(r0, c0), d10)
        p = astuple(FIVE, FIVE)
        Pc = toobject(initset(p), T)
        OB = objects(T, T, F, T)
        g = compose(initset, centerofmass)              # B -> {com(B)}
        h = rbind(toobject, T)                          # S -> toobject(S, T)
        comp = chain(lbind(manhattan, Pc), h, g)        # distance from Pc to com-object in T
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
    # Relational/structural: pick object maximizing overlap with tile border (outline)
    z = ZERO; t = TEN; tt = double(TEN); U = UNITY
    d10 = astuple(TEN, TEN)
    def border_touch_max(r0, c0):
        T = crop(I, astuple(r0, c0), d10)
        OB = objects(T, T, F, T)
        BORDER = box(asindices(T))
        comp = chain(size, lbind(intersection, BORDER), toindices)
        B = argmax(OB, comp)
        return color(B)
    c00 = border_touch_max(z, z);   c01 = border_touch_max(z, t);   c02 = border_touch_max(z, tt)
    c10 = border_touch_max(t, z);   c11 = border_touch_max(t, t);   c12 = border_touch_max(t, tt)
    c20 = border_touch_max(tt, z);  c21 = border_touch_max(tt, t);  c22 = border_touch_max(tt, tt)
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O
```