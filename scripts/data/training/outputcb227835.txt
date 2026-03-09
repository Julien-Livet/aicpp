```python
def dsl1(I):
    objs = colorfilter(objects(I, T, F, T), EIGHT)
    t = totuple(objs)
    a = first(t)
    b = last(t)
    p = center(a)
    q = center(b)
    l = connect(add(p, LEFT), add(q, LEFT))
    r = connect(add(p, RIGHT), add(q, RIGHT))
    band = combine(l, r)
    O = underfill(I, THREE, band)
    return O

def dsl2(I):
    objs = colorfilter(objects(I, T, F, T), EIGHT)
    t = totuple(objs)
    a = first(t)
    b = last(t)
    p = center(a)
    q = center(b)
    up = connect(add(p, UP), add(q, UP))
    dn = connect(add(p, DOWN), add(q, DOWN))
    band = combine(up, dn)
    O = underfill(I, THREE, band)
    return O

def dsl3(I):
    objs = colorfilter(objects(I, T, F, T), EIGHT)
    t = totuple(objs)
    a = first(t)
    b = last(t)
    p = center(a)
    q = center(b)
    ur = connect(add(p, UP_RIGHT), add(q, UP_RIGHT))
    dl = connect(add(p, DOWN_LEFT), add(q, DOWN_LEFT))
    band = combine(ur, dl)
    O = underfill(I, THREE, band)
    return O

def dsl4(I):
    objs = colorfilter(objects(I, T, F, T), EIGHT)
    t = totuple(objs)
    a = first(t)
    b = last(t)
    p = center(a)
    q = center(b)
    ul = connect(add(p, UP_LEFT), add(q, UP_LEFT))
    dr = connect(add(p, DOWN_RIGHT), add(q, DOWN_RIGHT))
    band = combine(ul, dr)
    O = underfill(I, THREE, band)
    return O

def dsl5(I):
    objs = colorfilter(objects(I, T, F, T), EIGHT)
    t = totuple(objs)
    a = first(t)
    b = last(t)
    p = center(a)
    q = center(b)
    core = connect(p, q)
    rect = box(backdrop(core))
    O = underfill(I, THREE, rect)
    return O
```