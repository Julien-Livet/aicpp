```python
def dsl1(I):
    O = vconcat(hmirror(I), I)
    return O

def dsl2(I):
    x1 = hmirror(I)
    x2 = hmirror(x1)
    O = vconcat(x1, x2)
    return O

def dsl3(I):
    x1 = vmirror(I)
    x2 = rot180(x1)
    O = vconcat(x2, I)
    return O

def dsl4(I):
    x1 = hmirror(I)
    x2 = vconcat(I, x1)
    O = hmirror(x2)
    return O

def dsl5(I):
    x1 = rot180(vmirror(I))
    x2 = hmirror(hmirror(I))
    O = vconcat(x1, x2)
    return O
```