```python
def dsl1(I):
    # crop the same-sized block immediately to the left of the 8-rectangle
    p = ofcolor(I, EIGHT)
    G = subgrid(p, I)
    h = height(G)
    w = width(G)
    ul = ulcorner(p)
    s = subtract(ul, astuple(ZERO, w))
    O = crop(I, s, astuple(h, w))
    return O

def dsl2(I):
    # crop the same-sized block immediately above the 8-rectangle (shift by full height)
    p = ofcolor(I, EIGHT)
    G = subgrid(p, I)
    h = height(G)
    w = width(G)
    ul = ulcorner(p)
    s = subtract(ul, astuple(h, ZERO))
    O = crop(I, s, astuple(h, w))
    return O

def dsl3(I):
    # crop the same-sized block immediately below the 8-rectangle (shift by full height)
    p = ofcolor(I, EIGHT)
    G = subgrid(p, I)
    h = height(G)
    w = width(G)
    ul = ulcorner(p)
    s = add(ul, astuple(h, ZERO))
    O = crop(I, s, astuple(h, w))
    return O

def dsl4(I):
    # crop the same-sized block diagonally above-left of the 8-rectangle
    p = ofcolor(I, EIGHT)
    G = subgrid(p, I)
    h = height(G)
    w = width(G)
    ul = ulcorner(p)
    s = subtract(ul, astuple(h, w))
    O = crop(I, s, astuple(h, w))
    return O

def dsl5(I):
    # crop the same-sized block immediately to the right of the 8-rectangle
    # implemented by mirroring, cropping left, then mirroring back
    M = hmirror(I)
    p = ofcolor(M, EIGHT)
    G = subgrid(p, M)
    h = height(G)
    w = width(G)
    ul = ulcorner(p)
    s = subtract(ul, astuple(ZERO, w))
    C = crop(M, s, astuple(h, w))
    O = hmirror(C)
    return O
```