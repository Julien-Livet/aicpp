```python
def dsl1(I):
    O = hconcat(I, I)
    return O

def dsl2(I):
    O = rot270(vconcat(rot90(I), rot90(I)))
    return O

def dsl3(I):
    base = hconcat(I, canvas(ZERO, shape(I)))
    objs = fgpartition(I)
    allobj = merge(objs)
    off = tojvec(width(I))
    shifted = shift(allobj, off)
    O = paint(base, shifted)
    return O

def dsl4(I):
    O = vmirror(hconcat(vmirror(I), vmirror(I)))
    return O

def dsl5(I):
    blank = canvas(ZERO, shape(I))
    base = hconcat(blank, blank)
    obj = asobject(I)
    left = paint(base, obj)
    right = paint(left, shift(obj, tojvec(width(I))))
    O = right
    return O
```