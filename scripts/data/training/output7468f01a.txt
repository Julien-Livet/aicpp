```python
def dsl1(I):
    x1 = asindices(I)
    x2 = ofcolor(I, mostcolor(I))
    x3 = difference(x1, x2)
    x4 = subgrid(x3, I)
    O = vmirror(x4)
    return O

def dsl2(I):
    x1 = asindices(I)
    x2 = ofcolor(I, ZERO)
    x3 = difference(x1, x2)
    x4 = subgrid(x3, I)
    O = vmirror(x4)
    return O

def dsl3(I):
    x1 = fgpartition(I)
    x2 = merge(x1)
    x3 = subgrid(x2, I)
    O = vmirror(x3)
    return O

def dsl4(I):
    x1 = objects(I, True, False, True)
    x2 = merge(x1)
    x3 = subgrid(x2, I)
    O = vmirror(x3)
    return O
```