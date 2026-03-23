```python
def dsl1(I):
    I2 = replace(I, FIVE, TWO)
    L0, R0 = vsplit(I, 2)
    L2, R2 = vsplit(I2, 2)
    O = hconcat(L2, R0)
    return O

def dsl2(I):
    top = tophalf(I)
    bot = bottomhalf(I)
    objs = objects(bot, T, F, T)
    fives = colorfilter(objs, FIVE)
    top_touch = sfilter(fives, matcher(uppermost, 0))
    bot2 = replace(bot, FIVE, TWO)
    O_bot = paint(bot2, merge(top_touch))
    O = vconcat(top, O_bot)
    return O

def dsl3(I):
    objs = objects(I, T, F, T)
    fives = colorfilter(objs, FIVE)
    nonborder = sfilter(fives, compose(flip, rbind(bordering, I)))
    recolored = mapply(lbind(recolor, TWO), nonborder)
    O = paint(I, recolored)
    return O

def dsl4(I):
    objs = objects(I, T, F, T)
    fives = colorfilter(objs, FIVE)
    keep = argmax(fives, rightmost)
    others = remove(keep, fives)
    recolored = mapply(lbind(recolor, TWO), others)
    O = paint(I, recolored)
    return O

def dsl5(I):
    S = ofcolor(I, FIVE)
    SL = shift(S, LEFT)
    SR = shift(S, RIGHT)
    SU = shift(S, UP)
    SD = shift(S, DOWN)
    adjh = combine(intersection(S, SL), intersection(S, SR))
    adjv = combine(intersection(S, SU), intersection(S, SD))
    adj_any = combine(adjh, adjv)
    iso = difference(S, adj_any)
    base = replace(I, FIVE, TWO)
    restore = toobject(iso, I)
    O = paint(base, restore)
    return O
```