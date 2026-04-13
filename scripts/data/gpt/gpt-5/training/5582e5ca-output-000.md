```python
def dsl1(I):
    c = mostcolor(I)
    O = canvas(c, shape(I))
    return O

def dsl2(I):
    c = mostcolor(I)
    obj = asobject(I)
    recol = recolor(c, obj)
    base = canvas(ZERO, shape(I))
    O = paint(base, recol)
    return O

def dsl3(I):
    p = palette(I)
    f = lbind(colorcount, I)
    c = argmax(p, f)
    O = canvas(c, shape(I))
    return O

def dsl4(I):
    c = mostcolor(I)
    seed = canvas(c, UNITY)
    tall = vupscale(seed, height(I))
    O = hupscale(tall, width(I))
    return O

def dsl5(I):
    c = mostcolor(I)
    mask = asindices(I)
    O = fill(I, c, mask)
    return O
```