```python
def dsl1(I):
    TL = crop(I, ORIGIN, TWO_BY_TWO)
    TOP = first(hsplit(TL, TWO))
    BOT = last(hsplit(TL, TWO))
    TL_L = first(vsplit(TOP, TWO))
    TL_R = last(vsplit(TOP, TWO))
    BL_L = first(vsplit(BOT, TWO))
    BL_R = last(vsplit(BOT, TWO))
    c00 = mostcolor(TL_L)
    c01 = mostcolor(TL_R)
    c10 = mostcolor(BL_L)
    c11 = mostcolor(BL_R)
    O1 = switch(I, c00, c01)
    O = switch(O1, c10, c11)
    return O

def dsl2(I):
    TL = crop(I, ORIGIN, TWO_BY_TWO)
    TOP = first(hsplit(TL, TWO))
    BOT = last(hsplit(TL, TWO))
    c00 = mostcolor(first(vsplit(TOP, TWO)))
    c01 = mostcolor(last(vsplit(TOP, TWO)))
    c10 = mostcolor(first(vsplit(BOT, TWO)))
    c11 = mostcolor(last(vsplit(BOT, TWO)))
    A = recolor(c01, ofcolor(I, c00))
    B = recolor(c00, ofcolor(I, c01))
    C = recolor(c11, ofcolor(I, c10))
    D = recolor(c10, ofcolor(I, c11))
    O = paint(paint(paint(paint(I, A), B), C), D)
    return O

def dsl3(I):
    TL = crop(I, ORIGIN, TWO_BY_TWO)
    TOP = first(hsplit(TL, TWO))
    BOT = last(hsplit(TL, TWO))
    c00 = mostcolor(first(vsplit(TOP, TWO)))
    c01 = mostcolor(last(vsplit(TOP, TWO)))
    c10 = mostcolor(first(vsplit(BOT, TWO)))
    c11 = mostcolor(last(vsplit(BOT, TWO)))
    bg = cover(cover(cover(cover(I, ofcolor(I, c00)), ofcolor(I, c01)), ofcolor(I, c10)), ofcolor(I, c11))
    A = recolor(c01, ofcolor(I, c00))
    B = recolor(c00, ofcolor(I, c01))
    C = recolor(c11, ofcolor(I, c10))
    D = recolor(c10, ofcolor(I, c11))
    O = underpaint(underpaint(underpaint(underpaint(bg, A), B), C), D)
    return O

def dsl4(I):
    TL = crop(I, ORIGIN, TWO_BY_TWO)
    TOP = first(hsplit(TL, TWO))
    BOT = last(hsplit(TL, TWO))
    topobjs = order(objects(TOP, T, F, T), leftmost)
    botobjs = order(objects(BOT, T, F, T), leftmost)
    c00 = color(first(topobjs))
    c01 = color(last(topobjs))
    c10 = color(first(botobjs))
    c11 = color(last(botobjs))
    A = recolor(c01, ofcolor(I, c00))
    B = recolor(c00, ofcolor(I, c01))
    C = recolor(c11, ofcolor(I, c10))
    D = recolor(c10, ofcolor(I, c11))
    O = paint(paint(paint(paint(I, A), B), C), D)
    return O

def dsl5(I):
    TL = crop(I, ORIGIN, TWO_BY_TWO)
    objs = objects(TL, T, F, T)
    topobjs = sfilter(objs, matcher(uppermost, ZERO))
    botobjs = sfilter(objs, matcher(uppermost, ONE))
    to = first(topobjs)
    bo = first(botobjs)
    c00 = color(to)
    c01 = color(other(topobjs, to))
    c10 = color(bo)
    c11 = color(other(botobjs, bo))
    A = recolor(c01, ofcolor(I, c00))
    B = recolor(c00, ofcolor(I, c01))
    C = recolor(c11, ofcolor(I, c10))
    D = recolor(c10, ofcolor(I, c11))
    O = paint(paint(paint(paint(I, A), B), C), D)
    return O
```