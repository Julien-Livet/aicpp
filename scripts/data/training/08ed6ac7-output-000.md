```python
def dsl1(I):
    objs = objects(I, T, F, T)
    fives = colorfilter(objs, FIVE)
    ord5 = order(fives, uppermost)
    n = size(ord5)
    cols = interval(ONE, add(n, ONE), ONE)
    recol = papply(recolor, cols, ord5)
    union = merge(recol)
    base = canvas(ZERO, shape(I))
    O = paint(base, union)
    return O

def dsl2(I):
    objs = objects(I, T, F, T)
    fives = colorfilter(objs, FIVE)
    ord5 = order(fives, centerofmass)
    n = size(ord5)
    cols = interval(ONE, add(n, ONE), ONE)
    recol = papply(recolor, cols, ord5)
    union = merge(recol)
    base = canvas(ZERO, shape(I))
    O = paint(base, union)
    return O

def dsl3(I):
    objs = objects(I, T, F, T)
    fives = colorfilter(objs, FIVE)
    ord5 = order(fives, uppermost)
    n = size(ord5)
    cols = interval(ONE, add(n, ONE), ONE)
    recol = papply(recolor, cols, ord5)
    union = merge(recol)
    base = cover(I, ofcolor(I, FIVE))
    O = underpaint(base, union)
    return O

def dsl4(I):
    Iv = vmirror(I)
    objs = objects(Iv, T, F, T)
    fives = colorfilter(objs, FIVE)
    ord5 = order(fives, uppermost)
    n = size(ord5)
    cols = interval(ONE, add(n, ONE), ONE)
    recol = papply(recolor, cols, ord5)
    union = merge(recol)
    basev = canvas(ZERO, shape(Iv))
    Ov = paint(basev, union)
    O = vmirror(Ov)
    return O

def dsl5(I):
    objs = objects(I, T, F, T)
    vobjs = sfilter(objs, vline)
    fives = colorfilter(vobjs, FIVE)
    ord5 = order(fives, uppermost)
    n = size(ord5)
    cols = interval(ONE, add(n, ONE), ONE)
    recol = papply(recolor, cols, ord5)
    union = merge(recol)
    base = canvas(ZERO, shape(I))
    O = paint(base, union)
    return O
```