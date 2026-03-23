```python
def dsl1(I):
    # Global hole-fill inside the 3-structure bounding box via subgrid partition
    A = ofcolor(I, THREE)
    S = subgrid(A, I)
    P = partition(S)
    Zobjs = colorfilter(P, ZERO)
    NonBorder = sfilter(Zobjs, compose(flip, rbind(bordering, S)))
    HolesS = toindices(merge(NonBorder))
    Off = ulcorner(A)
    H = shift(HolesS, Off)
    O = underfill(I, FOUR, H)
    return O

def dsl2(I):
    # Object-level: zero components not adjacent to the 3-bbox border are holes
    A = ofcolor(I, THREE)
    B = box(A)
    Zobjs = colorfilter(objects(I, T, F, F), ZERO)
    NotAdj = sfilter(Zobjs, compose(flip, lbind(adjacent, B)))
    H = intersection(merge(NotAdj), delta(A))
    O = underfill(I, FOUR, H)
    return O

def dsl3(I):
    # Color filtering with subgrid objects: zeros in subgrid not bordering its frame
    A = ofcolor(I, THREE)
    S = subgrid(A, I)
    ObjFun1 = rbind(objects, T)
    ObjFun2 = rbind(ObjFun1, F)
    ObjFun3 = rbind(ObjFun2, T)
    Zobjs = apply(rbind(colorfilter, ZERO), apply(ObjFun3, initset(S)))
    # Zobjs is a container of zero-object sets; merge then filter by non-bordering
    Zset = merge(Zobjs)
    NonBorder = sfilter(Zset, compose(flip, rbind(bordering, S)))
    HolesS = toindices(merge(NonBorder))
    H = shift(HolesS, ulcorner(A))
    O = underfill(I, FOUR, H)
    return O

def dsl4(I):
    # Geometric: use backdrops of horizontal/vertical 3-lines; intersect and gate by 3-bbox
    O3 = colorfilter(objects(I, T, F, T), THREE)
    Hs = sfilter(O3, hline)
    Vs = sfilter(O3, vline)
    HB = merge(apply(backdrop, Hs))
    VB = merge(apply(backdrop, Vs))
    A = ofcolor(I, THREE)
    Z = ofcolor(I, ZERO)
    H = intersection(Z, intersection(intersection(HB, VB), delta(A)))
    O = underfill(I, FOUR, H)
    return O

def dsl5(I):
    # Relational/structural: zeros inside any 3-object bbox but not near bbox border
    O3 = colorfilter(objects(I, T, F, T), THREE)
    BBs = merge(apply(backdrop, O3))
    Boxes = merge(apply(box, O3))
    NearBorder = merge(apply(dneighbors, Boxes))
    Z = ofcolor(I, ZERO)
    InBBoxes = intersection(Z, BBs)
    Deep = difference(InBBoxes, NearBorder)
    A = ofcolor(I, THREE)
    H = intersection(Deep, delta(A))
    O = underfill(I, FOUR, H)
    return O
```