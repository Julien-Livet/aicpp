```python
def dsl1(I):
    a = ofcolor(I, ONE)
    b = shift(a, RIGHT)
    c = shift(a, LEFT)
    m = intersection(b, c)
    z = ofcolor(I, ZERO)
    p = intersection(m, z)
    O = fill(I, TWO, p)
    return O

def dsl2(I):
    a = ofcolor(I, ONE)
    p = intersection(shift(a, RIGHT), shift(a, LEFT))
    O = underfill(I, TWO, p)
    return O

def dsl3(I):
    a = ofcolor(I, ONE)
    p = intersection(shift(a, RIGHT), shift(a, LEFT))
    obj = recolor(TWO, toobject(p, I))
    O = underpaint(I, obj)
    return O

def dsl4(I):
    ones = ofcolor(I, ONE)
    right_of_ones = shift(ones, RIGHT)
    left_of_ones = shift(ones, LEFT)
    between = intersection(right_of_ones, left_of_ones)
    O = fill(I, TWO, between)
    return O

def dsl5(I):
    mid = intersection(shift(ofcolor(I, ONE), RIGHT), shift(ofcolor(I, ONE), LEFT))
    obj2 = recolor(TWO, toobject(mid, I))
    O = paint(I, obj2)
    return O
```