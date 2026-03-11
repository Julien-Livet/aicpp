```python
def dsl1(I):
    # Remove all border-touching horizontal bars, then recolor a color present only in the bottom half (not in top) to FIVE
    bg = mostcolor(I)
    objs = objects(I, T, F, T)
    pred_bar = fork(both, hline, rbind(bordering, I))
    bars = sfilter(objs, pred_bar)
    bar_inds = mapply(toindices, bars)
    I1 = fill(I, bg, bar_inds)
    p_bot = palette(bottomhalf(I1))
    p_top = palette(tophalf(I1))
    cand = difference(p_bot, p_top)
    cand = remove(bg, cand)
    target = branch(equality(size(cand), ZERO), bg, maximum(cand))
    O = replace(I1, target, FIVE)
    return O

def dsl2(I):
    # Remove border-touching horizontal bars, then recolor the uppermost remaining non-bar object's color to FIVE
    bg = mostcolor(I)
    objs = objects(I, T, F, T)
    pred_bar = fork(both, hline, rbind(bordering, I))
    bars = sfilter(objs, pred_bar)
    bar_inds = mapply(toindices, bars)
    I1 = fill(I, bg, bar_inds)
    nonbars = difference(objs, bars)
    top_obj = argmin(nonbars, uppermost)
    target = color(top_obj)
    O = replace(I1, target, FIVE)
    return O

def dsl3(I):
    # Remove border-touching horizontal bars, then recolor the rightmost remaining non-bar object's color to FIVE
    bg = mostcolor(I)
    objs = objects(I, T, F, T)
    pred_bar = fork(both, hline, rbind(bordering, I))
    bars = sfilter(objs, pred_bar)
    bar_inds = mapply(toindices, bars)
    I1 = fill(I, bg, bar_inds)
    nonbars = difference(objs, bars)
    right_obj = argmax(nonbars, rightmost)
    target = color(right_obj)
    O = replace(I1, target, FIVE)
    return O

def dsl4(I):
    # Remove border-touching horizontal bars, then recolor the least common color in the bottom half to FIVE
    bg = mostcolor(I)
    objs = objects(I, T, F, T)
    pred_bar = fork(both, hline, rbind(bordering, I))
    bars = sfilter(objs, pred_bar)
    bar_inds = mapply(toindices, bars)
    I1 = fill(I, bg, bar_inds)
    target = leastcolor(bottomhalf(I1))
    O = replace(I1, target, FIVE)
    return O

def dsl5(I):
    # Remove border-touching horizontal bars, then recolor the maximum (by value) non-background color to FIVE
    bg = mostcolor(I)
    objs = objects(I, T, F, T)
    pred_bar = fork(both, hline, rbind(bordering, I))
    bars = sfilter(objs, pred_bar)
    bar_inds = mapply(toindices, bars)
    I1 = fill(I, bg, bar_inds)
    pal = remove(bg, palette(I1))
    target = branch(equality(size(pal), ZERO), bg, maximum(pal))
    O = replace(I1, target, FIVE)
    return O
```