```python
def dsl1(I):
    # Keep spine, keep top and bottom border objects, and add central pluses for top-row nonzeros
    h = height(I)
    w = width(I)
    O = canvas(ZERO, astuple(h, w))

    # helper to draw a 5-cell plus
    def draw_plus(G, r, j, c):
        if c == ZERO:
            return G
        pts = initset(astuple(r, j))
        if r > 0:
            pts = insert(astuple(r - 1, j), pts)
        if r < h - 1:
            pts = insert(astuple(r + 1, j), pts)
        if j > 0:
            pts = insert(astuple(r, j - 1), pts)
        if j < w - 1:
            pts = insert(astuple(r, j + 1), pts)
        return fill(G, c, pts)

    spine = None
    spine_j = None
    spine_col = None
    for obj in objects(I, T, F, T):
        if vline(obj) and height(obj) == h:
            spine = obj
            spine_j = leftmost(obj)
            spine_col = color(obj)
            break

    if spine is not None:
        O = underpaint(O, spine)

    # paint top and bottom border objects from I
    for obj in objects(I, T, F, T):
        if obj == spine:
            continue
        if uppermost(obj) == 0 or lowermost(obj) == h - 1:
            O = underpaint(O, obj)

    # add plus centered at mid-height for each nonzero on top row (excluding spine color)
    mid_r = h // 2
    for j in range(w):
        c = index(I, astuple(0, j))
        if c != ZERO and (spine_col is None or c != spine_col):
            O = draw_plus(O, mid_r, j, c)

    return O


def dsl2(I):
    # Keep spine and borders; add pluses for each top-row nonzero at the row of the color's center-of-mass
    h = height(I)
    w = width(I)
    O = canvas(ZERO, astuple(h, w))

    def draw_plus(G, r, j, c):
        if c == ZERO:
            return G
        pts = initset(astuple(r, j))
        if r > 0:
            pts = insert(astuple(r - 1, j), pts)
        if r < h - 1:
            pts = insert(astuple(r + 1, j), pts)
        if j > 0:
            pts = insert(astuple(r, j - 1), pts)
        if j < w - 1:
            pts = insert(astuple(r, j + 1), pts)
        return fill(G, c, pts)

    spine = None
    spine_j = None
    spine_col = None
    for obj in objects(I, T, F, T):
        if vline(obj) and height(obj) == h:
            spine = obj
            spine_j = leftmost(obj)
            spine_col = color(obj)
            break

    if spine is not None:
        O = underpaint(O, spine)

    for obj in objects(I, T, F, T):
        if obj == spine:
            continue
        if uppermost(obj) == 0 or lowermost(obj) == h - 1:
            O = underpaint(O, obj)

    # for each nonzero on top row, place a plus at the interior center-of-mass row of that color
    mid_r = h // 2
    for j in range(w):
        c = index(I, astuple(0, j))
        if c == ZERO or (spine_col is not None and c == spine_col):
            continue
        inds = ofcolor(I, c)
        rows = []
        for (ri, cj) in inds:
            if ri != 0 and ri != h - 1:
                rows.append(ri)
        r = mid_r if len(rows) == 0 else sum(rows) // len(rows)
        O = draw_plus(O, r, j, c)

    return O


def dsl3(I):
    # Keep spine and borders; add pluses for both top-row and bottom-row nonzeros, centered near mid-height
    h = height(I)
    w = width(I)
    O = canvas(ZERO, astuple(h, w))

    def draw_plus(G, r, j, c):
        if c == ZERO:
            return G
        pts = initset(astuple(r, j))
        if r > 0:
            pts = insert(astuple(r - 1, j), pts)
        if r < h - 1:
            pts = insert(astuple(r + 1, j), pts)
        if j > 0:
            pts = insert(astuple(r, j - 1), pts)
        if j < w - 1:
            pts = insert(astuple(r, j + 1), pts)
        return fill(G, c, pts)

    spine = None
    spine_j = None
    spine_col = None
    for obj in objects(I, T, F, T):
        if vline(obj) and height(obj) == h:
            spine = obj
            spine_j = leftmost(obj)
            spine_col = color(obj)
            break

    if spine is not None:
        O = underpaint(O, spine)

    for obj in objects(I, T, F, T):
        if obj == spine:
            continue
        if uppermost(obj) == 0 or lowermost(obj) == h - 1:
            O = underpaint(O, obj)

    top_r = max(1, (h // 2) - 2)
    bot_r = min(h - 2, (h // 2) + 2)

    # top-row pluses
    for j in range(w):
        c = index(I, astuple(0, j))
        if c != ZERO and (spine_col is None or c != spine_col):
            O = draw_plus(O, top_r, j, c)
    # bottom-row pluses
    for j in range(w):
        c = index(I, astuple(h - 1, j))
        if c != ZERO and (spine_col is None or c != spine_col):
            O = draw_plus(O, bot_r, j, c)

    return O


def dsl4(I):
    # Keep spine and borders; add plus at the center-of-mass of each non-zero, non-spine color
    h = height(I)
    w = width(I)
    O = canvas(ZERO, astuple(h, w))

    def draw_plus(G, r, j, c):
        if c == ZERO:
            return G
        pts = initset(astuple(r, j))
        if r > 0:
            pts = insert(astuple(r - 1, j), pts)
        if r < h - 1:
            pts = insert(astuple(r + 1, j), pts)
        if j > 0:
            pts = insert(astuple(r, j - 1), pts)
        if j < w - 1:
            pts = insert(astuple(r, j + 1), pts)
        return fill(G, c, pts)

    spine = None
    spine_col = None
    for obj in objects(I, T, F, T):
        if vline(obj) and height(obj) == h:
            spine = obj
            spine_col = color(obj)
            break

    if spine is not None:
        O = underpaint(O, spine)

    # paint border objects
    for obj in objects(I, T, F, T):
        if obj == spine:
            continue
        if uppermost(obj) == 0 or lowermost(obj) == h - 1:
            O = underpaint(O, obj)

    # add pluses at center-of-mass for each color (excluding background and spine color)
    for c in palette(I):
        if c == ZERO or (spine_col is not None and c == spine_col):
            continue
        inds = ofcolor(I, c)
        if size(inds) == 0:
            continue
        (ri, cj) = centerofmass(inds)
        O = draw_plus(O, ri, cj, c)

    return O


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