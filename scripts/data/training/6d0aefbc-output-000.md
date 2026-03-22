```python
def dsl1(I):
    O = hconcat(I, vmirror(I))
    return O

def dsl2(I):
    dims = shape(I)
    obj = asobject(I)
    left = paint(canvas(ZERO, dims), obj)
    right = paint(canvas(ZERO, dims), vmirror(obj))
    O = hconcat(left, right)
    return O

def dsl3(I):
    c = mostcolor(I)
    J = switch(I, c, c)
    O = hconcat(J, vmirror(J))
    return O

def dsl4(I):
    R = rot270(hmirror(rot90(I)))
    O = hconcat(I, R)
    return O

def dsl5(I):
    w = width(I)
    h = height(I)
    outdims = astuple(h, add(w, w))
    base = canvas(ZERO, outdims)
    obj = asobject(I)
    right = shift(vmirror(obj), tojvec(w))
    O = paint(paint(base, obj), right)
    return O
```