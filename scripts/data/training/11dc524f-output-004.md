```python
def dsl1(I):
    R = rot180(I)
    A = ofcolor(R, TWO)
    B = ofcolor(R, FIVE)
    d = gravitate(A, B)
    base = replace(R, TWO, SEVEN)
    R2 = paint(base, recolor(TWO, shift(A, d)))
    O = rot180(R2)
    return O

def dsl2(I):
    A = ofcolor(I, TWO)
    B = ofcolor(I, FIVE)
    aobj = toobject(A, I)
    d = gravitate(A, B)
    O = move(I, aobj, d)
    return O

def dsl3(I):
    A = ofcolor(I, TWO)
    B = ofcolor(I, FIVE)
    d = gravitate(box(A), box(B))
    base = replace(I, TWO, SEVEN)
    O = underfill(base, TWO, shift(A, d))
    return O

def dsl4(I):
    H = hmirror(I)
    A = ofcolor(H, TWO)
    B = ofcolor(H, FIVE)
    d = gravitate(A, B)
    base = replace(H, TWO, SEVEN)
    H2 = paint(base, recolor(TWO, shift(A, d)))
    O = hmirror(H2)
    return O

def dsl5(I):
    A = ofcolor(I, TWO)
    B = ofcolor(I, FIVE)
    ca = center(A)
    dir = position(A, B)
    ray = shoot(ca, dir)
    tgt = intersection(ray, box(B))
    d = gravitate(A, tgt)
    base = replace(I, TWO, SEVEN)
    O = paint(base, recolor(TWO, shift(A, d)))
    return O
```