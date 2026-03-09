```python
def dsl1(I):
    # Move all foreground objects downward until adjacent to the last two rows (leave a 1-row buffer above the floor)
    h = height(I)
    w = width(I)
    row_m1 = subtract(h, ONE)
    row_m2 = subtract(h, TWO)
    lastrow = shoot(astuple(row_m1, ZERO), RIGHT)
    above_last = shoot(astuple(row_m2, ZERO), RIGHT)
    barrier = combine(lastrow, above_last)

    objs = fgpartition(I)
    movable = []
    for o in objs:
        if size(intersection(toindices(o), barrier)) == 0:
            movable.append(o)

    G = I
    for o in movable:
        G = cover(G, o)
    for o in movable:
        v = gravitate(o, barrier)
        G = move(G, o, v)
    return G

def dsl2(I):
    # Like dsl1 but stop adjacent to the bottom row only (no buffer)
    h = height(I)
    row_m1 = subtract(h, ONE)
    lastrow = shoot(astuple(row_m1, ZERO), RIGHT)

    objs = fgpartition(I)
    movable = []
    for o in objs:
        if size(intersection(toindices(o), lastrow)) == 0:
            movable.append(o)

    G = I
    for o in movable:
        G = cover(G, o)
    for o in movable:
        v = gravitate(o, lastrow)
        G = move(G, o, v)
    return G

def dsl3(I):
    # Flip the entire grid except the last two rows vertically (bring upper content downward)
    h = height(I)
    w = width(I)
    top_h = subtract(h, TWO)
    top = crop(I, astuple(ZERO, ZERO), astuple(top_h, w))
    bot = crop(I, astuple(top_h, ZERO), astuple(TWO, w))
    newtop = hmirror(top)
    O = vconcat(newtop, bot)
    return O

def dsl4(I):
    # Cyclically rotate the right half downward by one row, leave the left half unchanged
    h = height(I)
    left = lefthalf(I)
    right = righthalf(I)
    rw = width(right)
    top_part = crop(right, astuple(ZERO, ZERO), astuple(subtract(h, ONE), rw))
    bottom_row = crop(right, astuple(subtract(h, ONE), ZERO), astuple(ONE, rw))
    newright = vconcat(bottom_row, top_part)
    O = hconcat(left, newright)
    return O

def dsl5(I):
    # Move only the most common foreground color (excluding background) downward to be adjacent to the last two rows
    h = height(I)
    w = width(I)
    row_m1 = subtract(h, ONE)
    row_m2 = subtract(h, TWO)
    lastrow = shoot(astuple(row_m1, ZERO), RIGHT)
    above_last = shoot(astuple(row_m2, ZERO), RIGHT)
    barrier = combine(lastrow, above_last)

    bg = mostcolor(I)
    cols = remove(bg, palette(I))
    if size(cols) == 0:
        return I
    cstar = argmax(cols, rbind(colorcount, I))
    src = toobject(ofcolor(I, cstar), I)
    G = cover(I, src)
    v = gravitate(src, barrier)
    O = move(G, src, v)
    return O
```