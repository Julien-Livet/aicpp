```python
def dsl1(I):
    zeros = ofcolor(I, ZERO)
    objs = objects(I, T, F, T)
    sevens = colorfilter(objs, SEVEN)
    non7 = difference(objs, sevens)
    non7inds = apply(toindices, non7)
    is_adj_zero = rbind(adjacent, zeros)
    is_border = lbind(bordering, I)
    cond = fork(either, is_border, is_adj_zero)
    targets = sfilter(non7inds, cond)
    recol = mapply(lbind(recolor, THREE), targets)
    O = paint(I, merge(recol))
    return O

def dsl2(I):
    A = replace(I, ONE, THREE)
    B = replace(A, FIVE, THREE)
    O = replace(B, EIGHT, THREE)
    return O

def dsl3(I):
    sev = ofcolor(I, SEVEN)
    bbox = backdrop(sev)
    outside = difference(asindices(I), bbox)
    O = fill(I, THREE, outside)
    return O

def dsl4(I):
    fr = frontiers(I)
    fr_inds = merge(apply(toindices, fr))
    O = fill(I, THREE, fr_inds)
    return O

def dsl5(I):
    L = lefthalf(I)
    leftinds = asindices(L)
    zerosL = ofcolor(L, ZERO)
    sevensL = ofcolor(L, SEVEN)
    keepL = combine(zerosL, sevensL)
    targets = difference(leftinds, keepL)
    O = fill(I, THREE, targets)
    return O
```