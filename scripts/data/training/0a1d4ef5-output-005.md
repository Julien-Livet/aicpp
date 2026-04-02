```python
def dsl1(I):
    C = compress(I)
    D = downscale(C, TEN)
    O = trim(D)
    return O

def dsl2(I):
    lc = leastcolor(I)
    inds = ofcolor(I, lc)
    s = subgrid(inds, I)
    g = downscale(s, TEN)
    O = trim(g)
    return O

def dsl3(I):
    bg = mostcolor(I)
    K = replace(I, bg, ZERO)
    D = downscale(K, TEN)
    O = trim(D)
    return O

def dsl4(I):
    V = vmirror(I)
    M = cellwise(I, V, ZERO)
    H = hmirror(M)
    S = cellwise(M, H, ZERO)
    D = downscale(S, TEN)
    O = trim(D)
    return O

def dsl5(I):
    obs = objects(I, T, F, T)
    mkdot = fork(recolor, color, compose(initset, center))
    dots = merge(apply(mkdot, obs))
    base = canvas(ZERO, shape(I))
    pic = paint(base, dots)
    D = downscale(pic, TEN)
    O = trim(D)
    return O
```