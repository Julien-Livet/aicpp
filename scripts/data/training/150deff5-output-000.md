```python
def dsl1(I):
    g = asindices(I)
    c = center(g)
    v1 = shoot(c, UP)
    v2 = shoot(c, DOWN)
    v = combine(v1, v2)
    p5 = ofcolor(I, FIVE)
    mask = intersection(v, p5)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O

def dsl2(I):
    p5 = ofcolor(I, FIVE)
    b = box(p5)
    edge = intersection(b, p5)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, edge)
    return O

def dsl3(I):
    O = replace(I, FIVE, EIGHT)
    return O

def dsl4(I):
    p5 = ofcolor(I, FIVE)
    c = center(p5)
    h1 = shoot(c, LEFT)
    h2 = shoot(c, RIGHT)
    h = combine(h1, h2)
    mask = intersection(h, p5)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O

def dsl5(I):
    p5 = ofcolor(I, FIVE)
    c = center(p5)
    v = combine(shoot(c, UP), shoot(c, DOWN))
    h = combine(shoot(c, LEFT), shoot(c, RIGHT))
    axes = combine(v, h)
    mask = intersection(axes, p5)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, mask)
    return O
```