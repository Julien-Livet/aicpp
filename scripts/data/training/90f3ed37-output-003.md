```python
def dsl(I):
    S = ofcolor(I, EIGHT)
    # adjacency among 8-cells
    hasR  = intersection(S, shift(S, LEFT))                # immediate right neighbor
    has2R = intersection(S, shift(S, add(LEFT, LEFT)))     # two-right neighbor
    hasL  = intersection(S, shift(S, RIGHT))               # immediate left neighbor
    has2L = intersection(S, shift(S, add(RIGHT, RIGHT)))   # two-left neighbor
    hasDR = intersection(S, shift(S, add(UP, LEFT)))       # down-right neighbor
    hasUL = intersection(S, shift(S, add(DOWN, RIGHT)))    # up-left neighbor

    # terminal 8-cells: no right, no two-right, no down-right
    term = difference(S, combine(combine(hasR, has2R), hasDR))

    # seeds
    T1 = shift(intersection(term, hasL), RIGHT)                                # contiguous run -> start at j+1
    Td = shift(intersection(difference(difference(term, has2L), hasL), hasUL), add(DOWN, RIGHT))  # diagonal end (not checkerboard) -> next row j+1
    T2 = shift(intersection(term, has2L), add(RIGHT, RIGHT))                   # checkerboard run -> start at j+2

    # propagation
    w = width(I)
    ks = interval(ZERO, add(w, ONE), ONE)
    V1 = apply(tojvec, ks)             # (0, k)
    V2 = apply(double, V1)             # (0, 2k)

    R1 = mapply(lbind(shift, combine(T1, Td)), V1)
    R2 = mapply(lbind(shift, T2), V2)
    R  = combine(R1, R2)

    O = underfill(I, ONE, R)
    return O
```