```python
def dsl1(I):
    # Use axes defined by c = leftmost column of 2s, r = lowermost row of 2s.
    s2 = ofcolor(I, TWO)
    if size(s2) == 0:
        return I
    c = leftmost(s2)
    r = lowermost(s2)
    H = height(I)
    W = width(I)
    G = asindices(I)
    dcol = subtract(double(c), subtract(W, ONE))  # 2*c - (W-1)
    drow = subtract(double(r), subtract(H, ONE))  # 2*r - (H-1)
    # Mirror 7s across vertical axis at column c
    s7v = ofcolor(vmirror(I), SEVEN)
    p7v = intersection(shift(s7v, astuple(ZERO, dcol)), G)
    # Mirror 7s across horizontal axis at row r
    s7h = ofcolor(hmirror(I), SEVEN)
    p7h = intersection(shift(s7h, astuple(drow, ZERO)), G)
    # Mirror 7s across both axes (rot180 + shift)
    s7b = ofcolor(rot180(I), SEVEN)
    p7b = intersection(shift(s7b, astuple(drow, dcol)), G)
    base = I
    base = underpaint(base, recolor(SEVEN, p7v))
    base = underpaint(base, recolor(SEVEN, p7h))
    base = underpaint(base, recolor(SEVEN, p7b))
    # Draw cross of 2s at row r and column c (preserve 7s)
    top = astuple(ZERO, c)
    bot = astuple(subtract(H, ONE), c)
    vline = combine(shoot(top, DOWN), shoot(bot, UP))
    L = astuple(r, ZERO)
    R = astuple(r, subtract(W, ONE))
    hline = combine(shoot(L, RIGHT), shoot(R, LEFT))
    cross = combine(vline, hline)
    O = underfill(base, TWO, cross)
    return O

def dsl2(I):
    # Only vertical symmetry for 7s and vertical 2-line at c = leftmost(2)
    s2 = ofcolor(I, TWO)
    if size(s2) == 0:
        return I
    c = leftmost(s2)
    H = height(I)
    W = width(I)
    G = asindices(I)
    dcol = subtract(double(c), subtract(W, ONE))
    s7v = ofcolor(vmirror(I), SEVEN)
    p7v = intersection(shift(s7v, astuple(ZERO, dcol)), G)
    base = underpaint(I, recolor(SEVEN, p7v))
    # Vertical 2-line at column c
    top = astuple(ZERO, c)
    bot = astuple(subtract(H, ONE), c)
    vline = combine(shoot(top, DOWN), shoot(bot, UP))
    O = underfill(base, TWO, vline)
    return O

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

def dsl4(I):
    # Use alternative axes: c = rightmost column of 2s, r = uppermost row of 2s, mirror 7s both ways and draw cross
    s2 = ofcolor(I, TWO)
    if size(s2) == 0:
        return I
    c = rightmost(s2)
    r = uppermost(s2)
    H = height(I)
    W = width(I)
    G = asindices(I)
    dcol = subtract(double(c), subtract(W, ONE))
    drow = subtract(double(r), subtract(H, ONE))
    s7v = ofcolor(vmirror(I), SEVEN)
    p7v = intersection(shift(s7v, astuple(ZERO, dcol)), G)
    s7h = ofcolor(hmirror(I), SEVEN)
    p7h = intersection(shift(s7h, astuple(drow, ZERO)), G)
    s7b = ofcolor(rot180(I), SEVEN)
    p7b = intersection(shift(s7b, astuple(drow, dcol)), G)
    base = I
    base = underpaint(base, recolor(SEVEN, p7v))
    base = underpaint(base, recolor(SEVEN, p7h))
    base = underpaint(base, recolor(SEVEN, p7b))
    top = astuple(ZERO, c)
    bot = astuple(subtract(H, ONE), c)
    vline = combine(shoot(top, DOWN), shoot(bot, UP))
    L = astuple(r, ZERO)
    R = astuple(r, subtract(W, ONE))
    hline = combine(shoot(L, RIGHT), shoot(R, LEFT))
    cross = combine(vline, hline)
    O = underfill(base, TWO, cross)
    return O

def dsl5(I):
    # Cross at c = leftmost(2), r = lowermost(2); then only both-axes 7 mirroring (rot180-based) to reduce duplication
    s2 = ofcolor(I, TWO)
    if size(s2) == 0:
        return I
    c = leftmost(s2)
    r = lowermost(s2)
    H = height(I)
    W = width(I)
    G = asindices(I)
    dcol = subtract(double(c), subtract(W, ONE))
    drow = subtract(double(r), subtract(H, ONE))
    s7b = ofcolor(rot180(I), SEVEN)
    p7b = intersection(shift(s7b, astuple(drow, dcol)), G)
    base = underpaint(I, recolor(SEVEN, p7b))
    top = astuple(ZERO, c)
    bot = astuple(subtract(H, ONE), c)
    vline = combine(shoot(top, DOWN), shoot(bot, UP))
    L = astuple(r, ZERO)
    R = astuple(r, subtract(W, ONE))
    hline = combine(shoot(L, RIGHT), shoot(R, LEFT))
    cross = combine(vline, hline)
    O = underfill(base, TWO, cross)
    return O
```