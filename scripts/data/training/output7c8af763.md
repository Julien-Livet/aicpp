```python
def dsl1(I):
    # Fill each zero-component with the majority color (1 or 2) among its 4-neighborhood ring
    G = I
    comps = colorfilter(objects(I, True, False, False), ZERO)
    for comp in totuple(comps):
        rim = difference(mapply(neighbors, toindices(comp)), toindices(comp))
        rim_obj = toobject(rim, I)
        c1 = colorcount(rim_obj, ONE)
        c2 = colorcount(rim_obj, TWO)
        chosen = branch(greater(c2, c1), TWO, ONE)
        G = fill(G, chosen, toindices(comp))
    return G

def dsl2(I):
    # Like dsl1 but consider 8-neighborhood (4-neighbors + diagonals)
    G = I
    comps = colorfilter(objects(I, True, False, False), ZERO)
    for comp in totuple(comps):
        ring4 = difference(mapply(neighbors, toindices(comp)), toindices(comp))
        ringd = difference(mapply(ineighbors, toindices(comp)), toindices(comp))
        rim = difference(combine(ring4, ringd), toindices(comp))
        rim_obj = toobject(rim, I)
        c1 = colorcount(rim_obj, ONE)
        c2 = colorcount(rim_obj, TWO)
        chosen = branch(greater(c2, c1), TWO, ONE)
        G = fill(G, chosen, toindices(comp))
    return G

def dsl3(I):
    # Majority based on the bounding-box outline around each zero-component
    G = I
    comps = colorfilter(objects(I, True, False, False), ZERO)
    for comp in totuple(comps):
        outline = difference(box(toindices(comp)), toindices(comp))
        rim_obj = toobject(outline, I)
        c1 = colorcount(rim_obj, ONE)
        c2 = colorcount(rim_obj, TWO)
        chosen = branch(greater(c2, c1), TWO, ONE)
        G = fill(G, chosen, toindices(comp))
    return G

def dsl4(I):
    # Majority based on all non-component cells within the component's bounding box (delta)
    G = I
    comps = colorfilter(objects(I, True, False, False), ZERO)
    for comp in totuple(comps):
        ring_bb = delta(toindices(comp))
        rim_obj = toobject(ring_bb, I)
        c1 = colorcount(rim_obj, ONE)
        c2 = colorcount(rim_obj, TWO)
        chosen = branch(greater(c2, c1), TWO, ONE)
        G = fill(G, chosen, toindices(comp))
    return G

def dsl5(I):
    # Weighted majority: 4-neighbors count double, diagonals count single
    G = I
    comps = colorfilter(objects(I, True, False, False), ZERO)
    for comp in totuple(comps):
        ring4 = difference(mapply(neighbors, toindices(comp)), toindices(comp))
        ringd = difference(mapply(ineighbors, toindices(comp)), toindices(comp))
        obj4 = toobject(ring4, I)
        objd = toobject(ringd, I)
        c1 = add(multiply(colorcount(obj4, ONE), TWO), colorcount(objd, ONE))
        c2 = add(multiply(colorcount(obj4, TWO), TWO), colorcount(objd, TWO))
        chosen = branch(greater(c2, c1), TWO, ONE)
        G = fill(G, chosen, toindices(comp))
    return G
```