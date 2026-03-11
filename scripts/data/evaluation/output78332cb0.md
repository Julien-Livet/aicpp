```python
def dsl1(I):
    dims = astuple(FIVE, FIVE)
    seprow = canvas(SIX, astuple(ONE, FIVE))
    sepcol = canvas(SIX, astuple(FIVE, ONE))
    is_vertcol = both(equality(width(I), FIVE), greater(height(I), FIVE))
    is_horrow = both(equality(height(I), FIVE), greater(width(I), FIVE))
    A = crop(I, astuple(ZERO, ZERO), dims)
    Bv = crop(I, astuple(SIX, ZERO), dims)
    Cv = crop(I, astuple(TWELVE := add(SIX, SIX), ZERO), dims)
    Bh = crop(I, astuple(ZERO, SIX), dims)
    Ch = crop(I, astuple(ZERO, TWELVE), dims)
    if is_vertcol:
        x1 = hconcat(A, sepcol)
        x2 = hconcat(x1, Bv)
        x3 = hconcat(x2, sepcol)
        O = hconcat(x3, Cv)
    else:
        if is_horrow:
            y1 = vconcat(A, seprow)
            y2 = vconcat(y1, Bh)
            y3 = vconcat(y2, seprow)
            O = vconcat(y3, Ch)
        else:
            NW = A
            NE = Bh
            SW = Bv
            SE = crop(I, astuple(SIX, SIX), dims)
            z1 = vconcat(NW, seprow)
            z2 = vconcat(z1, SE)
            z3 = vconcat(z2, seprow)
            z4 = vconcat(z3, NE)
            z5 = vconcat(z4, seprow)
            O = vconcat(z5, SW)
    return O

def dsl2(I):
    dims = astuple(FIVE, FIVE)
    seprow = canvas(SIX, astuple(ONE, FIVE))
    sepcol = canvas(SIX, astuple(FIVE, ONE))
    is_vertcol = both(equality(width(I), FIVE), greater(height(I), FIVE))
    is_horrow = both(equality(height(I), FIVE), greater(width(I), FIVE))
    A = crop(I, astuple(ZERO, ZERO), dims)
    Bv = crop(I, astuple(SIX, ZERO), dims)
    Cv = crop(I, astuple(TWELVE := add(SIX, SIX), ZERO), dims)
    Bh = crop(I, astuple(ZERO, SIX), dims)
    Ch = crop(I, astuple(ZERO, TWELVE), dims)
    if is_vertcol:
        x1 = hconcat(A, sepcol)
        x2 = hconcat(x1, Bv)
        x3 = hconcat(x2, sepcol)
        O = hconcat(x3, Cv)
    else:
        if is_horrow:
            y1 = vconcat(A, seprow)
            y2 = vconcat(y1, Bh)
            y3 = vconcat(y2, seprow)
            O = vconcat(y3, Ch)
        else:
            NW = A
            NE = Bh
            SW = Bv
            SE = crop(I, astuple(SIX, SIX), dims)
            z1 = vconcat(NW, seprow)
            z2 = vconcat(z1, NE)
            z3 = vconcat(z2, seprow)
            z4 = vconcat(z3, SW)
            z5 = vconcat(z4, seprow)
            O = vconcat(z5, SE)
    return O

def dsl3(I):
    dims = astuple(FIVE, FIVE)
    seprow = canvas(SIX, astuple(ONE, FIVE))
    sepcol = canvas(SIX, astuple(FIVE, ONE))
    is_vertcol = both(equality(width(I), FIVE), greater(height(I), FIVE))
    is_horrow = both(equality(height(I), FIVE), greater(width(I), FIVE))
    A = crop(I, astuple(ZERO, ZERO), dims)
    Bv = crop(I, astuple(SIX, ZERO), dims)
    Cv = crop(I, astuple(TWELVE := add(SIX, SIX), ZERO), dims)
    Bh = crop(I, astuple(ZERO, SIX), dims)
    Ch = crop(I, astuple(ZERO, TWELVE), dims)
    if is_vertcol:
        x1 = hconcat(A, sepcol)
        x2 = hconcat(x1, Bv)
        x3 = hconcat(x2, sepcol)
        O = hconcat(x3, Cv)
    else:
        if is_horrow:
            y1 = vconcat(A, seprow)
            y2 = vconcat(y1, Bh)
            y3 = vconcat(y2, seprow)
            O = vconcat(y3, Ch)
        else:
            NW = A
            NE = Bh
            SW = Bv
            SE = crop(I, astuple(SIX, SIX), dims)
            z1 = hconcat(NW, sepcol)
            z2 = hconcat(z1, SE)
            z3 = hconcat(z2, sepcol)
            z4 = hconcat(z3, NE)
            z5 = hconcat(z4, sepcol)
            O = hconcat(z5, SW)
    return O

def dsl4(I):
    dims = astuple(FIVE, FIVE)
    seprow = canvas(SIX, astuple(ONE, FIVE))
    sepcol = canvas(SIX, astuple(FIVE, ONE))
    is_vertcol = both(equality(width(I), FIVE), greater(height(I), FIVE))
    is_horrow = both(equality(height(I), FIVE), greater(width(I), FIVE))
    A = crop(I, astuple(ZERO, ZERO), dims)
    Bv = crop(I, astuple(SIX, ZERO), dims)
    Cv = crop(I, astuple(TWELVE := add(SIX, SIX), ZERO), dims)
    Bh = crop(I, astuple(ZERO, SIX), dims)
    Ch = crop(I, astuple(ZERO, TWELVE), dims)
    if is_vertcol:
        x1 = hconcat(A, sepcol)
        x2 = hconcat(x1, Bv)
        x3 = hconcat(x2, sepcol)
        O = hconcat(x3, Cv)
    else:
        if is_horrow:
            y1 = vconcat(A, seprow)
            y2 = vconcat(y1, Bh)
            y3 = vconcat(y2, seprow)
            O = vconcat(y3, Ch)
        else:
            NW = A
            NE = Bh
            SW = Bv
            SE = crop(I, astuple(SIX, SIX), dims)
            z1 = hconcat(NW, sepcol)
            z2 = hconcat(z1, NE)
            z3 = hconcat(z2, sepcol)
            z4 = hconcat(z3, SW)
            z5 = hconcat(z4, sepcol)
            O = hconcat(z5, SE)
    return O

def dsl5(I):
    dims = astuple(FIVE, FIVE)
    seprow = canvas(SIX, astuple(ONE, FIVE))
    sepcol = canvas(SIX, astuple(FIVE, ONE))
    is_vertcol = both(equality(width(I), FIVE), greater(height(I), FIVE))
    is_horrow = both(equality(height(I), FIVE), greater(width(I), FIVE))
    A = crop(I, astuple(ZERO, ZERO), dims)
    Bv = crop(I, astuple(SIX, ZERO), dims)
    Cv = crop(I, astuple(TWELVE := add(SIX, SIX), ZERO), dims)
    Bh = crop(I, astuple(ZERO, SIX), dims)
    Ch = crop(I, astuple(ZERO, TWELVE), dims)
    if is_vertcol:
        x1 = hconcat(A, sepcol)
        x2 = hconcat(x1, Bv)
        x3 = hconcat(x2, sepcol)
        O = hconcat(x3, Cv)
    else:
        if is_horrow:
            y1 = vconcat(A, seprow)
            y2 = vconcat(y1, Bh)
            y3 = vconcat(y2, seprow)
            O = vconcat(y3, Ch)
        else:
            NW = A
            NE = Bh
            SW = Bv
            SE = crop(I, astuple(SIX, SIX), dims)
            z1 = vconcat(NW, seprow)
            z2 = vconcat(z1, SW)
            z3 = vconcat(z2, seprow)
            z4 = vconcat(z3, NE)
            z5 = vconcat(z4, seprow)
            O = vconcat(z5, SE)
    return O
```