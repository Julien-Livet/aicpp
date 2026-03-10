```python
def dsl1(I):
    # Dual completion: horizontal extrusion from a header row + vertical tiling from a bottom sample row
    objs = objects(I, T, F, T)

    # Horizontal extrusion across the widest horizontal nonzero band
    hls = sfilter(objs, hline)
    baseh = argmax(hls, width)
    uh = ulcorner(baseh)
    row_mask = difference(hfrontier(uh), ofcolor(I, ZERO))
    anchors_h = difference(vfrontier(uh), ofcolor(I, ZERO))
    sh_row = lbind(shift, row_mask)
    g_row = rbind(subtract, uh)
    mask_fn = compose(sh_row, g_row)
    vals = lbind(index, I)
    recol_fn = fork(recolor, vals, mask_fn)
    paints_h = mapply(recol_fn, anchors_h)

    # Vertical tiling using the bottommost row that intersects the leftmost tall vertical bar
    vls = sfilter(objs, vline)
    tall = sfilter(vls, compose(rbind(greater, ONE), height))
    basev = argmin(tall, leftmost)
    uv = ulcorner(basev)
    anchors_v = difference(vfrontier(uv), ofcolor(I, ZERO))
    ordered_v = order(anchors_v, first)
    sample_cross = last(ordered_v)
    sample_row_inds = difference(hfrontier(sample_cross), ofcolor(I, ZERO))
    sample_obj = toobject(sample_row_inds, I)
    sh_sample = lbind(shift, sample_obj)
    g_sample = rbind(subtract, sample_cross)
    place_sample = compose(sh_sample, g_sample)
    paints_v = mapply(place_sample, anchors_v)

    paints = combine(paints_h, paints_v)
    O = underpaint(I, paints)
    return O

def dsl2(I):
    # Horizontal extrusion only: use the widest horizontal band; fill its columns on each row using the color from the band's start column
    objs = objects(I, T, F, T)
    hls = sfilter(objs, hline)
    baseh = argmax(hls, width)
    uh = ulcorner(baseh)
    row_mask = difference(hfrontier(uh), ofcolor(I, ZERO))
    anchors = difference(vfrontier(uh), ofcolor(I, ZERO))
    sh_row = lbind(shift, row_mask)
    g_row = rbind(subtract, uh)
    mask_fn = compose(sh_row, g_row)
    vals = lbind(index, I)
    recol_fn = fork(recolor, vals, mask_fn)
    paints = mapply(recol_fn, anchors)
    O = underpaint(I, paints)
    return O

def dsl3(I):
    # Vertical tiling only: find the leftmost tall vertical bar and copy the bottommost sample row upward along it
    objs = objects(I, T, F, T)
    vls = sfilter(objs, vline)
    tall = sfilter(vls, compose(rbind(greater, ONE), height))
    basev = argmin(tall, leftmost)
    uv = ulcorner(basev)
    anchors = difference(vfrontier(uv), ofcolor(I, ZERO))
    ordered = order(anchors, first)
    sample_cross = last(ordered)
    sample_row_inds = difference(hfrontier(sample_cross), ofcolor(I, ZERO))
    sample_obj = toobject(sample_row_inds, I)
    sh = lbind(shift, sample_obj)
    g = rbind(subtract, sample_cross)
    place = compose(sh, g)
    paints = mapply(place, anchors)
    O = underpaint(I, paints)
    return O

def dsl4(I):
    # Dual completion variant: do vertical tiling first (from bottom sample row) then horizontal extrusion across the widest header
    objs = objects(I, T, F, T)

    # Vertical tiling from leftmost tall vertical bar
    vls = sfilter(objs, vline)
    tall = sfilter(vls, compose(rbind(greater, ONE), height))
    basev = argmin(tall, leftmost)
    uv = ulcorner(basev)
    anchors_v = difference(vfrontier(uv), ofcolor(I, ZERO))
    ordered_v = order(anchors_v, first)
    sample_cross = last(ordered_v)
    sample_row_inds = difference(hfrontier(sample_cross), ofcolor(I, ZERO))
    sample_obj = toobject(sample_row_inds, I)
    sh_sample = lbind(shift, sample_obj)
    g_sample = rbind(subtract, sample_cross)
    place_sample = compose(sh_sample, g_sample)
    paints_v = mapply(place_sample, anchors_v)

    # Horizontal extrusion across the widest horizontal band
    hls = sfilter(objs, hline)
    baseh = argmax(hls, width)
    uh = ulcorner(baseh)
    row_mask = difference(hfrontier(uh), ofcolor(I, ZERO))
    anchors_h = difference(vfrontier(uh), ofcolor(I, ZERO))
    sh_row = lbind(shift, row_mask)
    g_row = rbind(subtract, uh)
    mask_fn = compose(sh_row, g_row)
    vals = lbind(index, I)
    recol_fn = fork(recolor, vals, mask_fn)
    paints_h = mapply(recol_fn, anchors_h)

    paints = combine(paints_v, paints_h)
    O = underpaint(I, paints)
    return O
```