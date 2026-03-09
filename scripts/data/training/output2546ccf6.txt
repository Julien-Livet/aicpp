```python
def dsl1(I):
    # Shift all non-border content up by one band (block height) and underpaint
    c = mostcolor(I)
    Z = canvas(ZERO, shape(I))
    B = paint(Z, recolor(c, ofcolor(I, c)))
    py = vperiod(asobject(B))
    J = replace(I, c, ZERO)
    NB = asobject(J)
    Z2 = canvas(ZERO, shape(I))
    up = move(Z2, NB, toivec(invert(py)))
    O = underpaint(I, asobject(up))
    return O

def dsl2(I):
    # Shift all non-border content left by one band (block width) and underpaint
    c = mostcolor(I)
    Z = canvas(ZERO, shape(I))
    B = paint(Z, recolor(c, ofcolor(I, c)))
    px = hperiod(asobject(B))
    J = replace(I, c, ZERO)
    NB = asobject(J)
    Z2 = canvas(ZERO, shape(I))
    left = move(Z2, NB, tojvec(invert(px)))
    O = underpaint(I, asobject(left))
    return O

def dsl3(I):
    # Shift all non-border content diagonally up-left by one band in both axes and underpaint
    c = mostcolor(I)
    Z = canvas(ZERO, shape(I))
    B = paint(Z, recolor(c, ofcolor(I, c)))
    px = hperiod(asobject(B))
    py = vperiod(asobject(B))
    J = replace(I, c, ZERO)
    NB = asobject(J)
    Z2 = canvas(ZERO, shape(I))
    off = add(toivec(invert(py)), tojvec(invert(px)))
    diag = move(Z2, NB, off)
    O = underpaint(I, asobject(diag))
    return O

def dsl4(I):
    # Mirror non-border content horizontally and vertically, underpaint both onto original
    c = mostcolor(I)
    J = replace(I, c, ZERO)
    H = hmirror(J)
    V = vmirror(J)
    U = underpaint(I, asobject(H))
    O = underpaint(U, asobject(V))
    return O

def dsl5(I):
    # Rotate non-border content by 180 degrees and underpaint
    c = mostcolor(I)
    J = replace(I, c, ZERO)
    R = rot180(J)
    O = underpaint(I, asobject(R))
    return O
```