```python
def dsl1(I):
    E = ofcolor(I, EIGHT)
    c8 = centerofmass(E)
    R = shoot(c8, RIGHT)
    B = inbox(R)
    O = underfill(I, EIGHT, B)
    return O

def dsl2(I):
    Os = fgpartition(I)
    F4s = colorfilter(Os, FOUR)
    Outlines = apply(box, F4s)
    P = merge(Outlines)
    O = fill(I, THREE, P)
    return O

def dsl3(I):
    O = replace(I, FOUR, THREE)
    return O

def dsl4(I):
    Ih = hmirror(I)
    Iv = vmirror(I)
    Eh = ofcolor(Ih, EIGHT)
    Ev = ofcolor(Iv, EIGHT)
    U = combine(Eh, Ev)
    Obj = recolor(EIGHT, U)
    O = underpaint(I, Obj)
    return O

def dsl5(I):
    E8 = ofcolor(I, EIGHT)
    c8 = centerofmass(E8)
    Os = fgpartition(I)
    F4s = colorfilter(Os, FOUR)
    Cs = apply(centerofmass, F4s)
    Lines = merge(prapply(connect, Cs, initset(c8)))
    O = fill(I, THREE, Lines)
    return O
```