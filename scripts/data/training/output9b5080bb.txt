```python
def dsl1(I):
    # Rotate colors along the cycle 1->8->4->2->1 using pairwise switches
    x1 = switch(I, ONE, EIGHT)
    x2 = switch(x1, ONE, FOUR)
    O = switch(x2, ONE, TWO)
    return O

def dsl2(I):
    # For each object's bbox: where it's TWO, paint bbox-on-8 as ONE; where it's FOUR, paint bbox-on-8 as TWO
    # Also turn original background 1-cells into 8 (but keep newly created 1s intact)
    x8 = ofcolor(I, EIGHT)
    x2 = toobject(ofcolor(I, TWO), I)
    x4 = toobject(ofcolor(I, FOUR), I)
    b2 = box(x2)
    b4 = box(x4)
    m21 = intersection(b2, x8)
    m42 = intersection(b4, x8)
    y1 = fill(I, ONE, m21)
    y2 = fill(y1, TWO, m42)
    bg1 = ofcolor(I, ONE)
    O = fill(y2, EIGHT, bg1)
    return O

def dsl3(I):
    # Like dsl2 but use the delta ring (bbox minus object) around TWO/FOUR objects intersected with EIGHT
    # Then convert original 1-cells to 8
    x8 = ofcolor(I, EIGHT)
    x2 = toobject(ofcolor(I, TWO), I)
    x4 = toobject(ofcolor(I, FOUR), I)
    r2 = delta(x2)
    r4 = delta(x4)
    m21 = intersection(r2, x8)
    m42 = intersection(r4, x8)
    y1 = fill(I, ONE, m21)
    y2 = fill(y1, TWO, m42)
    bg1 = ofcolor(I, ONE)
    O = fill(y2, EIGHT, bg1)
    return O

def dsl4(I):
    # Swap the least common and most common colors in the grid
    cmin = leastcolor(I)
    cmax = mostcolor(I)
    O = switch(I, cmin, cmax)
    return O

def dsl5(I):
    # Inverse rotation: 1->2, 2->4, 4->8, 8->1 via pairwise switches
    x1 = switch(I, ONE, TWO)
    x2 = switch(x1, ONE, FOUR)
    O = switch(x2, ONE, EIGHT)
    return O
```