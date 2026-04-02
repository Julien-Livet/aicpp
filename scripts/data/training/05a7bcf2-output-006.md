```python
def dsl1(I):
    core = combine(ofcolor(I, TWO), ofcolor(I, FOUR))
    R = inbox(core)
    frame = box(R)
    A = fill(I, EIGHT, frame)
    O = underfill(A, THREE, R)
    return O

def dsl2(I):
    objs = objects(I, T, F, T)
    o4 = colorfilter(objs, FOUR)
    r4 = mapply(inbox, o4)
    b4 = mapply(box, r4)
    B = merge(b4)
    O = fill(I, THREE, B)
    return O

def dsl3(I):
    A = replace(I, FOUR, THREE)
    r2 = inbox(ofcolor(A, TWO))
    O = underfill(A, EIGHT, r2)
    return O

def dsl4(I):
    M = hmirror(I)
    p = ofcolor(M, FOUR)
    O = fill(I, EIGHT, p)
    return O

def dsl5(I):
    objs = objects(I, T, F, T)
    o4 = colorfilter(objs, FOUR)
    o2 = colorfilter(objs, TWO)
    c4 = mapply(lrcorner, o4)
    c2 = mapply(ulcorner, o2)
    paths = prapply(connect, c4, c2)
    O = fill(I, EIGHT, paths)
    return O
```