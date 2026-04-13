```python
def dsl1(I):
    O = replace(I, FIVE, TWO)
    return O

def dsl2(I):
    objs = objects(I, T, F, T)
    fives = colorfilter(objs, FIVE)
    nonborder = mfilter(fives, compose(flip, rbind(bordering, I)))
    recolored = mapply(lbind(recolor, TWO), nonborder)
    O = paint(I, merge(recolored))
    return O

def dsl3(I):
    top = tophalf(I)
    bot = bottomhalf(I)
    bot2 = replace(bot, FIVE, TWO)
    O = vconcat(top, bot2)
    return O

def dsl4(I):
    objs = objects(I, T, F, T)
    fives = colorfilter(objs, FIVE)
    keep = argmax(fives, rightmost)
    others = remove(keep, fives)
    recolored = mapply(lbind(recolor, TWO), others)
    O = paint(I, merge(recolored))
    return O

def dsl5(I):
    S = ofcolor(I, FIVE)
    SL = shift(S, LEFT)
    SR = shift(S, RIGHT)
    leftadj = intersection(S, SL)
    rightadj = intersection(S, SR)
    bothadj = combine(leftadj, rightadj)
    O = fill(I, TWO, bothadj)
    return O
```