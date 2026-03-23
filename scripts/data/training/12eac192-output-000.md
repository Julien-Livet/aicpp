```python
def dsl1(I):
    zeros = ofcolor(I, ZERO)
    objs = objects(I, T, F, T)
    sevens = colorfilter(objs, SEVEN)
    non7 = difference(objs, sevens)
    f_adj_zero = rbind(adjacent, zeros)
    f_border = lbind(bordering, I)
    cond = fork(either, f_border, f_adj_zero)
    targets = sfilter(non7, cond)
    recol = mapply(lbind(recolor, THREE), targets)
    O = paint(I, merge(recol))
    return O

def dsl2(I):
    A = replace(I, ONE, THREE)
    B = replace(A, FIVE, THREE)
    O = replace(B, EIGHT, THREE)
    return O

def dsl3(I):
    objs = objects(I, T, F, T)
    non7 = difference(objs, colorfilter(objs, SEVEN))
    recol = mapply(lbind(recolor, THREE), non7)
    O = paint(I, merge(recol))
    return O

def dsl4(I):
    O = compress(I)
    return O

def dsl5(I):
    sev = ofcolor(I, SEVEN)
    outline = box(sev)
    O = fill(I, THREE, outline)
    return O
```