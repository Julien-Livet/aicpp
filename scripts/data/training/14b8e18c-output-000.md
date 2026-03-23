```python
def dsl1(I):
    objs = objects(I, T, F, T)
    sqs = sfilter(objs, square)
    fN = compose(lbind(mapply, neighbors), corners)
    fE = fork(intersection, fN, outbox)
    recol2 = lbind(recolor, TWO)
    fR = compose(recol2, fE)
    obj2 = mapply(fR, sqs)
    O = underpaint(I, obj2)
    return O

def dsl2(I):
    objs = objects(I, T, F, T)
    sqs = sfilter(objs, square)
    c = corners
    u = compose(lbind(shift, UP), c)
    d = compose(lbind(shift, DOWN), c)
    l = compose(lbind(shift, LEFT), c)
    r = compose(lbind(shift, RIGHT), c)
    ud = fork(combine, u, d)
    lr = fork(combine, l, r)
    alln = fork(combine, ud, lr)
    ext = fork(intersection, alln, outbox)
    recol2 = lbind(recolor, TWO)
    fR = compose(recol2, ext)
    obj2 = mapply(fR, sqs)
    O = underpaint(I, obj2)
    return O

def dsl3(I):
    objs = objects(I, T, F, T)
    eqhw = fork(equality, height, width)
    sqs = sfilter(objs, eqhw)
    fN = compose(lbind(mapply, neighbors), corners)
    fE = fork(intersection, fN, outbox)
    fR = compose(lbind(recolor, TWO), fE)
    obj2 = mapply(fR, sqs)
    O = underpaint(I, obj2)
    return O

def dsl4(I):
    objs = objects(I, T, F, T)
    sqs = sfilter(objs, square)
    # use shoot outward then restrict to outbox to keep only the first step
    ul = ulcorner
    ur = urcorner
    ll = llcorner
    lr = lrcorner
    s_up_ul = compose(lbind(shoot, UP), ul)
    s_left_ul = compose(lbind(shoot, LEFT), ul)
    s_up_ur = compose(lbind(shoot, UP), ur)
    s_right_ur = compose(lbind(shoot, RIGHT), ur)
    s_down_ll = compose(lbind(shoot, DOWN), ll)
    s_left_ll = compose(lbind(shoot, LEFT), ll)
    s_down_lr = compose(lbind(shoot, DOWN), lr)
    s_right_lr = compose(lbind(shoot, RIGHT), lr)
    a = fork(combine, s_up_ul, s_left_ul)
    b = fork(combine, s_up_ur, s_right_ur)
    c = fork(combine, s_down_ll, s_left_ll)
    d = fork(combine, s_down_lr, s_right_lr)
    ab = fork(combine, a, b)
    cd = fork(combine, c, d)
    allshoot = fork(combine, ab, cd)
    ext = fork(intersection, allshoot, outbox)
    fR = compose(lbind(recolor, TWO), ext)
    obj2 = mapply(fR, sqs)
    O = paint(I, obj2)
    return O

def dsl5(I):
    objs = objects(I, T, F, T)
    sqs = sfilter(objs, square)
    ch = compose(lbind(mapply, hfrontier), corners)
    cv = compose(lbind(mapply, vfrontier), corners)
    hv = fork(combine, ch, cv)
    ext = fork(intersection, hv, outbox)
    fR = compose(lbind(recolor, TWO), ext)
    obj2 = mapply(fR, sqs)
    O = underpaint(I, obj2)
    return O
```