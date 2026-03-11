```python
def dsl1(I):
    c = leastcolor(I)
    allidx = asindices(I)
    bg = ofcolor(I, EIGHT)
    nonbg = difference(allidx, bg)
    bbox = backdrop(nonbg)
    pcs = ofcolor(I, c)
    loc = first(pcs)
    col = vfrontier(loc)
    seg = intersection(bbox, col)
    O = underfill(I, c, seg)
    return O

def dsl2(I):
    x1 = vmirror(I)
    obj = asobject(x1)
    O = underpaint(I, obj)
    return O

def dsl3(I):
    x1 = vmirror(I)
    x2 = hmirror(I)
    obj1 = asobject(x1)
    obj2 = asobject(x2)
    tmp = underpaint(I, obj1)
    O = underpaint(tmp, obj2)
    return O

def dsl4(I):
    top = tophalf(I)
    bot = vmirror(top)
    O = vconcat(top, bot)
    return O

def dsl5(I):
    x1 = cmirror(I)
    obj = asobject(x1)
    O = underpaint(I, obj)
    return O
```