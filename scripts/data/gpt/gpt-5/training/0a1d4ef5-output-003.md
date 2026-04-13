```python
def dsl1(I):
    G = compress(I)
    O = downscale(G, TEN)
    return O

def dsl2(I):
    obs = objects(I, T, F, T)
    bobs = sfilter(obs, rbind(bordering, I))
    inner = difference(obs, bobs)
    big = argmax(inner, size)
    base = canvas(ZERO, shape(I))
    iso = paint(base, big)
    O = downscale(iso, TEN)
    return O

def dsl3(I):
    lc = leastcolor(I)
    mask = ofcolor(I, lc)
    base = canvas(ZERO, shape(I))
    pic = fill(base, lc, mask)
    O = downscale(pic, TEN)
    return O

def dsl4(I):
    G = rot90(I)
    O = downscale(G, TEN)
    return O

def dsl5(I):
    obs = objects(I, T, F, T)
    g = fork(recolor, color, backdrop)
    rects = merge(apply(g, obs))
    base = canvas(ZERO, shape(I))
    pic = paint(base, rects)
    O = downscale(pic, TEN)
    return O
```