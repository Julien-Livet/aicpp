```python
def dsl1(I):
    parts = vsplit(I, THREE)
    O = first(parts)
    return O

def dsl2(I):
    h = height(I)
    w = width(I)
    w3 = divide(w, THREE)
    dims = astuple(h, w3)
    O = crop(I, ORIGIN, dims)
    return O

def dsl3(I):
    parts = vsplit(I, THREE)
    O = extract(parts, identity)
    return O

def dsl4(I):
    x = vmirror(I)
    parts = vsplit(x, THREE)
    p = last(parts)
    O = vmirror(p)
    return O

def dsl5(I):
    parts = vsplit(I, THREE)
    O = first(order(parts, width))
    return O
```