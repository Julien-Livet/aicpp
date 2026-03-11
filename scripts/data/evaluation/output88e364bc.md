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

def dsl2(I):
    # For each FOUR: move diagonally toward the nearest FIVE (by Manhattan),
    # stepping one cell in both row and column directions at a time through zeros until blocked.
    H, W = shape(I)
    fives = ofcolor(I, FIVE)
    if size(fives) == 0:
        return I
    fours = ofcolor(I, FOUR)
    new_positions = []
    for (r, c) in fours:
        # find nearest FIVE
        best_d = None
        tgt = (r, c)
        for (fr, fc) in fives:
            d = abs(fr - r) + abs(fc - c)
            if best_d is None or d < best_d:
                best_d = d
                tgt = (fr, fc)
        nr, nc = r, c
        # step diagonally toward tgt
        while True:
            dr = 0 if tgt[0] == nr else (1 if tgt[0] > nr else -1)
            dc = 0 if tgt[1] == nc else (1 if tgt[1] > nc else -1)
            if dr == 0 and dc == 0:
                break
            tr, tc = nr + dr, nc + dc
            if not (0 <= tr < H and 0 <= tc < W):
                break
            if index(I, (tr, tc)) != ZERO:
                break
            nr, nc = tr, tc
        new_positions.append((nr, nc))
    O = replace(I, FOUR, ZERO)
    O = fill(O, FOUR, frozenset(new_positions))
    return O

def dsl3(I):
    # Slide each FOUR toward the center-of-mass of FIVE cells (not all nonzeros),
    # moving along the (sign) direction and through zeros until blocked.
    H, W = shape(I)
    fives = ofcolor(I, FIVE)
    if size(fives) == 0:
        return I
    s_r = sum(r for (r, c) in fives)
    s_c = sum(c for (r, c) in fives)
    com_r = s_r // size(fives)
    com_c = s_c // size(fives)
    fours = ofcolor(I, FOUR)
    new_positions = []
    for (r, c) in fours:
        dr = 0 if com_r == r else (1 if com_r > r else -1)
        dc = 0 if com_c == c else (1 if com_c > c else -1)
        nr, nc = r, c
        while True:
            tr, tc = nr + dr, nc + dc
            if not (0 <= tr < H and 0 <= tc < W):
                break
            if index(I, (tr, tc)) != ZERO:
                break
            nr, nc = tr, tc
        new_positions.append((nr, nc))
    O = replace(I, FOUR, ZERO)
    O = fill(O, FOUR, frozenset(new_positions))
    return O

def dsl4(I):
    # For each FOUR: snap to the nearest zero cell that is orthogonally adjacent to any nonzero cell.
    H, W = shape(I)
    inds = asindices(I)
    # collect border-zero candidates
    candidates = []
    for (r, c) in inds:
        if index(I, (r, c)) != ZERO:
            continue
        adj = neighbors((r, c))
        touch_nonzero = False
        for (ar, ac) in adj:
            if 0 <= ar < H and 0 <= ac < W and index(I, (ar, ac)) != ZERO:
                touch_nonzero = True
                break
        if touch_nonzero:
            candidates.append((r, c))
    fours = ofcolor(I, FOUR)
    new_positions = []
    for (r, c) in fours:
        best = (r, c)
        best_d = None
        for (tr, tc) in candidates:
            d = abs(tr - r) + abs(tc - c)
            if best_d is None or d < best_d:
                best_d = d
                best = (tr, tc)
        new_positions.append(best)
    O = replace(I, FOUR, ZERO)
    O = fill(O, FOUR, frozenset(new_positions))
    return O

def dsl5(I):
    # Direction choice by region: in top half, prefer sliding toward a SEVEN; in bottom half, prefer toward a FIVE.
    # Among directions that reach the preferred color, choose the one with the longest zero-run; otherwise fall back to any longest.
    H, W = shape(I)
    fours = ofcolor(I, FOUR)
    new_positions = []
    for (r, c) in fours:
        prefer = SEVEN if r < H // 2 else FIVE
        dirs = [UP, DOWN, LEFT, RIGHT]
        cand_pref = []
        cand_all = []
        for (dr, dc) in dirs:
            steps = 0
            nr, nc = r + dr, c + dc
            while 0 <= nr < H and 0 <= nc < W and index(I, (nr, nc)) == ZERO:
                steps += 1
                nr += dr
                nc += dc
            # barrier color
            barrier_color = None
            if 0 <= nr < H and 0 <= nc < W:
                barrier_color = index(I, (nr, nc))
            # stop pos just before barrier
            tr = r + dr * steps
            tc = c + dc * steps
            entry = (steps, tr, tc, barrier_color)
            if barrier_color == prefer:
                cand_pref.append(entry)
            if barrier_color is not None:
                cand_all.append(entry)
        chosen = None
        if len(cand_pref) > 0:
            chosen = max(cand_pref, key=lambda x: x[0])
        elif len(cand_all) > 0:
            chosen = max(cand_all, key=lambda x: x[0])
        else:
            chosen = (0, r, c, None)
        new_positions.append((chosen[1], chosen[2]))
    O = replace(I, FOUR, ZERO)
    O = fill(O, FOUR, frozenset(new_positions))
    return O
```