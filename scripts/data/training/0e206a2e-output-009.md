```python
def dsl1(I):
    # Global: draw the bounding box of the entire foreground with the dominant nonzero color
    colors = remove(ZERO, palette(I))
    L = argmax(colors, lbind(colorcount, I))
    objs = objects(I, T, F, T)
    fg = merge(objs)
    edge = box(fg)
    base = replace(I, L, ZERO)
    O = underfill(base, L, edge)
    return O

def dsl2(I):
    # Object extraction: ring around the merged non-dominant foreground
    colors = remove(ZERO, palette(I))
    L = argmax(colors, lbind(colorcount, I))
    objs = objects(I, T, F, T)
    nonL = sfilter(objs, compose(flip, matcher(color, L)))
    mN = merge(nonL)
    ring = outbox(mN)
    base = replace(I, L, ZERO)
    O = underfill(base, L, ring)
    return O

def dsl3(I):
    # Color filtering: per-object tight boxes around each non-dominant object
    colors = remove(ZERO, palette(I))
    L = argmax(colors, lbind(colorcount, I))
    objs = objects(I, T, F, T)
    nonL = sfilter(objs, compose(flip, matcher(color, L)))
    perboxes = mapply(box, nonL)
    edges = merge(perboxes)
    base = replace(I, L, ZERO)
    O = underfill(base, L, edges)
    return O

def dsl4(I):
    # Geometric: gravitate merged non-dominant mass toward dominant mass and outline its new position
    colors = remove(ZERO, palette(I))
    L = argmax(colors, lbind(colorcount, I))
    objs = objects(I, T, F, T)
    Lobjs = sfilter(objs, matcher(color, L))
    nonL = sfilter(objs, compose(flip, matcher(color, L)))
    mL = merge(Lobjs)
    mN = merge(nonL)
    dir = gravitate(mN, mL)
    moved = shift(mN, dir)
    edge = outbox(moved)
    base = replace(I, L, ZERO)
    O = underfill(base, L, edge)
    return O

def dsl5(I):
    # Relational: fill the negative space (bounding-box minus content) around merged non-dominant mass
    colors = remove(ZERO, palette(I))
    L = argmax(colors, lbind(colorcount, I))
    objs = objects(I, T, F, T)
    nonL = sfilter(objs, compose(flip, matcher(color, L)))
    mN = merge(nonL)
    hollow = delta(mN)
    base = replace(I, L, ZERO)
    O = underfill(base, L, hollow)
    return O
```