```python
def dsl1(I):
    O = downscale(I, TEN)
    return O

def dsl2(I):
    G = hmirror(I)
    O = downscale(G, TEN)
    return O

def dsl3(I):
    pal = remove(ZERO, palette(I))
    f = lbind(colorcount, I)
    domnz = valmax(pal, f)
    mask = ofcolor(I, domnz)
    base = canvas(ZERO, shape(I))
    pic = fill(base, domnz, mask)
    O = downscale(pic, TEN)
    return O

def dsl4(I):
    obs = objects(I, T, F, T)
    bobs = sfilter(obs, rbind(bordering, I))
    borderidxs = mapply(toindices, bobs)
    cleared = fill(I, mostcolor(I), borderidxs)
    O = downscale(cleared, TEN)
    return O

def dsl5(I):
    fobs = frontiers(I)
    fidxs = mapply(toindices, fobs)
    defrontier = fill(I, mostcolor(I), fidxs)
    O = downscale(defrontier, TEN)
    return O
```