```python
def dsl1(I):
    nz = difference(asindices(I), ofcolor(I, ZERO))
    y = subgrid(nz, I)
    y = rot90(y)
    O = downscale(y, TWO)
    return O

def dsl2(I):
    nz = difference(asindices(I), ofcolor(I, ZERO))
    y = subgrid(nz, I)
    y = rot270(y)
    O = downscale(y, TWO)
    return O

def dsl3(I):
    y = compress(I)
    y = dmirror(y)
    O = downscale(y, TWO)
    return O

def dsl4(I):
    nz = difference(asindices(I), ofcolor(I, ZERO))
    y = subgrid(nz, I)
    y = vmirror(y)
    y = hmirror(y)
    O = downscale(y, TWO)
    return O

def dsl5(I):
    top = tophalf(I)
    bot = bottomhalf(I)
    tl = lefthalf(top)
    tr = righthalf(top)
    bl = lefthalf(bot)
    br = righthalf(bot)
    c11 = mostcolor(tl)
    c12 = mostcolor(tr)
    c21 = mostcolor(bl)
    c22 = mostcolor(br)
    r1 = hconcat(canvas(c11, UNITY), canvas(c12, UNITY))
    r2 = hconcat(canvas(c21, UNITY), canvas(c22, UNITY))
    g2 = vconcat(r1, r2)
    O = vupscale(hupscale(g2, TWO), TWO)
    return O
```