```python
def dsl1(I):
    p = palette(I)
    p2 = remove(ZERO, p)
    n = size(p2)
    O = upscale(I, n)
    return O

def dsl2(I):
    p = palette(I)
    p2 = remove(ZERO, p)
    n = size(p2)
    x = vupscale(I, n)
    O = hupscale(x, n)
    return O

def dsl3(I):
    p = palette(I)
    p2 = remove(ZERO, p)
    n = size(p2)
    x = hupscale(I, n)
    O = vupscale(x, n)
    return O

def dsl4(I):
    n = subtract(size(palette(I)), ONE)
    O = upscale(I, n)
    return O

def dsl5(I):
    colors = remove(ZERO, palette(I))
    n = size(colors)
    x1 = vupscale(I, n)
    O = hconcat(hupscale(x1, n), canvas(ZERO, astuple(0, 0)))
    return O
```