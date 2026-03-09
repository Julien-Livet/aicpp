```python
def dsl1(I):
    bg = mostcolor(I)
    # extract the three 3x3 header blocks left-to-right
    sqs = sizefilter(objects(I, True, False, True), 9)
    seq = order(sqs, leftmost)
    A = first(seq)
    rest1 = remove(A, seq)
    B = first(rest1)
    rest2 = remove(B, rest1)
    C = first(rest2)
    Ag = subgrid(A, I)
    Bg = subgrid(B, I)
    Cg = subgrid(C, I)
    # 1-col separators to keep width 11
    sepcol = canvas(bg, astuple(3, 1))
    rowBAC = hconcat(Bg, hconcat(sepcol, hconcat(Ag, hconcat(sepcol, Cg))))
    rowCBA = hconcat(Cg, hconcat(sepcol, hconcat(Bg, hconcat(sepcol, Ag))))
    rowACB = hconcat(Ag, hconcat(sepcol, hconcat(Cg, hconcat(sepcol, Bg))))
    seprow = canvas(bg, astuple(1, width(rowBAC)))
    big = vconcat(rowBAC, vconcat(seprow, vconcat(rowCBA, vconcat(seprow, vconcat(rowACB, vconcat(seprow, rowBAC))))))
    O = crop(big, ORIGIN, astuple(13, width(big)))
    return O

def dsl2(I):
    bg = mostcolor(I)
    # extract headers A,B,C (left-to-right)
    sqs = sizefilter(objects(I, True, False, True), 9)
    seq = order(sqs, leftmost)
    A = first(seq)
    rest1 = remove(A, seq)
    B = first(rest1)
    rest2 = remove(B, rest1)
    C = first(rest2)
    Ag = subgrid(A, I)
    Bg = subgrid(B, I)
    Cg = subgrid(C, I)
    sepcol = canvas(bg, astuple(3, 1))
    rowABC = hconcat(Ag, hconcat(sepcol, hconcat(Bg, hconcat(sepcol, Cg))))
    rowBCA = hconcat(Bg, hconcat(sepcol, hconcat(Cg, hconcat(sepcol, Ag))))
    rowCAB = hconcat(Cg, hconcat(sepcol, hconcat(Ag, hconcat(sepcol, Bg))))
    seprow = canvas(bg, astuple(1, width(rowABC)))
    big = vconcat(rowABC, vconcat(seprow, vconcat(rowABC, vconcat(seprow, vconcat(rowBCA, vconcat(seprow, rowCAB))))))
    O = crop(big, ORIGIN, astuple(13, width(big)))
    return O

def dsl3(I):
    bg = mostcolor(I)
    # extract headers and sort by color value ascending
    sqs = sizefilter(objects(I, True, False, True), 9)
    cseq = order(sqs, color)
    D = first(cseq)
    r1 = remove(D, cseq)
    E = first(r1)
    r2 = remove(E, r1)
    F = first(r2)
    Dg = subgrid(D, I)
    Eg = subgrid(E, I)
    Fg = subgrid(F, I)
    sepcol = canvas(bg, astuple(3, 1))
    rowDEF = hconcat(Dg, hconcat(sepcol, hconcat(Eg, hconcat(sepcol, Fg))))
    rowEFD = hconcat(Eg, hconcat(sepcol, hconcat(Fg, hconcat(sepcol, Dg))))
    rowFDE = hconcat(Fg, hconcat(sepcol, hconcat(Dg, hconcat(sepcol, Eg))))
    seprow = canvas(bg, astuple(1, width(rowDEF)))
    big = vconcat(rowDEF, vconcat(seprow, vconcat(rowEFD, vconcat(seprow, vconcat(rowFDE, vconcat(seprow, rowDEF))))))
    O = crop(big, ORIGIN, astuple(13, width(big)))
    return O

def dsl4(I):
    bg = mostcolor(I)
    # headers
    sqs = sizefilter(objects(I, True, False, True), 9)
    seq = order(sqs, leftmost)
    A = first(seq)
    rest1 = remove(A, seq)
    B = first(rest1)
    rest2 = remove(B, rest1)
    C = first(rest2)
    Ag = subgrid(A, I)
    Bg = subgrid(B, I)
    Cg = subgrid(C, I)
    # detect presence of any full-width non-bg horizontal line in bottom half
    bot = bottomhalf(I)
    ob = objects(bot, True, False, True)
    wide = sizefilter(ob, width(I))
    cond = greater(size(wide), 0)
    sepcol = canvas(bg, astuple(3, 1))
    seprow = canvas(bg, astuple(1, 11))
    # alt1: BCA/CAB/ABC/BCA
    rowBCA = hconcat(Bg, hconcat(sepcol, hconcat(Cg, hconcat(sepcol, Ag))))
    rowCAB = hconcat(Cg, hconcat(sepcol, hconcat(Ag, hconcat(sepcol, Bg))))
    rowABC = hconcat(Ag, hconcat(sepcol, hconcat(Bg, hconcat(sepcol, Cg))))
    alt1 = vconcat(rowBCA, vconcat(seprow, vconcat(rowCAB, vconcat(seprow, vconcat(rowABC, vconcat(seprow, rowBCA))))))
    # alt2: CBA/BAC/ACB/CBA
    rowCBA = hconcat(Cg, hconcat(sepcol, hconcat(Bg, hconcat(sepcol, Ag))))
    rowBAC = hconcat(Bg, hconcat(sepcol, hconcat(Ag, hconcat(sepcol, Cg))))
    rowACB = hconcat(Ag, hconcat(sepcol, hconcat(Cg, hconcat(sepcol, Bg))))
    alt2 = vconcat(rowCBA, vconcat(seprow, vconcat(rowBAC, vconcat(seprow, vconcat(rowACB, vconcat(seprow, rowCBA))))))
    big = branch(cond, alt1, alt2)
    O = crop(big, ORIGIN, astuple(13, width(big)))
    return O

def dsl5(I):
    bg = mostcolor(I)
    # headers
    sqs = sizefilter(objects(I, True, False, True), 9)
    seq = order(sqs, leftmost)
    A = first(seq)
    rest1 = remove(A, seq)
    B = first(rest1)
    rest2 = remove(B, rest1)
    C = first(rest2)
    Ag = subgrid(A, I)
    Bg = subgrid(B, I)
    Cg = subgrid(C, I)
    # use 2-col separators, then crop width to 11
    sep2 = canvas(bg, astuple(3, 2))
    rowABC = hconcat(Ag, hconcat(sep2, hconcat(Bg, hconcat(sep2, Cg))))
    rowBCA = hconcat(Bg, hconcat(sep2, hconcat(Cg, hconcat(sep2, Ag))))
    rowCAB = hconcat(Cg, hconcat(sep2, hconcat(Ag, hconcat(sep2, Bg))))
    seprow = canvas(bg, astuple(1, width(rowABC)))
    big = vconcat(rowABC, vconcat(seprow, vconcat(rowBCA, vconcat(seprow, vconcat(rowCAB, vconcat(seprow, rowABC))))))
    O = crop(big, ORIGIN, astuple(13, 11))
    return O
```