```python
def dsl1(I):
    # Global pooling via quadrant-halves intersections using mostcolor
    fg = difference(asindices(I), ofcolor(I, ZERO))
    B = subgrid(fg, I)
    tl = mostcolor(tophalf(lefthalf(B)))
    tm = mostcolor(tophalf(B))
    tr = mostcolor(tophalf(righthalf(B)))
    ml = mostcolor(lefthalf(B))
    mm = mostcolor(B)
    mr = mostcolor(righthalf(B))
    bl = mostcolor(bottomhalf(lefthalf(B)))
    bm = mostcolor(bottomhalf(B))
    br = mostcolor(bottomhalf(righthalf(B)))
    r1 = hconcat(hconcat(canvas(tl, UNITY), canvas(tm, UNITY)), canvas(tr, UNITY))
    r2 = hconcat(hconcat(canvas(ml, UNITY), canvas(mm, UNITY)), canvas(mr, UNITY))
    r3 = hconcat(hconcat(canvas(bl, UNITY), canvas(bm, UNITY)), canvas(br, UNITY))
    O = vconcat(vconcat(r1, r2), r3)
    return O

def dsl2(I):
    # Object extraction: three topmost components (by uppermost) as uniform rows
    comps = objects(I, T, F, T)
    c1 = argmin(comps, uppermost)
    rest1 = remove(c1, comps)
    c2 = argmin(rest1, uppermost)
    rest2 = remove(c2, rest1)
    c3 = argmin(rest2, uppermost)
    r1 = canvas(color(c1), astuple(ONE, THREE))
    r2 = canvas(color(c2), astuple(ONE, THREE))
    r3 = canvas(color(c3), astuple(ONE, THREE))
    O = vconcat(vconcat(r1, r2), r3)
    return O

def dsl3(I):
    # Color filtering variant: use leastcolor over quadrant-halves intersections
    fg = difference(asindices(I), ofcolor(I, ZERO))
    B = subgrid(fg, I)
    tl = leastcolor(tophalf(lefthalf(B)))
    tm = leastcolor(tophalf(B))
    tr = leastcolor(tophalf(righthalf(B)))
    ml = leastcolor(lefthalf(B))
    mm = leastcolor(B)
    mr = leastcolor(righthalf(B))
    bl = leastcolor(bottomhalf(lefthalf(B)))
    bm = leastcolor(bottomhalf(B))
    br = leastcolor(bottomhalf(righthalf(B)))
    r1 = hconcat(hconcat(canvas(tl, UNITY), canvas(tm, UNITY)), canvas(tr, UNITY))
    r2 = hconcat(hconcat(canvas(ml, UNITY), canvas(mm, UNITY)), canvas(mr, UNITY))
    r3 = hconcat(hconcat(canvas(bl, UNITY), canvas(bm, UNITY)), canvas(br, UNITY))
    O = vconcat(vconcat(r1, r2), r3)
    return O

def dsl4(I):
    # Geometric: centerline crops of top/mid/bottom of the bbox
    fg = difference(asindices(I), ofcolor(I, ZERO))
    BB = subgrid(fg, I)
    TOP = tophalf(BB)
    BOT = bottomhalf(BB)
    fgT = difference(asindices(TOP), ofcolor(TOP, ZERO))
    fgM = difference(asindices(BB), ofcolor(BB, ZERO))
    fgB = difference(asindices(BOT), ofcolor(BOT, ZERO))
    ctT = center(fgT)
    ctM = center(fgM)
    ctB = center(fgB)
    sT = subtract(ctT, tojvec(ONE))
    sM = subtract(ctM, tojvec(ONE))
    sB = subtract(ctB, tojvec(ONE))
    r1 = crop(TOP, sT, astuple(ONE, THREE))
    r2 = crop(BB, sM, astuple(ONE, THREE))
    r3 = crop(BOT, sB, astuple(ONE, THREE))
    O = vconcat(vconcat(r1, r2), r3)
    return O

def dsl5(I):
    # Relational: sample colors at centers of mass across left/mid/right and top/mid/bot intersections
    fg = difference(asindices(I), ofcolor(I, ZERO))
    B = subgrid(fg, I)
    L = lefthalf(B)
    C = B
    R = righthalf(B)
    TL = tophalf(L)
    TC = tophalf(C)
    TR = tophalf(R)
    BL = bottomhalf(L)
    BC = bottomhalf(C)
    BR = bottomhalf(R)
    fTL = difference(asindices(TL), ofcolor(TL, ZERO))
    fTC = difference(asindices(TC), ofcolor(TC, ZERO))
    fTR = difference(asindices(TR), ofcolor(TR, ZERO))
    fL = difference(asindices(L), ofcolor(L, ZERO))
    fC = difference(asindices(C), ofcolor(C, ZERO))
    fR = difference(asindices(R), ofcolor(R, ZERO))
    fBL = difference(asindices(BL), ofcolor(BL, ZERO))
    fBC = difference(asindices(BC), ofcolor(BC, ZERO))
    fBR = difference(asindices(BR), ofcolor(BR, ZERO))
    v11 = index(TL, centerofmass(fTL))
    v12 = index(TC, centerofmass(fTC))
    v13 = index(TR, centerofmass(fTR))
    v21 = index(L, centerofmass(fL))
    v22 = index(C, centerofmass(fC))
    v23 = index(R, centerofmass(fR))
    v31 = index(BL, centerofmass(fBL))
    v32 = index(BC, centerofmass(fBC))
    v33 = index(BR, centerofmass(fBR))
    r1 = hconcat(hconcat(canvas(v11, UNITY), canvas(v12, UNITY)), canvas(v13, UNITY))
    r2 = hconcat(hconcat(canvas(v21, UNITY), canvas(v22, UNITY)), canvas(v23, UNITY))
    r3 = hconcat(hconcat(canvas(v31, UNITY), canvas(v32, UNITY)), canvas(v33, UNITY))
    O = vconcat(vconcat(r1, r2), r3)
    return O
```