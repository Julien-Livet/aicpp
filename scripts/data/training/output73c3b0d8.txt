```python
def dsl1(I):
    w = width(I)
    h = height(I)
    R = lowermost(toobject(ofcolor(I, TWO), I))
    top = crop(I, ORIGIN, astuple(R, w))
    bot = crop(I, astuple(R, ZERO), astuple(subtract(h, R), w))
    # shift 4s down within regions
    st = intersection(shift(ofcolor(top, FOUR), DOWN), asindices(top))
    sb_local = intersection(shift(ofcolor(bot, FOUR), DOWN), asindices(bot))
    # apex: downshifted top 4s on the last row above the 2-bar
    last_top = decrement(R)
    rowline_top = hfrontier(astuple(last_top, ZERO))
    apex = intersection(st, rowline_top)
    # diagonals from apex within top: up-right and up-left
    upr = mapply(rbind(shoot, UP_RIGHT), apex)
    upl = mapply(rbind(shoot, NEG_UNITY), apex)
    lines = intersection(combine(upr, upl), asindices(top))
    # assemble
    top_out = paint(replace(top, FOUR, ZERO), recolor(FOUR, combine(st, lines)))
    sb = shift(sb_local, astuple(R, ZERO))
    base = replace(I, FOUR, ZERO)
    O = paint(base, recolor(FOUR, sb))
    O = paint(O, toobject(asindices(top), O))  # ensure top region preserved
    O = vconcat(top_out, crop(O, astuple(R, ZERO), astuple(subtract(h, R), w)))
    return O

def dsl2(I):
    w = width(I)
    h = height(I)
    R = lowermost(toobject(ofcolor(I, TWO), I))
    top = crop(I, ORIGIN, astuple(R, w))
    bot = crop(I, astuple(R, ZERO), astuple(subtract(h, R), w))
    base = replace(I, FOUR, ZERO)
    # global shifted sets
    st_global = intersection(shift(ofcolor(top, FOUR), DOWN), asindices(top))
    sb_global = shift(intersection(shift(ofcolor(bot, FOUR), DOWN), asindices(bot)), astuple(R, ZERO))
    # apex row (global coords)
    last_top = decrement(R)
    rowline = hfrontier(astuple(last_top, ZERO))
    apex = intersection(st_global, rowline)
    # diagonals clipped to top region (global)
    upr = mapply(rbind(shoot, UP_RIGHT), apex)
    upl = mapply(rbind(shoot, NEG_UNITY), apex)
    lines = intersection(combine(upr, upl), asindices(top))
    paints = recolor(FOUR, combine(st_global, combine(sb_global, lines)))
    O = paint(base, paints)
    return O

def dsl3(I):
    w = width(I)
    h = height(I)
    R = lowermost(toobject(ofcolor(I, TWO), I))
    top = crop(I, ORIGIN, astuple(R, w))
    bot = crop(I, astuple(R, ZERO), astuple(subtract(h, R), w))
    # shift downs
    st = intersection(shift(ofcolor(top, FOUR), DOWN), asindices(top))
    sb = shift(intersection(shift(ofcolor(bot, FOUR), DOWN), asindices(bot)), astuple(R, ZERO))
    # apex via row R-2 in top, then downshift
    row_r2 = hfrontier(astuple(subtract(R, TWO), ZERO))
    pre = intersection(ofcolor(top, FOUR), row_r2)
    apex = intersection(shift(pre, DOWN), asindices(top))
    # diagonals from apex within top
    lines = combine(mapply(rbind(shoot, UP_RIGHT), apex), mapply(rbind(shoot, NEG_UNITY), apex))
    lines = intersection(lines, asindices(top))
    # paint all
    base = replace(I, FOUR, ZERO)
    paints = recolor(FOUR, combine(st, combine(sb, lines)))
    O = paint(base, paints)
    return O

def dsl4(I):
    w = width(I)
    h = height(I)
    R = lowermost(toobject(ofcolor(I, TWO), I))
    top = crop(I, ORIGIN, astuple(R, w))
    bot = crop(I, astuple(R, ZERO), astuple(subtract(h, R), w))
    # top processing
    st = intersection(shift(ofcolor(top, FOUR), DOWN), asindices(top))
    last_top = decrement(R)
    apex = intersection(st, hfrontier(astuple(last_top, ZERO)))
    upl = mapply(rbind(shoot, NEG_UNITY), apex)
    upr = mapply(rbind(shoot, UP_RIGHT), apex)
    diag = intersection(combine(upl, upr), asindices(top))
    top_out = paint(replace(top, FOUR, ZERO), recolor(FOUR, combine(st, diag)))
    # bottom processing (only shift down)
    sb_local = intersection(shift(ofcolor(bot, FOUR), DOWN), asindices(bot))
    bot_out = paint(replace(bot, FOUR, ZERO), recolor(FOUR, sb_local))
    O = vconcat(top_out, bot_out)
    return O

def dsl5(I):
    w = width(I)
    h = height(I)
    R = lowermost(toobject(ofcolor(I, TWO), I))
    top = crop(I, ORIGIN, astuple(R, w))
    bot = crop(I, astuple(R, ZERO), astuple(subtract(h, R), w))
    # compute once and paint on a single base
    base = replace(I, FOUR, ZERO)
    # shifted 4s
    top_shift = intersection(shift(ofcolor(top, FOUR), DOWN), asindices(top))
    bot_shift = shift(intersection(shift(ofcolor(bot, FOUR), DOWN), asindices(bot)), astuple(R, ZERO))
    # apex on last top row
    apex = intersection(top_shift, hfrontier(astuple(decrement(R), ZERO)))
    # draw both diagonals upward from apex, clipped to top
    diag_up = combine(mapply(rbind(shoot, UP_RIGHT), apex), mapply(rbind(shoot, NEG_UNITY), apex))
    diag_up = intersection(diag_up, asindices(top))
    paints = recolor(FOUR, combine(top_shift, combine(bot_shift, diag_up)))
    O = paint(base, paints)
    return O
```