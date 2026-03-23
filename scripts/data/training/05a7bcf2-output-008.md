```python
def dsl1(I):
    E8 = ofcolor(I, EIGHT)
    Box = inbox(E8)
    O = fill(I, EIGHT, Box)
    return O

def dsl2(I):
    E4 = ofcolor(I, FOUR)
    Rays = merge(apply(rbind(shoot, RIGHT), E4))
    O = underfill(I, EIGHT, Rays)
    return O

def dsl3(I):
    Os = fgpartition(I)
    F4s = colorfilter(Os, FOUR)
    Border = merge(apply(box, F4s))
    O = fill(I, THREE, Border)
    return O

def dsl4(I):
    J = vmirror(I)
    Obj = asobject(J)
    O = underpaint(I, Obj)
    return O

def dsl5(I):
    E8 = ofcolor(I, EIGHT)
    R = merge(apply(rbind(shoot, RIGHT), E8))
    L = merge(apply(rbind(shoot, LEFT), E8))
    HL = combine(R, L)
    F4 = ofcolor(I, FOUR)
    Rows = merge(apply(hfrontier, F4))
    Mask = intersection(HL, Rows)
    O = underfill(I, EIGHT, Mask)
    return O
```