```python
def dsl1(I):
    # Per-color union bounding-box fill (underpaint)
    groups = fgpartition(I)
    rects = apply(fork(recolor, color, backdrop), groups)
    merged = merge(rects)
    O = underpaint(I, merged)
    return O

def dsl2(I):
    # Per-color union bounding-box outline (underpaint)
    groups = fgpartition(I)
    outlines = apply(fork(recolor, color, box), groups)
    merged = merge(outlines)
    O = underpaint(I, merged)
    return O

def dsl3(I):
    # Fill global nonzero bounding-box with most frequent nonzero color (preserve existing)
    nz = difference(asindices(I), ofcolor(I, ZERO))
    rect = backdrop(nz)
    obj = toobject(nz, I)
    c = mostcolor(obj)
    O = underfill(I, c, rect)
    return O

def dsl4(I):
    # Per-object bounding-box fill (underpaint)
    comps = objects(I, T, F, T)
    rects = apply(fork(recolor, color, backdrop), comps)
    merged = merge(rects)
    O = underpaint(I, merged)
    return O

def dsl5(I):
    # Per-color union outbox outline (underpaint)
    groups = fgpartition(I)
    outlines = apply(fork(recolor, color, outbox), groups)
    merged = merge(outlines)
    O = underpaint(I, merged)
    return O
```