```python
def dsl1(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    sub = subgrid(p5, I)
    filled_sub = replace(sub, ZERO, TWO)
    obj = asobject(filled_sub)
    top = ulcorner(p5)
    O0 = move(I, obj, top)
    inner = delta(p5)
    edgeinner = intersection(inner, box(b))
    vproj = mapply(vfrontier, edgeinner)
    hproj = mapply(hfrontier, edgeinner)
    proj = combine(vproj, hproj)
    ring = intersection(outbox(b), proj)
    O = underfill(O0, ONE, ring)
    return O

def dsl2(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    inner = delta(p5)
    O0 = fill(I, TWO, inner)
    edgeinner = intersection(inner, box(b))
    touch = mapply(neighbors, edgeinner)
    ring = intersection(outbox(b), touch)
    O = underfill(O0, ONE, ring)
    return O

def dsl3(I):
    p5 = ofcolor(I, FIVE)
    inner = delta(p5)
    O0 = fill(I, TWO, inner)
    twos = ofcolor(O0, TWO)
    b = backdrop(p5)
    touch = mapply(neighbors, twos)
    ring = intersection(outbox(b), touch)
    O = underfill(O0, ONE, ring)
    return O

def dsl4(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    inner = delta(p5)
    edgeinner = intersection(inner, box(b))
    vproj = intersection(outbox(b), mapply(vfrontier, edgeinner))
    hproj = intersection(outbox(b), mapply(hfrontier, edgeinner))
    ring = combine(vproj, hproj)
    obj2 = recolor(TWO, inner)
    obj1 = recolor(ONE, ring)
    O1 = paint(I, obj2)
    O = underpaint(O1, obj1)
    return O

def dsl5(I):
    p5 = ofcolor(I, FIVE)
    b = backdrop(p5)
    hgap = intersection(b, mapply(hfrontier, p5))
    vgap = intersection(b, mapply(vfrontier, p5))
    inner = combine(hgap, vgap)
    O0 = fill(I, TWO, inner)
    edge = intersection(inner, box(b))
    ring = intersection(outbox(b), mapply(neighbors, edge))
    O = underfill(O0, ONE, ring)
    return O
```