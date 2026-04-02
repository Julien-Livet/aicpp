```python
def dsl1(I):
    G = downscale(I, TEN)
    O = trim(G)
    return O

def dsl2(I):
    obs = objects(I, T, F, T)
    inds = merge(apply(toindices, obs))
    sub = subgrid(inds, I)
    O = downscale(sub, TEN)
    return O

def dsl3(I):
    obs = objects(I, T, F, T)
    mkrect = fork(recolor, color, backdrop)
    rects = merge(apply(mkrect, obs))
    base = canvas(ZERO, shape(I))
    pic = paint(base, rects)
    G = downscale(pic, TEN)
    O = trim(G)
    return O

def dsl4(I):
    G = vmirror(I)
    H = downscale(G, TEN)
    O = vmirror(H)
    return O

def dsl5(I):
    obs = objects(I, T, F, T)
    mkbox = fork(recolor, color, box)
    outlines = merge(apply(mkbox, obs))
    base = canvas(ZERO, shape(I))
    pic = paint(base, outlines)
    G = downscale(pic, TEN)
    O = trim(G)
    return O
```