```python
def dsl1(I):
    # Global 3x3 binning on bbox with dominant nonzero color per bin
    fg = difference(asindices(I), ofcolor(I, ZERO))
    BB = subgrid(fg, I)
    TOP = tophalf(BB)
    MID = bottomhalf(tophalf(BB))
    BOT = bottomhalf(BB)
    TL = lefthalf(TOP)
    TC = righthalf(lefthalf(TOP))
    TR = righthalf(TOP)
    ML = lefthalf(MID)
    MC = righthalf(lefthalf(MID))
    MR = righthalf(MID)
    BL = lefthalf(BOT)
    BC = righthalf(lefthalf(BOT))
    BR = righthalf(BOT)
    nzdom = lambda G: branch(
        equality(size(remove(ZERO, palette(G))), ZERO),
        ZERO,
        argmax(remove(ZERO, palette(G)), lbind(colorcount, G))
    )
    v11 = nzdom(TL); v12 = nzdom(TC); v13 = nzdom(TR)
    v21 = nzdom(ML); v22 = nzdom(MC); v23 = nzdom(MR)
    v31 = nzdom(BL); v32 = nzdom(BC); v33 = nzdom(BR)
    r1 = hconcat(hconcat(canvas(v11, UNITY), canvas(v12, UNITY)), canvas(v13, UNITY))
    r2 = hconcat(hconcat(canvas(v21, UNITY), canvas(v22, UNITY)), canvas(v23, UNITY))
    r3 = hconcat(hconcat(canvas(v31, UNITY), canvas(v32, UNITY)), canvas(v33, UNITY))
    O = vconcat(vconcat(r1, r2), r3)
    return O

def dsl2(I):
    # 3x3 binning on bbox; sample color at center-of-mass of each bin (fallback 0)
    fg = difference(asindices(I), ofcolor(I, ZERO))
    BB = subgrid(fg, I)
    TOP = tophalf(BB)
    MID = bottomhalf(tophalf(BB))
    BOT = bottomhalf(BB)
    TL = lefthalf(TOP)
    TC = righthalf(lefthalf(TOP))
    TR = righthalf(TOP)
    ML = lefthalf(MID)
    MC = righthalf(lefthalf(MID))
    MR = righthalf(MID)
    BL = lefthalf(BOT)
    BC = righthalf(lefthalf(BOT))
    BR = righthalf(BOT)
    samp = lambda G: branch(
        equality(size(remove(ZERO, palette(G))), ZERO),
        ZERO,
        index(G, centerofmass(asindices(G)))
    )
    v11 = samp(TL); v12 = samp(TC); v13 = samp(TR)
    v21 = samp(ML); v22 = samp(MC); v23 = samp(MR)
    v31 = samp(BL); v32 = samp(BC); v33 = samp(BR)
    r1 = hconcat(hconcat(canvas(v11, UNITY), canvas(v12, UNITY)), canvas(v13, UNITY))
    r2 = hconcat(hconcat(canvas(v21, UNITY), canvas(v22, UNITY)), canvas(v23, UNITY))
    r3 = hconcat(hconcat(canvas(v31, UNITY), canvas(v32, UNITY)), canvas(v33, UNITY))
    O = vconcat(vconcat(r1, r2), r3)
    return O

def dsl3(I):
    # 3x3 binning on bbox; choose color of largest object per bin (fallback 0)
    fg = difference(asindices(I), ofcolor(I, ZERO))
    BB = subgrid(fg, I)
    TOP = tophalf(BB)
    MID = bottomhalf(tophalf(BB))
    BOT = bottomhalf(BB)
    TL = lefthalf(TOP)
    TC = righthalf(lefthalf(TOP))
    TR = righthalf(TOP)
    ML = lefthalf(MID)
    MC = righthalf(lefthalf(MID))
    MR = righthalf(MID)
    BL = lefthalf(BOT)
    BC = righthalf(lefthalf(BOT))
    BR = righthalf(BOT)
    pick = lambda G: branch(
        equality(size(fgpartition(G)), ZERO),
        ZERO,
        color(argmax(fgpartition(G), size))
    )
    v11 = pick(TL); v12 = pick(TC); v13 = pick(TR)
    v21 = pick(ML); v22 = pick(MC); v23 = pick(MR)
    v31 = pick(BL); v32 = pick(BC); v33 = pick(BR)
    r1 = hconcat(hconcat(canvas(v11, UNITY), canvas(v12, UNITY)), canvas(v13, UNITY))
    r2 = hconcat(hconcat(canvas(v21, UNITY), canvas(v22, UNITY)), canvas(v23, UNITY))
    r3 = hconcat(hconcat(canvas(v31, UNITY), canvas(v32, UNITY)), canvas(v33, UNITY))
    O = vconcat(vconcat(r1, r2), r3)
    return O

def dsl4(I):
    # Horizontal band reasoning on bbox: per band use [leftmost obj color, largest obj color, rightmost obj color]
    fg = difference(asindices(I), ofcolor(I, ZERO))
    BB = subgrid(fg, I)
    TOP = tophalf(BB)
    MID = bottomhalf(tophalf(BB))
    BOT = bottomhalf(BB)
    rowvec = lambda G: (
        branch(equality(size(fgpartition(G)), ZERO), ZERO, color(argmin(fgpartition(G), leftmost))),
        branch(equality(size(fgpartition(G)), ZERO), ZERO, color(argmax(fgpartition(G), size))),
        branch(equality(size(fgpartition(G)), ZERO), ZERO, color(argmax(fgpartition(G), rightmost)))
    )
    a1, b1, c1 = rowvec(TOP)
    a2, b2, c2 = rowvec(MID)
    a3, b3, c3 = rowvec(BOT)
    r1 = hconcat(hconcat(canvas(a1, UNITY), canvas(b1, UNITY)), canvas(c1, UNITY))
    r2 = hconcat(hconcat(canvas(a2, UNITY), canvas(b2, UNITY)), canvas(c2, UNITY))
    r3 = hconcat(hconcat(canvas(a3, UNITY), canvas(b3, UNITY)), canvas(c3, UNITY))
    O = vconcat(vconcat(r1, r2), r3)
    return O

def dsl5(I):
    # Vertical band reasoning on bbox: per band use [uppermost obj color; largest obj color; lowermost obj color] stacked
    fg = difference(asindices(I), ofcolor(I, ZERO))
    BB = subgrid(fg, I)
    L = lefthalf(BB)
    C = righthalf(lefthalf(BB))
    R = righthalf(BB)
    colvec = lambda G: (
        branch(equality(size(fgpartition(G)), ZERO), ZERO, color(argmin(fgpartition(G), uppermost))),
        branch(equality(size(fgpartition(G)), ZERO), ZERO, color(argmax(fgpartition(G), size))),
        branch(equality(size(fgpartition(G)), ZERO), ZERO, color(argmax(fgpartition(G), lowermost)))
    )
    t1, m1, b1 = colvec(L)
    t2, m2, b2 = colvec(C)
    t3, m3, b3 = colvec(R)
    col1 = vconcat(vconcat(canvas(t1, UNITY), canvas(m1, UNITY)), canvas(b1, UNITY))
    col2 = vconcat(vconcat(canvas(t2, UNITY), canvas(m2, UNITY)), canvas(b2, UNITY))
    col3 = vconcat(vconcat(canvas(t3, UNITY), canvas(m3, UNITY)), canvas(b3, UNITY))
    O = hconcat(hconcat(col1, col2), col3)
    return O
```