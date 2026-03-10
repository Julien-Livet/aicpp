```python
def dsl1(I):
    # Recolor 3s that touch both a 0 and a 2 (4-neighborhood)
    three = ofcolor(I, THREE)
    z = ofcolor(I, ZERO)
    t = ofcolor(I, TWO)
    adjz = combine(combine(shift(z, UP), shift(z, DOWN)), combine(shift(z, LEFT), shift(z, RIGHT)))
    adjt = combine(combine(shift(t, UP), shift(t, DOWN)), combine(shift(t, LEFT), shift(t, RIGHT)))
    to_change = intersection(three, intersection(adjz, adjt))
    O = fill(I, EIGHT, to_change)
    return O

def dsl2(I):
    # Recolor 3s that have zeros on both horizontal sides (pattern 0-3-0)
    three = ofcolor(I, THREE)
    z = ofcolor(I, ZERO)
    left_zero = shift(z, RIGHT)   # cells with a zero to their left
    right_zero = shift(z, LEFT)   # cells with a zero to their right
    to_change = intersection(three, intersection(left_zero, right_zero))
    O = fill(I, EIGHT, to_change)
    return O

def dsl3(I):
    # Recolor 3s that have zeros above and below (vertical sandwich)
    three = ofcolor(I, THREE)
    z = ofcolor(I, ZERO)
    up_zero = shift(z, DOWN)   # cells with a zero above
    down_zero = shift(z, UP)   # cells with a zero below
    to_change = intersection(three, intersection(up_zero, down_zero))
    O = fill(I, EIGHT, to_change)
    return O

def dsl4(I):
    # Recolor 3s that touch a 0 and also touch either a 2 or a 7 (4-neighborhood)
    three = ofcolor(I, THREE)
    z = ofcolor(I, ZERO)
    two = ofcolor(I, TWO)
    sev = ofcolor(I, SEVEN)
    adjz = combine(combine(shift(z, UP), shift(z, DOWN)), combine(shift(z, LEFT), shift(z, RIGHT)))
    adj2 = combine(combine(shift(two, UP), shift(two, DOWN)), combine(shift(two, LEFT), shift(two, RIGHT)))
    adj7 = combine(combine(shift(sev, UP), shift(sev, DOWN)), combine(shift(sev, LEFT), shift(sev, RIGHT)))
    adj27 = combine(adj2, adj7)
    to_change = intersection(three, intersection(adjz, adj27))
    O = fill(I, EIGHT, to_change)
    return O

def dsl5(I):
    # Recolor 3s that have at least two zero neighbors (any two of up/down/left/right)
    three = ofcolor(I, THREE)
    z = ofcolor(I, ZERO)
    zr = shift(z, RIGHT)
    zl = shift(z, LEFT)
    zu = shift(z, UP)
    zd = shift(z, DOWN)
    two_or_more = combine(
        combine(intersection(zl, zr), intersection(zu, zd)),
        combine(
            combine(intersection(zl, zu), intersection(zl, zd)),
            combine(intersection(zr, zu), intersection(zr, zd))
        )
    )
    to_change = intersection(three, two_or_more)
    O = fill(I, EIGHT, to_change)
    return O
```