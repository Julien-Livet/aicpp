```python
def dsl1(I):
    bg = mostcolor(I)
    obs = objects(I, F, F, T)
    def nbcount_obj(o):
        g = subgrid(toindices(o), I)
        nonbg = remove(bg, palette(g))
        return size(nonbg)
    motif_obj = argmax(obs, nbcount_obj)
    rest = remove(motif_obj, obs)
    mask_obj = argmin(rest, nbcount_obj)
    motif = subgrid(toindices(motif_obj), I)
    mask = subgrid(toindices(mask_obj), I)
    th = height(motif); tw = width(motif)
    mh = height(mask); mw = width(mask)
    row = power(rbind(hconcat, motif), subtract(mw, ONE))(motif)
    tiled = power(rbind(vconcat, row), subtract(mh, ONE))(row)
    exp_mask = hupscale(vupscale(mask, th), tw)
    O = fill(tiled, bg, ofcolor(exp_mask, bg))
    return O

def dsl2(I):
    bg = mostcolor(I)
    obs = objects(I, F, F, T)
    def square_score(o):
        g = subgrid(toindices(o), I)
        h = height(g); w = width(g)
        eq = equality(h, w)
        return branch(eq, multiply(h, w), ZERO)
    primary = argmax(obs, square_score)
    alt = argmax(obs, lambda o: size(remove(bg, palette(subgrid(toindices(o), I)))))
    motif_obj = branch(equality(square_score(primary), ZERO), alt, primary)
    others = remove(motif_obj, obs)
    def nbcount_obj(o):
        g = subgrid(toindices(o), I)
        return size(remove(bg, palette(g)))
    mask_obj = argmin(others, nbcount_obj)
    motif = subgrid(toindices(motif_obj), I)
    mask = subgrid(toindices(mask_obj), I)
    th = height(motif); tw = width(motif)
    mh = height(mask); mw = width(mask)
    row = power(rbind(hconcat, motif), subtract(mw, ONE))(motif)
    tiled = power(rbind(vconcat, row), subtract(mh, ONE))(row)
    exp_mask = hupscale(vupscale(mask, th), tw)
    O = fill(tiled, bg, ofcolor(exp_mask, bg))
    return O

def dsl3(I):
    bg = mostcolor(I)
    has8 = contained(EIGHT, palette(I))
    has9 = contained(NINE, palette(I))
    motif_guess = branch(has8, subgrid(ofcolor(I, EIGHT), I),
                   branch(has9, subgrid(ofcolor(I, NINE), I),
                          subgrid(toindices(argmax(objects(I, F, F, T), lambda o: size(remove(bg, palette(subgrid(toindices(o), I)))))), I)))
    mot_pal = remove(bg, palette(motif_guess))
    all_pal = remove(bg, palette(I))
    mask_cols = difference(all_pal, mot_pal)
    mc = first(mask_cols)
    motif = motif_guess
    mask = subgrid(ofcolor(I, mc), I)
    th = height(motif); tw = width(motif)
    mh = height(mask); mw = width(mask)
    row = power(rbind(hconcat, motif), subtract(mw, ONE))(motif)
    tiled = power(rbind(vconcat, row), subtract(mh, ONE))(row)
    exp_mask = hupscale(vupscale(mask, th), tw)
    O = fill(tiled, bg, ofcolor(exp_mask, bg))
    return O

def dsl4(I):
    bg = mostcolor(I)
    obs = objects(I, F, F, T)
    def richness(o):
        g = subgrid(toindices(o), I)
        return size(remove(bg, palette(g)))
    motif_obj = argmax(obs, richness)
    rest = remove(motif_obj, obs)
    mask_obj = argmin(rest, richness)
    motif = subgrid(toindices(motif_obj), I)
    mask = subgrid(toindices(mask_obj), I)
    th = height(motif); tw = width(motif)
    mh = height(mask); mw = width(mask)
    row = power(rbind(hconcat, motif), subtract(mw, ONE))(motif)
    O = power(rbind(vconcat, row), subtract(mh, ONE))(row)
    return O

def dsl5(I):
    bg = mostcolor(I)
    obs = objects(I, F, F, T)
    # pick motif as multi-color object with the smallest area (compact tile), mask as largest mono-color object
    def ncolors(o):
        g = subgrid(toindices(o), I)
        return size(remove(bg, palette(g)))
    def area(o):
        g = subgrid(toindices(o), I)
        return multiply(height(g), width(g))
    multi = mfilter(obs, lambda o: greater(ncolors(o), ONE))
    mono = mfilter(obs, lambda o: equality(ncolors(o), ONE))
    motif_obj = argmin(multi, area)
    mask_obj = argmax(mono, area)
    motif = subgrid(toindices(motif_obj), I)
    mask = subgrid(toindices(mask_obj), I)
    th = height(motif); tw = width(motif)
    mh = height(mask); mw = width(mask)
    row = power(rbind(hconcat, motif), subtract(mw, ONE))(motif)
    tiled = power(rbind(vconcat, row), subtract(mh, ONE))(row)
    exp_mask = hupscale(vupscale(mask, th), tw)
    O = fill(tiled, bg, ofcolor(exp_mask, bg))
    return O
```