```python
def dsl1(I):
    # Global 3x3 tiling summary via mostcolor per 10x10 tile, then crop zero rows/cols
    d10 = astuple(TEN, TEN)
    z = ZERO
    t = TEN
    tt = double(TEN)
    # tiles
    T00 = crop(I, astuple(z, z), d10)
    T01 = crop(I, astuple(z, t), d10)
    T02 = crop(I, astuple(z, tt), d10)
    T10 = crop(I, astuple(t, z), d10)
    T11 = crop(I, astuple(t, t), d10)
    T12 = crop(I, astuple(t, tt), d10)
    T20 = crop(I, astuple(tt, z), d10)
    T21 = crop(I, astuple(tt, t), d10)
    T22 = crop(I, astuple(tt, tt), d10)
    # colors
    c00 = mostcolor(T00); c01 = mostcolor(T01); c02 = mostcolor(T02)
    c10 = mostcolor(T10); c11 = mostcolor(T11); c12 = mostcolor(T12)
    c20 = mostcolor(T20); c21 = mostcolor(T21); c22 = mostcolor(T22)
    # assemble 3x3
    U = UNITY
    r0 = hconcat(canvas(c00, U), hconcat(canvas(c01, U), canvas(c02, U)))
    r1 = hconcat(canvas(c10, U), hconcat(canvas(c11, U), canvas(c12, U)))
    r2 = hconcat(canvas(c20, U), hconcat(canvas(c21, U), canvas(c22, U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O

def dsl2(I):
    # Geometric robustness: use central 8x8 of each 10x10 tile before mostcolor, then crop zeros
    d8 = astuple(EIGHT, EIGHT)
    z = ZERO
    t = TEN
    tt = double(TEN)
    o = ONE
    # starts for central 8x8 in each 10x10 tile
    s00 = astuple(o, o)
    s01 = astuple(o, add(t, o))
    s02 = astuple(o, add(tt, o))
    s10 = astuple(add(t, o), o)
    s11 = astuple(add(t, o), add(t, o))
    s12 = astuple(add(t, o), add(tt, o))
    s20 = astuple(add(tt, o), o)
    s21 = astuple(add(tt, o), add(t, o))
    s22 = astuple(add(tt, o), add(tt, o))
    # tiles (central 8x8)
    T00 = crop(I, s00, d8)
    T01 = crop(I, s01, d8)
    T02 = crop(I, s02, d8)
    T10 = crop(I, s10, d8)
    T11 = crop(I, s11, d8)
    T12 = crop(I, s12, d8)
    T20 = crop(I, s20, d8)
    T21 = crop(I, s21, d8)
    T22 = crop(I, s22, d8)
    # colors
    c00 = mostcolor(T00); c01 = mostcolor(T01); c02 = mostcolor(T02)
    c10 = mostcolor(T10); c11 = mostcolor(T11); c12 = mostcolor(T12)
    c20 = mostcolor(T20); c21 = mostcolor(T21); c22 = mostcolor(T22)
    # assemble and crop zeros
    U = UNITY
    r0 = hconcat(canvas(c00, U), hconcat(canvas(c01, U), canvas(c02, U)))
    r1 = hconcat(canvas(c10, U), hconcat(canvas(c11, U), canvas(c12, U)))
    r2 = hconcat(canvas(c20, U), hconcat(canvas(c21, U), canvas(c22, U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O

def dsl3(I):
    # Color filtering before coarse downscaling: suppress color FIVE noise, then downscale and crop
    F = replace(I, FIVE, ZERO)
    D = downscale(F, TEN)
    nz = difference(asindices(D), ofcolor(D, ZERO))
    O = subgrid(nz, D)
    return O

def dsl4(I):
    # Geometric sampling: take the color at the center of each 10x10 tile, assemble 3x3, crop zeros
    f = FIVE
    t = TEN
    tt = double(TEN)
    # centers
    r0 = f; r1 = add(t, f); r2 = add(tt, f)
    c0 = f; c1 = add(t, f); c2 = add(tt, f)
    # sampled colors
    c00 = index(I, astuple(r0, c0)); c01 = index(I, astuple(r0, c1)); c02 = index(I, astuple(r0, c2))
    c10 = index(I, astuple(r1, c0)); c11 = index(I, astuple(r1, c1)); c12 = index(I, astuple(r1, c2))
    c20 = index(I, astuple(r2, c0)); c21 = index(I, astuple(r2, c1)); c22 = index(I, astuple(r2, c2))
    # assemble and crop zeros
    U = UNITY
    row0 = hconcat(canvas(c00, U), hconcat(canvas(c01, U), canvas(c02, U)))
    row1 = hconcat(canvas(c10, U), hconcat(canvas(c11, U), canvas(c12, U)))
    row2 = hconcat(canvas(c20, U), hconcat(canvas(c21, U), canvas(c22, U)))
    G = vconcat(row0, vconcat(row1, row2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O

def dsl5(I):
    # Relational per-tile adjustment: swap ZERO with tile's leastcolor, then mostcolor per tile
    d10 = astuple(TEN, TEN)
    z = ZERO
    t = TEN
    tt = double(TEN)
    # tiles
    A00 = crop(I, astuple(z, z), d10)
    A01 = crop(I, astuple(z, t), d10)
    A02 = crop(I, astuple(z, tt), d10)
    A10 = crop(I, astuple(t, z), d10)
    A11 = crop(I, astuple(t, t), d10)
    A12 = crop(I, astuple(t, tt), d10)
    A20 = crop(I, astuple(tt, z), d10)
    A21 = crop(I, astuple(tt, t), d10)
    A22 = crop(I, astuple(tt, tt), d10)
    # swap zero with tile's leastcolor to de-emphasize background, then take mostcolor
    B00 = switch(A00, z, leastcolor(A00)); c00 = mostcolor(B00)
    B01 = switch(A01, z, leastcolor(A01)); c01 = mostcolor(B01)
    B02 = switch(A02, z, leastcolor(A02)); c02 = mostcolor(B02)
    B10 = switch(A10, z, leastcolor(A10)); c10 = mostcolor(B10)
    B11 = switch(A11, z, leastcolor(A11)); c11 = mostcolor(B11)
    B12 = switch(A12, z, leastcolor(A12)); c12 = mostcolor(B12)
    B20 = switch(A20, z, leastcolor(A20)); c20 = mostcolor(B20)
    B21 = switch(A21, z, leastcolor(A21)); c21 = mostcolor(B21)
    B22 = switch(A22, z, leastcolor(A22)); c22 = mostcolor(B22)
    # assemble and crop zeros
    U = UNITY
    r0 = hconcat(canvas(c00, U), hconcat(canvas(c01, U), canvas(c02, U)))
    r1 = hconcat(canvas(c10, U), hconcat(canvas(c11, U), canvas(c12, U)))
    r2 = hconcat(canvas(c20, U), hconcat(canvas(c21, U), canvas(c22, U)))
    G = vconcat(r0, vconcat(r1, r2))
    nz = difference(asindices(G), ofcolor(G, ZERO))
    O = subgrid(nz, G)
    return O
```