```python
def dsl1(I):
    O = replace(I, ZERO, ZERO)
    return O

def dsl2(I):
    dims = shape(I)
    base = canvas(ZERO, dims)
    obj = asobject(I)
    O = paint(base, obj)
    return O

def dsl3(I):
    O = cellwise(I, I, ZERO)
    return O

def dsl4(I):
    O = hmirror(hmirror(I))
    return O

def dsl5(I):
    O = vmirror(vmirror(I))
    return O
```