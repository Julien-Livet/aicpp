```python
def dsl1(I):
    dims = shape(I)
    H = height(I)
    Z = canvas(ZERO, dims)
    objs = objects(I, T, F, T)

    const0 = lbind(identity, ZERO)
    startloc = fork(astuple, uppermost, const0)
    rowpatch = compose(rbind(shoot, RIGHT), startloc)
    rowobj = fork(recolor, color, rowpatch)
    rowobjs = mapply(rowobj, objs)

    topobj = argmin(objs, uppermost)
    botobj = argmax(objs, lowermost)
    toprow = recolor(color(topobj), shoot(astuple(ZERO, ZERO), RIGHT))
    H1 = decrement(H)
    botrow = recolor(color(botobj), shoot(astuple(H1, ZERO), RIGHT))

    unionrows = combine(rowobjs, combine(toprow, botrow))
    O = paint(Z, unionrows)
    return O

def dsl2(I):
    dims = shape(I)
    H = height(I)
    W = width(I)
    Z = canvas(ZERO, dims)
    objs = objects(I, T, F, T)

    const0 = lbind(identity, ZERO)
    W1 = decrement(W)
    constw1 = lbind(identity, W1)

    # full row at object row
    startloc = fork(astuple, uppermost, const0)
    rowpatch = compose(rbind(shoot, RIGHT), startloc)
    rowobj = fork(recolor, color, rowpatch)

    # small vertical segments (r-1 to r+1) on both borders
    dec_r = compose(decrement, uppermost)
    inc_r = compose(increment, uppermost)

    left_top = fork(astuple, dec_r, const0)
    left_bot = fork(astuple, inc_r, const0)
    left_seg = fork(connect, left_top, left_bot)
    left_obj = fork(recolor, color, left_seg)

    right_top = fork(astuple, dec_r, constw1)
    right_bot = fork(astuple, inc_r, constw1)
    right_seg = fork(connect, right_top, right_bot)
    right_obj = fork(recolor, color, right_seg)

    sides = fork(combine, left_obj, right_obj)
    triplet = fork(combine, rowobj, sides)
    segs = mapply(triplet, objs)

    # also enforce edge rows colored by top/bottom objects
    topobj = argmin(objs, uppermost)
    botobj = argmax(objs, lowermost)
    toprow = recolor(color(topobj), shoot(astuple(ZERO, ZERO), RIGHT))
    H1 = decrement(H)
    botrow = recolor(color(botobj), shoot(astuple(H1, ZERO), RIGHT))

    allobjs = combine(segs, combine(toprow, botrow))
    O = paint(Z, allobjs)
    return O

def dsl3(I):
    objs = objects(I, T, F, T)
    topobj = argmin(objs, uppermost)
    ctop = color(topobj)
    O = replace(I, ZERO, ctop)
    return O

def dsl4(I):
    dims = shape(I)
    Z = canvas(ZERO, dims)
    frame = box(asindices(I))
    objs = objects(I, T, F, T)
    botobj = argmax(objs, lowermost)
    cbot = color(botobj)
    O = paint(Z, recolor(cbot, frame))
    return O

def dsl5(I):
    dims = shape(I)
    H = height(I)
    W = width(I)
    Z = canvas(ZERO, dims)
    objs = objects(I, T, F, T)

    # horizontal full rows at anchors (object rows)
    const0 = lbind(identity, ZERO)
    startloc = fork(astuple, uppermost, const0)
    rowpatch = compose(rbind(shoot, RIGHT), startloc)
    rowobj = fork(recolor, color, rowpatch)
    rowobjs = mapply(rowobj, objs)

    # also include top and bottom edge rows colored by top/bottom objects
    topobj = argmin(objs, uppermost)
    botobj = argmax(objs, lowermost)
    toprow = recolor(color(topobj), shoot(astuple(ZERO, ZERO), RIGHT))
    H1 = decrement(H)
    botrow = recolor(color(botobj), shoot(astuple(H1, ZERO), RIGHT))

    # build vertical border segments split at midpoints between consecutive anchors
    pairs = product(objs, objs)
    ra = compose(uppermost, first)
    rb = compose(uppermost, last)
    ca = compose(color, first)
    cb = compose(color, last)
    cond = fork(greater, rb, ra)  # keep pairs with rb > ra
    ordpairs = sfilter(pairs, cond)

    W1 = decrement(W)
    constw1 = lbind(identity, W1)
    midf = compose(halve, fork(add, ra, rb))

    # left column segments
    a_left = fork(astuple, ra, const0)
    m_left = fork(astuple, midf, const0)
    b_left = fork(astuple, rb, const0)
    top2mid_l = fork(connect, a_left, m_left)
    mid2bot_l = fork(connect, compose(increment, midf), b_left)
    top2mid_l_obj = fork(recolor, ca, top2mid_l)
    mid2bot_l_obj = fork(recolor, cb, mid2bot_l)
    left_union = fork(combine, top2mid_l_obj, mid2bot_l_obj)

    # right column segments
    a_right = fork(astuple, ra, constw1)
    m_right = fork(astuple, midf, constw1)
    b_right = fork(astuple, rb, constw1)
    top2mid_r = fork(connect, a_right, m_right)
    mid2bot_r = fork(connect, compose(increment, midf), b_right)
    top2mid_r_obj = fork(recolor, ca, top2mid_r)
    mid2bot_r_obj = fork(recolor, cb, mid2bot_r)
    right_union = fork(combine, top2mid_r_obj, mid2bot_r_obj)

    pair_union = fork(combine, left_union, right_union)
    border_objs = mapply(pair_union, ordpairs)

    allobjs = combine(border_objs, combine(rowobjs, combine(toprow, botrow)))
    O = paint(Z, allobjs)
    return O
```