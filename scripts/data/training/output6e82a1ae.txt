```python
def dsl1(I):
    # Border-aware + interior side split
    x1 = objects(I, T, F, T)
    x2 = colorfilter(x1, FIVE)
    brd = sfilter(x2, rbind(bordering, I))
    rB = sfilter(brd, matcher(rightmost, subtract(width(I), ONE)))
    otherB = difference(brd, rB)
    notB = difference(x2, brd)
    mid = halve(width(I))
    leftInt = sfilter(notB, compose(lbind(greater, mid), leftmost))
    rightInt = difference(notB, leftInt)
    y1 = mapply(lbind(recolor, ONE), otherB)
    y2 = mapply(lbind(recolor, TWO), rB)
    y3 = mapply(lbind(recolor, TWO), leftInt)
    y4 = mapply(lbind(recolor, THREE), rightInt)
    y = merge((y1, y2, y3, y4))
    O = paint(I, y)
    return O

def dsl2(I):
    # By component size: 4 -> 1, 3 -> 2, rest -> 3
    x1 = objects(I, T, F, T)
    x2 = colorfilter(x1, FIVE)
    s4 = sizefilter(x2, 4)
    s3 = sizefilter(x2, 3)
    rest = difference(x2, combine(s4, s3))
    y1 = mapply(lbind(recolor, ONE), s4)
    y2 = mapply(lbind(recolor, TWO), s3)
    y3 = mapply(lbind(recolor, THREE), rest)
    y = merge((y1, y2, y3))
    O = paint(I, y)
    return O

def dsl3(I):
    # By shape: horizontal lines -> 2, vertical lines -> 3, others -> 1
    x1 = objects(I, T, F, T)
    x2 = colorfilter(x1, FIVE)
    h = sfilter(x2, hline)
    v = sfilter(x2, vline)
    hv = combine(h, v)
    other = difference(x2, hv)
    yh = mapply(lbind(recolor, TWO), h)
    yv = mapply(lbind(recolor, THREE), v)
    yo = mapply(lbind(recolor, ONE), other)
    y = merge((yh, yv, yo))
    O = paint(I, y)
    return O

def dsl4(I):
    # Horizontal thirds: top->2, middle->3, bottom->1
    a, b, c = hsplit(I, THREE)
    aa = replace(a, FIVE, TWO)
    bb = replace(b, FIVE, THREE)
    cc = replace(c, FIVE, ONE)
    O = vconcat(vconcat(aa, bb), cc)
    return O

def dsl5(I):
    # Left/Right halves: left->2, right->3
    L = lefthalf(I)
    R = righthalf(I)
    L2 = replace(L, FIVE, TWO)
    R3 = replace(R, FIVE, THREE)
    O = hconcat(L2, R3)
    return O
```