```python
def dsl1(I):
    c = mostcolor(I)
    P = box(asindices(I))
    O = paint(I, recolor(c, P))
    return O

def dsl2(I):
    Os = objects(I, T, F, T)
    Ps = apply(compose(box, toindices), Os)
    P = merge(Ps)
    S = argmin(Os, size)
    c = color(S)
    O = paint(I, recolor(c, P))
    return O

def dsl3(I):
    lc = leastcolor(I)
    O = replace(I, lc, ZERO)
    return O

def dsl4(I):
    lc = leastcolor(I)
    P = ofcolor(I, lc)
    C = centerofmass(P)
    H = hfrontier(C)
    V = vfrontier(C)
    X = combine(H, V)
    O = paint(I, recolor(lc, X))
    return O

def dsl5(I):
    lc = leastcolor(I)
    P = ofcolor(I, lc)
    A = ulcorner(P)
    B = lrcorner(P)
    L = connect(A, B)
    O = paint(I, recolor(lc, L))
    return O
```