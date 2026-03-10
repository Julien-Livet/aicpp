```python
def dsl1(I):
    a = vmirror(I)
    b = hmirror(I)
    c = rot180(I)
    top = hconcat(I, a)
    bottom = hconcat(b, c)
    O = vconcat(top, bottom)
    return O

def dsl2(I):
    top = hconcat(I, vmirror(I))
    bottom = rot180(top)
    O = vconcat(top, bottom)
    return O

def dsl3(I):
    left = vconcat(I, hmirror(I))
    right = vmirror(left)
    O = hconcat(left, right)
    return O

def dsl4(I):
    right = vmirror(I)
    bottomleft = rot180(right)
    bottomright = rot180(I)
    top = hconcat(I, right)
    bottom = hconcat(bottomleft, bottomright)
    O = vconcat(top, bottom)
    return O

def dsl5(I):
    rightcol = vconcat(vmirror(I), rot180(I))
    leftcol = vmirror(rightcol)
    O = hconcat(leftcol, rightcol)
    return O
```