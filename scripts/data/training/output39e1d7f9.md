```python
def dsl1(I):
    O = rot90(I)
    return O

def dsl2(I):
    O = rot270(I)
    return O

def dsl3(I):
    O = vmirror(I)
    return O

def dsl4(I):
    O = rot180(I)
    return O

def dsl5(I):
    x1 = rot90(I)
    O = dmirror(x1)
    return O
```