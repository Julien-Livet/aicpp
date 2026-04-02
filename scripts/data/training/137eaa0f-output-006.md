```python
def dsl1(I):
    # Global 3x3 pooling on bbox: majority color (including zero) per bin
    fg = difference(asindices(I), ofcolor(I, ZERO))
    BB = subgrid(fg, I)
    H = height(BB); W = width(BB)
    h1 = divide(H, THREE); h2 = divide(H, THREE); h12 = add(h1, h2); h3 = subtract(H, h12)
    w1 = divide(W, THREE); w2 = divide(W, THREE); w12 = add(w1, w2); w3 = subtract(W, w12)
    sr1 = ORIGIN; sr2 = toivec(h1); sr3 = toivec(h12)
    sc1 = ORIGIN; sc2 = tojvec(w1); sc3 = tojvec(w12)
    G11 = crop(BB, add(sr1, sc1), astuple(h1, w1))
    G12 = crop(BB, add(sr1, sc2), astuple(h1, w2))
    G13 = crop(BB, add(sr1, sc3), astuple(h1, w3))
    G21 = crop(BB, add(sr2, sc1), astuple(h2, w1))
    G22 = crop(BB, add(sr2, sc2), astuple(h2, w2))
    G23 = crop(BB, add(sr2, sc3), astuple(h2, w3))
    G31 = crop(BB, add(sr3, sc1), astuple(h3, w1))
    G32 = crop(BB, add(sr3, sc2), astuple(h3, w2))
    G33 = crop(BB, add(sr3, sc3), astuple(h3, w3))
    pick = mostcolor
    v11 = pick(G11); v12 = pick(G12); v13 = pick(G13)
    v21 = pick(G21); v22 = pick(G22); v23 = pick(G23)
    v31 = pick(G31); v32 = pick(G32); v33 = pick(G33)
    r1 = hconcat(hconcat(canvas(v11, UNITY), canvas(v12, UNITY)), canvas(v13, UNITY))
    r2 = hconcat(hconcat(canvas(v21, UNITY), canvas(v22, UNITY)), canvas(v23, UNITY))
    r3 = hconcat(hconcat(canvas(v31, UNITY), canvas(v32, UNITY)), canvas(v33, UNITY))
    O = vconcat(vconcat(r1, r2), r3)
    return O

def dsl2(I):
    # Object extraction per 3x3 bin: color of largest nonzero object (safe fallback with dummy zero object)
    fg = difference(asindices(I), ofcolor(I, ZERO))
    BB = subgrid(fg, I)
    H = height(BB); W = width(BB)
    h1 = divide(H, THREE); h2 = divide(H, THREE); h12 = add(h1, h2); h3 = subtract(H, h12)
    w1 = divide(W, THREE); w2 = divide(W, THREE); w12 = add(w1, w2); w3 = subtract(W, w12)
    sr1 = ORIGIN; sr2 = toivec(h1); sr3 = toivec(h12)
    sc1 = ORIGIN; sc2 = tojvec(w1); sc3 = tojvec(w12)
    Gs = (
        crop(BB, add(sr1, sc1), astuple(h1, w1)),
        crop(BB, add(sr1, sc2), astuple(h1, w2)),
        crop(BB, add(sr1, sc3), astuple(h1, w3)),
        crop(BB, add(sr2, sc1), astuple(h2, w1)),
        crop(BB, add(sr2, sc2), astuple(h2, w2)),
        crop(BB, add(sr2, sc3), astuple(h2, w3)),
        crop(BB, add(sr3, sc1), astuple(h3, w1)),
        crop(BB, add(sr3, sc2), astuple(h3, w2)),
        crop(BB, add(sr3, sc3), astuple(h3, w3)),
    )
    dummy = initset(asobject(canvas(ZERO, UNITY)))
    choose = lambda G: color(argmax(combine(fgpartition(G), dummy), size))
    vals = tuple(apply(choose, Gs))
    r1 = hconcat(hconcat(canvas(vals[0], UNITY), canvas(vals[1], UNITY)), canvas(vals[2], UNITY))
    r2 = hconcat(hconcat(canvas(vals[3], UNITY), canvas(vals[4], UNITY)), canvas(vals[5], UNITY))
    r3 = hconcat(hconcat(canvas(vals[6], UNITY), canvas(vals[7], UNITY)), canvas(vals[8], UNITY))
    O = vconcat(vconcat(r1, r2), r3)
    return O

def dsl3(I):
    # Color filtering per 3x3 bin: maximum nonzero color (fallback 0) per bin
    fg = difference(asindices(I), ofcolor(I, ZERO))
    BB = subgrid(fg, I)
    H = height(BB); W = width(BB)
    h1 = divide(H, THREE); h2 = divide(H, THREE); h12 = add(h1, h2); h3 = subtract(H, h12)
    w1 = divide(W, THREE); w2 = divide(W, THREE); w12 = add(w1, w2); w3 = subtract(W, w12)
    sr1 = ORIGIN; sr2 = toivec(h1); sr3 = toivec(h12)
    sc1 = ORIGIN; sc2 = tojvec(w1); sc3 = tojvec(w12)
    Gs = (
        crop(BB, add(sr1, sc1), astuple(h1, w1)),
        crop(BB, add(sr1, sc2), astuple(h1, w2)),
        crop(BB, add(sr1, sc3), astuple(h1, w3)),
        crop(BB, add(sr2, sc1), astuple(h2, w1)),
        crop(BB, add(sr2, sc2), astuple(h2, w2)),
        crop(BB, add(sr2, sc3), astuple(h2, w3)),
        crop(BB, add(sr3, sc1), astuple(h3, w1)),
        crop(BB, add(sr3, sc2), astuple(h3, w2)),
        crop(BB, add(sr3, sc3), astuple(h3, w3)),
    )
    mxnz = lambda G: maximum(combine(remove(ZERO, palette(G)), initset(ZERO)))
    vals = tuple(apply(mxnz, Gs))
    r1 = hconcat(hconcat(canvas(vals[0], UNITY), canvas(vals[1], UNITY)), canvas(vals[2], UNITY))
    r2 = hconcat(hconcat(canvas(vals[3], UNITY), canvas(vals[4], UNITY)), canvas(vals[5], UNITY))
    r3 = hconcat(hconcat(canvas(vals[6], UNITY), canvas(vals[7], UNITY)), canvas(vals[8], UNITY))
    O = vconcat(vconcat(r1, r2), r3)
    return O

def dsl4(I):
    # Geometric sampling: colors at intersections of extreme rows/cols (top/mid/bottom x left/mid/right)
    FG = difference(asindices(I), ofcolor(I, ZERO))
    r1 = uppermost(FG); r3 = lowermost(FG); r2 = divide(add(r1, r3), TWO)
    c1 = leftmost(FG); c3 = rightmost(FG); c2 = divide(add(c1, c3), TWO)
    s = lambda r, c: index(I, astuple(r, c))
    v11 = s(r1, c1); v12 = s(r1, c2); v13 = s(r1, c3)
    v21 = s(r2, c1); v22 = s(r2, c2); v23 = s(r2, c3)
    v31 = s(r3, c1); v32 = s(r3, c2); v33 = s(r3, c3)
    r_1 = hconcat(hconcat(canvas(v11, UNITY), canvas(v12, UNITY)), canvas(v13, UNITY))
    r_2 = hconcat(hconcat(canvas(v21, UNITY), canvas(v22, UNITY)), canvas(v23, UNITY))
    r_3 = hconcat(hconcat(canvas(v31, UNITY), canvas(v32, UNITY)), canvas(v33, UNITY))
    O = vconcat(vconcat(r_1, r_2), r_3)
    return O

def dsl5(I):
    # Relational: majority per row segments anchored at global left/mid/right columns on top/mid/bottom rows
    FG = difference(asindices(I), ofcolor(I, ZERO))
    H = height(I); W = width(I)
    r1 = uppermost(FG); r3 = lowermost(FG); r2 = divide(add(r1, r3), TWO)
    c1 = leftmost(FG); c3 = rightmost(FG); c2 = divide(add(c1, c3), TWO)
    R1 = crop(I, astuple(r1, 0), astuple(1, W))
    R2 = crop(I, astuple(r2, 0), astuple(1, W))
    R3 = crop(I, astuple(r3, 0), astuple(1, W))
    w12 = increment(subtract(c2, c1))
    w23 = increment(subtract(c3, c2))
    w3e = subtract(W, c3)
    segs = (
        crop(R1, astuple(0, c1), astuple(1, w12)),
        crop(R1, astuple(0, c2), astuple(1, w23)),
        crop(R1, astuple(0, c3), astuple(1, w3e)),
        crop(R2, astuple(0, c1), astuple(1, w12)),
        crop(R2, astuple(0, c2), astuple(1, w23)),
        crop(R2, astuple(0, c3), astuple(1, w3e)),
        crop(R3, astuple(0, c1), astuple(1, w12)),
        crop(R3, astuple(0, c2), astuple(1, w23)),
        crop(R3, astuple(0, c3), astuple(1, w3e)),
    )
    vals = tuple(apply(mostcolor, segs))
    r_1 = hconcat(hconcat(canvas(vals[0], UNITY), canvas(vals[1], UNITY)), canvas(vals[2], UNITY))
    r_2 = hconcat(hconcat(canvas(vals[3], UNITY), canvas(vals[4], UNITY)), canvas(vals[5], UNITY))
    r_3 = hconcat(hconcat(canvas(vals[6], UNITY), canvas(vals[7], UNITY)), canvas(vals[8], UNITY))
    O = vconcat(vconcat(r_1, r_2), r_3)
    return O
```