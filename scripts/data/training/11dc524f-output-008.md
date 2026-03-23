```python
def dsl1(I):
    # Global normalization via rotation; gravitate A onto B, then unrotate
    R = rot90(I)
    A = ofcolor(R, TWO)
    B = ofcolor(R, FIVE)
    d = gravitate(A, B)
    base = replace(R, TWO, SEVEN)
    R2 = underfill(base, TWO, shift(A, d))
    O = rot270(R2)
    return O

def dsl2(I):
    # Object extraction; gravitate the 2-object onto the 5-object
    obs = objects(I, T, F, T)
    Aobj = first(colorfilter(obs, TWO))
    Bobj = first(colorfilter(obs, FIVE))
    A = toindices(Aobj)
    d = gravitate(Aobj, Bobj)
    base = replace(I, TWO, SEVEN)
    O = underfill(base, TWO, shift(A, d))
    return O

def dsl3(I):
    # Color filtering; move A adjacent to B and underpaint
    A = ofcolor(I, TWO)
    B = ofcolor(I, FIVE)
    d = gravitate(A, B)
    base = replace(I, TWO, SEVEN)
    O = underpaint(base, recolor(TWO, shift(A, d)))
    return O

def dsl4(I):
    # Geometric: steer by bounding boxes; move A by box-to-box gravitation and place by move
    A = ofcolor(I, TWO)
    B = ofcolor(I, FIVE)
    v = gravitate(box(A), box(B))
    base = replace(I, TWO, SEVEN)
    Aobj = toobject(A, I)
    O = move(base, Aobj, v)
    return O

def dsl5(I):
    # Relational/structural: use A’s backdrop to compute approach vector; paint shifted A beneath existing content
    A = ofcolor(I, TWO)
    B = ofcolor(I, FIVE)
    v = gravitate(backdrop(A), B)
    base = replace(I, TWO, SEVEN)
    O = underpaint(base, recolor(TWO, shift(A, v)))
    return O
```