```python
def dsl1(I):
    # Geometric (shifts of corners): put 2s at outbox-adjacent orthogonal neighbors of non-singleton square corners
    objs = objects(I, T, F, T)
    eqhw = fork(equality, height, width)
    sq0 = sfilter(objs, eqhw)
    size1 = compose(lbind(equality, ONE), size)
    nonsing = compose(flip, size1)
    sqs = sfilter(sq0, nonsing)
    c = corners
    u = compose(rbind(shift, UP), c)
    d = compose(rbind(shift, DOWN), c)
    l = compose(rbind(shift, LEFT), c)
    r = compose(rbind(shift, RIGHT), c)
    ud = fork(combine, u, d)
    lr = fork(combine, l, r)
    alln = fork(combine, ud, lr)
    ext = fork(intersection, alln, outbox)
    obj2 = mapply(compose(lbind(recolor, TWO), ext), sqs)
    O = underpaint(I, obj2)
    return O

def dsl2(I):
    # Object-neighborhood: neighbors of corners intersected with outbox, excluding singletons
    objs = objects(I, T, F, T)
    sq0 = sfilter(objs, square)
    size1 = compose(lbind(equality, ONE), size)
    nonsing = compose(flip, size1)
    sqs = sfilter(sq0, nonsing)
    fN = compose(lbind(mapply, neighbors), corners)
    ext = fork(intersection, fN, outbox)
    obj2 = mapply(compose(lbind(recolor, TWO), ext), sqs)
    O = underpaint(I, obj2)
    return O

def dsl3(I):
    # Geometric rays (shoot): shoot from each corner in four orthogonal directions; keep first step via outbox
    objs = objects(I, T, F, T)
    eqhw = fork(equality, height, width)
    sq0 = sfilter(objs, eqhw)
    size1 = compose(lbind(equality, ONE), size)
    nonsing = compose(flip, size1)
    sqs = sfilter(sq0, nonsing)
    c = corners
    su = compose(rbind(shoot, UP), c)
    sd = compose(rbind(shoot, DOWN), c)
    sl = compose(rbind(shoot, LEFT), c)
    sr = compose(rbind(shoot, RIGHT), c)
    ud = fork(combine, su, sd)
    lr = fork(combine, sl, sr)
    rays = fork(combine, ud, lr)
    ext = fork(intersection, rays, outbox)
    obj2 = mapply(compose(lbind(recolor, TWO), ext), sqs)
    O = underpaint(I, obj2)
    return O

def dsl4(I):
    # Relational frontiers: horizontal/vertical frontiers from corners clipped to outbox
    objs = objects(I, T, F, T)
    sq0 = sfilter(objs, square)
    size1 = compose(lbind(equality, ONE), size)
    nonsing = compose(flip, size1)
    sqs = sfilter(sq0, nonsing)
    ch = compose(lbind(mapply, hfrontier), corners)
    cv = compose(lbind(mapply, vfrontier), corners)
    hv = fork(combine, ch, cv)
    ext = fork(intersection, hv, outbox)
    obj2 = mapply(compose(lbind(recolor, TWO), ext), sqs)
    O = underpaint(I, obj2)
    return O

def dsl5(I):
    # Color fill (underfill): compute target indices then fill background with 2
    objs = objects(I, T, F, T)
    eqhw = fork(equality, height, width)
    sq0 = sfilter(objs, eqhw)
    size1 = compose(lbind(equality, ONE), size)
    nonsing = compose(flip, size1)
    sqs = sfilter(sq0, nonsing)
    fN = compose(lbind(mapply, neighbors), corners)
    ext = fork(intersection, fN, outbox)
    idx = mapply(ext, sqs)
    O = underfill(I, TWO, idx)
    return O
```