```python
def dsl1(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    gaps = delta(p5)
    O0 = underfill(I, TWO, gaps)
    outside = difference(asindices(I), b)
    lines = combine(mapply(hfrontier, gaps), mapply(vfrontier, gaps))
    ring = intersection(outside, lines)
    O = underfill(O0, ONE, ring)
    return O

def dsl2(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    z = ofcolor(I, ZERO)
    belts = intersection(z, b)
    O0 = fill(I, TWO, belts)
    lines = combine(mapply(hfrontier, belts), mapply(vfrontier, belts))
    outside = difference(asindices(I), b)
    ring = intersection(outside, lines)
    O = underfill(O0, ONE, ring)
    return O

def dsl3(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    O0 = underfill(I, TWO, b)
    t = ofcolor(O0, TWO)
    outside = difference(asindices(I), b)
    ring = intersection(outside, combine(mapply(hfrontier, t), mapply(vfrontier, t)))
    O = underfill(O0, ONE, ring)
    return O

def dsl4(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    gaps = delta(p5)
    belts = intersection(b, gaps)
    O0 = underfill(I, TWO, belts)
    ob = outbox(b)
    aligned = combine(mapply(hfrontier, belts), mapply(vfrontier, belts))
    ring = intersection(ob, aligned)
    O = underfill(O0, ONE, ring)
    return O

def dsl5(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    belts = difference(b, p5)
    axes = combine(mapply(hfrontier, belts), mapply(vfrontier, belts))
    inner = intersection(b, axes)
    O0 = underfill(I, TWO, inner)
    outside = difference(asindices(I), b)
    ring = intersection(outside, axes)
    O = underfill(O0, ONE, ring)
    return O
```