```python
def dsl1(I):
    # Color filtering + reconstruction on per-bbox canvas, then vmirror and project (fixed recolor)
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    Gf = rbind(subgrid, I)
    P2 = compose(rbind(ofcolor, TWO), Gf)
    Obj = compose(lbind(recolor, TWO), P2)
    Df = compose(shape, Gf)
    Cf = compose(lbind(canvas, ZERO), Df)
    Ug = fork(paint, Cf, Obj)
    Vm = compose(vmirror, Ug)
    Ar = compose(rbind(ofcolor, TWO), Vm)
    Sr = fork(shift, Ar, ulcorner)
    Pr = merge(mapply(Sr, EO))
    O = underfill(I, TWO, Pr)
    return O

def dsl2(I):
    # Relational: mirror 2s via vmirror of (interior ∪ twos) and subtract interior
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    Ifn = fork(difference, inbox, box)
    Tw = compose(rbind(intersection, ofcolor(I, TWO)), Ifn)
    Un = fork(combine, Ifn, Tw)
    Vm = compose(vmirror, Un)
    Mir2 = fork(difference, Vm, Ifn)
    P = merge(mapply(Mir2, EO))
    R2 = recolor(TWO, P)
    O = underpaint(I, R2)
    return O

def dsl3(I):
    # Geometric: same relational trick but vmirror via rot270∘cmirror∘rot90
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    Ifn = fork(difference, inbox, box)
    Tw = compose(rbind(intersection, ofcolor(I, TWO)), Ifn)
    Un = fork(combine, Ifn, Tw)
    Rm = chain(rot270, cmirror, rot90)
    M2 = compose(Rm, Un)
    Mir2 = fork(difference, M2, Ifn)
    P = merge(mapply(Mir2, EO))
    R2 = recolor(TWO, P)
    O = underpaint(I, R2)
    return O

def dsl4(I):
    # Object extraction: vmirror inside each interior subgrid and reproject
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    Ifn = fork(difference, inbox, box)
    Gg = compose(rbind(subgrid, I), Ifn)
    Vm = compose(vmirror, Gg)
    Ar = compose(rbind(ofcolor, TWO), Vm)
    Ul = compose(ulcorner, Ifn)
    Sr = fork(shift, Ar, Ul)
    Pr = merge(mapply(Sr, EO))
    O = underfill(I, TWO, Pr)
    return O

def dsl5(I):
    # Global symmetry on bbox: replace 8→0, rot270∘hmirror∘rot90, then project 2s
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    Gf = rbind(subgrid, I)
    Rz = rbind(replace, ZERO)              # (grid, replacee) -> replace(grid, replacee, 0)
    Re8 = rbind(Rz, EIGHT)                 # grid -> replace(grid, 8, 0)
    Cg = compose(Re8, Gf)                  # clear 8-border inside bbox
    Rm = chain(rot270, hmirror, rot90)     # vertical mirror via rotations + hmirror
    Vm = compose(Rm, Cg)
    Ar = compose(rbind(ofcolor, TWO), Vm)
    Sr = fork(shift, Ar, ulcorner)
    Pr = merge(mapply(Sr, EO))
    O = underfill(I, TWO, Pr)
    return O
```