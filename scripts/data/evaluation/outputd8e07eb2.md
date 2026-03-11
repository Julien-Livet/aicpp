```python
def dsl1(I):
    fg = merge(fgpartition(I))
    rect = backdrop(fg)
    c = leastcolor(I)
    O = underfill(I, c, rect)
    return O

def dsl2(I):
    objs = fgpartition(I)
    rects = mapply(backdrop, objs)
    region = merge(rects)
    c = leastcolor(I)
    O = underfill(I, c, region)
    return O

def dsl3(I):
    h = height(I)
    w = width(I)
    topi = hfrontier(astuple(ONE, ZERO))
    boti = hfrontier(astuple(subtract(h, TWO), ZERO))
    lefti = vfrontier(astuple(ZERO, ONE))
    righti = vfrontier(astuple(ZERO, subtract(w, TWO)))
    frame = combine(combine(topi, boti), combine(lefti, righti))
    c = leastcolor(I)
    O = underfill(I, c, frame)
    return O

def dsl4(I):
    perim = box(asindices(I))
    inside = difference(asindices(I), perim)
    c = leastcolor(I)
    O = underfill(I, c, inside)
    return O

def dsl5(I):
    c = leastcolor(I)
    O = replace(I, EIGHT, c)
    return O
```