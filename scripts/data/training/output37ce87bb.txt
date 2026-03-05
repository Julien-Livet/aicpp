```python
def dsl1(I):
    H = height(I)
    W = width(I)
    j = subtract(W, TWO)
    c8 = colorcount(I, EIGHT)
    c2 = colorcount(I, TWO)
    h = subtract(c8, c2)
    start_row = subtract(H, h)
    start = astuple(start_row, j)
    patch = shoot(start, DOWN)
    O = fill(I, FIVE, patch)
    return O

def dsl2(I):
    H = height(I)
    W = width(I)
    j = subtract(W, TWO)
    c8 = colorcount(I, EIGHT)
    c2 = colorcount(I, TWO)
    h = subtract(c8, c2)
    start_row = subtract(H, h)
    start = astuple(start_row, j)
    end = astuple(subtract(H, ONE), j)
    patch = connect(start, end)
    O = fill(I, FIVE, patch)
    return O

def dsl3(I):
    W = width(I)
    j = subtract(W, TWO)
    n8 = colorcount(I, EIGHT)
    n2 = colorcount(I, TWO)
    h = subtract(n8, n2)
    H = height(I)
    top = subtract(H, h)
    colstart = astuple(ZERO, j)
    fullcol = shoot(colstart, DOWN)
    top_idx = astuple(top, j)
    topline = shoot(top_idx, DOWN)
    patch = intersection(fullcol, topline)
    O = fill(I, FIVE, patch)
    return O
```