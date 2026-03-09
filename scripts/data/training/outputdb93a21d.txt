```python
def dsl1(I):
    # For each 9-rectangle: draw a 3-outline of its bounding box and a 1-outline just outside it
    obs = colorfilter(objects(I, T, F, T), NINE)
    rects = apply(backdrop, obs)
    inner_borders = apply(box, rects)
    outer_borders = apply(outbox, rects)
    threes = recolor(THREE, merge(inner_borders))
    ones = recolor(ONE, merge(outer_borders))
    O = underpaint(I, combine(threes, ones))
    return O

def dsl2(I):
    # Use the union of all 9-rectangles' bounding boxes: 3 on its outline, 1 on its outer outline
    obs = colorfilter(objects(I, T, F, T), NINE)
    rects = apply(backdrop, obs)
    allrect = merge(rects)
    three_outline = recolor(THREE, box(allrect))
    one_outline = recolor(ONE, outbox(allrect))
    O = underpaint(I, combine(three_outline, one_outline))
    return O

def dsl3(I):
    # For each 9-object: 3 on the object's outline, 1 on the outer outline of that outline
    obs = colorfilter(objects(I, T, F, T), NINE)
    obj_borders = apply(box, obs)
    threes = recolor(THREE, merge(obj_borders))
    outer = apply(outbox, obj_borders)
    ones = recolor(ONE, merge(outer))
    O = underpaint(I, combine(threes, ones))
    return O

def dsl4(I):
    # For each 9-rectangle: 3 on the one-pixel ring just outside it, 1 on the next outside ring
    obs = colorfilter(objects(I, T, F, T), NINE)
    ring1_list = apply(compose(outbox, backdrop), obs)
    ring2_list = apply(outbox, ring1_list)
    threes = recolor(THREE, merge(ring1_list))
    ones = recolor(ONE, merge(ring2_list))
    O = underpaint(I, combine(threes, ones))
    return O

def dsl5(I):
    # For each 9-rectangle: 3 on its bounding-box outline; 1 only on the outline of the outer ring
    obs = colorfilter(objects(I, T, F, T), NINE)
    rects = apply(backdrop, obs)
    inner = apply(box, rects)
    outer_rings = apply(outbox, rects)
    outer_outlines = apply(box, outer_rings)
    threes = recolor(THREE, merge(inner))
    ones = recolor(ONE, merge(outer_outlines))
    O = underpaint(I, combine(threes, ones))
    return O
```