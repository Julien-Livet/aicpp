```python
def dsl1(I):
    # Normalize so the 2-wall is at the bottom, gravitate others to it, then rotate back
    def to_bottom(g):
        h = height(g); w = width(g)
        objs = objects(g, T, F, T)
        twos = colorfilter(objs, TWO)
        wall = first(twos)
        if equality(lowermost(wall), subtract(h, ONE)):
            return g, identity
        if equality(uppermost(wall), ZERO):
            return rot180(g), rot180
        if equality(leftmost(wall), ZERO):
            return rot270(g), rot90
        return rot90(g), rot270
    R, inv = to_bottom(I)
    objsR = objects(R, T, F, T)
    twosR = colorfilter(objsR, TWO)
    wallR = first(twosR)
    restR = difference(objsR, twosR)
    pull = fork(shift, toindices, rbind(gravitate, wallR))
    recol = fork(recolor, color, pull)
    movedR = mapply(recol, restR)
    baseR = paint(canvas(ZERO, shape(R)), wallR)
    packedR = paint(baseR, movedR)
    O = inv(packedR)
    return O

def dsl2(I):
    # Two-stage: place the closest objects to the 2-wall first (paint), then the rest (underpaint)
    g = I
    objs = objects(g, T, F, T)
    twos = colorfilter(objs, TWO)
    wall = first(twos)
    rest = difference(objs, twos)
    # distance to wall by manhattan
    dist = rbind(manhattan, wall)
    # partition into nearest and others
    dmin = valmin(rest, dist)
    near = sfilter(rest, matcher(dist, dmin))
    far = difference(rest, near)
    pull = fork(shift, toindices, rbind(gravitate, wall))
    recol = fork(recolor, color, pull)
    near_moved = mapply(recol, near)
    far_moved = mapply(recol, far)
    base = paint(canvas(ZERO, shape(g)), wall)
    stage1 = paint(base, near_moved)
    O = underpaint(stage1, far_moved)
    return O

def dsl3(I):
    # Gravitate per color-group (treat all cells of a color as one rigid object), except color 2
    g = I
    base = paint(canvas(ZERO, shape(g)), first(colorfilter(objects(g, T, F, T), TWO)))
    objs = objects(g, T, F, T)
    wall = first(colorfilter(objs, TWO))
    cols = remove(TWO, palette(g))
    def place_color(c):
        patch = ofcolor(g, c)
        objc = toobject(patch, g)
        shifted = shift(toindices(objc), gravitate(objc, wall))
        return recolor(c, shifted)
    moved = mapply(place_color, cols)
    O = paint(base, moved)
    return O

def dsl4(I):
    # Orientation-aware gravitation with ordering heuristic: place by proximity to wall (descending)
    g = I
    h = height(g); w = width(g)
    objs = objects(g, T, F, T)
    twos = colorfilter(objs, TWO)
    wall = first(twos)
    rest = difference(objs, twos)
    # determine side of wall to set ordering key
    on_left = equality(leftmost(wall), ZERO)
    on_right = equality(rightmost(wall), subtract(w, ONE))
    on_top = equality(uppermost(wall), ZERO)
    # choose key so that "near wall first"
    key = branch(on_left, leftmost,
          branch(on_right, compose(invert, rightmost),
          branch(on_top, uppermost, compose(invert, lowermost))))
    ordered = order(rest, key)
    pull = fork(shift, toindices, rbind(gravitate, wall))
    recol = fork(recolor, color, pull)
    moved = mapply(recol, ordered)
    base = paint(canvas(ZERO, shape(g)), wall)
    O = paint(base, moved)
    return O

def dsl5(I):
    # Normalize to the side where the 2-wall is vertical (left or right); if horizontal, rotate to bottom; then gravitate; rotate back
    g = I
    h = height(g); w = width(g)
    objs = objects(g, T, F, T)
    twos = colorfilter(objs, TWO)
    wall = first(twos)
    # choose rotation to make wall vertical-left if vertical, else bottom
    if equality(leftmost(wall), ZERO):
        R = g; inv = identity
    elif equality(rightmost(wall), subtract(w, ONE)):
        R = rot180(g); inv = rot180
    elif equality(uppermost(wall), ZERO):
        R = rot90(g); inv = rot270
    else:
        R = g; inv = identity
    objsR = objects(R, T, F, T)
    wallR = first(colorfilter(objsR, TWO))
    restR = difference(objsR, colorfilter(objsR, TWO))
    pull = fork(shift, toindices, rbind(gravitate, wallR))
    recol = fork(recolor, color, pull)
    movedR = mapply(recol, restR)
    baseR = paint(canvas(ZERO, shape(R)), wallR)
    packedR = paint(baseR, movedR)
    O = inv(packedR)
    return O
```