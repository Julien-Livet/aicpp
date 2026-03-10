```python
def dsl1(I):
    O = vconcat(I, hmirror(I))
    return O

def dsl2(I):
    x1 = hmirror(I)
    O = vconcat(I, x1)
    return O

def dsl3(I):
    x1 = vmirror(rot180(I))
    O = vconcat(I, x1)
    return O

def dsl4(I):
    x1 = rot180(vmirror(I))
    O = vconcat(I, x1)
    return O

def dsl5(I):
    x1 = rot180(I)
    x2 = vmirror(x1)
    O = vconcat(I, x2)
    return O
```