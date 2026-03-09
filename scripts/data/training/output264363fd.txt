```python
def dsl1(I):
    # Plus from each 4; map along lines: 1->2, 2->3, 3->4
    seeds4 = ofcolor(I, FOUR)
    H = merge(apply(hfrontier, seeds4))
    V = merge(apply(vfrontier, seeds4))
    O = I
    O = fill(O, TWO,   intersection(H, ofcolor(I, ONE)))
    O = fill(O, TWO,   intersection(V, ofcolor(I, ONE)))
    O = fill(O, THREE, intersection(H, ofcolor(I, TWO)))
    O = fill(O, THREE, intersection(V, ofcolor(I, TWO)))
    O = fill(O, FOUR,  intersection(H, ofcolor(I, THREE)))
    O = fill(O, FOUR,  intersection(V, ofcolor(I, THREE)))
    O = fill(O, FOUR, seeds4)
    return O

def dsl2(I):
    # Draw plus only through non-background (mostcolor is background), recolor to 3
    bg = mostcolor(I)
    seeds4 = ofcolor(I, FOUR)
    H = merge(apply(hfrontier, seeds4))
    V = merge(apply(vfrontier, seeds4))
    L = combine(H, V)
    nb = difference(asindices(I), ofcolor(I, bg))
    draw = intersection(L, nb)
    O = fill(I, THREE, draw)
    O = fill(O, FOUR, seeds4)
    return O

def dsl3(I):
    # Only affect 3-regions: horizontal from 4 -> 5, vertical from 4 -> 6
    seeds4 = ofcolor(I, FOUR)
    H = merge(apply(hfrontier, seeds4))
    V = merge(apply(vfrontier, seeds4))
    threes = ofcolor(I, THREE)
    O = I
    O = fill(O, FIVE, intersection(H, threes))
    O = fill(O, SIX,  intersection(V, threes))
    O = fill(O, FOUR, seeds4)
    return O

def dsl4(I):
    # Restrict drawing to bounding rectangles of 2- and 3-regions
    seeds4 = ofcolor(I, FOUR)
    H = merge(apply(hfrontier, seeds4))
    V = merge(apply(vfrontier, seeds4))
    rect2 = backdrop(ofcolor(I, TWO))
    rect3 = backdrop(ofcolor(I, THREE))
    O = I
    # within 2-rectangle: mark both H and V as 3
    O = fill(O, THREE, intersection(H, rect2))
    O = fill(O, THREE, intersection(V, rect2))
    # within 3-rectangle: H->5, V->6
    O = fill(O, FIVE,  intersection(H, rect3))
    O = fill(O, SIX,   intersection(V, rect3))
    O = fill(O, FOUR, seeds4)
    return O

def dsl5(I):
    # Use bounding rectangles of 1/2/3-regions with distinct mappings; keep 4 as anchor
    seeds4 = ofcolor(I, FOUR)
    H = merge(apply(hfrontier, seeds4))
    V = merge(apply(vfrontier, seeds4))
    L = combine(H, V)
    rect1 = backdrop(ofcolor(I, ONE))
    rect2 = backdrop(ofcolor(I, TWO))
    rect3 = backdrop(ofcolor(I, THREE))
    O = I
    O = fill(O, TWO,   intersection(L, rect1))   # in 1-rect -> 2
    O = fill(O, THREE, intersection(L, rect2))   # in 2-rect -> 3
    O = fill(O, FIVE,  intersection(H, rect3))   # in 3-rect, H->5
    O = fill(O, SIX,   intersection(V, rect3))   # in 3-rect, V->6
    O = fill(O, FOUR, seeds4)
    return O
```