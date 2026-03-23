```python
def dsl1(I):
    R = hmirror(I)
    aidx = ofcolor(R, TWO)
    bidx = ofcolor(R, FIVE)
    d = gravitate(aidx, bidx)
    base = fill(R, SEVEN, aidx)
    tgt = shift(aidx, d)
    R2 = fill(base, TWO, tgt)
    O = hmirror(R2)
    return O

def dsl2(I):
    objs = objects(I, T, F, T)
    a = first(colorfilter(objs, TWO))
    b = first(colorfilter(objs, FIVE))
    d = gravitate(toindices(a), toindices(b))
    base = cover(I, a)
    O = paint(base, recolor(TWO, shift(a, d)))
    return O

def dsl3(I):
    aidx = ofcolor(I, TWO)
    bidx = ofcolor(I, FIVE)
    d = gravitate(aidx, bidx)
    base = replace(I, TWO, SEVEN)
    tgt = shift(aidx, d)
    O = fill(base, TWO, tgt)
    return O

def dsl4(I):
    objs = objects(I, T, F, T)
    a = first(colorfilter(objs, TWO))
    b = first(colorfilter(objs, FIVE))
    A = toindices(a)
    B = toindices(b)
    d = gravitate(box(A), box(B))
    base = cover(I, a)
    O = paint(base, shift(a, d))
    return O

def dsl5(I):
    aidx = ofcolor(I, TWO)
    bidx = ofcolor(I, FIVE)
    d = gravitate(inbox(aidx), inbox(bidx))
    base = fill(I, SEVEN, aidx)
    tgt = shift(aidx, d)
    O = fill(base, TWO, tgt)
    return O
```