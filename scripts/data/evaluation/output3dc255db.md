```python
def dsl1(I):
    # Column-wise upward packing of the least-common nonzero color (acc)
    H, W = shape(I)
    pals = [v for v in totuple(palette(I)) if v != ZERO]
    if not pals:
        return I
    acc, accc = None, None
    for v in pals:
        c = colorcount(I, v)
        if acc is None or c < accc:
            acc, accc = v, c
    # build mutable copy and clear acc
    O = [list(r) for r in I]
    for i in range(H):
        for j in range(W):
            if O[i][j] == acc:
                O[i][j] = ZERO
    # per column, move acc cells to top until first barrier (first nonzero in that column)
    for j in range(W):
        # count acc in original column
        k = 0
        for i in range(H):
            if index(I, (i, j)) == acc:
                k += 1
        # find barrier in current O
        barrier = H
        for i in range(H):
            if O[i][j] != ZERO:
                barrier = i
                break
        t = min(k, barrier)
        for i in range(t):
            O[i][j] = acc
    return tuple(tuple(r) for r in O)


def dsl2(I):
    # For the two most-common colors, move non-matching colors inside each bbox
    # into a horizontal run adjacent to the densest row of that color within its bbox.
    H, W = shape(I)
    pals = [v for v in totuple(palette(I)) if v != ZERO]
    if not pals:
        return I
    counts = []
    for v in pals:
        counts.append((colorcount(I, v), v))
    counts.sort(reverse=True)
    mains = [v for (_, v) in counts[:2]]
    O = [list(r) for r in I]

    def bbox_of_color(grid, c):
        imin, imax, jmin, jmax = H, -1, W, -1
        for i in range(H):
            for j in range(W):
                if index(grid, (i, j)) == c:
                    imin = min(imin, i)
                    imax = max(imax, i)
                    jmin = min(jmin, j)
                    jmax = max(jmax, j)
        if imax < 0:
            return None
        return (imin, imax, jmin, jmax)

    for m in mains:
        bb = bbox_of_color(I, m)
        if bb is None:
            continue
        imin, imax, jmin, jmax = bb
        # gather non-m colors inside bbox, grouped by color
        acc_counts = {}
        cells_to_clear = []
        for i in range(imin, imax + 1):
            for j in range(jmin, jmax + 1):
                v = index(I, (i, j))
                if v != ZERO and v != m:
                    acc_counts[v] = acc_counts.get(v, 0) + 1
                    cells_to_clear.append((i, j))
        # clear those cells from O
        for (i, j) in cells_to_clear:
            O[i][j] = ZERO
        if not acc_counts:
            continue
        # choose target row: row within bbox with max count of m
        best_row = imin
        best_cnt = -1
        for i in range(imin, imax + 1):
            cnt = 0
            for j in range(jmin, jmax + 1):
                if index(I, (i, j)) == m:
                    cnt += 1
            if cnt > best_cnt:
                best_cnt = cnt
                best_row = i
        # find run extents of m on best_row within bbox
        left_end, right_end = None, None
        for j in range(jmin, jmax + 1):
            if index(I, (best_row, j)) == m:
                left_end = j
                break
        for j in range(jmax, jmin - 1, -1):
            if index(I, (best_row, j)) == m:
                right_end = j
                break
        if left_end is None:
            left_end = jmin - 1
            right_end = jmin - 1
        # compute free space on both sides in O
        rs = 0
        j = right_end + 1
        while j < W and O[best_row][j] == ZERO:
            rs += 1
            j += 1
        ls = 0
        j = left_end - 1
        while j >= 0 and O[best_row][j] == ZERO:
            ls += 1
            j -= 1
        # order of placement for accent colors (by color id)
        for cacc in sorted(acc_counts.keys()):
            k = acc_counts[cacc]
            # choose side with more space; tie -> right
            if rs >= ls and rs > 0:
                t = min(k, rs)
                for dj in range(t):
                    jj = right_end + 1 + dj
                    if 0 <= jj < W:
                        O[best_row][jj] = cacc
                rs -= t
            elif ls > 0:
                t = min(k, ls)
                for dj in range(t):
                    jj = left_end - t + dj
                    if 0 <= jj < W:
                        O[best_row][jj] = cacc
                ls -= t
            # if no space, drop remaining for this bbox
    return tuple(tuple(r) for r in O)


def dsl3(I):
    # Collapse least-common nonzero color into a single vertical stack
    # placed from the top in the column whose first occupied cell (any nonzero) is closest to the top.
    H, W = shape(I)
    pals = [v for v in totuple(palette(I)) if v != ZERO]
    if not pals:
        return I
    # least-common nonzero
    acc, accc = None, None
    for v in pals:
        c = colorcount(I, v)
        if acc is None or c < accc:
            acc, accc = v, c
    # choose column with minimal first-nonzero row (over any nonzero)
    def first_nonzero_row(j):
        for i in range(H):
            if index(I, (i, j)) != ZERO and index(I, (i, j)) != acc:
                return i
        return H
    best_j = 0
    best_top = H
    for j in range(W):
        t = first_nonzero_row(j)
        if t < best_top:
            best_top, best_j = t, j
    # build O: clear acc, then place up to 'best_top' cells in best_j from top
    O = [list(r) for r in I]
    total_acc = 0
    for i in range(H):
        for j in range(W):
            if O[i][j] == acc:
                O[i][j] = ZERO
                total_acc += 1
    t = min(total_acc, best_top)
    for i in range(t):
        O[i][best_j] = acc
    return tuple(tuple(r) for r in O)


def dsl4(I):
    # Distribute least-common nonzero color upward across columns that already contain any nonzero,
    # filling from the top until the first occupied cell in each column, left-to-right.
    H, W = shape(I)
    pals = [v for v in totuple(palette(I)) if v != ZERO]
    if not pals:
        return I
    # least-common nonzero
    acc, accc = None, None
    for v in pals:
        c = colorcount(I, v)
        if acc is None or c < accc:
            acc, accc = v, c
    # count total acc and clear them
    O = [list(r) for r in I]
    total = 0
    for i in range(H):
        for j in range(W):
            if O[i][j] == acc:
                O[i][j] = ZERO
                total += 1
    if total == 0:
        return tuple(tuple(r) for r in O)
    # columns that contain any nonzero (excluding acc since cleared)
    cols = []
    for j in range(W):
        have = False
        for i in range(H):
            if O[i][j] != ZERO:
                have = True
                break
        if have:
            cols.append(j)
    # fill from top in these columns
    rem = total
    for j in cols:
        if rem <= 0:
            break
        # barrier in this column
        barrier = H
        for i in range(H):
            if O[i][j] != ZERO:
                barrier = i
                break
        cap = barrier
        t = min(rem, cap)
        for i in range(t):
            O[i][j] = acc
        rem -= t
    return tuple(tuple(r) for r in O)


def dsl5(I):
    # Row-wise left packing of the least-common nonzero color just before the first nonzero in each row.
    H, W = shape(I)
    pals = [v for v in totuple(palette(I)) if v != ZERO]
    if not pals:
        return I
    acc, accc = None, None
    for v in pals:
        c = colorcount(I, v)
        if acc is None or c < accc:
            acc, accc = v, c
    O = [list(r) for r in I]
    # clear acc
    for i in range(H):
        for j in range(W):
            if O[i][j] == acc:
                O[i][j] = ZERO
    # for each row, pack acc cells immediately to the left of the first nonzero
    for i in range(H):
        # count acc in original row
        k = 0
        for j in range(W):
            if index(I, (i, j)) == acc:
                k += 1
        if k == 0:
            continue
        # barrier: first nonzero in row after clearing acc
        barrier = W
        for j in range(W):
            if O[i][j] != ZERO:
                barrier = j
                break
        t = min(k, barrier)
        for dj in range(t):
            jj = barrier - t + dj
            if 0 <= jj < W:
                O[i][jj] = acc
    return tuple(tuple(r) for r in O)
```