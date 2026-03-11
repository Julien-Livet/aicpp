```python
def dsl1(I):
    start = astuple(ZERO, subtract(width(I), SEVEN))
    O = crop(I, start, astuple(height(I), SEVEN))
    return O

def dsl2(I):
    M = vmirror(I)
    part = crop(M, ORIGIN, astuple(height(M), SEVEN))
    O = vmirror(part)
    return O

def dsl3(I):
    h = height(I)
    w = width(I)
    start = astuple(ZERO, subtract(w, SEVEN))
    O = crop(I, start, astuple(h, SEVEN))
    return O

def dsl4(I):
    h = height(I)
    last4 = crop(I, astuple(ZERO, subtract(width(I), FOUR)), astuple(h, FOUR))
    prev3 = crop(I, astuple(ZERO, subtract(width(I), SEVEN)), astuple(h, THREE))
    O = hconcat(prev3, last4)
    return O

def dsl5(I):
    h = height(I)
    step = crop(I, astuple(ZERO, subtract(width(I), EIGHT)), astuple(h, EIGHT))
    O = crop(step, astuple(ZERO, ONE), astuple(h, SEVEN))
    return O
```