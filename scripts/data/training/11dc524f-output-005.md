```python
def dsl1(I):
    # Global symmetry: compute in vertically mirrored space, then unmirror
    V = vmirror(I)
    A = ofcolor(V, TWO)
    B = ofcolor(V, FIVE)
    d = gravitate(A, B)
    base = replace(V, TWO, SEVEN)
    V2 = underfill(base, TWO, shift(A, d))
    O = vmirror(V2)
    return O

def dsl2(I):
    # Object extraction: move the 2-object to the outline (box) of the 5-object
    A = ofcolor(I, TWO)
    B = ofcolor(I, FIVE)
    d = gravitate(A, box(B))
    base = replace(I, TWO, SEVEN)
    O = underfill(base, TWO, shift(A, d))
    return O

def dsl3(I):
    # Color filtering with a point anchor: move the center of 2s toward the 5s’ outline
    A = ofcolor(I, TWO)
    B = ofcolor(I, FIVE)
    ca = center(A)
    src = initset(ca)
    d = gravitate(src, box(B))
    base = replace(I, TWO, SEVEN)
    O = underfill(base, TWO, shift(A, d))
    return O

def dsl4(I):
    # Geometric ray casting: shoot from center of 2s in coarse direction toward 5s and land on their box
    A = ofcolor(I, TWO)
    B = ofcolor(I, FIVE)
    ca = center(A)
    dir = position(A, B)
    ray = shoot(ca, dir)
    tgt = intersection(ray, box(B))
    d = gravitate(A, tgt)
    base = replace(I, TWO, SEVEN)
    O = underfill(base, TWO, shift(A, d))
    return O

def dsl5(I):
    # Relational reasoning: move nearest corner of 2s to touch the 5s’ outline
    A = ofcolor(I, TWO)
    B = ofcolor(I, FIVE)
    d = gravitate(corners(A), box(B))
    base = replace(I, TWO, SEVEN)
    O = underfill(base, TWO, shift(A, d))
    return O
```