```python
def dsl1(I):
    # Replace 1->2, then for each 2-object draw its top and left bbox edges with 3
    x = replace(I, ONE, TWO)
    objs = objects(x, T, F, T)
    twos = colorfilter(objs, TWO)
    seg_top = fork(connect, ulcorner, urcorner)
    seg_left = fork(connect, ulcorner, llcorner)
    edges_fun = fork(combine, seg_top, seg_left)
    edges = mapply(edges_fun, twos)
    O = underpaint(x, recolor(THREE, edges))
    return O

def dsl2(I):
    # Replace 1->2, then draw a top-left L on the bbox of (2 U 3)
    x = replace(I, ONE, TWO)
    mask = combine(ofcolor(x, TWO), ofcolor(I, THREE))
    if size(mask) == 0:
        return x
    ul = ulcorner(mask)
    ur = urcorner(mask)
    ll = llcorner(mask)
    top = connect(ul, ur)
    left = connect(ul, ll)
    obj = recolor(THREE, combine(top, left))
    O = underpaint(x, obj)
    return O

def dsl3(I):
    # Replace 1->2, then outline (full perimeter) of each 2-object with 3
    x = replace(I, ONE, TWO)
    objs = objects(x, T, F, T)
    twos = colorfilter(objs, TWO)
    perim_fun = compose(box, inbox)
    perims = mapply(perim_fun, twos)
    O = underpaint(x, recolor(THREE, perims))
    return O

def dsl4(I):
    # Replace 1->2, then from the (first) 3-cell draw up to top border, then left to corner, then down the left border
    x = replace(I, ONE, TWO)
    objs = objects(I, T, F, T)
    threes = colorfilter(objs, THREE)
    if size(threes) == 0:
        return x
    a3 = first(threes)
    ri = uppermost(a3)
    cj = leftmost(a3)
    h = height(I)
    top_pt = astuple(ZERO, cj)
    anc_pt = astuple(ri, cj)
    top_left = astuple(ZERO, ZERO)
    bottom_left = astuple(subtract(h, ONE), ZERO)
    up_seg = connect(anc_pt, top_pt)
    left_seg = connect(top_pt, top_left)
    down_seg = connect(top_left, bottom_left)
    obj = recolor(THREE, combine(combine(up_seg, left_seg), down_seg))
    O = underpaint(x, obj)
    return O

def dsl5(I):
    # Replace 1->2, then draw an L using extremes of all 2-cells (top row and left column of their bbox)
    x = replace(I, ONE, TWO)
    mask = ofcolor(x, TWO)
    if size(mask) == 0:
        return x
    topi = uppermost(mask)
    leftj = leftmost(mask)
    rightj = rightmost(mask)
    lowi = lowermost(mask)
    top_line = connect(astuple(topi, leftj), astuple(topi, rightj))
    left_line = connect(astuple(topi, leftj), astuple(lowi, leftj))
    obj = recolor(THREE, combine(top_line, left_line))
    O = underpaint(x, obj)
    return O
```