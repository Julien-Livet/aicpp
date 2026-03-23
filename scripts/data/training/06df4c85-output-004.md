```python
def dsl1(I):
    # Global: bidirectional row/column bridging via rotation, horizontal-first to resolve overlaps
    lc = mostcolor(I)
    obs = objects(I, T, F, T)
    seeds = sizefilter(difference(obs, colorfilter(obs, lc)), 4)
    prs = product(seeds, seeds)
    samec = fork(equality, compose(color, first), compose(color, last))
    hmat = fork(hmatching, first, last)
    hp = sfilter(prs, fork(both, samec, hmat))
    hadd = mapply(fork(recolor, compose(color, first), compose(inbox, fork(combine, first, last))), hp)
    H = underpaint(I, hadd)
    R = rot90(I)
    lcr = mostcolor(R)
    obsr = objects(R, T, F, T)
    seedsr = sizefilter(difference(obsr, colorfilter(obsr, lcr)), 4)
    prsr = product(seedsr, seedsr)
    samecr = fork(equality, compose(color, first), compose(color, last))
    hmatr = fork(hmatching, first, last)
    hpr = sfilter(prsr, fork(both, samecr, hmatr))
    addr = mapply(fork(recolor, compose(color, first), compose(inbox, fork(combine, first, last))), hpr)
    HR = underpaint(R, addr)
    V = rot270(HR)
    O = underpaint(H, asobject(V))
    return O

def dsl2(I):
    # Object extraction: same-row and same-col rectangular fills from 2x2 seeds
    lc = mostcolor(I)
    obs = objects(I, T, F, T)
    seeds = sizefilter(difference(obs, colorfilter(obs, lc)), 4)
    prs = product(seeds, seeds)
    samec = fork(equality, compose(color, first), compose(color, last))
    samer = fork(equality, compose(uppermost, first), compose(uppermost, last))
    samek = fork(equality, compose(leftmost, first), compose(leftmost, last))
    hp = sfilter(prs, fork(both, samec, samer))
    vp = sfilter(prs, fork(both, samec, samek))
    hin = mapply(fork(recolor, compose(color, first), compose(inbox, fork(combine, first, last))), hp)
    vin = mapply(fork(recolor, compose(color, first), compose(inbox, fork(combine, first, last))), vp)
    O = underpaint(I, combine(hin, vin))
    return O

def dsl3(I):
    # Geometric: fill the interior between aligned same-color seeds using delta (interior of bbox)
    lc = mostcolor(I)
    obs = objects(I, T, F, T)
    seeds = sizefilter(difference(obs, colorfilter(obs, lc)), 4)
    prs = product(seeds, seeds)
    samec = fork(equality, compose(color, first), compose(color, last))
    hrow = fork(equality, compose(uppermost, first), compose(uppermost, last))
    vcol = fork(equality, compose(leftmost, first), compose(leftmost, last))
    hp = sfilter(prs, fork(both, samec, hrow))
    vp = sfilter(prs, fork(both, samec, vcol))
    hfill = mapply(fork(recolor, compose(color, first), compose(delta, fork(combine, first, last))), hp)
    vfill = mapply(fork(recolor, compose(color, first), compose(delta, fork(combine, first, last))), vp)
    O = underpaint(I, combine(hfill, vfill))
    return O

def dsl4(I):
    # Color filtering: per-color closure along rows then along cols, merged
    lc = mostcolor(I)
    obs = objects(I, T, F, T)
    seeds = sizefilter(difference(obs, colorfilter(obs, lc)), 4)
    prs = product(seeds, seeds)
    samec = fork(equality, compose(color, first), compose(color, last))
    hrow = fork(equality, compose(uppermost, first), compose(uppermost, last))
    vcol = fork(equality, compose(leftmost, first), compose(leftmost, last))
    hp = sfilter(prs, fork(both, samec, hrow))
    vp = sfilter(prs, fork(both, samec, vcol))
    hcover = mapply(fork(recolor, compose(color, first), compose(backdrop, fork(combine, first, last))), hp)
    vcover = mapply(fork(recolor, compose(color, first), compose(backdrop, fork(combine, first, last))), vp)
    O = underpaint(I, combine(hcover, vcover))
    return O

def dsl5(I):
    # Relational/structural: use row/col sharing (hmatching/vmatching) with rectangle fill; rotate for verticals
    lc = mostcolor(I)
    obs = objects(I, T, F, T)
    seeds = sizefilter(difference(obs, colorfilter(obs, lc)), 4)
    prs = product(seeds, seeds)
    samec = fork(equality, compose(color, first), compose(color, last))
    hmat = fork(hmatching, first, last)
    hp = sfilter(prs, fork(both, samec, hmat))
    hadd = mapply(fork(recolor, compose(color, first), compose(inbox, fork(combine, first, last))), hp)
    base = underpaint(I, hadd)
    R = rot90(I)
    lcr = mostcolor(R)
    obsr = objects(R, T, F, T)
    seedsr = sizefilter(difference(obsr, colorfilter(obsr, lcr)), 4)
    prsr = product(seedsr, seedsr)
    samecr = fork(equality, compose(color, first), compose(color, last))
    hmatr = fork(hmatching, first, last)
    hpr = sfilter(prsr, fork(both, samecr, hmatr))
    addr = mapply(fork(recolor, compose(color, first), compose(inbox, fork(combine, first, last))), hpr)
    HR = underpaint(R, addr)
    V = rot270(HR)
    O = underpaint(base, asobject(V))
    return O
```