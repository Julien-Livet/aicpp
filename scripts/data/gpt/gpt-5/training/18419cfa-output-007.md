```python
def dsl1(I):
    # Object-wise horizontal mirroring of 2s inside each 8-bbox interior
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    Gf = rbind(subgrid, I)
    Vm = compose(vmirror, Gf)
    Ar = compose(rbind(ofcolor, TWO), Vm)
    Sr = fork(shift, Ar, ulcorner)
    Pr = merge(mapply(Sr, EO))
    IN = merge(mapply(inbox, EO))
    BO = merge(mapply(box, EO))
    INT = difference(IN, BO)
    P = intersection(INT, Pr)
    O = underfill(I, TWO, P)
    return O

def dsl2(I):
    # Geometric reasoning: vmirror via rot180∘hmirror inside each 8-bbox
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    Gf = rbind(subgrid, I)
    Rm = compose(rot180, hmirror)
    Ar = chain(rbind(ofcolor, TWO), Rm, Gf)
    Sr = fork(shift, Ar, ulcorner)
    Pr = merge(mapply(Sr, EO))
    IN = merge(mapply(inbox, EO))
    BO = merge(mapply(box, EO))
    INT = difference(IN, BO)
    P = intersection(INT, Pr)
    O = underfill(I, TWO, P)
    return O

def dsl3(I):
    # Color filtering + reconstruction on per-bbox canvas, then vmirror and project
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    Gf = rbind(subgrid, I)
    P2 = compose(rbind(ofcolor, TWO), Gf)
    Obj = compose(rbind(recolor, TWO), P2)
    Df = compose(shape, Gf)
    Cf = compose(lbind(canvas, ZERO), Df)
    Ug = fork(paint, Cf, Obj)
    Vm = compose(vmirror, Ug)
    Ar = compose(rbind(ofcolor, TWO), Vm)
    Sr = fork(shift, Ar, ulcorner)
    Pr = merge(mapply(Sr, EO))
    IN = merge(mapply(inbox, EO))
    BO = merge(mapply(box, EO))
    INT = difference(IN, BO)
    P = intersection(INT, Pr)
    O = underfill(I, TWO, P)
    return O

def dsl4(I):
    # Mirror using interiors as anchors: subgrid of interior, vmirror, and reproject
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    Ifn = fork(difference, inbox, box)
    Gg = compose(rbind(subgrid, I), Ifn)
    Vm = compose(vmirror, Gg)
    Ar = compose(rbind(ofcolor, TWO), Vm)
    Ul = compose(ulcorner, Ifn)
    Sr = fork(shift, Ar, Ul)
    Pr = merge(mapply(Sr, EO))
    IN = merge(mapply(inbox, EO))
    BO = merge(mapply(box, EO))
    INT = difference(IN, BO)
    P = intersection(INT, Pr)
    O = underfill(I, TWO, P)
    return O

def dsl5(I):
    # Axis construction via rotated diagonal mirror: rot270∘cmirror∘rot90 ≈ vmirror
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    Gf = rbind(subgrid, I)
    Vm = chain(rot270, cmirror, rot90)
    Ar = chain(rbind(ofcolor, TWO), Vm, Gf)
    Sr = fork(shift, Ar, ulcorner)
    Pr = merge(mapply(Sr, EO))
    IN = merge(mapply(inbox, EO))
    BO = merge(mapply(box, EO))
    INT = difference(IN, BO)
    P = intersection(INT, Pr)
    O = underfill(I, TWO, P)
    return O
```