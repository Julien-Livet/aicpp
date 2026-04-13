```python
def dsl1(I):
    top = tophalf(I)
    ones = ofcolor(top, ONE)
    cols = mapply(rbind(shoot, DOWN), ones)
    fives = ofcolor(I, FIVE)
    keep = intersection(fives, cols)
    base = replace(I, FIVE, TWO)
    O = paint(base, toobject(keep, I))
    return O

def dsl2(I):
    S = ofcolor(I, FIVE)
    outline = box(S)
    keep = intersection(S, outline)
    base = replace(I, FIVE, TWO)
    O = paint(base, toobject(keep, I))
    return O

def dsl3(I):
    S = ofcolor(I, FIVE)
    SU = shift(S, UP)
    topmost = difference(S, SU)
    base = replace(I, FIVE, TWO)
    O = paint(base, toobject(topmost, I))
    return O

def dsl4(I):
    objs = objects(I, T, F, T)
    fives = colorfilter(objs, FIVE)
    ones_objs = colorfilter(objs, ONE)
    ones_union = merge(ones_objs)
    keep = argmin(fives, rbind(manhattan, ones_union))
    others = remove(keep, fives)
    recolored = mapply(lbind(recolor, TWO), others)
    O = paint(I, recolored)
    return O

def dsl5(I):
    top = tophalf(I)
    ones_objs = colorfilter(objects(top, T, F, T), ONE)
    left_one = argmin(ones_objs, leftmost)
    ul = ulcorner(left_one)
    ur = urcorner(left_one)
    span = connect(ul, ur)
    cols = mapply(rbind(shoot, DOWN), span)
    S = ofcolor(I, FIVE)
    keep = intersection(S, cols)
    base = replace(I, FIVE, TWO)
    O = paint(base, toobject(keep, I))
    return O
```