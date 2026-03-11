```python
def dsl1(I):
    objs = fgpartition(I)
    rb = rbind(toobject, I)
    co = compose(rb, outbox)
    pick = compose(mostcolor, co)
    add = mapply(fork(recolor, pick, delta), objs)
    O = underpaint(I, add)
    return O

def dsl2(I):
    objs = fgpartition(I)
    rb = rbind(toobject, I)
    co = compose(rb, outbox)
    pick = compose(leastcolor, co)
    add = mapply(fork(recolor, pick, delta), objs)
    O = underpaint(I, add)
    return O

def dsl3(I):
    objs = fgpartition(I)
    add = mapply(fork(recolor, color, delta), objs)
    O = underpaint(I, add)
    return O

def dsl4(I):
    w = width(I)
    start = astuple(ZERO, ZERO)
    dims = astuple(TWO, w)
    band = crop(I, start, dims)
    c = leastcolor(band)
    objs = fgpartition(I)
    add = mapply(compose(lbind(recolor, c), delta), objs)
    O = underpaint(I, add)
    return O

def dsl5(I):
    objs = fgpartition(I)
    rb = rbind(toobject, I)
    co = compose(rb, outbox)
    pick = compose(mostcolor, co)
    add = mapply(fork(recolor, pick, inbox), objs)
    O = underfill(I, add)
    return O
```