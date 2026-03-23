```python
def dsl1(I):
    J = dmirror(I)
    objs = objects(J, T, F, T)
    m = merge(objs)
    O = underpaint(I, m)
    return O

def dsl2(I):
    objs = objects(I, T, F, T)
    a = first(colorfilter(objs, TWO))
    b = first(colorfilter(objs, FIVE))
    d = gravitate(toindices(a), toindices(b))
    a2 = shift(a, d)
    base = cover(I, a)
    O = paint(base, a2)
    return O

def dsl3(I):
    objs = objects(I, T, F, T)
    a = first(colorfilter(objs, TWO))
    b = first(colorfilter(objs, FIVE))
    d = sign(gravitate(toindices(a), toindices(b)))
    a1 = shift(a, d)
    b1 = shift(b, invert(d))
    O = underpaint(underpaint(I, a1), b1)
    return O

def dsl4(I):
    objs = objects(I, T, F, T)
    a = first(colorfilter(objs, TWO))
    b = first(colorfilter(objs, FIVE))
    ca = centerofmass(toindices(a))
    cb = centerofmass(toindices(b))
    ln = connect(ca, cb)
    obj = recolor(FIVE, ln)
    O = underpaint(I, obj)
    return O

def dsl5(I):
    O = switch(I, TWO, FIVE)
    return O
```