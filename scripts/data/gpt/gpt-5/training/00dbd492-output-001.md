```python
def dsl1(I):
    comps = partition(I)
    twos = colorfilter(comps, TWO)
    gt2 = rbind(greater, TWO)
    cond = fork(both, compose(gt2, height), compose(gt2, width))
    rings = sfilter(twos, cond)
    isw5 = compose(rbind(equality, FIVE), width)
    isw7 = compose(rbind(equality, SEVEN), width)
    set5 = sfilter(rings, isw5)
    set7 = sfilter(rings, isw7)
    rest = difference(rings, combine(set5, set7))
    rec8 = lbind(recolor, EIGHT)
    rec4 = lbind(recolor, FOUR)
    rec3 = lbind(recolor, THREE)
    obj = merge((
        mapply(compose(rec8, delta), set5),
        mapply(compose(rec4, delta), set7),
        mapply(compose(rec3, delta), rest)
    ))
    O = underpaint(I, obj)
    return O

def dsl2(I):
    comps = fgpartition(I)
    twos = colorfilter(comps, TWO)
    gt2 = rbind(greater, TWO)
    cond = fork(both, compose(gt2, height), compose(gt2, width))
    rings = sfilter(twos, cond)
    ish5 = compose(rbind(equality, FIVE), height)
    ish7 = compose(rbind(equality, SEVEN), height)
    set5 = sfilter(rings, ish5)
    set7 = sfilter(rings, ish7)
    rest = difference(rings, combine(set5, set7))
    obj = merge((
        mapply(compose(lbind(recolor, EIGHT), delta), set5),
        mapply(compose(lbind(recolor, FOUR), delta), set7),
        mapply(compose(lbind(recolor, THREE), delta), rest)
    ))
    O = underpaint(I, obj)
    return O

def dsl3(I):
    twos = colorfilter(objects(I, T, F, T), TWO)
    gt2 = rbind(greater, TWO)
    rings = sfilter(twos, fork(both, compose(gt2, height), compose(gt2, width)))
    ish5 = matcher(height, FIVE)
    ish7 = matcher(height, SEVEN)
    set5 = sfilter(rings, ish5)
    set7 = sfilter(rings, ish7)
    rest = difference(rings, combine(set5, set7))
    rec8 = lbind(recolor, EIGHT)
    rec4 = lbind(recolor, FOUR)
    rec3 = lbind(recolor, THREE)
    obj = merge((
        mapply(compose(rec8, delta), set5),
        mapply(compose(rec4, delta), set7),
        mapply(compose(rec3, delta), rest)
    ))
    O = underpaint(I, obj)
    return O

def dsl4(I):
    twos = colorfilter(objects(I, T, F, T), TWO)
    gt2 = rbind(greater, TWO)
    rings = sfilter(twos, fork(both, compose(gt2, height), compose(gt2, width)))
    isw5 = compose(rbind(equality, FIVE), width)
    isw7 = compose(rbind(equality, SEVEN), width)
    set5 = sfilter(rings, isw5)
    set7 = sfilter(rings, isw7)
    rest = difference(rings, combine(set5, set7))
    inner = compose(delta, box)
    obj = merge((
        mapply(compose(lbind(recolor, EIGHT), inner), set5),
        mapply(compose(lbind(recolor, FOUR), inner), set7),
        mapply(compose(lbind(recolor, THREE), inner), rest)
    ))
    O = underpaint(I, obj)
    return O

def dsl5(I):
    twos = colorfilter(objects(I, T, F, T), TWO)
    gt2 = rbind(greater, TWO)
    rings = sfilter(twos, fork(both, compose(gt2, height), compose(gt2, width)))
    iss16 = compose(rbind(equality, 16), size)
    iss24 = compose(rbind(equality, 24), size)
    set5 = sfilter(rings, iss16)
    set7 = sfilter(rings, iss24)
    rest = difference(rings, combine(set5, set7))
    obj = merge((
        mapply(compose(lbind(recolor, EIGHT), delta), set5),
        mapply(compose(lbind(recolor, FOUR), delta), set7),
        mapply(compose(lbind(recolor, THREE), delta), rest)
    ))
    O = underpaint(I, obj)
    return O
```