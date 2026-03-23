```python
def dsl1(I):
    # Object extraction: mirror 2s left-right inside each 8-enclosed interior and reproject
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    Ifn = fork(difference, inbox, box)
    Gint = compose(rbind(subgrid, I), Ifn)
    Vm = compose(vmirror, Gint)
    Tw = compose(rbind(ofcolor, TWO), Vm)
    Ul = compose(ulcorner, Ifn)
    Sr = fork(shift, Tw, Ul)
    P = merge(mapply(Sr, EO))
    O = underpaint(I, recolor(TWO, P))
    return O

def dsl2(I):
    # Global-on-bbox: clear 8s in each bbox, vmirror, take 2s, project back
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    Sg = rbind(subgrid, I)
    Rz = rbind(replace, ZERO)
    Re8 = rbind(Rz, EIGHT)
    Cb = compose(Re8, Sg)
    Vm = compose(vmirror, Cb)
    Tw = compose(rbind(ofcolor, TWO), Vm)
    Sr = fork(shift, Tw, ulcorner)
    P = merge(mapply(Sr, EO))
    O = underpaint(I, recolor(TWO, P))
    return O

def dsl3(I):
    # Geometric: add both vertical and horizontal mirrors of 2s inside interiors
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    Ifn = fork(difference, inbox, box)
    Gint = compose(rbind(subgrid, I), Ifn)
    Mv = compose(vmirror, Gint)
    Mh = compose(hmirror, Gint)
    Tv = compose(rbind(ofcolor, TWO), Mv)
    Th = compose(rbind(ofcolor, TWO), Mh)
    Un = fork(combine, Tv, Th)
    Ul = compose(ulcorner, Ifn)
    Sr = fork(shift, Un, Ul)
    P = merge(mapply(Sr, EO))
    O = underpaint(I, recolor(TWO, P))
    return O

def dsl4(I):
    # Geometric via rotations: vmirror implemented as rot270∘hmirror∘rot90 inside interiors
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    Ifn = fork(difference, inbox, box)
    Gint = compose(rbind(subgrid, I), Ifn)
    Rm = chain(rot270, hmirror, rot90)
    Vm = compose(Rm, Gint)
    Tw = compose(rbind(ofcolor, TWO), Vm)
    Ul = compose(ulcorner, Ifn)
    Sr = fork(shift, Tw, Ul)
    P = merge(mapply(Sr, EO))
    O = underpaint(I, recolor(TWO, P))
    return O

def dsl5(I):
    # Relational: add only the new 2s (mirrored minus original) inside each interior
    EO = colorfilter(objects(I, T, F, T), EIGHT)
    Ifn = fork(difference, inbox, box)
    Gint = compose(rbind(subgrid, I), Ifn)
    T0 = compose(rbind(ofcolor, TWO), Gint)
    Tm = compose(rbind(ofcolor, TWO), compose(vmirror, Gint))
    New = fork(difference, Tm, T0)
    Ul = compose(ulcorner, Ifn)
    Sr = fork(shift, New, Ul)
    P = merge(mapply(Sr, EO))
    O = underpaint(I, recolor(TWO, P))
    return O
```