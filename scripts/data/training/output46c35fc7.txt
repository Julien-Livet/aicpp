```python
def dsl1(I):
    O = I
    for obj in totuple(objects(I, F, F, T)):
        sub = subgrid(obj, I)
        idxs = asindices(sub)
        ring = box(idxs)
        crn = corners(idxs)
        cw = rot90(sub)
        ccw = rot270(sub)
        O = move(O, toobject(ring, cw), ulcorner(obj))
        O = move(O, toobject(crn, ccw), ulcorner(obj))
    return O

def dsl2(I):
    O = I
    for obj in totuple(objects(I, F, F, T)):
        sub = subgrid(obj, I)
        frm = box(backdrop(obj))
        crn = corners(backdrop(obj))
        O = move(O, toobject(frm, rot90(sub)), ulcorner(obj))
        O = move(O, toobject(crn, rot270(sub)), ulcorner(obj))
    return O

def dsl3(I):
    O = I
    for obj in totuple(objects(I, F, F, T)):
        sub = subgrid(obj, I)
        idxs = asindices(sub)
        O = cover(O, obj)
        O = move(O, toobject(box(idxs), rot90(sub)), ulcorner(obj))
        O = move(O, toobject(corners(idxs), rot270(sub)), ulcorner(obj))
    return O

def dsl4(I):
    O = I
    for obj in totuple(objects(I, F, F, T)):
        sub = subgrid(obj, I)
        idxs = asindices(sub)
        cw = rot180(rot270(sub))
        ccw = rot180(rot90(sub))
        O = move(O, toobject(box(idxs), cw), ulcorner(obj))
        O = move(O, toobject(corners(idxs), ccw), ulcorner(obj))
    return O

def dsl5(I):
    O = I
    for obj in totuple(objects(I, F, F, T)):
        sub = subgrid(obj, I)
        idxs = asindices(sub)
        ring = box(idxs)
        crn = corners(idxs)
        edg = difference(ring, crn)
        cw = rot90(sub)
        ccw = rot270(sub)
        O = move(O, toobject(edg, cw), ulcorner(obj))
        O = move(O, toobject(crn, ccw), ulcorner(obj))
    return O
```