```python
def dsl1(I):
    # Copy each gray object away from its nearest border:
    # - place 1-copy horizontally opposite the nearest vertical border by width+1
    # - place 8-copy vertically opposite the nearest horizontal border by height+1
    objs = colorfilter(objects(I, True, False, True), THREE)
    H = height(I)
    W = width(I)
    def hcopy(o):
        w1 = add(width(o), ONE)
        l = leftmost(o)
        r = rightmost(o)
        dL = l
        dR = subtract(subtract(W, ONE), r)
        nearL = flip(greater(dL, dR))
        off = branch(nearL, tojvec(w1), tojvec(invert(w1)))
        return recolor(ONE, toobject(shift(toindices(o), off), I))
    def vcopy(o):
        h1 = add(height(o), ONE)
        u = uppermost(o)
        b = lowermost(o)
        dT = u
        dB = subtract(subtract(H, ONE), b)
        nearT = flip(greater(dT, dB))
        off = branch(nearT, toivec(h1), toivec(invert(h1)))
        return recolor(EIGHT, toobject(shift(toindices(o), off), I))
    ones = merge(apply(hcopy, objs))
    eights = merge(apply(vcopy, objs))
    O = underpaint(I, ones)
    O = underpaint(O, eights)
    return O

def dsl2(I):
    # Only ring-like gray objects (equal to their outline) duplicate:
    # - 1-copy horizontally to the right by width+1
    # - 8-copy vertically downward by height+1
    objs = colorfilter(objects(I, True, False, True), THREE)
    def is_ring(o):
        return equality(size(toindices(o)), size(box(o)))
    rings = sfilter(objs, is_ring)
    def hcopy(o):
        off = tojvec(add(width(o), ONE))
        return recolor(ONE, toobject(shift(toindices(o), off), I))
    def vcopy(o):
        off = toivec(add(height(o), ONE))
        return recolor(EIGHT, toobject(shift(toindices(o), off), I))
    ones = merge(apply(hcopy, rings))
    eights = merge(apply(vcopy, rings))
    O = underpaint(I, ones)
    O = underpaint(O, eights)
    return O

def dsl3(I):
    # Only extremal gray objects duplicate:
    # - topmost object creates a 1-copy to the right by width+1
    # - bottommost object creates an 8-copy downward by height+1
    objs = colorfilter(objects(I, True, False, True), THREE)
    top = argmin(objs, uppermost)
    bot = argmax(objs, lowermost)
    one = recolor(ONE, toobject(shift(toindices(top), tojvec(add(width(top), ONE))), I))
    eight = recolor(EIGHT, toobject(shift(toindices(bot), toivec(add(height(bot), ONE))), I))
    O = underpaint(I, one)
    O = underpaint(O, eight)
    return O

def dsl4(I):
    # Half-plane rule:
    # - gray objects whose rightmost column is in the left half get an 8-copy below by height+1
    # - gray objects in the right half get a 1-copy to the left by width+1
    objs = colorfilter(objects(I, True, False, True), THREE)
    W = width(I)
    mid = divide(W, TWO)
    lefts = sfilter(objs, lambda o: flip(greater(rightmost(o), mid)))
    rights = sfilter(objs, lambda o: greater(rightmost(o), mid))
    def vcopy(o):
        return recolor(EIGHT, toobject(shift(toindices(o), toivec(add(height(o), ONE))), I))
    def hcopy(o):
        return recolor(ONE, toobject(shift(toindices(o), tojvec(invert(add(width(o), ONE)))), I))
    eights = merge(apply(vcopy, lefts))
    ones = merge(apply(hcopy, rights))
    O = underpaint(I, ones)
    O = underpaint(O, eights)
    return O

def dsl5(I):
    # Copy toward the grid center:
    # - if object's horizontal midpoint is in left half -> 1-copy right by width+1 else left
    # - if object's vertical midpoint is in top half -> 8-copy down by height+1 else up
    objs = colorfilter(objects(I, True, False, True), THREE)
    H = height(I)
    W = width(I)
    midW = divide(W, TWO)
    midH = divide(H, TWO)
    def hcopy(o):
        l = leftmost(o)
        r = rightmost(o)
        midcol = divide(add(l, r), TWO)
        w1 = add(width(o), ONE)
        leftHalf = flip(greater(midcol, midW))
        off = branch(leftHalf, tojvec(w1), tojvec(invert(w1)))
        return recolor(ONE, toobject(shift(toindices(o), off), I))
    def vcopy(o):
        u = uppermost(o)
        b = lowermost(o)
        midrow = divide(add(u, b), TWO)
        h1 = add(height(o), ONE)
        topHalf = flip(greater(midrow, midH))
        off = branch(topHalf, toivec(h1), toivec(invert(h1)))
        return recolor(EIGHT, toobject(shift(toindices(o), off), I))
    ones = merge(apply(hcopy, objs))
    eights = merge(apply(vcopy, objs))
    O = underpaint(I, ones)
    O = underpaint(O, eights)
    return O
```