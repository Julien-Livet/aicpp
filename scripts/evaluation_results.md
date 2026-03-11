evaluation 1818057f 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # Recolor all plus-shaped 4s (center and its 4-neighbors) to 8 using set-shift intersections
    S = ofcolor(I, FOUR)
    a = shift(S, UP)
    b = shift(S, DOWN)
    c = shift(S, LEFT)
    d = shift(S, RIGHT)
    t1 = intersection(S, a)
    t2 = intersection(t1, b)
    t3 = intersection(t2, c)
    centers = intersection(t3, d)
    upc = shift(centers, UP)
    downc = shift(centers, DOWN)
    leftc = shift(centers, LEFT)
    rightc = shift(centers, RIGHT)
    p1 = combine(centers, upc)
    p2 = combine(p1, downc)
    p3 = combine(p2, leftc)
    pluscells = combine(p3, rightc)
    O = fill(I, EIGHT, pluscells)
    return O
```
evaluation 45a5af55 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # Concentric filled rings using the first column palette; center uses the last row color
    h = height(I)
    D = subtract(multiply(h, TWO), TWO)
    center_col = index(I, astuple(subtract(h, ONE), ZERO))
    O = canvas(center_col, astuple(D, D))
    for i in range(0, subtract(h, ONE)):  # 0..h-2
        outer_side = subtract(D, multiply(TWO, i))
        start = astuple(i, i)
        outer_idx = shift(asindices(canvas(ZERO, astuple(outer_side, outer_side))), start)
        inner_side = subtract(outer_side, TWO)
        if inner_side > 0:
            inner_idx = shift(asindices(canvas(ZERO, astuple(inner_side, inner_side))), astuple(add(i, ONE), add(i, ONE)))
            ring_idx = difference(outer_idx, inner_idx)
        else:
            ring_idx = outer_idx
        colval = index(I, astuple(i, ZERO))
        O = fill(O, colval, ring_idx)
    return O
```
evaluation 2ba387bc 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # Separate 4x4 objects into hollow (left column) and solid (right column), keep raster order, pack into 4x4 tiles
    allobjs = objects(I, T, F, T)
    dims44 = astuple(FOUR, FOUR)
    is44 = matcher(shape, dims44)
    objs44 = sfilter(allobjs, is44)
    ordered = order(objs44, ulcorner)
    isHollow = compose(positive, compose(size, delta))
    hollows = sfilter(ordered, isHollow)
    solids = sfilter(ordered, compose(flip, isHollow))
    # build 4x4 tile objects from source
    tilefunc = compose(asobject, rbind(subgrid, I))
    htiles = apply(tilefunc, hollows)
    stiles = apply(tilefunc, solids)
    # layout
    lenH = size(hollows)
    lenS = size(solids)
    nrows = branch(greater(lenH, lenS), lenH, lenS)
    H = multiply(nrows, FOUR)
    W = multiply(TWO, FOUR)
    O = canvas(ZERO, astuple(H, W))
    # offsets for left column (hollows)
    rowsH = interval(ZERO, multiply(lenH, FOUR), FOUR)
    vH = apply(toivec, rowsH)
    offH = apply(lbind(add, tojvec(ZERO)), vH)
    # offsets for right column (solids)
    rowsS = interval(ZERO, multiply(lenS, FOUR), FOUR)
    vS = apply(toivec, rowsS)
    offS = apply(lbind(add, tojvec(FOUR)), vS)
    # place hollows
    placedH = merge(papply(shift, htiles, offH))
    O = paint(O, placedH)
    # place solids
    placedS = merge(papply(shift, stiles, offS))
    O = paint(O, placedS)
    return O
```
evaluation 28a6681f 0.0 10.473708194342818 0.30000000000000004 0.10606601714048212 10.8797742114833
```python
def dsl5(I):
    # Connectivity-based pruning: keep only ONEs reachable from any non-ONE via paths stepping through ONEs; then immediate sandwich fill.
    h = height(I)
    w = width(I)
    from collections import deque
    # mark reachable ONEs by BFS starting from all non-ONE non-zero cells
    reach = [[False]*w for _ in range(h)]
    q = deque()
    for i in range(h):
        for j in range(w):
            v = index(I, (i, j))
            if v != ZERO and v != ONE:
                reach[i][j] = True
                q.append((i, j))
    while q:
        i, j = q.popleft()
        for di, dj in ((1,0),(-1,0),(0,1),(0,-1)):
            ii, jj = i+di, j+dj
            if 0 <= ii < h and 0 <= jj < w and not reach[ii][jj]:
                if index(I, (ii, jj)) == ONE:
                    reach[ii][jj] = True
                    q.append((ii, jj))
    O = [list(row) for row in I]
    # prune ONEs not reachable
    for i in range(h):
        for j in range(w):
            if O[i][j] == ONE and not reach[i][j]:
                O[i][j] = ZERO
    # immediate horizontal/vertical A-0-A sandwich fill
    for i in range(h):
        for j in range(w):
            if O[i][j] != ZERO:
                continue
            if 0 < j < w-1:
                L = index(I, (i, j-1))
                R = index(I, (i, j+1))
                if L == R and L != ZERO and L != ONE:
                    O[i][j] = ONE
                    continue
            if 0 < i < h-1:
                U = index(I, (i-1, j))
                D = index(I, (i+1, j))
                if U == D and U != ZERO and U != ONE:
                    O[i][j] = ONE
    return tuple(tuple(row) for row in O)
```
evaluation 9bbf930d 0.0 13.889220158756238 0.15701778423039703 0.0 14.046237942986636
```python
def dsl4(I):
    # Remove left-edge 6 on rows where the last column is not 7; leave other rows unchanged.
    w = width(I)
    six = ofcolor(I, SIX)
    lastcol = vfrontier(lrcorner(asindices(I)))
    last_not7 = difference(lastcol, ofcolor(I, SEVEN))
    # align those rows to column 1
    off = tojvec(invert(subtract(w, ONE)))
    rows_to_clear = intersection(six, shift(last_not7, off))
    O = fill(I, SEVEN, rows_to_clear)
    return O
```
evaluation 7b5033c1 0.0 15.684387141358123 0.72 0.0 16.40438714135812
```python
def dsl1(I):
    # Group by color, order colors by their topmost occurrence, stack blocks with height equal to pixel count
    bg = mostcolor(I)
    cols = [c for c in totuple(palette(I)) if c != bg]
    items = []
    for c in cols:
        r = uppermost(ofcolor(I, c))
        items.append((r, c))
    items.sort(key=lambda t: t[0])
    O = None
    for _, c in items:
        h = colorcount(I, c)
        block = canvas(c, astuple(h, ONE))
        O = block if O is None else vconcat(O, block)
    return O
```
evaluation 97d7923e 0.0 16.380659544255987 0.09833333333333327 0.0 16.47899287758932
```python
def dsl2(I):
    # Connect both the leftmost and rightmost bracketed vertical segments (if they exist)
    H = height(I)
    W = width(I)
    all_cands = []
    for j in range(W):
        rows_by_c = {}
        for r in range(H):
            v = index(I, astuple(r, j))
            if v != ZERO:
                rows_by_c.setdefault(v, []).append(r)
        for c, rows in rows_by_c.items():
            if len(rows) < 2:
                continue
            top, bot = rows[0], rows[-1]
            if bot - top < 2:
                continue
            diff = False
            for r in range(top + 1, bot):
                v = index(I, astuple(r, j))
                if v != ZERO and v != c:
                    diff = True
                    break
            if diff:
                all_cands.append((j, c, top, bot))
    if not all_cands:
        return I
    left = min(all_cands, key=lambda t: t[0])
    right = max(all_cands, key=lambda t: t[0])
    O = I
    for (j, c, top, bot) in (left,):
        O = fill(O, c, connect(astuple(top, j), astuple(bot, j)))
    if right[0] != left[0]:
        j, c, top, bot = right
        O = fill(O, c, connect(astuple(top, j), astuple(bot, j)))
    return O
```
evaluation db695cfb 0.0 18.466185312619388 0.08380952380952378 0.0 18.549994836428912
```python
def dsl1(I):
    # Hypothesis 1: Choose the farthest pair of 1s that lie on the same diagonal (main or anti).
    # Paint full perpendicular 6-diagonals from any 6 on that connecting segment (6s overwrite).
    # Finally, fill the 1s along the segment only (underfill so 6 stays dominant at intersections).
    ones = ofcolor(I, ONE)
    pts = totuple(ones)
    n = len(pts)
    if n < 2:
        return I
    best_p = None
    best_q = None
    best_dist = -1
    for a in range(n):
        p = pts[a]
        main_p = combine(shoot(p, UNITY), shoot(p, NEG_UNITY))
        main_p = insert(p, main_p)
        anti_p = combine(shoot(p, UP_RIGHT), shoot(p, DOWN_LEFT))
        anti_p = insert(p, anti_p)
        for b in range(a + 1, n):
            q = pts[b]
            if contained(q, main_p) or contained(q, anti_p):
                sp = initset(p)
                sq = initset(q)
                d = manhattan(sp, sq)
                if d > best_dist:
                    best_dist = d
                    best_p = p
                    best_q = q
    if best_p is None:
        return I
    p, q = best_p, best_q
    main_through_p = combine(shoot(p, UNITY), shoot(p, NEG_UNITY))
    main_through_p = insert(p, main_through_p)
    is_main = contained(q, main_through_p)
    seg = connect(p, q)
    sixes = ofcolor(I, SIX)
    seeds = intersection(seg, sixes)
    seeds_t = totuple(seeds)
    acc6 = initset(ORIGIN)
    acc6 = remove(ORIGIN, acc6)
    for s in seeds_t:
        if is_main:
            diag = combine(shoot(s, UP_RIGHT), shoot(s, DOWN_LEFT))
        else:
            diag = combine(shoot(s, UNITY), shoot(s, NEG_UNITY))
        diag = insert(s, diag)
        acc6 = combine(acc6, diag)
    G = paint(I, recolor(SIX, acc6)) if len(seeds_t) > 0 else I
    O = underfill(G, ONE, seg)
    return O
```
evaluation 332f06d7 0.0 20.12461179749811 0.19112882653061225 0.0 20.31574062402872
```python
def dsl1(I):
    # Move ZERO so its upper-left aligns with the TWO upper-left; fill vacated ZERO with ONE
    zind = ofcolor(I, ZERO)
    tind = ofcolor(I, TWO)
    O1 = fill(I, ONE, zind)
    off = subtract(ulcorner(tind), ulcorner(zind))
    nz = shift(zind, off)
    O = fill(O1, ZERO, nz)
    return O
```
evaluation e376de54 0.0 32.30554529655453 0.109375 0.0 32.41492029655453
```python
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
evaluation 409aa875 0.0 34.92402304735405 0.15625 0.0 35.08027304735405
```python
def dsl5(I):
    H = height(I)
    W = width(I)
    grid = asindices(I)
    z = ofcolor(I, ZERO)
    t = ofcolor(I, TWO)
    up5 = subtract(ZERO, FIVE)
    vec = astuple(up5, up5)
    src = combine(z, t)
    tgt = intersection(shift(src, vec), grid)
    O = fill(I, NINE, tgt)
    return O
```
evaluation 7491f3cf 0.0 35.1842378217507 0.15428571428571436 0.0 35.33852353603641
```python
def dsl1(I):
    # Copy left-half of block2's feature into left half of block4; 
    # copy right-half of block3's feature into right half of block4; 2 overrides 3.
    O = I
    b2 = crop(I, astuple(1,7), astuple(5,5))
    b3 = crop(I, astuple(1,13), astuple(5,5))
    b4 = crop(I, astuple(1,19), astuple(5,5))
    bg2 = mostcolor(b2)
    bg3 = mostcolor(b3)
    c2 = other(palette(b2), bg2)
    c3 = other(palette(b3), bg3)
    # absolute masks for block4 columns
    box4_abs = shift(asindices(b4), astuple(1,19))
    c19 = intersection(box4_abs, shoot(astuple(1,19), DOWN))
    c20 = intersection(box4_abs, shoot(astuple(1,20), DOWN))
    c21 = intersection(box4_abs, shoot(astuple(1,21), DOWN))
    c22 = intersection(box4_abs, shoot(astuple(1,22), DOWN))
    c23 = intersection(box4_abs, shoot(astuple(1,23), DOWN))
    left_mask = combine(combine(c19, c20), c21)
    right_mask = combine(combine(c21, c22), c23)
    # features shifted to block4
    p2_abs = shift(ofcolor(b2, c2), astuple(1,19))
    p3_abs = shift(ofcolor(b3, c3), astuple(1,19))
    # restrict to masks
    p2_left = intersection(p2_abs, left_mask)
    p3_right = intersection(p3_abs, right_mask)
    O = paint(O, recolor(c3, p3_right))
    O = paint(O, recolor(c2, p2_left))
    return O
```
evaluation 7b80bb43 0.0 38.03840158876355 0.09774280401815894 0.0 38.1361443927817
```python
def dsl5(I):
    fg = leastcolor(I)
    objs = objects(I, True, F, T)
    big = argmax(objs, size)
    bb = backdrop(big)
    span = connect(ulcorner(bb), urcorner(bb))
    O = fill(I, fg, span)
    return O
```
evaluation 58490d8a 0.0 37.500257160358764 0.25165739022881883 0.8408356078857058 38.592750158473294
```python
def dsl1(I):
    obs = objects(I, T, F, T)
    zobs = colorfilter(obs, ZERO)
    best = argmax(zobs, size)
    O = subgrid(best, I)
    return O
```
evaluation 16de56c4 0.0 41.902827663335046 0.312962962962963 0.0 42.21579062629801
```python
def dsl1(I):
    # Orientation-adaptive periodic fill with bounding when endpoint colors differ.
    H, W = height(I), width(I)
    row_pairs = 0
    col_pairs = 0
    for i in range(H):
        js = []
        for j in range(W):
            if index(I, astuple(i, j)) != ZERO:
                js.append(j)
        if len(js) >= 2:
            row_pairs += 1
    for j in range(W):
        is_ = []
        for i in range(H):
            if index(I, astuple(i, j)) != ZERO:
                is_.append(i)
        if len(is_) >= 2:
            col_pairs += 1

    O = I
    if col_pairs > row_pairs:
        # Column mode: minimal-gap periodic fill, using bottommost color, bounded to bottommost if colors differ
        for j in range(W):
            is_ = []
            for i in range(H):
                if index(I, astuple(i, j)) != ZERO:
                    is_.append(i)
            if len(is_) < 2:
                continue
            is_.sort()
            best_p = None
            i0 = None
            for k in range(len(is_) - 1):
                p = is_[k+1] - is_[k]
                if (best_p is None) or (p < best_p):
                    best_p = p
                    i0 = is_[k]
            if best_p is None or best_p <= 0:
                continue
            i_last = is_[-1]
            c0 = index(I, astuple(i0, j))
            cfill = index(I, astuple(i_last, j))
            bounded = (c0 != cfill)
            patch = set()
            for i in range(H):
                if ((i - i0) % best_p) == 0:
                    if (not bounded) or (i <= i_last):
                        patch.add(astuple(i, j))
            if patch:
                O = fill(O, cfill, frozenset(patch))
    else:
        # Row mode: minimal-gap periodic fill, using rightmost color, bounded to rightmost if colors differ
        for i in range(H):
            js = []
            for j in range(W):
                if index(I, astuple(i, j)) != ZERO:
                    js.append(j)
            if len(js) < 2:
                continue
            js.sort()
            best_p = None
            j0 = None
            for k in range(len(js) - 1):
                p = js[k+1] - js[k]
                if (best_p is None) or (p < best_p):
                    best_p = p
                    j0 = js[k]
            if best_p is None or best_p <= 0:
                continue
            j_last = js[-1]
            c0 = index(I, astuple(i, j0))
            cfill = index(I, astuple(i, j_last))
            bounded = (c0 != cfill)
            patch = set()
            for j in range(W):
                if ((j - j0) % best_p) == 0:
                    if (not bounded) or (j <= j_last):
                        patch.add(astuple(i, j))
            if patch:
                O = fill(O, cfill, frozenset(patch))
    return O
```
evaluation 135a2760 0.0 43.54028484224057 0.09676946121654795 0.0 43.63705430345712
```python
def dsl2(I):
    # Parity propagation by two steps within non-separator zones (avoid 2 and 4 as separators).
    G = I
    pal = totuple(palette(G))
    sep = combine(ofcolor(G, TWO), ofcolor(G, FOUR))
    allowed = difference(asindices(G), sep)
    for d in pal:
        if d == TWO or d == FOUR:
            continue
        od = ofcolor(G, d)
        # propagate d two to the right where the in-between is allowed
        tR = intersection(shift(od, (0, 2)), allowed)
        tR = intersection(tR, shift(allowed, RIGHT))  # ensure middle is allowed
        # propagate d two to the left where the in-between is allowed
        tL = intersection(shift(od, (0, -2)), allowed)
        tL = intersection(tL, shift(allowed, LEFT))   # ensure middle is allowed
        G = fill(G, d, tR)
        G = fill(G, d, tL)
    return G
```
evaluation 53fb4810 0.0 43.943798802304556 0.17194444444444446 0.0 44.115743246749005
```python
def dsl1(I):
    # Orientation-aware column fill to the lowest non-8 in each involved column; preserve 1s.
    l4 = first(ofcolor(I, FOUR))
    adj2 = first(intersection(neighbors(l4), ofcolor(I, TWO)))
    ones = ofcolor(I, ONE)
    non8 = difference(asindices(I), ofcolor(I, EIGHT))

    isvert = vmatching(initset(l4), initset(adj2))

    c4 = vfrontier(l4)
    c4_non8 = intersection(c4, non8)
    top4 = ulcorner(c4)
    bot4 = llcorner(c4_non8)
    seg4 = connect(top4, bot4)

    O = fill(I, FOUR, difference(seg4, ones))

    if not isvert:
        c2 = vfrontier(adj2)
        c2_non8 = intersection(c2, non8)
        top2 = ulcorner(c2)
        bot2 = llcorner(c2_non8)
        seg2 = connect(top2, bot2)
        O = fill(O, TWO, difference(seg2, ones))
    return O
```
evaluation 3dc255db 0.0 47.69202976201592 0.15476495726495731 0.0926577999185938 47.93945251919947
```python
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
```
evaluation 88e364bc 0.0 48.24502858293894 0.07500000000000007 0.0 48.32002858293894
```python
def dsl1(I):
    # Slide each FOUR in the cardinal direction (up/down/left/right) that has the longest run of zeros
    # and stop just before the first nonzero barrier.
    H, W = shape(I)
    fours = ofcolor(I, FOUR)
    new_positions = []
    dirs = [UP, DOWN, LEFT, RIGHT]
    for (r, c) in fours:
        best_steps = -1
        best_pos = (r, c)
        for (dr, dc) in dirs:
            steps = 0
            nr, nc = r + dr, c + dc
            while 0 <= nr < H and 0 <= nc < W and index(I, (nr, nc)) == ZERO:
                steps += 1
                nr += dr
                nc += dc
            # stop just before barrier
            nr = r + dr * steps
            nc = c + dc * steps
            if steps > best_steps:
                best_steps = steps
                best_pos = (nr, nc)
        new_positions.append(best_pos)
    O = replace(I, FOUR, ZERO)
    O = fill(O, FOUR, frozenset(new_positions))
    return O
```
evaluation 8f3a5a89 0.0 49.06044292850357 0.5815104166666666 0.0 49.641953345170236
```python
def dsl2(I):
    # Same intent as dsl1 but compute adjacency to non-background via shifts of all non-bg objects
    tgt = extract(colorfilter(partition(I), EIGHT), rbind(adjacent, toobject(ofcolor(I, SIX), I)))
    objs = objects(I, T, F, T)  # all non-background objects
    upn = mapply(rbind(shift, UP), objs)
    dnn = mapply(rbind(shift, DOWN), objs)
    lfn = mapply(rbind(shift, LEFT), objs)
    rgn = mapply(rbind(shift, RIGHT), objs)
    adjpatch = combine(combine(upn, dnn), combine(lfn, rgn))
    adjidx = toindices(adjpatch)
    tidx = toindices(tgt)
    b1 = intersection(adjidx, tidx)              # 8-cells in tgt adjacent to any non-bg
    b2 = intersection(box(tgt), tidx)            # include grid-border part of tgt
    b = combine(b1, b2)
    obj = recolor(SEVEN, toobject(b, I))
    O = underpaint(I, obj)
    return O
```
evaluation dd6b8c4b 0.0 49.60409937126198 0.2727272727272726 0.0 49.87682664398926
```python
def dsl2(I):
    # Move nines from the nearest 7-region and fill the ring proportionally (top 1/2/3 rows by thresholds)
    threes = colorfilter(objects(I, T, F, T), THREE)
    three = first(threes)
    bbox = backdrop(three)
    ul = ulcorner(bbox)
    toprow = intersection(shoot(ul, RIGHT), bbox)
    midrow = intersection(shoot(add(ul, DOWN), RIGHT), bbox)
    botrow = intersection(shoot(add(ul, TWO_BY_ZERO), RIGHT), bbox)
    bgs = colorfilter(objects(I, T, F, F), SEVEN)
    bg = argmin(bgs, lbind(manhattan, bbox))
    nineobjs = colorfilter(objects(I, T, F, T), NINE)
    near = sfilter(nineobjs, lbind(adjacent, bg))
    nearcells = mapply(toindices, near)
    cnt = size(nearcells)
    g0 = fill(I, SEVEN, nearcells)
    patch2 = combine(toprow, midrow)
    patch3 = combine(patch2, botrow)
    patch = branch(greater(cnt, EIGHT), bbox,
             branch(greater(cnt, FIVE), patch2,
             branch(greater(cnt, TWO), toprow, initset(ul))))
    O = fill(g0, NINE, patch)
    return O
```
evaluation 31f7f899 0.0 51.08196378334111 0.2898404926421201 0.0 51.37180427598324
```python
def dsl1(I):
    c = leastcolor(I)
    allidx = asindices(I)
    bg = ofcolor(I, EIGHT)
    nonbg = difference(allidx, bg)
    bbox = backdrop(nonbg)
    pcs = ofcolor(I, c)
    loc = first(pcs)
    col = vfrontier(loc)
    seg = intersection(bbox, col)
    O = underfill(I, c, seg)
    return O
```
evaluation dbff022c 0.0 51.604548205387594 0.22092209072978308 0.0 51.82547029611737
```python
def dsl1(I):
    objs = fgpartition(I)
    rb = rbind(toobject, I)
    co = compose(rb, outbox)
    pick = compose(mostcolor, co)
    add = mapply(fork(recolor, pick, delta), objs)
    O = underpaint(I, add)
    return O
```
evaluation 8e5c0c38 0.0 54.957926564872906 0.08471074380165278 0.02272727272362032 55.065364581398185
```python
def dsl1(I):
    bg = mostcolor(I)
    cols = remove(bg, palette(I))
    oc = lbind(ofcolor, I)
    tobj = rbind(toobject, I)
    corner = compose(initset, ulcorner)
    f = chain(corner, tobj, oc)
    uls = mapply(f, cols)
    O = fill(I, bg, uls)
    return O
```
evaluation 36a08778 0.0 56.04153412313651 1.756980447627769 0.0 57.798514570764276
```python
def dsl4(I):
    # Draw a one-cell outer frame (outbox) around each BLUE object, background-only.
    O = I
    blue_objs = colorfilter(objects(I, True, False, True), TWO)
    patch = set()
    for obj in blue_objs:
        inds = toindices(obj)
        # outbox: ring just outside the bounding box of the object
        ring = outbox(inds)
        for rc in ring:
            if index(O, rc) == SEVEN:
                patch.add(rc)
    if patch:
        O = fill(O, SIX, frozenset(patch))
    return O
```
evaluation 2b83f449 0.0 59.480873808675625 0.1929734352334972 0.0 59.67384724390912
```python
def dsl1(I):
    # 7 -> 8; put 6 at centers of 7-runs and one row above and below; keep 3s
    objs = objects(I, T, F, T)
    sev = colorfilter(objs, SEVEN)
    centers = merge(apply(initset, apply(center, sev)))
    up = shift(centers, UP)
    down = shift(centers, DOWN)
    p6 = combine(centers, combine(up, down))
    O0 = replace(I, SEVEN, EIGHT)
    O = fill(O0, SIX, p6)
    return O
```
evaluation 136b0064 0.0 60.33144731120247 0.7963284835465286 1.317944478778292 62.44572027352729
```python
def dsl2(I):
    h = height(I)
    j4 = leftmost(ofcolor(I, FOUR))
    start = add(j4, ONE)
    O = replace(crop(I, astuple(ZERO, start), astuple(h, SEVEN)), FOUR, ZERO)
    return O
```
evaluation de809cff 0.0 68.35904265380964 0.19944444444444442 0.011785113018386903 68.57027221127247
```python
def dsl1(I):
    # Fill inner zero holes with 8, then flip both 4- and 8-neighbor ring around 8 between the two FG colors
    objs = objects(I, T, F, F)
    zeros = colorfilter(objs, ZERO)
    inner_zeros = sfilter(zeros, compose(flip, rbind(bordering, I)))
    holes = merge(inner_zeros)
    G = fill(I, EIGHT, holes)
    eidx = ofcolor(G, EIGHT)
    nnei = mapply(neighbors, eidx)
    inei = mapply(ineighbors, eidx)
    ring = difference(combine(nnei, inei), eidx)
    pal = palette(I)
    pal1 = remove(ZERO, pal)
    pal2 = remove(EIGHT, pal1)
    cmin = minimum(pal2)
    cmax = maximum(pal2)
    rmin = intersection(ring, ofcolor(I, cmin))
    rmax = intersection(ring, ofcolor(I, cmax))
    H = fill(G, cmax, rmin)
    O = fill(H, cmin, rmax)
    return O
```
evaluation 8b9c3697 0.0 68.30726047098938 0.35108137053217137 0.0 68.65834184152155
```python
def dsl5(I):
    # Hypothesis E: For each 2, find nearest 1 (Manhattan) and draw an L-shaped zero path (horizontal then vertical), excluding endpoints
    twos = ofcolor(I, TWO)
    ones = ofcolor(I, ONE)
    if size(twos) == 0 or size(ones) == 0:
        return I
    zero_patch = set()
    for (r2, c2) in twos:
        # Find nearest 1 by manhattan distance
        best = None
        bestd = None
        for (r1, c1) in ones:
            d = abs(r1 - r2) + abs(c1 - c2)
            if bestd is None or d < bestd:
                bestd = d
                best = (r1, c1)
        (r1, c1) = best
        # Horizontal segment from (r2, c2) to (r2, c1), excluding endpoints
        if c2 < c1:
            hrange = range(c2 + 1, c1)
        else:
            hrange = range(c1 + 1, c2)
        for j in hrange:
            zero_patch.add((r2, j))
        # Vertical segment from (r2, c1) to (r1, c1), excluding endpoints
        if r2 < r1:
            vrange = range(r2 + 1, r1)
        else:
            vrange = range(r1 + 1, r2)
        for i in vrange:
            zero_patch.add((i, c1))
    zero_patch = difference(frozenset(zero_patch), ones)
    O = fill(I, ZERO, zero_patch)
    return O
```
evaluation 80a900e0 0.0 72.47150340253208 0.2739357864357864 0.0 72.74543918896786
```python
def dsl5(I):
    # Extend only the highest-valued present color among {8,4,2,3} along counter-diagonals.
    O = I
    inds = asindices(I)
    dirs = insert(UP_RIGHT, initset(DOWN_LEFT))
    s2 = ofcolor(I, TWO)
    r2 = merge(prapply(shoot, s2, dirs))
    p2 = intersection(inds, combine(s2, r2))
    s3 = ofcolor(I, THREE)
    r3 = merge(prapply(shoot, s3, dirs))
    p3 = intersection(inds, combine(s3, r3))
    s4 = ofcolor(I, FOUR)
    r4 = merge(prapply(shoot, s4, dirs))
    p4 = intersection(inds, combine(s4, r4))
    s8 = ofcolor(I, EIGHT)
    r8 = merge(prapply(shoot, s8, dirs))
    p8 = intersection(inds, combine(s8, r8))
    c8 = greater(colorcount(I, EIGHT), ZERO)
    c4 = greater(colorcount(I, FOUR), ZERO)
    c2 = greater(colorcount(I, TWO), ZERO)
    psel = branch(c8, p8, branch(c4, p4, branch(c2, p2, p3)))
    O = paint(O, recolor(branch(c8, EIGHT, branch(c4, FOUR, branch(c2, TWO, THREE))), psel))
    return O
```
evaluation a395ee82 0.0 76.25606580760984 0.5909090909090909 0.0 76.84697489851894
```python
def dsl3(I):
    # Cross-stamping using largest object per color (instead of union), COM anchoring
    bg = mostcolor(I)
    shp = shape(I)
    cols = remove(bg, palette(I))
    colst = totuple(cols)
    c1 = first(colst)
    c2 = last(colst)
    allobjs = objects(I, T, F, T)
    oc1objs = colorfilter(allobjs, c1)
    oc2objs = colorfilter(allobjs, c2)
    o1 = argmax(oc1objs, size)
    o2 = argmax(oc2objs, size)
    s1 = normalize(toindices(o1))
    s2 = normalize(toindices(o2))
    a1 = shift(s1, invert(centerofmass(s1)))
    a2 = shift(s2, invert(centerofmass(s2)))
    oc1 = ofcolor(I, c1)
    oc2 = ofcolor(I, c2)
    stamps1 = apply(lbind(shift, a1), oc2)
    stamps2 = apply(lbind(shift, a2), oc1)
    u1 = merge(stamps1)
    u2 = merge(stamps2)
    obj1 = recolor(c1, u1)
    obj2 = recolor(c2, u2)
    out = canvas(bg, shp)
    # Paint the one with fewer pixels on top
    dfirst = greater(size(u1), size(u2))
    base = branch(dfirst, paint(out, obj1), paint(out, obj2))
    O = branch(dfirst, paint(base, obj2), paint(base, obj1))
    return O
```
evaluation b10624e5 0.0 80.24028314293236 0.33058984910836764 0.0 80.57087299204073
```python
def dsl1(I):
    A = replace(I, ONE, FOUR)
    H = hmirror(A)
    V = vmirror(A)
    R = rot180(A)
    O = I
    O = underpaint(O, asobject(H))
    O = underpaint(O, asobject(V))
    O = underpaint(O, asobject(R))
    return O
```
evaluation 4c416de3 0.0 80.63426627477867 0.21402505642169078 0.0 80.84829133120036
```python
def dsl2(I):
    # Same as dsl1 but overshoot by 2x the gravitate vector to place marks a bit further from source.
    objs = objects(I, T, F, T)
    zobjs = colorfilter(objs, ZERO)
    dst = merge(zobjs)
    nz = difference(objs, zobjs)
    vfun = compose(double, rbind(gravitate, dst))
    shifter = fork(shift, identity, vfun)
    stamper = fork(recolor, color, shifter)
    stamps = merge(apply(stamper, nz))
    O = underpaint(I, stamps)
    return O
```
evaluation faa9f03d 0.0 84.55420609303673 0.48611111111111105 0.312469050953864 85.3527862551017
```python
def dsl5(I):
    # Replace least common nonzero color with most common nonzero color
    cols = tuple(c for c in palette(I) if c != ZERO)
    if not cols:
        return I
    # compute counts
    counts = {c: colorcount(I, c) for c in cols}
    most = max(cols, key=lambda c: counts[c])
    least = min(cols, key=lambda c: counts[c])
    O = replace(I, least, most)
    return O
```
evaluation 800d221b 0.0 87.70069553063112 0.9625 0.0 88.66319553063111
```python
def dsl1(I):
    pal = palette(I)
    bg = valmax(pal, lbind(colorcount, I))
    pal1 = remove(bg, pal)
    target = valmax(pal1, lbind(colorcount, I))
    others = remove(target, pal1)
    a = first(others)
    b = other(others, a)

    L = lefthalf(I)
    R = righthalf(I)
    la = colorcount(L, a)
    lb = colorcount(L, b)
    leftseed = branch(greater(la, lb), a, b)
    rightseed = other(others, leftseed)

    O = hconcat(replace(L, target, leftseed), replace(R, target, rightseed))
    return O
```
evaluation 64efde09 0.0 88.54860634402235 0.3953572594079927 0.0 88.94396360343033
```python
def dsl4(I):
    # Edge-seed from the left border:
    # If a row starts with a non-background color at column 0,
    # extend that color rightward across background cells until hitting the next non-background cell.
    O = I
    H = height(I)
    W = width(I)
    for r in range(H):
        v0 = index(I, astuple(r, 0))
        if v0 == EIGHT:
            continue
        # find the first barrier (next non-background after col 0)
        jbar = None
        for j in range(1, W):
            if index(I, astuple(r, j)) != EIGHT:
                jbar = j
                break
        if jbar is None:
            jbar = W
        if jbar > 1:
            seg = connect(astuple(r, 0), astuple(r, jbar - 1))
            O = underfill(O, v0, seg)
    return O
```
evaluation a47bf94d 0.0 90.00209920038048 0.406026160074743 0.05160156870265786 90.4597269291579
```python
def dsl5(I):
    # Swap colors 1<->4 and 2<->3 using a temporary placeholder (7)
    x1 = switch(I, FOUR, SEVEN)
    x2 = switch(x1, ONE, FOUR)
    x3 = switch(x2, SEVEN, ONE)
    x4 = switch(x3, THREE, SEVEN)
    x5 = switch(x4, TWO, THREE)
    O = switch(x5, SEVEN, TWO)
    return O
```
evaluation 8b7bacbf 0.0 92.12966376865077 0.27702214452214446 0.0 92.40668591317291
```python
def dsl2(I):
    # Like dsl1 but explicitly require the two in-between cells to be empty (background) before bridging
    s = leastcolor(I)
    fg = difference(asindices(I), ofcolor(I, ZERO))
    colors = remove(ZERO, remove(s, palette(I)))
    p1 = compose(initset, first)
    p2 = compose(initset, last)
    aligned = fork(either, fork(hmatching, p1, p2), fork(vmatching, p1, p2))
    noteq = compose(flip, fork(equality, first, last))
    dist = fork(manhattan, p1, p2)
    eq3 = compose(rbind(equality, THREE), dist)
    seg = fork(connect, first, last)
    endpoints = fork(combine, p1, p2)
    between = fork(difference, seg, endpoints)
    empty_between = compose(rbind(equality, ZERO), compose(size, compose(rbind(intersection, fg), between)))
    def lines_for_c(c):
        idxs = ofcolor(I, c)
        pairs = product(idxs, idxs)
        cond = fork(both, fork(both, aligned, noteq), fork(both, eq3, empty_between))
        sel = sfilter(pairs, cond)
        segs = apply(seg, sel)
        return merge(segs)
    lines = mapply(lines_for_c, colors)
    O = underfill(I, s, lines)
    return O
```
evaluation 7b0280bc 0.0 94.90156146116843 0.40487654320987654 0.0 95.3064380043783
```python
def dsl3(I):
    TH = tophalf(I)
    bg = mostcolor(TH)
    pal = remove(bg, palette(TH))
    ordcols = order(pal, lbind(colorcount, TH))
    least = first(ordcols)
    rest = remove(least, pal)
    second = first(order(rest, lbind(colorcount, TH)))
    x1 = fill(I, FIVE, ofcolor(TH, least))
    O = fill(x1, THREE, ofcolor(TH, second))
    return O
```
evaluation 581f7754 0.0 95.12737240690838 0.7232962744326379 0.0 95.85066868134102
```python
def dsl1(I):
    # Move each center+ring group so its center aligns to the column of the uppermost isolated center (colors 1,2,4).
    O = I
    bg = mostcolor(I)
    W = width(I)
    unival = objects(I, T, F, T)

    # collect candidate center objects (colors 1,2,4)
    centers = initset(ORIGIN); centers = remove(ORIGIN, centers)
    for o in totuple(unival):
        c = color(o)
        if c == ONE or c == TWO or c == FOUR:
            centers = insert(o, centers)

    # isolated singleton centers = size==1 and not adjacent to any non-bg object
    isolated = initset(ORIGIN); isolated = remove(ORIGIN, isolated)
    for cobj in totuple(centers):
        if size(toindices(cobj)) != 1:
            continue
        adj_any = F
        for u in totuple(unival):
            if u == cobj:
                continue
            if color(u) == bg:
                continue
            if adjacent(cobj, u):
                adj_any = T
        if flip(adj_any):
            isolated = insert(cobj, isolated)

    # choose anchor: uppermost isolated; fallback to middle of right half
    if size(isolated) > 0:
        anc = argmin(isolated, uppermost)
        ai, aj = centerofmass(anc)
        targetj = aj
    else:
        targetj = add(divide(W, TWO), ONE)

    # move each center object that is adjacent to any non-center object; move its adjacent group too
    for cobj in totuple(centers):
        # check if this center participates in a composite (adjacent to any unival object of different color)
        has_adj = F
        for u in totuple(unival):
            if u == cobj:
                continue
            if color(u) == color(cobj):
                continue
            if adjacent(cobj, u):
                has_adj = T
        if flip(has_adj):
            continue
        ci, cj = centerofmass(cobj)
        dj = subtract(targetj, cj)
        if dj == 0:
            continue
        # collect adjacent group
        adjgroup = initset(ORIGIN); adjgroup = remove(ORIGIN, adjgroup)
        for u in totuple(unival):
            if u == cobj:
                continue
            if adjacent(cobj, u):
                adjgroup = insert(u, adjgroup)
        # cover then move center and its adjacent group
        O = cover(O, cobj)
        for u in totuple(adjgroup):
            O = cover(O, u)
        O = move(O, cobj, astuple(ZERO, dj))
        for u in totuple(adjgroup):
            O = move(O, u, astuple(ZERO, dj))
    return O
```
evaluation 9aaea919 0.0 96.5390827206231 0.24444444444444458 0.0 96.78352716506754
```python
def dsl3(I):
    # Remove border-touching horizontal bars, then recolor the rightmost remaining non-bar object's color to FIVE
    bg = mostcolor(I)
    objs = objects(I, T, F, T)
    pred_bar = fork(both, hline, rbind(bordering, I))
    bars = sfilter(objs, pred_bar)
    bar_inds = mapply(toindices, bars)
    I1 = fill(I, bg, bar_inds)
    nonbars = difference(objs, bars)
    right_obj = argmax(nonbars, rightmost)
    target = color(right_obj)
    O = replace(I1, target, FIVE)
    return O
```
evaluation 7666fa5d 0.0 102.10054563633447 0.39453125 0.0 102.49507688633447
```python
def dsl4(I):
    # Row-priority: fill 2 between row seeds but suppress where a closer column seed competes (nearest-seed dominance)
    bg = mostcolor(I)
    h, w = shape(I)
    INF = h + w + 5
    def nearest_row_dists(i, j):
        dl = INF
        for jj in range(j-1, -1, -1):
            if index(I, (i, jj)) != bg:
                dl = j - jj
                break
        dr = INF
        for jj in range(j+1, w):
            if index(I, (i, jj)) != bg:
                dr = jj - j
                break
        return dl, dr
    def nearest_col_dists(i, j):
        du = INF
        for ii in range(i-1, -1, -1):
            if index(I, (ii, j)) != bg:
                du = i - ii
                break
        dd = INF
        for ii in range(i+1, h):
            if index(I, (ii, j)) != bg:
                dd = ii - i
                break
        return du, dd
    fillset = set()
    for i in range(h):
        for j in range(w):
            if index(I, (i, j)) != bg:
                continue
            dl, dr = nearest_row_dists(i, j)
            if dl < INF and dr < INF:
                dmin = dl if dl < dr else dr
                du, dd = nearest_col_dists(i, j)
                cmin = du if du < dd else dd
                if cmin >= dmin:
                    fillset.add((i, j))
    O = fill(I, TWO, frozenset(fillset))
    return O
```
evaluation a25697e4 0.0 106.43436837920817 0.37111111111111117 0.0 106.80547949031927
```python
def dsl1(I):
    # Slide all foreground to touch the left border (preserve vertical placement)
    bg = mostcolor(I)
    dims = shape(I)
    fg = merge(objects(I, T, F, T))
    left_border = vfrontier(ORIGIN)
    off = gravitate(fg, left_border)
    moved = shift(fg, off)
    O = canvas(bg, dims)
    O = paint(O, moved)
    return O
```
evaluation d35bdbdc 0.0 107.82257500081998 1.1099999999999999 0.2745736123956079 109.2071486132156
```python
def dsl2(I):
    # Keep rings in the most populated column lane; tiebreaker: choose the lane closest to the right border.
    # Fill kept centers top-to-bottom with ascending donor center values.
    obs = objects(I, T, F, T)
    O = canvas(ZERO, shape(I))
    h, w = shape(I)
    rings = []
    lines5 = []
    for obj in totuple(obs):
        if (width(obj) == 3 and height(obj) == 3 and size(obj) >= 8):
            rings.append(obj)
        elif color(obj) == FIVE and (hline(obj) or vline(obj)):
            lines5.append(obj)
    if rings:
        colgroups = {}
        for r in rings:
            lcol = leftmost(r)
            colgroups[lcol] = colgroups.get(lcol, []) + [r]
        best_col = None
        best_count = -1
        for cc, lst in colgroups.items():
            # prefer lane nearer the right (larger column) on ties
            if len(lst) > best_count or (len(lst) == best_count and (best_col is None or cc > best_col)):
                best_col = cc
                best_count = len(lst)
        keep = set(colgroups.get(best_col, []))
        donors = []
        for r in rings:
            if r not in keep:
                val = index(I, center(r))
                if val != ZERO:
                    donors.append(val)
        donors.sort()
        keep_sorted = sorted(list(keep), key=lambda r: uppermost(r))
        for r in keep_sorted:
            O = paint(O, r)
        for i, r in enumerate(keep_sorted):
            if i < len(donors):
                O = fill(O, donors[i], initset(center(r)))
    for ln in lines5:
        O = paint(O, ln)
    return O
```
evaluation 7ed72f31 0.0 109.43787203892614 0.40005353993449244 0.0 109.83792557886063
```python
def dsl1(I):
    # Mirror all non-2 objects across every detected '2' axis (vertical lines, horizontal lines, and single pivots).
    H = height(I)
    W = width(I)
    O = I
    twos = colorfilter(objects(I, True, False, True), TWO)

    for ax in twos:
        if vline(ax):
            c = leftmost(ax)
            dc = subtract(double(c), decrement(W))
            VM = vmirror(I)
            vm_objs = objects(VM, True, False, True)
            vm_non2 = difference(vm_objs, colorfilter(vm_objs, TWO))
            for obj in vm_non2:
                O = underpaint(O, shift(obj, astuple(ZERO, dc)))
        elif hline(ax):
            r = uppermost(ax)
            dr = subtract(double(r), decrement(H))
            HM = hmirror(I)
            hm_objs = objects(HM, True, False, True)
            hm_non2 = difference(hm_objs, colorfilter(hm_objs, TWO))
            for obj in hm_non2:
                O = underpaint(O, shift(obj, astuple(dr, ZERO)))
        else:
            r = uppermost(ax)
            c = leftmost(ax)
            dr = subtract(double(r), decrement(H))
            dc = subtract(double(c), decrement(W))
            R = rot180(I)
            r_objs = objects(R, True, False, True)
            r_non2 = difference(r_objs, colorfilter(r_objs, TWO))
            for obj in r_non2:
                O = underpaint(O, shift(obj, astuple(dr, dc)))
    return O
```
evaluation 4c3d4a41 0.0 112.01349933074033 0.9312500000000001 0.2785430072009226 113.22329233794125
```python
def dsl3(I):
    # Frame (top, bottom, right) + keep 5s only in the top half on columns that contain non-FIVEs
    dims = shape(I)
    objs = objects(I, T, F, T)
    fiveobjs = colorfilter(objs, FIVE)
    non5objs = difference(objs, fiveobjs)
    non5 = merge(non5objs)
    n5idx = toindices(non5)

    topRow = hfrontier(astuple(0, 0))
    topFives = intersection(ofcolor(I, FIVE), topRow)
    j0 = leftmost(topFives)

    topRight = shoot(astuple(0, j0), RIGHT)
    rightPlane = merge(apply(vfrontier, topRight))
    rect = backdrop(rightPlane)

    ul = ulcorner(rect)
    ur = urcorner(rect)
    ll = llcorner(rect)
    lr = lrcorner(rect)

    topEdge = connect(ul, ur)
    bottomEdge = connect(ll, lr)
    rightEdge = connect(ur, lr)
    edges = combine(combine(topEdge, bottomEdge), rightEdge)

    colsMask = merge(apply(vfrontier, n5idx))
    topHalf = asindices(tophalf(I))
    colsTop = intersection(colsMask, topHalf)
    colsTopRight = intersection(colsTop, rightPlane)

    allowed = combine(edges, colsTopRight)

    O0 = canvas(ZERO, dims)
    O1 = fill(O0, FIVE, allowed)
    O = paint(O1, non5)
    return O
```
evaluation abc82100 0.0 111.80796838977568 0.861111111111111 0.9388683785416393 113.60794787942844
```python
def dsl1(I):
    sh = shape(I)
    Z = canvas(ZERO, sh)
    objs = objects(I, T, F, T)
    hobjs = sfilter(objs, hline)
    vobjs = sfilter(objs, vline)
    H = argmax(hobjs, size)
    V = argmax(vobjs, size)
    rH = recolor(TWO, H)
    rV = recolor(ONE, V)
    O = paint(paint(Z, rH), rV)
    return O
```
evaluation 269e22fb 0.0 112.37892330479512 2.8100000000000005 0.0 115.18892330479513
```python
def dsl3(I):
    A = hconcat(I, rot90(I))
    B = hconcat(rot270(I), rot180(I))
    C = vconcat(A, B)
    D = hconcat(C, C)
    E = vconcat(D, D)
    O = crop(E, ORIGIN, (20, 20))
    return O
```
evaluation 7c66cb00 0.0 116.55601915870366 0.4930555555555556 0.0 117.04907471425922
```python
def dsl2(I):
    # Clear top half; for the two largest bands, stamp a 3x1 horizontal tiling
    # of the smallest same-color exemplar’s delta, recolored with the flank color.
    bg = mostcolor(I)
    O = vconcat(canvas(bg, shape(tophalf(I))), bottomhalf(I))

    objs = objects(I, T, F, T)

    # First band
    big1 = argmax(objs, size)
    same1 = colorfilter(objs, color(big1))
    small1 = argmin(remove(big1, same1), size)
    mot = delta(small1)
    w = width(mot)
    dv = tojvec(w)
    r0 = mot
    r1 = shift(mot, dv)
    r2 = shift(mot, double(dv))
    S = insert(r0, initset(r0))
    S = insert(r1, S)
    S = insert(r2, S)
    row = merge(S)
    off1 = subtract(ulcorner(big1), ulcorner(small1))
    row1s = shift(row, off1)
    col1 = index(I, add(ulcorner(big1), LEFT))
    O = fill(O, col1, row1s)

    # Second band
    objs2 = remove(big1, objs)
    big2 = argmax(objs2, size)
    same2 = colorfilter(objs, color(big2))
    small2 = argmin(remove(big2, same2), size)
    mot2 = delta(small2)
    w2 = width(mot2)
    dv2 = tojvec(w2)
    q0 = mot2
    q1 = shift(mot2, dv2)
    q2 = shift(mot2, double(dv2))
    Q = insert(q0, initset(q0))
    Q = insert(q1, Q)
    Q = insert(q2, Q)
    row2 = merge(Q)
    off2 = subtract(ulcorner(big2), ulcorner(small2))
    row2s = shift(row2, off2)
    col2 = index(I, add(ulcorner(big2), LEFT))
    O = fill(O, col2, row2s)

    return O
```
evaluation 35ab12c3 0.0 121.59668538219366 0.3961753590325019 0.034513545266241064 122.02737428649239
```python
def dsl1(I):
    # Connect every pair of same-color objects (no row/col restriction)
    O = I
    obs = totuple(objects(I, T, F, T))
    for a in obs:
        ca = color(a)
        la = ulcorner(a)
        for b in obs:
            if a == b:
                continue
            if color(b) != ca:
                continue
            lb = ulcorner(b)
            seg = connect(la, lb)
            O = fill(O, ca, seg)
    return O
```
evaluation b99e7126 0.0 121.91016411066687 0.26634958382877527 0.0 122.17651369449564
```python
def dsl1(I):
    # Hypothesis 1: Vertically propagate the least frequent color object upward by the tile step (4) across multiple bands.
    c = leastcolor(I)
    obj = toobject(ofcolor(I, c), I)
    u4 = shift(obj, toivec(-4))
    u8 = shift(obj, toivec(-8))
    u12 = shift(obj, toivec(-12))
    u16 = shift(obj, toivec(-16))
    u20 = shift(obj, toivec(-20))
    u24 = shift(obj, toivec(-24))
    O = paint(I, u4)
    O = paint(O, u8)
    O = paint(O, u12)
    O = paint(O, u16)
    O = paint(O, u20)
    O = paint(O, u24)
    return O
```
evaluation c7f57c3e 0.0 124.15556218542562 0.5087238599143361 0.0 124.66428604533996
```python
def dsl2(I):
    # Swap top-right and bottom-left quadrants
    top = tophalf(I)
    bot = bottomhalf(I)
    tl = lefthalf(top)
    tr = righthalf(top)
    bl = lefthalf(bot)
    br = righthalf(bot)
    new_top = hconcat(tl, bl)
    new_bot = hconcat(tr, br)
    O = vconcat(new_top, new_bot)
    return O
```
evaluation c4d067a0 0.0 125.51196653490956 0.41125813904641884 0.0 125.92322467395599
```python
def dsl3(I):
    # Downward tiling (h+2) using two different non-bg colors (min and max), also place right neighbor
    bg = mostcolor(I)
    objs = objects(I, T, F, T)
    seed = argmax(objs, size)
    ul = ulcorner(seed)
    h = height(seed)
    w = width(seed)
    dy = add(h, TWO)
    dx = add(w, TWO)
    boxn = normalize(backdrop(seed))
    p = palette(I)
    pnb = remove(bg, p)
    c1 = minimum(pnb)
    c2 = maximum(pnb)
    O = fill(I, c1, shift(boxn, add(ul, toivec(dy))))
    O = fill(O, c1, shift(boxn, add(add(ul, toivec(dy)), tojvec(dx))))
    O = fill(O, c2, shift(boxn, add(ul, toivec(double(dy)))))
    O = fill(O, c2, shift(boxn, add(add(ul, toivec(double(dy))), tojvec(dx))))
    return O
```
evaluation 221dfab4 0.0 126.70931354818748 0.7033199582027168 0.0 127.4126335063902
```python
def dsl4(I):
    # Only project 4 vertically onto 8-cells and add top 3 header; do not modify 2s.
    objs = objects(I, T, F, T)
    obj4s = colorfilter(objs, FOUR)
    b4 = merge(obj4s)
    idx4 = toindices(b4)
    up4 = merge(apply(rbind(shoot, UP), idx4))
    down4 = merge(apply(rbind(shoot, DOWN), idx4))
    stripes4 = combine(combine(up4, down4), idx4)
    tgt8 = ofcolor(I, EIGHT)
    O = fill(I, FOUR, intersection(stripes4, tgt8))
    b4_idx = toindices(b4)
    top_edge = intersection(backdrop(b4_idx), hfrontier(ulcorner(b4)))
    upoff = toivec(invert(uppermost(b4)))
    top_header = shift(top_edge, upoff)
    O = fill(O, THREE, top_header)
    return O
```
evaluation 71e489b6 0.0 127.89391465342443 0.34302841202270373 0.16798385939340899 128.40492692484054
```python
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
evaluation edb79dae 0.0 130.45590545877832 1.4196370045994104 0.0 131.8755424633777
```python
def dsl1(I):
    # Extract the largest 5-colored frame, remove it to get the inner pattern,
    # recolor the two least frequent inner colors to 2 and 4, and re-frame with 5.
    obs = objects(I, T, F, T)
    fobs = colorfilter(obs, FIVE)
    five = argmax(fobs, size)
    C = subgrid(five, I)
    bgI = mostcolor(I)
    Inner = trim(replace(C, FIVE, bgI))
    bg = mostcolor(Inner)
    pal = remove(bg, palette(Inner))
    c1 = valmin(pal, lbind(colorcount, Inner))
    pal2 = remove(c1, pal)
    has2 = greater(size(pal2), ZERO)
    c2 = branch(has2, valmin(pal2, lbind(colorcount, Inner)), c1)
    tmp1 = replace(Inner, c1, TWO)
    tmp2 = replace(tmp1, c2, FOUR)
    dims = add(shape(tmp2), TWO_BY_TWO)
    Base = canvas(bgI, dims)
    Framed = fill(Base, FIVE, box(asindices(Base)))
    O = move(Framed, asobject(tmp2), UNITY)
    return O
```
evaluation 89565ca0 2.0 80.39619148757622 51.06666666666667 0.1414213561373095 133.6042795103802
```python
def dsl3(I):
    # Rank-based quantization by count: k = ceil(4 * rank / n), filler = color with most connected components
    pal = palette(I)
    colors = [c for c in totuple(pal) if c != ZERO]
    objs = objects(I, T, T, T)
    comp_counts = {}
    for obj in totuple(objs):
        c = color(obj)
        comp_counts[c] = comp_counts.get(c, 0) + 1
    pepper = max(comp_counts, key=lambda c: comp_counts[c]) if comp_counts else colors[0]
    mains = [c for c in colors if c != pepper]
    if not mains:
        return tuple()
    cnts = {c: colorcount(I, c) for c in mains}
    mains_sorted = sorted(mains, key=lambda c: (cnts[c], c))  # ascending by count then color
    n = len(mains_sorted)
    rows = []
    for idx, c in enumerate(mains_sorted):
        rank = idx + 1
        k = (4*rank + n - 1) // n
        if k < 1: k = 1
        if k > 4: k = 4
        rows.append(tuple([c]*k + [pepper]*(4-k)))
    O = tuple(rows)
    return O
```
evaluation 6e453dd6 0.0 133.41132653879316 0.6327083333333334 0.0 134.04403487212647
```python
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
```
evaluation 247ef758 0.0 148.90185441391557 0.9126455026455026 0.08933752450812799 149.90383744106921
```python
def dsl5(I):
    # Symmetrize the grid across the spine: copy right-of-spine (including spine) to both sides
    h = height(I)
    w = width(I)
    O = canvas(ZERO, astuple(h, w))

    spine_j = None
    for obj in objects(I, T, F, T):
        if vline(obj) and height(obj) == h:
            spine_j = leftmost(obj)
            break

    if spine_j is None:
        return I

    for i in range(h):
        for j in range(spine_j, w):
            c = index(I, astuple(i, j))
            # place on right
            O = fill(O, c, initset(astuple(i, j)))
            # mirror to the left of spine
            jL = 2 * spine_j - j
            if jL >= 0:
                O = fill(O, c, initset(astuple(i, jL)))

    return O
```
evaluation d59b0160 0.0 152.0204072906123 0.8046875 0.0 152.8250947906123
```python
def dsl3(I):
    # For each row, clear everything strictly after the last 7 in that row
    h, w = shape(I)
    O = []
    for i in range(h):
        row = list(I[i])
        last7 = -1
        for j in range(w):
            if row[j] == SEVEN:
                last7 = j
        if last7 < w - 1:
            for j in range(last7 + 1, w):
                row[j] = SEVEN
        O.append(tuple(row))
    return tuple(O)
```
evaluation 8f215267 0.0 162.689644935594 0.7266960722537281 0.0 163.41634100784773
```python
def dsl1(I):
    # Keep large rectangular frames and add a solid center horizontal line inside each
    bg = mostcolor(I)
    O = canvas(bg, shape(I))
    for obj in objects(I, True, False, True):
        if size(obj) > 30:
            col = color(obj)
            O = paint(O, obj)
            inner = inbox(obj)
            if size(inner) == 0:
                continue
            c = center(inner)
            hr = hfrontier(c)
            O = fill(O, col, intersection(hr, inner))
    return O
```
evaluation 2c181942 0.0 169.28520581352666 0.5301292314770576 0.0 169.81533504500374
```python
def dsl2(I):
    O = rot180(I)
    return O
```
evaluation cbebaa4b 0.0 168.87304312615495 0.7845982688640031 0.47017653190041714 170.12781792691936
```python
def dsl3(I):
    # Catalog: for each nonzero color, draw a 4x5 hollow rectangle tile stacked, centered horizontally
    H, W = shape(I)
    O = canvas(ZERO, (H, W))
    cols = sorted([c for c in palette(I) if c != ZERO])
    hrect, wrect = 4, 5
    r = 0
    for c in cols:
        if r + hrect > H:
            break
        idxs = set()
        for i in range(hrect):
            for j in range(wrect):
                if i == 0 or i == hrect - 1 or j == 0 or j == wrect - 1:
                    idxs.add((i, j))
        tile = frozenset(idxs)
        cc = (W - wrect) // 2
        obj = recolor(c, tile)
        O = paint(O, shift(obj, (r, cc)))
        r += hrect + 1
    return O
```
evaluation 6e4f6532 0.0 171.2657088422174 0.5560844604113835 0.0 171.8217933026288
```python
def dsl2(I):
    h = height(I)
    w = width(I)
    top2 = crop(I, (0, 0), (2, w))
    bottom2 = crop(I, (h - 2, 0), (2, w))
    left2_mid = crop(I, (2, 0), (h - 4, 2))
    right2_mid = crop(I, (2, w - 2), (h - 4, 2))
    center = crop(I, (2, 2), (h - 4, w - 4))
    center_h = hmirror(center)
    middle = hconcat(hconcat(left2_mid, center_h), right2_mid)
    O = vconcat(vconcat(top2, middle), bottom2)
    return O
```
evaluation db0c5428 0.0 170.34203845297387 1.5624042723301486 0.0 171.90444272530402
```python
def dsl4(I):
    # Spaced 3x3 tiling plus fill the four gap-intersection 3x3 blocks with the central tile.
    t = trim(I)
    nb = difference(asindices(I), ofcolor(I, EIGHT))
    r0 = uppermost(nb)
    c0 = leftmost(nb)
    rr = subtract(r0, THREE)
    cc = subtract(c0, THREE)
    O = canvas(EIGHT, shape(I))
    b00 = asobject(crop(t, astuple(ZERO, ZERO), THREE_BY_THREE))
    b01 = asobject(crop(t, astuple(ZERO, THREE), THREE_BY_THREE))
    b02 = asobject(crop(t, astuple(ZERO, SIX), THREE_BY_THREE))
    b10 = asobject(crop(t, astuple(THREE, ZERO), THREE_BY_THREE))
    b11 = asobject(crop(t, astuple(THREE, THREE), THREE_BY_THREE))
    b12 = asobject(crop(t, astuple(THREE, SIX), THREE_BY_THREE))
    b20 = asobject(crop(t, astuple(SIX, ZERO), THREE_BY_THREE))
    b21 = asobject(crop(t, astuple(SIX, THREE), THREE_BY_THREE))
    b22 = asobject(crop(t, astuple(SIX, SIX), THREE_BY_THREE))
    # place nine tiles
    O = underpaint(O, shift(b00, astuple(rr, cc)))
    O = underpaint(O, shift(b01, astuple(rr, add(cc, SIX))))
    O = underpaint(O, shift(b02, astuple(rr, add(cc, multiply(SIX, TWO)))))
    O = underpaint(O, shift(b10, astuple(add(rr, SIX), cc)))
    O = underpaint(O, shift(b11, astuple(add(rr, SIX), add(cc, SIX))))
    O = underpaint(O, shift(b12, astuple(add(rr, SIX), add(cc, multiply(SIX, TWO)))))
    O = underpaint(O, shift(b20, astuple(add(rr, multiply(SIX, TWO)), cc)))
    O = underpaint(O, shift(b21, astuple(add(rr, multiply(SIX, TWO)), add(cc, SIX))))
    O = underpaint(O, shift(b22, astuple(add(rr, multiply(SIX, TWO)), add(cc, multiply(SIX, TWO)))))
    # fill four central gap intersections with the central tile
    O = underpaint(O, shift(b11, astuple(add(rr, THREE), add(cc, THREE))))
    O = underpaint(O, shift(b11, astuple(add(rr, THREE), add(cc, add(THREE, SIX)))))
    O = underpaint(O, shift(b11, astuple(add(rr, add(THREE, SIX)), add(cc, THREE))))
    O = underpaint(O, shift(b11, astuple(add(rr, add(THREE, SIX)), add(cc, add(THREE, SIX)))))
    return O
```
evaluation 4a21e3da 0.0 175.20335601150367 0.8427160493827159 0.0 176.0460720608864
```python
def dsl3(I):
    # Only horizontal symmetry for 7s and horizontal 2-line at r = lowermost(2)
    s2 = ofcolor(I, TWO)
    if size(s2) == 0:
        return I
    r = lowermost(s2)
    H = height(I)
    W = width(I)
    G = asindices(I)
    drow = subtract(double(r), subtract(H, ONE))
    s7h = ofcolor(hmirror(I), SEVEN)
    p7h = intersection(shift(s7h, astuple(drow, ZERO)), G)
    base = underpaint(I, recolor(SEVEN, p7h))
    # Horizontal 2-line at row r
    L = astuple(r, ZERO)
    R = astuple(r, subtract(W, ONE))
    hline = combine(shoot(L, RIGHT), shoot(R, LEFT))
    O = underfill(base, TWO, hline)
    return O
```
evaluation e12f9a14 0.0 176.0873027668561 0.6340277777777779 0.09501461874706392 176.81634516338096
```python
def dsl1(I):
    # Rays from each 2x2 non-3 block: UP, RIGHT, and DOWN_LEFT, along background only.
    O = I
    bg0 = ofcolor(I, EIGHT)
    parts = fgpartition(I)
    cols = remove(EIGHT, remove(THREE, palette(I)))
    dirs = (UP, RIGHT, DOWN_LEFT)
    for c in totuple(cols):
        cobjs = colorfilter(parts, c)
        twobytwos = sizefilter(cobjs, FOUR)
        for blk in totuple(twobytwos):
            if not square(blk):
                continue
            cells = toindices(blk)
            for d in dirs:
                nbr = intersection(shift(cells, d), bg0)
                if size(nbr) == 0:
                    continue
                starts = totuple(nbr)
                ds = repeat(d, size(nbr))
                lines = prapply(shoot, starts, ds)
                rays = merge(lines)
                patch = intersection(rays, bg0)
                O = fill(O, c, patch)
    return O
```
evaluation e3721c99 0.0 178.93189441677762 0.8922222222222221 0.04714045207354761 179.8712570910734
```python
def dsl3(I):
    c = leastcolor(tophalf(I))
    O = replace(I, FIVE, c)
    return O
```
evaluation cb2d8a2c 0.0 179.99935556933042 0.6606832650913074 0.0 180.66003883442173
```python
def dsl1(I):
    # Replace 1->2, then for each 2-object draw its top and left bbox edges with 3
    x = replace(I, ONE, TWO)
    objs = objects(x, T, F, T)
    twos = colorfilter(objs, TWO)
    seg_top = fork(connect, ulcorner, urcorner)
    seg_left = fork(connect, ulcorner, llcorner)
    edges_fun = fork(combine, seg_top, seg_left)
    edges = mapply(edges_fun, twos)
    O = underpaint(x, recolor(THREE, edges))
    return O
```
evaluation 9385bd28 0.0 187.6955080716013 1.5130602524410575 0.0 189.20856832404237
```python
def dsl4(I):
    # Per-object bounding-box fill (underpaint)
    comps = objects(I, T, F, T)
    rects = apply(fork(recolor, color, backdrop), comps)
    merged = merge(rects)
    O = underpaint(I, merged)
    return O
```
evaluation 271d71e2 0.0 191.10171983095827 1.4116724279919648 0.0 192.51339225895023
```python
def dsl5(I):
    union = combine(ofcolor(I, ZERO), combine(ofcolor(I, FIVE), ofcolor(I, SEVEN)))
    obj = toobject(union, I)
    off = gravitate(obj, ofcolor(I, NINE))
    O = move(I, obj, off)
    return O
```
evaluation 5961cc34 0.0 201.27856373993853 0.4992346438079127 0.0 201.77779838374644
```python
def dsl2(I):
    h, w = shape(I)
    O = canvas(EIGHT, astuple(h, w))
    p4 = first(ofcolor(I, FOUR))
    col = vfrontier(p4)
    O = fill(O, TWO, col)
    return O
```
evaluation 16b78196 0.0 200.88003758994552 0.8111111111111111 0.23904362576628393 201.9301923268229
```python
def dsl1(I):
    O = hmirror(I)
    return O
```
evaluation 3e6067c3 0.0 216.0933165033245 1.0123502278562393 0.0 217.10566673118075
```python
def dsl1(I):
    # Hypothesis A: Horizontally dilate only the non-1, non-background colors across 8s until blocked.
    objs = objects(I, T, F, T)
    non1 = difference(objs, colorfilter(objs, ONE))
    seed = merge(non1)
    O = I
    # spread right (12 steps)
    s = shift(seed, RIGHT); O = underpaint(O, s)
    s = shift(s, RIGHT);    O = underpaint(O, s)
    s = shift(s, RIGHT);    O = underpaint(O, s)
    s = shift(s, RIGHT);    O = underpaint(O, s)
    s = shift(s, RIGHT);    O = underpaint(O, s)
    s = shift(s, RIGHT);    O = underpaint(O, s)
    s = shift(s, RIGHT);    O = underpaint(O, s)
    s = shift(s, RIGHT);    O = underpaint(O, s)
    s = shift(s, RIGHT);    O = underpaint(O, s)
    s = shift(s, RIGHT);    O = underpaint(O, s)
    s = shift(s, RIGHT);    O = underpaint(O, s)
    s = shift(s, RIGHT);    O = underpaint(O, s)
    # spread left (12 steps)
    s = shift(seed, LEFT);  O = underpaint(O, s)
    s = shift(s, LEFT);     O = underpaint(O, s)
    s = shift(s, LEFT);     O = underpaint(O, s)
    s = shift(s, LEFT);     O = underpaint(O, s)
    s = shift(s, LEFT);     O = underpaint(O, s)
    s = shift(s, LEFT);     O = underpaint(O, s)
    s = shift(s, LEFT);     O = underpaint(O, s)
    s = shift(s, LEFT);     O = underpaint(O, s)
    s = shift(s, LEFT);     O = underpaint(O, s)
    s = shift(s, LEFT);     O = underpaint(O, s)
    s = shift(s, LEFT);     O = underpaint(O, s)
    s = shift(s, LEFT);     O = underpaint(O, s)
    return O
```
evaluation aa4ec2a5 0.0 216.94821389975186 0.8153554175293306 0.0 217.76356931728117
```python
def dsl5(I):
    # For each 1-object, draw 2 outbox, 8 border, and a 6 cross through the center of its bbox
    O = I
    onesobjs = colorfilter(objects(I, True, False, True), ONE)
    for obj in onesobjs:
        rect = backdrop(obj)
        c = center(rect)
        li = leftmost(rect)
        ri = rightmost(rect)
        ui = uppermost(rect)
        lo = lowermost(rect)
        hlinep = connect(astuple(c[0], li), astuple(c[0], ri))
        vlinep = connect(astuple(ui, c[1]), astuple(lo, c[1]))
        cross = combine(hlinep, vlinep)
        O = fill(O, SIX, cross)
        O = underpaint(O, recolor(TWO, outbox(rect)))
        O = underpaint(O, recolor(EIGHT, box(rect)))
    return O
```
evaluation 446ef5d2 0.0 223.38567318180623 1.9608333333333334 0.0 225.34650651513954
```python
def dsl2(I):
    # Draw separate rectangles around each non-dominant color at their original locations; border=dominant color; interior=that color
    sh = shape(I)
    P = remove(EIGHT, palette(I))
    cframe = valmax(P, lbind(colorcount, I))
    Pn = remove(cframe, P)
    cA = branch(greater(size(Pn), ZERO), valmax(Pn, lbind(colorcount, I)), cframe)
    Pn2 = remove(cA, Pn)
    cB = branch(greater(size(Pn2), ZERO), valmax(Pn2, lbind(colorcount, I)), cA)
    O = canvas(EIGHT, sh)
    iA = ofcolor(I, cA)
    bbA = backdrop(iA)
    brdA = box(bbA)
    innA = difference(bbA, brdA)
    O = fill(O, cframe, brdA)
    O = fill(O, cA, innA)
    iB = ofcolor(I, cB)
    bbB = backdrop(iB)
    brdB = box(bbB)
    innB = difference(bbB, brdB)
    O = fill(O, cframe, brdB)
    O = fill(O, cB, innB)
    return O
```
evaluation dfadab01 0.0 234.2963818561507 1.9275 0.35799379034161016 236.5818756464923
```python
def dsl5(I):
    # 2x2 filled blocks at each nonzero seed with simple mapping and mirrored replication
    H = height(I)
    W = width(I)
    C = canvas(ZERO, shape(I))
    safeB = asindices(canvas(ZERO, astuple(subtract(H, ONE), subtract(W, ONE))))
    def stamp2x2(cin, cout, X):
        S = intersection(ofcolor(I, cin), safeB)
        pf = fork(combine, initset, compose(rbind(shift, UNITY), initset))
        R = mapply(backdrop, apply(pf, S))
        return paint(X, recolor(cout, R))
    X = C
    X = stamp2x2(TWO, FOUR, X)
    X = stamp2x2(THREE, ONE, X)
    X = stamp2x2(FIVE, SIX, X)
    X = stamp2x2(EIGHT, SEVEN, X)
    # optional: include 6->1
    X = stamp2x2(SIX, ONE, X)
    # mirror-replicate
    O = paint(paint(paint(X, asobject(vmirror(X))), asobject(hmirror(X))), asobject(rot180(X)))
    return O
```
evaluation b6f77b65 0.0 241.02971994631952 2.784722222222222 0.23570226032607142 244.0501444288678
```python
def dsl5(I):
    h = height(I)
    w = width(I)
    bh = divide(h, THREE)
    bw = divide(w, THREE)
    t00 = crop(I, ORIGIN, astuple(bh, bw))
    t01 = crop(I, astuple(0, bw), astuple(bh, bw))
    t02 = crop(I, astuple(0, multiply(bw, TWO)), astuple(bh, bw))
    t10 = crop(I, astuple(bh, 0), astuple(bh, bw))
    t11 = crop(I, astuple(bh, bw), astuple(bh, bw))
    t12 = crop(I, astuple(bh, multiply(bw, TWO)), astuple(bh, bw))
    t20 = crop(I, astuple(multiply(bh, TWO), 0), astuple(bh, bw))
    t21 = crop(I, astuple(multiply(bh, TWO), bw), astuple(bh, bw))
    t22 = crop(I, astuple(multiply(bh, TWO), multiply(bw, TWO)), astuple(bh, bw))
    r0 = hconcat(hconcat(t00, t10), t20)
    r1 = hconcat(hconcat(t01, t11), t21)
    r2 = hconcat(hconcat(t02, t12), t22)
    O = vconcat(vconcat(r0, r1), r2)
    return O
```
evaluation e8686506 5.06449510224598 40.0 199.0 0.31272979286520497 244.37722489511117
```python
def dsl5(I):
    bg = mostcolor(I)
    big = argmax(objects(I, T, F, T), size)
    c = color(big)
    x = switch(I, bg, c)
    idx = difference(asindices(x), ofcolor(x, c))
    sub = subgrid(idx, x)
    O = downscale(compress(sub), TWO)
    return O
```
evaluation 0934a4d8 3.0 223.83060023690985 30.53154761904762 1.0 258.36214785595746
```python
def dsl1(I):
    # crop the same-sized block immediately to the left of the 8-rectangle
    p = ofcolor(I, EIGHT)
    G = subgrid(p, I)
    h = height(G)
    w = width(G)
    ul = ulcorner(p)
    s = subtract(ul, astuple(ZERO, w))
    O = crop(I, s, astuple(h, w))
    return O
```
evaluation eee78d87 0.0 264.1387370112409 1.5 0.07544417380748825 265.71418118504835
```python
def dsl1(I):
    # detect accent color (non-7)
    accent = leastcolor(I)

    # build row stripes: rows with indices 1-2,4-5,7-8,10-11,13-14 are 7; others 0
    r0 = canvas(ZERO, (1, 16))
    r7 = canvas(SEVEN, (1, 16))
    tR = vconcat(r0, vconcat(r7, r7))
    rr1 = vconcat(tR, tR)
    rr2 = vconcat(rr1, tR)
    rr3 = vconcat(rr2, tR)
    rr4 = vconcat(rr3, tR)       # 15 rows
    RS = vconcat(rr4, r0)        # 16 rows

    # build column stripes: columns with indices 1-2,4-5,7-8,10-11,13-14 are 7; others 0
    c0 = canvas(ZERO, (16, 1))
    c7 = canvas(SEVEN, (16, 1))
    tC = hconcat(c0, hconcat(c7, c7))
    cc1 = hconcat(tC, tC)
    cc2 = hconcat(cc1, tC)
    cc3 = hconcat(cc2, tC)
    cc4 = hconcat(cc3, tC)       # 15 cols
    CS = hconcat(cc4, c0)        # 16 cols

    # delta-columns (col % 3 == 0 is 7)
    tDC = hconcat(c7, hconcat(c0, c0))
    dc1 = hconcat(tDC, tDC)
    dc2 = hconcat(dc1, tDC)
    dc3 = hconcat(dc2, tDC)
    dc4 = hconcat(dc3, tDC)      # 15 cols
    DC = hconcat(dc4, c7)        # 16 cols

    # delta-rows (row % 3 == 0 is 7)
    tDR = vconcat(r7, vconcat(r0, r0))
    dr1 = vconcat(tDR, tDR)
    dr2 = vconcat(dr1, tDR)
    dr3 = vconcat(dr2, tDR)
    dr4 = vconcat(dr3, tDR)      # 15 rows
    DR = vconcat(dr4, r7)        # 16 rows

    # base patterns
    squares = cellwise(RS, CS, ZERO)    # 2x2 blocks
    vbars = cellwise(RS, DC, ZERO)      # vertical bars
    hbars = cellwise(DR, CS, ZERO)      # horizontal bars

    is_one = equality(accent, ONE)
    is_six = equality(accent, SIX)
    base = branch(is_one, vbars, branch(is_six, hbars, squares))

    # central cross of 9s, clipped to window
    # vertical segments at cols 6 and 9, rows 5..11
    vlines = combine(shoot(astuple(0, 6), DOWN), shoot(astuple(0, 9), DOWN))
    rowwin = backdrop(connect(astuple(5, 0), astuple(11, 15)))
    vseg = intersection(vlines, rowwin)

    # horizontal segments at rows 6 and 9, cols 5..10
    hlines = combine(shoot(astuple(6, 0), RIGHT), shoot(astuple(9, 0), RIGHT))
    colwin = backdrop(connect(astuple(0, 5), astuple(15, 10)))
    hseg = intersection(hlines, colwin)

    cross = combine(vseg, hseg)
    O = fill(base, NINE, cross)
    return O
```
evaluation b5ca7ac4 0.0 290.945457093948 2.2355371900826446 0.03214121732149596 293.2131355013522
```python
def dsl5(I):
    O = dmirror(I)
    return O
```
evaluation 4c7dc4dd 2.8284271247461903 189.0165408655043 102.8 0.32449468892702266 294.9694626791775
```python
def dsl2(I):
    # Trim a uniform border once, then apply mapping and downscale by 6
    t = trim(I)
    x = replace(t, ZERO, EIGHT)
    x = replace(x, ONE, ZERO)
    x = replace(x, TWO, ZERO)
    x = replace(x, THREE, ZERO)
    x = replace(x, FOUR, ZERO)
    x = replace(x, EIGHT, TWO)
    x = replace(x, FIVE, TWO)
    x = replace(x, SEVEN, TWO)
    x = replace(x, NINE, TWO)
    O = downscale(x, SIX)
    return O
```
evaluation 13e47133 0.0 317.751788971708 3.4082905982905984 0.0 321.16007956999863
```python
def dsl3(I):
    tl = index(I, astuple(ZERO, ZERO))
    O = replace(I, mostcolor(I), tl)
    return O
```
evaluation 195c6913 0.0 320.51556852742607 2.482788888888889 0.0 322.998357416315
```python
def dsl1(I):
    O = hmirror(I)
    return O
```
evaluation 21897d95 0.0 355.04005850535947 5.467460317460318 0.0 360.50751882281975
```python
def dsl5(I):
    J = dmirror(I)
    h = height(J)
    w = width(J)
    w2 = divide(w, TWO)
    left = crop(J, astuple(ZERO, ZERO), astuple(h, w2))
    right = crop(J, astuple(ZERO, w2), astuple(h, subtract(w, w2)))
    O = canvas(leastcolor(J), astuple(h, w))
    O = fill(O, mostcolor(left), shift(asindices(left), astuple(ZERO, ZERO)))
    O = fill(O, mostcolor(right), shift(asindices(right), astuple(ZERO, w2)))
    return O
```
evaluation d8e07eb2 0.0 409.4162268918265 2.0681818181818183 0.0 411.4844087100083
```python
def dsl3(I):
    h = height(I)
    w = width(I)
    topi = hfrontier(astuple(ONE, ZERO))
    boti = hfrontier(astuple(subtract(h, TWO), ZERO))
    lefti = vfrontier(astuple(ZERO, ONE))
    righti = vfrontier(astuple(ZERO, subtract(w, TWO)))
    frame = combine(combine(topi, boti), combine(lefti, righti))
    c = leastcolor(I)
    O = underfill(I, c, frame)
    return O
```
evaluation 981571dc 0.0 420.4059455527453 2.5544444444444445 0.0 422.96038999718974
```python
def dsl1(I):
    O = I
    H = hmirror(I)
    O = underpaint(O, asobject(H))
    V = vmirror(I)
    O = underpaint(O, asobject(V))
    R90 = rot90(I)
    O = underpaint(O, asobject(R90))
    R180 = rot180(I)
    O = underpaint(O, asobject(R180))
    R270 = rot270(I)
    O = underpaint(O, asobject(R270))
    D = dmirror(I)
    O = underpaint(O, asobject(D))
    C = cmirror(I)
    O = underpaint(O, asobject(C))
    return O
```
evaluation da515329 0.0 430.8635033167245 2.000292733684342 0.022097086907196795 432.8858931373161
```python
def dsl2(I):
    seeds = ofcolor(I, EIGHT)
    dirs = insert(UP, insert(DOWN, insert(LEFT, insert(RIGHT, insert(UP_RIGHT, insert(DOWN_LEFT, insert(UNITY, insert(NEG_UNITY, initset(ORIGIN)))))))))
    rays = prapply(shoot, seeds, dirs)
    lines = merge(rays)
    base = canvas(EIGHT, shape(I))
    O = fill(base, ZERO, lines)
    return O
```
evaluation 38007db0 1.0 142.31851652578138 435.06436090225566 0.016692188128448214 578.3995696161654
```python
def dsl1(I):
    start = astuple(ZERO, subtract(width(I), SEVEN))
    O = crop(I, start, astuple(height(I), SEVEN))
    return O
```
evaluation 5545f144 55.855866334710115 61.94427190999916 528.0888888888888 1.5122184161480101 647.4012455497461
```python
def dsl4(I):
    # Choose the sparsest panel (fewest non-background cells)
    bg = mostcolor(I)
    totalcells = compose(size, asindices)
    bgcount = rbind(colorcount, bg)
    forecount = fork(subtract, totalcells, bgcount)
    allobjs = objects(I, T, F, T)
    vliners = sfilter(allobjs, vline)
    fullheight = matcher(compose(height, rbind(subgrid, I)), height(I))
    vfull = sfilter(vliners, fullheight)
    npanels = add(size(vfull), ONE)
    tiles = vsplit(I, npanels)
    O = argmin(tiles, forecount)
    return O
```
evaluation 20270e3b 22.778298558384023 148.0 480.0952380952381 1.0820405198623555 651.9555771734845
```python
def dsl3(I):
    h = height(I)
    O = crop(I, ORIGIN, astuple(h, SIX))
    return O
```
evaluation 78332cb0 47.089151775499644 223.16441400296898 430.2352941176471 1.2503809474088823 701.7392408435246
```python
def dsl1(I):
    dims = astuple(FIVE, FIVE)
    seprow = canvas(SIX, astuple(ONE, FIVE))
    sepcol = canvas(SIX, astuple(FIVE, ONE))
    is_vertcol = both(equality(width(I), FIVE), greater(height(I), FIVE))
    is_horrow = both(equality(height(I), FIVE), greater(width(I), FIVE))
    A = crop(I, astuple(ZERO, ZERO), dims)
    Bv = crop(I, astuple(SIX, ZERO), dims)
    Cv = crop(I, astuple(TWELVE := add(SIX, SIX), ZERO), dims)
    Bh = crop(I, astuple(ZERO, SIX), dims)
    Ch = crop(I, astuple(ZERO, TWELVE), dims)
    if is_vertcol:
        x1 = hconcat(A, sepcol)
        x2 = hconcat(x1, Bv)
        x3 = hconcat(x2, sepcol)
        O = hconcat(x3, Cv)
    else:
        if is_horrow:
            y1 = vconcat(A, seprow)
            y2 = vconcat(y1, Bh)
            y3 = vconcat(y2, seprow)
            O = vconcat(y3, Ch)
        else:
            NW = A
            NE = Bh
            SW = Bv
            SE = crop(I, astuple(SIX, SIX), dims)
            z1 = vconcat(NW, seprow)
            z2 = vconcat(z1, SE)
            z3 = vconcat(z2, seprow)
            z4 = vconcat(z3, NE)
            z5 = vconcat(z4, seprow)
            O = vconcat(z5, SW)
    return O
```
evaluation f560132c 8.485281374238571 483.63519208854837 372.21875 0.31111111099675187 864.6503345737838
```python
def dsl5(I):
    # Fixed 8x8 hypothesis: 2x2 seed upscaled by 4
    objs = objects(I, True, False, True)
    singles = sizefilter(objs, ONE)
    quad = merge(singles)
    ul = ulcorner(quad); ur = urcorner(quad); ll = llcorner(quad); lr = lrcorner(quad)
    c_ul = index(I, ul); c_ur = index(I, ur); c_ll = index(I, ll); c_lr = index(I, lr)
    r1 = hconcat(canvas(c_ul, UNITY), canvas(c_ur, UNITY))
    r2 = hconcat(canvas(c_ll, UNITY), canvas(c_lr, UNITY))
    seed = vconcat(r1, r2)
    O = upscale(seed, FOUR)
    return O
```
evaluation 58f5dbd5 6.0 495.29248849452534 380.4099746407439 0.13972392981724874 881.8421870650865
```python
def dsl3(I):
    # Joint chooser: compare best 3x1 column, best 1x3 row, and best 2x2 block and return the densest
    bg = mostcolor(I)
    n19 = add(multiply(SIX, THREE), ONE)
    n13 = add(multiply(SIX, TWO), ONE)
    G = crop(I, ORIGIN, astuple(n19, n19))
    # best column-band
    c0 = crop(G, astuple(ZERO, ZERO), astuple(height(G), SEVEN))
    c1 = crop(G, astuple(ZERO, SIX), astuple(height(G), SEVEN))
    c2 = crop(G, astuple(ZERO, multiply(SIX, TWO)), astuple(height(G), SEVEN))
    a0 = multiply(height(c0), width(c0)); n0 = subtract(a0, colorcount(c0, bg))
    a1 = multiply(height(c1), width(c1)); n1 = subtract(a1, colorcount(c1, bg))
    a2 = multiply(height(c2), width(c2)); n2 = subtract(a2, colorcount(c2, bg))
    bestc = branch(greater(n0, n1), c0, c1)
    nbcc  = branch(greater(n0, n1), n0, n1)
    bestc = branch(greater(n2, nbcc), c2, bestc)
    nbcc  = branch(greater(n2, nbcc), n2, nbcc)
    # best row-band
    r0 = crop(G, astuple(ZERO, ZERO), astuple(SEVEN, width(G)))
    r1 = crop(G, astuple(SIX, ZERO), astuple(SEVEN, width(G)))
    r2 = crop(G, astuple(multiply(SIX, TWO), ZERO), astuple(SEVEN, width(G)))
    b0 = multiply(height(r0), width(r0)); m0 = subtract(b0, colorcount(r0, bg))
    b1 = multiply(height(r1), width(r1)); m1 = subtract(b1, colorcount(r1, bg))
    b2 = multiply(height(r2), width(r2)); m2 = subtract(b2, colorcount(r2, bg))
    bestr = branch(greater(m0, m1), r0, r1)
    nbrr  = branch(greater(m0, m1), m0, m1)
    bestr = branch(greater(m2, nbrr), r2, bestr)
    nbrr  = branch(greater(m2, nbrr), m2, nbrr)
    # best 2x2
    tl = crop(G, ORIGIN, astuple(n13, n13))
    tr = crop(G, astuple(ZERO, SIX), astuple(n13, n13))
    bl = crop(G, astuple(SIX, ZERO), astuple(n13, n13))
    br = crop(G, astuple(SIX, SIX), astuple(n13, n13))
    atl = multiply(height(tl), width(tl)); ntl = subtract(atl, colorcount(tl, bg))
    atr = multiply(height(tr), width(tr)); ntr = subtract(atr, colorcount(tr, bg))
    abl = multiply(height(bl), width(bl)); nbl = subtract(abl, colorcount(bl, bg))
    abr = multiply(height(br), width(br)); nbr = subtract(abr, colorcount(br, bg))
    best22 = branch(greater(ntl, ntr), tl, tr)
    nb22   = branch(greater(ntl, ntr), ntl, ntr)
    best22 = branch(greater(nbl, nb22), bl, best22)
    nb22   = branch(greater(nbl, nb22), nbl, nb22)
    best22 = branch(greater(nbr, nb22), br, best22)
    nb22   = branch(greater(nbr, nb22), nbr, nb22)
    # compare three candidates
    bestbr = branch(greater(nbcc, nbrr), bestc, bestr)
    nbbr   = branch(greater(nbcc, nbrr), nbcc, nbrr)
    O = branch(greater(nb22, nbbr), best22, bestbr)
    return O
```
evaluation 67e490f4 19.4164878389476 551.3133441403264 331.3560565308817 0.4336241749522826 902.5195126851079
```python
def dsl3(I):
    # Build a symmetric icon template using the top non-bg colors by frequency.
    # 13x13 if bg=8 else 11x11. Base background = most common non-bg color.
    H, W = height(I), width(I)
    bg = mostcolor(I)
    # count non-background colors
    cnt = {}
    for r in range(H):
        for c in range(W):
            v = index(I, (r, c))
            if v == bg:
                continue
            cnt[v] = cnt.get(v, 0) + 1
    if not cnt:
        return canvas(bg, (11, 11))
    colors_sorted = sorted(cnt.keys(), key=lambda x: (-cnt[x], x))
    base = colors_sorted[0]
    size_target = 13 if bg == EIGHT else 11
    O = canvas(base, (size_target, size_target))
    def sp(r, c, v):
        nonlocal O
        O = fill(O, v, frozenset({(r, c)}))
    def rect(r0, c0, r1, c1, v):
        nonlocal O
        inds = set()
        for r in range(r0, r1 + 1):
            for c in range(c0, c1 + 1):
                inds.add((r, c))
        O = fill(O, v, frozenset(inds))
    if size_target == 11:
        c1 = colors_sorted[1] if len(colors_sorted) > 1 else base
        c2 = colors_sorted[2] if len(colors_sorted) > 2 else base
        c3 = colors_sorted[3] if len(colors_sorted) > 3 else base
        c4 = colors_sorted[4] if len(colors_sorted) > 4 else base
        # corners 2x2 blocks with c1
        for (r0, c0) in [(1,1),(1,8),(8,1),(8,8)]:
            rect(r0, c0, r0+1, c0+1, c1)
        # central vertical line small with c2
        for r in range(1, 3):
            sp(r, 5, c2)
        for r in range(8, 10):
            sp(r, 5, c2)
        # mid cross with c3
        rect(5, 4, 5, 6, c3)
        rect(4, 5, 6, 5, c3)
        # small side 2x2 with c4
        rect(1, 1, 2, 2, c1)  # already corners
        # sprinkle c4 near center-sides
        for (r, c) in [(5,1),(5,9),(1,5),(9,5)]:
            sp(r, c, c4)
    else:
        # size 13 template
        c1 = colors_sorted[1] if len(colors_sorted) > 1 else base
        c2 = colors_sorted[2] if len(colors_sorted) > 2 else base
        c3 = colors_sorted[3] if len(colors_sorted) > 3 else base
        c4 = colors_sorted[4] if len(colors_sorted) > 4 else base
        # inner square ring (3..9) with c1
        for i in range(3, 10):
            sp(3, i, c1); sp(9, i, c1)
            sp(i, 3, c1); sp(i, 9, c1)
        # inner plus of length 3 with c2 at center (6,6)
        rect(6, 5, 6, 7, c2)
        rect(5, 6, 7, 6, c2)
        # corners 2x2 with c3
        for (r0, c0) in [(1,1),(1,10),(10,1),(10,10)]:
            rect(r0, c0, r0+1, c0+1, c3)
        # four mid-edge beacons with c4
        sp(1, 6, c4); sp(11, 6, c4); sp(6, 1, c4); sp(6, 11, c4)
    return O
```
evaluation 6ffbe589 21.353238174658927 438.544820285692 478.1065088757397 0.8891817323095179 938.8937490684002
```python
def dsl1(I):
    # Largest multi-color connected component (4-adjacent), then crop to its bbox
    obs = objects(I, F, F, T)
    pick = argmax(obs, size)
    O = subgrid(pick, I)
    return O
```
evaluation 20a9e565 60.939186141825715 616.0 320.0 2.9578160971725973 999.8970022389983
```python
def dsl4(I):
    # 3x3 ring of the least common non-zero color
    cols = remove(ZERO, palette(I))
    c = argmin(cols, lbind(colorcount, I))
    Z = canvas(ZERO, THREE_BY_THREE)
    O = fill(Z, c, box(asindices(Z)))
    return O
```
evaluation 142ca369 1.4142135623730951 392.3910385484121 760.954598765432 0.1269703255219085 1154.8868212017392
```python
def dsl3(I):
    # Mirror along counter-diagonal and underpaint the original on top
    O = cmirror(I)
    O = underpaint(O, asobject(I))
    return O
```
evaluation a6f40cea 13.734541479955949 358.0 891.0 0.508052356235683 1263.2425938361916
```python
def dsl4(I):
    bg = mostcolor(I)
    objs = objects(I, T, F, T)
    norm = apply(normalize, objs)
    merged = merge(norm)
    dims = shape(merged)
    O = paint(canvas(bg, dims), merged)
    return O
```
evaluation a251c730 44.114665909404536 882.3137084989847 341.0526315789474 1.3603845393384135 1268.841390526675
```python
def dsl3(I):
    # Choose the 3-frame maximizing (#8 inside + #1 inside)
    objs = objects(I, T, F, F)
    threes = colorfilter(objs, THREE)
    isframe = fork(equality, toindices, box)
    frames = sfilter(threes, isframe)
    sub = rbind(subgrid, I)
    cnt8 = compose(rbind(colorcount, EIGHT), sub)
    cnt1 = compose(rbind(colorcount, ONE), sub)
    score = fork(add, cnt8, cnt1)
    target = argmax(frames, score)
    O = subgrid(target, I)
    return O
```
evaluation 5dbc8537 5.0 591.1658788381679 936.9507936507937 0.10010550239917053 1533.2167779913607
```python
def dsl1(I):
    # Unify the two most common background colors, then crop along the dimension that reduces more.
    colors = palette(I)
    countf = lbind(colorcount, I)
    c1 = argmax(colors, countf)
    colors2 = remove(c1, colors)
    c2 = argmax(colors2, countf)
    x = replace(I, c2, c1)
    S = asindices(x)
    BG = ofcolor(x, c1)
    FG = difference(S, BG)
    top = uppermost(FG)
    bot = lowermost(FG)
    L = leftmost(FG)
    R = rightmost(FG)
    H = height(I)
    W = width(I)
    hspan = add(ONE, subtract(bot, top))
    wspan = add(ONE, subtract(R, L))
    dh = subtract(H, hspan)
    dw = subtract(W, wspan)
    croprows = crop(x, astuple(top, 0), astuple(hspan, W))
    cropcols = crop(x, astuple(0, L), astuple(H, wspan))
    O = branch(greater(dh, dw), croprows, cropcols)
    return O
```
evaluation 2d0172a1 11.43397840021018 642.0 950.0 0.4127778955581578 1603.8467562957685
```python
def dsl2(I):
    x0 = trim(I)
    x1 = compress(x0)
    x2 = downscale(x1, TWO)
    lc = leastcolor(I)
    b = box(asindices(x2))
    O = fill(x2, lc, b)
    return O
```
evaluation 291dc1e1 46.64835624347283 915.0 772.0 1.4764186358411817 1735.124774879314
```python
def dsl1(I):
    x = replace(I, ZERO, EIGHT)
    x = replace(x, ONE, EIGHT)
    x = replace(x, TWO, EIGHT)
    x = trim(x)
    x = rot270(x)
    O = compress(x)
    return O
```
evaluation 3a25b0d8 14.919796900954 777.0 1089.0 0.49093715832665796 1881.4107340592807
```python
def dsl1(I):
    bg = mostcolor(I)
    all_idx = asindices(I)
    bg_idx = ofcolor(I, bg)
    fg_idx = difference(all_idx, bg_idx)
    x = subgrid(fg_idx, I)
    O = downscale(x, TWO)
    return O
```
evaluation 7b3084d4 10.231551362179038 1320.0 574.0 0.47516363072986967 1904.706714992909
```python
def dsl3(I):
    y = compress(I)
    y = dmirror(y)
    O = downscale(y, TWO)
    return O
```
evaluation fc7cae8d 40.6328548607663 1449.8885438199982 588.44 1.786477798263936 2080.7478764790285
```python
def dsl2(I):
    idx = ofcolor(I, EIGHT)
    O = subgrid(idx, I)
    return O
```
evaluation 4e34c42c 72.02672786418499 721.0 1317.0 1.1808058258307863 2111.207533690016
```python
def dsl1(I):
    # Rotate the sequence of valid 5-row bands left by one (multi-color filter), then hconcat.
    h = height(I)
    w = width(I)
    bg = mostcolor(I)
    rows = interval(ZERO, h, ONE)
    hasfg = lambda i: greater(w, colorcount(crop(I, astuple(i, ZERO), astuple(ONE, w)), bg))

    # band A (top-most)
    r1 = extract(rows, hasfg)
    A0 = crop(I, astuple(r1, ZERO), astuple(FIVE, w))
    nb1 = difference(asindices(A0), ofcolor(A0, bg))
    has1 = greater(size(nb1), ZERO)
    l1 = branch(has1, leftmost(nb1), ZERO)
    r1b = branch(has1, rightmost(nb1), NEG_ONE)
    w1 = add(subtract(r1b, l1), ONE)
    A = branch(has1, crop(A0, astuple(ZERO, l1), astuple(FIVE, w1)), canvas(bg, astuple(FIVE, ONE)))
    p1 = palette(A0)
    c1 = size(remove(bg, p1))
    v1 = both(has1, greater(c1, ONE))

    # band B (next 5 rows after A)
    rows2 = interval(add(r1, FIVE), h, ONE)
    r2 = extract(rows2, hasfg)
    B0 = crop(I, astuple(r2, ZERO), astuple(FIVE, w))
    nb2 = difference(asindices(B0), ofcolor(B0, bg))
    has2 = greater(size(nb2), ZERO)
    l2 = branch(has2, leftmost(nb2), ZERO)
    r2b = branch(has2, rightmost(nb2), NEG_ONE)
    w2 = add(subtract(r2b, l2), ONE)
    B = branch(has2, crop(B0, astuple(ZERO, l2), astuple(FIVE, w2)), canvas(bg, astuple(FIVE, ONE)))
    p2 = palette(B0)
    c2 = size(remove(bg, p2))
    v2 = both(has2, greater(c2, ONE))

    # band C (next 5 rows after B)
    rows3 = interval(add(r2, FIVE), h, ONE)
    r3 = extract(rows3, hasfg)
    C0 = crop(I, astuple(r3, ZERO), astuple(FIVE, w))
    nb3 = difference(asindices(C0), ofcolor(C0, bg))
    has3 = greater(size(nb3), ZERO)
    l3 = branch(has3, leftmost(nb3), ZERO)
    r3b = branch(has3, rightmost(nb3), NEG_ONE)
    w3 = add(subtract(r3b, l3), ONE)
    C = branch(has3, crop(C0, astuple(ZERO, l3), astuple(FIVE, w3)), canvas(bg, astuple(FIVE, ONE)))
    p3 = palette(C0)
    c3 = size(remove(bg, p3))
    v3 = both(has3, greater(c3, ONE))

    E = canvas(bg, astuple(FIVE, ONE))

    # Build rotation-left: [A,B,C] -> [B,C,A], considering which bands are valid (v*)
    # Base (no C)
    ABrot = branch(both(v1, v2), hconcat(B, A), branch(v1, A, branch(v2, B, E)))
    # With C present
    O = branch(v3,
               branch(both(v1, v2), hconcat(B, hconcat(C, A)),
                      branch(v2, hconcat(C, B), branch(v1, hconcat(C, A), C))),
               ABrot)
    return O
```
evaluation f931b4a8 42.8385195488975 1568.4852813742386 660.5 2.0866794890436555 2273.91048041218
```python
def dsl1(I):
    bh = bottomhalf(I)
    bl = lefthalf(bh)
    br = righthalf(bh)
    c = mostcolor(bl)
    O = replace(br, ZERO, c)
    return O
```
evaluation 62593bfd 2.0 324.69011257575005 2261.1719298245616 0.07351216112626435 2587.9355545614376
```python
def dsl5(I):
    top = tophalf(I)
    bot = bottomhalf(I)
    O = vconcat(bot, top)
    return O
```
evaluation 8698868d 29.657276161841214 2765.0 2053.0 0.5705891629264256 4848.227865324768
```python
def dsl2(I):
    # Compress each vertical half separately, then stitch
    L = lefthalf(I)
    R = righthalf(I)
    LC = compress(L)
    RC = compress(R)
    O = hconcat(LC, RC)
    return O
```
evaluation 898e7135 30.970562748477143 3219.0 2424.0 0.5244247901042831 5674.494987538581
```python
def dsl5(I):
    y = downscale(I, 3)
    p = remove(ZERO, palette(I))
    c = argmax(p, lbind(colorcount, I))
    z = replace(y, ZERO, c)
    O = upscale(z, 2)
    return O
```
evaluation 65b59efc 30.859794699220657 2619.0 3156.0 2.637912641359741 5808.497707340581
```python
def dsl5(I):
    # Coarse-grain and use frontiers as outlines
    x1 = switch(I, FIVE, ZERO)
    fac = branch(greater(width(I), 12), FIVE, THREE)
    x2 = downscale(x1, fac)
    x3 = upscale(x2, fac)
    fr = frontiers(x3)
    u = merge(fr)
    Z = canvas(ZERO, shape(x3))
    O = paint(Z, u)
    return O
```
evaluation e87109e9 24.0 1343.0 4464.0 0.35947828237507096 5831.359478282375
```python
def dsl5(I):
    # Fill only horizontal rows through every 8, but do not overwrite 5
    objs8 = colorfilter(objects(I, T, F, T), EIGHT)
    if size(objs8) == 0:
        return I
    idxs = merge(apply(toindices, objs8))
    lefts = mapply(rbind(shoot, LEFT), idxs)
    rights = mapply(rbind(shoot, RIGHT), idxs)
    band = combine(lefts, rights)
    band = combine(band, idxs)
    avoid5 = ofcolor(I, FIVE)
    band = difference(band, avoid5)
    O = fill(I, EIGHT, band)
    return O
```
evaluation a32d8b75 31.0 3049.0 6180.0 0.4309753291999112 9260.4309753292
```python
def dsl1(I):
    h = height(I)
    w = width(I)
    s6 = ofcolor(I, SIX)
    j6 = leftmost(s6)
    start = astuple(ZERO, add(j6, ONE))
    dims = astuple(h, subtract(w, add(j6, ONE)))
    O = crop(I, start, dims)
    return O
```
evaluation 88bcf3b4 nan nan nan nan nan
```python

```
evaluation b0039139 nan nan nan nan nan
```python

```
evaluation b9e38dc0 nan nan nan nan nan
```python

```
evaluation bf45cf4b nan nan nan nan nan
```python

```
evaluation 1ae2feb7 nan nan nan nan nan
```python
def dsl1(I):
    h = height(I)
    w = width(I)
    b = leftmost(ofcolor(I, TWO))
    bm1 = decrement(b)
    col = crop(I, astuple(ZERO, bm1), astuple(h, ONE))
    base = shift(asobject(col), tojvec(bm1))
    s1 = shift(base, tojvec(TWO))
    s2 = shift(s1, tojvec(ONE))
    s3 = shift(s2, tojvec(ONE))
    s4 = shift(s3, tojvec(ONE))
    s5 = shift(s4, tojvec(ONE))
    s6 = shift(s5, tojvec(ONE))
    s7 = shift(s6, tojvec(ONE))
    s8 = shift(s7, tojvec(ONE))
    s9 = shift(s8, tojvec(ONE))
    s10 = shift(s9, tojvec(ONE))
    u1 = combine(s1, s2)
    u2 = combine(u1, s3)
    u3 = combine(u2, s4)
    u4 = combine(u3, s5)
    u5 = combine(u4, s6)
    u6 = combine(u5, s7)
    u7 = combine(u6, s8)
    u8 = combine(u7, s9)
    u9 = combine(u8, s10)
    O = underpaint(I, u9)
    return O
```
