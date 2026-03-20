```python
def dsl(I):
    S = ofcolor(I, EIGHT)
    hasR  = intersection(S, shift(S, LEFT))
    has2R = intersection(S, shift(S, add(LEFT, LEFT)))
    hasL  = intersection(S, shift(S, RIGHT))
    has2L = intersection(S, shift(S, add(RIGHT, RIGHT)))
    hasDR = intersection(S, shift(S, add(UP, LEFT)))
    hasUL = intersection(S, shift(S, add(DOWN, RIGHT)))
    hasUR = intersection(S, shift(S, add(DOWN, LEFT)))
    hasDL = intersection(S, shift(S, add(UP, RIGHT)))

    term = difference(S, combine(combine(hasR, has2R), hasDR))

    # seeds for step-1 (contiguous)
    T1  = shift(intersection(term, hasL), RIGHT)
    Td1 = shift(intersection(difference(difference(term, has2L), hasL), difference(hasUL, hasUR)), add(DOWN, RIGHT))

    # seeds for step-2 (checkerboard)
    T2  = shift(intersection(term, has2L), add(RIGHT, RIGHT))
    T2d = shift(intersection(intersection(term, has2L), hasDL), add(DOWN, RIGHT))

    w = width(I)
    ks = interval(ZERO, add(w, ONE), ONE)
    V1 = apply(tojvec, ks)
    V2 = apply(double, V1)

    R1 = mapply(lbind(shift, combine(T1, Td1)), V1)
    R2 = mapply(lbind(shift, combine(T2, T2d)), V2)
    R  = combine(R1, R2)

    O = underfill(I, ONE, R)
    return O
```