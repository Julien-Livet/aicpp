```python
def dsl1(I):
    idx8 = ofcolor(I, EIGHT)
    rmin = uppermost(idx8)
    rmax = lowermost(idx8)
    cmin = leftmost(idx8)
    cmax = rightmost(idx8)

    rows = interval(rmin, increment(rmax), 1)
    cols = interval(cmin, increment(cmax), 1)
    ones = ofcolor(I, ONE)

    # vertical arms (up)
    up_starts = prapply(astuple, initset(decrement(rmin)), cols)
    up_rays = merge(prapply(shoot, up_starts, initset(UP)))
    up_barriers = intersection(ones, up_rays)
    up_shadows = merge(prapply(shoot, up_barriers, initset(UP)))
    fill_up = difference(up_rays, up_shadows)

    # vertical arms (down)
    down_starts = prapply(astuple, initset(increment(rmax)), cols)
    down_rays = merge(prapply(shoot, down_starts, initset(DOWN)))
    down_barriers = intersection(ones, down_rays)
    down_shadows = merge(prapply(shoot, down_barriers, initset(DOWN)))
    fill_down = difference(down_rays, down_shadows)

    # horizontal arms (left)
    left_starts = prapply(astuple, rows, initset(decrement(cmin)))
    left_rays = merge(prapply(shoot, left_starts, initset(LEFT)))
    left_barriers = intersection(ones, left_rays)
    left_shadows = merge(prapply(shoot, left_barriers, initset(LEFT)))
    fill_left = difference(left_rays, left_shadows)

    # horizontal arms (right)
    right_starts = prapply(astuple, rows, initset(increment(cmax)))
    right_rays = merge(prapply(shoot, right_starts, initset(RIGHT)))
    right_barriers = intersection(ones, right_rays)
    right_shadows = merge(prapply(shoot, right_barriers, initset(RIGHT)))
    fill_right = difference(right_rays, right_shadows)

    band = combine(combine(fill_up, fill_down), combine(fill_left, fill_right))

    allow = combine(ofcolor(I, ZERO), ofcolor(I, TWO))
    targets = intersection(band, allow)
    obj = recolor(FOUR, toobject(targets, I))
    O = paint(I, obj)
    return O


def dsl2(I):
    idx8 = ofcolor(I, EIGHT)
    rmin = uppermost(idx8)
    rmax = lowermost(idx8)
    cmin = leftmost(idx8)
    cmax = rightmost(idx8)

    rows = interval(rmin, increment(rmax), 1)
    cols = interval(cmin, increment(cmax), 1)
    ones = ofcolor(I, ONE)

    # build all directional rays once
    up_rays = merge(prapply(shoot, prapply(astuple, initset(decrement(rmin)), cols), initset(UP)))
    down_rays = merge(prapply(shoot, prapply(astuple, initset(increment(rmax)), cols), initset(DOWN)))
    left_rays = merge(prapply(shoot, prapply(astuple, rows, initset(decrement(cmin))), initset(LEFT)))
    right_rays = merge(prapply(shoot, prapply(astuple, rows, initset(increment(cmax))), initset(RIGHT)))

    # shadows from 1's (barriers) in corresponding directions
    up_shadows = merge(prapply(shoot, intersection(ones, up_rays), initset(UP)))
    down_shadows = merge(prapply(shoot, intersection(ones, down_rays), initset(DOWN)))
    left_shadows = merge(prapply(shoot, intersection(ones, left_rays), initset(LEFT)))
    right_shadows = merge(prapply(shoot, intersection(ones, right_rays), initset(RIGHT)))

    # reachable arms (barrier-limited)
    v_band = combine(difference(up_rays, up_shadows), difference(down_rays, down_shadows))
    h_band = combine(difference(left_rays, left_shadows), difference(right_rays, right_shadows))
    band = combine(v_band, h_band)

    mod = combine(ofcolor(I, ZERO), ofcolor(I, TWO))
    targets = intersection(band, mod)
    obj = recolor(FOUR, toobject(targets, I))
    O = paint(I, obj)
    return O


def dsl3(I):
    idx8 = ofcolor(I, EIGHT)
    rmin = uppermost(idx8)
    rmax = lowermost(idx8)
    cmin = leftmost(idx8)
    cmax = rightmost(idx8)

    rows = interval(rmin, increment(rmax), 1)
    cols = interval(cmin, increment(cmax), 1)
    ones = ofcolor(I, ONE)

    # full unpruned band (rows and columns spanning the 8's bbox)
    row_starts = prapply(astuple, rows, initset(0))
    col_starts = prapply(astuple, initset(0), cols)
    row_lines = merge(prapply(shoot, row_starts, initset(RIGHT)))
    col_lines = merge(prapply(shoot, col_starts, initset(DOWN)))
    band_full = combine(row_lines, col_lines)

    # build side-specific rays just to compute barrier shadows away from the bbox
    up_rays = merge(prapply(shoot, prapply(astuple, initset(decrement(rmin)), cols), initset(UP)))
    down_rays = merge(prapply(shoot, prapply(astuple, initset(increment(rmax)), cols), initset(DOWN)))
    left_rays = merge(prapply(shoot, prapply(astuple, rows, initset(decrement(cmin))), initset(LEFT)))
    right_rays = merge(prapply(shoot, prapply(astuple, rows, initset(increment(cmax))), initset(RIGHT)))

    up_shadows = merge(prapply(shoot, intersection(ones, up_rays), initset(UP)))
    down_shadows = merge(prapply(shoot, intersection(ones, down_rays), initset(DOWN)))
    left_shadows = merge(prapply(shoot, intersection(ones, left_rays), initset(LEFT)))
    right_shadows = merge(prapply(shoot, intersection(ones, right_rays), initset(RIGHT)))

    # prune unreachable areas beyond the nearest 1 in each row/column
    pruned = difference(band_full, combine(combine(up_shadows, down_shadows), combine(left_shadows, right_shadows)))

    # do not alter 1 or 8; only recolor 0 and 2 within pruned band
    mod = combine(ofcolor(I, ZERO), ofcolor(I, TWO))
    targets = intersection(pruned, mod)
    obj = recolor(FOUR, toobject(targets, I))
    O = paint(I, obj)
    return O


def dsl4(I):
    # same as dsl1 but performed in a single recolor op
    idx8 = ofcolor(I, EIGHT)
    rmin = uppermost(idx8)
    rmax = lowermost(idx8)
    cmin = leftmost(idx8)
    cmax = rightmost(idx8)

    rows = interval(rmin, increment(rmax), 1)
    cols = interval(cmin, increment(cmax), 1)
    ones = ofcolor(I, ONE)

    up_rays = merge(prapply(shoot, prapply(astuple, initset(decrement(rmin)), cols), initset(UP)))
    up_shadows = merge(prapply(shoot, intersection(ones, up_rays), initset(UP)))
    fill_up = difference(up_rays, up_shadows)

    down_rays = merge(prapply(shoot, prapply(astuple, initset(increment(rmax)), cols), initset(DOWN)))
    down_shadows = merge(prapply(shoot, intersection(ones, down_rays), initset(DOWN)))
    fill_down = difference(down_rays, down_shadows)

    left_rays = merge(prapply(shoot, prapply(astuple, rows, initset(decrement(cmin))), initset(LEFT)))
    left_shadows = merge(prapply(shoot, intersection(ones, left_rays), initset(LEFT)))
    fill_left = difference(left_rays, left_shadows)

    right_rays = merge(prapply(shoot, prapply(astuple, rows, initset(increment(cmax))), initset(RIGHT)))
    right_shadows = merge(prapply(shoot, intersection(ones, right_rays), initset(RIGHT)))
    fill_right = difference(right_rays, right_shadows)

    band = combine(combine(fill_up, fill_down), combine(fill_left, fill_right))
    targets = intersection(band, combine(ofcolor(I, ZERO), ofcolor(I, TWO)))
    O = paint(I, recolor(FOUR, toobject(targets, I)))
    return O
```