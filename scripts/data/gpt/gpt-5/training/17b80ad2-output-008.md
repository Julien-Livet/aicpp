```python
def dsl1(I):
    # Global: for each nonzero cell, paint downward rays and the column's top-to-topmost segment
    idx = asindices(I)
    nz = difference(idx, ofcolor(I, ZERO))
    toobj = rbind(toobject, I)
    getc = compose(color, compose(toobj, initset))
    vf = vfrontier
    topcol = compose(ulcorner, vf)
    colnz = compose(lbind(intersection, nz), vf)
    topnz = compose(ulcorner, colnz)
    topseg = fork(connect, topcol, topnz)
    topcolr = compose(getc, topnz)
    mk_top = fork(recolor, topcolr, topseg)
    dshoot = rbind(shoot, DOWN)
    mk_down = fork(recolor, getc, dshoot)
    topobjs = merge(apply(mk_top, nz))
    downobjs = merge(apply(mk_down, nz))
    objs = combine(topobjs, downobjs)
    O = underpaint(I, objs)
    return O

def dsl2(I):
    # Object extraction: per object, connect center to bottom; also paint column top to topmost nonzero
    seeds = fgpartition(I)
    idx = asindices(I)
    nz = difference(idx, ofcolor(I, ZERO))
    toobj = rbind(toobject, I)
    getc = compose(color, compose(toobj, initset))
    cf = center
    vf = compose(vfrontier, cf)
    topcol = compose(ulcorner, vf)
    botcol = compose(lrcorner, vf)
    colnz = compose(lbind(intersection, nz), vf)
    topnz = compose(ulcorner, colnz)
    col_top = compose(getc, topnz)
    seg_up = fork(connect, topcol, topnz)
    seg_dn = fork(connect, cf, botcol)
    obj_up = fork(recolor, col_top, seg_up)
    obj_dn = fork(recolor, color, seg_dn)
    upobjs = merge(apply(obj_up, seeds))
    dnobjs = merge(apply(obj_dn, seeds))
    objs = combine(upobjs, dnobjs)
    O = underpaint(I, objs)
    return O

def dsl3(I):
    # Color filtering: per color, union all downward rays; add global top-to-topmost segments
    seeds = fgpartition(I)
    idx = asindices(I)
    nz = difference(idx, ofcolor(I, ZERO))
    toobj = rbind(toobject, I)
    getc = compose(color, compose(toobj, initset))
    vf = vfrontier
    topcol = compose(ulcorner, vf)
    colnz = compose(lbind(intersection, nz), vf)
    topnz = compose(ulcorner, colnz)
    topseg = fork(connect, topcol, topnz)
    topcolr = compose(getc, topnz)
    mk_top = fork(recolor, topcolr, topseg)
    topobjs = merge(apply(mk_top, nz))
    samec = compose(lbind(colorfilter, seeds), color)
    colinds = compose(merge, lbind(apply, toindices), samec)
    rayspatch = compose(merge, lbind(apply, rbind(shoot, DOWN)), colinds)
    mk_raysobj = fork(recolor, color, rayspatch)
    raysobjs = merge(apply(mk_raysobj, seeds))
    objs = combine(topobjs, raysobjs)
    O = underpaint(I, objs)
    return O

def dsl4(I):
    # Geometric: use directions to bottom and to column top; shoot accordingly
    seeds = fgpartition(I)
    idx = asindices(I)
    nz = difference(idx, ofcolor(I, ZERO))
    toobj = rbind(toobject, I)
    getc = compose(color, compose(toobj, initset))
    cf = center
    vf = compose(vfrontier, cf)
    topcol = compose(ulcorner, vf)
    botcol = compose(lrcorner, vf)
    vecdn = fork(subtract, botcol, cf)
    dirdn = compose(sign, vecdn)
    raydn = fork(shoot, cf, dirdn)
    obj_dn = fork(recolor, color, raydn)
    colnz = compose(lbind(intersection, nz), vf)
    topnz = compose(ulcorner, colnz)
    vectop = fork(subtract, topcol, topnz)
    dirup = compose(sign, vectop)
    rayup = fork(shoot, topnz, dirup)
    col_top = compose(getc, topnz)
    obj_up = fork(recolor, col_top, rayup)
    upobjs = merge(apply(obj_up, seeds))
    dnobjs = merge(apply(obj_dn, seeds))
    objs = combine(upobjs, dnobjs)
    O = underpaint(I, objs)
    return O

def dsl5(I):
    # Relational: connect each object downward to bottom; connect column top to topmost nonzero
    seeds = fgpartition(I)
    idx = asindices(I)
    nz = difference(idx, ofcolor(I, ZERO))
    toobj = rbind(toobject, I)
    getc = compose(color, compose(toobj, initset))
    cf = center
    vf = compose(vfrontier, cf)
    topcol = compose(ulcorner, vf)
    botcol = compose(lrcorner, vf)
    colnz = compose(lbind(intersection, nz), vf)
    topnz = compose(ulcorner, colnz)
    seg_up = fork(connect, topcol, topnz)
    seg_dn = fork(connect, cf, botcol)
    col_top = compose(getc, topnz)
    obj_up = fork(recolor, col_top, seg_up)
    obj_dn = fork(recolor, color, seg_dn)
    upobjs = merge(apply(obj_up, seeds))
    dnobjs = merge(apply(obj_dn, seeds))
    objs = combine(upobjs, dnobjs)
    O = underpaint(I, objs)
    return O
```