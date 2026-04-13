```python
def dsl1(I):
    O = replace(I, SEVEN, FIVE)
    return O

def dsl2(I):
    O = fill(I, FIVE, ofcolor(I, SEVEN))
    return O

def dsl3(I):
    mask = ofcolor(I, SEVEN)
    base = cover(I, mask)
    obj = recolor(FIVE, mask)
    O = paint(base, obj)
    return O

def dsl4(I):
    J = hmirror(I)
    obj = recolor(FIVE, ofcolor(J, SEVEN))
    K = paint(J, obj)
    O = hmirror(K)
    return O

def dsl5(I):
    objs = fgpartition(I)
    sevenobjs = colorfilter(objs, SEVEN)
    recolored = apply(lbind(recolor, FIVE), sevenobjs)
    unionobj = merge(recolored)
    base = cover(I, ofcolor(I, SEVEN))
    O = paint(base, unionobj)
    return O
```