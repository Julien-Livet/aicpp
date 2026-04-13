```python
def dsl1(I):
    O = rot270(I)
    return O

def dsl2(I):
    O = rot180(rot90(I))
    return O

def dsl3(I):
    O = rot90(rot180(I))
    return O

def dsl4(I):
    O = hmirror(dmirror(I))
    return O

def dsl5(I):
    O = vmirror(cmirror(I))
    return O
```