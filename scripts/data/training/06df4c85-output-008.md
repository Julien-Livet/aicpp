```python
def dsl1(I):
    # Global scale-space: downscale to unitize seeds, fill between same-color seeds, upscale, and underpaint on original
    D = downscale(I, TWO)
    lcd = mostcolor(D)
    obsd = objects(D, T, F, T)
    seedsd = sizefilter(difference(obsd, colorfilter(obsd, lcd)), ONE)
    prs = product(seedsd, seedsd)
    samec = fork(equality, compose(color, first), compose(color, last))
    samerow = fork(equality, compose(uppermost, first), compose(uppermost, last))
    samecol = fork(equality, compose(leftmost, first), compose(leftmost, last))
    hprs = sfilter(prs, fork(both, samec, samerow))
    vprs = sfilter(prs, fork(both, samec, samecol))
    hfill = mapply(fork(recolor, compose(color, first), compose(inbox, fork(combine, first, last))), hprs)
    vfill = mapply(fork(recolor, compose(color, first), compose(inbox, fork(combine, first, last))), vprs)
    J = underpaint(D, combine(hfill, vfill))
    U = upscale(J, TWO)
    O = underpaint(I, asobject(U))
    return O

def dsl2(I):
    # Geometric rotation: do horizontal fills, rotate, repeat, rotate back, and merge
    lc = mostcolor(I)
    obs = objects(I, T, F, T)
    seeds = sizefilter(difference(obs, colorfilter(obs, lc)), FOUR)
    prs = product(seeds, seeds)
    samec = fork(equality, compose(color, first), compose(color, last))
    samerow = fork(equality, compose(uppermost, first), compose(uppermost, last))
    hprs = sfilter(prs, fork(both, samec, samerow))
    hfill = mapply(fork(recolor, compose(color, first), compose(inbox, fork(combine, first, last))), hprs)
    J = underpaint(I, hfill)
    R = rot90(J)
    lcr = mostcolor(R)
    obsr = objects(R, T, F, T)
    seedsr = sizefilter(difference(obsr, colorfilter(obsr, lcr)), FOUR)
    prsr = product(seedsr, seedsr)
    samecr = fork(equality, compose(color, first), compose(color, last))
    samerowr = fork(equality, compose(uppermost, first), compose(uppermost, last))
    hrprs = sfilter(prsr, fork(both, samecr, samerowr))
    rfill = mapply(fork(recolor, compose(color, first), compose(inbox, fork(combine, first, last))), hrprs)
    RR = underpaint(R, rfill)
    O = underpaint(J, asobject(rot270(RR)))
    return O

def dsl3(I):
    # Color filtering: remove lattice color for detection, then connect same-color seeds via bounding rectangles
    lc = mostcolor(I)
    base = replace(I, lc, ZERO)
    obs = objects(base, T, F, T)
    seeds = sizefilter(obs, FOUR)
    prs = product(seeds, seeds)
    samec = fork(equality, compose(color, first), compose(color, last))
    samerow = fork(equality, compose(uppermost, first), compose(uppermost, last))
    samecol = fork(equality, compose(leftmost, first), compose(leftmost, last))
    hprs = sfilter(prs, fork(both, samec, samerow))
    vprs = sfilter(prs, fork(both, samec, samecol))
    hfill = mapply(fork(recolor, compose(color, first), compose(inbox, fork(combine, first, last))), hprs)
    vfill = mapply(fork(recolor, compose(color, first), compose(inbox, fork(combine, first, last))), vprs)
    O = underpaint(I, combine(hfill, vfill))
    return O

def dsl4(I):
    # Masked frontiers: intersect full row/column frontiers with pairwise bounding rectangles of same-color seeds
    lc = mostcolor(I)
    obs = objects(I, T, F, T)
    seeds = sizefilter(difference(obs, colorfilter(obs, lc)), FOUR)
    prs = product(seeds, seeds)
    samec = fork(equality, compose(color, first), compose(color, last))
    samerow = fork(equality, compose(uppermost, first), compose(uppermost, last))
    samecol = fork(equality, compose(leftmost, first), compose(leftmost, last))
    rect = compose(inbox, fork(combine, first, last))
    rowline = compose(hfrontier, center)
    colline = compose(vfrontier, center)
    hprs = sfilter(prs, fork(both, samec, samerow))
    vprs = sfilter(prs, fork(both, samec, samecol))
    hmask = mapply(fork(recolor, compose(color, first), fork(intersection, rect, compose(rowline, first))), hprs)
    vmask = mapply(fork(recolor, compose(color, first), fork(intersection, rect, compose(colline, first))), vprs)
    O = underpaint(I, combine(hmask, vmask))
    return O

def dsl5(I):
    # Relational outlines: draw box outlines between aligned same-color seeds (both row and column)
    lc = mostcolor(I)
    obs = objects(I, T, F, T)
    seeds = sizefilter(difference(obs, colorfilter(obs, lc)), FOUR)
    prs = product(seeds, seeds)
    samec = fork(equality, compose(color, first), compose(color, last))
    hprs = sfilter(prs, fork(both, samec, fork(hmatching, first, last)))
    vprs = sfilter(prs, fork(both, samec, fork(vmatching, first, last)))
    hbox = mapply(fork(recolor, compose(color, first), compose(box, fork(combine, first, last))), hprs)
    vbox = mapply(fork(recolor, compose(color, first), compose(box, fork(combine, first, last))), vprs)
    O = underpaint(I, combine(hbox, vbox))
    return O
```