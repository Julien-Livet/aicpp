```python
def dsl1(I):
    O = hmirror(I)
    return O

def dsl2(I):
    O = dmirror(I)
    return O

def dsl3(I):
    O = rot180(I)
    return O

def dsl4(I):
    O = cmirror(I)
    return O

def dsl5(I):
    obj = asobject(I)
    base = canvas(SEVEN, shape(I))
    offset = add(UP, LEFT)
    O = move(base, obj, offset)
    return O
```