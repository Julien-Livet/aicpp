```python
def dsl1(I):
    eights = ofcolor(I, EIGHT)
    objs = objects(I, T, F, T)
    seeds = difference(objs, colorfilter(objs, EIGHT))
    base = cover(I, eights)
    comp_builder = compose(lbind(rbind, manhattan), initset)
    nearest_seed = chain(lbind(argmin, seeds), comp_builder, identity)
    nearest_color = compose(color, nearest_seed)
    point_patch = compose(initset, identity)
    recol_point = fork(recolor, nearest_color, point_patch)
    recolored_points = apply(recol_point, eights)
    O = paint(base, merge(recolored_points))
    return O

def dsl2(I):
    eights = ofcolor(I, EIGHT)
    objs = objects(I, T, F, T)
    seeds = difference(objs, colorfilter(objs, EIGHT))
    base = cover(I, eights)
    comp_builder = compose(lbind(rbind, manhattan), initset)
    nearest_seed = chain(lbind(argmin, seeds), comp_builder, identity)
    pred_builder = lbind(matcher, nearest_seed)
    filter_points = lbind(sfilter, eights)
    assigned = chain(filter_points, pred_builder, identity)
    recolor_for_seed = fork(recolor, compose(color, identity), assigned)
    recolored = apply(recolor_for_seed, seeds)
    O = paint(base, merge(recolored))
    return O

def dsl3(I):
    eights = ofcolor(I, EIGHT)
    objs = objects(I, T, F, T)
    seeds = difference(objs, colorfilter(objs, EIGHT))
    base = cover(I, eights)
    comp_builder = compose(lbind(rbind, manhattan), initset)
    nearest_seed = chain(first, lbind(order, seeds), comp_builder)
    nearest_color = compose(color, nearest_seed)
    point_patch = compose(initset, identity)
    recol_point = fork(recolor, nearest_color, point_patch)
    recolored_points = apply(recol_point, eights)
    O = paint(base, merge(recolored_points))
    return O

def dsl4(I):
    eights = ofcolor(I, EIGHT)
    objs = objects(I, T, F, T)
    seeds = difference(objs, colorfilter(objs, EIGHT))
    base = cover(I, eights)
    comp_builder = compose(lbind(rbind, manhattan), initset)
    nearest_seed = chain(lbind(argmin, seeds), comp_builder, identity)
    nearest_color = compose(color, nearest_seed)
    point_patch = compose(initset, identity)
    recol_point = fork(recolor, nearest_color, point_patch)
    recolored_points = apply(recol_point, eights)
    mask = merge(recolored_points)
    O = underpaint(base, mask)
    return O

def dsl5(I):
    eights = ofcolor(I, EIGHT)
    objs = objects(I, T, F, T)
    seeds = difference(objs, colorfilter(objs, EIGHT))
    base = cover(I, eights)
    pointobj = compose(rbind(toobject, I), initset)
    comp_builder = compose(lbind(rbind, manhattan), pointobj)
    nearest_seed = chain(lbind(argmin, seeds), comp_builder, identity)
    nearest_color = compose(color, nearest_seed)
    point_patch = compose(initset, identity)
    recol_point = fork(recolor, nearest_color, point_patch)
    recolored_points = apply(recol_point, eights)
    O = paint(base, merge(recolored_points))
    return O
```