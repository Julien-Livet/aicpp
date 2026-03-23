```python
def dsl1(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    inner = delta(p5)
    O0 = underfill(I, TWO, inner)
    top = ulcorner(b)
    leftedge = intersection(inner, vfrontier(top))
    rightedge = intersection(inner, vfrontier(urcorner(b)))
    botedge = intersection(inner, hfrontier(llcorner(b)))
    vproj = intersection(outbox(b), mapply(vfrontier, botedge))
    hproj = intersection(outbox(b), mapply(hfrontier, combine(leftedge, rightedge)))
    ring = combine(vproj, hproj)
    O = underfill(O0, ONE, ring)
    return O

def dsl2(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    O0 = underpaint(I, recolor(TWO, b))
    ring = difference(outbox(b), mapply(neighbors, p5))
    O = underfill(O0, ONE, ring)
    return O

def dsl3(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    inner = delta(p5)
    O0 = underfill(I, TWO, inner)
    projv = intersection(outbox(b), mapply(vfrontier, inner))
    projh = intersection(outbox(b), mapply(hfrontier, inner))
    ring = combine(projv, projh)
    O = underfill(O0, ONE, ring)
    return O

def dsl4(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    cols5 = intersection(b, mapply(vfrontier, p5))
    rows5 = intersection(b, mapply(hfrontier, p5))
    gcols = difference(b, cols5)
    grows = difference(b, rows5)
    belts = combine(gcols, grows)
    O0 = underfill(I, TWO, belts)
    ringv = intersection(outbox(b), mapply(vfrontier, gcols))
    ringh = intersection(outbox(b), mapply(hfrontier, grows))
    ring = combine(ringv, ringh)
    O = underfill(O0, ONE, ring)
    return O

def dsl5(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    cols5 = intersection(b, mapply(vfrontier, p5))
    rows5 = intersection(b, mapply(hfrontier, p5))
    gcols = difference(b, cols5)
    grows = difference(b, rows5)
    belts = combine(gcols, grows)
    O0 = underfill(I, TWO, belts)
    edgebelts = intersection(belts, box(b))
    ring = intersection(outbox(b), mapply(neighbors, edgebelts))
    O = underfill(O0, ONE, ring)
    return O
```