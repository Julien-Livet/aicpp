```python
def dsl1(I):
    inds = asindices(I)
    ctr = center(inds)
    mover = fork(add, identity, compose(double, compose(sign, lbind(subtract, ctr))))
    pal = remove(ZERO, palette(I))
    pof = lbind(ofcolor, I)
    # original foreground (by colors)
    orig_percolor = fork(recolor, identity, pof)
    orig_objs = apply(orig_percolor, pal)
    orig = merge(orig_objs)
    # moved copies toward center by 2
    moved_patch = compose(lbind(apply, mover), pof)
    moved_percolor = fork(recolor, identity, moved_patch)
    moved_objs = apply(moved_percolor, pal)
    moved = merge(moved_objs)
    # center-of-mass of moved copies for the FIVE
    com = centerofmass(toindices(moved))
    five = recolor(FIVE, initset(com))
    finalobj = combine(orig, combine(moved, five))
    O = paint(canvas(ZERO, shape(I)), finalobj)
    return O

def dsl2(I):
    inds = asindices(I)
    ctr = center(inds)
    mover = fork(add, identity, compose(double, compose(sign, lbind(subtract, ctr))))
    objs = objects(I, T, F, T)
    # keep originals
    orig = merge(objs)
    # move each object pointwise toward center by 2
    movedpatch = compose(lbind(apply, mover), toindices)
    perobj = fork(recolor, color, movedpatch)
    movedobjs = apply(perobj, objs)
    moved = merge(movedobjs)
    com = centerofmass(toindices(moved))
    five = recolor(FIVE, initset(com))
    finalobj = combine(orig, combine(moved, five))
    O = paint(canvas(ZERO, shape(I)), finalobj)
    return O

def dsl3(I):
    inds = asindices(I)
    ctr = center(inds)
    mover = fork(add, identity, compose(double, compose(sign, lbind(subtract, ctr))))
    groups = fgpartition(I)
    # originals
    orig = merge(groups)
    # moved copies
    movedpatch = compose(lbind(apply, mover), toindices)
    pergroup = fork(recolor, color, movedpatch)
    movedgroups = apply(pergroup, groups)
    moved = merge(movedgroups)
    com = centerofmass(toindices(moved))
    five = recolor(FIVE, initset(com))
    finalobj = combine(orig, combine(moved, five))
    O = paint(canvas(ZERO, shape(I)), finalobj)
    return O

def dsl4(I):
    inds = asindices(I)
    ctr = center(inds)
    mover = fork(add, identity, compose(double, compose(sign, lbind(subtract, ctr))))
    pal = remove(ZERO, palette(I))
    pof = lbind(ofcolor, I)
    moved_patch = compose(lbind(apply, mover), pof)
    permoved = fork(recolor, identity, moved_patch)
    movedobjs = apply(permoved, pal)
    moved = merge(movedobjs)
    com = centerofmass(toindices(moved))
    five = recolor(FIVE, initset(com))
    O = underpaint(I, combine(moved, five))
    return O

def dsl5(I):
    inds = asindices(I)
    ctr = center(inds)
    # originals via nonzero mask
    fginds = difference(inds, ofcolor(I, ZERO))
    orig = toobject(fginds, I)
    # per-color constant shift based on color COM toward global center (magnitude 2)
    pal = remove(ZERO, palette(I))
    pof = lbind(ofcolor, I)
    cm_patch = compose(centerofmass, pof)
    dirf = compose(double, compose(sign, compose(lbind(subtract, ctr), cm_patch)))
    shifted = fork(shift, pof, dirf)
    recol = fork(recolor, identity, shifted)
    movedobjs = apply(recol, pal)
    moved = merge(movedobjs)
    com = centerofmass(toindices(moved))
    five = recolor(FIVE, initset(com))
    finalobj = combine(orig, combine(moved, five))
    O = paint(canvas(ZERO, shape(I)), finalobj)
    return O
```