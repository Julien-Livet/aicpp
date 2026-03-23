```python
def dsl1(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    gaps = delta(p5)
    O0 = underfill(I, TWO, gaps)
    grows = intersection(b, mapply(hfrontier, gaps))
    gcols = intersection(b, mapply(vfrontier, gaps))
    outside = difference(asindices(I), b)
    ringr = intersection(outside, mapply(hfrontier, grows))
    ringc = intersection(outside, mapply(vfrontier, gcols))
    O = underfill(O0, ONE, combine(ringr, ringc))
    return O

def dsl2(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    pobjs = colorfilter(objects(I, T, F, T), FIVE)
    pidx = merge(apply(toindices, pobjs))
    rows5 = intersection(b, mapply(hfrontier, pidx))
    cols5 = intersection(b, mapply(vfrontier, pidx))
    grows = difference(b, rows5)
    gcols = difference(b, cols5)
    belts = combine(grows, gcols)
    O0 = underfill(I, TWO, belts)
    outside = difference(asindices(I), b)
    ringr = intersection(outside, mapply(hfrontier, grows))
    ringc = intersection(outside, mapply(vfrontier, gcols))
    O = underfill(O0, ONE, combine(ringr, ringc))
    return O

def dsl3(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    belts = difference(b, p5)
    O0 = underfill(I, TWO, belts)
    rows5 = intersection(b, mapply(hfrontier, p5))
    cols5 = intersection(b, mapply(vfrontier, p5))
    grows = difference(b, rows5)
    gcols = difference(b, cols5)
    outside = difference(asindices(I), b)
    ringr = intersection(outside, mapply(hfrontier, grows))
    ringc = intersection(outside, mapply(vfrontier, gcols))
    O = underfill(O0, ONE, combine(ringr, ringc))
    return O

def dsl4(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    belts = difference(b, p5)
    O0 = underfill(I, TWO, belts)
    rows5 = intersection(b, mapply(hfrontier, p5))
    cols5 = intersection(b, mapply(vfrontier, p5))
    grows = difference(b, rows5)
    gcols = difference(b, cols5)
    ob = outbox(b)
    sideband = intersection(ob, mapply(hfrontier, grows))
    topbotband = intersection(ob, mapply(vfrontier, gcols))
    outside = difference(asindices(I), b)
    ringr = intersection(outside, mapply(hfrontier, sideband))
    ringc = intersection(outside, mapply(vfrontier, topbotband))
    O = underfill(O0, ONE, combine(ringr, ringc))
    return O

def dsl5(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    allrows = mapply(hfrontier, b)
    rows5all = mapply(hfrontier, p5)
    grows = intersection(b, difference(allrows, rows5all))
    allcols = mapply(vfrontier, b)
    cols5all = mapply(vfrontier, p5)
    gcols = intersection(b, difference(allcols, cols5all))
    belts = combine(grows, gcols)
    O0 = underfill(I, TWO, belts)
    outside = difference(asindices(I), b)
    ringr = intersection(outside, mapply(hfrontier, grows))
    ringc = intersection(outside, mapply(vfrontier, gcols))
    O = underfill(O0, ONE, combine(ringr, ringc))
    return O
```