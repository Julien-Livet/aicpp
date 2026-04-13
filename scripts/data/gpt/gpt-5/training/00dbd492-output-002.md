```python
def dsl1(I):
    comps = fgpartition(I)
    twos = colorfilter(comps, TWO)
    gt2 = rbind(greater, TWO)
    rings = sfilter(twos, fork(both, compose(gt2, height), compose(gt2, width)))
    inner = fork(difference, backdrop, box)
    iss16 = compose(rbind(equality, 16), size)
    iss24 = compose(rbind(equality, 24), size)
    set5 = sfilter(rings, iss16)
    set7 = sfilter(rings, iss24)
    rest = difference(rings, combine(set5, set7))
    obj = merge((
        mapply(compose(lbind(recolor, EIGHT), inner), set5),
        mapply(compose(lbind(recolor, FOUR), inner), set7),
        mapply(compose(lbind(recolor, THREE), inner), rest)
    ))
    O = underpaint(I, obj)
    return O

def dsl2(I):
    twos = colorfilter(objects(I, T, F, T), TWO)
    gt2 = rbind(greater, TWO)
    rings = sfilter(twos, fork(both, compose(gt2, height), compose(gt2, width)))
    ish5 = compose(rbind(equality, astuple(FIVE, FIVE)), shape)
    ish7 = compose(rbind(equality, astuple(SEVEN, SEVEN)), shape)
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
    rings = sfilter(colorfilter(partition(I), TWO), fork(both, compose(rbind(greater, TWO), height), compose(rbind(greater, TWO), width)))
    isw5 = compose(rbind(equality, FIVE), width)
    isw7 = compose(rbind(equality, SEVEN), width)
    set5 = sfilter(rings, isw5)
    set7 = sfilter(rings, isw7)
    rest = difference(rings, combine(set5, set7))
    obj = merge((
        mapply(compose(lbind(recolor, EIGHT), inbox), set5),
        mapply(compose(lbind(recolor, FOUR), inbox), set7),
        mapply(compose(lbind(recolor, THREE), inbox), rest)
    ))
    O = underpaint(I, obj)
    return O

def dsl4(I):
    twos = colorfilter(objects(I, T, T, T), TWO)
    gt2 = rbind(greater, TWO)
    rings = sfilter(twos, fork(both, compose(gt2, height), compose(gt2, width)))
    ish5 = compose(rbind(equality, FIVE), height)
    ish7 = compose(rbind(equality, SEVEN), height)
    set5 = sfilter(rings, ish5)
    set7 = sfilter(rings, ish7)
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
    isin9 = compose(rbind(equality, 9), compose(size, delta))
    isin25 = compose(rbind(equality, 25), compose(size, delta))
    set5 = sfilter(rings, isin9)
    set7 = sfilter(rings, isin25)
    rest = difference(rings, combine(set5, set7))
    obj = merge((
        mapply(compose(lbind(recolor, EIGHT), delta), set5),
        mapply(compose(lbind(recolor, FOUR), delta), set7),
        mapply(compose(lbind(recolor, THREE), delta), rest)
    ))
    O = underpaint(I, obj)
    return O
```