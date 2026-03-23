```python
def dsl1(I):
    # Global lines from the bounding box, subtract lines induced by 5s
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    lb = combine(mapply(hfrontier, b), mapply(vfrontier, b))
    l5 = combine(mapply(hfrontier, p5), mapply(vfrontier, p5))
    axes = difference(lb, l5)
    belts = intersection(b, axes)
    O0 = underfill(I, TWO, belts)
    ring = intersection(outbox(b), axes)
    O = underfill(O0, ONE, ring)
    return O

def dsl2(I):
    # Use background zeros inside the box to induce belts
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    z = ofcolor(I, ZERO)
    zib = intersection(b, z)
    hz = mapply(hfrontier, zib)
    vz = mapply(vfrontier, zib)
    axes = combine(hz, vz)
    belts = intersection(b, axes)
    O0 = underfill(I, TWO, belts)
    ring = intersection(outbox(b), axes)
    O = underfill(O0, ONE, ring)
    return O

def dsl3(I):
    # Axis-wise removal: box-lines minus 5-lines per axis, then combine
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    rb = mapply(hfrontier, b)
    cb = mapply(vfrontier, b)
    r5 = mapply(hfrontier, p5)
    c5 = mapply(vfrontier, p5)
    rbelts = intersection(b, difference(rb, r5))
    cbelts = intersection(b, difference(cb, c5))
    belts = combine(rbelts, cbelts)
    O0 = underfill(I, TWO, belts)
    axes = combine(difference(rb, r5), difference(cb, c5))
    ring = intersection(outbox(b), axes)
    O = underfill(O0, ONE, ring)
    return O

def dsl4(I):
    # Object-extraction: outlines around each 5-object define a grid; filter near-5, then extend to ring via frontiers
    objs = colorfilter(objects(I, T, F, T), FIVE)
    boxes = merge(mapply(box, objs))
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    l5 = combine(mapply(hfrontier, p5), mapply(vfrontier, p5))
    axes = difference(boxes, l5)
    belts = intersection(b, axes)
    O0 = underfill(I, TWO, belts)
    blines = combine(mapply(hfrontier, belts), mapply(vfrontier, belts))
    ring = intersection(outbox(b), blines)
    O = underfill(O0, ONE, ring)
    return O

def dsl5(I):
    # Relational via gap-induced lines from non-5 area inside the box
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    gaps = difference(b, p5)
    hg = mapply(hfrontier, gaps)
    vg = mapply(vfrontier, gaps)
    axes = combine(hg, vg)
    belts = intersection(b, axes)
    O0 = underfill(I, TWO, belts)
    ring = intersection(outbox(b), axes)
    O = underfill(O0, ONE, ring)
    return O
```