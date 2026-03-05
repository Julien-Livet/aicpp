```python
def dsl1(I):
    x1 = objects(I, T, F, T)
    x2 = argmax(x1, size)
    O = subgrid(x2, I)
    return O

def dsl2(I):
    x1 = fgpartition(I)
    x2 = argmax(x1, size)
    O = subgrid(x2, I)
    return O

def dsl3(I):
    x1 = palette(I)
    x2 = remove(ZERO, x1)
    x3 = argmax(x2, lbind(colorcount, I))
    x4 = ofcolor(I, x3)
    O = subgrid(x4, I)
    return O
```