```python
def dsl1(I):
    # Global 3x3 partition on bbox; pick color at lower-rightmost nonzero per bin (fallback 0 via origin)
    FG = difference(asindices(I), ofcolor(I, ZERO))
    BB = subgrid(FG, I)
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
    pick = lambda G: index(G, lrcorner(toobject(combine(difference(asindices(G), ofcolor(G, ZERO)), initset(ORIGIN)), G)))
    vals = tuple(apply(pick, Gs))
    r1 = hconcat(hconcat(canvas(vals[0], UNITY), canvas(vals[1], UNITY)), canvas(vals[2], UNITY))
    r2 = hconcat(hconcat(canvas(vals[3], UNITY), canvas(vals[4], UNITY)), canvas(vals[5], UNITY))
    r3 = hconcat(hconcat(canvas(vals[6], UNITY), canvas(vals[7], UNITY)), canvas(vals[8], UNITY))
    O = vconcat(vconcat(r1, r2), r3)
    return O

def dsl2(I):
    # Object extraction: pick three horizontal-line objects (size 2 or 3), order by vertical position, sample L/M/R
    FG = difference(asindices(I), ofcolor(I, ZERO))
    allobjs = objects(I, F, F, T)
    hlines = mfilter(allobjs, hline)
    L2 = sizefilter(hlines, TWO)
    L3 = sizefilter(hlines, THREE)
    lines = combine(L2, L3)
    rtop = uppermost(FG); rbot = lowermost(FG); rmid = divide(add(rtop, rbot), TWO)
    midrow = hfrontier(astuple(rmid, ZERO))
    top = argmin(lines, uppermost)
    bot = argmax(lines, lowermost)
    rest = remove(bot, remove(top, lines))
    dist_to_mid = compose(lbind(manhattan, midrow), toindices)
    mid = argmin(rest, dist_to_mid)
    mkrow = lambda o: (
        lambda G, W, c3, c2, v1, v2, v3, r:
            hconcat(hconcat(canvas(v1, UNITY), canvas(v2, UNITY)), canvas(v3, UNITY))
    )(
        subgrid(o, I),
        width(subgrid(o, I)),
        decrement(width(subgrid(o, I))),
        divide(decrement(width(subgrid(o, I))), TWO),
        index(subgrid(o, I), ORIGIN),
        index(subgrid(o, I), astuple(ZERO, divide(decrement(width(subgrid(o, I))), TWO))),
        index(subgrid(o, I), astuple(ZERO, decrement(width(subgrid(o, I))))),
        ZERO
    )
    R_top = mkrow(top)
    R_mid = mkrow(mid)
    R_bot = mkrow(bot)
    O = vconcat(vconcat(R_top, R_mid), R_bot)
    return O

def dsl3(I):
    # Color filtering per 3x3 bin: replace zeros by leastcolor of bbox, then take mostcolor per bin
    FG = difference(asindices(I), ofcolor(I, ZERO))
    BB = subgrid(FG, I)
    base = leastcolor(BB)
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
    choose = lambda G: mostcolor(replace(G, ZERO, base))
    vals = tuple(apply(choose, Gs))
    r1 = hconcat(hconcat(canvas(vals[0], UNITY), canvas(vals[1], UNITY)), canvas(vals[2], UNITY))
    r2 = hconcat(hconcat(canvas(vals[3], UNITY), canvas(vals[4], UNITY)), canvas(vals[5], UNITY))
    r3 = hconcat(hconcat(canvas(vals[6], UNITY), canvas(vals[7], UNITY)), canvas(vals[8], UNITY))
    O = vconcat(vconcat(r1, r2), r3)
    return O

def dsl4(I):
    # Geometric sampling: intersections of extreme rows/cols with midpoint rows/cols
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
    # Relational by vertical slices: in each slice, pick upper/mid/lower rows at the slice's rightmost fg column
    FG = difference(asindices(I), ofcolor(I, ZERO))
    BB = subgrid(FG, I)
    H = height(BB); W = width(BB)
    w1 = divide(W, THREE); w2 = divide(W, THREE); w12 = add(w1, w2); w3 = subtract(W, w12)
    sc1 = ORIGIN; sc2 = tojvec(w1); sc3 = tojvec(w12)
    S1 = crop(BB, add(ORIGIN, sc1), astuple(H, w1))
    S2 = crop(BB, add(ORIGIN, sc2), astuple(H, w2))
    S3 = crop(BB, add(ORIGIN, sc3), astuple(H, w3))
    colpick = lambda S: (
        lambda P, r1, r3, r2, c, v1, v2, v3: vconcat(vconcat(canvas(v1, UNITY), canvas(v2, UNITY)), canvas(v3, UNITY))
    )(
        difference(asindices(S), ofcolor(S, ZERO)),
        uppermost(difference(asindices(S), ofcolor(S, ZERO))),
        lowermost(difference(asindices(S), ofcolor(S, ZERO))),
        divide(add(uppermost(difference(asindices(S), ofcolor(S, ZERO))), lowermost(difference(asindices(S), ofcolor(S, ZERO)))), TWO),
        rightmost(difference(asindices(S), ofcolor(S, ZERO))),
        index(S, astuple(uppermost(difference(asindices(S), ofcolor(S, ZERO))), rightmost(difference(asindices(S), ofcolor(S, ZERO))))),
        index(S, astuple(divide(add(uppermost(difference(asindices(S), ofcolor(S, ZERO))), lowermost(difference(asindices(S), ofcolor(S, ZERO)))), TWO), rightmost(difference(asindices(S), ofcolor(S, ZERO))))),
        index(S, astuple(lowermost(difference(asindices(S), ofcolor(S, ZERO))), rightmost(difference(asindices(S), ofcolor(S, ZERO)))))
    )
    C1 = colpick(S1)
    C2 = colpick(S2)
    C3 = colpick(S3)
    O = hconcat(hconcat(C1, C2), C3)
    return O
```