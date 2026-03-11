```python
def dsl1(I):
    w = width(I)
    h = height(I)
    row = crop(I, astuple(1, 0), astuple(1, w))
    pattern = vupscale(row, h)
    mask = ofcolor(I, FIVE)
    obj = toobject(mask, pattern)
    base = replace(I, FIVE, ZERO)
    O = underpaint(base, obj)
    return O

def dsl2(I):
    w = width(I)
    h = height(I)
    row = crop(I, astuple(2, 0), astuple(1, w))
    pattern = vupscale(row, h)
    mask = ofcolor(I, FIVE)
    obj = toobject(mask, pattern)
    base = replace(I, FIVE, ZERO)
    O = underpaint(base, obj)
    return O

def dsl3(I):
    c = leastcolor(tophalf(I))
    O = replace(I, FIVE, c)
    return O

def dsl4(I):
    c = leastcolor(I)
    O = replace(I, FIVE, c)
    return O

def dsl5(I):
    w = width(I)
    h = height(I)
    row = crop(I, astuple(3, 0), astuple(1, w))
    pattern = vupscale(row, h)
    mask = ofcolor(I, FIVE)
    obj = toobject(mask, pattern)
    base = replace(I, FIVE, ZERO)
    O = underpaint(base, obj)
    return O
```