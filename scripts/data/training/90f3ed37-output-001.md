```python
def dsl(I):
    # Extract 8-cells
    S = ofcolor(I, EIGHT)
    # Predecessor detectors
    P1 = shift(S, LEFT)                  # has 8 immediately to the left
    P2 = shift(S, add(LEFT, LEFT))       # has 8 two to the left
    Pd = shift(S, add(UP, LEFT))         # has 8 up-left
    Upr = shift(S, add(UP, RIGHT))       # has 8 up-right
    # True terminal 8s: no successor to right, down-right, or two-right
    term = difference(S, combine(combine(P1, Pd), P2))
    # Tip classes
    tips1 = intersection(term, P1)                                   # extend by step 1 on same row
    tips2 = combine(difference(intersection(term, P2), P1),          # extend by step 2 on same row
                    intersection(intersection(term, Pd), Upr))
    tipsd = difference(difference(intersection(term, Pd), Upr),      # extend by step 1 on next row
                       combine(P1, P2))
    # Propagation vectors
    w = width(I)
    ks = interval(ONE, add(w, ONE), ONE)
    V1 = apply(tojvec, ks)                       # (0, k)
    V2 = apply(double, V1)                       # (0, 2k)
    Iv = repeat(toivec(ONE), size(ks))           # (1, 0) repeated
    Vb = mpapply(add, Iv, V1)                    # (1, k)
    # Propagate from tips
    R = combine(combine(mapply(lbind(shift, tips1), V1),
                        mapply(lbind(shift, tips2), V2)),
                mapply(lbind(shift, tipsd), Vb))
    # Paint ones on background
    O = underfill(I, ONE, R)
    return O
```