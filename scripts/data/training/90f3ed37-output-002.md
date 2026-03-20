```python
def dsl(I):
    S = ofcolor(I, EIGHT)
    # adjacency relations among 8-cells
    hasR  = intersection(S, shift(S, LEFT))                 # 8 with right neighbor
    has2R = intersection(S, shift(S, add(LEFT, LEFT)))      # 8 with two-right neighbor
    hasDR = intersection(S, shift(S, add(UP, LEFT)))        # 8 with down-right neighbor
    hasL  = intersection(S, shift(S, RIGHT))                # 8 with left neighbor
    has2L = intersection(S, shift(S, add(RIGHT, RIGHT)))    # 8 with two-left neighbor
    hasUL = intersection(S, shift(S, add(DOWN, RIGHT)))     # 8 with up-left neighbor
    hasUR = intersection(S, shift(S, add(DOWN, LEFT)))      # 8 with up-right neighbor
    # terminal 8-cells (no right, two-right, or down-right continuation)
    term = difference(S, combine(combine(hasR, has2R), hasDR))
    # seeds: step-1 (same row) and step-1 (next row after diagonal end)
    T1 = shift(intersection(term, hasL), RIGHT)
    Td = shift(intersection(term, hasUL), add(DOWN, RIGHT))
    # seeds: step-2 (same row), from two-left or from checkerboard (up-left and up-right) without left
    last2same = intersection(term, has2L)
    alt2 = intersection(difference(hasUL, hasL), hasUR)
    T2 = shift(combine(last2same, intersection(term, alt2)), add(RIGHT, RIGHT))
    # propagation vectors
    w = width(I)
    ks = interval(ZERO, add(w, ONE), ONE)
    V1 = apply(tojvec, ks)            # (0, k)
    V2 = apply(double, V1)            # (0, 2k)
    R1 = mapply(lbind(shift, combine(T1, Td)), V1)
    R2 = mapply(lbind(shift, T2), V2)
    R = combine(R1, R2)
    O = underfill(I, ONE, R)
    return O
```