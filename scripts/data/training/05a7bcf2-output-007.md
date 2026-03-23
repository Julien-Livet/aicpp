```python
def dsl1(I):
    E8 = ofcolor(I, EIGHT)
    Rays = merge(apply(rbind(shoot, RIGHT), E8))
    O = underfill(I, EIGHT, Rays)
    return O

def dsl2(I):
    Os = fgpartition(I)
    F4s = colorfilter(Os, FOUR)
    Boxes = merge(apply(inbox, F4s))
    O1 = fill(I, FOUR, Boxes)
    Out = merge(apply(box, F4s))
    O = fill(O1, THREE, Out)
    return O

def dsl3(I):
    O = replace(I, FOUR, ZERO)
    return O

def dsl4(I):
    E8 = ofcolor(I, EIGHT)
    R = merge(apply(rbind(shoot, RIGHT), E8))
    L = merge(apply(rbind(shoot, LEFT), E8))
    HL = combine(R, L)
    O = underfill(I, EIGHT, HL)
    return O

def dsl5(I):
    E8 = ofcolor(I, EIGHT)
    c8 = centerofmass(E8)
    Os = fgpartition(I)
    F4s = colorfilter(Os, FOUR)
    Cs = apply(centerofmass, F4s)
    Lines = merge(prapply(connect, Cs, initset(c8)))
    O = fill(I, EIGHT, Lines)
    return O
```