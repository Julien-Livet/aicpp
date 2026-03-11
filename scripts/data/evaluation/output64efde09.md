```python
def dsl1(I):
    # For each row, use the first '1' as a pivot:
    # - fill all background cells to its left with the first non-background color found on that row (to the left of the pivot)
    # - fill all background cells to its right with the first non-background color found on that row (to the right of the pivot)
    O = I
    H = height(I)
    W = width(I)
    for r in range(H):
        j1 = None
        for j in range(W):
            if index(I, astuple(r, j)) == ONE:
                j1 = j
                break
        if j1 is None:
            continue
        # left fill up to pivot-1 using first non-background value on the left side
        vL = None
        for j in range(0, j1):
            v = index(I, astuple(r, j))
            if v != EIGHT:
                vL = v
                break
        if vL is not None and j1 > 0:
            segL = connect(astuple(r, 0), astuple(r, j1 - 1))
            O = underfill(O, vL, segL)
        # right fill from pivot+1 to end using first non-background value on the right side
        vR = None
        for j in range(j1 + 1, W):
            v = index(I, astuple(r, j))
            if v != EIGHT:
                vR = v
                break
        if vR is not None and j1 + 1 < W:
            segR = connect(astuple(r, j1 + 1), astuple(r, W - 1))
            O = underfill(O, vR, segR)
    return O

def dsl2(I):
    # For each row, if it contains a '1', fill all background cells to the left of the first '1'
    # using the first non-background color appearing on that row (from the left).
    O = I
    H = height(I)
    W = width(I)
    for r in range(H):
        # find first 1 in the row
        j1 = None
        for j in range(W):
            if index(I, astuple(r, j)) == ONE:
                j1 = j
                break
        if j1 is None:
            continue
        # seed is first non-background in the row (from left)
        seed = None
        for j in range(W):
            v = index(I, astuple(r, j))
            if v != EIGHT and v != ONE:
                seed = v
                break
        if seed is not None and j1 > 0:
            seg = connect(astuple(r, 0), astuple(r, j1 - 1))
            O = underfill(O, seed, seg)
    return O

def dsl3(I):
    # For each column, find the bottommost non-background color and
    # propagate that color upward over background cells in that column.
    O = I
    H = height(I)
    W = width(I)
    for c in range(W):
        rbot = None
        vbot = None
        for r in range(H - 1, -1, -1):
            v = index(I, astuple(r, c))
            if v != EIGHT:
                rbot = r
                vbot = v
                break
        if rbot is not None and rbot >= 0:
            seg = connect(astuple(0, c), astuple(rbot, c))
            O = underfill(O, vbot, seg)
    return O

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

def dsl5(I):
    # Edge-seed from the right border:
    # If a row ends with a non-background color at the last column,
    # extend that color leftward across background cells until hitting the previous non-background cell.
    O = I
    H = height(I)
    W = width(I)
    for r in range(H):
        vR = index(I, astuple(r, W - 1))
        if vR == EIGHT:
            continue
        # find the left barrier (previous non-background before last col)
        jbar = None
        for j in range(W - 2, -1, -1):
            if index(I, astuple(r, j)) != EIGHT:
                jbar = j
                break
        if jbar is None:
            jbar = -1
        if jbar + 1 < W - 1:
            seg = connect(astuple(r, jbar + 1), astuple(r, W - 1))
            O = underfill(O, vR, seg)
    return O
```