```python
def dsl1(I):
    parts = colorfilter(fgpartition(I), ONE)
    erode = fork(difference, toindices, box)
    inner1_list = apply(erode, parts)
    inner2_list = apply(erode, inner1_list)
    ring2 = merge(apply(box, inner2_list))
    inner1 = merge(inner1_list)
    O = fill(I, TWO, inner1)
    O = fill(O, THREE, ring2)
    return O

def dsl2(I):
    comps = colorfilter(objects(I, True, False, True), ONE)
    erode = fork(difference, toindices, box)
    shrink2 = compose(erode, erode)
    inner1 = merge(apply(erode, comps))
    inner2_list = apply(shrink2, comps)
    ring2 = merge(apply(box, inner2_list))
    O = fill(I, TWO, inner1)
    O = fill(O, THREE, ring2)
    return O

def dsl3(I):
    comps = colorfilter(objects(I, True, False, True), ONE)
    erode = fork(difference, toindices, box)
    inner1_list = apply(erode, comps)
    inner2_list = apply(erode, inner1_list)
    ring2 = merge(apply(outbox, inner2_list))
    inner1 = merge(inner1_list)
    O = fill(I, TWO, inner1)
    O = fill(O, THREE, ring2)
    return O

def dsl4(I):
    comps = colorfilter(objects(I, True, False, True), ONE)
    erode = fork(difference, toindices, box)
    inner1_list = apply(erode, comps)
    inner2_list = apply(erode, inner1_list)
    ring2_list = apply(fork(difference, box, toindices), inner2_list)
    inner1 = merge(inner1_list)
    ring2 = merge(ring2_list)
    O = fill(I, TWO, inner1)
    O = fill(O, THREE, ring2)
    return O

def dsl5(I):
    parts = colorfilter(fgpartition(I), ONE)
    innermaker = fork(difference, toindices, box)
    inner1_list = apply(innermaker, parts)
    inner2_list = apply(innermaker, inner1_list)
    ring2 = merge(apply(box, inner2_list))
    inner1 = merge(inner1_list)
    O = fill(I, TWO, inner1)
    O = fill(O, THREE, ring2)
    return O
```