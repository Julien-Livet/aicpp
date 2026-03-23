```python
def dsl1(I):
    lc = mostcolor(I)
    obs = objects(I, T, F, T)
    seeds = sizefilter(difference(obs, colorfilter(obs, lc)), 4)
    prs = product(seeds, seeds)
    samec = fork(equality, compose(color, first), compose(color, last))
    samer = fork(equality, compose(uppermost, first), compose(uppermost, last))
    samek = fork(equality, compose(leftmost, first), compose(leftmost, last))
    hp = sfilter(prs, fork(both, samec, samer))
    vp = sfilter(prs, fork(both, samec, samek))
    hadd = mapply(fork(recolor, compose(color, first), compose(backdrop, fork(combine, first, last))), hp)
    vadd = mapply(fork(recolor, compose(color, first), compose(backdrop, fork(combine, first, last))), vp)
    add = combine(hadd, vadd)
    O = underpaint(I, add)
    return O

def dsl2(I):
    lc = mostcolor(I)
    obs = objects(I, T, F, T)
    seeds = sizefilter(difference(obs, colorfilter(obs, lc)), 4)
    prs = product(seeds, seeds)
    samec = fork(equality, compose(color, first), compose(color, last))
    samer = fork(equality, compose(uppermost, first), compose(uppermost, last))
    hp = sfilter(prs, fork(both, samec, samer))
    addh = mapply(fork(recolor, compose(color, first), compose(backdrop, fork(combine, first, last))), hp)
    H = underpaint(I, addh)
    R = rot90(I)
    lcr = mostcolor(R)
    obsr = objects(R, T, F, T)
    seedsr = sizefilter(difference(obsr, colorfilter(obsr, lcr)), 4)
    prr = product(seedsr, seedsr)
    samecr = fork(equality, compose(color, first), compose(color, last))
    samerr = fork(equality, compose(uppermost, first), compose(uppermost, last))
    hpr = sfilter(prr, fork(both, samecr, samerr))
    addr = mapply(fork(recolor, compose(color, first), compose(backdrop, fork(combine, first, last))), hpr)
    R2 = underpaint(R, addr)
    V = rot270(R2)
    O = underpaint(V, addh)
    return O

def dsl3(I):
    lc = mostcolor(I)
    obs = objects(I, T, F, T)
    seeds = sizefilter(difference(obs, colorfilter(obs, lc)), 4)
    prs = product(seeds, seeds)
    samec = fork(equality, compose(color, first), compose(color, last))
    samer = fork(equality, compose(uppermost, first), compose(uppermost, last))
    samek = fork(equality, compose(leftmost, first), compose(leftmost, last))
    hp = sfilter(prs, fork(both, samec, samer))
    vp = sfilter(prs, fork(both, samec, samek))
    hadd = mapply(fork(recolor, compose(color, first), compose(delta, fork(combine, first, last))), hp)
    vadd = mapply(fork(recolor, compose(color, first), compose(delta, fork(combine, first, last))), vp)
    add = combine(hadd, vadd)
    O = underpaint(I, add)
    return O

def dsl4(I):
    lc = mostcolor(I)
    obs = objects(I, T, F, T)
    seeds = sizefilter(difference(obs, colorfilter(obs, lc)), 4)
    prs = product(seeds, seeds)
    samec = fork(equality, compose(color, first), compose(color, last))
    hmat = hmatching
    vmat = vmatching
    hp = sfilter(prs, fork(both, samec, hmat))
    vp = sfilter(prs, fork(both, samec, vmat))
    hadd = mapply(fork(recolor, compose(color, first), compose(backdrop, fork(combine, first, last))), hp)
    vadd = mapply(fork(recolor, compose(color, first), compose(backdrop, fork(combine, first, last))), vp)
    add = combine(hadd, vadd)
    O = underpaint(I, add)
    return O

def dsl5(I):
    lc = mostcolor(I)
    obs = objects(I, T, F, T)
    seeds = sizefilter(difference(obs, colorfilter(obs, lc)), 4)
    prs = product(seeds, seeds)
    samec = fork(equality, compose(color, first), compose(color, last))
    samer = fork(equality, compose(uppermost, first), compose(uppermost, last))
    hp = sfilter(prs, fork(both, samec, samer))
    addh = mapply(fork(recolor, compose(color, first), compose(backdrop, fork(combine, first, last))), hp)
    H = underpaint(I, addh)
    lc2 = mostcolor(H)
    obs2 = objects(H, T, F, T)
    seeds2 = sizefilter(difference(obs2, colorfilter(obs2, lc2)), 4)
    prs2 = product(seeds2, seeds2)
    samec2 = fork(equality, compose(color, first), compose(color, last))
    samek2 = fork(equality, compose(leftmost, first), compose(leftmost, last))
    vp2 = sfilter(prs2, fork(both, samec2, samek2))
    addv = mapply(fork(recolor, compose(color, first), compose(backdrop, fork(combine, first, last))), vp2)
    O = underpaint(H, addv)
    return O
```