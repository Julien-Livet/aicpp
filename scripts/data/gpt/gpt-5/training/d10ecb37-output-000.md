```python
def dsl1(I):
    O = crop(I, ORIGIN, TWO_BY_TWO)
    return O

def dsl2(I):
    s = combine(initset(ORIGIN), initset(add(DOWN, RIGHT)))
    b = backdrop(s)
    O = subgrid(b, I)
    return O

def dsl3(I):
    s = combine(initset(ORIGIN), initset(add(DOWN, RIGHT)))
    b = backdrop(s)
    c = cover(I, difference(asindices(I), b))
    O = trim(c)
    return O

def dsl4(I):
    g = asindices(I)
    a = ulcorner(g)
    d = shift(initset(a), UNITY)
    p = combine(initset(a), d)
    b = box(p)
    O = subgrid(b, I)
    return O

def dsl5(I):
    c = combine(vfrontier(ORIGIN), vfrontier(RIGHT))
    r = combine(hfrontier(ORIGIN), hfrontier(DOWN))
    b = intersection(c, r)
    O = subgrid(b, I)
    return O
```