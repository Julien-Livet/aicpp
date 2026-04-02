```python
def dsl1(I):
    anchors = combine(combine(ofcolor(I, TWO), ofcolor(I, FOUR)), ofcolor(I, EIGHT))
    region = inbox(anchors)
    O = underfill(I, EIGHT, region)
    return O

def dsl2(I):
    p4 = ofcolor(I, FOUR)
    p2 = ofcolor(I, TWO)
    a = urcorner(p4)
    b = ulcorner(p2)
    path = connect(a, b)
    O = fill(I, EIGHT, path)
    return O

def dsl3(I):
    e = ofcolor(I, EIGHT)
    region = inbox(e)
    O = underfill(I, EIGHT, region)
    return O

def dsl4(I):
    p4 = ofcolor(I, FOUR)
    p2 = ofcolor(I, TWO)
    core = combine(p4, p2)
    region = delta(core)
    O = underfill(I, EIGHT, region)
    return O

def dsl5(I):
    p4 = ofcolor(I, FOUR)
    p2 = ofcolor(I, TWO)
    a = centerofmass(p4)
    b = centerofmass(p2)
    path = connect(a, b)
    O = fill(I, EIGHT, path)
    return O
```