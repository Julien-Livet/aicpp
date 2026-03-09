```python
def dsl1(I):
    ps = remove(ZERO, palette(I))
    seeds = mapply(lbind(ofcolor, I), ps)
    r = mapply(rbind(shoot, RIGHT), seeds)
    l = mapply(rbind(shoot, LEFT), seeds)
    u = mapply(rbind(shoot, UP), seeds)
    d = mapply(rbind(shoot, DOWN), seeds)
    lines = combine(combine(r, l), combine(u, d))
    c = maximum(ps)
    O = canvas(FIVE, shape(I))
    O = fill(O, c, lines)
    return O

def dsl2(I):
    ps = remove(ZERO, palette(I))
    seeds = mapply(lbind(ofcolor, I), ps)
    r = mapply(rbind(shoot, RIGHT), seeds)
    d = mapply(rbind(shoot, DOWN), seeds)
    lines = combine(r, d)
    c = maximum(ps)
    O = canvas(FIVE, shape(I))
    O = fill(O, c, lines)
    return O

def dsl3(I):
    ps = remove(ZERO, palette(I))
    seeds = mapply(lbind(ofcolor, I), ps)
    ur = mapply(rbind(shoot, UP_RIGHT), seeds)
    dl = mapply(rbind(shoot, DOWN_LEFT), seeds)
    lines = combine(ur, dl)
    c = maximum(ps)
    O = canvas(FIVE, shape(I))
    O = fill(O, c, lines)
    return O

def dsl4(I):
    frs = frontiers(I)
    gridlines = merge(frs)
    ps = remove(ZERO, palette(I))
    c = maximum(ps)
    O = canvas(FIVE, shape(I))
    O = fill(O, c, gridlines)
    return O

def dsl5(I):
    ps = remove(ZERO, palette(I))
    fg_parts = mapply(lbind(ofcolor, I), ps)
    fg = merge(fg_parts)
    frame = box(fg)
    c = maximum(ps)
    O = canvas(FIVE, shape(I))
    O = fill(O, c, frame)
    return O
```