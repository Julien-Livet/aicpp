```python
def dsl1(I):
    # Fill 2 where a background cell is between non-bg seeds both horizontally and vertically (intersection of row/col spans)
    bg = mostcolor(I)
    h, w = shape(I)
    fillset = set()
    for i in range(h):
        for j in range(w):
            if index(I, (i, j)) != bg:
                continue
            # row-bounded
            left_has = any(index(I, (i, jj)) != bg for jj in range(0, j))
            right_has = any(index(I, (i, jj)) != bg for jj in range(j+1, w))
            if not (left_has and right_has):
                continue
            # col-bounded
            up_has = any(index(I, (ii, j)) != bg for ii in range(0, i))
            down_has = any(index(I, (ii, j)) != bg for ii in range(i+1, h))
            if not (up_has and down_has):
                continue
            fillset.add((i, j))
    O = fill(I, TWO, frozenset(fillset))
    return O

def dsl2(I):
    # Cast rays in all four orthogonal directions from each non-bg seed until hitting another non-bg; fill those bg cells with 2
    bg = mostcolor(I)
    h, w = shape(I)
    fillset = set()
    for i in range(h):
        for j in range(w):
            if index(I, (i, j)) == bg:
                continue
            # right
            jj = j + 1
            while jj < w and index(I, (i, jj)) == bg:
                fillset.add((i, jj))
                jj += 1
            # left
            jj = j - 1
            while jj >= 0 and index(I, (i, jj)) == bg:
                fillset.add((i, jj))
                jj -= 1
            # down
            ii = i + 1
            while ii < h and index(I, (ii, j)) == bg:
                fillset.add((ii, j))
                ii += 1
            # up
            ii = i - 1
            while ii >= 0 and index(I, (ii, j)) == bg:
                fillset.add((ii, j))
                ii -= 1
    O = fill(I, TWO, frozenset(fillset))
    return O

def dsl3(I):
    # Fill 2 where a background cell is between non-bg seeds in its row OR in its column (union of row/col spans)
    bg = mostcolor(I)
    h, w = shape(I)
    fillset = set()
    for i in range(h):
        for j in range(w):
            if index(I, (i, j)) != bg:
                continue
            row_left = any(index(I, (i, jj)) != bg for jj in range(0, j))
            row_right = any(index(I, (i, jj)) != bg for jj in range(j+1, w))
            col_up = any(index(I, (ii, j)) != bg for ii in range(0, i))
            col_down = any(index(I, (ii, j)) != bg for ii in range(i+1, h))
            if (row_left and row_right) or (col_up and col_down):
                fillset.add((i, j))
    O = fill(I, TWO, frozenset(fillset))
    return O

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

def dsl5(I):
    # Column-priority: fill 2 between column seeds but suppress where a closer row seed competes (nearest-seed dominance)
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
            du, dd = nearest_col_dists(i, j)
            if du < INF and dd < INF:
                dmin = du if du < dd else dd
                dl, dr = nearest_row_dists(i, j)
                rmin = dl if dl < dr else dr
                if rmin >= dmin:
                    fillset.add((i, j))
    O = fill(I, TWO, frozenset(fillset))
    return O
```