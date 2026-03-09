```python
def dsl1(I):
    O = vmirror(I)
    return O

def dsl2(I):
    O = rot90(I)
    return O

def dsl3(I):
    O = rot270(I)
    return O

def dsl4(I):
    O = rot180(I)
    return O

def dsl5(I):
    h = height(I)
    w = width(I)
    all_idx = asindices(I)
    bg_idx = ofcolor(I, ZERO)
    fg_idx = difference(all_idx, bg_idx)
    obj = toobject(fg_idx, I)
    r = rightmost(fg_idx)
    dx = subtract(subtract(w, ONE), r)
    O = move(canvas(ZERO, astuple(h, w)), obj, astuple(0, dx))
    return O
```