```python
def dsl1(I):
    R = rot90(I)
    aidx = ofcolor(R, TWO)
    bidx = ofcolor(R, FIVE)
    d = gravitate(aidx, bidx)
    base = fill(R, SEVEN, aidx)
    tgt = shift(aidx, d)
    R2 = fill(base, TWO, tgt)
    O = rot270(R2)
    return O

def dsl2(I):
    aidx = ofcolor(I, TWO)
    bidx = ofcolor(I, FIVE)
    aobj = toobject(aidx, I)
    d = gravitate(aidx, bidx)
    base = cover(I, aobj)
    O = paint(base, recolor(TWO, shift(aobj, d)))
    return O

def dsl3(I):
    aidx = ofcolor(I, TWO)
    bidx = ofcolor(I, FIVE)
    d = gravitate(aidx, bidx)
    base = replace(I, TWO, SEVEN)
    O = underpaint(base, recolor(TWO, shift(aidx, d)))
    return O

def dsl4(I):
    objs = objects(I, T, F, T)
    a = first(colorfilter(objs, TWO))
    b = first(colorfilter(objs, FIVE))
    A = toindices(a)
    B = toindices(b)
    d = gravitate(box(A), box(B))
    base = cover(I, a)
    O = paint(base, shift(recolor(TWO, a), d))
    return O

def dsl5(I):
    A = ofcolor(I, TWO)
    B = ofcolor(I, FIVE)
    hr = rightmost(A)
    hl = leftmost(A)
    br = rightmost(B)
    bl = leftmost(B)
    at = uppermost(A)
    ab = lowermost(A)
    bt = uppermost(B)
    bb = lowermost(B)
    condR = greater(bl, hr)
    condL = greater(hl, br)
    moveR = subtract(subtract(bl, hr), ONE)
    moveL = add(subtract(br, hl), ONE)
    hvec = branch(condR, tojvec(moveR), branch(condL, tojvec(moveL), ORIGIN))
    condD = greater(bt, ab)
    condU = greater(at, bb)
    downVal = subtract(subtract(bt, ab), ONE)
    upVal = add(subtract(bb, at), ONE)
    vvec = branch(condD, toivec(downVal), branch(condU, toivec(upVal), ORIGIN))
    d = add(hvec, vvec)
    base = replace(I, TWO, SEVEN)
    O = fill(base, TWO, shift(A, d))
    return O
```