```python
def dsl1(I):
    O = rot180(I)
    return O

def dsl2(I):
    O = hmirror(vmirror(I))
    return O

def dsl3(I):
    O = rot90(rot90(I))
    return O

def dsl4(I):
    O = cmirror(dmirror(I))
    return O

def dsl5(I):
    O = paint(canvas(ZERO, shape(I)), asobject(rot180(I)))
    return O
```