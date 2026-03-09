```python
def dsl1(I):
    # Replicate the largest 8-object wherever its bounding-ring (outbox) pattern occurs
    O = I
    domain = asindices(I)
    comps = objects(I, True, False, True)
    eights = colorfilter(comps, EIGHT)
    if size(eights) == 0:
        return O
    seed = argmax(eights, size)
    ring = outbox(seed)
    if size(ring) == 0:
        return O
    ctx = normalize(toobject(ring, I))
    occs = occurrences(I, ctx)
    pat = toindices(normalize(seed))
    mask = difference(domain, domain)
    for p in totuple(occs):
        mask = combine(mask, shift(pat, p))
    O = fill(O, EIGHT, mask)
    return O

def dsl2(I):
    # Replicate every 8-object using its own outbox-context occurrences; union all replications
    O = I
    domain = asindices(I)
    comps = objects(I, True, False, True)
    eights = colorfilter(comps, EIGHT)
    if size(eights) == 0:
        return O
    mask = difference(domain, domain)
    for obj in totuple(eights):
        ring = outbox(obj)
        if size(ring) == 0:
            continue
        ctx = normalize(toobject(ring, I))
        occs = occurrences(I, ctx)
        pat = toindices(normalize(obj))
        for p in totuple(occs):
            mask = combine(mask, shift(pat, p))
    O = fill(O, EIGHT, mask)
    return O

def dsl3(I):
    # Use a stronger context: outbox plus the four bounding-box corners of the 8-object
    O = I
    domain = asindices(I)
    comps = objects(I, True, False, True)
    eights = colorfilter(comps, EIGHT)
    if size(eights) == 0:
        return O
    seed = argmax(eights, size)
    ring = outbox(seed)
    ctxpatch = combine(ring, corners(seed))
    if size(ctxpatch) == 0:
        return O
    ctx = normalize(toobject(ctxpatch, I))
    occs = occurrences(I, ctx)
    pat = toindices(normalize(seed))
    mask = difference(domain, domain)
    for p in totuple(occs):
        mask = combine(mask, shift(pat, p))
    O = fill(O, EIGHT, mask)
    return O

def dsl4(I):
    # Use full bounding box outline (box) of the largest 8-object as the matching context
    O = I
    domain = asindices(I)
    comps = objects(I, True, False, True)
    eights = colorfilter(comps, EIGHT)
    if size(eights) == 0:
        return O
    seed = argmax(eights, size)
    outline = box(seed)
    if size(outline) == 0:
        return O
    ctx = normalize(toobject(outline, I))
    occs = occurrences(I, ctx)
    pat = toindices(normalize(seed))
    mask = difference(domain, domain)
    for p in totuple(occs):
        mask = combine(mask, shift(pat, p))
    O = fill(O, EIGHT, mask)
    return O

def dsl5(I):
    # Two-step neighbor template: match colors at distance 1 and 2 in all four directions
    O = I
    H, W = height(I), width(I)
    domain = asindices(I)
    comps = objects(I, True, False, True)
    eights = colorfilter(comps, EIGHT)
    if size(eights) == 0:
        return O
    mask = difference(domain, domain)
    for obj in totuple(eights):
        for c in totuple(toindices(obj)):
            cu = index(I, add(c, UP))
            cd = index(I, add(c, DOWN))
            cl = index(I, add(c, LEFT))
            cr = index(I, add(c, RIGHT))
            cu2 = index(I, add(c, add(UP, UP)))
            cd2 = index(I, add(c, add(DOWN, DOWN)))
            cl2 = index(I, add(c, add(LEFT, LEFT)))
            cr2 = index(I, add(c, add(RIGHT, RIGHT)))
            S = domain
            # one-step neighbors
            S = intersection(S, shift(ofcolor(I, cu), DOWN))
            S = intersection(S, shift(ofcolor(I, cd), UP))
            S = intersection(S, shift(ofcolor(I, cl), RIGHT))
            S = intersection(S, shift(ofcolor(I, cr), LEFT))
            # two-step neighbors
            S = intersection(S, shift(ofcolor(I, cu2), add(DOWN, DOWN)))
            S = intersection(S, shift(ofcolor(I, cd2), add(UP, UP)))
            S = intersection(S, shift(ofcolor(I, cl2), add(RIGHT, RIGHT)))
            S = intersection(S, shift(ofcolor(I, cr2), add(LEFT, LEFT)))
            mask = combine(mask, S)
    mask = intersection(mask, domain)
    O = fill(O, EIGHT, mask)
    return O
```