```python
def dsl1(I):
    # Global: mark vertical frontiers of the grid within the 5s
    P = ofcolor(I, FIVE)
    Fs = frontiers(I)
    V = merge(mfilter(Fs, vline))
    base = replace(I, FIVE, EIGHT)
    R = intersection(P, V)
    O = fill(base, TWO, R)
    return O

def dsl2(I):
    # Object extraction: per 5-object left edges become 2
    Os = colorfilter(objects(I, T, F, T), FIVE)
    f = fork(difference, identity, rbind(shift, LEFT))
    L = merge(apply(f, Os))
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, L)
    return O

def dsl3(I):
    # Color filtering: vertical boundaries inside the 5 mask become 2
    P = ofcolor(I, FIVE)
    T = difference(P, shift(P, UP))
    B = difference(P, shift(P, DOWN))
    R = combine(T, B)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, R)
    return O

def dsl4(I):
    # Geometric: corners of the 5s' bounding box become 2
    P = ofcolor(I, FIVE)
    C = corners(P)
    R = intersection(P, C)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, R)
    return O

def dsl5(I):
    # Relational/structural: all 4-neighborhood corners of 5 regions become 2
    P = ofcolor(I, FIVE)
    L = difference(P, shift(P, LEFT))
    Rr = difference(P, shift(P, RIGHT))
    U = difference(P, shift(P, UP))
    D = difference(P, shift(P, DOWN))
    TL = intersection(U, L)
    TR = intersection(U, Rr)
    BL = intersection(D, L)
    BR = intersection(D, Rr)
    C = merge(combine(TL, TR), combine(BL, BR))
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, C)
    return O
```