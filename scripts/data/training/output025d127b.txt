```python
def dsl1(I):
    O = canvas(ZERO, shape(I))
    objs = objects(I, T, T, T)
    for obj in objs:
        inds = toindices(obj)
        # bottom row of the object
        bottom = intersection(inds, hfrontier(llcorner(obj)))
        # all non-bottom indices
        upper = difference(inds, bottom)
        # right-edge indices (by object's rightmost column)
        rightedge = intersection(upper, vfrontier(urcorner(obj)))
        # shift upper non-rightedge to the right by 1
        upper_move = shift(difference(upper, rightedge), RIGHT)
        newinds = merge((bottom, rightedge, upper_move))
        newobj = recolor(color(obj), newinds)
        O = paint(O, newobj)
    return O

def dsl2(I):
    base = canvas(ZERO, shape(I))
    for obj in objects(I, T, T, T):
        inds = toindices(obj)
        bottom = intersection(inds, hfrontier(llcorner(obj)))
        upper = difference(inds, bottom)
        # clip shifted cells to the object's bounding box and preserve right edge
        bbox = inbox(obj)
        shifted = intersection(shift(upper, RIGHT), bbox)
        rightedge = intersection(upper, vfrontier(urcorner(obj)))
        newinds = merge((bottom, rightedge, shifted))
        base = paint(base, recolor(color(obj), newinds))
    return base

def dsl3(I):
    out = canvas(ZERO, shape(I))
    for obj in objects(I, T, T, T):
        c = color(obj)
        inds = toindices(obj)
        lo_row = llcorner(obj)  # (lowermost_row, leftmost_col)
        ur = urcorner(obj)      # (upper_row, rightmost_col)
        bottom = intersection(inds, hfrontier(lo_row))
        edge = intersection(inds, vfrontier(ur))
        upper = difference(inds, bottom)
        stay = intersection(upper, edge)
        go = difference(upper, stay)
        moved = shift(go, RIGHT)
        combined = merge((bottom, stay, moved))
        out = paint(out, recolor(c, combined))
    return out

def dsl4(I):
    res = canvas(ZERO, shape(I))
    for obj in objects(I, T, T, T):
        c = color(obj)
        inds = toindices(obj)
        btm = intersection(inds, hfrontier(llcorner(obj)))
        not_btm = difference(inds, btm)
        rcol = vfrontier(urcorner(obj))
        keep = intersection(not_btm, rcol)
        moved = shift(difference(not_btm, keep), RIGHT)
        res = paint(res, recolor(c, merge((btm, keep, moved))))
    return res

def dsl5(I):
    O = canvas(ZERO, shape(I))
    for obj in objects(I, T, T, T):
        inds = toindices(obj)
        bottom = intersection(inds, hfrontier(llcorner(obj)))
        upper = difference(inds, bottom)
        # preserve any part of upper already at object's rightmost column
        preserve = intersection(upper, vfrontier(urcorner(obj)))
        moveable = difference(upper, preserve)
        O = paint(O, recolor(color(obj), merge((bottom, preserve, shift(moveable, RIGHT)))))
    return O
```