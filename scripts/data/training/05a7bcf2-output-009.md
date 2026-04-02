```python
def dsl1(I):
    c4 = centerofmass(ofcolor(I, FOUR))
    c8 = centerofmass(ofcolor(I, EIGHT))
    c2 = centerofmass(ofcolor(I, TWO))
    L = inbox(connect(c4, c8))
    R = inbox(connect(c8, c2))
    G0 = replace(I, FOUR, ZERO)
    G1 = fill(G0, FOUR, L)
    G2 = underfill(G1, EIGHT, R)
    O = paint(G2, recolor(THREE, ofcolor(I, FOUR)))
    return O

def dsl2(I):
    H = hmirror(I)
    V = vmirror(I)
    P = combine(ofcolor(H, TWO), ofcolor(V, TWO))
    M = inbox(combine(P, ofcolor(I, EIGHT)))
    A = underfill(I, EIGHT, M)
    O = replace(A, FOUR, THREE)
    return O

def dsl3(I):
    objs4 = colorfilter(objects(I, T, F, T), FOUR)
    boxes = mapply(outbox, objs4)
    U = merge(boxes)
    P = inbox(combine(U, ofcolor(I, EIGHT)))
    A = underfill(I, EIGHT, P)
    O = replace(A, FOUR, THREE)
    return O

def dsl4(I):
    R8 = inbox(ofcolor(I, EIGHT))
    A = underfill(I, EIGHT, R8)
    O = replace(A, FOUR, THREE)
    return O

def dsl5(I):
    R2 = inbox(ofcolor(I, TWO))
    A = underfill(I, EIGHT, R2)
    O = replace(A, FOUR, THREE)
    return O
```