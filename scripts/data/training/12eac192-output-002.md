```python
def dsl1(I):
    # Global: recolor all non-zero, non-seven cells in the top half to 3
    T = tophalf(I)
    topinds = asindices(T)
    zerosT = ofcolor(T, ZERO)
    sevensT = ofcolor(T, SEVEN)
    mask = difference(topinds, combine(zerosT, sevensT))
    O = fill(I, THREE, mask)
    return O

def dsl2(I):
    # Object extraction: recolor all small (size 1 or 2) non-seven objects to 3
    objs = objects(I, T, F, T)
    sevobjs = colorfilter(objs, SEVEN)
    non7 = difference(objs, sevobjs)
    s1 = sizefilter(non7, 1)
    s2 = sizefilter(non7, 2)
    small = combine(s1, s2)
    recol = mapply(lbind(recolor, THREE), small)
    O = paint(I, merge(recol))
    return O

def dsl3(I):
    # Color filtering: replace colors 1 and 5 with 3
    A = replace(I, ONE, THREE)
    O = replace(A, FIVE, THREE)
    return O

def dsl4(I):
    # Geometric: recolor all non-zero, non-seven cells in the left half to 3
    L = lefthalf(I)
    leftinds = asindices(L)
    zerosL = ofcolor(L, ZERO)
    sevensL = ofcolor(L, SEVEN)
    mask = difference(leftinds, combine(zerosL, sevensL))
    O = fill(I, THREE, mask)
    return O

def dsl5(I):
    # Relational: recolor non-seven objects that share any row with a seven to 3
    objs = objects(I, T, F, T)
    sevpatch = ofcolor(I, SEVEN)
    non7 = difference(objs, colorfilter(objs, SEVEN))
    is_hmatch = rbind(hmatching, sevpatch)
    targets = sfilter(non7, is_hmatch)
    recol = mapply(lbind(recolor, THREE), targets)
    O = paint(I, merge(recol))
    return O
```