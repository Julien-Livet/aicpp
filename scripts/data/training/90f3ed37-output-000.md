```python
def dsl(I):
    # Extract 8-cells
    S = ofcolor(I, EIGHT)
    # Successor directions
    DR = add(DOWN, RIGHT)
    R2 = add(RIGHT, RIGHT)
    # Terminal 8s (no successor in any allowed direction)
    succ = combine(combine(shift(S, RIGHT), shift(S, DR)), shift(S, R2))
    term = difference(S, succ)
    # Previous-step detectors
    P1 = shift(S, LEFT)
    P2 = shift(S, add(LEFT, LEFT))
    Pd = shift(S, add(UP, LEFT))
    Upr = shift(S, add(UP, RIGHT))
    # Tip classes
    tips1 = intersection(term, P1)
    tips2a = difference(intersection(term, P2), P1)
    diagcand = intersection(term, Pd)
    tips2b = intersection(diagcand, Upr)
    tips2 = combine(tips2a, tips2b)
    tipsd = difference(difference(diagcand, Upr), combine(P1, P2))
    # Propagation vectors
    w = width(I)
    ks = interval(ONE, add(w, ONE), ONE)
    V1 = apply(tojvec, ks)                       # (0, k)
    V2 = apply(double, V1)                       # (0, 2k)
    Iv = repeat(toivec(ONE), size(ks))           # (1, 0) repeated
    Vd = mpapply(add, Iv, V1)                    # (1, k)
    # Propagate from tips
    R1 = mapply(lbind(shift, tips1), V1)
    R2 = mapply(lbind(shift, tips2), V2)
    Rd = mapply(lbind(shift, tipsd), Vd)
    prop = combine(combine(R1, R2), Rd)
    # Paint ones on background
    O = underfill(I, ONE, prop)
    return O
```