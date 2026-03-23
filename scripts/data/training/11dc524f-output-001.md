```python
def dsl1(I):
    J = dmirror(I)
    objs = objects(J, T, F, T)
    a = first(colorfilter(objs, TWO))
    b = first(colorfilter(objs, FIVE))
    d = gravitate(toindices(a), toindices(b))
    base = cover(J, a)
    K = move(base, a, d)
    O = dmirror(K)
    return O

def dsl2(I):
    objs = objects(I, T, F, T)
    a = first(colorfilter(objs, TWO))
    b = first(colorfilter(objs, FIVE))
    A = toindices(a)
    B = toindices(b)
    hcase = hmatching(A, B)
    dxl = subtract(subtract(leftmost(b), rightmost(a)), ONE)
    dxr = subtract(subtract(leftmost(a), rightmost(b)), ONE)
    isleft = greater(leftmost(b), rightmost(a))
    sx = branch(isleft, dxl, invert(dxr))
    vx = tojvec(sx)
    dyl = subtract(subtract(uppermost(b), lowermost(a)), ONE)
    dyr = subtract(subtract(uppermost(a), lowermost(b)), ONE)
    isabove = greater(uppermost(b), lowermost(a))
    sy = branch(isabove, dyl, invert(dyr))
    vy = toivec(sy)
    d = branch(hcase, vx, vy)
    base = cover(I, a)
    O = move(base, a, d)
    return O

def dsl3(I):
    objs = objects(I, T, F, T)
    a = first(colorfilter(objs, TWO))
    b = first(colorfilter(objs, FIVE))
    d = gravitate(toindices(a), toindices(b))
    tgt = shift(toindices(a), d)
    base = fill(I, SEVEN, toindices(a))
    O = fill(base, TWO, tgt)
    return O

def dsl4(I):
    R = rot90(I)
    objs = objects(R, T, F, T)
    a = first(colorfilter(objs, TWO))
    b = first(colorfilter(objs, FIVE))
    d = gravitate(toindices(a), toindices(b))
    base = cover(R, a)
    R2 = paint(base, shift(a, d))
    O = rot270(R2)
    return O

def dsl5(I):
    aidx = ofcolor(I, TWO)
    bidx = ofcolor(I, FIVE)
    d = gravitate(aidx, bidx)
    base = fill(I, SEVEN, aidx)
    tgt = shift(aidx, d)
    O = fill(base, TWO, tgt)
    return O
```