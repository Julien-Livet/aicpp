```python
def dsl1(I):
    # Object-extraction + local 180° rotation of each 8-bbox; union with interior and underfill 2s
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    Gf = rbind(subgrid, I)
    Ar = chain(rbind(ofcolor, TWO), rot180, Gf)
    Sr = fork(shift, Ar, ulcorner)
    Pr = merge(mapply(Sr, EO))
    IN = merge(mapply(inbox, EO))
    BO = merge(mapply(box, EO))
    INT = difference(IN, BO)
    P = intersection(INT, Pr)
    O = underfill(I, TWO, P)
    return O

def dsl2(I):
    # Geometric reasoning via axis mirrors: hmirror∘vmirror on each 8-bbox; project 2s back and underfill
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    Rm = compose(hmirror, vmirror)
    Gf = rbind(subgrid, I)
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
    # Relational two-step symmetry completion: horizontal mirror union, then vertical mirror; underfill 2s
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    Gf = rbind(subgrid, I)
    Hf = compose(hmirror, Gf)
    P1 = compose(rbind(ofcolor, TWO), Hf)
    O1 = compose(rbind(recolor, TWO), P1)
    U1 = fork(underpaint, Gf, O1)
    Vg = compose(vmirror, U1)
    P2 = compose(rbind(ofcolor, TWO), Vg)
    Sr = fork(shift, P2, ulcorner)
    Pr = merge(mapply(Sr, EO))
    IN = merge(mapply(inbox, EO))
    BO = merge(mapply(box, EO))
    INT = difference(IN, BO)
    P = intersection(INT, Pr)
    O = underfill(I, TWO, P)
    return O

def dsl4(I):
    # Interior-only rotation: build per-enclosure interior subgrid, rot180, and underfill 2s back into interiors
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    Ifn = fork(difference, inbox, box)
    Gf = chain(rbind(subgrid, I), Ifn)
    Ar = chain(rbind(ofcolor, TWO), rot180, Gf)
    Ul = chain(ulcorner, Ifn)
    Sr = fork(shift, Ar, Ul)
    Pr = merge(mapply(Sr, EO))
    IN = merge(mapply(inbox, EO))
    BO = merge(mapply(box, EO))
    INT = difference(IN, BO)
    P = intersection(INT, Pr)
    O = underfill(I, TWO, P)
    return O

def dsl5(I):
    # Color filtering + reconstruction: rotate each 8-bbox grid, union 2s via underpaint, then project back
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    Gf = rbind(subgrid, I)
    Rg = compose(rot180, Gf)
    P2 = compose(rbind(ofcolor, TWO), Rg)
    Obj = compose(rbind(recolor, TWO), P2)
    U = fork(underpaint, Gf, Obj)
    Pf = compose(rbind(ofcolor, TWO), U)
    Sr = fork(shift, Pf, ulcorner)
    Pr = merge(mapply(Sr, EO))
    IN = merge(mapply(inbox, EO))
    BO = merge(mapply(box, EO))
    INT = difference(IN, BO)
    P = intersection(INT, Pr)
    O = underfill(I, TWO, P)
    return O
```