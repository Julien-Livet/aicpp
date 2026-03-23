```python
def dsl1(I):
    # Global: remove 1-cell frame then downscale by 8 to a 3x3 summary; crop to nonzero bbox
    U = UNITY; TW = TWO_BY_TWO
    dims = shape(I)
    inner_dims = subtract(dims, TW)
    C = crop(I, U, inner_dims)
    D = downscale(C, EIGHT)
    nz = difference(asindices(D), ofcolor(D, ZERO))
    O = subgrid(nz, D)
    return O

def dsl2(I):
    # Object extraction via color filtering: exclude colors present on the tile border, fallback to inner palette
    z = ZERO; t = TEN; tt = double(TEN); U = UNITY
    d10 = astuple(TEN, TEN); off = UNITY; d8 = astuple(EIGHT, EIGHT)
    def noborder_mode(r0, c0):
        T = crop(I, astuple(r0, c0), d10)
        C = crop(T, off, d8)
        EC = asobject(C)
        BORDER = box(asindices(T))
        BOBJ = toobject(BORDER, T)
        Bcols = difference(palette(BOBJ), initset(ZERO))
        Pc0 = difference(difference(palette(EC), initset(ZERO)), Bcols)
        PcF = difference(palette(EC), initset(ZERO))
        use = branch(equality(size(Pc0), ZERO), PcF, Pc0)
        comp = lbind(colorcount, EC)
        return argmax(use, comp)
    c00 = noborder_mode(z, z);   c01 = noborder_mode(z, t);   c02 = noborder_mode(z, tt)
    c10 = noborder_mode(t, z);   c11 = noborder_mode(t, t);   c12 = noborder_mode(t, tt)
    c20 = noborder_mode(tt, z);  c21 = noborder_mode(tt, t);  c22 = noborder_mode(tt, tt)
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O

def dsl3(I):
    # Color filtering by bilateral symmetry: intersect colors from left/right halves of inner 8x8; fallback to inner palette
    z = ZERO; t = TEN; tt = double(TEN); U = UNITY
    d10 = astuple(TEN, TEN); off = UNITY; d8 = astuple(EIGHT, EIGHT)
    def bilateral_mode(r0, c0):
        T = crop(I, astuple(r0, c0), d10)
        C = crop(T, off, d8)
        EC = asobject(C)
        L = lefthalf(C); R = righthalf(C)
        PcL = palette(L); PcR = palette(R)
        PcI = difference(intersection(PcL, PcR), initset(ZERO))
        PcF = difference(palette(EC), initset(ZERO))
        use = branch(equality(size(PcI), ZERO), PcF, PcI)
        comp = lbind(colorcount, EC)
        return argmax(use, comp)
    c00 = bilateral_mode(z, z);   c01 = bilateral_mode(z, t);   c02 = bilateral_mode(z, tt)
    c10 = bilateral_mode(t, z);   c11 = bilateral_mode(t, t);   c12 = bilateral_mode(t, tt)
    c20 = bilateral_mode(tt, z);  c21 = bilateral_mode(tt, t);  c22 = bilateral_mode(tt, tt)
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O

def dsl4(I):
    # Geometric: per tile, choose color whose center-of-mass is closest to the inner-8x8 center
    z = ZERO; t = TEN; tt = double(TEN); U = UNITY
    d10 = astuple(TEN, TEN); off = UNITY; d8 = astuple(EIGHT, EIGHT)
    def color_nearest_center(r0, c0):
        T = crop(I, astuple(r0, c0), d10)
        C = crop(T, off, d8)
        p = astuple(FOUR, FOUR)
        Pc0 = toobject(initset(p), C)
        Pc = difference(palette(C), initset(ZERO))
        ofc = lbind(ofcolor, C)                 # c -> indices in C
        toc = rbind(toobject, C)                # S -> object in C
        ocf = compose(toc, ofc)                 # c -> object in C
        g = compose(initset, centerofmass)      # obj -> {com(obj)}
        k = compose(g, ocf)                     # c -> {com(color c in C)}
        comp = compose(lbind(manhattan, Pc0), k)
        return argmin(Pc, comp)
    c00 = color_nearest_center(z, z);   c01 = color_nearest_center(z, t);   c02 = color_nearest_center(z, tt)
    c10 = color_nearest_center(t, z);   c11 = color_nearest_center(t, t);   c12 = color_nearest_center(t, tt)
    c20 = color_nearest_center(tt, z);  c21 = color_nearest_center(tt, t);  c22 = color_nearest_center(tt, tt)
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O

def dsl5(I):
    # Relational/structural: maximize overlap with the central 4x4 box of each 10x10 tile
    z = ZERO; t = TEN; tt = double(TEN); U = UNITY
    d10 = astuple(TEN, TEN); c4 = astuple(FOUR, FOUR); s33 = astuple(THREE, THREE)
    def central_box_mode(r0, c0):
        T = crop(I, astuple(r0, c0), d10)
        B = crop(T, s33, c4)
        EB = asobject(B)
        Pc = difference(palette(EB), initset(ZERO))
        comp = lbind(colorcount, EB)
        return argmax(Pc, comp)
    c00 = central_box_mode(z, z);   c01 = central_box_mode(z, t);   c02 = central_box_mode(z, tt)
    c10 = central_box_mode(t, z);   c11 = central_box_mode(t, t);   c12 = central_box_mode(t, tt)
    c20 = central_box_mode(tt, z);  c21 = central_box_mode(tt, t);  c22 = central_box_mode(tt, tt)
    r0 = hconcat(canvas(c00,U), hconcat(canvas(c01,U), canvas(c02,U)))
    r1 = hconcat(canvas(c10,U), hconcat(canvas(c11,U), canvas(c12,U)))
    r2 = hconcat(canvas(c20,U), hconcat(canvas(c21,U), canvas(c22,U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O
```