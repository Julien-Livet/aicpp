```python
def dsl1(I):
    twos = colorfilter(fgpartition(I), TWO)
    alltwos = merge(twos)
    s = subgrid(alltwos, I)
    zs = colorfilter(partition(s), ZERO)
    inner = sfilter(zs, compose(flip, rbind(bordering, s)))
    moved = apply(rbind(shift, ulcorner(alltwos)), inner)
    obj = merge(apply(lbind(recolor, ONE), moved))
    O = underpaint(I, obj)
    return O

def dsl2(I):
    twos = colorfilter(fgpartition(I), TWO)
    alltwos = merge(twos)
    s = subgrid(alltwos, I)
    zs = colorfilter(partition(s), ZERO)
    inner = sfilter(zs, compose(flip, rbind(bordering, s)))
    moved = apply(rbind(shift, ulcorner(alltwos)), inner)
    fillidx = merge(apply(toindices, moved))
    O = underfill(I, ONE, fillidx)
    return O

def dsl3(I):
    objs = objects(I, T, F, F)
    zeros = colorfilter(objs, ZERO)
    inner = sfilter(zeros, compose(flip, rbind(bordering, I)))
    ones_objs = merge(apply(lbind(recolor, ONE), inner))
    O = underpaint(I, ones_objs)
    return O

def dsl4(I):
    J = trim(I)
    zparts = colorfilter(partition(J), ZERO)
    innerJ = sfilter(zparts, compose(flip, rbind(bordering, J)))
    moved = apply(rbind(shift, UNITY), innerJ)
    obj = merge(apply(lbind(recolor, ONE), moved))
    O = underpaint(I, obj)
    return O

def dsl5(I):
    twos = colorfilter(fgpartition(I), TWO)
    alltwos = merge(twos)
    s = subgrid(alltwos, I)
    zcomps = colorfilter(partition(s), ZERO)
    notborder = sfilter(zcomps, compose(flip, rbind(bordering, s)))
    shifted = apply(rbind(shift, ulcorner(alltwos)), notborder)
    idx = merge(apply(toindices, shifted))
    O = underfill(I, ONE, idx)
    return O
```