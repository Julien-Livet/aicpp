```python
def dsl1(I):
    # Fill 9-cells using values from the vertically mirrored grid at the same positions
    m = ofcolor(I, NINE)
    base = cover(I, m)
    J = vmirror(I)
    obj = toobject(m, J)
    O = underpaint(base, obj)
    return O

def dsl2(I):
    # Fill 9-cells using values from the 180-rotated grid at the same positions
    m = ofcolor(I, NINE)
    base = cover(I, m)
    J = rot180(I)
    obj = toobject(m, J)
    O = underpaint(base, obj)
    return O

def dsl3(I):
    # Propagate values into 9-cells: first from below, then from the right
    m = ofcolor(I, NINE)
    base = cover(I, m)
    src = shift(m, DOWN)
    obj = toobject(src, I)
    O1 = move(base, obj, UP)
    m2 = ofcolor(O1, NINE)
    base2 = cover(O1, m2)
    src2 = shift(m2, RIGHT)
    obj2 = toobject(src2, O1)
    O = move(base2, obj2, LEFT)
    return O

def dsl4(I):
    # Two-step fill: first from rot90, then from rot270 for any remaining 9s
    m = ofcolor(I, NINE)
    base = cover(I, m)
    J1 = rot90(I)
    obj1 = toobject(m, J1)
    O1 = underpaint(base, obj1)
    m2 = ofcolor(O1, NINE)
    base2 = cover(O1, m2)
    J2 = rot270(I)
    obj2 = toobject(m2, J2)
    O = underpaint(base2, obj2)
    return O

def dsl5(I):
    # Diagonal borrowing: first from up-right, then from down-left for remaining 9s
    m = ofcolor(I, NINE)
    base = cover(I, m)
    src1 = shift(m, UP_RIGHT)
    obj1 = toobject(src1, I)
    O1 = move(base, obj1, DOWN_LEFT)
    m2 = ofcolor(O1, NINE)
    base2 = cover(O1, m2)
    src2 = shift(m2, DOWN_LEFT)
    obj2 = toobject(src2, O1)
    O = move(base2, obj2, UP_RIGHT)
    return O
```