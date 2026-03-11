```python
def dsl1(I):
    O = hmirror(I)
    return O

def dsl2(I):
    O = vmirror(I)
    return O

def dsl3(I):
    O = rot180(I)
    return O

def dsl4(I):
    L, R = vsplit(I, 2)
    O = hconcat(R, L)
    return O

def dsl5(I):
    O = dmirror(I)
    return O
```