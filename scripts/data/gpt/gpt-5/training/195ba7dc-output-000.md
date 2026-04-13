```python
def dsl1(I):
    p2 = ofcolor(I, TWO)
    j = leftmost(p2)
    h = height(I)
    w = width(I)
    j1 = increment(j)
    left = crop(I, astuple(ZERO, ZERO), astuple(h, j))
    right = crop(I, astuple(ZERO, j1), astuple(h, subtract(w, j1)))
    left1 = replace(left, SEVEN, ONE)
    right1 = replace(right, SEVEN, ONE)
    LL = ofcolor(left1, ONE)
    RR = ofcolor(right1, ONE)
    U = combine(LL, RR)
    O = fill(canvas(ZERO, astuple(h, j)), ONE, U)
    return O

def dsl2(I):
    p2 = ofcolor(I, TWO)
    j = leftmost(p2)
    h = height(I)
    w = width(I)
    j1 = increment(j)
    left = crop(I, astuple(ZERO, ZERO), astuple(h, j))
    right = crop(I, astuple(ZERO, j1), astuple(h, subtract(w, j1)))
    left1 = replace(left, SEVEN, ONE)
    right1 = replace(right, SEVEN, ONE)
    PR = ofcolor(right1, ONE)
    O = underfill(left1, ONE, PR)
    return O

def dsl3(I):
    p2 = ofcolor(I, TWO)
    j = leftmost(p2)
    h = height(I)
    w = width(I)
    j1 = increment(j)
    left = crop(I, astuple(ZERO, ZERO), astuple(h, j))
    right = crop(I, astuple(ZERO, j1), astuple(h, subtract(w, j1)))
    left1 = replace(left, SEVEN, ONE)
    right1 = replace(right, SEVEN, ONE)
    objR = recolor(ONE, ofcolor(right1, ONE))
    O = underpaint(left1, objR)
    return O

def dsl4(I):
    p2 = ofcolor(I, TWO)
    j = leftmost(p2)
    h = height(I)
    w = width(I)
    j1 = increment(j)
    left = crop(I, astuple(ZERO, ZERO), astuple(h, j))
    right = crop(I, astuple(ZERO, j1), astuple(h, subtract(w, j1)))
    left1 = replace(left, SEVEN, ONE)
    right1 = replace(right, SEVEN, ONE)
    objL = recolor(ONE, ofcolor(left1, ONE))
    objR = recolor(ONE, ofcolor(right1, ONE))
    base = canvas(ZERO, astuple(h, j))
    tmp = paint(base, objL)
    O = paint(tmp, objR)
    return O

def dsl5(I):
    p2 = ofcolor(I, TWO)
    j = leftmost(p2)
    h = height(I)
    w = width(I)
    j1 = increment(j)
    left = crop(I, astuple(ZERO, ZERO), astuple(h, j))
    right = crop(I, astuple(ZERO, j1), astuple(h, subtract(w, j1)))
    left1 = replace(left, SEVEN, ONE)
    right1 = replace(right, SEVEN, ONE)
    PL = ofcolor(left1, ONE)
    PR = ofcolor(right1, ONE)
    base = canvas(ZERO, astuple(h, j))
    tmp = fill(base, ONE, PL)
    O = fill(tmp, ONE, PR)
    return O
```