```python
def dsl1(I):
    O = dmirror(I)
    return O

def dsl2(I):
    O = vmirror(rot90(I))
    return O

def dsl3(I):
    obj = asobject(I)
    base = canvas(ZERO, shape(I))
    O = paint(base, dmirror(obj))
    return O

def dsl4(I):
    O = cmirror(rot180(I))
    return O

def dsl5(I):
    O = hmirror(rot270(I))
    return O
```