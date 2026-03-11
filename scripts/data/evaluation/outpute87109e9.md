```python
def dsl1(I):
    # Fill entire rows and columns through every 8, but do not overwrite 5
    objs8 = colorfilter(objects(I, T, F, T), EIGHT)
    if size(objs8) == 0:
        return I
    idxs = merge(apply(toindices, objs8))
    lefts = mapply(rbind(shoot, LEFT), idxs)
    rights = mapply(rbind(shoot, RIGHT), idxs)
    ups = mapply(rbind(shoot, UP), idxs)
    downs = mapply(rbind(shoot, DOWN), idxs)
    band = combine(combine(lefts, rights), combine(ups, downs))
    band = combine(band, idxs)
    avoid5 = ofcolor(I, FIVE)
    band = difference(band, avoid5)
    O = fill(I, EIGHT, band)
    return O

def dsl2(I):
    # Fill only vertical columns through every 8, but do not overwrite 5
    objs8 = colorfilter(objects(I, T, F, T), EIGHT)
    if size(objs8) == 0:
        return I
    idxs = merge(apply(toindices, objs8))
    ups = mapply(rbind(shoot, UP), idxs)
    downs = mapply(rbind(shoot, DOWN), idxs)
    band = combine(ups, downs)
    band = combine(band, idxs)
    avoid5 = ofcolor(I, FIVE)
    band = difference(band, avoid5)
    O = fill(I, EIGHT, band)
    return O

def dsl3(I):
    # Replace the most common non-5, non-8 color globally with 8
    pals = palette(I)
    pals = remove(FIVE, pals)
    pals = remove(EIGHT, pals)
    if size(pals) == 0:
        return I
    comp = lbind(colorcount, I)
    tgt = argmax(pals, comp)
    O = replace(I, tgt, EIGHT)
    return O

def dsl4(I):
    # Recolor any non-5, non-8 component that is adjacent to any 8 into 8
    objs = objects(I, T, F, F)
    objs8 = colorfilter(objs, EIGHT)
    if size(objs8) == 0:
        return I
    idxs8 = merge(apply(toindices, objs8))
    is5 = compose(lbind(equality, FIVE), color)
    not5 = compose(flip, is5)
    is8 = compose(lbind(equality, EIGHT), color)
    not8 = compose(flip, is8)
    adj_to_8 = compose(lbind(adjacent, idxs8), toindices)
    cond = fork(both, adj_to_8, fork(both, not5, not8))
    targets = sfilter(objs, cond)
    patch = merge(apply(toindices, targets))
    O = fill(I, EIGHT, patch)
    return O

def dsl5(I):
    # Fill only horizontal rows through every 8, but do not overwrite 5
    objs8 = colorfilter(objects(I, T, F, T), EIGHT)
    if size(objs8) == 0:
        return I
    idxs = merge(apply(toindices, objs8))
    lefts = mapply(rbind(shoot, LEFT), idxs)
    rights = mapply(rbind(shoot, RIGHT), idxs)
    band = combine(lefts, rights)
    band = combine(band, idxs)
    avoid5 = ofcolor(I, FIVE)
    band = difference(band, avoid5)
    O = fill(I, EIGHT, band)
    return O
```