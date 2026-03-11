```python
def dsl1(I):
    c = leastcolor(I)
    idx = ofcolor(I, c)
    O = subgrid(idx, I)
    return O

def dsl2(I):
    idx = ofcolor(I, EIGHT)
    O = subgrid(idx, I)
    return O

def dsl3(I):
    a = ofcolor(I, EIGHT)
    b = ofcolor(I, FOUR)
    idx = combine(a, b)
    O = subgrid(idx, I)
    return O

def dsl4(I):
    a = ofcolor(I, EIGHT)
    b = ofcolor(I, NINE)
    c = ofcolor(I, THREE)
    idx = combine(combine(a, b), c)
    O = subgrid(idx, I)
    return O

def dsl5(I):
    bg = mostcolor(I)
    J = replace(I, bg, ZERO)
    O = trim(J)
    return O
```