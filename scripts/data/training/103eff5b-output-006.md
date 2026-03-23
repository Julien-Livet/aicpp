```python
def dsl1(I):
    small = downscale(I, THREE)
    objs_s = objects(small, T, F, T)
    eightpix_s = ofcolor(small, EIGHT)
    base_s = cover(small, eightpix_s)
    eightobjs_s = colorfilter(objs_s, EIGHT)
    seeds_s = difference(objs_s, eightobjs_s)
    p2obj_s = compose(rbind(toobject, small), compose(initset, identity))
    comp_builder = compose(lbind(rbind, manhattan), p2obj_s)
    nearest_seed = chain(lbind(argmin, seeds_s), comp_builder, identity)
    recol_pix = fork(recolor, compose(color, nearest_seed), p2obj_s)
    recolored = apply(recol_pix, eightpix_s)
    small_colored = paint(base_s, merge(recolored))
    big = vupscale(hupscale(small_colored, THREE), THREE)
    eightpix_full = ofcolor(I, EIGHT)
    base_big = cover(I, eightpix_full)
    colored_obj = toobject(eightpix_full, big)
    O = paint(base_big, colored_obj)
    return O

def dsl2(I):
    objs = objects(I, T, F, T)
    eightobjs = colorfilter(objs, EIGHT)
    seeds = difference(objs, eightobjs)
    pix8 = ofcolor(I, EIGHT)
    base = cover(I, pix8)
    ul8 = ulcorner(pix8)
    tilegrid = crop(I, ul8, THREE_BY_THREE)
    tile = asobject(tilegrid)
    occs = occurrences(I, tile)
    place = compose(lbind(shift, tile), identity)
    tile_ul_point = compose(rbind(toobject, I), compose(initset, compose(ulcorner, place)))
    seed_ul_point = compose(rbind(toobject, I), compose(initset, ulcorner))
    manh_with_tileul = compose(lbind(rbind, manhattan), tile_ul_point)
    keyfunc = compose(manh_with_tileul, seed_ul_point)
    nearest_seed = chain(lbind(argmin, seeds), keyfunc, identity)
    recol_tile = fork(recolor, compose(color, nearest_seed), place)
    recolored = apply(recol_tile, occs)
    O = paint(base, merge(recolored))
    return O

def dsl3(I):
    objs = objects(I, T, F, T)
    eightpix = ofcolor(I, EIGHT)
    base = cover(I, eightpix)
    non8 = difference(objs, colorfilter(objs, EIGHT))
    bigseeds = merge(non8)
    scols = palette(bigseeds)
    to_group = compose(merge, compose(lbind(colorfilter, non8), identity))
    groups = apply(to_group, scols)
    p2obj = compose(rbind(toobject, I), compose(initset, identity))
    gcpoint = compose(rbind(toobject, I), compose(initset, compose(centerofmass, identity)))
    manh_with_p = compose(lbind(rbind, manhattan), p2obj)
    keyfunc = compose(manh_with_p, gcpoint)
    nearest_group = chain(lbind(argmin, groups), keyfunc, identity)
    recol_pix = fork(recolor, compose(color, nearest_group), p2obj)
    recolored = apply(recol_pix, eightpix)
    O = paint(base, merge(recolored))
    return O

def dsl4(I):
    objs = objects(I, T, F, T)
    eightpix = ofcolor(I, EIGHT)
    base = cover(I, eightpix)
    seeds = difference(objs, colorfilter(objs, EIGHT))
    per_seed_rays = fork(
        recolor,
        compose(color, identity),
        compose(lbind(intersection, eightpix), compose(merge, compose(lbind(apply, rbind(shoot, DOWN)), toindices)))
    )
    recolored = apply(per_seed_rays, seeds)
    O = paint(base, merge(recolored))
    return O

def dsl5(I):
    pix8 = ofcolor(I, EIGHT)
    base = cover(I, pix8)
    # seed template (3x3) at its own UL, stamped onto each 3x3 eight-tile occurrence by aligning UL corners
    ul8 = ulcorner(pix8)
    tile8 = asobject(crop(I, ul8, THREE_BY_THREE))
    # seed patch 3x3 around the UL of non-8s
    non8pix = difference(asindices(I), pix8)
    ulseed = ulcorner(non8pix)
    seedtile_grid = crop(I, ulseed, THREE_BY_THREE)
    seedtile = asobject(seedtile_grid)
    occs = occurrences(I, tile8)
    place8 = compose(lbind(shift, tile8), identity)
    dirf = compose(rbind(subtract, ulseed), compose(ulcorner, place8))
    const_seedtile = lbind(identity, seedtile)
    placed_seedtile = fork(shift, const_seedtile, dirf)
    # restrict to eight region and paint
    placed_in_8 = compose(rbind(toobject, I), compose(lbind(intersection, pix8), compose(toindices, placed_seedtile)))
    recolored = apply(placed_in_8, occs)
    O = paint(base, merge(recolored))
    return O
```