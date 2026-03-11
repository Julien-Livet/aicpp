```python
def dsl1(I):
    # Clear the top half; then, for the three largest same-color bands,
    # stamp the delta of the smallest same-color exemplar from the top,
    # recolored with the band’s flank (border) color and aligned by ulcorner.
    bg = mostcolor(I)
    top = tophalf(I)
    bot = bottomhalf(I)
    O = vconcat(canvas(bg, shape(top)), bot)

    objs = objects(I, T, F, T)

    # First largest band
    big1 = argmax(objs, size)
    same1 = colorfilter(objs, color(big1))
    smalls1 = remove(big1, same1)
    small1 = argmin(smalls1, size)
    mot1 = delta(small1)
    off1 = subtract(ulcorner(big1), ulcorner(small1))
    mot1s = shift(mot1, off1)
    col1 = index(I, add(ulcorner(big1), LEFT))
    O = fill(O, col1, mot1s)

    # Second largest band
    objs2 = remove(big1, objs)
    big2 = argmax(objs2, size)
    same2 = colorfilter(objs, color(big2))
    smalls2 = remove(big2, same2)
    small2 = argmin(smalls2, size)
    mot2 = delta(small2)
    off2 = subtract(ulcorner(big2), ulcorner(small2))
    mot2s = shift(mot2, off2)
    col2 = index(I, add(ulcorner(big2), LEFT))
    O = fill(O, col2, mot2s)

    # Third largest band
    objs3 = remove(big2, objs2)
    big3 = argmax(objs3, size)
    same3 = colorfilter(objs, color(big3))
    smalls3 = remove(big3, same3)
    small3 = argmin(smalls3, size)
    mot3 = delta(small3)
    off3 = subtract(ulcorner(big3), ulcorner(small3))
    mot3s = shift(mot3, off3)
    col3 = index(I, add(ulcorner(big3), LEFT))
    O = fill(O, col3, mot3s)

    return O

def dsl2(I):
    # Clear top half; for the two largest bands, stamp a 3x1 horizontal tiling
    # of the smallest same-color exemplar’s delta, recolored with the flank color.
    bg = mostcolor(I)
    O = vconcat(canvas(bg, shape(tophalf(I))), bottomhalf(I))

    objs = objects(I, T, F, T)

    # First band
    big1 = argmax(objs, size)
    same1 = colorfilter(objs, color(big1))
    small1 = argmin(remove(big1, same1), size)
    mot = delta(small1)
    w = width(mot)
    dv = tojvec(w)
    r0 = mot
    r1 = shift(mot, dv)
    r2 = shift(mot, double(dv))
    S = insert(r0, initset(r0))
    S = insert(r1, S)
    S = insert(r2, S)
    row = merge(S)
    off1 = subtract(ulcorner(big1), ulcorner(small1))
    row1s = shift(row, off1)
    col1 = index(I, add(ulcorner(big1), LEFT))
    O = fill(O, col1, row1s)

    # Second band
    objs2 = remove(big1, objs)
    big2 = argmax(objs2, size)
    same2 = colorfilter(objs, color(big2))
    small2 = argmin(remove(big2, same2), size)
    mot2 = delta(small2)
    w2 = width(mot2)
    dv2 = tojvec(w2)
    q0 = mot2
    q1 = shift(mot2, dv2)
    q2 = shift(mot2, double(dv2))
    Q = insert(q0, initset(q0))
    Q = insert(q1, Q)
    Q = insert(q2, Q)
    row2 = merge(Q)
    off2 = subtract(ulcorner(big2), ulcorner(small2))
    row2s = shift(row2, off2)
    col2 = index(I, add(ulcorner(big2), LEFT))
    O = fill(O, col2, row2s)

    return O

def dsl3(I):
    # Only clear the top half to background, keep the rest unchanged.
    bg = mostcolor(I)
    O = vconcat(canvas(bg, shape(tophalf(I))), bottomhalf(I))
    return O

def dsl4(I):
    # Clear top; for two largest bands, stamp a 3x2 tiling of smallest exemplar’s delta,
    # recolored with the band’s flank color, aligned to band’s ulcorner.
    bg = mostcolor(I)
    O = vconcat(canvas(bg, shape(tophalf(I))), bottomhalf(I))

    objs = objects(I, T, F, T)

    # First band
    big1 = argmax(objs, size)
    same1 = colorfilter(objs, color(big1))
    small1 = argmin(remove(big1, same1), size)
    mot = delta(small1)
    w = width(mot)
    h = height(mot)
    dv = tojvec(w)
    iv = toivec(h)
    r0 = mot
    r1 = shift(mot, dv)
    r2 = shift(mot, double(dv))
    S = insert(r0, initset(r0))
    S = insert(r1, S)
    S = insert(r2, S)
    row = merge(S)
    row2 = shift(row, iv)
    Tset = insert(row, initset(row))
    Tset = insert(row2, Tset)
    tile = merge(Tset)
    off1 = subtract(ulcorner(big1), ulcorner(small1))
    tile1s = shift(tile, off1)
    col1 = index(I, add(ulcorner(big1), LEFT))
    O = fill(O, col1, tile1s)

    # Second band
    objs2 = remove(big1, objs)
    big2 = argmax(objs2, size)
    same2 = colorfilter(objs, color(big2))
    small2 = argmin(remove(big2, same2), size)
    mot2 = delta(small2)
    w2 = width(mot2)
    h2 = height(mot2)
    dv2 = tojvec(w2)
    iv2 = toivec(h2)
    q0 = mot2
    q1 = shift(mot2, dv2)
    q2 = shift(mot2, double(dv2))
    Q = insert(q0, initset(q0))
    Q = insert(q1, Q)
    Q = insert(q2, Q)
    rowb = merge(Q)
    rowb2 = shift(rowb, iv2)
    Uset = insert(rowb, initset(rowb))
    Uset = insert(rowb2, Uset)
    tile2 = merge(Uset)
    off2 = subtract(ulcorner(big2), ulcorner(small2))
    tile2s = shift(tile2, off2)
    col2 = index(I, add(ulcorner(big2), LEFT))
    O = fill(O, col2, tile2s)

    return O

def dsl5(I):
    # Clear top; for the two largest bands, stamp the box (outline) of the smallest same-color exemplar
    # recolored with the band’s flank color and aligned by ulcorner (variation vs delta).
    bg = mostcolor(I)
    O = vconcat(canvas(bg, shape(tophalf(I))), bottomhalf(I))

    objs = objects(I, T, F, T)

    # First band
    big1 = argmax(objs, size)
    same1 = colorfilter(objs, color(big1))
    small1 = argmin(remove(big1, same1), size)
    mot1 = box(small1)
    off1 = subtract(ulcorner(big1), ulcorner(small1))
    mot1s = shift(mot1, off1)
    col1 = index(I, add(ulcorner(big1), LEFT))
    O = fill(O, col1, mot1s)

    # Second band
    objs2 = remove(big1, objs)
    big2 = argmax(objs2, size)
    same2 = colorfilter(objs, color(big2))
    small2 = argmin(remove(big2, same2), size)
    mot2 = box(small2)
    off2 = subtract(ulcorner(big2), ulcorner(small2))
    mot2s = shift(mot2, off2)
    col2 = index(I, add(ulcorner(big2), LEFT))
    O = fill(O, col2, mot2s)

    return O
```