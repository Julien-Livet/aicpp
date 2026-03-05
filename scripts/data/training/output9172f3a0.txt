```python
def dsl1(I):
    O = upscale(I, THREE)
    return O

def dsl2(I):
    x1 = hupscale(I, THREE)
    O = vupscale(x1, THREE)
    return O

def dsl3(I):
    x1 = vupscale(I, THREE)
    O = hupscale(x1, THREE)
    return O

def dsl4(I):
    x1 = rot270(I)
    x2 = upscale(x1, THREE)
    O = rot90(x2)
    return O

def dsl5(I):
    x1 = rot180(I)
    x2 = upscale(x1, THREE)
    O = rot180(x2)
    return O
```