```python
def dsl1(I):
    x1 = rbind(objects, T)
    x2 = rbind(x1, F)
    x3 = rbind(x2, T)
    x4 = compose(merge, x3)
    obj0 = x4(I)
    p = hperiod(obj0)
    dir = astuple(ZERO, p)
    sh = rbind(shift, dir)
    shobj = compose(sh, x4)
    f = fork(underpaint, identity, shobj)
    n = width(I)
    powf = power(f, n)
    O = powf(I)
    return O

def dsl2(I):
    x1 = rbind(objects, T)
    x2 = rbind(x1, F)
    x3 = rbind(x2, T)
    x4 = compose(merge, x3)
    obj0 = x4(I)
    p = hperiod(obj0)
    dir = astuple(ZERO, p)
    sh = rbind(shift, dir)
    shobj = compose(sh, x4)
    f = fork(underpaint, identity, shobj)
    k = divide(width(I), p)
    n = add(k, ONE)
    powf = power(f, n)
    O = powf(I)
    return O

def dsl3(I):
    xobjs = rbind(objects, T)
    xobjs = rbind(xobjs, F)
    xobjs = rbind(xobjs, T)
    uobj = compose(merge, xobjs)
    base = uobj(I)
    per = hperiod(base)
    step = astuple(ZERO, per)
    sh = rbind(shift, step)
    nxt = compose(sh, uobj)
    grow = fork(underpaint, identity, nxt)
    times = add(width(I), ONE)
    O = power(grow, times)(I)
    return O
```