```python
def dsl1(I):
    # Horizontal rectangle bridging between same-colored, horizontally aligned pairs; underpaint
    s = mostcolor(I)
    dims = shape(I)
    objs = objects(I, T, F, T)
    fg = sfilter(objs, compose(flip, matcher(color, s)))
    pairs = product(fg, fg)
    same = fork(equality, compose(color, first), compose(color, last))
    hA = fork(hmatching, first, last)
    good = sfilter(pairs, fork(both, same, hA))
    fill = compose(backdrop, fork(combine, first, last))
    can = compose(rbind(canvas, dims), compose(color, first))
    mk = fork(toobject, fill, can)
    P = merge(apply(mk, good))
    O = underpaint(I, P)
    return O

def dsl2(I):
    # Geometric: connect centers of horizontally aligned same-colored pairs with lines; underpaint
    s = mostcolor(I)
    dims = shape(I)
    objs = objects(I, T, F, T)
    fg = sfilter(objs, compose(flip, matcher(color, s)))
    pairs = product(fg, fg)
    same = fork(equality, compose(color, first), compose(color, last))
    hA = fork(hmatching, first, last)
    good = sfilter(pairs, fork(both, same, hA))
    seg = fork(connect, compose(centerofmass, first), compose(centerofmass, last))
    can = compose(rbind(canvas, dims), compose(color, first))
    mk = fork(toobject, seg, can)
    P = merge(apply(mk, good))
    O = underpaint(I, P)
    return O

def dsl3(I):
    # Object-wise row-band projection: shoot left/right from object's upper and lower corners; underpaint
    s = mostcolor(I)
    dims = shape(I)
    objs = objects(I, T, F, T)
    fg = sfilter(objs, compose(flip, matcher(color, s)))
    sl = rbind(shoot, LEFT)
    sr = rbind(shoot, RIGHT)
    topL = compose(sl, ulcorner)
    topR = compose(sr, ulcorner)
    botL = compose(sl, llcorner)
    botR = compose(sr, llcorner)
    segT = fork(combine, topL, topR)
    segB = fork(combine, botL, botR)
    seg = fork(combine, segT, segB)
    can = compose(rbind(canvas, dims), color)
    mk = fork(toobject, seg, compose(can, identity))
    P = merge(apply(mk, fg))
    O = underpaint(I, P)
    return O

def dsl4(I):
    # Global (scale-space): downscale to cell grid, bridge horizontally there, upscale, then underpaint onto original
    G = downscale(I, THREE)
    dimsG = shape(G)
    sG = mostcolor(G)
    objs = objects(G, T, F, T)
    notS = compose(flip, matcher(color, sG))
    notZ = compose(flip, matcher(color, ZERO))
    cond = fork(both, notS, notZ)
    fg = sfilter(objs, cond)
    pairs = product(fg, fg)
    same = fork(equality, compose(color, first), compose(color, last))
    hA = fork(hmatching, first, last)
    good = sfilter(pairs, fork(both, same, hA))
    fill = compose(backdrop, fork(combine, first, last))
    can = compose(rbind(canvas, dimsG), compose(color, first))
    mk = fork(toobject, fill, can)
    P = merge(apply(mk, good))
    G2 = underpaint(G, P)
    U = upscale(G2, THREE)
    O = underpaint(I, asobject(U))
    return O

def dsl5(I):
    # Color filtering + local thickening: per non-dominant object fill its bounding box; underpaint
    s = mostcolor(I)
    dims = shape(I)
    objs = objects(I, T, F, T)
    fg = sfilter(objs, compose(flip, matcher(color, s)))
    boxfill = compose(backdrop, identity)
    can = compose(rbind(canvas, dims), color)
    mk = fork(toobject, boxfill, compose(can, identity))
    P = merge(apply(mk, fg))
    O = underpaint(I, P)
    return O
```