```python
def dsl1(I):
    # Extend the rectangle to include the 8 by taking the backdrop of union with the 8-cell
    base = replace(I, EIGHT, ZERO)
    # get the two-color rectangle area via border-color object
    pal = palette(base)
    pal1 = remove(ZERO, pal)
    bcol = argmax(pal1, lbind(colorcount, base))
    objs = objects(base, T, F, T)
    bset = colorfilter(objs, bcol)
    bobj = argmax(bset, size)
    band = backdrop(toindices(bobj))
    # colors by sampling border and interior
    bord0 = box(band)
    inter0 = difference(band, bord0)
    bsample = first(bord0)
    isample = first(inter0)
    bclr = index(base, bsample)
    iclr = index(base, isample)
    # enlarge by including the 8's cell in the seed, then take its bounding box
    epatch = ofcolor(I, EIGHT)
    seed = combine(band, epatch)
    rect = backdrop(seed)
    bord = box(rect)
    inter = difference(rect, bord)
    x1 = fill(base, bclr, bord)
    O = fill(x1, iclr, inter)
    return O

def dsl2(I):
    # Extend rectangle along the axis aligned with the 8 using explicit line at 8's row/col
    base = replace(I, EIGHT, ZERO)
    pal = palette(base)
    pal1 = remove(ZERO, pal)
    bcol = argmax(pal1, lbind(colorcount, base))
    objs = objects(base, T, F, T)
    bset = colorfilter(objs, bcol)
    bobj = argmax(bset, size)
    band = backdrop(toindices(bobj))
    # colors by sampling
    bord0 = box(band)
    inter0 = difference(band, bord0)
    bclr = index(base, first(bord0))
    iclr = index(base, first(inter0))
    # orientation via row/col alignment
    epatch = ofcolor(I, EIGHT)
    e = first(epatch)
    hr = intersection(hfrontier(e), band)
    ish = greater(size(hr), ZERO)  # True if same row -> horizontal extension
    top = uppermost(band)
    bot = lowermost(band)
    lef = leftmost(band)
    rig = rightmost(band)
    erow = uppermost(hfrontier(e))
    ecol = leftmost(vfrontier(e))
    vline = connect(astuple(top, ecol), astuple(bot, ecol))
    hline = connect(astuple(erow, lef), astuple(erow, rig))
    ext = branch(ish, vline, hline)
    rect = backdrop(combine(band, ext))
    bord = box(rect)
    inter = difference(rect, bord)
    x1 = fill(base, bclr, bord)
    O = fill(x1, iclr, inter)
    return O

def dsl3(I):
    # Use fgpartition to get the two-color object; union-with-8 backdrop enlargement
    base = replace(I, EIGHT, ZERO)
    comp = fgpartition(base)
    obj = argmax(comp, size)
    band = backdrop(toindices(obj))
    # colors by sampling
    bord0 = box(band)
    inter0 = difference(band, bord0)
    bclr = index(base, first(bord0))
    iclr = index(base, first(inter0))
    # enlarge by including the 8's cell
    epatch = ofcolor(I, EIGHT)
    rect = backdrop(combine(band, epatch))
    bord = box(rect)
    inter = difference(rect, bord)
    x1 = fill(base, bclr, bord)
    O = fill(x1, iclr, inter)
    return O

def dsl4(I):
    # Compute new rectangle corners explicitly using 8's row/col and take rectangle backdrop
    base = replace(I, EIGHT, ZERO)
    pal = palette(base)
    pal1 = remove(ZERO, pal)
    bcol = argmax(pal1, lbind(colorcount, base))
    objs = objects(base, T, F, T)
    bset = colorfilter(objs, bcol)
    bobj = argmax(bset, size)
    band = backdrop(toindices(bobj))
    # colors by sampling
    bord0 = box(band)
    inter0 = difference(band, bord0)
    bclr = index(base, first(bord0))
    iclr = index(base, first(inter0))
    # corners
    top = uppermost(band)
    bot = lowermost(band)
    lef = leftmost(band)
    rig = rightmost(band)
    e = first(ofcolor(I, EIGHT))
    erow = uppermost(hfrontier(e))
    ecol = leftmost(vfrontier(e))
    # decide axis by row alignment
    hr = intersection(hfrontier(e), band)
    ish = greater(size(hr), ZERO)
    new_left = branch(ish, branch(greater(lef, ecol), ecol, lef), lef)
    new_right = branch(ish, branch(greater(rig, ecol), rig, ecol), rig)
    new_top = branch(ish, top, branch(greater(top, erow), erow, top))
    new_bot = branch(ish, bot, branch(greater(bot, erow), bot, erow))
    ul = astuple(new_top, new_left)
    lr = astuple(new_bot, new_right)
    rect = backdrop(connect(ul, lr))
    bord = box(rect)
    inter = difference(rect, bord)
    x1 = fill(base, bclr, bord)
    O = fill(x1, iclr, inter)
    return O

def dsl5(I):
    # Use gravitate for axis decision; build corners accordingly
    base = replace(I, EIGHT, ZERO)
    pal = palette(base)
    pal1 = remove(ZERO, pal)
    bcol = argmax(pal1, lbind(colorcount, base))
    objs = objects(base, T, F, T)
    bset = colorfilter(objs, bcol)
    bobj = argmax(bset, size)
    band = backdrop(toindices(bobj))
    # colors by sampling
    bord0 = box(band)
    inter0 = difference(band, bord0)
    bclr = index(base, first(bord0))
    iclr = index(base, first(inter0))
    # axis via gravitate
    epatch = ofcolor(I, EIGHT)
    e = first(epatch)
    dirv = gravitate(toindices(bobj), epatch)
    ish = either(equality(dirv, RIGHT), equality(dirv, LEFT))
    top = uppermost(band)
    bot = lowermost(band)
    lef = leftmost(band)
    rig = rightmost(band)
    erow = uppermost(hfrontier(e))
    ecol = leftmost(vfrontier(e))
    new_left = branch(ish, branch(greater(lef, ecol), ecol, lef), lef)
    new_right = branch(ish, branch(greater(rig, ecol), rig, ecol), rig)
    new_top = branch(ish, top, branch(greater(top, erow), erow, top))
    new_bot = branch(ish, bot, branch(greater(bot, erow), bot, erow))
    rect = backdrop(connect(astuple(new_top, new_left), astuple(new_bot, new_right)))
    bord = box(rect)
    inter = difference(rect, bord)
    x1 = fill(base, bclr, bord)
    O = fill(x1, iclr, inter)
    return O
```