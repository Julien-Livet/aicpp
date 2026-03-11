```python
def dsl1(I):
    A = replace(I, ONE, FOUR)
    H = hmirror(A)
    V = vmirror(A)
    R = rot180(A)
    O = I
    O = underpaint(O, asobject(H))
    O = underpaint(O, asobject(V))
    O = underpaint(O, asobject(R))
    return O

def dsl2(I):
    A = replace(I, ONE, FOUR)
    HV = hmirror(vmirror(A))
    O = I
    O = underpaint(O, asobject(hmirror(A)))
    O = underpaint(O, asobject(vmirror(A)))
    O = underpaint(O, asobject(HV))
    return O

def dsl3(I):
    A = replace(I, ONE, FOUR)
    O = I
    O = underpaint(O, asobject(vmirror(A)))
    O = underpaint(O, asobject(hmirror(A)))
    O = underpaint(O, asobject(rot180(A)))
    return O

def dsl4(I):
    dims = shape(I)
    Base = canvas(FOUR, dims)
    A = replace(I, ONE, FOUR)
    O = Base
    O = underpaint(O, asobject(A))
    O = underpaint(O, asobject(hmirror(A)))
    O = underpaint(O, asobject(vmirror(A)))
    O = underpaint(O, asobject(rot180(A)))
    O = fill(O, ONE, ofcolor(I, ONE))
    return O

def dsl5(I):
    # Symmetry closure by repeated underpaint from all three independent reflections
    A = replace(I, ONE, FOUR)
    O = I
    M1 = hmirror(A)
    M2 = vmirror(A)
    M3 = hmirror(vmirror(A))
    O = underpaint(O, asobject(M1))
    O = underpaint(O, asobject(M2))
    O = underpaint(O, asobject(M3))
    return O
```