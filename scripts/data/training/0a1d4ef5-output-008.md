```python
def dsl1(I):
    # Keep global frontiers and trim
    Fs = frontiers(I)
    allf = merge(Fs)
    O = trim(paint(canvas(ZERO, shape(I)), allf))
    return O

def dsl2(I):
    # Object extraction: crop to the widest univalued object
    obs = objects(I, T, F, T)
    o = argmax(obs, width)
    O = subgrid(o, I)
    return O

def dsl3(I):
    # Color filtering: keep the least frequent nonzero color and trim
    cols = remove(ZERO, palette(I))
    lc = argmin(cols, lbind(colorcount, I))
    inds = ofcolor(I, lc)
    obj = toobject(inds, I)
    O = trim(paint(canvas(ZERO, shape(I)), obj))
    return O

def dsl4(I):
    # Geometric: intersect with 180-degree rotation and trim
    S = cellwise(I, rot180(I), ZERO)
    O = trim(S)
    return O

def dsl5(I):
    # Relational: fill each object's bounding box (inbox) with its color, then trim
    obs = objects(I, T, F, T)
    mk = fork(recolor, color, inbox)
    rects = merge(apply(mk, obs))
    O = trim(paint(canvas(ZERO, shape(I)), rects))
    return O
```