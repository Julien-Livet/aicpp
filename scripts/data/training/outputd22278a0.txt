```python
def dsl1(I):
    # For each present corner, draw "fans" to its two far borders at step-2 sampling
    h = height(I)
    w = width(I)
    O = canvas(ZERO, shape(I))
    tl = astuple(0, 0)
    tr = astuple(0, subtract(w, ONE))
    bl = astuple(subtract(h, ONE), 0)
    br = astuple(subtract(h, ONE), subtract(w, ONE))
    corners_list = [(tl, index(I, tl), ['bottom', 'right']),
                    (tr, index(I, tr), ['bottom', 'left']),
                    (bl, index(I, bl), ['top', 'right']),
                    (br, index(I, br), ['top', 'left'])]
    for pos, col, targets in corners_list:
        if not positive(col):
            continue
        pr, pc = pos
        # build target points on designated far borders, sampled every 2 cells
        tpoints = []
        if 'bottom' in targets:
            r = subtract(h, ONE)
            for c in range(0, w, 2):
                tpoints.append(astuple(r, c))
        if 'top' in targets:
            r = 0
            for c in range(0, w, 2):
                tpoints.append(astuple(r, c))
        if 'right' in targets:
            c = subtract(w, ONE)
            for r in range(0, h, 2):
                tpoints.append(astuple(r, c))
        if 'left' in targets:
            c = 0
            for r in range(0, h, 2):
                tpoints.append(astuple(r, c))
        # draw connections
        for tp in tpoints:
            seg = connect(pos, tp)
            O = underpaint(O, recolor(col, seg))
    return O

def dsl2(I):
    # For each present corner, draw fans to its two far borders at every cell (dense sampling)
    h = height(I)
    w = width(I)
    O = canvas(ZERO, shape(I))
    tl = astuple(0, 0)
    tr = astuple(0, subtract(w, ONE))
    bl = astuple(subtract(h, ONE), 0)
    br = astuple(subtract(h, ONE), subtract(w, ONE))
    corners_list = [(tl, index(I, tl), ['bottom', 'right']),
                    (tr, index(I, tr), ['bottom', 'left']),
                    (bl, index(I, bl), ['top', 'right']),
                    (br, index(I, br), ['top', 'left'])]
    for pos, col, targets in corners_list:
        if not positive(col):
            continue
        if 'bottom' in targets:
            r = subtract(h, ONE)
            for c in range(0, w):
                O = underpaint(O, recolor(col, connect(pos, astuple(r, c))))
        if 'top' in targets:
            r = 0
            for c in range(0, w):
                O = underpaint(O, recolor(col, connect(pos, astuple(r, c))))
        if 'right' in targets:
            c = subtract(w, ONE)
            for r in range(0, h):
                O = underpaint(O, recolor(col, connect(pos, astuple(r, c))))
        if 'left' in targets:
            c = 0
            for r in range(0, h):
                O = underpaint(O, recolor(col, connect(pos, astuple(r, c))))
    return O

def dsl3(I):
    # Nearest-corner assignment with vertical stripe gating by corner's column parity
    h = height(I)
    w = width(I)
    O = canvas(ZERO, shape(I))
    # collect present corners
    cs = []
    corners = [(0, 0), (0, subtract(w, ONE)), (subtract(h, ONE), 0), (subtract(h, ONE), subtract(w, ONE))]
    for (r, c) in corners:
        col = index(I, astuple(r, c))
        if positive(col):
            cs.append((r, c, col))
    if not cs:
        return O
    # fill by nearest corner (Manhattan), break ties to background, then keep only columns matching corner col-parity
    grid = [list(row) for row in O]
    for i in range(h):
        for j in range(w):
            best = None
            bestd = None
            tie = False
            for (cr, cc, col) in cs:
                d = abs(i - cr) + abs(j - cc)
                if (bestd is None) or (d < bestd):
                    bestd = d
                    best = (cr, cc, col)
                    tie = False
                elif d == bestd:
                    tie = True
            if not tie and best is not None:
                cr, cc, col = best
                if (j % 2) == (cc % 2):
                    grid[i][j] = col
    return tuple(tuple(row) for row in grid)

def dsl4(I):
    # Nearest-corner assignment with horizontal stripe gating by corner's row parity
    h = height(I)
    w = width(I)
    O = canvas(ZERO, shape(I))
    cs = []
    corners = [(0, 0), (0, subtract(w, ONE)), (subtract(h, ONE), 0), (subtract(h, ONE), subtract(w, ONE))]
    for (r, c) in corners:
        col = index(I, astuple(r, c))
        if positive(col):
            cs.append((r, c, col))
    if not cs:
        return O
    grid = [list(row) for row in O]
    for i in range(h):
        for j in range(w):
            best = None
            bestd = None
            tie = False
            for (cr, cc, col) in cs:
                d = abs(i - cr) + abs(j - cc)
                if (bestd is None) or (d < bestd):
                    bestd = d
                    best = (cr, cc, col)
                    tie = False
                elif d == bestd:
                    tie = True
            if not tie and best is not None:
                cr, cc, col = best
                if (i % 2) == (cr % 2):
                    grid[i][j] = col
    return tuple(tuple(row) for row in grid)

def dsl5(I):
    # Mixed fan: for top corners connect to bottom row (step-2), for bottom corners connect to top row (step-2);
    # additionally, connect to the lateral far column densely.
    h = height(I)
    w = width(I)
    O = canvas(ZERO, shape(I))
    tl = astuple(0, 0)
    tr = astuple(0, subtract(w, ONE))
    bl = astuple(subtract(h, ONE), 0)
    br = astuple(subtract(h, ONE), subtract(w, ONE))
    # top corners to bottom row at step 2
    ctl = index(I, tl)
    if positive(ctl):
        for c in range(0, w, 2):
            O = underpaint(O, recolor(ctl, connect(tl, astuple(subtract(h, ONE), c))))
        # and to right column densely
        for r in range(0, h):
            O = underpaint(O, recolor(ctl, connect(tl, astuple(r, subtract(w, ONE)))))
    ctr = index(I, tr)
    if positive(ctr):
        for c in range(0, w, 2):
            O = underpaint(O, recolor(ctr, connect(tr, astuple(subtract(h, ONE), c))))
        # and to left column densely
        for r in range(0, h):
            O = underpaint(O, recolor(ctr, connect(tr, astuple(r, 0))))
    # bottom corners to top row at step 2
    cbl = index(I, bl)
    if positive(cbl):
        for c in range(0, w, 2):
            O = underpaint(O, recolor(cbl, connect(bl, astuple(0, c))))
        # and to right column densely
        for r in range(0, h):
            O = underpaint(O, recolor(cbl, connect(bl, astuple(r, subtract(w, ONE)))))
    cbr = index(I, br)
    if positive(cbr):
        for c in range(0, w, 2):
            O = underpaint(O, recolor(cbr, connect(br, astuple(0, c))))
        # and to left column densely
        for r in range(0, h):
            O = underpaint(O, recolor(cbr, connect(br, astuple(r, 0))))
    return O
```