```python
def dsl1(I):
    top = tophalf(I)
    left = lefthalf(top)
    new_left = canvas(SIX, shape(left))
    new_top = hconcat(new_left, vmirror(left))
    O = vconcat(new_top, bottomhalf(I))
    return O

def dsl2(I):
    O = switch(I, FIVE, SEVEN)
    return O

def dsl3(I):
    bottom = bottomhalf(I)
    new_top = hmirror(bottom)
    O = vconcat(new_top, bottom)
    return O

def dsl4(I):
    top = tophalf(I)
    cleared = canvas(SIX, shape(top))
    top_kept9 = fill(cleared, NINE, ofcolor(top, NINE))
    O = vconcat(top_kept9, bottomhalf(I))
    return O

def dsl5(I):
    union = combine(ofcolor(I, ZERO), combine(ofcolor(I, FIVE), ofcolor(I, SEVEN)))
    obj = toobject(union, I)
    off = gravitate(obj, ofcolor(I, NINE))
    O = move(I, obj, off)
    return O
```