```python
def dsl1(I):
    # Global triple ring around the union of all 1-cells
    O = I
    ones = ofcolor(I, ONE)
    if size(ones) > 0:
        obj = toobject(ones, I)
        rect = backdrop(obj)
        innerrect = backdrop(inbox(rect))
        O = underpaint(O, recolor(TWO, outbox(rect)))
        O = underpaint(O, recolor(EIGHT, box(rect)))
        O = underpaint(O, recolor(SIX, box(innerrect)))
    return O

def dsl2(I):
    # Replace 1 -> 8, put a 6 at the center of mass of all 1s, and add a 2 outbox ring around their bbox
    O = replace(I, ONE, EIGHT)
    ones = ofcolor(I, ONE)
    if size(ones) > 0:
        obj = toobject(ones, I)
        rect = backdrop(obj)
        O = underpaint(O, recolor(TWO, outbox(rect)))
        c = centerofmass(obj)
        O = fill(O, SIX, initset(c))
    return O

def dsl3(I):
    # Paint frontiers with 2; for each 1-object (diagonal-merged) add 8 border and inner 6 ring
    O = I
    frs = frontiers(I)
    P = merge(frs)
    O = underpaint(O, recolor(TWO, P))
    onesobjs = colorfilter(objects(I, True, True, True), ONE)
    for obj in onesobjs:
        rect = backdrop(obj)
        O = underpaint(O, recolor(EIGHT, box(rect)))
        inner = backdrop(inbox(rect))
        O = underpaint(O, recolor(SIX, box(inner)))
    return O

def dsl4(I):
    # Outer ring 2 around bbox of all non-4 cells; for each 1-object fill inner area with 6 and outline with 8
    O = I
    allidx = asindices(I)
    bg = ofcolor(I, FOUR)
    occ = difference(allidx, bg)
    if size(occ) > 0:
        rect_all = backdrop(toobject(occ, I))
        O = underpaint(O, recolor(TWO, outbox(rect_all)))
    onesobjs = colorfilter(objects(I, True, False, True), ONE)
    for obj in onesobjs:
        rect = backdrop(obj)
        inner = inbox(rect)
        O = fill(O, SIX, inner)
        O = underpaint(O, recolor(EIGHT, box(rect)))
    return O

def dsl5(I):
    # For each 1-object, draw 2 outbox, 8 border, and a 6 cross through the center of its bbox
    O = I
    onesobjs = colorfilter(objects(I, True, False, True), ONE)
    for obj in onesobjs:
        rect = backdrop(obj)
        c = center(rect)
        li = leftmost(rect)
        ri = rightmost(rect)
        ui = uppermost(rect)
        lo = lowermost(rect)
        hlinep = connect(astuple(c[0], li), astuple(c[0], ri))
        vlinep = connect(astuple(ui, c[1]), astuple(lo, c[1]))
        cross = combine(hlinep, vlinep)
        O = fill(O, SIX, cross)
        O = underpaint(O, recolor(TWO, outbox(rect)))
        O = underpaint(O, recolor(EIGHT, box(rect)))
    return O
```