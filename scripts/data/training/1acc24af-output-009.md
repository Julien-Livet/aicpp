```python
def dsl1(I):
    # Global: keep 5s only on the vertical frontier through the center of the 5s' bounding box
    S = ofcolor(I, FIVE)
    col = vfrontier(center(S))
    keep = intersection(S, col)
    O = paint(replace(I, FIVE, TWO), toobject(keep, I))
    return O

def dsl2(I):
    # Object extraction: choose the top 1-object whose bbox vertical projection overlaps the 5s most; keep only that overlap
    top = tophalf(I)
    ones = colorfilter(objects(top, T, F, T), ONE)
    S = ofcolor(I, FIVE)
    projs = apply(compose(lbind(mapply, rbind(shoot, DOWN)), compose(backdrop, toindices)), ones)
    best = argmax(projs, compose(size, rbind(intersection, S)))
    keep = intersection(S, best)
    O = paint(replace(I, FIVE, TWO), toobject(keep, I))
    return O

def dsl3(I):
    # Color filtering: keep 5s in columns that contain 1s on the lowermost row of the top half
    P = ofcolor(tophalf(I), ONE)
    r = lowermost(P)
    base_row = hfrontier(astuple(r, ZERO))
    anchors = intersection(P, base_row)
    cols = merge(apply(vfrontier, anchors))
    keep = intersection(ofcolor(I, FIVE), cols)
    O = paint(replace(I, FIVE, TWO), toobject(keep, I))
    return O

def dsl4(I):
    # Geometric: keep 5s only on the densest 5-column (max overlap of a vertical frontier with the 5s)
    S = ofcolor(I, FIVE)
    lines = apply(vfrontier, S)
    best = argmax(lines, compose(size, rbind(intersection, S)))
    keep = intersection(S, best)
    O = paint(replace(I, FIVE, TWO), toobject(keep, I))
    return O

def dsl5(I):
    # Relational: keep 5s only on the vertical frontier through the center of the top-half 1s' bounding box
    P = ofcolor(tophalf(I), ONE)
    col = vfrontier(center(P))
    keep = intersection(ofcolor(I, FIVE), col)
    O = paint(replace(I, FIVE, TWO), toobject(keep, I))
    return O
```