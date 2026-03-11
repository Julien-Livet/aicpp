```python
def dsl1(I):
    # Swap top-left and bottom-right quadrants
    top = tophalf(I)
    bot = bottomhalf(I)
    tl = lefthalf(top)
    tr = righthalf(top)
    bl = lefthalf(bot)
    br = righthalf(bot)
    new_top = hconcat(br, tr)
    new_bot = hconcat(bl, tl)
    O = vconcat(new_top, new_bot)
    return O

def dsl2(I):
    # Swap top-right and bottom-left quadrants
    top = tophalf(I)
    bot = bottomhalf(I)
    tl = lefthalf(top)
    tr = righthalf(top)
    bl = lefthalf(bot)
    br = righthalf(bot)
    new_top = hconcat(tl, bl)
    new_bot = hconcat(tr, br)
    O = vconcat(new_top, new_bot)
    return O

def dsl3(I):
    # Mirror along the main diagonal
    O = dmirror(I)
    return O

def dsl4(I):
    # Rotate 90 degrees then mirror vertically
    x = rot90(I)
    O = vmirror(x)
    return O

def dsl5(I):
    # Conditional color swaps by halves:
    # - In the top half, swap colors 3 and 8
    # - In the bottom half, swap colors 2 and 8
    top = tophalf(I)
    bot = bottomhalf(I)
    top2 = switch(top, THREE, EIGHT)
    bot2 = switch(bot, TWO, EIGHT)
    O = vconcat(top2, bot2)
    return O
```