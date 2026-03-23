```python
def dsl1(I):
    p5 = ofcolor(I, FIVE)
    O = fill(I, TWO, delta(p5))
    return O

def dsl2(I):
    p5 = ofcolor(I, FIVE)
    rect = backdrop(p5)
    O0 = underfill(I, TWO, rect)
    ring = outbox(rect)
    O = underfill(O0, ONE, ring)
    return O

def dsl3(I):
    p5 = ofcolor(I, FIVE)
    inner = delta(p5)
    obj2 = recolor(TWO, inner)
    O = paint(I, obj2)
    return O

def dsl4(I):
    p5 = ofcolor(I, FIVE)
    sub = subgrid(p5, I)
    sub2 = replace(sub, ZERO, TWO)
    obj = asobject(sub2)
    top = ulcorner(p5)
    O = move(I, obj, top)
    return O

def dsl5(I):
    p5 = ofcolor(I, FIVE)
    inner = delta(p5)
    cols = mapply(vfrontier, inner)
    outside = difference(cols, backdrop(p5))
    O0 = fill(I, TWO, inner)
    O = fill(O0, ONE, outside)
    return O
```