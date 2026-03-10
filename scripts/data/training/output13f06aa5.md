```python
def dsl1(I):
    # Rule: For each non-background singleton cell, choose the unique clear direction to a border (if any; else nearest),
    # paint that whole border with its color, draw a step-2 ray from the cell in that direction, and set any intersecting
    # colored border corners to 0.
    inds = asindices(I)
    tlc = ulcorner(inds); trc = urcorner(inds); blc = llcorner(inds)
    top = hfrontier(tlc); bot = hfrontier(blc); lef = vfrontier(tlc); rig = vfrontier(trc)
    bg = mostcolor(I)
    singles = sizefilter(objects(I, T, F, T), ONE)
    nonbg = difference(singles, colorfilter(singles, bg))

    def proc(O, o, gate):
        p = first(toindices(o))
        c = color(o)
        bu = difference(intersection(shoot(p, UP), inds), initset(p))
        bd = difference(intersection(shoot(p, DOWN), inds), initset(p))
        bl = difference(intersection(shoot(p, LEFT), inds), initset(p))
        br = difference(intersection(shoot(p, RIGHT), inds), initset(p))
        cu = equality(bu, intersection(bu, ofcolor(I, bg)))
        cd = equality(bd, intersection(bd, ofcolor(I, bg)))
        cl = equality(bl, intersection(bl, ofcolor(I, bg)))
        cr = equality(br, intersection(br, ofcolor(I, bg)))
        anyc = either(cu, either(cd, either(cl, cr)))

        du = manhattan(o, top); dd = manhattan(o, bot)
        dl = manhattan(o, lef); dr = manhattan(o, rig)
        up_best = both(flip(greater(du, dl)), both(flip(greater(du, dr)), flip(greater(du, dd))))
        dn_best = both(flip(greater(dd, du)), both(flip(greater(dd, dl)), flip(greater(dd, dr))))
        lf_best = both(flip(greater(dl, du)), both(flip(greater(dl, dr)), flip(greater(dl, dd))))
        rg_best = both(flip(greater(dr, du)), both(flip(greater(dr, dl)), flip(greater(dr, dd))))

        sel_u = either(cu, both(flip(anyc), up_best))
        sel_r = both(flip(sel_u), either(cr, both(flip(anyc), rg_best)))
        sel_l = both(flip(either(sel_u, sel_r)), either(cl, both(flip(anyc), lf_best)))
        sel_d = both(flip(either(either(sel_u, sel_r), sel_l)), either(cd, both(flip(anyc), dn_best)))

        O = branch(both(gate, sel_u), fill(O, c, top), O)
        O = branch(both(gate, sel_r), fill(O, c, rig), O)
        O = branch(both(gate, sel_l), fill(O, c, lef), O)
        O = branch(both(gate, sel_d), fill(O, c, bot), O)

        O = branch(both(gate, sel_u), fill(O, c, intersection(shoot(p, double(UP)), inds)), O)
        O = branch(both(gate, sel_r), fill(O, c, intersection(shoot(p, double(RIGHT)), inds)), O)
        O = branch(both(gate, sel_l), fill(O, c, intersection(shoot(p, double(LEFT)), inds)), O)
        O = branch(both(gate, sel_d), fill(O, c, intersection(shoot(p, double(DOWN)), inds)), O)
        return O, sel_u, sel_d, sel_l, sel_r

    O = I
    o1 = first(nonbg)
    o2 = last(nonbg)
    two = flip(equality(o1, o2))
    O, su1, sd1, sl1, sr1 = proc(O, o1, T)
    O, su2, sd2, sl2, sr2 = proc(O, o2, two)

    bt = either(su1, su2); bb = either(sd1, sd2)
    blf = either(sl1, sl2); brg = either(sr1, sr2)
    O = branch(both(bt, blf), fill(O, ZERO, intersection(top, lef)), O)
    O = branch(both(bt, brg), fill(O, ZERO, intersection(top, rig)), O)
    O = branch(both(bb, blf), fill(O, ZERO, intersection(bot, lef)), O)
    O = branch(both(bb, brg), fill(O, ZERO, intersection(bot, rig)), O)
    return O

def dsl2(I):
    # Variation: same as dsl1 but simpler direction choice: pick the first clear among U,L,R,D; fallback to nearest border if none clear.
    inds = asindices(I)
    tlc = ulcorner(inds); trc = urcorner(inds); blc = llcorner(inds)
    top = hfrontier(tlc); bot = hfrontier(blc); lef = vfrontier(tlc); rig = vfrontier(trc)
    bg = mostcolor(I)
    singles = sizefilter(objects(I, T, F, T), ONE)
    nonbg = difference(singles, colorfilter(singles, bg))

    def proc(O, o, gate):
        p = first(toindices(o)); c = color(o)
        bu = difference(intersection(shoot(p, UP), inds), initset(p))
        bd = difference(intersection(shoot(p, DOWN), inds), initset(p))
        bl = difference(intersection(shoot(p, LEFT), inds), initset(p))
        br = difference(intersection(shoot(p, RIGHT), inds), initset(p))
        cu = equality(bu, intersection(bu, ofcolor(I, bg)))
        cd = equality(bd, intersection(bd, ofcolor(I, bg)))
        cl = equality(bl, intersection(bl, ofcolor(I, bg)))
        cr = equality(br, intersection(br, ofcolor(I, bg)))
        anyc = either(cu, either(cd, either(cl, cr)))
        du = manhattan(o, top); dd = manhattan(o, bot); dl = manhattan(o, lef); dr = manhattan(o, rig)
        up_best = both(flip(greater(du, dl)), both(flip(greater(du, dr)), flip(greater(du, dd))))
        dn_best = both(flip(greater(dd, du)), both(flip(greater(dd, dl)), flip(greater(dd, dr))))
        lf_best = both(flip(greater(dl, du)), both(flip(greater(dl, dr)), flip(greater(dl, dd))))
        rg_best = both(flip(greater(dr, du)), both(flip(greater(dr, dl)), flip(greater(dr, dd))))

        # Priority U, L, R, D if clear; else nearest by distance with same priority
        su = cu
        sl = both(flip(su), cl)
        sr = both(flip(either(su, sl)), cr)
        sd = both(flip(either(either(su, sl), sr)), cd)
        su = either(su, both(flip(anyc), up_best))
        sl = either(sl, both(flip(anyc), lf_best))
        sr = either(sr, both(flip(anyc), rg_best))
        sd = either(sd, both(flip(anyc), dn_best))

        O = branch(both(gate, su), fill(O, c, top), O)
        O = branch(both(gate, sl), fill(O, c, lef), O)
        O = branch(both(gate, sr), fill(O, c, rig), O)
        O = branch(both(gate, sd), fill(O, c, bot), O)

        O = branch(both(gate, su), fill(O, c, intersection(shoot(p, double(UP)), inds)), O)
        O = branch(both(gate, sl), fill(O, c, intersection(shoot(p, double(LEFT)), inds)), O)
        O = branch(both(gate, sr), fill(O, c, intersection(shoot(p, double(RIGHT)), inds)), O)
        O = branch(both(gate, sd), fill(O, c, intersection(shoot(p, double(DOWN)), inds)), O)
        return O, su, sd, sl, sr

    O = I
    o1 = first(nonbg); o2 = last(nonbg)
    two = flip(equality(o1, o2))
    O, su1, sd1, sl1, sr1 = proc(O, o1, T)
    O, su2, sd2, sl2, sr2 = proc(O, o2, two)

    bt = either(su1, su2); bb = either(sd1, sd2)
    blf = either(sl1, sl2); brg = either(sr1, sr2)
    O = branch(both(bt, blf), fill(O, ZERO, intersection(top, lef)), O)
    O = branch(both(bt, brg), fill(O, ZERO, intersection(top, rig)), O)
    O = branch(both(bb, blf), fill(O, ZERO, intersection(bot, lef)), O)
    O = branch(both(bb, brg), fill(O, ZERO, intersection(bot, rig)), O)
    return O

def dsl3(I):
    # Fallback-focused: if no non-bg singletons, use leastcolor pivot; otherwise behave like dsl1 for up to two pivots.
    inds = asindices(I)
    tlc = ulcorner(inds); trc = urcorner(inds); blc = llcorner(inds)
    top = hfrontier(tlc); bot = hfrontier(blc); lef = vfrontier(tlc); rig = vfrontier(trc)
    bg = mostcolor(I)
    singles = sizefilter(objects(I, T, F, T), ONE)
    nonbg = difference(singles, colorfilter(singles, bg))

    def choose_pivots():
        # if nonbg has at least one, take first/last; else build a 1-cell object from leastcolor index
        cond = greater(size(nonbg), ZERO)
        return branch(cond, first(nonbg), toobject(ofcolor(I, leastcolor(I)), I)), branch(cond, last(nonbg), first(nonbg))

    o1, o2 = choose_pivots()
    two = flip(equality(o1, o2))

    def proc(O, o, gate):
        p = first(toindices(o)); c = color(o)
        bu = difference(intersection(shoot(p, UP), inds), initset(p))
        bd = difference(intersection(shoot(p, DOWN), inds), initset(p))
        bl = difference(intersection(shoot(p, LEFT), inds), initset(p))
        br = difference(intersection(shoot(p, RIGHT), inds), initset(p))
        cu = equality(bu, intersection(bu, ofcolor(I, bg)))
        cd = equality(bd, intersection(bd, ofcolor(I, bg)))
        cl = equality(bl, intersection(bl, ofcolor(I, bg)))
        cr = equality(br, intersection(br, ofcolor(I, bg)))
        anyc = either(cu, either(cd, either(cl, cr)))

        du = manhattan(o, top); dd = manhattan(o, bot)
        dl = manhattan(o, lef); dr = manhattan(o, rig)
        up_best = both(flip(greater(du, dl)), both(flip(greater(du, dr)), flip(greater(du, dd))))
        dn_best = both(flip(greater(dd, du)), both(flip(greater(dd, dl)), flip(greater(dd, dr))))
        lf_best = both(flip(greater(dl, du)), both(flip(greater(dl, dr)), flip(greater(dl, dd))))
        rg_best = both(flip(greater(dr, du)), both(flip(greater(dr, dl)), flip(greater(dr, dd))))

        sel_u = either(cu, both(flip(anyc), up_best))
        sel_r = both(flip(sel_u), either(cr, both(flip(anyc), rg_best)))
        sel_l = both(flip(either(sel_u, sel_r)), either(cl, both(flip(anyc), lf_best)))
        sel_d = both(flip(either(either(sel_u, sel_r), sel_l)), either(cd, both(flip(anyc), dn_best)))

        O = branch(both(gate, sel_u), fill(O, c, top), O)
        O = branch(both(gate, sel_r), fill(O, c, rig), O)
        O = branch(both(gate, sel_l), fill(O, c, lef), O)
        O = branch(both(gate, sel_d), fill(O, c, bot), O)
        O = branch(both(gate, sel_u), fill(O, c, intersection(shoot(p, double(UP)), inds)), O)
        O = branch(both(gate, sel_r), fill(O, c, intersection(shoot(p, double(RIGHT)), inds)), O)
        O = branch(both(gate, sel_l), fill(O, c, intersection(shoot(p, double(LEFT)), inds)), O)
        O = branch(both(gate, sel_d), fill(O, c, intersection(shoot(p, double(DOWN)), inds)), O)
        return O, sel_u, sel_d, sel_l, sel_r

    O = I
    O, su1, sd1, sl1, sr1 = proc(O, o1, T)
    O, su2, sd2, sl2, sr2 = proc(O, o2, two)

    bt = either(su1, su2); bb = either(sd1, sd2)
    blf = either(sl1, sl2); brg = either(sr1, sr2)
    O = branch(both(bt, blf), fill(O, ZERO, intersection(top, lef)), O)
    O = branch(both(bt, brg), fill(O, ZERO, intersection(top, rig)), O)
    O = branch(both(bb, blf), fill(O, ZERO, intersection(bot, lef)), O)
    O = branch(both(bb, brg), fill(O, ZERO, intersection(bot, rig)), O)
    return O

def dsl4(I):
    # Simpler hypothesis: for each non-bg singleton, paint only the chosen border (no step-2 ray), with ULRD clear-path priority;
    # zero any border-intersection corners.
    inds = asindices(I)
    tlc = ulcorner(inds); trc = urcorner(inds); blc = llcorner(inds)
    top = hfrontier(tlc); bot = hfrontier(blc); lef = vfrontier(tlc); rig = vfrontier(trc)
    bg = mostcolor(I)
    singles = sizefilter(objects(I, T, F, T), ONE)
    nonbg = difference(singles, colorfilter(singles, bg))

    def proc(O, o, gate):
        p = first(toindices(o)); c = color(o)
        bu = difference(intersection(shoot(p, UP), inds), initset(p))
        bd = difference(intersection(shoot(p, DOWN), inds), initset(p))
        bl = difference(intersection(shoot(p, LEFT), inds), initset(p))
        br = difference(intersection(shoot(p, RIGHT), inds), initset(p))
        cu = equality(bu, intersection(bu, ofcolor(I, bg)))
        cd = equality(bd, intersection(bd, ofcolor(I, bg)))
        cl = equality(bl, intersection(bl, ofcolor(I, bg)))
        cr = equality(br, intersection(br, ofcolor(I, bg)))

        su = cu
        sl = both(flip(su), cl)
        sr = both(flip(either(su, sl)), cr)
        sd = both(flip(either(either(su, sl), sr)), cd)

        O = branch(both(gate, su), fill(O, c, top), O)
        O = branch(both(gate, sl), fill(O, c, lef), O)
        O = branch(both(gate, sr), fill(O, c, rig), O)
        O = branch(both(gate, sd), fill(O, c, bot), O)
        return O, su, sd, sl, sr

    O = I
    o1 = first(nonbg); o2 = last(nonbg)
    two = flip(equality(o1, o2))
    O, su1, sd1, sl1, sr1 = proc(O, o1, T)
    O, su2, sd2, sl2, sr2 = proc(O, o2, two)

    bt = either(su1, su2); bb = either(sd1, sd2)
    blf = either(sl1, sl2); brg = either(sr1, sr2)
    O = branch(both(bt, blf), fill(O, ZERO, intersection(top, lef)), O)
    O = branch(both(bt, brg), fill(O, ZERO, intersection(top, rig)), O)
    O = branch(both(bb, blf), fill(O, ZERO, intersection(bot, lef)), O)
    O = branch(both(bb, brg), fill(O, ZERO, intersection(bot, rig)), O)
    return O

def dsl5(I):
    # Variant: like dsl1 but also extend the step-2 ray one-way (forward only) more aggressively:
    # for horizontal picks, propagate every 2 cells to the right; for vertical picks, propagate every 2 cells downward.
    inds = asindices(I)
    tlc = ulcorner(inds); trc = urcorner(inds); blc = llcorner(inds)
    top = hfrontier(tlc); bot = hfrontier(blc); lef = vfrontier(tlc); rig = vfrontier(trc)
    bg = mostcolor(I)
    singles = sizefilter(objects(I, T, F, T), ONE)
    nonbg = difference(singles, colorfilter(singles, bg))

    def proc(O, o, gate):
        p = first(toindices(o)); c = color(o)
        bu = difference(intersection(shoot(p, UP), inds), initset(p))
        bd = difference(intersection(shoot(p, DOWN), inds), initset(p))
        bl = difference(intersection(shoot(p, LEFT), inds), initset(p))
        br = difference(intersection(shoot(p, RIGHT), inds), initset(p))
        cu = equality(bu, intersection(bu, ofcolor(I, bg)))
        cd = equality(bd, intersection(bd, ofcolor(I, bg)))
        cl = equality(bl, intersection(bl, ofcolor(I, bg)))
        cr = equality(br, intersection(br, ofcolor(I, bg)))
        anyc = either(cu, either(cd, either(cl, cr)))

        du = manhattan(o, top); dd = manhattan(o, bot)
        dl = manhattan(o, lef); dr = manhattan(o, rig)
        up_best = both(flip(greater(du, dl)), both(flip(greater(du, dr)), flip(greater(du, dd))))
        dn_best = both(flip(greater(dd, du)), both(flip(greater(dd, dl)), flip(greater(dd, dr))))
        lf_best = both(flip(greater(dl, du)), both(flip(greater(dl, dr)), flip(greater(dl, dd))))
        rg_best = both(flip(greater(dr, du)), both(flip(greater(dr, dl)), flip(greater(dr, dd))))

        sel_u = either(cu, both(flip(anyc), up_best))
        sel_r = both(flip(sel_u), either(cr, both(flip(anyc), rg_best)))
        sel_l = both(flip(either(sel_u, sel_r)), either(cl, both(flip(anyc), lf_best)))
        sel_d = both(flip(either(either(sel_u, sel_r), sel_l)), either(cd, both(flip(anyc), dn_best)))

        O = branch(both(gate, sel_u), fill(O, c, top), O)
        O = branch(both(gate, sel_r), fill(O, c, rig), O)
        O = branch(both(gate, sel_l), fill(O, c, lef), O)
        O = branch(both(gate, sel_d), fill(O, c, bot), O)

        # Base step-2 ray in selected direction
        O = branch(both(gate, sel_u), fill(O, c, intersection(shoot(p, double(UP)), inds)), O)
        O = branch(both(gate, sel_r), fill(O, c, intersection(shoot(p, double(RIGHT)), inds)), O)
        O = branch(both(gate, sel_l), fill(O, c, intersection(shoot(p, double(LEFT)), inds)), O)
        O = branch(both(gate, sel_d), fill(O, c, intersection(shoot(p, double(DOWN)), inds)), O)

        # Extra "forward-only" propagation: if horizontal pick, extend to the right; if vertical pick, extend downward.
        O = branch(both(gate, sel_r), fill(O, c, intersection(shoot(p, double(RIGHT)), inds)), O)
        O = branch(both(gate, sel_l), fill(O, c, intersection(shoot(p, double(RIGHT)), inds)), O)
        O = branch(both(gate, sel_u), fill(O, c, intersection(shoot(p, double(DOWN)), inds)), O)
        O = branch(both(gate, sel_d), fill(O, c, intersection(shoot(p, double(DOWN)), inds)), O)
        return O, sel_u, sel_d, sel_l, sel_r

    O = I
    o1 = first(nonbg); o2 = last(nonbg)
    two = flip(equality(o1, o2))
    O, su1, sd1, sl1, sr1 = proc(O, o1, T)
    O, su2, sd2, sl2, sr2 = proc(O, o2, two)

    bt = either(su1, su2); bb = either(sd1, sd2)
    blf = either(sl1, sl2); brg = either(sr1, sr2)
    O = branch(both(bt, blf), fill(O, ZERO, intersection(top, lef)), O)
    O = branch(both(bt, brg), fill(O, ZERO, intersection(top, rig)), O)
    O = branch(both(bb, blf), fill(O, ZERO, intersection(bot, lef)), O)
    O = branch(both(bb, brg), fill(O, ZERO, intersection(bot, rig)), O)
    return O
```