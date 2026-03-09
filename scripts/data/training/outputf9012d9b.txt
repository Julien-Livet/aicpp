```python
def dsl1(I):
    # Quadrant nonzero-mode tile; if exactly one zero in I, collapse to 1x1 of tile's most common color.
    h = height(I); w = width(I)
    rmid = divide(h, TWO); cmid = divide(w, TWO)
    TL = crop(I, astuple(ZERO, ZERO), astuple(rmid, cmid))
    TR = crop(I, astuple(ZERO, cmid), astuple(rmid, subtract(w, cmid)))
    BL = crop(I, astuple(rmid, ZERO), astuple(subtract(h, rmid), cmid))
    BR = crop(I, astuple(rmid, cmid), astuple(subtract(h, rmid), subtract(w, cmid)))
    f1000 = multiply(TEN, multiply(TEN, TEN))
    pick = lambda G: branch(
        greater(size(remove(ZERO, palette(G))), ZERO),
        valmax(remove(ZERO, palette(G)), fork(add, compose(rbind(multiply, f1000), lbind(colorcount, G)), identity)),
        ZERO
    )
    a = pick(TL); b = pick(TR); c = pick(BL); d = pick(BR)
    tile = vconcat(hconcat(canvas(a, UNITY), canvas(b, UNITY)),
                   hconcat(canvas(c, UNITY), canvas(d, UNITY)))
    O = branch(equality(colorcount(I, ZERO), ONE), canvas(mostcolor(tile), UNITY), tile)
    return O

def dsl2(I):
    # Same as dsl1 but if exactly one zero, collapse to top-left tile entry.
    h = height(I); w = width(I)
    rmid = divide(h, TWO); cmid = divide(w, TWO)
    TL = crop(I, astuple(ZERO, ZERO), astuple(rmid, cmid))
    TR = crop(I, astuple(ZERO, cmid), astuple(rmid, subtract(w, cmid)))
    BL = crop(I, astuple(rmid, ZERO), astuple(subtract(h, rmid), cmid))
    BR = crop(I, astuple(rmid, cmid), astuple(subtract(h, rmid), subtract(w, cmid)))
    f1000 = multiply(TEN, multiply(TEN, TEN))
    pick = lambda G: branch(
        greater(size(remove(ZERO, palette(G))), ZERO),
        valmax(remove(ZERO, palette(G)), fork(add, compose(rbind(multiply, f1000), lbind(colorcount, G)), identity)),
        ZERO
    )
    a = pick(TL); b = pick(TR); c = pick(BL); d = pick(BR)
    tile = vconcat(hconcat(canvas(a, UNITY), canvas(b, UNITY)),
                   hconcat(canvas(c, UNITY), canvas(d, UNITY)))
    O = branch(equality(colorcount(I, ZERO), ONE), canvas(a, UNITY), tile)
    return O

def dsl3(I):
    # Quadrant nonzero-mode tile; if up to two zeros in I, collapse to 1x1 of tile's most common color.
    h = height(I); w = width(I)
    rmid = divide(h, TWO); cmid = divide(w, TWO)
    TL = crop(I, astuple(ZERO, ZERO), astuple(rmid, cmid))
    TR = crop(I, astuple(ZERO, cmid), astuple(rmid, subtract(w, cmid)))
    BL = crop(I, astuple(rmid, ZERO), astuple(subtract(h, rmid), cmid))
    BR = crop(I, astuple(rmid, cmid), astuple(subtract(h, rmid), subtract(w, cmid)))
    f1000 = multiply(TEN, multiply(TEN, TEN))
    pick = lambda G: branch(
        greater(size(remove(ZERO, palette(G))), ZERO),
        valmax(remove(ZERO, palette(G)), fork(add, compose(rbind(multiply, f1000), lbind(colorcount, G)), identity)),
        ZERO
    )
    a = pick(TL); b = pick(TR); c = pick(BL); d = pick(BR)
    tile = vconcat(hconcat(canvas(a, UNITY), canvas(b, UNITY)),
                   hconcat(canvas(c, UNITY), canvas(d, UNITY)))
    zc = colorcount(I, ZERO)
    cond = either(equality(zc, ONE), equality(zc, TWO))
    O = branch(cond, canvas(mostcolor(tile), UNITY), tile)
    return O

def dsl4(I):
    # Quadrant nonzero-mode with fallback to global nonzero-mode if a quadrant has no nonzero colors; no collapse.
    h = height(I); w = width(I)
    rmid = divide(h, TWO); cmid = divide(w, TWO)
    TL = crop(I, astuple(ZERO, ZERO), astuple(rmid, cmid))
    TR = crop(I, astuple(ZERO, cmid), astuple(rmid, subtract(w, cmid)))
    BL = crop(I, astuple(rmid, ZERO), astuple(subtract(h, rmid), cmid))
    BR = crop(I, astuple(rmid, cmid), astuple(subtract(h, rmid), subtract(w, cmid)))
    f1000 = multiply(TEN, multiply(TEN, TEN))
    gp = remove(ZERO, palette(I))
    gmode = branch(
        greater(size(gp), ZERO),
        valmax(gp, fork(add, compose(rbind(multiply, f1000), lbind(colorcount, I)), identity)),
        ZERO
    )
    mode = lambda G: branch(
        greater(size(remove(ZERO, palette(G))), ZERO),
        valmax(remove(ZERO, palette(G)), fork(add, compose(rbind(multiply, f1000), lbind(colorcount, G)), identity)),
        gmode
    )
    a = mode(TL); b = mode(TR); c = mode(BL); d = mode(BR)
    O = vconcat(hconcat(canvas(a, UNITY), canvas(b, UNITY)),
                hconcat(canvas(c, UNITY), canvas(d, UNITY)))
    return O

def dsl5(I):
    # Sample-biased quadrant selection: prefer each quadrant's top-left sample if nonzero; otherwise use nonzero-mode. Collapse to tile mode on exactly one zero.
    h = height(I); w = width(I)
    rmid = divide(h, TWO); cmid = divide(w, TWO)
    TL = crop(I, astuple(ZERO, ZERO), astuple(rmid, cmid))
    TR = crop(I, astuple(ZERO, cmid), astuple(rmid, subtract(w, cmid)))
    BL = crop(I, astuple(rmid, ZERO), astuple(subtract(h, rmid), cmid))
    BR = crop(I, astuple(rmid, cmid), astuple(subtract(h, rmid), subtract(w, cmid)))
    f1000 = multiply(TEN, multiply(TEN, TEN))
    m = lambda G: branch(
        greater(size(remove(ZERO, palette(G))), ZERO),
        valmax(remove(ZERO, palette(G)), fork(add, compose(rbind(multiply, f1000), lbind(colorcount, G)), identity)),
        ZERO
    )
    sTL = index(TL, astuple(ZERO, ZERO))
    sTR = index(TR, astuple(ZERO, ZERO))
    sBL = index(BL, astuple(ZERO, ZERO))
    sBR = index(BR, astuple(ZERO, ZERO))
    a = branch(greater(sTL, ZERO), sTL, m(TL))
    b = branch(greater(sTR, ZERO), sTR, m(TR))
    c = branch(greater(sBL, ZERO), sBL, m(BL))
    d = branch(greater(sBR, ZERO), sBR, m(BR))
    tile = vconcat(hconcat(canvas(a, UNITY), canvas(b, UNITY)),
                   hconcat(canvas(c, UNITY), canvas(d, UNITY)))
    O = branch(equality(colorcount(I, ZERO), ONE), canvas(mostcolor(tile), UNITY), tile)
    return O
```