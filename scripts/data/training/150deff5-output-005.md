```python
def dsl1(I):
    # Global morphological: mark top starts of tall vertical 5-runs (≥3) and horizontal singletons as 2
    P = ofcolor(I, FIVE)
    Top = difference(P, shift(P, UP))
    B1 = shift(P, DOWN)
    B2 = shift(P, TWO_BY_ZERO)
    TallTop = intersection(Top, intersection(B1, B2))
    TallTop2 = shift(TallTop, DOWN)
    Hiso = intersection(difference(P, shift(P, LEFT)), difference(P, shift(P, RIGHT)))
    Mark = combine(combine(TallTop, TallTop2), Hiso)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, Mark)
    return O

def dsl2(I):
    # Object extraction: per-5-object, paint the vertical line through its center as 2 (within the object)
    Os = colorfilter(objects(I, T, F, T), FIVE)
    UpF = compose(rbind(shoot, UP), center)
    DownF = compose(rbind(shoot, DOWN), center)
    Vfun = fork(combine, UpF, DownF)
    IdxF = compose(toindices, identity)
    InsideF = fork(intersection, IdxF, Vfun)
    Lines = merge(apply(InsideF, Os))
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, Lines)
    return O

def dsl3(I):
    # Color filtering: left edges of 5-runs that have depth ≥2 below, plus horizontal singletons, become 2
    P = ofcolor(I, FIVE)
    Left = difference(P, shift(P, LEFT))
    LeftDeep = intersection(Left, shift(P, TWO_BY_ZERO))
    Hiso = intersection(difference(P, shift(P, LEFT)), difference(P, shift(P, RIGHT)))
    Mark = combine(LeftDeep, Hiso)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, Mark)
    return O

def dsl4(I):
    # Geometric: vertical line through the center of the 5-region becomes 2 (inside the 5s)
    P = ofcolor(I, FIVE)
    c = center(P)
    Vline = combine(shoot(c, UP), shoot(c, DOWN))
    Inside = intersection(P, Vline)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, Inside)
    return O

def dsl5(I):
    # Relational/structural: 5-cells that are corners (simultaneous horizontal and vertical boundaries) become 2
    P = ofcolor(I, FIVE)
    L = difference(P, shift(P, LEFT))
    Rr = difference(P, shift(P, RIGHT))
    U = difference(P, shift(P, UP))
    D = difference(P, shift(P, DOWN))
    UL = intersection(L, U)
    DL = intersection(L, D)
    UR = intersection(Rr, U)
    DR = intersection(Rr, D)
    Corners = combine(combine(UL, DL), combine(UR, DR))
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, Corners)
    return O
```