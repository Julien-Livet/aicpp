```python
def dsl1(I):
    # Place TWOs at knight-move offsets from each FOUR
    x4 = ofcolor(I, FOUR)
    a = shift(x4, astuple(2, 1))
    b = shift(x4, astuple(1, 2))
    c = shift(x4, astuple(-1, 2))
    d = shift(x4, astuple(-2, 1))
    e = shift(x4, astuple(-2, -1))
    f = shift(x4, astuple(-1, -2))
    g = shift(x4, astuple(1, -2))
    h = shift(x4, astuple(2, -1))
    p1 = combine(combine(a, b), combine(c, d))
    p2 = combine(combine(e, f), combine(g, h))
    p = combine(p1, p2)
    O = underfill(I, TWO, p)
    return O

def dsl2(I):
    # Place TWOs at distance-2 ring around each FOUR (rook and bishop directions)
    x4 = ofcolor(I, FOUR)
    a = shift(x4, astuple(2, 0))
    b = shift(x4, astuple(-2, 0))
    c = shift(x4, astuple(0, 2))
    d = shift(x4, astuple(0, -2))
    e = shift(x4, astuple(2, 2))
    f = shift(x4, astuple(2, -2))
    g = shift(x4, astuple(-2, 2))
    h = shift(x4, astuple(-2, -2))
    p1 = combine(combine(a, b), combine(c, d))
    p2 = combine(combine(e, f), combine(g, h))
    p = combine(p1, p2)
    O = underfill(I, TWO, p)
    return O

def dsl3(I):
    # Fill the single-cell gaps between pairs of FOURS separated by one cell (all 8 directions)
    x4 = ofcolor(I, FOUR)
    # Horizontal gaps
    hr = shift(x4, astuple(0, 1))
    hl = shift(x4, astuple(0, -1))
    hgap = intersection(hr, hl)
    # Vertical gaps
    hd = shift(x4, astuple(1, 0))
    hu = shift(x4, astuple(-1, 0))
    vgap = intersection(hd, hu)
    # Diagonal gaps (main)
    d1p = shift(x4, astuple(1, 1))
    d1m = shift(x4, astuple(-1, -1))
    dgap1 = intersection(d1p, d1m)
    # Diagonal gaps (counter)
    d2p = shift(x4, astuple(1, -1))
    d2m = shift(x4, astuple(-1, 1))
    dgap2 = intersection(d2p, d2m)
    p = combine(combine(hgap, vgap), combine(dgap1, dgap2))
    O = underfill(I, TWO, p)
    return O

def dsl4(I):
    # Extend NE-SW diagonal from each FOUR by 1 and 2 steps
    x4 = ofcolor(I, FOUR)
    a = shift(x4, astuple(1, 1))
    b = shift(x4, astuple(2, 2))
    c = shift(x4, astuple(-1, -1))
    d = shift(x4, astuple(-2, -2))
    p = combine(combine(a, b), combine(c, d))
    O = underfill(I, TWO, p)
    return O

def dsl5(I):
    # Paint a 2x2 block of TWOs above-right of each FOUR
    x4 = ofcolor(I, FOUR)
    a = shift(x4, astuple(-1, 1))
    b = shift(x4, astuple(0, 1))
    c = shift(x4, astuple(-1, 2))
    d = shift(x4, astuple(0, 2))
    p = combine(combine(a, b), combine(c, d))
    O = underfill(I, TWO, p)
    return O
```