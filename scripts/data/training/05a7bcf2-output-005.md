```python
def dsl1(I):
    p2 = ofcolor(I, TWO)
    p4 = ofcolor(I, FOUR)
    p8 = ofcolor(I, EIGHT)
    big = inbox(combine(p2, combine(p4, p8)))
    frame4 = box(inbox(p4))
    A = fill(I, THREE, frame4)
    O = underfill(A, EIGHT, big)
    return O

def dsl2(I):
    objs = objects(I, T, F, T)
    o4 = colorfilter(objs, FOUR)
    o2 = colorfilter(objs, TWO)
    r4 = mapply(inbox, o4)
    r2 = mapply(inbox, o2)
    A = underfill(I, THREE, r4)
    O = underfill(A, EIGHT, r2)
    return O

def dsl3(I):
    A = replace(I, FOUR, THREE)
    core = combine(ofcolor(A, TWO), ofcolor(A, THREE))
    frame = box(inbox(core))
    O = fill(A, EIGHT, frame)
    return O

def dsl4(I):
    M = vmirror(I)
    m4 = ofcolor(M, FOUR)
    obj = recolor(EIGHT, m4)
    O = paint(I, obj)
    return O

def dsl5(I):
    p4 = ofcolor(I, FOUR)
    p2 = ofcolor(I, TWO)
    a = lrcorner(p4)
    b = ulcorner(p2)
    path = connect(a, b)
    O = fill(I, EIGHT, path)
    return O
```