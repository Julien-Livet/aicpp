```python
def dsl1(I):
    # Replace 8 with the most common color within each quadrant (2x2 split)
    hs = hsplit(I, TWO)
    top = first(hs)
    bottom = last(hs)

    vs_top = vsplit(top, TWO)
    tl = first(vs_top)
    tr = last(vs_top)

    vs_bot = vsplit(bottom, TWO)
    bl = first(vs_bot)
    br = last(vs_bot)

    tl2 = replace(tl, EIGHT, mostcolor(tl))
    tr2 = replace(tr, EIGHT, mostcolor(tr))
    top2 = hconcat(tl2, tr2)

    bl2 = replace(bl, EIGHT, mostcolor(bl))
    br2 = replace(br, EIGHT, mostcolor(br))
    bottom2 = hconcat(bl2, br2)

    O = vconcat(top2, bottom2)
    return O

def dsl2(I):
    # Replace 8 with the most common color within each horizontal half (top/bottom)
    hs = hsplit(I, TWO)
    top = first(hs)
    bottom = last(hs)

    top2 = replace(top, EIGHT, mostcolor(top))
    bottom2 = replace(bottom, EIGHT, mostcolor(bottom))

    O = vconcat(top2, bottom2)
    return O

def dsl3(I):
    # Replace 8 with the most common color within each vertical half (left/right)
    vs = vsplit(I, TWO)
    left_half = first(vs)
    right_half = last(vs)

    left2 = replace(left_half, EIGHT, mostcolor(left_half))
    right2 = replace(right_half, EIGHT, mostcolor(right_half))

    O = hconcat(left2, right2)
    return O

def dsl4(I):
    # Quadrants again, but compute colors after trimming each quadrant (robust to borders)
    hs = hsplit(I, TWO)
    top = first(hs)
    bottom = last(hs)

    vs_top = vsplit(top, TWO)
    tl = first(vs_top)
    tr = last(vs_top)

    vs_bot = vsplit(bottom, TWO)
    bl = first(vs_bot)
    br = last(vs_bot)

    tl2 = replace(tl, EIGHT, mostcolor(trim(tl)))
    tr2 = replace(tr, EIGHT, mostcolor(trim(tr)))
    top2 = hconcat(tl2, tr2)

    bl2 = replace(bl, EIGHT, mostcolor(trim(bl)))
    br2 = replace(br, EIGHT, mostcolor(trim(br)))
    bottom2 = hconcat(bl2, br2)

    O = vconcat(top2, bottom2)
    return O

def dsl5(I):
    # Top/bottom halves with trimming before computing most common color
    hs = hsplit(I, TWO)
    top = first(hs)
    bottom = last(hs)

    top2 = replace(top, EIGHT, mostcolor(trim(top)))
    bottom2 = replace(bottom, EIGHT, mostcolor(trim(bottom)))

    O = vconcat(top2, bottom2)
    return O
```