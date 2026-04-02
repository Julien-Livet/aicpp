```python
def dsl1(I):
    # Relational: propagate columns from horizontally isolated 5s (singletons) upward and downward; others 5->8
    P = ofcolor(I, FIVE)
    Hleft = shift(P, LEFT)
    Hright = shift(P, RIGHT)
    Singles = difference(P, combine(Hleft, Hright))
    Up = rbind(shoot, UP)
    Down = rbind(shoot, DOWN)
    Vline = fork(combine, compose(Up, identity), compose(Down, identity))
    Lines = merge(apply(Vline, Singles))
    Stripe = intersection(P, Lines)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, Stripe)
    return O

def dsl2(I):
    # Global morphological: mark vertical endpoints (no 5 above and no 5 below); others 5->8
    P = ofcolor(I, FIVE)
    UpAdj = intersection(P, shift(P, UP))
    DownAdj = intersection(P, shift(P, DOWN))
    HasNeighbor = combine(UpAdj, DownAdj)
    Endpoints = difference(P, HasNeighbor)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, Endpoints)
    return O

def dsl3(I):
    # Color filtering: unsupported from below (no 5 directly below) become 2; others 5->8
    P = ofcolor(I, FIVE)
    Below = shift(P, DOWN)
    Unsupported = difference(P, Below)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, Unsupported)
    return O

def dsl4(I):
    # Object extraction: per-5-object right edge pixels become 2; others 5->8
    Os = colorfilter(objects(I, T, F, T), FIVE)
    ShL = rbind(shift, LEFT)
    Inx = toindices
    HasRight = fork(intersection, compose(Inx, identity), compose(ShL, compose(Inx, identity)))
    RightEdge = fork(difference, compose(Inx, identity), HasRight)
    EdgeCols = merge(apply(RightEdge, Os))
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, EdgeCols)
    return O

def dsl5(I):
    # Geometric (period-2 vertical alignment): columns where a 5 recurs two rows apart become 2 (propagated along the column); others 5->8
    P = ofcolor(I, FIVE)
    P1 = shift(P, DOWN)
    P2 = shift(P1, DOWN)
    Seeds = intersection(P, P2)
    Up = rbind(shoot, UP)
    Down = rbind(shoot, DOWN)
    Vline = fork(combine, compose(Up, identity), compose(Down, identity))
    Lines = merge(apply(Vline, Seeds))
    Stripe = intersection(P, Lines)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, Stripe)
    return O
```