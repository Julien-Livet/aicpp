```python
def dsl1(I):
    x1 = replace(I, mostcolor(I), ZERO)
    O = downscale(x1, NINE)
    return O

def dsl2(I):
    x1 = replace(I, mostcolor(I), ZERO)
    x2 = downscale(x1, THREE)
    O = downscale(x2, THREE)
    return O

def dsl3(I):
    x1 = replace(I, mostcolor(I), ZERO)
    x2 = downscale(x1, NINE)
    O = replace(x2, mostcolor(x2), ZERO)
    return O

def dsl4(I):
    x1 = replace(I, mostcolor(I), ZERO)
    x2 = downscale(x1, THREE)
    x3 = compress(x2)
    O = downscale(x3, THREE)
    return O

def dsl5(I):
    x1 = replace(I, mostcolor(I), ZERO)
    x2 = downscale(x1, THREE)
    x3 = downscale(x2, THREE)
    O = replace(x3, mostcolor(x3), ZERO)
    return O
```