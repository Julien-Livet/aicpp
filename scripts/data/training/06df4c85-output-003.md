```python
def dsl1(I):
    # Global transformation: horizontal bridging on I and its 90° rotation, then merge
    lc = mostcolor(I)
    obs = objects(I, T, F, T)
    seeds = sizefilter(difference(obs, colorfilter(obs, lc)), 4)
    prs = product(seeds, seeds)
    samec = fork(equality, compose(color, first), compose(color, last))
    samer = fork(equality, compose(uppermost, first), compose(uppermost, last))
    hp = sfilter(prs, fork(both, samec, samer))
    addh = mapply(fork(recolor, compose(color, first), compose(inbox, fork(combine, first, last))), hp)
    H = underpaint(I, addh)
    R = rot90(I)
    lcr = mostcolor(R)
    obsr = objects(R, T, F, T)
    seedsr = sizefilter(difference(obsr, colorfilter(obsr, lcr)), 4)
    prsr = product(seedsr, seedsr)
    samecr = fork(equality, compose(color, first), compose(color, last))
    samerr = fork(equality, compose(uppermost, first), compose(uppermost, last))
    hpr = sfilter(prsr, fork(both, samecr, samerr))
    addr = mapply(fork(recolor, compose(color, first), compose(inbox, fork(combine, first, last))), hpr)
    HR = underpaint(R, addr)
    V = rot270(HR)
    O = underpaint(H, asobject(V))
    return O

def dsl2(I):
    # Object extraction: bridge same-color 2x2 seeds across same row/col using rectangular fill
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
    # Geometric reasoning: use interior (delta) of bounding rectangles between aligned seeds
    lc = mostcolor(I)
    obs = objects(I, T, F, T)
    seeds = sizefilter(difference(obs, colorfilter(obs, lc)), 4)
    prs = product(seeds, seeds)
    samec = fork(equality, compose(color, first), compose(color, last))
    samer = fork(equality, compose(uppermost, first), compose(uppermost, last))
    samek = fork(equality, compose(leftmost, first), compose(leftmost, last))
    hp = sfilter(prs, fork(both, samec, samer))
    vp = sfilter(prs, fork(both, samec, samek))
    hfill = mapply(fork(recolor, compose(color, first), compose(delta, fork(combine, first, last))), hp)
    vfill = mapply(fork(recolor, compose(color, first), compose(delta, fork(combine, first, last))), vp)
    O = underpaint(I, combine(hfill, vfill))
    return O

def dsl4(I):
    # Color filtering: per-color horizontal/vertical closure via backdrop, merged across colors
    lc = mostcolor(I)
    obs = objects(I, T, F, T)
    seeds = sizefilter(difference(obs, colorfilter(obs, lc)), 4)
    prs = product(seeds, seeds)
    samec = fork(equality, compose(color, first), compose(color, last))
    samer = fork(equality, compose(uppermost, first), compose(uppermost, last))
    samek = fork(equality, compose(leftmost, first), compose(leftmost, last))
    aligned = sfilter(prs, fork(both, samec, fork(either, samer, samek)))
    add = mapply(fork(recolor, compose(color, first), compose(backdrop, fork(combine, first, last))), aligned)
    O = underpaint(I, add)
    return O

def dsl5(I):
    # Relational/structural: overlap matching (row/col sharing) with rectangular fill and symmetry
    lc = mostcolor(I)
    obs = objects(I, T, F, T)
    seeds = sizefilter(difference(obs, colorfilter(obs, lc)), 4)
    prs = product(seeds, seeds)
    samec = fork(equality, compose(color, first), compose(color, last))
    hmat = fork(hmatching, first, last)
    vmat = fork(vmatching, first, last)
    hp = sfilter(prs, fork(both, samec, hmat))
    vp = sfilter(prs, fork(both, samec, vmat))
    hadd = mapply(fork(recolor, compose(color, first), compose(inbox, fork(combine, first, last))), hp)
    vadd = mapply(fork(recolor, compose(color, first), compose(inbox, fork(combine, first, last))), vp)
    base = underpaint(I, combine(hadd, vadd))
    R = rot180(I)
    lcr = mostcolor(R)
    obsr = objects(R, T, F, T)
    seedsr = sizefilter(difference(obsr, colorfilter(obsr, lcr)), 4)
    prsr = product(seedsr, seedsr)
    samecr = fork(equality, compose(color, first), compose(color, last))
    hmatr = fork(hmatching, first, last)
    vmatr = fork(vmatching, first, last)
    hpr = sfilter(prsr, fork(both, samecr, hmatr))
    vpr = sfilter(prsr, fork(both, samecr, vmatr))
    haddr = mapply(fork(recolor, compose(color, first), compose(inbox, fork(combine, first, last))), hpr)
    vaddr = mapply(fork(recolor, compose(color, first), compose(inbox, fork(combine, first, last))), vpr)
    BR = underpaint(R, combine(haddr, vaddr))
    M = rot180(BR)
    O = underpaint(base, asobject(M))
    return O
```