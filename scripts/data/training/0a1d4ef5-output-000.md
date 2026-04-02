```python
def dsl1(I):
    O = downscale(I, TEN)
    return O

def dsl2(I):
    pal = remove(ZERO, palette(I))
    col2idx = rbind(ofcolor, I)
    idxsets = apply(col2idx, pal)
    mask = merge(idxsets)
    O = subgrid(mask, I)
    return O

def dsl3(I):
    pal = remove(ZERO, palette(I))
    f = lbind(colorcount, I)
    dom = valmax(pal, f)
    mask = ofcolor(I, dom)
    base = canvas(ZERO, shape(I))
    single = fill(base, dom, mask)
    O = subgrid(mask, single)
    return O

def dsl4(I):
    C = compress(I)
    R = rot90(C)
    O = vmirror(hmirror(R))
    return O

def dsl5(I):
    obs = objects(I, T, F, T)
    bobs = mfilter(obs, rbind(bordering, I))
    idxs = mapply(toindices, bobs)
    borderpatch = merge(idxs)
    inner = cover(I, borderpatch)
    ipal = remove(ZERO, palette(inner))
    occ = apply(rbind(ofcolor, inner), ipal)
    imask = merge(occ)
    O = subgrid(imask, inner)
    return O
```