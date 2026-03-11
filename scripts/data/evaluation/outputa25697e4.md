```python
def dsl1(I):
    # Slide all foreground to touch the left border (preserve vertical placement)
    bg = mostcolor(I)
    dims = shape(I)
    fg = merge(objects(I, T, F, T))
    left_border = vfrontier(ORIGIN)
    off = gravitate(fg, left_border)
    moved = shift(fg, off)
    O = canvas(bg, dims)
    O = paint(O, moved)
    return O

def dsl2(I):
    # Normalize union to upper-left and then shift down to original top row
    bg = mostcolor(I)
    dims = shape(I)
    fg = merge(objects(I, T, F, T))
    top = uppermost(fg)
    nfg = normalize(fg)
    moved = shift(nfg, astuple(top, ZERO))
    O = canvas(bg, dims)
    O = paint(O, moved)
    return O

def dsl3(I):
    # Compress grid (remove empty rows/cols) and place at original top row
    bg = mostcolor(I)
    dims = shape(I)
    fg = merge(objects(I, T, F, T))
    top = uppermost(fg)
    C = compress(I)
    cfg = merge(objects(C, T, F, T))
    v = astuple(subtract(top, uppermost(cfg)), ZERO)
    moved = shift(cfg, v)
    O = canvas(bg, dims)
    O = paint(O, moved)
    return O

def dsl4(I):
    # Slide all foreground to touch both the left and top borders
    bg = mostcolor(I)
    dims = shape(I)
    fg = merge(objects(I, T, F, T))
    left_border = vfrontier(ORIGIN)
    top_border = hfrontier(ORIGIN)
    off1 = gravitate(fg, left_border)
    fg1 = shift(fg, off1)
    off2 = gravitate(fg1, top_border)
    off = add(off1, off2)
    moved = shift(fg, off)
    O = canvas(bg, dims)
    O = paint(O, moved)
    return O

def dsl5(I):
    # Crop to foreground bounding box and place it at the same top row, left-aligned
    bg = mostcolor(I)
    H = height(I)
    W = width(I)
    fg = merge(objects(I, T, F, T))
    top = uppermost(fg)
    bb = subgrid(fg, I)
    h2 = height(bb)
    w2 = width(bb)
    top_pad = canvas(bg, astuple(top, W))
    right_pad = canvas(bg, astuple(h2, subtract(W, w2)))
    mid = hconcat(bb, right_pad)
    bot_h = subtract(H, add(top, h2))
    bottom_pad = canvas(bg, astuple(bot_h, W))
    O = vconcat(top_pad, vconcat(mid, bottom_pad))
    return O
```