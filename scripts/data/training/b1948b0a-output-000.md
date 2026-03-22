```python
def dsl1(I):
    O = replace(I, SIX, TWO)
    return O

def dsl2(I):
    P = ofcolor(I, SIX)
    O = fill(I, TWO, P)
    return O

def dsl3(I):
    P = ofcolor(I, SIX)
    J = cover(I, P)
    R = recolor(TWO, P)
    O = underpaint(J, R)
    return O

def dsl4(I):
    G = hmirror(hmirror(I))
    O = replace(G, SIX, TWO)
    return O

def dsl5(I):
    P = ofcolor(I, SIX)
    R = recolor(TWO, P)
    O = paint(I, R)
    return O
```