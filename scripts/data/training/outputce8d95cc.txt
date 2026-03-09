```python
def dsl1(I):
    x1 = rot90(I)
    x2 = compress(x1)
    x3 = rot270(x2)
    O = compress(x3)
    return O

def dsl2(I):
    x1 = hmirror(I)
    x2 = compress(x1)
    O = hmirror(x2)
    return O

def dsl3(I):
    x1 = vmirror(I)
    x2 = compress(x1)
    O = vmirror(x2)
    return O

def dsl4(I):
    x1 = compress(I)
    x2 = rot90(x1)
    x3 = compress(x2)
    O = rot270(x3)
    return O

def dsl5(I):
    x1 = frontiers(I)
    x2 = merge(x1)
    x3 = canvas(ZERO, shape(I))
    x4 = paint(x3, x2)
    O = compress(x4)
    return O
```