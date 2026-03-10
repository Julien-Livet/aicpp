```python
def dsl1(I):
    x0 = asobject(I)
    x1 = shift(x0, DOWN)
    x2 = canvas(ZERO, shape(I))
    O = paint(x2, x1)
    return O

def dsl2(I):
    x0 = asobject(I)
    x1 = canvas(ZERO, shape(I))
    O = move(x1, x0, DOWN)
    return O

def dsl3(I):
    x0 = difference(asindices(I), ofcolor(I, ZERO))
    x1 = toobject(x0, I)
    x2 = canvas(ZERO, shape(I))
    O = move(x2, x1, DOWN)
    return O

def dsl4(I):
    x0 = asobject(I)
    x1 = shift(x0, DOWN)
    x2 = canvas(ZERO, shape(I))
    O = underpaint(x2, x1)
    return O
```