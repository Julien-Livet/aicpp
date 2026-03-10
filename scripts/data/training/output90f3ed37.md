```python
def dsl1(I):
    # Conditional right-fill on rows where the 8-run does not continue diagonally to the next row
    s = ofcolor(I, EIGHT)
    adj = intersection(s, shift(s, RIGHT))  # rows with horizontal adjacency among 8s
    rowsR = mapply(rbind(shoot, RIGHT), adj)
    rowsL = mapply(rbind(shoot, LEFT), adj)
    rows_with_adj = combine(rowsR, rowsL)
    b1 = difference(shift(s, RIGHT), s)  # first zero to the right of any 8
    block = shift(s, UP)  # indicates there is an 8 one row below at same column (diagonal continuation)
    starts = difference(intersection(b1, rows_with_adj), block)
    rays = mapply(rbind(shoot, RIGHT), starts)
    O = underfill(I, ONE, rays)
    return O

def dsl2(I):
    # Like dsl1, plus "repair" on the next row when the diagonal continuation is missing and the source row has no adjacency
    s = ofcolor(I, EIGHT)
    adj = intersection(s, shift(s, RIGHT))
    rowsR = mapply(rbind(shoot, RIGHT), adj)
    rowsL = mapply(rbind(shoot, LEFT), adj)
    rows_with_adj = combine(rowsR, rowsL)
    rows_all = asindices(I)
    rows_wo_adj = difference(rows_all, rows_with_adj)
    b1 = difference(shift(s, RIGHT), s)
    block = shift(s, UP)
    # current row continuous fill (only if row has adjacency and no diagonal continuation)
    starts_curr = difference(intersection(b1, rows_with_adj), block)
    rays_curr = mapply(rbind(shoot, RIGHT), starts_curr)
    # next row repair (only if row has no adjacency and no diagonal continuation)
    starts_next = shift(difference(intersection(b1, rows_wo_adj), block), DOWN)
    rays_next = mapply(rbind(shoot, RIGHT), starts_next)
    F = combine(rays_curr, rays_next)
    O = underfill(I, ONE, F)
    return O

def dsl3(I):
    # Alternating (step-2) completion on rows without horizontal adjacency, guarded by diagonal-with-above-left
    s = ofcolor(I, EIGHT)
    adj = intersection(s, shift(s, RIGHT))
    rowsR = mapply(rbind(shoot, RIGHT), adj)
    rowsL = mapply(rbind(shoot, LEFT), adj)
    rows_with_adj = combine(rowsR, rowsL)
    rows_all = asindices(I)
    rows_wo_adj = difference(rows_all, rows_with_adj)
    start2 = intersection(difference(shift(s, ZERO_BY_TWO), s), rows_wo_adj)
    # avoid when there is an 8 at (i+1, j-1) (block via up-right shift of s)
    block2 = shift(s, UP_RIGHT)
    start2 = difference(start2, block2)
    a2 = start2
    a4 = shift(a2, ZERO_BY_TWO)
    a6 = shift(a4, ZERO_BY_TWO)
    a8 = shift(a6, ZERO_BY_TWO)
    fillset = combine(a2, combine(a4, combine(a6, a8)))
    O = underfill(I, ONE, fillset)
    return O

def dsl4(I):
    # Combined strategy: conditional continuous fill + next-row repair + alternating extension
    s = ofcolor(I, EIGHT)
    adj = intersection(s, shift(s, RIGHT))
    rowsR = mapply(rbind(shoot, RIGHT), adj)
    rowsL = mapply(rbind(shoot, LEFT), adj)
    rows_with_adj = combine(rowsR, rowsL)
    rows_all = asindices(I)
    rows_wo_adj = difference(rows_all, rows_with_adj)
    b1 = difference(shift(s, RIGHT), s)
    block = shift(s, UP)
    # current row (continuous)
    starts_curr = difference(intersection(b1, rows_with_adj), block)
    rays_curr = mapply(rbind(shoot, RIGHT), starts_curr)
    # next row repair (continuous)
    starts_next = shift(difference(intersection(b1, rows_wo_adj), block), DOWN)
    rays_next = mapply(rbind(shoot, RIGHT), starts_next)
    # alternating (step-2) on rows without adjacency, guarded
    start2 = intersection(difference(shift(s, ZERO_BY_TWO), s), rows_wo_adj)
    block2 = shift(s, UP_RIGHT)
    start2 = difference(start2, block2)
    a2 = start2
    a4 = shift(a2, ZERO_BY_TWO)
    a6 = shift(a4, ZERO_BY_TWO)
    a8 = shift(a6, ZERO_BY_TWO)
    altfill = combine(a2, combine(a4, combine(a6, a8)))
    F = combine(rays_curr, combine(rays_next, altfill))
    O = underfill(I, ONE, F)
    return O

def dsl5(I):
    # Tip-based completion: from 8s that have no right neighbor and no down-right continuation
    s = ofcolor(I, EIGHT)
    right8 = shift(s, RIGHT)
    downright8 = shift(shift(s, DOWN), RIGHT)
    blockers = combine(right8, downright8)
    tips = difference(s, blockers)
    # continuous fill from immediate right of tips
    cstart = shift(tips, RIGHT)
    crayons = mapply(rbind(shoot, RIGHT), cstart)
    # alternating fill from two-right of tips
    astart = shift(tips, ZERO_BY_TWO)
    a2 = astart
    a4 = shift(a2, ZERO_BY_TWO)
    a6 = shift(a4, ZERO_BY_TWO)
    a8 = shift(a6, ZERO_BY_TWO)
    afill = combine(a2, combine(a4, combine(a6, a8)))
    F = combine(crayons, afill)
    O = underfill(I, ONE, F)
    return O
```