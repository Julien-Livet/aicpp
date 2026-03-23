```python
def dsl1(I):
    O = trim(I)
    return O

def dsl2(I):
    p = ofcolor(I, EIGHT)
    O = subgrid(p, I)
    return O

def dsl3(I):
    p = ofcolor(I, EIGHT)
    O = cover(I, p)
    return O

def dsl4(I):
    O = hmirror(I)
    return O

def dsl5(I):
    s = shape(I)
    base = canvas(ZERO, s)
    p = ofcolor(I, EIGHT)
    b = box(p)
    O = fill(base, EIGHT, b)
    return O
```