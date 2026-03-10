```python
def dsl1(I):
    O = upscale(I, TWO)
    return O

def dsl2(I):
    x1 = vupscale(I, TWO)
    O = hupscale(x1, TWO)
    return O

def dsl3(I):
    x1 = hupscale(I, TWO)
    O = vupscale(x1, TWO)
    return O

def dsl4(I):
    x1 = vupscale(I, TWO)
    x2 = rot90(x1)
    x3 = vupscale(x2, TWO)
    O = rot270(x3)
    return O

def dsl5(I):
    f = rbind(vupscale, TWO)
    g = rbind(hupscale, TWO)
    h = compose(g, f)
    O = h(I)
    return O
```