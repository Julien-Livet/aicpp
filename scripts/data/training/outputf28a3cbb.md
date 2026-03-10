```python
def dsl1(I):
    bg = mostcolor(I)
    p = palette(I)
    pnbg = remove(bg, p)
    a = first(pnbg)
    b = other(pnbg, a)
    oa = ofcolor(I, a)
    ob = ofcolor(I, b)
    sca = add(uppermost(oa), leftmost(oa))
    scb = add(uppermost(ob), leftmost(ob))
    ctl = branch(greater(sca, scb), b, a)
    cbr = other(pnbg, ctl)
    ntl = colorcount(I, ctl)
    nbr = colorcount(I, cbr)
    stl = branch(greater(ntl, multiply(EIGHT, EIGHT)), NINE,
          branch(greater(ntl, multiply(SEVEN, SEVEN)), EIGHT,
          branch(greater(ntl, multiply(SIX, SIX)), SEVEN,
          branch(greater(ntl, multiply(FIVE, FIVE)), SIX,
          branch(greater(ntl, multiply(FOUR, FOUR)), FIVE,
          branch(greater(ntl, multiply(THREE, THREE)), FOUR,
          branch(greater(ntl, multiply(TWO, TWO)), THREE,
          branch(greater(ntl, multiply(ONE, ONE)), TWO, ONE))))))))
    sbr = branch(greater(nbr, multiply(EIGHT, EIGHT)), NINE,
          branch(greater(nbr, multiply(SEVEN, SEVEN)), EIGHT,
          branch(greater(nbr, multiply(SIX, SIX)), SEVEN,
          branch(greater(nbr, multiply(FIVE, FIVE)), SIX,
          branch(greater(nbr, multiply(FOUR, FOUR)), FIVE,
          branch(greater(nbr, multiply(THREE, THREE)), FOUR,
          branch(greater(nbr, multiply(TWO, TWO)), THREE,
          branch(greater(nbr, multiply(ONE, ONE)), TWO, ONE))))))))
    qtl = divide(ntl, stl)
    rtl = subtract(ntl, multiply(qtl, stl))
    qbr = divide(nbr, sbr)
    rbr = subtract(nbr, multiply(qbr, sbr))
    H = height(I)
    W = width(I)
    base = canvas(bg, shape(I))
    # TL row-major: full rows + partial row
    full_tl = asindices(canvas(ZERO, astuple(qtl, stl)))
    part_tl = asindices(canvas(ZERO, astuple(ONE, rtl)))
    part_tl = shift(part_tl, astuple(qtl, ZERO))
    base = fill(base, ctl, combine(full_tl, part_tl))
    # BR column-major: full cols + partial col from bottom
    full_br = asindices(canvas(ZERO, astuple(sbr, qbr)))
    full_br = shift(full_br, astuple(subtract(H, sbr), subtract(W, qbr)))
    part_br = asindices(canvas(ZERO, astuple(rbr, ONE)))
    part_br = shift(part_br, astuple(subtract(H, rbr), decrement(subtract(W, qbr))))
    O = fill(base, cbr, combine(full_br, part_br))
    return O

def dsl2(I):
    bg = mostcolor(I)
    p = palette(I)
    pnbg = remove(bg, p)
    a = first(pnbg)
    b = other(pnbg, a)
    oa = ofcolor(I, a)
    ob = ofcolor(I, b)
    sca = add(uppermost(oa), leftmost(oa))
    scb = add(uppermost(ob), leftmost(ob))
    ctl = branch(greater(sca, scb), b, a)
    cbr = other(pnbg, ctl)
    ntl = colorcount(I, ctl)
    nbr = colorcount(I, cbr)
    stl = branch(greater(ntl, multiply(EIGHT, EIGHT)), NINE,
          branch(greater(ntl, multiply(SEVEN, SEVEN)), EIGHT,
          branch(greater(ntl, multiply(SIX, SIX)), SEVEN,
          branch(greater(ntl, multiply(FIVE, FIVE)), SIX,
          branch(greater(ntl, multiply(FOUR, FOUR)), FIVE,
          branch(greater(ntl, multiply(THREE, THREE)), FOUR,
          branch(greater(ntl, multiply(TWO, TWO)), THREE,
          branch(greater(ntl, multiply(ONE, ONE)), TWO, ONE))))))))
    sbr = branch(greater(nbr, multiply(EIGHT, EIGHT)), NINE,
          branch(greater(nbr, multiply(SEVEN, SEVEN)), EIGHT,
          branch(greater(nbr, multiply(SIX, SIX)), SEVEN,
          branch(greater(nbr, multiply(FIVE, FIVE)), SIX,
          branch(greater(nbr, multiply(FOUR, FOUR)), FIVE,
          branch(greater(nbr, multiply(THREE, THREE)), FOUR,
          branch(greater(nbr, multiply(TWO, TWO)), THREE,
          branch(greater(nbr, multiply(ONE, ONE)), TWO, ONE))))))))
    qtl = divide(ntl, stl)
    rtl = subtract(ntl, multiply(qtl, stl))
    qbr = divide(nbr, sbr)
    rbr = subtract(nbr, multiply(qbr, sbr))
    H = height(I)
    W = width(I)
    base = canvas(bg, shape(I))
    # TL column-major top-down
    full_tl = asindices(canvas(ZERO, astuple(stl, qtl)))
    part_tl = asindices(canvas(ZERO, astuple(rtl, ONE)))
    part_tl = shift(part_tl, astuple(ZERO, qtl))
    base = fill(base, ctl, combine(full_tl, part_tl))
    # BR column-major bottom-up
    full_br = asindices(canvas(ZERO, astuple(sbr, qbr)))
    full_br = shift(full_br, astuple(subtract(H, sbr), subtract(W, qbr)))
    part_br = asindices(canvas(ZERO, astuple(rbr, ONE)))
    part_br = shift(part_br, astuple(subtract(H, rbr), decrement(subtract(W, qbr))))
    O = fill(base, cbr, combine(full_br, part_br))
    return O

def dsl3(I):
    bg = mostcolor(I)
    p = palette(I)
    pnbg = remove(bg, p)
    # choose TL by proximity to top-left
    a = first(pnbg)
    b = other(pnbg, a)
    oa = ofcolor(I, a)
    ob = ofcolor(I, b)
    sca = add(uppermost(oa), leftmost(oa))
    scb = add(uppermost(ob), leftmost(ob))
    ctl = branch(greater(sca, scb), b, a)
    cbr = other(pnbg, ctl)
    ntl = colorcount(I, ctl)
    nbr = colorcount(I, cbr)
    stl = branch(greater(ntl, multiply(EIGHT, EIGHT)), NINE,
          branch(greater(ntl, multiply(SEVEN, SEVEN)), EIGHT,
          branch(greater(ntl, multiply(SIX, SIX)), SEVEN,
          branch(greater(ntl, multiply(FIVE, FIVE)), SIX,
          branch(greater(ntl, multiply(FOUR, FOUR)), FIVE,
          branch(greater(ntl, multiply(THREE, THREE)), FOUR,
          branch(greater(ntl, multiply(TWO, TWO)), THREE,
          branch(greater(ntl, multiply(ONE, ONE)), TWO, ONE))))))))
    sbr = branch(greater(nbr, multiply(EIGHT, EIGHT)), NINE,
          branch(greater(nbr, multiply(SEVEN, SEVEN)), EIGHT,
          branch(greater(nbr, multiply(SIX, SIX)), SEVEN,
          branch(greater(nbr, multiply(FIVE, FIVE)), SIX,
          branch(greater(nbr, multiply(FOUR, FOUR)), FIVE,
          branch(greater(nbr, multiply(THREE, THREE)), FOUR,
          branch(greater(nbr, multiply(TWO, TWO)), THREE,
          branch(greater(nbr, multiply(ONE, ONE)), TWO, ONE))))))))
    qtl = divide(ntl, stl)
    rtl = subtract(ntl, multiply(qtl, stl))
    qbr = divide(nbr, sbr)
    rbr = subtract(nbr, multiply(qbr, sbr))
    H = height(I)
    W = width(I)
    base = canvas(bg, shape(I))
    # TL row-major
    full_tl = asindices(canvas(ZERO, astuple(qtl, stl)))
    part_tl = asindices(canvas(ZERO, astuple(ONE, rtl)))
    part_tl = shift(part_tl, astuple(qtl, ZERO))
    base = fill(base, ctl, combine(full_tl, part_tl))
    # BR row-major (from bottom-right)
    full_br = asindices(canvas(ZERO, astuple(qbr, sbr)))
    full_br = shift(full_br, astuple(subtract(H, qbr), subtract(W, sbr)))
    part_br = asindices(canvas(ZERO, astuple(ONE, rbr)))
    part_br = shift(part_br, astuple(decrement(subtract(H, qbr)), subtract(W, rbr)))
    O = fill(base, cbr, combine(full_br, part_br))
    return O

def dsl4(I):
    bg = mostcolor(I)
    p = palette(I)
    pnbg = remove(bg, p)
    a = first(pnbg)
    b = other(pnbg, a)
    # alternate TL selection: leastcolor as TL
    ctl = leastcolor(I)
    cbr = other(pnbg, ctl)
    ntl = colorcount(I, ctl)
    nbr = colorcount(I, cbr)
    stl = branch(greater(ntl, multiply(EIGHT, EIGHT)), NINE,
          branch(greater(ntl, multiply(SEVEN, SEVEN)), EIGHT,
          branch(greater(ntl, multiply(SIX, SIX)), SEVEN,
          branch(greater(ntl, multiply(FIVE, FIVE)), SIX,
          branch(greater(ntl, multiply(FOUR, FOUR)), FIVE,
          branch(greater(ntl, multiply(THREE, THREE)), FOUR,
          branch(greater(ntl, multiply(TWO, TWO)), THREE,
          branch(greater(ntl, multiply(ONE, ONE)), TWO, ONE))))))))
    sbr = branch(greater(nbr, multiply(EIGHT, EIGHT)), NINE,
          branch(greater(nbr, multiply(SEVEN, SEVEN)), EIGHT,
          branch(greater(nbr, multiply(SIX, SIX)), SEVEN,
          branch(greater(nbr, multiply(FIVE, FIVE)), SIX,
          branch(greater(nbr, multiply(FOUR, FOUR)), FIVE,
          branch(greater(nbr, multiply(THREE, THREE)), FOUR,
          branch(greater(nbr, multiply(TWO, TWO)), THREE,
          branch(greater(nbr, multiply(ONE, ONE)), TWO, ONE))))))))
    qtl = divide(ntl, stl)
    rtl = subtract(ntl, multiply(qtl, stl))
    qbr = divide(nbr, sbr)
    rbr = subtract(nbr, multiply(qbr, sbr))
    H = height(I)
    W = width(I)
    base = canvas(bg, shape(I))
    # TL column-major
    full_tl = asindices(canvas(ZERO, astuple(stl, qtl)))
    part_tl = asindices(canvas(ZERO, astuple(rtl, ONE)))
    part_tl = shift(part_tl, astuple(ZERO, qtl))
    base = fill(base, ctl, combine(full_tl, part_tl))
    # BR row-major
    full_br = asindices(canvas(ZERO, astuple(qbr, sbr)))
    full_br = shift(full_br, astuple(subtract(H, qbr), subtract(W, sbr)))
    part_br = asindices(canvas(ZERO, astuple(ONE, rbr)))
    part_br = shift(part_br, astuple(decrement(subtract(H, qbr)), subtract(W, rbr)))
    O = fill(base, cbr, combine(full_br, part_br))
    return O

def dsl5(I):
    bg = mostcolor(I)
    p = palette(I)
    pnbg = remove(bg, p)
    a = first(pnbg)
    b = other(pnbg, a)
    oa = ofcolor(I, a)
    ob = ofcolor(I, b)
    sca = add(uppermost(oa), leftmost(oa))
    scb = add(uppermost(ob), leftmost(ob))
    ctl = branch(greater(sca, scb), b, a)
    cbr = other(pnbg, ctl)
    ntl = colorcount(I, ctl)
    nbr = colorcount(I, cbr)
    stl = branch(greater(ntl, multiply(EIGHT, EIGHT)), NINE,
          branch(greater(ntl, multiply(SEVEN, SEVEN)), EIGHT,
          branch(greater(ntl, multiply(SIX, SIX)), SEVEN,
          branch(greater(ntl, multiply(FIVE, FIVE)), SIX,
          branch(greater(ntl, multiply(FOUR, FOUR)), FIVE,
          branch(greater(ntl, multiply(THREE, THREE)), FOUR,
          branch(greater(ntl, multiply(TWO, TWO)), THREE,
          branch(greater(ntl, multiply(ONE, ONE)), TWO, ONE))))))))
    sbr = branch(greater(nbr, multiply(EIGHT, EIGHT)), NINE,
          branch(greater(nbr, multiply(SEVEN, SEVEN)), EIGHT,
          branch(greater(nbr, multiply(SIX, SIX)), SEVEN,
          branch(greater(nbr, multiply(FIVE, FIVE)), SIX,
          branch(greater(nbr, multiply(FOUR, FOUR)), FIVE,
          branch(greater(nbr, multiply(THREE, THREE)), FOUR,
          branch(greater(nbr, multiply(TWO, TWO)), THREE,
          branch(greater(nbr, multiply(ONE, ONE)), TWO, ONE))))))))
    # Use minimal width given height (may be < side), pack column-major
    qtl = divide(ntl, stl)         # full columns
    rtl = subtract(ntl, multiply(qtl, stl))  # remainder rows in next col
    qbr = divide(nbr, sbr)
    rbr = subtract(nbr, multiply(qbr, sbr))
    H = height(I)
    W = width(I)
    base = canvas(bg, shape(I))
    # TL: full columns + partial column (column-major, minimal width)
    full_tl = asindices(canvas(ZERO, astuple(stl, qtl)))
    part_tl = asindices(canvas(ZERO, astuple(rtl, ONE)))
    part_tl = shift(part_tl, astuple(ZERO, qtl))
    base = fill(base, ctl, combine(full_tl, part_tl))
    # BR: same minimal-width packing from right edge
    full_br = asindices(canvas(ZERO, astuple(sbr, qbr)))
    full_br = shift(full_br, astuple(subtract(H, sbr), subtract(W, qbr)))
    part_br = asindices(canvas(ZERO, astuple(rbr, ONE)))
    part_br = shift(part_br, astuple(subtract(H, rbr), decrement(subtract(W, qbr))))
    O = fill(base, cbr, combine(full_br, part_br))
    return O
```