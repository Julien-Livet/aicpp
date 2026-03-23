```python
def dsl1(I):
    # O = compress-normalize, compute gravitation, place shifted A back on original base
    J = compress(I)
    v = gravitate(ofcolor(J, TWO), ofcolor(J, FIVE))
    base = replace(I, TWO, SEVEN)
    O = underpaint(base, recolor(TWO, shift(ofcolor(I, TWO), v)))
    return O

def dsl2(I):
    # O = extract objects, align A flush-left to B by extrema, move object
    obs = objects(I, T, F, T)
    Aobj = first(colorfilter(obs, TWO))
    Bobj = first(colorfilter(obs, FIVE))
    Ai = toindices(Aobj)
    Bi = toindices(Bobj)
    dr = subtract(lowermost(Bi), lowermost(Ai))
    dc = subtract(subtract(leftmost(Bi), rightmost(Ai)), ONE)
    v = add(toivec(dr), tojvec(dc))
    base = replace(I, TWO, SEVEN)
    O = move(base, Aobj, v)
    return O

def dsl3(I):
    # O = use B’s bounding-box outline as attractor; underfill shifted A
    A = ofcolor(I, TWO)
    B = ofcolor(I, FIVE)
    v = gravitate(A, box(B))
    base = replace(I, TWO, SEVEN)
    O = underfill(base, TWO, shift(A, v))
    return O

def dsl4(I):
    # O = mirror to canonical pose, gravitate by boxes, unmirror
    R = dmirror(I)
    AR = ofcolor(R, TWO)
    BR = ofcolor(R, FIVE)
    v = gravitate(box(AR), box(BR))
    baseR = replace(R, TWO, SEVEN)
    OR = underpaint(baseR, recolor(TWO, shift(AR, v)))
    O = dmirror(OR)
    return O

def dsl5(I):
    # O = gravitate A’s center-of-mass toward B; underpaint shifted A
    A = ofcolor(I, TWO)
    B = ofcolor(I, FIVE)
    c = centerofmass(A)
    v = gravitate(initset(c), B)
    base = replace(I, TWO, SEVEN)
    O = underpaint(base, recolor(TWO, shift(A, v)))
    return O
```