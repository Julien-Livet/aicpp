```python
def dsl1(I):
    bg = mostcolor(I)
    pal = remove(bg, palette(I))
    dom = last(order(pal, lbind(colorcount, I)))
    objs = objects(I, T, F, T)
    domobjs = colorfilter(objs, dom)
    other = difference(objs, domobjs)
    bd = sfilter(other, rbind(bordering, I))
    nbd = difference(other, bd)
    x1 = fill(I, FIVE, merge(bd))
    O = fill(x1, THREE, merge(nbd))
    return O

def dsl2(I):
    bg = mostcolor(I)
    pal = remove(bg, palette(I))
    dom = last(order(pal, lbind(colorcount, I)))
    objs = objects(I, T, F, T)
    domobjs = colorfilter(objs, dom)
    A = merge(domobjs)
    other = difference(objs, domobjs)
    adj = sfilter(other, rbind(adjacent, A))
    bda = sfilter(domobjs, rbind(bordering, I))
    x1 = fill(I, THREE, merge(adj))
    O = fill(x1, FIVE, merge(bda))
    return O

def dsl3(I):
    TH = tophalf(I)
    bg = mostcolor(TH)
    pal = remove(bg, palette(TH))
    ordcols = order(pal, lbind(colorcount, TH))
    least = first(ordcols)
    rest = remove(least, pal)
    second = first(order(rest, lbind(colorcount, TH)))
    x1 = fill(I, FIVE, ofcolor(TH, least))
    O = fill(x1, THREE, ofcolor(TH, second))
    return O

def dsl4(I):
    objs = objects(I, T, F, T)
    hl = sfilter(objs, hline)
    vl = sfilter(objs, vline)
    lines = combine(hl, vl)
    blobs = difference(objs, lines)
    x1 = fill(I, FIVE, merge(lines))
    O = fill(x1, THREE, merge(blobs))
    return O

def dsl5(I):
    objs = objects(I, T, F, T)
    ordobjs = order(objs, size)
    o1 = first(ordobjs)
    o2 = first(remove(o1, ordobjs))
    x1 = fill(I, FIVE, o1)
    O = fill(x1, THREE, o2)
    return O
```