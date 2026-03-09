```python
def dsl1(I):
    # Decide orientation by row/column overlap, then bridge with 1-cell margin on the overlap axis.
    obs = objects(I, T, F, T)
    a = argmin(obs, leftmost)
    b = other(obs, a)
    side = both(hmatching(a, b), flip(vmatching(a, b)))  # side-by-side if rows overlap but columns don't
    if side:
        lefto = a
        righto = b
        topov = branch(greater(uppermost(lefto), uppermost(righto)), uppermost(lefto), uppermost(righto))
        botov = branch(greater(lowermost(lefto), lowermost(righto)), lowermost(righto), lowermost(lefto))
        i0 = increment(topov)
        i1 = decrement(botov)
        j0 = increment(rightmost(lefto))
        j1 = decrement(leftmost(righto))
    else:
        topo = argmin(obs, uppermost)
        boto = other(obs, topo)
        leftov = branch(greater(leftmost(topo), leftmost(boto)), leftmost(topo), leftmost(boto))
        rightov = branch(greater(rightmost(topo), rightmost(boto)), rightmost(boto), rightmost(topo))
        j0 = increment(leftov)
        j1 = decrement(rightov)
        i0 = increment(lowermost(topo))
        i1 = decrement(uppermost(boto))
    rect = backdrop(connect(astuple(i0, j0), astuple(i1, j1)))
    O = underfill(I, EIGHT, rect)
    return O

def dsl2(I):
    # Build both candidates and choose the one that neither overlaps nor touches the given objects.
    obs = objects(I, T, F, T)
    lefto = argmin(obs, leftmost)
    righto = other(obs, lefto)
    topo = argmin(obs, uppermost)
    boto = other(obs, topo)
    # side-by-side candidate
    su = branch(greater(uppermost(lefto), uppermost(righto)), uppermost(lefto), uppermost(righto))
    sl = branch(greater(lowermost(lefto), lowermost(righto)), lowermost(righto), lowermost(lefto))
    si0 = increment(su)
    si1 = decrement(sl)
    sj0 = increment(rightmost(lefto))
    sj1 = decrement(leftmost(righto))
    srect = backdrop(connect(astuple(si0, sj0), astuple(si1, sj1)))
    # stacked candidate
    vl = branch(greater(leftmost(topo), leftmost(boto)), leftmost(topo), leftmost(boto))
    vr = branch(greater(rightmost(topo), rightmost(boto)), rightmost(boto), rightmost(topo))
    vi0 = increment(lowermost(topo))
    vi1 = decrement(uppermost(boto))
    vj0 = increment(vl)
    vj1 = decrement(vr)
    vrect = backdrop(connect(astuple(vi0, vj0), astuple(vi1, vj1)))
    # choose the clear (no overlap, no adjacency) candidate
    aidx = toindices(lefto)
    bidx = toindices(righto)
    sover = either(greater(size(intersection(srect, aidx)), ZERO), greater(size(intersection(srect, bidx)), ZERO))
    vover = either(greater(size(intersection(vrect, aidx)), ZERO), greater(size(intersection(vrect, bidx)), ZERO))
    sadj = either(adjacency(srect, lefto), adjacency(srect, righto))
    vadj = either(adjacency(vrect, lefto), adjacency(vrect, righto))
    sclear = both(flip(sover), flip(sadj))
    vclear = both(flip(vover), flip(vadj))
    rect = branch(sclear, srect, branch(vclear, vrect, vrect))
    O = underfill(I, EIGHT, rect)
    return O

def dsl3(I):
    # Orientation by checking for a positive horizontal gap between leftmost and rightmost boxes.
    obs = objects(I, T, F, T)
    lefto = argmin(obs, leftmost)
    othero = other(obs, lefto)
    side = greater(leftmost(othero), rightmost(lefto))
    if side:
        topov = branch(greater(uppermost(lefto), uppermost(othero)), uppermost(lefto), uppermost(othero))
        botov = branch(greater(lowermost(lefto), lowermost(othero)), lowermost(othero), lowermost(lefto))
        i0 = increment(topov)
        i1 = decrement(botov)
        j0 = increment(rightmost(lefto))
        j1 = decrement(leftmost(othero))
    else:
        topo = argmin(obs, uppermost)
        boto = other(obs, topo)
        leftov = branch(greater(leftmost(topo), leftmost(boto)), leftmost(topo), leftmost(boto))
        rightov = branch(greater(rightmost(topo), rightmost(boto)), rightmost(boto), rightmost(topo))
        j0 = increment(leftov)
        j1 = decrement(rightov)
        i0 = increment(lowermost(topo))
        i1 = decrement(uppermost(boto))
    rect = backdrop(connect(astuple(i0, j0), astuple(i1, j1)))
    O = fill(I, EIGHT, rect)
    return O

def dsl4(I):
    # Use largest two foreground objects; decide by shared rows, then bridge with margin.
    obs = fgpartition(I)
    a = argmax(obs, size)
    b = other(obs, a)
    side = hmatching(a, b)
    if side:
        lefto = branch(greater(leftmost(a), leftmost(b)), b, a)
        righto = other(obs, lefto)
        topov = branch(greater(uppermost(lefto), uppermost(righto)), uppermost(lefto), uppermost(righto))
        botov = branch(greater(lowermost(lefto), lowermost(righto)), lowermost(righto), lowermost(lefto))
        i0 = increment(topov)
        i1 = decrement(botov)
        j0 = increment(rightmost(lefto))
        j1 = decrement(leftmost(righto))
    else:
        topo = branch(greater(uppermost(a), uppermost(b)), b, a)
        boto = other(obs, topo)
        leftov = branch(greater(leftmost(topo), leftmost(boto)), leftmost(topo), leftmost(boto))
        rightov = branch(greater(rightmost(topo), rightmost(boto)), rightmost(boto), rightmost(topo))
        j0 = increment(leftov)
        j1 = decrement(rightov)
        i0 = increment(lowermost(topo))
        i1 = decrement(uppermost(boto))
    rect = backdrop(connect(astuple(i0, j0), astuple(i1, j1)))
    O = underfill(I, EIGHT, rect)
    return O

def dsl5(I):
    # Compare gaps along axes; prefer the axis with a positive gap.
    obs = objects(I, T, F, T)
    lefto = argmin(obs, leftmost)
    righto = other(obs, lefto)
    topo = argmin(obs, uppermost)
    boto = other(obs, topo)
    hg = subtract(subtract(leftmost(righto), rightmost(lefto)), ONE)   # horizontal gap width
    vg = subtract(subtract(uppermost(boto), lowermost(topo)), ONE)     # vertical gap height
    side = greater(hg, ZERO)
    if side:
        topov = branch(greater(uppermost(lefto), uppermost(righto)), uppermost(lefto), uppermost(righto))
        botov = branch(greater(lowermost(lefto), lowermost(righto)), lowermost(righto), lowermost(lefto))
        i0 = increment(topov)
        i1 = decrement(botov)
        j0 = increment(rightmost(lefto))
        j1 = decrement(leftmost(righto))
    else:
        leftov = branch(greater(leftmost(topo), leftmost(boto)), leftmost(topo), leftmost(boto))
        rightov = branch(greater(rightmost(topo), rightmost(boto)), rightmost(boto), rightmost(topo))
        j0 = increment(leftov)
        j1 = decrement(rightov)
        i0 = increment(lowermost(topo))
        i1 = decrement(uppermost(boto))
    rect = backdrop(connect(astuple(i0, j0), astuple(i1, j1)))
    O = underfill(I, EIGHT, rect)
    return O
```