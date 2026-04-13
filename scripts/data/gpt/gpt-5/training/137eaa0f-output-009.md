```python
def dsl1(I):
    # Global 3x3 partition of full grid; per bin take majority color (including zero)
    H = height(I); W = width(I)
    h1 = divide(H, THREE); h2 = divide(H, THREE); h3 = subtract(H, add(h1, h2))
    w1 = divide(W, THREE); w2 = divide(W, THREE); w3 = subtract(W, add(w1, w2))
    sr1 = ORIGIN; sr2 = toivec(h1); sr3 = toivec(add(h1, h2))
    sc1 = ORIGIN; sc2 = tojvec(w1); sc3 = tojvec(add(w1, w2))
    Gs = (
        crop(I, add(sr1, sc1), astuple(h1, w1)),
        crop(I, add(sr1, sc2), astuple(h1, w2)),
        crop(I, add(sr1, sc3), astuple(h1, w3)),
        crop(I, add(sr2, sc1), astuple(h2, w1)),
        crop(I, add(sr2, sc2), astuple(h2, w2)),
        crop(I, add(sr2, sc3), astuple(h2, w3)),
        crop(I, add(sr3, sc1), astuple(h3, w1)),
        crop(I, add(sr3, sc2), astuple(h3, w2)),
        crop(I, add(sr3, sc3), astuple(h3, w3)),
    )
    choose = lambda G: argmax(palette(G), lbind(colorcount, G))
    vals = tuple(apply(choose, Gs))
    r1 = hconcat(hconcat(canvas(vals[0], UNITY), canvas(vals[1], UNITY)), canvas(vals[2], UNITY))
    r2 = hconcat(hconcat(canvas(vals[3], UNITY), canvas(vals[4], UNITY)), canvas(vals[5], UNITY))
    r3 = hconcat(hconcat(canvas(vals[6], UNITY), canvas(vals[7], UNITY)), canvas(vals[8], UNITY))
    O = vconcat(vconcat(r1, r2), r3)
    return O

def dsl2(I):
    # Object extraction: for mid-row of each horizontal third, pick nearest object; within its bbox sample L/M/R on top row
    H = height(I)
    h1 = divide(H, THREE); h2 = divide(H, THREE); h3 = subtract(H, add(h1, h2))
    r1 = halve(h1)
    r2 = add(h1, halve(h2))
    r3 = add(add(h1, h2), halve(h3))
    FGobjs = fgpartition(I)
    pick_near_row = lambda r: argmin(FGobjs, compose(lbind(manhattan, hfrontier(astuple(r, ZERO))), toindices))
    top = pick_near_row(r1)
    mid = pick_near_row(r2)
    bot = pick_near_row(r3)
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
    # Color filtering: per horizontal third, take majority color and replicate across row
    H = height(I)
    h1 = divide(H, THREE); h2 = divide(H, THREE); h3 = subtract(H, add(h1, h2))
    B1 = crop(I, ORIGIN, astuple(h1, width(I)))
    B2 = crop(I, toivec(h1), astuple(h2, width(I)))
    B3 = crop(I, toivec(add(h1, h2)), astuple(h3, width(I)))
    v1 = argmax(palette(B1), lbind(colorcount, B1))
    v2 = argmax(palette(B2), lbind(colorcount, B2))
    v3 = argmax(palette(B3), lbind(colorcount, B3))
    R1 = hconcat(hconcat(canvas(v1, UNITY), canvas(v1, UNITY)), canvas(v1, UNITY))
    R2 = hconcat(hconcat(canvas(v2, UNITY), canvas(v2, UNITY)), canvas(v2, UNITY))
    R3 = hconcat(hconcat(canvas(v3, UNITY), canvas(v3, UNITY)), canvas(v3, UNITY))
    O = vconcat(vconcat(R1, R2), R3)
    return O

def dsl4(I):
    # Geometric: intersections of extreme/mid rows&cols inside FG bbox, use nearest object (by manhattan) color
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
    # Relational: at FG extreme/mid intersections, cast rays in 4 directions; choose nearest object along rays
    FG = difference(asindices(I), ofcolor(I, ZERO))
    r1 = uppermost(FG); r3 = lowermost(FG); r2 = divide(add(r1, r3), TWO)
    c1 = leftmost(FG); c3 = rightmost(FG); c2 = divide(add(c1, c3), TWO)
    FGobjs = fgpartition(I)
    rays = lambda r, c: combine(
        combine(shoot(astuple(r, c), UP), shoot(astuple(r, c), DOWN)),
        combine(shoot(astuple(r, c), LEFT), shoot(astuple(r, c), RIGHT))
    )
    pick = lambda r, c: canvas(color(argmin(FGobjs, compose(lbind(manhattan, rays(r, c)), toindices))), UNITY)
    R1 = hconcat(hconcat(pick(r1, c1), pick(r1, c2)), pick(r1, c3))
    R2 = hconcat(hconcat(pick(r2, c1), pick(r2, c2)), pick(r2, c3))
    R3 = hconcat(hconcat(pick(r3, c1), pick(r3, c2)), pick(r3, c3))
    O = vconcat(vconcat(R1, R2), R3)
    return O
```