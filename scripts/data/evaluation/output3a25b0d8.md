```python
def dsl1(I):
    bg = mostcolor(I)
    all_idx = asindices(I)
    bg_idx = ofcolor(I, bg)
    fg_idx = difference(all_idx, bg_idx)
    x = subgrid(fg_idx, I)
    O = downscale(x, TWO)
    return O

def dsl2(I):
    O = compress(I)
    return O

def dsl3(I):
    x = trim(I)
    O = downscale(x, TWO)
    return O

def dsl4(I):
    x = compress(I)
    O = trim(x)
    return O

def dsl5(I):
    objs = fgpartition(I)
    largest = argmax(objs, size)
    O = subgrid(toindices(largest), I)
    return O
```