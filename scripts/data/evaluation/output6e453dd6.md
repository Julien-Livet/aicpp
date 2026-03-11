```python
def dsl1(I):
    # Shift left-of-5 right by 1; then fill right-of-5 rows with TWO if the last-left cell (c-1) is ZERO after the shift
    H = height(I)
    W = width(I)
    five = first(colorfilter(objects(I, T, F, T), FIVE))
    c = leftmost(five)
    rwidth = subtract(W, add(c, ONE))

    left = crop(I, astuple(0, 0), astuple(H, c))
    mid = crop(I, astuple(0, c), astuple(H, ONE))
    right = crop(I, astuple(0, add(c, ONE)), astuple(H, rwidth))

    blank = canvas(SIX, astuple(H, c))
    left_shifted = move(blank, asobject(left), RIGHT)

    base = hconcat(hconcat(left_shifted, mid), right)

    # rows to fill: those where col (c-1) is ZERO in left_shifted
    leftZ = ofcolor(left_shifted, ZERO)
    lastcol = vfrontier(astuple(0, subtract(c, ONE)))
    z_at_last = intersection(leftZ, lastcol)
    rows_fill = mapply(hfrontier, z_at_last)

    right_rel = asindices(right)
    right_global = shift(right_rel, astuple(0, add(c, ONE)))
    mask = intersection(rows_fill, right_global)

    O = fill(base, TWO, mask)
    return O

def dsl2(I):
    # Shift left-of-5 right by 1; then fill right-of-5 rows with TWO if there exists an isolated ZERO in that row (no horizontal ZERO neighbors)
    H = height(I)
    W = width(I)
    five = first(colorfilter(objects(I, T, F, T), FIVE))
    c = leftmost(five)
    rwidth = subtract(W, add(c, ONE))

    left = crop(I, astuple(0, 0), astuple(H, c))
    mid = crop(I, astuple(0, c), astuple(H, ONE))
    right = crop(I, astuple(0, add(c, ONE)), astuple(H, rwidth))

    blank = canvas(SIX, astuple(H, c))
    left_shifted = move(blank, asobject(left), RIGHT)
    base = hconcat(hconcat(left_shifted, mid), right)

    Z = ofcolor(left_shifted, ZERO)
    adjR = intersection(Z, shift(Z, RIGHT))
    adjL = intersection(Z, shift(Z, LEFT))
    adj_any = combine(adjR, adjL)
    iso = difference(Z, adj_any)
    rows_fill = mapply(hfrontier, iso)

    right_rel = asindices(right)
    right_global = shift(right_rel, astuple(0, add(c, ONE)))
    mask = intersection(rows_fill, right_global)

    O = fill(base, TWO, mask)
    return O

def dsl3(I):
    # Shift left-of-5 right by 1; then fill right-of-5 rows with TWO if that row is part of a vertical run of 3 ZEROs in left-of-5
    H = height(I)
    W = width(I)
    five = first(colorfilter(objects(I, T, F, T), FIVE))
    c = leftmost(five)
    rwidth = subtract(W, add(c, ONE))

    left = crop(I, astuple(0, 0), astuple(H, c))
    mid = crop(I, astuple(0, c), astuple(H, ONE))
    right = crop(I, astuple(0, add(c, ONE)), astuple(H, rwidth))

    blank = canvas(SIX, astuple(H, c))
    left_shifted = move(blank, asobject(left), RIGHT)
    base = hconcat(hconcat(left_shifted, mid), right)

    Z = ofcolor(left_shifted, ZERO)
    down1 = shift(Z, DOWN)
    down2 = shift(Z, double(DOWN))
    tops = intersection(Z, intersection(down1, down2))
    allrows_cells = combine(tops, combine(shift(tops, DOWN), shift(tops, double(DOWN))))
    rows_fill = mapply(hfrontier, allrows_cells)

    right_rel = asindices(right)
    right_global = shift(right_rel, astuple(0, add(c, ONE)))
    mask = intersection(rows_fill, right_global)

    O = fill(base, TWO, mask)
    return O

def dsl4(I):
    # Shift left-of-5 right by 1; then fill right-of-5 rows with TWO if the row contains a horizontal run of 3 ZEROs in left-of-5
    H = height(I)
    W = width(I)
    five = first(colorfilter(objects(I, T, F, T), FIVE))
    c = leftmost(five)
    rwidth = subtract(W, add(c, ONE))

    left = crop(I, astuple(0, 0), astuple(H, c))
    mid = crop(I, astuple(0, c), astuple(H, ONE))
    right = crop(I, astuple(0, add(c, ONE)), astuple(H, rwidth))

    blank = canvas(SIX, astuple(H, c))
    left_shifted = move(blank, asobject(left), RIGHT)
    base = hconcat(hconcat(left_shifted, mid), right)

    Z = ofcolor(left_shifted, ZERO)
    r1 = shift(Z, RIGHT)
    r2 = shift(Z, double(RIGHT))
    htrip = intersection(Z, intersection(r1, r2))
    rows_fill = mapply(hfrontier, htrip)

    right_rel = asindices(right)
    right_global = shift(right_rel, astuple(0, add(c, ONE)))
    mask = intersection(rows_fill, right_global)

    O = fill(base, TWO, mask)
    return O

def dsl5(I):
    # No shift; fill right-of-5 rows with TWO if the cell just left of FIVE (col c-1) is ZERO in the original grid
    H = height(I)
    W = width(I)
    five = first(colorfilter(objects(I, T, F, T), FIVE))
    c = leftmost(five)
    rwidth = subtract(W, add(c, ONE))

    left = crop(I, astuple(0, 0), astuple(H, c))
    mid = crop(I, astuple(0, c), astuple(H, ONE))
    right = crop(I, astuple(0, add(c, ONE)), astuple(H, rwidth))
    base = hconcat(hconcat(left, mid), right)

    col_last = vfrontier(astuple(0, subtract(c, ONE)))
    z_orig = ofcolor(I, ZERO)
    z_at_last = intersection(z_orig, col_last)
    rows_fill = mapply(hfrontier, z_at_last)

    right_rel = asindices(right)
    right_global = shift(right_rel, astuple(0, add(c, ONE)))
    mask = intersection(rows_fill, right_global)

    O = fill(base, TWO, mask)
    return O
```