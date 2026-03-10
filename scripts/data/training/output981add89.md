```python
def dsl1(I):
    bg = mostcolor(I)
    W = width(I)
    rowG = crop(I, (0, 0), (1, W))
    colors = remove(bg, palette(rowG))
    O = I
    row0 = shoot((0, 0), RIGHT)
    for c in totuple(colors):
        starts = intersection(ofcolor(I, c), row0)
        colpath = mapply(rbind(shoot, DOWN), starts)
        samecol = intersection(colpath, ofcolor(I, c))
        samecol_no_starts = difference(samecol, starts)
        O = fill(O, bg, samecol_no_starts)
        paintset = difference(colpath, samecol_no_starts)
        O = fill(O, c, paintset)
    return O

def dsl2(I):
    bg = mostcolor(I)
    O = I
    row0 = shoot((0, 0), RIGHT)
    bg_on_row0 = intersection(row0, ofcolor(I, bg))
    starts = difference(row0, bg_on_row0)
    for s in totuple(starts):
        c = index(I, s)
        path = shoot(s, DOWN)
        samecol = intersection(path, ofcolor(I, c))
        samecol_no_start = difference(samecol, initset(s))
        O = fill(O, bg, samecol_no_start)
        paintset = difference(path, samecol_no_start)
        O = fill(O, c, paintset)
    return O

def dsl3(I):
    bg = mostcolor(I)
    W = width(I)
    row0 = shoot((0, 0), RIGHT)
    rowG = crop(I, (0, 0), (1, W))
    cols = remove(bg, palette(rowG))
    O = I
    for c in totuple(cols):
        tops = intersection(row0, ofcolor(I, c))
        lines = mapply(rbind(shoot, DOWN), tops)
        erase = difference(intersection(lines, ofcolor(I, c)), tops)
        draw = difference(lines, erase)
        O = fill(O, bg, erase)
        O = fill(O, c, draw)
    return O

def dsl4(I):
    bg = mostcolor(I)
    O = I
    row0 = shoot((0, 0), RIGHT)
    nonbg_top = difference(row0, intersection(row0, ofcolor(I, bg)))
    for t in totuple(nonbg_top):
        c = index(I, t)
        col = shoot(t, DOWN)
        erase = difference(intersection(col, ofcolor(I, c)), initset(t))
        O = fill(O, bg, erase)
        O = fill(O, c, difference(col, erase))
    return O

def dsl5(I):
    bg = mostcolor(I)
    O = I
    row0 = shoot((0, 0), RIGHT)
    for c in totuple(remove(bg, palette(crop(I, (0, 0), (1, width(I)))))):
        starts = intersection(ofcolor(I, c), row0)
        path = mapply(rbind(shoot, DOWN), starts)
        cut = difference(intersection(path, ofcolor(I, c)), starts)
        O = fill(O, bg, cut)
        O = fill(O, c, difference(path, cut))
    return O
```