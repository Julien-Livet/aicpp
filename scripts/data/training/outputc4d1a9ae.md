```python
def dsl1(I):
    # Column-wise cycle: replace background (most common color) by the "next" color among the other three,
    # where "other" is the (first-encountered) non-background color present in that column.
    bg = mostcolor(I)
    P = palette(I)
    P1 = remove(bg, P)
    f1 = lbind(ofcolor, I)
    f2 = compose(leftmost, f1)
    Ss = order(P1, f2)  # ordered cycle of non-bg colors
    a = first(Ss)
    c = last(Ss)
    tmp = remove(a, P1)
    b = first(remove(c, tmp))  # middle color
    colsa = mapply(vfrontier, ofcolor(I, a))
    colsb = mapply(vfrontier, ofcolor(I, b))
    colsc = mapply(vfrontier, ofcolor(I, c))
    Bg = ofcolor(I, bg)
    ta = intersection(Bg, colsa)
    tb = intersection(Bg, colsb)
    tc = intersection(Bg, colsc)
    obj1 = recolor(b, ta)  # a -> b
    obj2 = recolor(c, tb)  # b -> c
    obj3 = recolor(a, tc)  # c -> a
    obj = combine(combine(obj1, obj2), obj3)
    O = paint(I, obj)
    return O

def dsl2(I):
    # Same as dsl1 but reverse cycle direction in case the task uses the opposite orientation.
    bg = mostcolor(I)
    P = palette(I)
    P1 = remove(bg, P)
    f1 = lbind(ofcolor, I)
    f2 = compose(leftmost, f1)
    Ss = order(P1, f2)
    a = first(Ss)
    c = last(Ss)
    b = first(remove(c, remove(a, P1)))
    colsa = mapply(vfrontier, ofcolor(I, a))
    colsb = mapply(vfrontier, ofcolor(I, b))
    colsc = mapply(vfrontier, ofcolor(I, c))
    Bg = ofcolor(I, bg)
    ta = intersection(Bg, colsa)
    tb = intersection(Bg, colsb)
    tc = intersection(Bg, colsc)
    obj1 = recolor(c, ta)  # a -> c (reverse)
    obj2 = recolor(a, tb)  # b -> a
    obj3 = recolor(b, tc)  # c -> b
    obj = combine(combine(obj1, obj2), obj3)
    O = paint(I, obj)
    return O

def dsl3(I):
    # Choose ZERO as background if present; else most common. Order non-bg by uppermost occurrence.
    zc = colorcount(I, ZERO)
    bg0 = mostcolor(I)
    bg = branch(greater(zc, ZERO), ZERO, bg0)
    P = palette(I)
    P1 = remove(bg, P)
    f1 = lbind(ofcolor, I)
    f2 = compose(uppermost, f1)
    Ss = order(P1, f2)
    a = first(Ss)
    c = last(Ss)
    b = first(remove(c, remove(a, P1)))
    colsa = mapply(vfrontier, ofcolor(I, a))
    colsb = mapply(vfrontier, ofcolor(I, b))
    colsc = mapply(vfrontier, ofcolor(I, c))
    Bg = ofcolor(I, bg)
    ta = intersection(Bg, colsa)
    tb = intersection(Bg, colsb)
    tc = intersection(Bg, colsc)
    obj1 = recolor(b, ta)
    obj2 = recolor(c, tb)
    obj3 = recolor(a, tc)
    O = paint(I, combine(combine(obj1, obj2), obj3))
    return O

def dsl4(I):
    # Same as dsl1 but order the three non-bg colors by rightmost occurrence (alternative stable ordering).
    bg = mostcolor(I)
    P = palette(I)
    P1 = remove(bg, P)
    f1 = lbind(ofcolor, I)
    f2 = compose(rightmost, f1)
    Ss = order(P1, f2)
    a = first(Ss)
    c = last(Ss)
    b = first(remove(c, remove(a, P1)))
    colsa = mapply(vfrontier, ofcolor(I, a))
    colsb = mapply(vfrontier, ofcolor(I, b))
    colsc = mapply(vfrontier, ofcolor(I, c))
    Bg = ofcolor(I, bg)
    ta = intersection(Bg, colsa)
    tb = intersection(Bg, colsb)
    tc = intersection(Bg, colsc)
    obj1 = recolor(b, ta)
    obj2 = recolor(c, tb)
    obj3 = recolor(a, tc)
    O = paint(I, combine(combine(obj1, obj2), obj3))
    return O

def dsl5(I):
    # Hybrid: prefer ZERO background if present, reverse cycle direction, and order by leftmost.
    zc = colorcount(I, ZERO)
    bg0 = mostcolor(I)
    bg = branch(greater(zc, ZERO), ZERO, bg0)
    P = palette(I)
    P1 = remove(bg, P)
    f1 = lbind(ofcolor, I)
    f2 = compose(leftmost, f1)
    Ss = order(P1, f2)
    a = first(Ss)
    c = last(Ss)
    b = first(remove(c, remove(a, P1)))
    colsa = mapply(vfrontier, ofcolor(I, a))
    colsb = mapply(vfrontier, ofcolor(I, b))
    colsc = mapply(vfrontier, ofcolor(I, c))
    Bg = ofcolor(I, bg)
    ta = intersection(Bg, colsa)
    tb = intersection(Bg, colsb)
    tc = intersection(Bg, colsc)
    obj1 = recolor(c, ta)  # reverse cycle
    obj2 = recolor(a, tb)
    obj3 = recolor(b, tc)
    O = paint(I, combine(combine(obj1, obj2), obj3))
    return O
```