```python
def dsl1(I):
    objs = objects(I, T, F, T)
    uobj = merge(objs)
    uin = toindices(uobj)
    ul = ulcorner(uin)
    lr = lrcorner(uin)
    diag = connect(ul, lr)
    col = color(uobj)
    O = underpaint(I, recolor(col, diag))
    return O

def dsl2(I):
    uobj = merge(objects(I, T, F, T))
    uin = toindices(uobj)
    ul = ulcorner(uin)
    sub = subgrid(uobj, I)
    rot = rot90(sub)
    robj = asobject(rot)
    base = canvas(ZERO, shape(I))
    O = move(base, robj, ul)
    return O

def dsl3(I):
    uobj = merge(objects(I, T, F, T))
    bbox = backdrop(toindices(uobj))
    col = color(uobj)
    base = canvas(ZERO, shape(I))
    O = fill(base, col, bbox)
    return O

def dsl4(I):
    uobj = merge(objects(I, T, F, T))
    uin = toindices(uobj)
    inner = delta(uin)
    col = color(uobj)
    O = underpaint(I, recolor(col, inner))
    return O

def dsl5(I):
    uobj = merge(objects(I, T, F, T))
    uin = toindices(uobj)
    col = color(uobj)
    s1 = uin
    s2 = shift(uin, UNITY)
    s3 = shift(uin, RIGHT)
    s4 = shift(uin, DOWN)
    combo = combine(combine(s1, s2), combine(s3, s4))
    obj = recolor(col, combo)
    O = underpaint(I, obj)
    return O
```