```python
def dsl1(I):
    non2 = difference(asindices(I), ofcolor(I, TWO))
    region = subgrid(non2, I)
    O = replace(region, ZERO, TWO)
    return O

def dsl2(I):
    nonzero = difference(asindices(I), ofcolor(I, ZERO))
    region = subgrid(nonzero, I)
    O = replace(region, ZERO, TWO)
    return O

def dsl3(I):
    x = compress(I)
    non2 = difference(asindices(x), ofcolor(x, TWO))
    region = subgrid(non2, x)
    O = replace(region, ZERO, TWO)
    return O

def dsl4(I):
    non2 = difference(asindices(I), ofcolor(I, TWO))
    region = subgrid(non2, I)
    rr = replace(region, ZERO, TWO)
    O = downscale(rr, 2)
    return O

def dsl5(I):
    cut = bottomhalf(I)
    non2 = difference(asindices(cut), ofcolor(cut, TWO))
    region = subgrid(non2, cut)
    O = replace(region, ZERO, TWO)
    return O
```