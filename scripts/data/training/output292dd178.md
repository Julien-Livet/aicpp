```python
def dsl1(I):
    # Per-object interior fill (bbox minus the 1s)
    objs = colorfilter(fgpartition(I), ONE)
    interior = merge(apply(delta, objs))
    O = underfill(I, TWO, interior)
    return O

def dsl2(I):
    # Interior fill + directed spills from rows/cols that contain exactly one 1 (per object via edge-unions)
    objs = colorfilter(fgpartition(I), ONE)
    U = merge(objs)
    S = toindices(U)

    # Interior (per object)
    interior = merge(apply(delta, objs))

    # Row-singletons (compute across all 1s, then direct by object edge unions)
    row_sets = apply(compose(rbind(intersection, S), hfrontier), S)
    row_single_cells = merge(sizefilter(row_sets, ONE))  # indices of rows having exactly one 1

    # Union of all objects' left and right edge columns
    Lcols = merge(apply(vfrontier, apply(ulcorner, objs)))
    Rcols = merge(apply(vfrontier, apply(urcorner, objs)))

    row_leftedge_cells = intersection(row_single_cells, Lcols)
    row_rightedge_cells = intersection(row_single_cells, Rcols)

    spill_right = merge(apply(rbind(shoot, RIGHT), row_leftedge_cells))
    spill_left  = merge(apply(rbind(shoot, LEFT),  row_rightedge_cells))

    # Column-singletons (compute across all 1s, then direct by object top/bottom edge rows)
    col_sets = apply(compose(rbind(intersection, S), vfrontier), S)
    col_single_cells = merge(sizefilter(col_sets, ONE))  # indices of cols having exactly one 1

    TopRows = merge(apply(hfrontier, apply(ulcorner, objs)))
    BotRows = merge(apply(hfrontier, apply(llcorner, objs)))

    col_top_cells = intersection(col_single_cells, TopRows)
    col_bot_cells = intersection(col_single_cells, BotRows)

    spill_up   = merge(apply(rbind(shoot, UP),   col_top_cells))
    spill_down = merge(apply(rbind(shoot, DOWN), col_bot_cells))

    P = combine(interior, combine(spill_left, combine(spill_right, combine(spill_up, spill_down))))
    O = underfill(I, TWO, P)
    return O

def dsl3(I):
    # Interior fill + only column-singleton directed spills (up from top edge, down from bottom edge)
    objs = colorfilter(fgpartition(I), ONE)
    U = merge(objs)
    S = toindices(U)

    interior = merge(apply(delta, objs))

    col_sets = apply(compose(rbind(intersection, S), vfrontier), S)
    col_single_cells = merge(sizefilter(col_sets, ONE))

    TopRows = merge(apply(hfrontier, apply(ulcorner, objs)))
    BotRows = merge(apply(hfrontier, apply(llcorner, objs)))

    col_top_cells = intersection(col_single_cells, TopRows)
    col_bot_cells = intersection(col_single_cells, BotRows)

    spill_up   = merge(apply(rbind(shoot, UP),   col_top_cells))
    spill_down = merge(apply(rbind(shoot, DOWN), col_bot_cells))

    P = combine(interior, combine(spill_up, spill_down))
    O = underfill(I, TWO, P)
    return O

def dsl4(I):
    # Interior fill + only row-singleton directed spills (right from left edge, left from right edge)
    objs = colorfilter(fgpartition(I), ONE)
    U = merge(objs)
    S = toindices(U)

    interior = merge(apply(delta, objs))

    row_sets = apply(compose(rbind(intersection, S), hfrontier), S)
    row_single_cells = merge(sizefilter(row_sets, ONE))

    Lcols = merge(apply(vfrontier, apply(ulcorner, objs)))
    Rcols = merge(apply(vfrontier, apply(urcorner, objs)))

    row_leftedge_cells = intersection(row_single_cells, Lcols)
    row_rightedge_cells = intersection(row_single_cells, Rcols)

    spill_right = merge(apply(rbind(shoot, RIGHT), row_leftedge_cells))
    spill_left  = merge(apply(rbind(shoot, LEFT),  row_rightedge_cells))

    P = combine(interior, combine(spill_left, spill_right))
    O = underfill(I, TWO, P)
    return O

def dsl5(I):
    # Interior fill + conservative outward spill: use only the innermost vertical lines inside each object's bbox,
    # then extend outward on the side that meets the border (avoid filling both sides).
    objs = colorfilter(fgpartition(I), ONE)
    interior_per_obj = apply(delta, objs)
    interior = merge(interior_per_obj)

    # Columns through interior cells
    VR_inside = merge(apply(vfrontier, interior))
    # All object backdrops (for masking inside)
    BB = merge(apply(backdrop, objs))
    # Only take parts of those columns that lie outside any object's bbox
    outside_cols = difference(VR_inside, BB)
    P = combine(interior, outside_cols)
    O = underfill(I, TWO, P)
    return O
```