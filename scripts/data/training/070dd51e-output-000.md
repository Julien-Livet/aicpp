```python
def dsl1(I):
    colors = remove(ZERO, palette(I))
    pts = apply(lbind(ofcolor, I), colors)
    vsets = sfilter(pts, fork(equality, leftmost, rightmost))
    hsets = sfilter(pts, fork(equality, uppermost, lowermost))
    line = fork(connect, first, last)
    col = compose(color, rbind(toobject, I))
    tint = fork(recolor, col, line)
    vobj = mapply(tint, vsets)
    hobj = mapply(tint, hsets)
    O0 = canvas(ZERO, shape(I))
    O1 = paint(O0, hobj)
    O = paint(O1, vobj)
    return O

def dsl2(I):
    colors = remove(ZERO, palette(I))
    pts = apply(lbind(ofcolor, I), colors)
    vsets = sfilter(pts, fork(equality, leftmost, rightmost))
    hsets = sfilter(pts, fork(equality, uppermost, lowermost))
    col = compose(color, rbind(toobject, I))
    seg = backdrop
    tint = fork(recolor, col, seg)
    vobj = mapply(tint, vsets)
    hobj = mapply(tint, hsets)
    O0 = canvas(ZERO, shape(I))
    O1 = paint(O0, vobj)
    O = underpaint(O1, hobj)
    return O

def dsl3(I):
    colors = remove(ZERO, palette(I))
    pts = apply(lbind(ofcolor, I), colors)
    rects = apply(backdrop, pts)
    vrects = sfilter(rects, vline)
    hrects = sfilter(rects, hline)
    col = compose(color, rbind(toobject, I))
    tint = fork(recolor, col, identity)
    vobj = mapply(tint, vrects)
    hobj = mapply(tint, hrects)
    O0 = canvas(ZERO, shape(I))
    O1 = paint(O0, hobj)
    O = paint(O1, vobj)
    return O

def dsl4(I):
    colors = remove(ZERO, palette(I))
    pts = apply(lbind(ofcolor, I), colors)
    vsets = sfilter(pts, fork(equality, leftmost, rightmost))
    hsets = sfilter(pts, fork(equality, uppermost, lowermost))
    col = compose(color, rbind(toobject, I))
    outline = box
    tint = fork(recolor, col, outline)
    vobj = mapply(tint, vsets)
    hobj = mapply(tint, hsets)
    O0 = canvas(ZERO, shape(I))
    O1 = paint(O0, vobj)
    O = underpaint(O1, hobj)
    return O

def dsl5(I):
    objs = objects(I, T, F, T)
    colors = remove(ZERO, palette(I))
    groups = apply(lbind(colorfilter, objs), colors)
    gather = lbind(mapply, toindices)
    psets = apply(gather, groups)
    vsets = sfilter(psets, fork(equality, leftmost, rightmost))
    hsets = sfilter(psets, fork(equality, uppermost, lowermost))
    line = fork(connect, first, last)
    col = compose(color, rbind(toobject, I))
    tint = fork(recolor, col, line)
    vobj = mapply(tint, vsets)
    hobj = mapply(tint, hsets)
    O0 = canvas(ZERO, shape(I))
    O1 = paint(O0, hobj)
    O = paint(O1, vobj)
    return O
```