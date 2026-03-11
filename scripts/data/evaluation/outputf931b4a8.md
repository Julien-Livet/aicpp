```python
def dsl1(I):
    bh = bottomhalf(I)
    bl = lefthalf(bh)
    br = righthalf(bh)
    c = mostcolor(bl)
    O = replace(br, ZERO, c)
    return O

def dsl2(I):
    O = lefthalf(bottomhalf(I))
    return O

def dsl3(I):
    bh = bottomhalf(I)
    bl = lefthalf(bh)
    br = righthalf(bh)
    c = mostcolor(bl)
    B = replace(br, ZERO, c)
    X = hconcat(B, B)
    Y = vconcat(X, X)
    O = vconcat(Y, Y)
    return O

def dsl4(I):
    th = tophalf(I)
    br = righthalf(bottomhalf(I))
    bg = mostcolor(righthalf(th))
    B = replace(br, ZERO, bg)
    O = vconcat(B, B)
    return O

def dsl5(I):
    bh = bottomhalf(I)
    bl = lefthalf(bh)
    br = righthalf(bh)
    c = mostcolor(bl)
    B = replace(br, ZERO, c)
    O = hconcat(B, bl)
    return O
```