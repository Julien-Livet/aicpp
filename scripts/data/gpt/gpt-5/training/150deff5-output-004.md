```python
def dsl1(I):
    # Global (rotation-based): mark vertical edges of 5s via top/bottom edges after rotation
    R = rot90(I)
    PR = ofcolor(R, FIVE)
    Top = difference(PR, shift(PR, UP))
    Bot = difference(PR, shift(PR, DOWN))
    EdgesR = combine(Top, Bot)
    Edges = rot270(EdgesR)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, Edges)
    return O

def dsl2(I):
    # Object extraction: per-5-object right edges become 2
    Os = colorfilter(objects(I, T, F, T), FIVE)
    f = fork(difference, identity, rbind(shift, RIGHT))
    Rg = merge(apply(f, Os))
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, Rg)
    return O

def dsl3(I):
    # Color filtering: both horizontal boundaries of 5-runs become 2
    P = ofcolor(I, FIVE)
    L = difference(P, shift(P, LEFT))
    Rr = difference(P, shift(P, RIGHT))
    Hedges = combine(L, Rr)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, Hedges)
    return O

def dsl4(I):
    # Geometric: paint the vertical line through the center of the 5-region as 2 (within the 5s)
    P = ofcolor(I, FIVE)
    c = center(P)
    Up = shoot(c, UP)
    Down = shoot(c, DOWN)
    Vline = combine(Up, Down)
    Inside = intersection(P, Vline)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, Inside)
    return O

def dsl5(I):
    # Relational/structural: 5-cells with vertical support (up & down) but on a horizontal boundary become 2
    P = ofcolor(I, FIVE)
    U = shift(P, UP)
    D = shift(P, DOWN)
    L = difference(P, shift(P, LEFT))
    Rr = difference(P, shift(P, RIGHT))
    Vert = intersection(U, D)
    Hbound = combine(L, Rr)
    Mark = intersection(P, intersection(Vert, Hbound))
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, Mark)
    return O
```