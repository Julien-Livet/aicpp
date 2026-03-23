```python
def dsl1(I):
    s7 = ofcolor(I, SEVEN)
    r = uppermost(s7)
    w = width(I)
    h = r
    dims = astuple(h, w)
    top = crop(I, ORIGIN, dims)
    bot = crop(I, astuple(add(r, ONE), ZERO), astuple(subtract(height(I), add(r, ONE)), w))
    both = intersection(ofcolor(top, ZERO), ofcolor(bot, ZERO))
    O = fill(canvas(ZERO, dims), EIGHT, both)
    return O

def dsl2(I):
    s7 = ofcolor(I, SEVEN)
    r = uppermost(s7)
    w = width(I)
    h = r
    dims = astuple(h, w)
    top = crop(I, ORIGIN, dims)
    bot = crop(I, astuple(add(r, ONE), ZERO), astuple(subtract(height(I), add(r, ONE)), w))
    A = replace(top, ZERO, EIGHT)
    B = replace(bot, ZERO, EIGHT)
    O = cellwise(A, B, ZERO)
    return O

def dsl3(I):
    s7 = ofcolor(I, SEVEN)
    r = uppermost(s7)
    w = width(I)
    h = r
    dims = astuple(h, w)
    top = crop(I, ORIGIN, dims)
    bot = crop(I, astuple(add(r, ONE), ZERO), astuple(subtract(height(I), add(r, ONE)), w))
    Tnz = difference(asindices(top), ofcolor(top, ZERO))
    Bnz = difference(asindices(bot), ofcolor(bot, ZERO))
    mask = combine(Tnz, Bnz)
    O = cover(canvas(EIGHT, dims), mask)
    return O

def dsl4(I):
    s7 = ofcolor(I, SEVEN)
    r = uppermost(s7)
    w = width(I)
    h = r
    dims = astuple(h, w)
    top = crop(I, ORIGIN, dims)
    bot = crop(I, astuple(add(r, ONE), ZERO), astuple(subtract(height(I), add(r, ONE)), w))
    both = intersection(ofcolor(top, ZERO), ofcolor(bot, ZERO))
    obj = recolor(EIGHT, both)
    O = paint(canvas(ZERO, dims), obj)
    return O

def dsl5(I):
    s7 = ofcolor(I, SEVEN)
    r = uppermost(s7)
    w = width(I)
    h = r
    dims = astuple(h, w)
    top = crop(I, ORIGIN, dims)
    bot = crop(I, astuple(add(r, ONE), ZERO), astuple(subtract(height(I), add(r, ONE)), w))
    Tnz = difference(asindices(top), ofcolor(top, ZERO))
    Bnz = difference(asindices(bot), ofcolor(bot, ZERO))
    TnzMask = fill(canvas(ZERO, dims), EIGHT, Tnz)
    BnzMask = fill(canvas(ZERO, dims), EIGHT, Bnz)
    bothNonZero = cellwise(TnzMask, BnzMask, ZERO)
    O = cover(canvas(EIGHT, dims), ofcolor(bothNonZero, EIGHT))
    return O
```