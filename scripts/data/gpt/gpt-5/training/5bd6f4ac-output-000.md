```python
def dsl1(I):
    start = astuple(ZERO, subtract(width(I), THREE))
    O = crop(I, start, THREE_BY_THREE)
    return O

def dsl2(I):
    right_third = last(vsplit(I, THREE))
    O = crop(right_third, ORIGIN, THREE_BY_THREE)
    return O

def dsl3(I):
    top_band = first(hsplit(I, THREE))
    O = last(vsplit(top_band, THREE))
    return O

def dsl4(I):
    J = vmirror(I)
    B = crop(J, ORIGIN, THREE_BY_THREE)
    O = vmirror(B)
    return O

def dsl5(I):
    TR = chain(last, rbind(vsplit, THREE), rbind(hsplit, THREE))
    O = TR(I)
    return O
```