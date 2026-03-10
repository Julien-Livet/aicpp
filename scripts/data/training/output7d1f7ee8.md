```python
def dsl1(I):
    # Priority painting: recolor interior nonzero cells per frame, paint smaller frame first, larger last
    a = objects(I, T, F, T)
    isframe = fork(equality, toindices, box)
    frames = sfilter(a, isframe)
    perim = compose(size, toindices)
    small = argmin(frames, perim)
    large = argmax(frames, perim)
    nz = difference(asindices(I), ofcolor(I, ZERO))
    inter_nz = lbind(intersection, nz)
    f = fork(recolor, color, compose(inter_nz, delta))
    s1 = f(small)
    s2 = f(large)
    O1 = paint(I, s1)
    O = paint(O1, s2)
    return O

def dsl2(I):
    # Same rule as dsl1 but via sorted order (ascending perimeter), sequentially painted
    a = objects(I, T, F, T)
    isframe = fork(equality, toindices, box)
    frames = sfilter(a, isframe)
    perim = compose(size, toindices)
    ords = order(frames, perim)
    nz = difference(asindices(I), ofcolor(I, ZERO))
    inter_nz = lbind(intersection, nz)
    f = fork(recolor, color, compose(inter_nz, delta))
    mo1 = f(first(ords))
    mo2 = f(last(ords))
    O = paint(paint(I, mo1), mo2)
    return O

def dsl3(I):
    # Outer-only hypothesis: recolor interior nonzero cells using only the largest (outermost) frame
    a = objects(I, T, F, T)
    isframe = fork(equality, toindices, box)
    frames = sfilter(a, isframe)
    perim = compose(size, toindices)
    outer = argmax(frames, perim)
    nz = difference(asindices(I), ofcolor(I, ZERO))
    inter_nz = lbind(intersection, nz)
    mo = fork(recolor, color, compose(inter_nz, delta))(outer)
    O = paint(I, mo)
    return O

def dsl4(I):
    # Recolor any object fully enclosed by any frame to that frame’s color (object-wise mapping)
    objs = objects(I, T, F, T)
    isframe = fork(equality, toindices, box)
    frames = sfilter(objs, isframe)
    pairs = product(objs, frames)
    # object is inside frame if its indices equal their intersection with the frame's interior (delta)
    inside = fork(
        equality,
        compose(toindices, first),
        compose(lbind(intersection, compose(toindices, first)), compose(delta, last))
    )
    enclosed = mfilter(pairs, inside)
    recol = fork(recolor, compose(color, last), compose(toindices, first))
    recolored = apply(recol, enclosed)
    mo = merge(recolored)
    O = paint(I, mo)
    return O

def dsl5(I):
    # Split-and-apply: process left and right halves independently with outermost-frame recolor
    def proc(G):
        a = objects(G, T, F, T)
        isframe = fork(equality, toindices, box)
        frames = sfilter(a, isframe)
        perim = compose(size, toindices)
        outer = argmax(frames, perim)
        nz = difference(asindices(G), ofcolor(G, ZERO))
        inter_nz = lbind(intersection, nz)
        mo = fork(recolor, color, compose(inter_nz, delta))(outer)
        return paint(G, mo)
    L = lefthalf(I)
    R = righthalf(I)
    OL = proc(L)
    OR = proc(R)
    O = hconcat(OL, OR)
    return O
```