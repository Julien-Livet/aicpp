```python
def dsl1(I):
    h = height(I)
    w = width(I)
    c = leastcolor(I)
    k = colorcount(I, c)
    r = halve(h)
    diff = subtract(w, k)
    s = halve(diff)
    ek = add(s, k)
    e = decrement(ek)
    p1 = astuple(r, s)
    p2 = astuple(r, e)
    seg = connect(p1, p2)
    dims = astuple(h, w)
    base = canvas(EIGHT, dims)
    O = fill(base, c, seg)
    return O

def dsl2(I):
    h = height(I)
    w = width(I)
    c = leastcolor(I)
    kset = ofcolor(I, c)
    k = size(kset)
    r = divide(h, TWO)
    s = divide(subtract(w, k), TWO)
    e = subtract(add(s, k), ONE)
    p1 = astuple(r, s)
    p2 = astuple(r, e)
    seg = connect(p1, p2)
    O = fill(canvas(EIGHT, astuple(h, w)), c, seg)
    return O

def dsl3(I):
    h = height(I)
    w = width(I)
    c = leastcolor(I)
    k = colorcount(I, c)
    r = divide(h, TWO)
    s = halve(subtract(w, k))
    e = decrement(add(s, k))
    seg = connect(astuple(r, s), astuple(r, e))
    O = fill(canvas(EIGHT, astuple(h, w)), c, seg)
    return O

def dsl4(I):
    h = height(I)
    w = width(I)
    c = leastcolor(I)
    k = size(ofcolor(I, c))
    r = halve(h)
    s = divide(subtract(w, k), TWO)
    e = subtract(add(s, k), ONE)
    seg = connect(astuple(r, s), astuple(r, e))
    base = canvas(EIGHT, astuple(h, w))
    O = fill(base, c, seg)
    return O

def dsl5(I):
    c = leastcolor(I)
    h = height(I)
    w = width(I)
    n = colorcount(I, c)
    row = divide(h, TWO)
    start = divide(subtract(w, n), TWO)
    stop = decrement(add(start, n))
    seg = connect(astuple(row, start), astuple(row, stop))
    O = fill(canvas(EIGHT, astuple(h, w)), c, seg)
    return O
```