```python
def dsl1(I):
    # Global rotation normalization: solve in rot90 space then unrotate
    R = rot90(I)
    A = ofcolor(R, TWO)
    B = ofcolor(R, FIVE)
    d = gravitate(A, outbox(B))
    base = replace(R, TWO, SEVEN)
    R2 = underfill(base, TWO, shift(A, d))
    O = rot270(R2)
    return O

def dsl2(I):
    # Object extraction: detect colored objects, then move the 2-object toward the 5-object’s outline
    obs = objects(I, T, F, T)
    Aobj = first(colorfilter(obs, TWO))
    Bobj = first(colorfilter(obs, FIVE))
    A = toindices(Aobj)
    d = gravitate(A, box(Bobj))
    base = replace(I, TWO, SEVEN)
    O = underfill(base, TWO, shift(A, d))
    return O

def dsl3(I):
    # Color filtering: move the 2s to the outbox (one-pixel ring) surrounding the 5s
    A = ofcolor(I, TWO)
    B = ofcolor(I, FIVE)
    d = gravitate(A, outbox(B))
    base = replace(I, TWO, SEVEN)
    O = underfill(base, TWO, shift(A, d))
    return O

def dsl4(I):
    # Geometric ray casting with robust direction: shoot from 2s’ center toward 5s and land on their outbox
    A = ofcolor(I, TWO)
    B = ofcolor(I, FIVE)
    ca = center(A)
    cb = center(B)
    src = initset(ca)
    dst = initset(cb)
    dir = sign(position(src, dst))
    ray = shoot(ca, dir)
    tgt = intersection(ray, outbox(B))
    d = gravitate(A, tgt)
    base = replace(I, TWO, SEVEN)
    O = underfill(base, TWO, shift(A, d))
    return O

def dsl5(I):
    # Relational/structural: align the box of 2s to touch the 5s directly
    A = ofcolor(I, TWO)
    B = ofcolor(I, FIVE)
    d = gravitate(box(A), B)
    base = replace(I, TWO, SEVEN)
    O = underfill(base, TWO, shift(A, d))
    return O
```