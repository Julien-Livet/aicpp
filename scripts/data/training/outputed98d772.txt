```python
def dsl1(I):
    A = I
    B = rot270(I)
    C = rot180(I)
    D = rot90(I)
    top = hconcat(A, B)
    bottom = hconcat(C, D)
    O = vconcat(top, bottom)
    return O

def dsl2(I):
    r90 = rot90(I)
    r180 = rot180(I)
    r270 = rot270(I)
    O = vconcat(hconcat(I, r270), hconcat(r180, r90))
    return O

def dsl3(I):
    r90 = rot90(I)
    r180 = rot90(r90)
    r270 = rot90(r180)
    O = vconcat(hconcat(I, r270), hconcat(r180, r90))
    return O

def dsl4(I):
    tl = I
    tr = rot270(I)
    bl = rot180(I)
    br = rot90(I)
    O = vconcat(hconcat(tl, tr), hconcat(bl, br))
    return O
```