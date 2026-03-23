```python
def dsl1(I):
    J = vmirror(I)
    M = ofcolor(J, ONE)
    S = shift(M, RIGHT)
    O = underpaint(I, recolor(TWO, S))
    return O

def dsl2(I):
    J = rot90(I)
    M = ofcolor(J, ONE)
    S = shift(M, RIGHT)
    P = rot270(S)
    O = underpaint(I, recolor(TWO, P))
    return O

def dsl3(I):
    J = hmirror(I)
    M = ofcolor(J, ONE)
    S = shift(M, DOWN)
    O = underpaint(I, recolor(TWO, S))
    return O

def dsl4(I):
    J = cmirror(I)
    M = ofcolor(J, ONE)
    S = shift(M, RIGHT)
    O = underpaint(I, recolor(TWO, S))
    return O

def dsl5(I):
    M = ofcolor(I, ONE)
    L1 = shift(M, LEFT)
    L2 = shift(L1, LEFT)
    P = combine(L1, L2)
    O = underpaint(I, recolor(TWO, P))
    return O
```