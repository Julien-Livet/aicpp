```python
def dsl1(I):
    u = merge(objects(I, T, F, T))
    sub = subgrid(u, I)
    rot = rot90(sub)
    robj = asobject(rot)
    off = subtract(center(u), center(robj))
    O = move(canvas(ZERO, shape(I)), robj, off)
    return O

def dsl2(I):
    u = merge(objects(I, T, F, T))
    uin = toindices(u)
    d1 = connect(ulcorner(uin), lrcorner(uin))
    d2 = connect(urcorner(uin), llcorner(uin))
    cross = combine(d1, d2)
    O = underpaint(I, recolor(color(u), cross))
    return O

def dsl3(I):
    objs = objects(I, T, F, T)
    col = other(palette(I), ZERO)
    u = merge(colorfilter(objs, col))
    outline = box(toindices(u))
    O = fill(canvas(ZERO, shape(I)), col, outline)
    return O

def dsl4(I):
    u = merge(objects(I, T, F, T))
    sub = subgrid(u, I)
    mobj = asobject(vmirror(sub))
    ul = ulcorner(toindices(u))
    O = move(I, mobj, ul)
    return O

def dsl5(I):
    u = merge(objects(I, T, F, T))
    ring = inbox(toindices(u))
    O = underpaint(I, recolor(color(u), ring))
    return O
```