```python
def dsl1(I):
    # Global: per column, fill from top to topmost nonzero and from bottommost nonzero to bottom
    idx = asindices(I)
    nz = difference(idx, ofcolor(I, ZERO))
    toobj = rbind(toobject, I)
    getc = compose(color, compose(toobj, initset))
    vcol = vfrontier
    topcol = compose(ulcorner, vcol)
    botcol = compose(lrcorner, vcol)
    colnz = compose(lbind(intersection, nz), vcol)
    topnz = compose(ulcorner, colnz)
    botnz = compose(lrcorner, colnz)
    seg_up = fork(connect, topcol, topnz)
    seg_dn = fork(connect, botnz, botcol)
    col_topc = compose(getc, topnz)
    col_botc = compose(getc, botnz)
    obj_up = fork(recolor, col_topc, seg_up)
    obj_dn = fork(recolor, col_botc, seg_dn)
    upobjs = merge(apply(obj_up, nz))
    dnobjs = merge(apply(obj_dn, nz))
    objs = combine(upobjs, dnobjs)
    O = underpaint(I, objs)
    return O

def dsl2(I):
    # Object extraction: for each nonzero cell, connect top of its column down to it (its color), and from it to bottom
    idx = asindices(I)
    nz = difference(idx, ofcolor(I, ZERO))
    toobj = rbind(toobject, I)
    getc = compose(color, compose(toobj, initset))
    vcol = vfrontier
    topcol = compose(ulcorner, vcol)
    botcol = compose(lrcorner, vcol)
    colnz = compose(lbind(intersection, nz), vcol)
    topnz = compose(ulcorner, colnz)
    seg_up = fork(connect, topcol, identity)
    obj_up = fork(recolor, getc, seg_up)
    seg_dn = fork(connect, identity, botcol)
    obj_dn = fork(recolor, getc, seg_dn)
    upobjs = merge(apply(obj_up, nz))
    dnobjs = merge(apply(obj_dn, nz))
    objs = combine(upobjs, dnobjs)
    O = underpaint(I, objs)
    return O

def dsl3(I):
    # Color filtering: per color, paint all columns containing that color (both up and down rays union)
    pals = remove(ZERO, palette(I))
    inds_of = lbind(ofcolor, I)
    upshot = rbind(shoot, UP)
    dnshot = rbind(shoot, DOWN)
    colrays = compose(merge, lbind(apply, vfrontier))
    # For each color: union columns where it occurs, recolored by that color
    mk_cols = compose(merge, lbind(apply, vfrontier), inds_of)
    mk_obj = fork(recolor, identity, mk_cols)
    colorobjs = merge(apply(mk_obj, pals))
    O = underpaint(I, colorobjs)
    return O

def dsl4(I):
    # Geometric: per column, fill entire column with the color of its bottommost nonzero
    idx = asindices(I)
    nz = difference(idx, ofcolor(I, ZERO))
    toobj = rbind(toobject, I)
    getc = compose(color, compose(toobj, initset))
    vcol = vfrontier
    colnz = compose(lbind(intersection, nz), vcol)
    botnz = compose(lrcorner, colnz)
    botc = compose(getc, botnz)
    colpatch = vcol
    obj_col = fork(recolor, botc, colpatch)
    colobjs = merge(apply(obj_col, nz))
    O = underpaint(I, colobjs)
    return O

def dsl5(I):
    # Relational/propagation: initialize top segments, then propagate colors downward via repeated underpaint of shifted objects
    idx = asindices(I)
    nz = difference(idx, ofcolor(I, ZERO))
    toobj = rbind(toobject, I)
    getc = compose(color, compose(toobj, initset))
    vcol = vfrontier
    topcol = compose(ulcorner, vcol)
    colnz = compose(lbind(intersection, nz), vcol)
    topnz = compose(ulcorner, colnz)
    seg_up = fork(connect, topcol, topnz)
    col_topc = compose(getc, topnz)
    obj_up = fork(recolor, col_topc, seg_up)
    topobjs = merge(apply(obj_up, nz))
    G0 = underpaint(I, topobjs)
    # Define one downward-propagation step on a grid
    idxf = asindices
    zerof = rbind(ofcolor, ZERO)
    nzindsf = fork(difference, idxf, zerof)
    nzobjf = fork(toobject, nzindsf, identity)
    shiftd = rbind(shift, DOWN)
    objdownf = compose(shiftd, nzobjf)
    step = fork(underpaint, identity, objdownf)
    relax = power(step, 30)
    O = relax(G0)
    return O
```