```python
def dsl1(I):
    g = asindices(I)
    c = center(g)
    v = combine(shoot(c, UP), shoot(c, DOWN))
    h = combine(shoot(c, LEFT), shoot(c, RIGHT))
    axes = combine(v, h)
    p5 = ofcolor(I, FIVE)
    mask = intersection(axes, p5)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O

def dsl2(I):
    p5 = ofcolor(I, FIVE)
    c = centerofmass(p5)
    v = combine(shoot(c, UP), shoot(c, DOWN))
    h = combine(shoot(c, LEFT), shoot(c, RIGHT))
    axes = combine(v, h)
    mask = intersection(axes, p5)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O

def dsl3(I):
    p5 = ofcolor(I, FIVE)
    vaxis = intersection(p5, vmirror(p5))
    haxis = intersection(p5, hmirror(p5))
    mask = combine(vaxis, haxis)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O

def dsl4(I):
    p5 = ofcolor(I, FIVE)
    c = centerofmass(p5)
    v = vfrontier(c)
    h = hfrontier(c)
    mask = combine(intersection(v, p5), intersection(h, p5))
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O

def dsl5(I):
    p5 = ofcolor(I, FIVE)
    ul = ulcorner(p5)
    ur = urcorner(p5)
    ll = llcorner(p5)
    lr = lrcorner(p5)
    left = connect(ul, ll)
    right = connect(ur, lr)
    top = connect(ul, ur)
    bottom = connect(ll, lr)
    edges = combine(combine(left, right), combine(top, bottom))
    mask = intersection(edges, p5)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O
```