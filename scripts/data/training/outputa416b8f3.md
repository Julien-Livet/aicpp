```python
def dsl1(I):
    O = hconcat(I, I)
    return O

def dsl2(I):
    x1 = crop(I, ORIGIN, shape(I))
    O = hconcat(I, x1)
    return O

def dsl3(I):
    O = hconcat(identity(I), identity(I))
    return O

def dsl4(I):
    x0 = astuple(height(I), multiply(width(I), TWO))
    x1 = canvas(ZERO, x0)
    x2 = asobject(I)
    x3 = shift(x2, tojvec(width(I)))
    x4 = combine(x2, x3)
    O = paint(x1, x4)
    return O

def dsl5(I):
    x0 = astuple(height(I), multiply(width(I), TWO))
    x1 = canvas(ZERO, x0)
    x2 = asobject(I)
    x3 = paint(x1, x2)
    x4 = shift(x2, tojvec(width(I)))
    O = paint(x3, x4)
    return O
```