```python
def dsl1(I):
    RH = asindices(righthalf(I))
    O = underfill(I, EIGHT, RH)
    return O

def dsl2(I):
    Os = fgpartition(I)
    F4s = colorfilter(Os, FOUR)
    BBs = merge(apply(backdrop, F4s))
    O = fill(I, EIGHT, BBs)
    return O

def dsl3(I):
    O = replace(I, FOUR, THREE)
    return O

def dsl4(I):
    J = hmirror(I)
    Obj = asobject(J)
    O = underpaint(I, Obj)
    return O

def dsl5(I):
    E8 = ofcolor(I, EIGHT)
    R = merge(apply(rbind(shoot, RIGHT), E8))
    L = merge(apply(rbind(shoot, LEFT), E8))
    U = merge(apply(rbind(shoot, UP), E8))
    D = merge(apply(rbind(shoot, DOWN), E8))
    Mask = combine(combine(R, L), combine(U, D))
    Obj = recolor(EIGHT, Mask)
    O = underpaint(I, Obj)
    return O
```