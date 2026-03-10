```python
def dsl1(I):
    x1 = switch(I, FIVE, SEVEN)
    O = replace(x1, SEVEN, FOUR)
    return O

def dsl2(I):
    p7 = ofcolor(I, SEVEN)
    x1 = replace(I, FIVE, FOUR)
    O = fill(x1, FIVE, p7)
    return O

def dsl3(I):
    x1 = replace(I, FIVE, FOUR)
    o7 = recolor(FIVE, toobject(ofcolor(I, SEVEN), I))
    O = paint(x1, o7)
    return O

def dsl4(I):
    p7 = ofcolor(I, SEVEN)
    x1 = fill(I, ZERO, p7)
    x2 = replace(x1, FIVE, FOUR)
    O = fill(x2, FIVE, p7)
    return O

def dsl5(I):
    p7 = ofcolor(I, SEVEN)
    x1 = replace(I, FIVE, FOUR)
    x2 = replace(x1, SEVEN, FOUR)
    O = fill(x2, FIVE, p7)
    return O
```