```python
def dsl1(I):
    # Center all FIVE pixels inside the inner rectangle (of TWOs) both horizontally and vertically.
    x2 = ofcolor(I, TWO)
    o2 = toobject(x2, I)
    interior = delta(o2)
    iU = uppermost(interior)
    iL = leftmost(interior)
    HI = height(interior)
    WI = width(interior)
    x5 = ofcolor(I, FIVE)
    o5 = toobject(x5, I)
    h5 = height(o5)
    w5 = width(o5)
    offi = subtract(add(iU, divide(subtract(HI, h5), TWO)), uppermost(o5))
    offj = subtract(add(iL, divide(subtract(WI, w5), TWO)), leftmost(o5))
    shifted = shift(toindices(o5), astuple(offi, offj))
    inside = intersection(shifted, interior)
    base = cover(I, o5)
    O = paint(base, recolor(FIVE, inside))
    return O

def dsl2(I):
    # Center all FIVE pixels horizontally inside the inner rectangle; keep their original rows.
    x2 = ofcolor(I, TWO)
    o2 = toobject(x2, I)
    interior = delta(o2)
    iL = leftmost(interior)
    WI = width(interior)
    x5 = ofcolor(I, FIVE)
    o5 = toobject(x5, I)
    w5 = width(o5)
    offj = subtract(add(iL, divide(subtract(WI, w5), TWO)), leftmost(o5))
    shifted = shift(toindices(o5), astuple(ZERO, offj))
    inside = intersection(shifted, interior)
    base = cover(I, o5)
    O = paint(base, recolor(FIVE, inside))
    return O

def dsl3(I):
    # Center all FIVE pixels vertically inside the inner rectangle; keep their original columns.
    x2 = ofcolor(I, TWO)
    o2 = toobject(x2, I)
    interior = delta(o2)
    iU = uppermost(interior)
    HI = height(interior)
    x5 = ofcolor(I, FIVE)
    o5 = toobject(x5, I)
    h5 = height(o5)
    offi = subtract(add(iU, divide(subtract(HI, h5), TWO)), uppermost(o5))
    shifted = shift(toindices(o5), astuple(offi, ZERO))
    inside = intersection(shifted, interior)
    base = cover(I, o5)
    O = paint(base, recolor(FIVE, inside))
    return O

def dsl4(I):
    # Orientation-driven centering: if FIVE layout is wider than tall, center horizontally; else center vertically.
    x2 = ofcolor(I, TWO)
    o2 = toobject(x2, I)
    interior = delta(o2)
    iU = uppermost(interior)
    iL = leftmost(interior)
    HI = height(interior)
    WI = width(interior)
    x5 = ofcolor(I, FIVE)
    o5 = toobject(x5, I)
    h5 = height(o5)
    w5 = width(o5)
    # compute both offsets
    offi_v = subtract(add(iU, divide(subtract(HI, h5), TWO)), uppermost(o5))
    offj_h = subtract(add(iL, divide(subtract(WI, w5), TWO)), leftmost(o5))
    # choose orientation
    use_h = greater(w5, h5)
    offi = branch(use_h, ZERO, offi_v)
    offj = branch(use_h, offj_h, ZERO)
    shifted = shift(toindices(o5), astuple(offi, offj))
    inside = intersection(shifted, interior)
    base = cover(I, o5)
    O = paint(base, recolor(FIVE, inside))
    return O

def dsl5(I):
    # Center with one-cell margin from inner borders (shrink interior by 2 then center).
    x2 = ofcolor(I, TWO)
    o2 = toobject(x2, I)
    interior = delta(o2)
    iU = add(uppermost(interior), ONE)
    iL = add(leftmost(interior), ONE)
    HI = subtract(height(interior), TWO)
    WI = subtract(width(interior), TWO)
    x5 = ofcolor(I, FIVE)
    o5 = toobject(x5, I)
    h5 = height(o5)
    w5 = width(o5)
    offi = subtract(add(iU, divide(subtract(HI, h5), TWO)), uppermost(o5))
    offj = subtract(add(iL, divide(subtract(WI, w5), TWO)), leftmost(o5))
    shifted = shift(toindices(o5), astuple(offi, offj))
    inside_core = intersection(shifted, interior)
    base = cover(I, o5)
    O = paint(base, recolor(FIVE, inside_core))
    return O
```