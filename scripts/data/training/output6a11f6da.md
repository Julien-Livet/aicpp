```python
def dsl1(I):
    h = divide(height(I), THREE)
    w = width(I)
    top = crop(I, astuple(ZERO, ZERO), astuple(h, w))
    mid = crop(I, astuple(h, ZERO), astuple(h, w))
    bot = crop(I, astuple(multiply(h, TWO), ZERO), astuple(h, w))
    base = canvas(ZERO, astuple(h, w))
    s6 = ofcolor(bot, SIX)
    s1 = ofcolor(top, ONE)
    s8 = ofcolor(mid, EIGHT)
    x1 = fill(base, SIX, s6)
    x2 = underfill(x1, ONE, s1)
    O = underfill(x2, EIGHT, s8)
    return O

def dsl2(I):
    top = crop(I, astuple(0, 0), astuple(5, 5))
    mid = crop(I, astuple(5, 0), astuple(5, 5))
    bot = crop(I, astuple(10, 0), astuple(5, 5))
    base = canvas(ZERO, astuple(5, 5))
    O = fill(base, SIX, ofcolor(bot, SIX))
    O = underfill(O, ONE, ofcolor(top, ONE))
    O = underfill(O, EIGHT, ofcolor(mid, EIGHT))
    return O

def dsl3(I):
    top = crop(I, astuple(0, 0), astuple(5, 5))
    mid = crop(I, astuple(5, 0), astuple(5, 5))
    bot = crop(I, astuple(10, 0), astuple(5, 5))
    o1 = toobject(ofcolor(top, ONE), top)
    o8 = toobject(ofcolor(mid, EIGHT), mid)
    o6 = toobject(ofcolor(bot, SIX), bot)
    base = canvas(ZERO, astuple(5, 5))
    a = underpaint(base, o8)
    b = paint(a, o1)
    O = paint(b, o6)
    return O

def dsl4(I):
    t = crop(I, astuple(0, 0), astuple(5, 5))
    m = crop(I, astuple(5, 0), astuple(5, 5))
    b = crop(I, astuple(10, 0), astuple(5, 5))
    o1 = toobject(ofcolor(t, ONE), t)
    o8 = toobject(ofcolor(m, EIGHT), m)
    o6 = toobject(ofcolor(b, SIX), b)
    base = canvas(ZERO, astuple(5, 5))
    x = paint(base, o1)
    y = underpaint(x, o8)
    O = paint(y, o6)
    return O

def dsl5(I):
    top = crop(I, astuple(0, 0), astuple(5, 5))
    mid = crop(I, astuple(5, 0), astuple(5, 5))
    bot = crop(I, astuple(10, 0), astuple(5, 5))
    base = canvas(ZERO, astuple(5, 5))
    a = underfill(base, EIGHT, ofcolor(mid, EIGHT))
    b = underfill(a, ONE, ofcolor(top, ONE))
    O = fill(b, SIX, ofcolor(bot, SIX))
    return O
```