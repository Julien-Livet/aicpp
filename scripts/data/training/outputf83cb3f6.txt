```python
def dsl1(I):
    P = palette(I)
    P1 = remove(ZERO, P)
    P2 = remove(EIGHT, P1)
    C = first(P2)

    E = ofcolor(I, EIGHT)
    O0 = canvas(ZERO, shape(I))
    O0 = paint(O0, toobject(E, I))

    e0 = first(E)
    row_up = hfrontier(add(e0, UP))
    row_dn = hfrontier(add(e0, DOWN))
    col_lt = vfrontier(add(e0, LEFT))
    col_rt = vfrontier(add(e0, RIGHT))
    col8 = mapply(vfrontier, E)

    A = ofcolor(I, C)

    upRays = mapply(rbind(shoot, UP), E)
    dnRays = mapply(rbind(shoot, DOWN), E)
    ltRays = mapply(rbind(shoot, LEFT), E)
    rtRays = mapply(rbind(shoot, RIGHT), E)

    upHits = intersection(upRays, A)
    dnHits = intersection(dnRays, A)
    ltHits = intersection(ltRays, A)
    rtHits = intersection(rtRays, A)

    col_up = mapply(vfrontier, upHits)
    col_dn = mapply(vfrontier, dnHits)
    rows_lt = mapply(hfrontier, ltHits)
    rows_rt = mapply(hfrontier, rtHits)

    tgt_up = intersection(row_up, intersection(col_up, col8))
    tgt_dn = intersection(row_dn, intersection(col_dn, col8))
    tgt_lt = intersection(rows_lt, col_lt)
    tgt_rt = intersection(rows_rt, col_rt)

    Oh = paint(paint(O0, recolor(C, tgt_up)), recolor(C, tgt_dn))
    Ov = paint(paint(O0, recolor(C, tgt_lt)), recolor(C, tgt_rt))

    O = branch(equality(height(E), ONE), Oh, Ov)
    return O

def dsl2(I):
    P = palette(I)
    P1 = remove(ZERO, P)
    P2 = remove(EIGHT, P1)
    C = first(P2)

    E = ofcolor(I, EIGHT)
    O = canvas(ZERO, shape(I))
    O = paint(O, toobject(E, I))

    e0 = first(E)
    row_up = hfrontier(add(e0, UP))
    row_dn = hfrontier(add(e0, DOWN))
    col8 = mapply(vfrontier, E)

    A = ofcolor(I, C)

    upRays = mapply(rbind(shoot, UP), E)
    dnRays = mapply(rbind(shoot, DOWN), E)

    upHits = intersection(upRays, A)
    dnHits = intersection(dnRays, A)

    col_up = mapply(vfrontier, upHits)
    col_dn = mapply(vfrontier, dnHits)

    tgt_up = intersection(row_up, intersection(col_up, col8))
    tgt_dn = intersection(row_dn, intersection(col_dn, col8))

    O = paint(paint(O, recolor(C, tgt_up)), recolor(C, tgt_dn))
    return O

def dsl3(I):
    P = palette(I)
    P1 = remove(ZERO, P)
    P2 = remove(EIGHT, P1)
    C = first(P2)

    E = ofcolor(I, EIGHT)
    O = canvas(ZERO, shape(I))
    O = paint(O, toobject(E, I))

    e0 = first(E)
    col_lt = vfrontier(add(e0, LEFT))
    col_rt = vfrontier(add(e0, RIGHT))

    A = ofcolor(I, C)

    ltRays = mapply(rbind(shoot, LEFT), E)
    rtRays = mapply(rbind(shoot, RIGHT), E)

    ltHits = intersection(ltRays, A)
    rtHits = intersection(rtRays, A)

    rows_lt = mapply(hfrontier, ltHits)
    rows_rt = mapply(hfrontier, rtHits)

    tgt_lt = intersection(rows_lt, col_lt)
    tgt_rt = intersection(rows_rt, col_rt)

    O = paint(paint(O, recolor(C, tgt_lt)), recolor(C, tgt_rt))
    return O

def dsl4(I):
    E = ofcolor(I, EIGHT)
    O = canvas(ZERO, shape(I))
    O = paint(O, toobject(E, I))

    P = palette(I)
    P1 = remove(ZERO, P)
    P2 = remove(EIGHT, P1)
    C = first(P2)

    e0 = first(E)
    col8 = mapply(vfrontier, E)
    row_up = hfrontier(add(e0, UP))
    row_dn = hfrontier(add(e0, DOWN))

    A = ofcolor(I, C)

    cols_with_A = mapply(vfrontier, A)
    tgt_up = intersection(row_up, intersection(cols_with_A, col8))
    tgt_dn = intersection(row_dn, intersection(cols_with_A, col8))

    O = paint(paint(O, recolor(C, tgt_up)), recolor(C, tgt_dn))
    return O

def dsl5(I):
    E = ofcolor(I, EIGHT)
    O = canvas(ZERO, shape(I))
    O = paint(O, toobject(E, I))

    P = palette(I)
    P1 = remove(ZERO, P)
    P2 = remove(EIGHT, P1)
    C = first(P2)

    e0 = first(E)
    col_lt = vfrontier(add(e0, LEFT))
    col_rt = vfrontier(add(e0, RIGHT))

    A = ofcolor(I, C)

    rows_with_A = mapply(hfrontier, A)
    tgt_lt = intersection(rows_with_A, col_lt)
    tgt_rt = intersection(rows_with_A, col_rt)

    O = paint(paint(O, recolor(C, tgt_lt)), recolor(C, tgt_rt))
    return O
```