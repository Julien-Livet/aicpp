```python
def dsl1(I):
    # Global normalization via rotation; push 2s onto the 5s’ outbox (one extra step toward ring), then unrotate
    R = rot180(I)
    A = ofcolor(R, TWO)
    B = ofcolor(R, FIVE)
    ring = outbox(B)
    v = gravitate(A, ring)
    u = sign(position(A, ring))
    d = add(v, u)
    base = replace(R, TWO, SEVEN)
    R2 = underfill(base, TWO, shift(A, d))
    O = rot180(R2)
    return O

def dsl2(I):
    # Object extraction; move the 2-object onto the outbox of the 5-object (overshoot by one toward ring)
    obs = objects(I, T, F, T)
    Aobj = first(colorfilter(obs, TWO))
    Bobj = first(colorfilter(obs, FIVE))
    A = toindices(Aobj)
    ring = outbox(Bobj)
    v = gravitate(A, ring)
    u = sign(position(A, ring))
    d = add(v, u)
    base = replace(I, TWO, SEVEN)
    O = underfill(base, TWO, shift(A, d))
    return O

def dsl3(I):
    # Color filtering; land the 2s exactly on the 5s’ outbox by adjacency + one step toward the ring
    A = ofcolor(I, TWO)
    B = ofcolor(I, FIVE)
    ring = outbox(B)
    v = gravitate(A, ring)
    u = sign(position(A, ring))
    d = add(v, u)
    base = replace(I, TWO, SEVEN)
    O = underfill(base, TWO, shift(A, d))
    return O

def dsl4(I):
    # Geometric: align via boxes and steer by centers; overshoot onto the outbox
    A = ofcolor(I, TWO)
    B = ofcolor(I, FIVE)
    ring = outbox(B)
    v = gravitate(box(A), ring)
    u = sign(position(initset(center(A)), initset(center(B))))
    d = add(v, u)
    base = replace(I, TWO, SEVEN)
    O = underfill(base, TWO, shift(A, d))
    return O

def dsl5(I):
    # Relational/structural: use full bounding regions; move A’s backdrop onto B’s outbox, with one-step overshoot
    A = ofcolor(I, TWO)
    B = ofcolor(I, FIVE)
    ring = outbox(B)
    v = gravitate(backdrop(A), ring)
    u = sign(position(backdrop(A), ring))
    d = add(v, u)
    base = replace(I, TWO, SEVEN)
    O = underfill(base, TWO, shift(A, d))
    return O
```