```python
def dsl1(I):
    # Move every non-background, non-zero object until it touches the nearest zero-region, then stamp it there.
    objs = objects(I, T, F, T)
    zobjs = colorfilter(objs, ZERO)
    dst = merge(zobjs)
    nz = difference(objs, zobjs)
    shifter = fork(shift, identity, rbind(gravitate, dst))
    stamper = fork(recolor, color, shifter)
    stamps = merge(apply(stamper, nz))
    O = underpaint(I, stamps)
    return O

def dsl2(I):
    # Same as dsl1 but overshoot by 2x the gravitate vector to place marks a bit further from source.
    objs = objects(I, T, F, T)
    zobjs = colorfilter(objs, ZERO)
    dst = merge(zobjs)
    nz = difference(objs, zobjs)
    vfun = compose(double, rbind(gravitate, dst))
    shifter = fork(shift, identity, vfun)
    stamper = fork(recolor, color, shifter)
    stamps = merge(apply(stamper, nz))
    O = underpaint(I, stamps)
    return O

def dsl3(I):
    # Outline every zero-component’s bounding box with the color of the globally nearest nonzero object to any zero.
    objs = objects(I, T, F, T)
    zobjs = colorfilter(objs, ZERO)
    dst = merge(zobjs)
    nz = difference(objs, zobjs)
    nearest = argmin(nz, lbind(manhattan, dst))
    c = color(nearest)
    boxes = apply(box, zobjs)
    colored_boxes = apply(lbind(recolor, c), boxes)
    frame = merge(colored_boxes)
    O = underpaint(I, frame)
    return O

def dsl4(I):
    # Move each nonzero object to the zero-region and then expand it to its backdrop (local bbox fill) before stamping.
    objs = objects(I, T, F, T)
    zobjs = colorfilter(objs, ZERO)
    dst = merge(zobjs)
    nz = difference(objs, zobjs)
    shifter = fork(shift, identity, rbind(gravitate, dst))
    # For each shifted object, fill its backdrop (local bbox) with its color
    backpatch = compose(backdrop, shifter)
    painter = fork(recolor, color, backpatch)
    stamps = merge(apply(painter, nz))
    O = underpaint(I, stamps)
    return O

def dsl5(I):
    # Move each nonzero object to the bounding box (outline) of the zero union and stamp there.
    objs = objects(I, T, F, T)
    zobjs = colorfilter(objs, ZERO)
    dst = merge(zobjs)
    border = box(dst)
    nz = difference(objs, zobjs)
    shifter = fork(shift, identity, rbind(gravitate, border))
    stamper = fork(recolor, color, shifter)
    stamps = merge(apply(stamper, nz))
    O = underpaint(I, stamps)
    return O
```