```python
def dsl1(I):
    # Move ZERO so its upper-left aligns with the TWO upper-left; fill vacated ZERO with ONE
    zind = ofcolor(I, ZERO)
    tind = ofcolor(I, TWO)
    O1 = fill(I, ONE, zind)
    off = subtract(ulcorner(tind), ulcorner(zind))
    nz = shift(zind, off)
    O = fill(O1, ZERO, nz)
    return O

def dsl2(I):
    # Move ZERO so its center of mass matches the TWO center of mass; fill vacated ZERO with ONE
    zind = ofcolor(I, ZERO)
    tind = ofcolor(I, TWO)
    O1 = fill(I, ONE, zind)
    off = subtract(centerofmass(tind), centerofmass(zind))
    nz = shift(zind, off)
    O = fill(O1, ZERO, nz)
    return O

def dsl3(I):
    # Move ZERO so its lower-right aligns with the TWO lower-right; fill vacated ZERO with ONE
    zind = ofcolor(I, ZERO)
    tind = ofcolor(I, TWO)
    O1 = fill(I, ONE, zind)
    off = subtract(lrcorner(tind), lrcorner(zind))
    nz = shift(zind, off)
    O = fill(O1, ZERO, nz)
    return O

def dsl4(I):
    # Overwrite all TWO cells with ZERO; replace original ZERO cells with ONE
    zind = ofcolor(I, ZERO)
    tind = ofcolor(I, TWO)
    O1 = fill(I, ONE, zind)
    O = fill(O1, ZERO, tind)
    return O

def dsl5(I):
    # Move ZERO adjacent to TWO using gravitation; fill vacated ZERO with ONE
    zind = ofcolor(I, ZERO)
    tind = ofcolor(I, TWO)
    direction = gravitate(zind, tind)
    nz = shift(zind, direction)
    O1 = fill(I, ONE, zind)
    O = fill(O1, ZERO, nz)
    return O
```