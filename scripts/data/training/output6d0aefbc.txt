```python
def dsl1(I):
    O = hconcat(I, vmirror(I))
    return O

def dsl2(I):
    x1 = vmirror(I)
    x2 = vmirror(x1)
    O = hconcat(x2, x1)
    return O

def dsl3(I):
    O = vmirror(hconcat(vmirror(I), I))
    return O

def dsl4(I):
    x1 = hmirror(hmirror(I))
    O = hconcat(x1, vmirror(x1))
    return O

def dsl5(I):
    x1 = vmirror(I)
    x2 = hconcat(I, x1)
    O = hmirror(hmirror(x2))
    return O
```