```python
def dsl1(I):
    # Global 3x3 partition on bbox; per bin pick color at lower-rightmost nonzero (fallback 0)
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
    choose = lambda G: (
        lambda P: branch(
            equality(size(P), ZERO),
            ZERO,
            index(G, lrcorner(toobject(P, G)))
        )
    )(difference(asindices(G), ofcolor(G, ZERO)))
    vals = tuple(apply(choose, Gs))
    r1 = hconcat(hconcat(canvas(vals[0], UNITY), canvas(vals[1], UNITY)), canvas(vals[2], UNITY))
    r2 = hconcat(hconcat(canvas(vals[3], UNITY), canvas(vals[4], UNITY)), canvas(vals[5], UNITY))
    r3 = hconcat(hconcat(canvas(vals[6], UNITY), canvas(vals[7], UNITY)), canvas(vals[8], UNITY))
    O = vconcat(vconcat(r1, r2), r3)
    return O

def dsl2(I):
    # Object extraction: pick three horizontal-line objects (top/mid/bot), sample L/M/R within each row object
    FG = difference(asindices(I), ofcolor(I, ZERO))
    HL = mfilter(objects(I, F, F, T), hline)
    rtop = uppermost(FG); rbot = lowermost(FG); rmid = divide(add(rtop, rbot), TWO)
    midrow = hfrontier(astuple(rmid, ZERO))
    top = argmin(HL, uppermost)
    bot = argmax(HL, lowermost)
    rest = remove(bot, remove(top, HL))
    dist_to_mid = compose(lbind(manhattan, midrow), toindices)
    mid = branch(equality(size(rest), ZERO), top, argmin(rest, dist_to_mid))
    mkrow = lambda o: (
        lambda S, W, j1, j2, j3:
            hconcat(
                hconcat(canvas(index(S, astuple(ZERO, j1)), UNITY),
                        canvas(index(S, astuple(ZERO, j2)), UNITY)),
                canvas(index(S, astuple(ZERO, j3)), UNITY)
            )
    )(
        subgrid(o, I),
        width(subgrid(o, I)),
        ZERO,
        divide(decrement(width(subgrid(o, I))), TWO),
        decrement(width(subgrid(o, I)))
    )
    R_top = mkrow(top)
    R_mid = mkrow(mid)
    R_bot = mkrow(bot)
    O = vconcat(vconcat(R_top, R_mid), R_bot)
    return O

def dsl3(I):
    # Color filtering per horizontal third: pick most common nonzero color in each band (fallback 0), repeat across row
    FG = difference(asindices(I), ofcolor(I, ZERO))
    BB = subgrid(FG, I)
    H = height(BB); W = width(BB)
    h1 = divide(H, THREE); h2 = divide(H, THREE); h12 = add(h1, h2); h3 = subtract(H, h12)
    B1 = crop(BB, ORIGIN, astuple(h1, W))
    B2 = crop(BB, toivec(h1), astuple(h2, W))
    B3 = crop(BB, toivec(h12), astuple(h3, W))
    pickrow = lambda G: (
        lambda pal: branch(
            equality(size(pal), ZERO),
            ZERO,
            argmax(pal, lbind(colorcount, G))
        )
    )(remove(ZERO, palette(G)))
    v1 = pickrow(B1); v2 = pickrow(B2); v3 = pickrow(B3)
    R1 = hconcat(hconcat(canvas(v1, UNITY), canvas(v1, UNITY)), canvas(v1, UNITY))
    R2 = hconcat(hconcat(canvas(v2, UNITY), canvas(v2, UNITY)), canvas(v2, UNITY))
    R3 = hconcat(hconcat(canvas(v3, UNITY), canvas(v3, UNITY)), canvas(v3, UNITY))
    O = vconcat(vconcat(R1, R2), R3)
    return O

def dsl4(I):
    # Geometric: at intersections of extreme/mid rows&cols, choose nearest color-object (by manhattan) and use its color
    FG = difference(asindices(I), ofcolor(I, ZERO))
    r1 = uppermost(FG); r3 = lowermost(FG); r2 = divide(add(r1, r3), TWO)
    c1 = leftmost(FG); c3 = rightmost(FG); c2 = divide(add(c1, c3), TWO)
    FGobjs = fgpartition(I)
    mkcell = lambda r, c: (
        lambda cross, near:
            canvas(color(near), UNITY)
    )(
        intersection(hfrontier(astuple(r, ZERO)), vfrontier(astuple(ZERO, c))),
        argmin(FGobjs, compose(lbind(manhattan, intersection(hfrontier(astuple(r, ZERO)), vfrontier(astuple(ZERO, c)))), toindices))
    )
    R1 = hconcat(hconcat(mkcell(r1, c1), mkcell(r1, c2)), mkcell(r1, c3))
    R2 = hconcat(hconcat(mkcell(r2, c1), mkcell(r2, c2)), mkcell(r2, c3))
    R3 = hconcat(hconcat(mkcell(r3, c1), mkcell(r3, c2)), mkcell(r3, c3))
    O = vconcat(vconcat(R1, R2), R3)
    return O

def dsl5(I):
    # Relational by vertical slices: per slice pick top/mid/bot rows; for each row take rightmost fg in that row (fallback 0)
    FG = difference(asindices(I), ofcolor(I, ZERO))
    BB = subgrid(FG, I)
    H = height(BB); W = width(BB)
    w1 = divide(W, THREE); w2 = divide(W, THREE); w12 = add(w1, w2); w3 = subtract(W, w12)
    S1 = crop(BB, ORIGIN, astuple(H, w1))
    S2 = crop(BB, tojvec(w1), astuple(H, w2))
    S3 = crop(BB, tojvec(w12), astuple(H, w3))
    colpick = lambda S: (
        lambda P, r1, r3, r2:
            vconcat(
                vconcat(
                    canvas(
                        branch(
                            equality(size(intersection(P, hfrontier(astuple(r1, ZERO)))), ZERO),
                            ZERO,
                            index(S, astuple(r1, rightmost(intersection(P, hfrontier(astuple(r1, ZERO))))))
                        ), UNITY
                    ),
                    canvas(
                        branch(
                            equality(size(intersection(P, hfrontier(astuple(r2, ZERO)))), ZERO),
                            ZERO,
                            index(S, astuple(r2, rightmost(intersection(P, hfrontier(astuple(r2, ZERO))))))
                        ), UNITY
                    )
                ),
                canvas(
                    branch(
                        equality(size(intersection(P, hfrontier(astuple(r3, ZERO)))), ZERO),
                        ZERO,
                        index(S, astuple(r3, rightmost(intersection(P, hfrontier(astuple(r3, ZERO))))))
                    ), UNITY
                )
            )
    )(
        difference(asindices(S), ofcolor(S, ZERO)),
        uppermost(difference(asindices(S), ofcolor(S, ZERO))),
        lowermost(difference(asindices(S), ofcolor(S, ZERO))),
        divide(add(uppermost(difference(asindices(S), ofcolor(S, ZERO))), lowermost(difference(asindices(S), ofcolor(S, ZERO)))), TWO)
    )
    C1 = colpick(S1)
    C2 = colpick(S2)
    C3 = colpick(S3)
    O = hconcat(hconcat(C1, C2), C3)
    return O
```