```python
def dsl1(I):
    # Move each left-edge 6 to the last column of its row if that cell is 7; otherwise remove the 6.
    w = width(I)
    six = ofcolor(I, SIX)
    x0 = replace(I, SIX, SEVEN)  # remove all 6s first
    lastcol = vfrontier(lrcorner(asindices(I)))
    last7 = intersection(lastcol, ofcolor(I, SEVEN))
    put6 = recolor(SIX, last7)
    O = paint(x0, put6)
    return O

def dsl2(I):
    # Move each left-edge 6 to the rightmost available slot: last column if 7 else penultimate if 7; otherwise remove.
    w = width(I)
    six = ofcolor(I, SIX)
    x0 = replace(I, SIX, SEVEN)
    ur = urcorner(asindices(I))
    lastcol = vfrontier(lrcorner(asindices(I)))
    penloc = subtract(ur, tojvec(ONE))
    pencol = vfrontier(penloc)
    last7 = intersection(lastcol, ofcolor(I, SEVEN))
    pen7 = intersection(pencol, ofcolor(I, SEVEN))
    # penultimate-only rows = pen7 rows where last is not 7
    pen7_only = difference(pen7, shift(last7, LEFT))
    target = merge((last7, pen7_only))
    O = paint(x0, recolor(SIX, target))
    return O

def dsl3(I):
    # Duplicate: also place a 6 at the last column wherever that cell is 7 (keep original left-edge 6s).
    lastcol = vfrontier(lrcorner(asindices(I)))
    last7 = intersection(lastcol, ofcolor(I, SEVEN))
    add6 = recolor(SIX, last7)
    O = underpaint(I, add6)
    return O

def dsl4(I):
    # Remove left-edge 6 on rows where the last column is not 7; leave other rows unchanged.
    w = width(I)
    six = ofcolor(I, SIX)
    lastcol = vfrontier(lrcorner(asindices(I)))
    last_not7 = difference(lastcol, ofcolor(I, SEVEN))
    # align those rows to column 1
    off = tojvec(invert(subtract(w, ONE)))
    rows_to_clear = intersection(six, shift(last_not7, off))
    O = fill(I, SEVEN, rows_to_clear)
    return O

def dsl5(I):
    # Combo: duplicate a 6 to the last column when it's 7; also remove left-edge 6 on rows where last column is not 7.
    w = width(I)
    six = ofcolor(I, SIX)
    lastcol = vfrontier(lrcorner(asindices(I)))
    last7 = intersection(lastcol, ofcolor(I, SEVEN))
    last_not7 = difference(lastcol, ofcolor(I, SEVEN))
    off = tojvec(invert(subtract(w, ONE)))
    rows_to_clear = intersection(six, shift(last_not7, off))
    x0 = fill(I, SEVEN, rows_to_clear)
    O = underpaint(x0, recolor(SIX, last7))
    return O
```