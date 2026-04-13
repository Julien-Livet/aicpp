```python
def dsl1(I):
    # Global crop: take the upper-left 3x3 of the foreground bounding box
    fg = difference(asindices(I), ofcolor(I, ZERO))
    start = ulcorner(fg)
    O = crop(I, start, THREE_BY_THREE)
    return O

def dsl2(I):
    # Object extraction into uniform columns: split bbox into 3 vertical bands and use their dominant colors
    fg = difference(asindices(I), ofcolor(I, ZERO))
    bbox = subgrid(fg, I)
    cols = vsplit(bbox, THREE)
    c1 = mostcolor(first(cols))
    c3 = mostcolor(last(cols))
    c2 = mostcolor(bbox)
    col1 = canvas(c1, astuple(THREE, ONE))
    col2 = canvas(c2, astuple(THREE, ONE))
    col3 = canvas(c3, astuple(THREE, ONE))
    O = hconcat(hconcat(col1, col2), col3)
    return O

def dsl3(I):
    # Color filtering by horizontal bands: use dominant color of top/mid/bot of bbox as uniform rows
    fg = difference(asindices(I), ofcolor(I, ZERO))
    bbox = subgrid(fg, I)
    parts = hsplit(bbox, THREE)
    r1 = mostcolor(first(parts))
    r3 = mostcolor(last(parts))
    r2 = mostcolor(bbox)
    row1 = canvas(r1, astuple(ONE, THREE))
    row2 = canvas(r2, astuple(ONE, THREE))
    row3 = canvas(r3, astuple(ONE, THREE))
    O = vconcat(vconcat(row1, row2), row3)
    return O

def dsl4(I):
    # Relational/structural: rows from three largest components by size
    comps = fgpartition(I)
    c1obj = argmax(comps, size)
    rest1 = remove(c1obj, comps)
    c2obj = argmax(rest1, size)
    rest2 = remove(c2obj, rest1)
    c3obj = argmax(rest2, size)
    r1 = color(c1obj)
    r2 = color(c2obj)
    r3 = color(c3obj)
    row1 = canvas(r1, astuple(ONE, THREE))
    row2 = canvas(r2, astuple(ONE, THREE))
    row3 = canvas(r3, astuple(ONE, THREE))
    O = vconcat(vconcat(row1, row2), row3)
    return O

def dsl5(I):
    # Geometric: crop 3x3 around center of foreground, then diagonal mirror
    fg = difference(asindices(I), ofcolor(I, ZERO))
    ctr = center(fg)
    start = subtract(ctr, UNITY)
    block = crop(I, start, THREE_BY_THREE)
    O = dmirror(block)
    return O
```