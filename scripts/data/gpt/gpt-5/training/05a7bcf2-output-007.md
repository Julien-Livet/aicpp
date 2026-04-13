```python
def dsl1(I):
    core = combine(combine(ofcolor(I, TWO), ofcolor(I, FOUR)), ofcolor(I, EIGHT))
    R = inbox(core)
    frame = box(R)
    A = fill(I, EIGHT, frame)
    O = underfill(A, THREE, R)
    return O

def dsl2(I):
    objs = objects(I, T, F, T)
    o4 = colorfilter(objs, FOUR)
    o2 = colorfilter(objs, TWO)
    c4 = mapply(urcorner, o4)
    c2 = mapply(ulcorner, o2)
    segs = prapply(connect, c4, c2)
    P = merge(segs)
    O = fill(I, EIGHT, P)
    return O

def dsl3(I):
    A = replace(I, FOUR, THREE)
    objs = objects(I, T, F, T)
    o2 = colorfilter(objs, TWO)
    B = mapply(compose(box, inbox), o2)
    O = fill(A, EIGHT, B)
    return O

def dsl4(I):
    M = vmirror(I)
    P = ofcolor(M, TWO)
    O = fill(I, EIGHT, P)
    return O

def dsl5(I):
    c4 = centerofmass(ofcolor(I, FOUR))
    c2 = centerofmass(ofcolor(I, TWO))
    path = connect(c4, c2)
    A = replace(I, FOUR, THREE)
    O = fill(A, EIGHT, path)
    return O
```