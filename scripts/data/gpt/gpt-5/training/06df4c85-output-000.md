```python
def dsl1(I):
    # Global transform: compress the grid structure
    O = compress(I)
    return O

def dsl2(I):
    # Object-level vertical propagation between same-color occurrences
    s = mostcolor(I)
    objs = objects(I, T, F, T)
    notS = mfilter(objs, compose(flip, matcher(color, s)))
    colors = apply(color, notS)
    grouped = apply(merge, apply(lbind(colorfilter, notS), colors))
    dims = shape(I)

    idxF = toindices
    upF = compose(merge, lbind(apply, rbind(shoot, UP)))
    dnF = compose(merge, lbind(apply, rbind(shoot, DOWN)))
    upIdx = compose(upF, idxF)
    dnIdx = compose(dnF, idxF)
    vlines = fork(combine, upIdx, dnIdx)
    bbox = backdrop
    vmask = fork(intersection, vlines, bbox)

    canF = compose(rbind(canvas, dims), color)
    objFromMask = fork(toobject, vmask, canF)

    P = mapply(objFromMask, grouped)
    O = underpaint(I, P)
    return O

def dsl3(I):
    # Color-filtered horizontal propagation between same-color occurrences
    s = mostcolor(I)
    objs = objects(I, T, F, T)
    notS = mfilter(objs, compose(flip, matcher(color, s)))
    colors = apply(color, notS)
    grouped = apply(merge, apply(lbind(colorfilter, notS), colors))
    dims = shape(I)

    idxF = toindices
    lfF = compose(merge, lbind(apply, rbind(shoot, LEFT)))
    rtF = compose(merge, lbind(apply, rbind(shoot, RIGHT)))
    lfIdx = compose(lfF, idxF)
    rtIdx = compose(rtF, idxF)
    hlines = fork(combine, lfIdx, rtIdx)
    bbox = backdrop
    hmask = fork(intersection, hlines, bbox)

    canF = compose(rbind(canvas, dims), color)
    objFromMask = fork(toobject, hmask, canF)

    P = mapply(objFromMask, grouped)
    O = underpaint(I, P)
    return O

def dsl4(I):
    # Geometric reasoning: draw the bounding box outline of each color group
    s = mostcolor(I)
    objs = objects(I, T, F, T)
    notS = mfilter(objs, compose(flip, matcher(color, s)))
    colors = apply(color, notS)
    grouped = apply(merge, apply(lbind(colorfilter, notS), colors))
    dims = shape(I)

    outline = compose(box, normalize)  # outline (box) around grouped color
    # Use original (unnormalized) group's bbox outline instead
    outline = box  # keep it simple: box around the group's support
    canF = compose(rbind(canvas, dims), color)
    objFromOutline = fork(toobject, outline, canF)

    P = mapply(objFromOutline, grouped)
    O = underpaint(I, P)
    return O

def dsl5(I):
    # Relational/structural: combined vertical and horizontal propagation per color
    s = mostcolor(I)
    objs = objects(I, T, F, T)
    notS = mfilter(objs, compose(flip, matcher(color, s)))
    colors = apply(color, notS)
    grouped = apply(merge, apply(lbind(colorfilter, notS), colors))
    dims = shape(I)

    idxF = toindices
    upF = compose(merge, lbind(apply, rbind(shoot, UP)))
    dnF = compose(merge, lbind(apply, rbind(shoot, DOWN)))
    lfF = compose(merge, lbind(apply, rbind(shoot, LEFT)))
    rtF = compose(merge, lbind(apply, rbind(shoot, RIGHT)))
    upIdx = compose(upF, idxF)
    dnIdx = compose(dnF, idxF)
    lfIdx = compose(lfF, idxF)
    rtIdx = compose(rtF, idxF)

    vlines = fork(combine, upIdx, dnIdx)
    hlines = fork(combine, lfIdx, rtIdx)
    bbox = backdrop
    vmask = fork(intersection, vlines, bbox)
    hmask = fork(intersection, hlines, bbox)
    mask = fork(combine, vmask, hmask)

    canF = compose(rbind(canvas, dims), color)
    objFromMask = fork(toobject, mask, canF)

    P = mapply(objFromMask, grouped)
    O = underpaint(I, P)
    return O
```