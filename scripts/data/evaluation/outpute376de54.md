```python
def dsl1(I):
    # Extend anti-diagonal chains only from their endpoints (per color), into background.
    H, W = shape(I)
    O = I
    for col in [v for v in palette(I) if v != SEVEN]:
        S = ofcolor(I, col)
        if size(S) == 0:
            continue
        R = initset(ORIGIN)
        R = remove(ORIGIN, R)
        for (r, c) in S:
            ne = add(astuple(r, c), UP_RIGHT)
            sw = add(astuple(r, c), DOWN_LEFT)
            has_ne = contained(ne, S)
            has_sw = contained(sw, S)
            has_any = either(has_ne, has_sw)
            has_both = both(has_ne, has_sw)
            is_endpoint = both(has_any, flip(has_both))
            if is_endpoint:
                dir1 = branch(flip(has_ne), UP_RIGHT, DOWN_LEFT)
                seg = shoot(astuple(r, c), dir1)
                R = combine(R, seg)
        O = underfill(O, col, R)
    return O

def dsl2(I):
    # Normalize only the first and last horizontal line objects to length W/2 (anchor at left).
    H, W = shape(I)
    O = I
    HL = sfilter(objects(I, True, False, True), hline)
    n = size(HL)
    if n == 0:
        return O
    top_obj = argmin(HL, uppermost)
    bot_obj = branch(greater(n, ONE), argmax(HL, uppermost), top_obj)
    for o in [top_obj, bot_obj]:
        c = color(o)
        r = uppermost(o)
        l = leftmost(o)
        rgt = min(W - 1, l + (W // 2) - 1)
        seg = connect(astuple(r, l), astuple(r, rgt))
        newo = recolor(c, seg)
        O = cover(O, o)
        O = paint(O, newo)
    return O

def dsl3(I):
    # For each color, find top contiguous block of dense rows (>= maxcount-1),
    # fill them with the union of their columns, and clear sparser rows below within the bbox.
    H, W = shape(I)
    O = I
    for col in [v for v in palette(I) if v != SEVEN]:
        S = ofcolor(I, col)
        if size(S) == 0:
            continue
        rows = {}
        cols_by_row = {}
        for (r, j) in S:
            rows[r] = rows.get(r, 0) + 1
            if r not in cols_by_row:
                cols_by_row[r] = set()
            cols_by_row[r].add(j)
        rmin = min(rows.keys())
        rmax = max(rows.keys())
        maxcount = max(rows.values())
        thr = maxcount - 1 if maxcount > 0 else 0
        block = []
        for r in range(rmin, rmax + 1):
            cnt = rows.get(r, 0)
            if cnt >= thr and (len(block) == 0 or r == block[-1] + 1):
                block.append(r)
            elif len(block) > 0:
                break
        if len(block) == 0:
            continue
        unioncols = set()
        for r in block:
            for j in cols_by_row.get(r, set()):
                unioncols.add(j)
        P = initset(ORIGIN); P = remove(ORIGIN, P)
        for r in block:
            for j in unioncols:
                P = insert(astuple(r, j), P)
        O = underfill(O, col, P)
        # Clear rows outside the block within original extent
        Q = initset(ORIGIN); Q = remove(ORIGIN, Q)
        blockset = set(block)
        for (r, j) in S:
            if r < rmin or r > rmax or (r not in blockset):
                Q = insert(astuple(r, j), Q)
        O = fill(O, SEVEN, Q)
    return O

def dsl4(I):
    # Propagate union of columns downward across consecutive dense rows (>=2),
    # stop at the first sparse row (<=1) and clear below for that color.
    H, W = shape(I)
    O = I
    for col in [v for v in palette(I) if v != SEVEN]:
        S = ofcolor(I, col)
        if size(S) == 0:
            continue
        rows = {}
        cols_by_row = {}
        for (r, j) in S:
            rows[r] = rows.get(r, 0) + 1
            if r not in cols_by_row:
                cols_by_row[r] = set()
            cols_by_row[r].add(j)
        if len(rows) == 0:
            continue
        r_sorted = sorted(rows.keys())
        run_rows = []
        unioncols = set()
        cutoff_index = len(r_sorted)
        for idx, r in enumerate(r_sorted):
            cnt = rows.get(r, 0)
            if idx == 0:
                run_rows.append(r)
                for j in cols_by_row.get(r, set()):
                    unioncols.add(j)
                continue
            prev = r_sorted[idx - 1]
            if cnt >= 2 and r == prev + 1:
                run_rows.append(r)
                for j in cols_by_row.get(r, set()):
                    unioncols.add(j)
            else:
                cutoff_index = idx
                break
        # Fill the run rows with union of columns
        P = initset(ORIGIN); P = remove(ORIGIN, P)
        for r in run_rows:
            for j in unioncols:
                P = insert(astuple(r, j), P)
        O = underfill(O, col, P)
        # Clear rows from cutoff onward (sparse or non-consecutive tail)
        if cutoff_index < len(r_sorted):
            Q = initset(ORIGIN); Q = remove(ORIGIN, Q)
            for r in r_sorted[cutoff_index:]:
                for j in cols_by_row.get(r, set()):
                    Q = insert(astuple(r, j), Q)
            O = fill(O, SEVEN, Q)
    return O

def dsl5(I):
    # Remove trailing sparse rows (<=1 count) after the last dense row (>=3) for each color.
    H, W = shape(I)
    O = I
    for col in [v for v in palette(I) if v != SEVEN]:
        S = ofcolor(I, col)
        if size(S) == 0:
            continue
        rows = {}
        cols_by_row = {}
        for (r, j) in S:
            rows[r] = rows.get(r, 0) + 1
            if r not in cols_by_row:
                cols_by_row[r] = set()
            cols_by_row[r].add(j)
        dense_rows = [r for r, c in rows.items() if c >= 3]
        if len(dense_rows) == 0:
            continue
        last_dense = max(dense_rows)
        Q = initset(ORIGIN); Q = remove(ORIGIN, Q)
        for r, c in rows.items():
            if r > last_dense and c <= 1:
                for j in cols_by_row.get(r, set()):
                    Q = insert(astuple(r, j), Q)
        O = fill(O, SEVEN, Q)
    return O
```