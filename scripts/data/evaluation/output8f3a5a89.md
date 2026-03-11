```python
def dsl1(I):
    # Outline the 6-connected background (8) region: frontiers within that region + its grid-border part
    comps = partition(I)
    bg8 = colorfilter(comps, EIGHT)
    sixobj = toobject(ofcolor(I, SIX), I)
    tgt = extract(bg8, rbind(adjacent, sixobj))  # the 8-component adjacent to the 6
    frs = frontiers(I)
    fobj = merge(frs)
    fidx = toindices(fobj)
    tidx = toindices(tgt)
    b1 = intersection(fidx, tidx)                # internal boundary (adjacent to non-8) within the target region
    b2 = intersection(box(tgt), tidx)            # add the part of region lying on the grid border
    b = combine(b1, b2)
    obj = recolor(SEVEN, toobject(b, I))
    O = underpaint(I, obj)
    return O

def dsl2(I):
    # Same intent as dsl1 but compute adjacency to non-background via shifts of all non-bg objects
    tgt = extract(colorfilter(partition(I), EIGHT), rbind(adjacent, toobject(ofcolor(I, SIX), I)))
    objs = objects(I, T, F, T)  # all non-background objects
    upn = mapply(rbind(shift, UP), objs)
    dnn = mapply(rbind(shift, DOWN), objs)
    lfn = mapply(rbind(shift, LEFT), objs)
    rgn = mapply(rbind(shift, RIGHT), objs)
    adjpatch = combine(combine(upn, dnn), combine(lfn, rgn))
    adjidx = toindices(adjpatch)
    tidx = toindices(tgt)
    b1 = intersection(adjidx, tidx)              # 8-cells in tgt adjacent to any non-bg
    b2 = intersection(box(tgt), tidx)            # include grid-border part of tgt
    b = combine(b1, b2)
    obj = recolor(SEVEN, toobject(b, I))
    O = underpaint(I, obj)
    return O

def dsl3(I):
    # Only draw the bounding-box outline of the 6-connected 8-region
    comps = partition(I)
    bg8 = colorfilter(comps, EIGHT)
    sixobj = toobject(ofcolor(I, SIX), I)
    tgt = extract(bg8, rbind(adjacent, sixobj))
    tidx = toindices(tgt)
    b = intersection(box(tgt), tidx)
    obj = recolor(SEVEN, toobject(b, I))
    O = underpaint(I, obj)
    return O

def dsl4(I):
    # Use neighbors of 1's but restrict to the 6-connected 8-region; plus grid-border of that region
    tgt = extract(colorfilter(partition(I), EIGHT), rbind(adjacent, toobject(ofcolor(I, SIX), I)))
    ones = ofcolor(I, ONE)
    n1 = combine(combine(shift(ones, UP), shift(ones, DOWN)),
                 combine(shift(ones, LEFT), shift(ones, RIGHT)))
    tidx = toindices(tgt)
    b1 = intersection(toindices(n1), tidx)
    b2 = intersection(box(tgt), tidx)
    b = combine(b1, b2)
    obj = recolor(SEVEN, toobject(b, I))
    O = underpaint(I, obj)
    return O

def dsl5(I):
    # Variant: union of (neighbors of all non-bg within tgt) and (tgt on grid border) and (neighbors of 6 within tgt)
    tgt = extract(colorfilter(partition(I), EIGHT), rbind(adjacent, toobject(ofcolor(I, SIX), I)))
    objs = objects(I, T, F, T)
    upn = mapply(rbind(shift, UP), objs)
    dnn = mapply(rbind(shift, DOWN), objs)
    lfn = mapply(rbind(shift, LEFT), objs)
    rgn = mapply(rbind(shift, RIGHT), objs)
    adj_nonbg = combine(combine(upn, dnn), combine(lfn, rgn))
    sixn = combine(combine(shift(ofcolor(I, SIX), UP), shift(ofcolor(I, SIX), DOWN)),
                   combine(shift(ofcolor(I, SIX), LEFT), shift(ofcolor(I, SIX), RIGHT)))
    tidx = toindices(tgt)
    b_nonbg = intersection(toindices(adj_nonbg), tidx)
    b_six = intersection(toindices(sixn), tidx)
    b_box = intersection(box(tgt), tidx)
    b = combine(combine(b_nonbg, b_six), b_box)
    obj = recolor(SEVEN, toobject(b, I))
    O = underpaint(I, obj)
    return O
```