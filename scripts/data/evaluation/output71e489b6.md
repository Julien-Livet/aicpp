```python
def dsl1(I):
    # Select zeros that have at least one horizontal 1-neighbor AND at least one vertical 1-neighbor.
    # Then paint 7 on all their 8-neighbors.
    H = height(I)
    W = width(I)
    targets = set()
    for (i, j) in ofcolor(I, ZERO):
        has_h = (j - 1 >= 0 and I[i][j - 1] == ONE) or (j + 1 < W and I[i][j + 1] == ONE)
        has_v = (i - 1 >= 0 and I[i - 1][j] == ONE) or (i + 1 < H and I[i + 1][j] == ONE)
        if has_h and has_v:
            nb = set(neighbors((i, j))) | set(ineighbors((i, j)))
            targets.update(nb)
    O = fill(I, SEVEN, frozenset(targets))
    return O

def dsl2(I):
    # Heuristic: keep only the dense band of rows/cols (majority-1 rows/cols), zeroing the rest.
    # Then apply the cross-adjacency rule and paint 7 on all 8-neighbors.
    H = height(I)
    W = width(I)
    row_ones = [sum(1 for j in range(W) if I[i][j] == ONE) for i in range(H)]
    col_ones = [sum(1 for i in range(H) if I[i][j] == ONE) for j in range(W)]
    dense_rows = [i for i in range(H) if row_ones[i] >= W // 2]
    dense_cols = [j for j in range(W) if col_ones[j] >= H // 2]
    if dense_rows and dense_cols:
        rmin, rmax = min(dense_rows), max(dense_rows)
        cmin, cmax = min(dense_cols), max(dense_cols)
        bbox = frozenset((i, j) for i in range(rmin, rmax + 1) for j in range(cmin, cmax + 1))
        outside = difference(asindices(I), bbox)
        J = fill(I, ZERO, outside)
    else:
        J = I
    targets = set()
    for (i, j) in ofcolor(J, ZERO):
        has_h = (j - 1 >= 0 and J[i][j - 1] == ONE) or (j + 1 < W and J[i][j + 1] == ONE)
        has_v = (i - 1 >= 0 and J[i - 1][j] == ONE) or (i + 1 < H and J[i + 1][j] == ONE)
        if has_h and has_v:
            nb = set(neighbors((i, j))) | set(ineighbors((i, j)))
            targets.update(nb)
    O = fill(J, SEVEN, frozenset(targets))
    return O

def dsl3(I):
    # Select zeros with at least 3 neighboring 1s in the 8-neighborhood; paint 7 on all 8-neighbors.
    H = height(I)
    W = width(I)
    targets = set()
    for (i, j) in ofcolor(I, ZERO):
        nb = list(neighbors((i, j))) + list(ineighbors((i, j)))
        ones_cnt = sum(1 for (r, c) in nb if 0 <= r < H and 0 <= c < W and I[r][c] == ONE)
        if ones_cnt >= 3:
            targets.update(nb)
    O = fill(I, SEVEN, frozenset(targets))
    return O

def dsl4(I):
    # Select zeros that are flanked by 1s on an axis: (left and right are 1) or (up and down are 1).
    # Then paint 7 on all 8-neighbors.
    H = height(I)
    W = width(I)
    targets = set()
    for (i, j) in ofcolor(I, ZERO):
        lr = (j - 1 >= 0 and I[i][j - 1] == ONE) and (j + 1 < W and I[i][j + 1] == ONE)
        ud = (i - 1 >= 0 and I[i - 1][j] == ONE) and (i + 1 < H and I[i + 1][j] == ONE)
        if lr or ud:
            nb = set(neighbors((i, j))) | set(ineighbors((i, j)))
            targets.update(nb)
    O = fill(I, SEVEN, frozenset(targets))
    return O

def dsl5(I):
    # Cross-adjacency selection as in dsl1, but paint 7 only onto neighbors that were originally 1.
    H = height(I)
    W = width(I)
    targets = set()
    for (i, j) in ofcolor(I, ZERO):
        has_h = (j - 1 >= 0 and I[i][j - 1] == ONE) or (j + 1 < W and I[i][j + 1] == ONE)
        has_v = (i - 1 >= 0 and I[i - 1][j] == ONE) or (i + 1 < H and I[i + 1][j] == ONE)
        if has_h and has_v:
            nb = list(neighbors((i, j))) + list(ineighbors((i, j)))
            for (r, c) in nb:
                if 0 <= r < H and 0 <= c < W and I[r][c] == ONE:
                    targets.add((r, c))
    O = fill(I, SEVEN, frozenset(targets))
    return O
```