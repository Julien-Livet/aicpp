```python
def dsl1(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    O0 = underpaint(I, recolor(TWO, b))
    rows5 = intersection(b, mapply(hfrontier, p5))
    cols5 = intersection(b, mapply(vfrontier, p5))
    grows = difference(b, rows5)
    gcols = difference(b, cols5)
    outside = difference(asindices(I), b)
    ringr = intersection(outside, mapply(hfrontier, grows))
    ringc = intersection(outside, mapply(vfrontier, gcols))
    ring = combine(ringr, ringc)
    O = underfill(O0, ONE, ring)
    return O

def dsl2(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    pobjs = colorfilter(objects(I, T, F, T), FIVE)
    rows5 = intersection(b, mapply(hfrontier, pobjs))
    cols5 = intersection(b, mapply(vfrontier, pobjs))
    grows = difference(b, rows5)
    gcols = difference(b, cols5)
    belts = combine(grows, gcols)
    O0 = underfill(I, TWO, belts)
    outside = difference(asindices(I), b)
    ringr = intersection(outside, mapply(hfrontier, grows))
    ringc = intersection(outside, mapply(vfrontier, gcols))
    ring = combine(ringr, ringc)
    O = underfill(O0, ONE, ring)
    return O

def dsl3(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    z = intersection(b, ofcolor(I, ZERO))
    rowsz = intersection(b, mapply(hfrontier, z))
    colsz = intersection(b, mapply(vfrontier, z))
    rows5 = intersection(b, mapply(hfrontier, p5))
    cols5 = intersection(b, mapply(vfrontier, p5))
    grows = difference(rowsz, rows5)
    gcols = difference(colsz, cols5)
    belts = combine(grows, gcols)
    O0 = underfill(I, TWO, belts)
    outside = difference(asindices(I), b)
    ringr = intersection(outside, mapply(hfrontier, grows))
    ringc = intersection(outside, mapply(vfrontier, gcols))
    ring = combine(ringr, ringc)
    O = underfill(O0, ONE, ring)
    return O

def dsl4(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    rows5 = intersection(b, mapply(hfrontier, p5))
    cols5 = intersection(b, mapply(vfrontier, p5))
    grows = difference(b, rows5)
    gcols = difference(b, cols5)
    belts = combine(grows, gcols)
    O0 = underfill(I, TWO, belts)
    outside_rows = difference(mapply(hfrontier, b), b)
    outside_cols = difference(mapply(vfrontier, b), b)
    ringr = intersection(outside_rows, mapply(hfrontier, grows))
    ringc = intersection(outside_cols, mapply(vfrontier, gcols))
    ring = combine(ringr, ringc)
    O = underfill(O0, ONE, ring)
    return O

def dsl5(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    d = delta(p5)
    O0 = underfill(I, TWO, d)
    outside = difference(asindices(I), b)
    gaprows = difference(b, intersection(b, mapply(hfrontier, p5)))
    gapcols = difference(b, intersection(b, mapply(vfrontier, p5)))
    ringr = intersection(outside, mapply(hfrontier, gaprows))
    ringc = intersection(outside, mapply(vfrontier, gapcols))
    ring = combine(ringr, ringc)
    O = underfill(O0, ONE, ring)
    return O
```