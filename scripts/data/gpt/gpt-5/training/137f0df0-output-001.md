```python
def dsl1(I):
    p5 = ofcolor(I, FIVE)
    inner = delta(p5)
    O0 = fill(I, TWO, inner)
    nbr = mapply(neighbors, inner)
    ring = difference(nbr, backdrop(p5))
    O = underfill(O0, ONE, ring)
    return O

def dsl2(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    inner = difference(b, p5)
    O0 = fill(I, TWO, inner)
    touch = mapply(neighbors, inner)
    ringall = outbox(b)
    ring = intersection(ringall, touch)
    O = underfill(O0, ONE, ring)
    return O

def dsl3(I):
    p5 = ofcolor(I, FIVE)
    sub = subgrid(p5, I)
    sub2 = replace(sub, ZERO, TWO)
    obj = asobject(sub2)
    top = ulcorner(p5)
    O0 = move(I, obj, top)
    inner = delta(p5)
    touch = mapply(neighbors, inner)
    ring = difference(touch, backdrop(p5))
    O = underfill(O0, ONE, ring)
    return O

def dsl4(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    inner = delta(p5)
    obj2 = recolor(TWO, inner)
    touch = mapply(neighbors, inner)
    ring = intersection(outbox(b), touch)
    obj1 = recolor(ONE, ring)
    O1 = paint(I, obj2)
    O = underpaint(O1, obj1)
    return O

def dsl5(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    inner = delta(p5)
    ring = outbox(b)
    vproj = intersection(ring, mapply(vfrontier, inner))
    hproj = intersection(ring, mapply(hfrontier, inner))
    out = combine(vproj, hproj)
    O0 = fill(I, TWO, inner)
    O = underfill(O0, ONE, out)
    return O
```