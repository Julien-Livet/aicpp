```python
def dsl1(I):
    # Subgrid of the bottom-right-most univalued object
    obs = objects(I, T, F, T)
    comp = fork(add, lowermost, rightmost)
    o = argmax(obs, comp)
    O = subgrid(toindices(o), I)
    return O

def dsl2(I):
    # Two rightmost columns that contain any non-zero, then trim
    nz = difference(asindices(I), ofcolor(I, ZERO))
    jr = rightmost(nz)
    jl = decrement(jr)
    h = height(I)
    sub = crop(I, astuple(0, jl), astuple(h, TWO))
    O = trim(sub)
    return O

def dsl3(I):
    # Compress grid by removing frontiers
    O = compress(I)
    return O

def dsl4(I):
    # 3x3 ring of the least common non-zero color
    cols = remove(ZERO, palette(I))
    c = argmin(cols, lbind(colorcount, I))
    Z = canvas(ZERO, THREE_BY_THREE)
    O = fill(Z, c, box(asindices(Z)))
    return O

def dsl5(I):
    # Three rightmost columns that contain any non-zero, then trim
    nz = difference(asindices(I), ofcolor(I, ZERO))
    jr = rightmost(nz)
    j0 = subtract(jr, TWO)
    h = height(I)
    sub = crop(I, astuple(0, j0), astuple(h, THREE))
    O = trim(sub)
    return O
```