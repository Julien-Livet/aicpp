```python
def dsl1(I):
    p5 = ofcolor(I, FIVE)
    c = center(p5)
    row = hfrontier(c)
    col = vfrontier(c)
    axes = combine(row, col)
    mask = intersection(p5, axes)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O

def dsl2(I):
    objs = objects(I, T, F, T)
    fives = colorfilter(objs, FIVE)
    hobjs = mfilter(fives, hline)
    vobjs = mfilter(fives, vline)
    lines = combine(hobjs, vobjs)
    lineinds = apply(toindices, lines)
    mask = merge(lineinds)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O

def dsl3(I):
    p5 = ofcolor(I, FIVE)
    outline = box(p5)
    mask = intersection(p5, outline)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O

def dsl4(I):
    p5 = ofcolor(I, FIVE)
    sl = shift(p5, LEFT)
    sr = shift(p5, RIGHT)
    su = shift(p5, UP)
    sd = shift(p5, DOWN)
    hdeep = intersection(sl, sr)
    vdeep = intersection(su, sd)
    core = intersection(p5, intersection(hdeep, vdeep))
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, core)
    return O

def dsl5(I):
    p5 = ofcolor(I, FIVE)
    lm = difference(p5, shift(p5, LEFT))
    rm = difference(p5, shift(p5, RIGHT))
    um = difference(p5, shift(p5, UP))
    dm = difference(p5, shift(p5, DOWN))
    edge = combine(combine(lm, rm), combine(um, dm))
    interior = difference(p5, edge)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, interior)
    return O
```