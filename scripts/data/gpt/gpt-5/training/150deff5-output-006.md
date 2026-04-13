```python
def dsl1(I):
    # Global morphological interior: mark 5-cells that have all four orthogonal 5-neighbors as 2; others 5->8
    P = ofcolor(I, FIVE)
    InUD = intersection(shift(P, UP), shift(P, DOWN))
    InLR = intersection(shift(P, LEFT), shift(P, RIGHT))
    Core = intersection(P, intersection(InUD, InLR))
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, Core)
    return O

def dsl2(I):
    # Object extraction via center of mass: per 5-object, draw vertical line through its center of mass inside the object as 2; 5->8
    Os = colorfilter(objects(I, T, F, T), FIVE)
    UpF = compose(rbind(shoot, UP), centerofmass)
    DownF = compose(rbind(shoot, DOWN), centerofmass)
    Vfun = fork(combine, UpF, DownF)
    InsideF = fork(intersection, compose(toindices, identity), Vfun)
    Lines = merge(apply(InsideF, Os))
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, Lines)
    return O

def dsl3(I):
    # Color filtering of horizontal cores: 5-cells with both left and right 5-neighbors become 2; 5->8
    P = ofcolor(I, FIVE)
    MidH = intersection(P, intersection(shift(P, LEFT), shift(P, RIGHT)))
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, MidH)
    return O

def dsl4(I):
    # Geometric cross: vertical and horizontal lines through the center of 5-region, clipped to 5s, become 2; 5->8
    P = ofcolor(I, FIVE)
    c = center(P)
    Vline = combine(shoot(c, UP), shoot(c, DOWN))
    Hline = combine(shoot(c, LEFT), shoot(c, RIGHT))
    Cross = combine(Vline, Hline)
    Inside = intersection(P, Cross)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, Inside)
    return O

def dsl5(I):
    # Relational propagation from left edges: for each left edge of a 5-run, draw vertical ray inside 5s as 2; 5->8
    P = ofcolor(I, FIVE)
    Seeds = difference(P, shift(P, LEFT))
    UpF = rbind(shoot, UP)
    DownF = rbind(shoot, DOWN)
    Vfun = fork(combine, UpF, DownF)
    Rays = merge(apply(Vfun, Seeds))
    Inside = intersection(P, Rays)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, Inside)
    return O
```