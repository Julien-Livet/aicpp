```python
def dsl1(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    r5 = mapply(hfrontier, p5)
    c5 = mapply(vfrontier, p5)
    rwo = intersection(b, difference(asindices(I), r5))
    cwo = intersection(b, difference(asindices(I), c5))
    belts = combine(rwo, cwo)
    O0 = underfill(I, TWO, belts)
    ob = outbox(b)
    aligned = combine(mapply(hfrontier, rwo), mapply(vfrontier, cwo))
    ring = intersection(ob, aligned)
    O = underfill(O0, ONE, ring)
    return O

def dsl2(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    r5b = intersection(b, mapply(hfrontier, p5))
    c5b = intersection(b, mapply(vfrontier, p5))
    rbelts = difference(b, r5b)
    cbelts = difference(b, c5b)
    belts = combine(rbelts, cbelts)
    O0 = underfill(I, TWO, belts)
    outside = difference(asindices(I), b)
    rlines = mapply(hfrontier, rbelts)
    clines = mapply(vfrontier, cbelts)
    ring = intersection(outside, combine(rlines, clines))
    O = underfill(O0, ONE, ring)
    return O

def dsl3(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    axes = combine(mapply(hfrontier, p5), mapply(vfrontier, p5))
    seeds = difference(asindices(I), axes)
    lines = combine(mapply(hfrontier, seeds), mapply(vfrontier, seeds))
    belts = intersection(b, lines)
    O0 = underfill(I, TWO, belts)
    ob = outbox(b)
    ring = intersection(ob, lines)
    O = underfill(O0, ONE, ring)
    return O

def dsl4(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    gaps = delta(p5)
    rowcand = difference(mapply(hfrontier, gaps), mapply(hfrontier, p5))
    colcand = difference(mapply(vfrontier, gaps), mapply(vfrontier, p5))
    rbelts = intersection(b, rowcand)
    cbelts = intersection(b, colcand)
    belts = combine(rbelts, cbelts)
    O0 = underfill(I, TWO, belts)
    ob = outbox(b)
    ring = intersection(ob, combine(rowcand, colcand))
    O = underfill(O0, ONE, ring)
    return O

def dsl5(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    O0 = underfill(I, TWO, b)
    t2 = ofcolor(O0, TWO)
    r2 = mapply(hfrontier, t2)
    c2 = mapply(vfrontier, t2)
    r5 = mapply(hfrontier, p5)
    c5 = mapply(vfrontier, p5)
    ronly = difference(r2, r5)
    conly = difference(c2, c5)
    ob = outbox(b)
    ring = intersection(ob, combine(ronly, conly))
    O = underfill(O0, ONE, ring)
    return O
```