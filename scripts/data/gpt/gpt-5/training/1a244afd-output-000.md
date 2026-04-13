```python
def dsl1(I):
    P = asindices(I)
    ones = ofcolor(I, ONE)
    sixes = ofcolor(I, SIX)
    base = replace(I, SIX, EIGHT)
    def per(o):
        p = initset(o)
        predh = compose(lbind(hmatching, p), initset)
        predv = compose(lbind(vmatching, p), initset)
        cond = fork(either, predh, predv)
        aligned = sfilter(sixes, cond)
        comp = compose(lbind(manhattan, p), initset)
        q = valmin(aligned, comp)
        qq = initset(q)
        d = gravitate(p, qq)
        orth = branch(equality(d, UP), LEFT, branch(equality(d, DOWN), RIGHT, branch(equality(d, LEFT), DOWN, UP)))
        dist = manhattan(p, qq)
        off = multiply(orth, dist)
        t = add(o, off)
        return intersection(initset(t), P)
    T = merge(apply(per, ones))
    O = fill(base, SEVEN, T)
    return O

def dsl2(I):
    base = replace(I, SIX, EIGHT)
    ones = ofcolor(I, ONE)
    ray_left = rbind(shoot, LEFT)
    leftmost = compose(ulcorner, ray_left)
    target = compose(initset, leftmost)
    T = merge(apply(target, ones))
    O = fill(base, SEVEN, T)
    return O

def dsl3(I):
    P = asindices(I)
    ones = ofcolor(I, ONE)
    base = replace(I, SIX, EIGHT)
    step_left = rbind(add, LEFT)
    rawt = compose(initset, step_left)
    tgt = compose(lbind(intersection, P), rawt)
    T = merge(apply(tgt, ones))
    O = fill(base, SEVEN, T)
    return O

def dsl4(I):
    P = asindices(I)
    ones = ofcolor(I, ONE)
    sixes = ofcolor(I, SIX)
    base = replace(I, SIX, EIGHT)
    def per(o):
        p = initset(o)
        predh = compose(lbind(hmatching, p), initset)
        predv = compose(lbind(vmatching, p), initset)
        cond = fork(either, predh, predv)
        aligned = sfilter(sixes, cond)
        comp = compose(lbind(manhattan, p), initset)
        q = valmin(aligned, comp)
        qq = initset(q)
        d = gravitate(p, qq)
        orth = branch(equality(d, UP), LEFT, branch(equality(d, DOWN), RIGHT, branch(equality(d, LEFT), DOWN, UP)))
        t = add(o, orth)
        return intersection(initset(t), P)
    T = merge(apply(per, ones))
    O = fill(base, SEVEN, T)
    return O

def dsl5(I):
    O = replace(I, SIX, EIGHT)
    return O
```