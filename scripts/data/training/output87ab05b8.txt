```python
def dsl1(I):
    p = first(ofcolor(I, TWO))
    s = multiply(halve(p), TWO)
    a = initset(s)
    b = insert(add(s, RIGHT), a)
    c = insert(add(s, DOWN), b)
    d = insert(add(add(s, DOWN), RIGHT), c)
    base = canvas(SIX, shape(I))
    O = fill(base, TWO, d)
    return O

def dsl2(I):
    p = first(ofcolor(I, TWO))
    s = multiply(halve(p), TWO)
    a = initset(s)
    b = insert(add(s, RIGHT), a)
    c = insert(add(s, DOWN), b)
    d = insert(add(add(s, DOWN), RIGHT), c)
    base = canvas(SIX, shape(I))
    obj = recolor(TWO, toobject(d, base))
    O = paint(base, obj)
    return O

def dsl3(I):
    p = first(ofcolor(I, TWO))
    s = multiply(halve(p), TWO)
    a = initset(s)
    b = insert(add(add(s, DOWN), RIGHT), a)
    quad = backdrop(b)
    base = canvas(SIX, shape(I))
    O = fill(base, TWO, quad)
    return O

def dsl4(I):
    p = first(ofcolor(I, TWO))
    s = multiply(halve(p), TWO)
    diag = connect(s, add(add(s, DOWN), RIGHT))
    quad = backdrop(diag)
    base = canvas(SIX, shape(I))
    O = fill(base, TWO, quad)
    return O

def dsl5(I):
    q = ulcorner(ofcolor(I, TWO))
    s = multiply(halve(q), TWO)
    a = initset(s)
    b = insert(add(s, RIGHT), a)
    c = insert(add(s, DOWN), b)
    d = insert(add(add(s, DOWN), RIGHT), c)
    base = canvas(SIX, shape(I))
    O = fill(base, TWO, d)
    return O
```