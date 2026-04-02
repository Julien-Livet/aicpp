```python
def dsl1(I):
    # Relational: propagate upward from horizontally isolated 5s; others 5->8
    P = ofcolor(I, FIVE)
    Singles = difference(P, combine(shift(P, LEFT), shift(P, RIGHT)))
    Up = rbind(shoot, UP)
    Lines = merge(apply(Up, Singles))
    Stripe = intersection(P, Lines)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, Stripe)
    return O

def dsl2(I):
    # Geometric: vertical XOR endpoints (cells with exactly one vertical neighbor) ->2; others 5->8
    P = ofcolor(I, FIVE)
    HasUp = intersection(P, shift(P, UP))
    HasDown = intersection(P, shift(P, DOWN))
    OneVertNeighbor = difference(combine(HasUp, HasDown), intersection(HasUp, HasDown))
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, OneVertNeighbor)
    return O

def dsl3(I):
    # Color filtering: top/bottom endpoints that also have a horizontal neighbor ->2; others 5->8
    P = ofcolor(I, FIVE)
    Top = difference(P, shift(P, UP))
    Bottom = difference(P, shift(P, DOWN))
    HasHor = combine(intersection(P, shift(P, LEFT)), intersection(P, shift(P, RIGHT)))
    Seeds = intersection(combine(Top, Bottom), HasHor)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, Seeds)
    return O

def dsl4(I):
    # Object extraction: per-5-object, propagate upward from row-singletons within the object; others 5->8
    Os = colorfilter(objects(I, T, F, T), FIVE)
    Inx = toindices
    ShL = rbind(shift, LEFT)
    ShR = rbind(shift, RIGHT)
    Hnbr = fork(combine, compose(ShL, Inx), compose(ShR, Inx))
    SinglesOf = fork(difference, Inx, Hnbr)
    SinglesSets = apply(SinglesOf, Os)
    SinglesAll = merge(SinglesSets)
    Up = rbind(shoot, UP)
    UpLines = merge(apply(Up, SinglesAll))
    Stripe = intersection(ofcolor(I, FIVE), UpLines)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, Stripe)
    return O

def dsl5(I):
    # Global: mark 5-cells that lie on any frontier as 2; others 5->8
    Fr = frontiers(I)
    FrIdxSets = apply(toindices, Fr)
    FrIdx = merge(FrIdxSets)
    EdgeOnFive = intersection(ofcolor(I, FIVE), FrIdx)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, EdgeOnFive)
    return O
```