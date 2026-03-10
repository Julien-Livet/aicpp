```python
def dsl1(I):
    h = height(I)
    w = width(I)
    half = divide(w, TWO)
    rw = subtract(w, half)
    col0 = crop(I, ORIGIN, astuple(h, ONE))
    n9 = colorcount(col0, NINE)
    n2 = colorcount(col0, TWO)
    # build right half on its own canvas
    R = canvas(SEVEN, astuple(h, rw))
    topR = asindices(crop(R, ORIGIN, astuple(n9, rw)))
    botR = asindices(crop(R, astuple(subtract(h, n2), ZERO), astuple(n2, rw)))
    R1 = fill(R, NINE, topR)
    R2 = fill(R1, TWO, botR)
    # left half is all 7
    L = canvas(SEVEN, astuple(h, half))
    O = hconcat(L, R2)
    return O

def dsl2(I):
    h = height(I)
    w = width(I)
    half = divide(w, TWO)
    col0 = crop(I, ORIGIN, astuple(h, ONE))
    n9 = colorcount(col0, NINE)
    n2 = colorcount(col0, TWO)
    O0 = canvas(SEVEN, shape(I))
    top = asindices(crop(O0, astuple(ZERO, half), astuple(n9, subtract(w, half))))
    O1 = fill(O0, NINE, top)
    bot = asindices(crop(O1, astuple(subtract(h, n2), half), astuple(n2, subtract(w, half))))
    O = fill(O1, TWO, bot)
    return O

def dsl3(I):
    h = height(I)
    w = width(I)
    half = divide(w, TWO)
    R = righthalf(I)
    rw = width(R)
    col0 = crop(I, ORIGIN, astuple(h, ONE))
    n9 = colorcount(col0, NINE)
    n2 = colorcount(col0, TWO)
    O0 = canvas(SEVEN, shape(I))
    topR = asindices(crop(R, ORIGIN, astuple(n9, rw)))
    botR = asindices(crop(R, astuple(subtract(h, n2), ZERO), astuple(n2, rw)))
    top = shift(topR, astuple(ZERO, half))
    bot = shift(botR, astuple(ZERO, half))
    O1 = fill(O0, NINE, top)
    O = fill(O1, TWO, bot)
    return O

def dsl4(I):
    h = height(I)
    w = width(I)
    half = divide(w, TWO)
    col0 = crop(I, ORIGIN, astuple(h, ONE))
    n9 = colorcount(col0, NINE)
    n2 = colorcount(col0, TWO)
    midh = subtract(subtract(h, n9), n2)
    # top block
    Top = canvas(SEVEN, astuple(n9, w))
    topRH = asindices(crop(Top, astuple(ZERO, half), astuple(n9, subtract(w, half))))
    TopF = fill(Top, NINE, topRH)
    # middle all 7s
    Mid = canvas(SEVEN, astuple(midh, w))
    # bottom block
    Bot = canvas(SEVEN, astuple(n2, w))
    botRH = asindices(crop(Bot, astuple(ZERO, half), astuple(n2, subtract(w, half))))
    BotF = fill(Bot, TWO, botRH)
    O = vconcat(TopF, vconcat(Mid, BotF))
    return O

def dsl5(I):
    h = height(I)
    w = width(I)
    half = divide(w, TWO)
    col0 = crop(I, ORIGIN, astuple(h, ONE))
    n9 = colorcount(col0, NINE)
    n2 = colorcount(col0, TWO)
    O0 = canvas(SEVEN, shape(I))
    # global indices for right half
    RH = asindices(crop(I, astuple(ZERO, half), astuple(h, subtract(w, half))))
    RHg = shift(RH, astuple(ZERO, half))
    # top rows and bottom rows as global index sets
    TopRows = asindices(crop(I, ORIGIN, astuple(n9, w)))
    BotRows = asindices(crop(I, astuple(subtract(h, n2), ZERO), astuple(n2, w)))
    topPatch = intersection(RHg, TopRows)
    botPatch = intersection(RHg, BotRows)
    O1 = fill(O0, NINE, topPatch)
    O = fill(O1, TWO, botPatch)
    return O
```