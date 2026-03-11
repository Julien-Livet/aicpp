```python
def dsl1(I):
    # Pick the 3-colored rectangular frame whose interior contains color 8, maximizing interior area
    objs = objects(I, T, F, F)
    threes = colorfilter(objs, THREE)
    isframe = fork(equality, toindices, box)
    frames = sfilter(threes, isframe)
    sub = rbind(subgrid, I)
    cnt8 = compose(rbind(colorcount, EIGHT), sub)
    has8 = compose(rbind(greater, ZERO), cnt8)
    cands = sfilter(frames, has8)
    area = compose(size, delta)
    target = argmax(cands, area)
    O = subgrid(target, I)
    return O

def dsl2(I):
    # Among 3-colored true frames not touching the outer border, maximize the palette size of their subgrid
    objs = objects(I, T, F, F)
    threes = colorfilter(objs, THREE)
    isframe = fork(equality, toindices, box)
    frames = sfilter(threes, isframe)
    nb = compose(flip, rbind(bordering, I))
    inner = sfilter(frames, nb)
    sub = rbind(subgrid, I)
    pal = compose(palette, sub)
    richness = compose(size, pal)
    target = argmax(inner, richness)
    O = subgrid(target, I)
    return O

def dsl3(I):
    # Choose the 3-frame maximizing (#8 inside + #1 inside)
    objs = objects(I, T, F, F)
    threes = colorfilter(objs, THREE)
    isframe = fork(equality, toindices, box)
    frames = sfilter(threes, isframe)
    sub = rbind(subgrid, I)
    cnt8 = compose(rbind(colorcount, EIGHT), sub)
    cnt1 = compose(rbind(colorcount, ONE), sub)
    score = fork(add, cnt8, cnt1)
    target = argmax(frames, score)
    O = subgrid(target, I)
    return O

def dsl4(I):
    # Choose the 3-frame with the most 8s inside (tie-breaking by interior area implicitly by argmax order)
    objs = objects(I, T, F, F)
    threes = colorfilter(objs, THREE)
    isframe = fork(equality, toindices, box)
    frames = sfilter(threes, isframe)
    sub = rbind(subgrid, I)
    cnt8 = compose(rbind(colorcount, EIGHT), sub)
    target = argmax(frames, cnt8)
    O = subgrid(target, I)
    return O

def dsl5(I):
    # Pick the 3-frame whose interior contains both color 2 and color 8, maximizing interior area
    objs = objects(I, T, F, F)
    threes = colorfilter(objs, THREE)
    isframe = fork(equality, toindices, box)
    frames = sfilter(threes, isframe)
    sub = rbind(subgrid, I)
    cnt8 = compose(rbind(colorcount, EIGHT), sub)
    cnt2 = compose(rbind(colorcount, TWO), sub)
    has8 = compose(rbind(greater, ZERO), cnt8)
    has2 = compose(rbind(greater, ZERO), cnt2)
    both_present = fork(both, has8, has2)
    cands = sfilter(frames, both_present)
    area = compose(size, delta)
    target = argmax(cands, area)
    O = subgrid(target, I)
    return O
```