training 6150a2bd test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # Global rotation by 180 degrees
    O = rot180(I)
    return O
```
training c8f0f002 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # Global direct recoloring
    O = replace(I, 7, 5)
    return O
```
training 68b16354 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # Global transformation: flip vertically (mirror along horizontal axis)
    return hmirror(I)
```
training 74dd1130 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl3(I):
    # Geometric: rotate 90° clockwise then mirror vertically
    O = vmirror(rot90(I))
    return O
```
training ed36ccf7 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl2(I):
    # geometric: 90° clockwise then 180° = 90° counter‑clockwise
    O = rot180(rot90(I))
    return O
```
training 67a3c6ac test 0.0 0.0 0.0 0.0 0.0
```python
def dsl4(I):
    # 4️⃣ Geometric reasoning – mirror the grid along the vertical axis.
    O = vmirror(I)
    return O
```
training a416b8f3 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # 1️⃣ Global transformation – simply paste the grid next to itself
    O = hconcat(I, I)
    return O
```
training 9dfd6313 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl3(I):
    # Diagonal mirror (built‑in diagonal symmetry) gives the transpose directly
    O = dmirror(I)
    return O
```
training b1948b0a test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # Global transformation: replace every 6 with 2 in the whole grid
    O = replace(I, SIX, TWO)
    return O
```
training 8be77c9e test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # Global transformation: stack the grid with its vertical mirror.
    O = vconcat(I, hmirror(I))
    return O
```
training c59eb873 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # Global scaling using the primitive that directly upsamples both dimensions.
    O = upscale(I, 2)
    return O
```
training 6fa7a44f test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # 1️⃣ Global transformation: stack the input with its vertical mirror.
    O = vconcat(I, hmirror(I))
    return O
```
training d511f180 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl4(I):
    # Direct colour‑swap primitive
    O = switch(I, 5, 8)      # swaps every 5 with 8 and every 8 with 5
    return O
```
training 4c4377d9 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # Global transformation: vertical mirror of the whole grid and stack on top
    O = vconcat(hmirror(I), I)
    return O
```
training 0d3d703e test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # global swapping using the built‑in switch primitive
    O = switch(switch(switch(switch(I, 1, 5), 2, 6), 3, 4), 8, 9)
    return O
```
training 5bd6f4ac test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # Global extraction: crop the right‑most 3 columns of the top 3 rows
    O = crop(I, (0, subtract(width(I), 3)), (3, 3))
    return O
```
training 5582e5ca test 0.0 0.0 0.0 0.0 0.0
```python
def dsl2(I):
    # Color‑filtering – use the primitive that directly returns the dominant color of a grid
    dom = mostcolor(I)
    O = canvas(dom, shape(I))
    return O
```
training 9172f3a0 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # --------- 1. Global uniform scaling ---------------------------------
    # upscale the whole input by a factor equal to its height (the grid is square)
    O = upscale(I, height(I))
    return O
```
training 6d0aefbc test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # geometric: vertical mirror obtained by 90° rotation, horizontal mirror,
    # then inverse rotation; concatenate original with this flipped copy
    O = hconcat(I, rot270(hmirror(rot90(I))))
    return O
```
training 1b2d62fb test 0.0 0.0 0.0 0.0 0.0
```python
def dsl2(I):
    # direct colour‑filter on zeros (colour‑filtering)
    L0 = ofcolor(lefthalf(I), ZERO)
    R0 = ofcolor(righthalf(I), ZERO)
    O = canvas(ZERO, shape(lefthalf(I)))
    O = fill(O, EIGHT, intersection(L0, R0))
    return O
```
training 3c9b0459 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl3(I):
    # 180° rotation using a diagonal mirror (dmirror) and a counter‑diagonal mirror (cmirror),
    # then restore the interior cells.
    mir = dmirror(cmirror(I))
    interior = delta(asobject(I))
    O = paint(mir, interior)
    return O
```
training 2dee498d test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # Global split: the whole picture consists of three identical horizontal parts.
    # Split it into three equal vertical slices and keep the left‑most one.
    parts = hsplit(I, 3)          # Tuple of three sub‑grids (left, middle, right)
    O = first(parts)              # select the left slice
    return O
```
training 32597951 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl2(I):
    # like dsl1 but first remove the 8‑pixels themselves, i.e. use the interior
    patch8      = ofcolor(I, 8)
    bbox8       = backdrop(patch8)
    interior8   = difference(bbox8, patch8)          # box without the 8‑border
    target      = intersection(ofcolor(I, 1), interior8)
    O = fill(I, 3, target)
    return O
```
training 1a2e2828 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # OBJECT‑EXTRACTION : pick object whose height equals grid height
    #                     or whose width  equals grid width
    objs = objects(I, True, False, False)
    h   = shape(I)[0]
    w   = shape(I)[1]
    full_obj = lambda o: either(
        both(equality(height(o), h),     True),
        both(equality(width(o),  w),     True))
    target = first(sfilter(objs, full_obj))
    return canvas(color(target), (1, 1))
```
training 1cf80156 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # remove any fully‑zero rows/columns that surround the picture
    O = trim(I)                 # strip outer empty rows/cols
    O = compress(O)              # collapse any remaining empty fringe
    return O


# ----------------------------------------------------------------------
# 2️⃣  OBJECT‑LEVEL EXTRACTION – crop to the bounding box of the
#      most frequent non‑zero colour
# ----------------------------------------------------------------------
```
training 25ff71a9 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # GLOBAL TRANSFORMATION: cut off the last row and put it on top
    # split the grid into (height‑1) rows and the final row, then concatenate in swapped order
    H = height(I)                     # total number of rows
    W = width(I)                      # total number of columns
    last_row   = crop(I, (subtract(H, ONE), ZERO), (ONE, W))
    rest_rows  = crop(I, (ZERO, ZERO), (subtract(H, ONE), W))
    O = vconcat(last_row, rest_rows)  # new grid with rows shifted down by one
    return O
```
training 05f2a901 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl5(I):
    # ---------- GRAVITY + UNDERPAINT ----------
    # Move the 2‑object until its outline touches the 8‑object, then place it
    # under the cleared background.
    obj2 = ofcolor(I, TWO)
    obj8 = ofcolor(I, EIGHT)

    outline2 = box(obj2)
    outline8 = box(obj8)

    # minimal orthogonal offset that makes the two outlines adjacent
    move = gravitate(outline2, outline8)

    moved   = recolor(TWO, shift(obj2, move))
    cleared = cover(I, obj2)
    O = underpaint(cleared, moved)
    return O
```
training 007bbfb7 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # 1️⃣  Global placement: copy the whole input pattern to every non‑zero cell.
    O = canvas(0, (height(I) * 3, width(I) * 3))
    P = asobject(I)                                           # whole pattern as an object
    nz = difference(asindices(I), ofcolor(I, 0))              # positions of non‑zero cells
    O = paint(O,
              merge(apply(lambda loc: shift(P, (loc[0] * 3, loc[1] * 3)),
                        nz)))                               # lay the pattern at each anchor
    return O
```
training 0ca9ddb6 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl5(I):
    # ---------- RELATIONAL / STRUCTURAL ----------
    # build neighbourhoods by applying adjacency primitives to every cell of a colour
    ones = ofcolor(I, ONE)
    twos = ofcolor(I, TWO)

    # orthogonal neighbours of each 1 → 7
    plus_patch = merge(apply(lambda loc: dneighbors(loc), ones))
    plus7      = recolor(SEVEN, plus_patch)

    # diagonal neighbours of each 2 → 4
    diag_patch = merge(apply(lambda loc: ineighbors(loc), twos))
    diag4      = recolor(FOUR, diag_patch)

    O = paint(I, combine(plus7, diag4))
    return O
```
training 0c786b71 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # ---------- Global symmetric tiling ----------
    # 1. Rotate the whole picture by 180°.
    # 2. Build the top half by concatenating this block with its
    #    left‑right mirror.
    # 3. Obtain the bottom half by mirroring the top half vertically.
    # 4. Stack the halves.
    base   = rot180(I)                                 # 180° rotation
    top    = hconcat(base, vmirror(base))              # left‑right reflection
    bottom = hmirror(top)                               # up‑down reflection
    O = vconcat(top, bottom)
    return O
```
training 0692e18c test 0.0 0.0 0.0 0.0 0.0
```python
def dsl5(I):
    # RELATIONAL / STRUCTURAL – use arithmetic primitive `multiply`
    fg = argmax(difference(palette(I), initset(0)),
                lbind(colorcount, I))
    N  = height(I)
    # inverted pattern (correct swap)
    tmp = replace(I, 0, NEG_ONE)
    tmp = replace(tmp, fg, 0)
    inv = replace(tmp, NEG_ONE, fg)
    Pobj = asobject(inv)
    anchors = ofcolor(I, fg)
    # shift using multiplication instead of direct scaling
    shifted = apply(lambda p: shift(Pobj,
                                   (multiply(p[0], N), multiply(p[1], N))),
                   anchors)
    O = paint(canvas(0, (N * N, N * N)), merge(shifted))
    return O
```
training 0c9aba6e test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # 1️⃣  Global: split horizontally at the 7‑row, keep the zero‑mask of each half
    #      and intersect the masks.
    sep   = ofcolor(I, 7)                                 # cells of the separator
    r     = lowermost(sep)                               # row index of the separator
    w     = add(subtract(rightmost(sep), leftmost(sep)), ONE)   # width of a half
    top   = crop(I, ORIGIN, astuple(r, w))                # upper half
    bot   = crop(I, astuple(add(r, ONE), ZERO),
                 astuple(subtract(height(I), add(r, ONE)), w))   # lower half
    both  = intersection(ofcolor(top, 0), ofcolor(bot, 0))# common zero‑cells
    O     = canvas(0, astuple(r, w))
    O     = fill(O, 8, both)
    return O
```
training c9e6f938 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl5(I):
    # 5️⃣ Relational / structural – map each foreground cell to its mirrored
    # position on the right half using index arithmetic, then paint both halves
    H, W = shape(I)
    O = canvas(0, (H, add(W, W)))                                   # empty canvas, double width
    O = paint(O, toobject(ofcolor(I, 7), I))                        # left half (original foreground)
    # compute mirrored coordinates for the right half
    right_coords = apply(
        lambda p: (p[0], subtract(double(W), add(p[1], ONE))),
        ofcolor(I, 7)
    )
    right_obj = recolor(7, right_coords)                           # colour the new indices
    O = paint(O, right_obj)                                        # right half (mirrored foreground)
    return O
```
training 5614dbcf test 0.0 0.0 0.0 0.0 0.0
```python
def dsl2(I):
    # Object‑extraction route: split the grid into 3×3 macro‑blocks,
    # compute the dominant non‑zero colour of each block with `mostcolor`,
    # and rebuild the 3×3 output from the resulting colours.
    rows = vsplit(I, THREE)                                 # three horizontal strips (3 rows each)
    blocks = apply(lambda r: hsplit(r, THREE), rows)        # each strip → three vertical blocks
    colors = apply(lambda blk_row: apply(mostcolor, blk_row), blocks)   # colour of each 3×3 block
    # turn the colours into 1×1 canvases and concatenate back to a 3×3 grid
    cells = apply(lambda row: apply(lambda c: canvas(c, (ONE, ONE)), row), colors)
    row_grids = apply(lambda r: hconcat(hconcat(r[0], r[1]), r[2]), cells)
    O = vconcat(vconcat(row_grids[0], row_grids[1]), row_grids[2])
    return O
```
training 1caeab9d test 0.0 0.0 0.0 0.0 0.0
```python
def dsl2(I):
    # OBJECT‑EXTRACTION – extract each colour as an object, translate it so that
    # its top edge matches the top edge of colour 1, then paint all objects.
    top_one   = uppermost(ofcolor(I, ONE))
    nonzero   = difference(palette(I), initset(ZERO))
    # translate a single colour
    def translate(c):
        patch = ofcolor(I, c)                                 # cells of colour c
        dr    = subtract(top_one, uppermost(patch))           # required vertical shift
        return recolor(c, shift(patch, (dr, ZERO)))          # shift and keep colour
    shifted   = apply(translate, nonzero)                     # coloured patches
    all_patch = merge(shifted)                                # union of patches
    O         = paint(canvas(ZERO, shape(I)), all_patch)      # final picture
    return O
```
training 140c817e test 0.0 0.0 0.0 0.0 0.0
```python
def dsl4(I):
    # colour‑filtering – recolour seeds and their neighbours first,
    # then paint the cross using the original seed colour
    seed   = leastcolor(I)
    src    = ofcolor(I, seed)
    # recolour seeds → 2
    Oa     = paint(I, recolor(seed + 1, src))
    # neighbours of the original seeds → 3
    neigh  = difference(merge(apply(neighbors, src)), src)
    Ob     = paint(Oa, recolor(3, neigh))
    # rows/cols that contain a seed
    rows   = { r for (r, _) in src }
    cols   = { c for (_, c) in src }
    cross  = combine(
                { (r, c) for r in rows for c in range(width(I)) },
                { (r, c) for c in cols for r in range(height(I)) })
    # fill the cross with the seed colour, but keep the recoloured seeds unchanged
    cross_without_src = difference(cross, src)
    Oc = fill(Ob, seed, cross_without_src)
    return Oc
```
training 00576224 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl5(I):
    # RELATIONAL / STRUCTURAL – construct the output by addressing rows
    # through explicit index arithmetic and a single conditional branch.
    idxs   = asindices(canvas(0, (6, 6)))                     # all 6×6 positions
    # map each index (i,j) → colour from the appropriate source band
    def colour_at(p):
        i, j = p
        # which source row (0‑1 original, 2‑3 mirrored, 4‑5 original) ?
        src_i = i % 2
        src_j = j % 2
        # choose original or mirrored column based on vertical band
        col = branch(i < 2 or i >= 4,
                     index(I, (src_i, src_j)),               # original
                     index(I, (src_i, 1 - src_j)))           # mirrored
        return col
    # build a 6×6 grid whose (i,j) cell is colour_at((i,j))
    O = tuple(tuple(colour_at((i, j)) for j in range(6)) for i in range(6))
    return O
```
training 17cae0c1 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # GLOBAL SHAPE‑CLASSIFICATION per vertical third
    strips = hsplit(I, 3)                     # three vertical strips
    s0, s1, s2 = strips[0], strips[1], strips[2]

    def strip_color(S):
        cnt  = colorcount(S, 5)               # number of 5‑pixels
        h    = height(S)
        top  = equality(uppermost(ofcolor(S, 5)), 0)
        bot  = equality(lowermost(ofcolor(S, 5)), decrement(h))
        top_line    = both(top, equality(lowermost(ofcolor(S, 5)), 0))
        bot_line    = both(bot, equality(uppermost(ofcolor(S, 5)), decrement(h)))
        single      = equality(cnt, 1)
        border      = equality(cnt, 8)          # full perimeter of a 3×3 block
        return branch(single, 4,
               branch(border, 3,
               branch(top_line, 6,
               branch(bot_line, 1, 9))))

    c0 = strip_color(s0)
    c1 = strip_color(s1)
    c2 = strip_color(s2)

    out0 = canvas(c0, shape(s0))
    out1 = canvas(c1, shape(s1))
    out2 = canvas(c2, shape(s2))
    O = hconcat(hconcat(out0, out1), out2)
    return O
```
training 017c7c7b train 0.0 2.8284271247461903 0.07407407407407407 0.0 2.9025011988202642
```python
def dsl3(I):
    # VERTICAL SPLIT – obtain the upper half via vsplit
    G = switch(I, ONE, TWO)                     # 1 → 2
    top = first(vsplit(G, 2))                    # first piece = upper half
    O = vconcat(G, top)
    return O
```
training 1a244afd train 0.0 5.146264369941973 0.07687500000000003 0.0 5.223139369941972
```python
def dsl2(I):
    # OBJECT‑BASED – use the outbox of each 6 and keep only the cells that lie directly below
    six_objs   = colorfilter(fgpartition(I), 6)                     # one‑cell objects for every 6
    six_out    = mapply(outbox, six_objs)                         # cells surrounding each 6
    below_six  = shift(ofcolor(I, 6), DOWN)                       # the exact row beneath every 6
    target     = intersection(intersection(six_out, ofcolor(I, 1)), below_six)
    step1      = fill(I, 7, target)
    step2      = fill(step1, 1, shift(target, RIGHT))
    return replace(step2, 6, 8)
```
training 11852cab test 0.0 5.656854249492381 0.020000000000000018 0.0 5.676854249492381
```python
def dsl1(I):
    # -------- geometric mirroring ----------
    # 1️⃣  colour that occurs the fewest non‑zero cells  (rare)
    rare   = argmin(palette(I), lambda c: branch(c == 0, 10**9, colorcount(I, c)))
    # 2️⃣  colour that occurs the most non‑zero cells (common)
    common = argmax(palette(I), lambda c: branch(c == 0, -1,   colorcount(I, c)))
    # 3️⃣  centre of mass of the common colour → symmetry centre
    ctr    = centerofmass(ofcolor(I, common))                 # (rc, cc)
    # 4️⃣  all cells of the rare colour
    rcells = ofcolor(I, rare)
    # 5️⃣  mirrors of each rare cell w.r.t. that centre
    hmir   = apply(lambda p: (p[0],
                              add(ctr[1], subtract(ctr[1], p[1]))), rcells)
    vmir   = apply(lambda p: (add(ctr[0], subtract(ctr[0], p[0])),
                              p[1]), rcells)
    bmir   = apply(lambda p: (add(ctr[0], subtract(ctr[0], p[0])),
                              add(ctr[1], subtract(ctr[1], p[1]))), rcells)
    # 6️⃣  union of original rare cells and all their mirrors
    allpts = combine(combine(combine(rcells, hmir), vmir), bmir)
    # 7️⃣  recolour the union with the rare colour and paint over the input
    obj    = recolor(rare, allpts)
    O      = paint(I, obj)
    return O
```
training 0b17323b train 0.0 6.0 0.022222222222222254 0.3999999999057191 6.4222222221279415
```python
def dsl3(I):
    # COLOR‑FILTERING – build the full main diagonal,
    # keep only the part that is missing,
    # and under‑paint it so that 2 fills the background only.
    full_diag  = shoot(astuple(0, 0), subtract(shape(I), astuple(1, 1)))   # whole (0,0)→bottom‑right diagonal
    ones       = ofcolor(I, 1)
    last_one   = astuple(lowermost(ones), rightmost(ones))
    existing   = shoot(astuple(0, 0), last_one)                         # diagonal that already exists
    missing    = difference(full_diag, existing)                        # cells that must become 2
    mask_obj   = recolor(2, missing)                                   # turn them into a 2‑object
    O          = underpaint(I, mask_obj)                               # paint only where background is 0
    return O
```
training 19bb5feb train 0.0 9.788656935474513 2.5 0.0 12.288656935474513
```python
def dsl4(I):
    # GEOMETRIC‑TRIM APPROACH:
    #   Remove the outer zero border (trim) – the remaining grid is exactly the
    #   bounding box of the non‑zero pattern.  Its size yields the digits.
    sub  = trim(I)                                        # crop to tight bounding box
    h    = height(sub)
    w    = width(sub)
    ht   = divide(h, 10)
    hu   = subtract(h, multiply(ht, 10))
    wt   = divide(w, 10)
    wu   = subtract(w, multiply(wt, 10))
    base = canvas(0, (2, 2))
    O    = fill(fill(fill(fill(base, ht, initset((0, 0))),
                     hu, initset((0, 1))),
               wt, initset((1, 0))),
               wu, initset((1, 1)))
    return O
```
training 90f3ed37 train 0.0 12.679467196254514 0.5533333333333333 0.027735009803569147 13.260535539391416
```python
def dsl1(I):
    # GLOBAL – shoot a horizontal ray to the right from every 8 and colour the
    # first background cells it meets.
    rays   = mapply(lambda p: shoot((p[0], p[1] + 1), (0, 1)), ofcolor(I, 8))
    mask   = intersection(rays, ofcolor(I, 0))
    O      = paint(I, recolor(1, mask))
    return O
```
training 08ed6ac7 train 0.0 13.926143746267005 0.3456790123456791 0.0 14.271822758612686
```python
def dsl5(I):
    # RELATIONAL – colour each 5‑object by 1 + how many other 5‑objects lie completely above it.
    objs      = colorfilter(fgpartition(I), FIVE)
    # for each object compute its rank directly from the set of objects above it
    recolored = apply(
        lambda o: recolor(
            add(ONE,
                size(
                    mfilter(objs,
                             lambda x: greater(uppermost(x), uppermost(o))))),
            o),
        objs)
    O = paint(I, merge(recolored))
    return O
```
training 18286ef8 train 0.0 16.970562748477143 0.054027777777777675 0.0 17.02459052625492
```python
def dsl1(I):
    # GLOBAL – direct colour substitution everywhere.
    O = replace(I, 6, 9)
    return O
```
training 178fcbfb train 0.0 18.908712114635712 0.26363636363636367 0.0 19.172348478272077
```python
def dsl3(I):
    H, W = shape(I)
    O = canvas(0, (H, W))

    col2 = leftmost(ofcolor(I, TWO))
    O = fill(O, TWO, connect((0, col2), (H - 1, col2)))

    row3 = lowermost(backdrop(ofcolor(I, THREE)))
    O = fill(O, THREE, connect((row3, 0), (row3, W - 1)))

    row1 = lowermost(backdrop(ofcolor(I, ONE)))
    O = fill(O, ONE, connect((row1, 0), (row1, W - 1)))

    return O
```
training 0d87d2a6 train 0.0 21.955665197466008 0.6532142857142857 0.0 22.608879483180292
```python
def dsl5(I):
    # RELATIONAL – for every 1‑pixel generate its full vertical line,
    # union all those lines, recolour any touching 2‑object.
    verticals = merge(
        apply(lambda p: combine(shoot(p, UP), shoot(p, DOWN)),
              ofcolor(I, ONE)))
    band = combine(ofcolor(I, ONE), verticals)
    O = fill(I, ONE, band)

    twos = {obj for obj in fgpartition(O)
            if color(obj) == TWO and adjacent(obj, ofcolor(O, ONE))}
    O = fill(O, ONE, {(r, c) for obj in twos for (_, (r, c)) in obj})
    return O
```
training 025d127b train 0.0 23.96281913965828 0.09126984126984128 0.03004208839728021 24.0841310693254
```python
def dsl1(I):
    # GLOBAL – translate all non‑zero cells one step to the right (clipped at border)
    all_cells = asobject(I)
    moved     = shift(all_cells, RIGHT)
    empty     = canvas(0, shape(I))
    return paint(empty, moved)
```
training 1acc24af train 0.0 25.133406355900405 0.1250000000000001 0.0 25.2584063559004
```python
def dsl4(I):
    # geometric reasoning – rotate 90°, mirror vertically, rotate back;
    # keep 5s that are invariant under this transformation
    r90   = rot90(I)
    vm    = vmirror(r90)
    back  = rot270(vm)                                       # back to original orientation
    five  = ofcolor(I, FIVE)
    keep  = intersection(five, ofcolor(back, FIVE))
    O     = fill(I, TWO, difference(five, keep))
    return O
```
training 1d0a4b61 train 0.0 25.963435293459217 0.12159999999999993 0.0 26.085035293459214
```python
def dsl1(I):
    # GLOBAL – fill every 0‑pixel with the colour that appears in its
    # horizontally‑mirrored position.
    zeros   = ofcolor(I, 0)                     # all 0‑cells
    mirror  = hmirror(I)                       # horizontal mirror of the whole grid
    fillobj = toobject(zeros, mirror)          # object made of the mirrored colours
    O = paint(I, fillobj)                      # paint those colours on the original grid
    return O
```
training 17829a00 train 0.0 26.41021788557326 0.22265625 0.0 26.63287413557326
```python
def dsl3(I):
    # COLOUR‑FILTERING – turn every non‑dominant cell that touches a dominant
    # cell into the dominant colour, but keep the original outer frame.
    dom = mostcolor(I)
    other = difference(palette(I), initset(dom))
    # cells of a non‑dominant colour that are orthogonal neighbours of a dominant cell
    masks = apply(lambda c: intersection(ofcolor(I, c),
                                        delta(ofcolor(I, dom))),
                 other)
    grow = combine(*masks)                                 # union of all those cells
    h, w = shape(I)
    top    = asindices(crop(I, (0, 0), (1, w)))
    bottom = asindices(crop(I, (h-1, 0), (1, w)))
    left   = asindices(crop(I, (0, 0), (h, 1)))
    right  = asindices(crop(I, (0, w-1), (h, 1)))
    border = combine(combine(top, bottom), combine(left, right))
    interior = difference(grow, border)
    recoloured = fill(I, dom, interior)                     # recolour the interior part
    O = paint(recoloured, toobject(border, I))             # restore border
    return O
```
training 182e5d0f train 0.0 28.23562273367665 0.29477134925852877 0.0 28.53039408293518
```python
def dsl3(I):
    # COLOR‑FILTERING – build a mask, erase those cells, then recolour them to 5.
    G      = replace(I, 5, 7)
    m1     = intersection(ofcolor(I, 3), shift(ofcolor(I, 7), RIGHT))
    m2     = intersection(ofcolor(I, 3), shift(ofcolor(I, 3), DOWN))
    mask   = combine(m1, m2)                             # cells that should become 5
    O0     = cover(G, mask)                              # clear the masked cells (to 0)
    O      = fill(O0, 5, mask)                           # repaint them with colour 5
    return O
```
training 15663ba9 train 0.0 40.09501112411194 0.3795822766976613 0.0 40.4745934008096
```python
def dsl1(I):
    # GLOBAL EXTREME COLUMNS – colour the leftmost non‑zero column with 4
    # and the rightmost non‑zero column with 2 (whole picture at once).
    nz      = sfilter(asindices(I), lambda rc: index(I, rc) != 0)
    left    = leftmost(nz)
    right   = rightmost(nz)
    left_m  = recolor(4, sfilter(nz, lambda rc: rc[1] == left))
    right_m = recolor(2, sfilter(nz, lambda rc: rc[1] == right))
    O = paint(I, left_m)
    O = paint(O, right_m)
    return O
```
training 1d61978c train 0.0 40.44994432064365 0.08984375 0.0 40.53978807064365
```python
def dsl5(I):
    # ROTATE‑180 REPLACE: rotate 180°, replace 5→8, rotate back.
    O = rot180(replace(rot180(I), 5, 8))
    return O
```
training 1a07d186 train 0.0 40.31369723052605 0.15619256474519627 0.3327917501079515 40.8026815453792
```python
def dsl4(I):
    # GEOMETRIC – overlay the grid with its vertical mirror and keep only the
    # intersecting cells (common part of original and mirror).
    MIR      = vmirror(I)                                       # vertical mirror
    INTER    = intersection(asobject(I), asobject(MIR))          # common cells
    O        = paint(canvas(0, shape(I)), INTER)                # draw intersection
    return O
```
training 0a2355a6 train 0.0 40.24140528443731 0.8668521954236239 0.0 41.10825747986094
```python
def dsl4(I):
    # GEOMETRIC‑MIRRORING: cells that survive both horizontal
    # and vertical mirroring are interior (2); border (1);
    # isolated cells (3) as before.
    mask = ofcolor(I, 8)

    hmir = hmirror(mask)          # horizontal mirror
    vmir = vmirror(mask)          # vertical mirror

    interior = intersection(mask, intersection(hmir, vmir))

    neighbours = combine(shift(mask, UP),
                   combine(shift(mask, DOWN),
                       combine(shift(mask, LEFT), shift(mask, RIGHT))))
    singles   = difference(mask, neighbours)

    border = difference(mask, combine(interior, singles))

    return paint(
        canvas(0, shape(I)),
        merge([recolor(2, interior), recolor(1, border), recolor(3, singles)])
    )
```
training 09c534e7 train 0.0 42.05826595696517 0.2059567901234568 0.0 42.26422274708863
```python
def dsl1(I):
    # colour‑filtering: recolour 1‑cells that lie inside the bounding box
    # of any colour > 1.
    seeds   = sfilter(palette(I), lambda c: c > 1)                     # colours to use
    boxes   = apply(lambda c: box(ofcolor(I, c)), seeds)              # their boxes
    patches = prapply(lambda c, b: recolor(c,
                                          intersection(b,
                                                       ofcolor(I, 1))),
                     seeds, boxes)                                    # colour the 1‑mask
    O = paint(I, merge(patches))                                     # paint on top
    return O
```
training 009d5c81 train 0.0 41.581064894786834 0.45408163265306123 0.740060442872642 42.77520697031253
```python
def dsl3(I):
    # COLOR‑FILTER – select the 8‑object, decide colour from its interior,
    # and wipe any 1‑pixel that lies strictly inside the object’s outline.
    p8        = ofcolor(I, 8)
    interior  = intersection(p8, shift(p8, UP))
    interior  = intersection(interior, shift(p8, DOWN))
    interior  = intersection(interior, shift(p8, LEFT))
    interior  = intersection(interior, RIGHT)
    col = branch(greater(size(interior), 0), 3,
           branch(greater(size(p8), 50), 7, 2))
    O = replace(I, 8, col)
    # cells of colour 1 that are also inside the 8‑object’s outline
    inside    = intersection(ofcolor(I, 1), p8)
    O = cover(O, inside)
    return O
```
training 00dbd492 train 0.0 42.68365161422002 0.6844662704003363 0.0 43.368117884620354
```python
def dsl1(I):
    # OBJECT‑EXTRACTION: 2‑frames → interior zeros → size ranking
    borders   = colorfilter(objects(I, True, False, True), 2)
    interiors = apply(
        lambda o: intersection(difference(backdrop(o), o), ofcolor(I, 0)),
        borders)

    ranked   = order(interiors, lambda p: size(p))
    smallest = first(ranked)
    largest  = last(ranked)
    rest     = difference(merge(interiors), combine(smallest, largest))

    O = fill(I, 8, smallest)
    O = fill(O, 3, largest)
    O = fill(O, 4, rest)
    return O
```
training 14754a24 train 0.0 45.32515153339341 0.2296313700918965 0.0 45.5547829034853
```python
def dsl4(I):
    # ----- GEOMETRIC – use vertical symmetry to locate the “mirrored” 5’s -----
    # 1. mirror the whole grid vertically (around the horizontal centre)
    mir = vmirror(I)

    # 2. cells that are 5 both in the original and in the mirrored image
    common5 = intersection(ofcolor(I, 5), ofcolor(mir, 5))

    # 3. from those, select the ones that are also adjacent (Manhattan‑1) to a 4
    fours   = ofcolor(I, 4)
    neigh4  = combine(
                combine(shift(fours, UP),    shift(fours, DOWN)),
                combine(shift(fours, LEFT),  shift(fours, RIGHT)))
    target = intersection(common5, neigh4)
    return fill(I, 2, toobject(target, I))
```
training 150deff5 train 0.0 48.31235619842196 0.305050505050505 0.0 48.61740670347247
```python
def dsl4(I):
    # GEOMETRIC REASONING (transpose → horizontal interior)
    # Transpose the picture, find the interior of horizontal runs (≥3),
    # then transpose back to obtain the vertical interiors in the original grid.
    T           = cmirror(I)                                   # transpose
    five_T      = ofcolor(T, 5)
    horiz_int_T = intersection(intersection(five_T, shift(five_T, LEFT)),
                               shift(five_T, RIGHT))         # interior of horizontal runs
    spine       = cmirror(horiz_int_T)                         # back to original orientation
    O = fill(replace(I, 5, 8), 2, spine)
    return O
```
training 0520fde7 train 9.0 12 27 3.0 51.0
```python
def dsl4(I):
    # Geometric reasoning: outline the 5‑region, mirror it horizontally, render on a blank canvas, then crop.
    five     = ofcolor(I, 5)               # cells coloured 5
    outline  = box(five)                   # border of the 5‑region
    mirrored = hmirror(outline)           # horizontal mirror
    base     = canvas(0, shape(I))        # empty canvas with original size
    painted  = fill(base, 2, mirrored)    # draw the mirrored outline in colour 2
    O = compress(painted)                  # crop to minimal occupied area
    return O
```
training 03560426 train 0.0 52.41209026270125 0.59 0.5439477180475568 53.54603798074881
```python
def dsl1(I):
    # GLOBAL – remove all empty outer rows/cols, delete interior empty
    # rows/cols, rotate 90° clockwise and draw the result on a fresh canvas.
    trimmed   = trim(I)
    compact  = compress(compress(trimmed))
    rotated  = rot90(compact)
    empty    = canvas(0, shape(I))
    return paint(empty, asobject(rotated))
```
training 00d62c1b train 0.0 53.72587067194518 0.2930555555555556 0.0 54.018926227500735
```python
def dsl2(I):
    # 2 – projection intersection:
    # all cells that lie both in the left‑projection of some 3
    # and in the right‑projection of some 3 are exactly the cells
    # that have a 3 on each side.  Intersect with the zero cells.
    zeros = ofcolor(I, 0)
    threes = ofcolor(I, 3)

    left_proj  = merge(mapply(lambda p: shoot(p, LEFT),  threes))
    right_proj = merge(mapply(lambda p: shoot(p, RIGHT), threes))

    interior = intersection(zeros, intersection(left_proj, right_proj))
    return fill(I, 4, toobject(interior, I))
```
training 14b8e18c train 0.0 54.63348191813314 0.44000000000000006 0.0 55.07348191813314
```python
def dsl5(I):
    # RELATIONAL / STRUCTURAL – recolour cells that are sandwiched horizontally
    # between two 6’s (a 6 on the left and a 6 on the right).
    six      = ofcolor(I, 6)
    left     = shift(six, LEFT)
    right    = shift(six, RIGHT)
    hpair    = intersection(left, right)                    # cells with a 6 on each side
    O        = paint(I, recolor(2, hpair))
    return O
```
training 0e206a2e train 0.0 58.0618056420016 0.16527777777777775 1.6217186728590014 59.84880209263838
```python
def dsl4(I):
    # 4️⃣ Geometric – keep the cells that are symmetric w.r.t. a horizontal mirror
    M = hmirror(I)                                          # mirror across the horizontal centre line
    O = cellwise(I, M, 0)                                   # keep cells identical to their mirror
    return O
```
training 17b866bd train 0.0 60.67437180029799 0.22191220238095233 0.0 60.89628400267894
```python
def dsl2(I):
    # OBJECT‑EXTRACTION – keep exactly the 8‑object, then add a 4 at its centre.
    obj8    = toobject(ofcolor(I, 8), I)                # the 8 component as an object
    step1   = paint(canvas(0, shape(I)), obj8)          # redraw only the 8 shape on a blank grid
    cen8    = center(obj8)                               # centre of that shape
    O       = fill(step1, 4, backdrop({cen8}))           # place a 4 at the centre
    return O
```
training 06df4c85 train 0.0 75.19861594555928 0.22879017013232505 0.0 75.42740611569161
```python
def dsl2(I):
    # OBJECT EXTRACTION – erase the rare‑colour objects and repaint them
    # with the most common non‑background colour.
    nonzero   = ofcolor(I, 0)                     # all non‑background cells
    rare      = leastcolor(nonzero)               # colour that occurs the fewest
    common    = mostcolor(nonzero)                # colour that occurs the most
    objs      = objects(I, univalued=True,
                       diagonal=False,
                       without_bg=True)       # all colour‑uniform objects
    rare_objs = colorfilter(objs, rare)           # keep only the rare ones
    patch     = merge(apply(toindices, rare_objs))  # their cells as a patch
    O = cover(I, patch)                           # erase them (set to 0)
    O = paint(O, recolor(common, patch))          # recolour with common colour
    return O
```
training 0e671a1a train 0.0 82.95565727721231 0.42603550295857995 0.0 83.3816927801709
```python
def dsl1(I):
    # geometric: draw the two L‑shapes that connect the left‑most cell (hub)
    # to the top‑most cell (vertical‑first) and to the right‑most cell
    # (horizontal‑first).  New cells are coloured 5.
    nz   = difference(asindices(I), ofcolor(I, 0))
    hub  = argmin(nz, lambda p: p[1])          # left‑most
    top  = argmin(nz, lambda p: p[0])          # top‑most
    right = argmax(nz, lambda p: p[1])         # right‑most

    # hub → top  (vertical then horizontal)
    path_t = combine(connect(hub, astuple(top[0], hub[1])),
                     connect(astuple(top[0], hub[1]), top))
    # hub → right (horizontal then vertical)
    path_r = combine(connect(hub, astuple(hub[0], right[1])),
                     connect(astuple(hub[0], right[1]), right))

    paint = difference(combine(path_t, path_r), nz)
    return fill(I, 5, paint)
```
training 18447a8d train 0.0 84.97320659876738 1.0941999177293296 0.0 86.0674065164967
```python
def dsl3(I):
    # ---------- 3. Bounding‑box sub‑grid cycle ----------
    # extract every non‑background component, apply the global
    # 9‑1‑3 cycle inside its minimal rectangle and paste back
    objs = {o for o in objects(I,
                               univalued=False,
                               diagonal=False,
                               without_bg=True)
            if color(o) in {9, 1, 3}}
    O = I
    for o in objs:
        sub = subgrid(o, I)                # smallest rectangle containing o
        # global cycle on the sub‑grid (same as dsl1 but without placeholders)
        sub0 = replace(sub, 9, 0)
        sub1 = replace(sub0, 1, 9)
        sub2 = replace(sub1, 3, 1)
        subc = replace(sub2, 0, 3)
        # put the transformed rectangle back, overwriting only the cells of o
        O = paint(O, toobject(o, subc))
    return O
```
training 184a9768 train 0.0 94.3501067717822 0.7226406926406928 0.5674316208684692 95.64017908529135
```python
def dsl3(I):
    # GEOMETRIC OVERLAY: mirror vertically and retain original colours where they exist
    V = vmirror(I)                           # vertical mirror of the input
    O = cellwise(I, V, fallback=0)           # union, original colours dominate
    return O
```
training 09629e4f train 0.0 96.74709297958259 1.1900826446280992 0.0 97.9371756242107
```python
def dsl1(I):
    # ---- object‑extraction – colour‑majority per rectangular component ----
    # turn the separator colour (5) into background (0)
    G = switch(I, 5, 0)

    # each maximal 4‑connected component of non‑background cells is a block
    blocks = objects(G, False, False, True)

    # recolour each block with the most common colour that occurs inside it
    recoloured = apply(
        lambda o: recolor(
            mostcolor(subgrid(o, I)),
            o),
        blocks)

    O = paint(I, merge(recoloured))
    return O
```
training 1d398264 train 0.0 97.75526156090751 0.7141666666666666 0.8399209142078068 99.30934914178201
```python
def dsl1(I):
    # DIAGONAL‑TO‑CORNER – for each coloured cell draw a line to the
    # nearest corner (Manhattan distance) and keep the original cells.
    h      = decrement(height(I))
    w      = decrement(width(I))
    corners = {(0,0), (0,w), (h,0), (h,w)}

    # nearest corner of a point p
    nearest = lambda p: argmin(corners,
                              lambda c: add(abs(p[0]-c[0]), abs(p[1]-c[1])))
    # segment from p to its nearest corner
    segment = lambda p: connect(p, nearest(p))

    cells   = merge(apply(lambda c: ofcolor(I, c),
                    difference(palette(I), {0})))
    segs    = merge(apply(segment, cells))
    O       = paint(I, asobject(segs))
    return O
```
training 18419cfa train 0.0 101.70025937952066 2.488784907902555 0.45155464636892795 104.64059893379215
```python
def dsl4(I):
    # fill the background (colour 0) with 2 using underfill
    O = underfill(I, 2, ofcolor(I, 0))
    return O
```
training 10fcaaa3 train 0.0 126.26983536659347 1.3958333333333333 0.11840169937862338 127.78407039930545
```python
def dsl3(I):
    # ── 3️⃣  Colour‑filter – keep original colours, replace everything else by a checker ──
    h, w = shape(I)

    tiled = vconcat(hconcat(I, I), hconcat(I, I))

    chk = frozenset({(r, c) for r in range(2 * h)
                    for c in range(2 * w) if (r + c) % 2 == 0})
    BG  = fill(canvas(0, (2 * h, 2 * w)), 8, chk)

    coloured = merge(difference(fgpartition(tiled), colorfilter(fgpartition(tiled), 0)))

    return underpaint(BG, coloured)
```
training 17b80ad2 train 0.0 133.4535961175839 0.9657887055506736 0.2025539178992487 134.62193874103383
```python
def dsl4(I):
    # GEOMETRIC – mirror the picture first horizontally, then vertically (full 180° flip by composition).
    O = vmirror(hmirror(I))
    return O
```
training 15113be4 train 0.0 140.56177859032198 0.616257088846881 0.0 141.17803567916886
```python
def dsl1(I):
    # GLOBAL‑REPLACE: replace every 1 with the most frequent non‑{0,1,4} colour.
    other = sfilter(palette(I), lambda c: c not in {0, 1, 4})
    main  = argmax(other, lambda c: colorcount(I, c))
    O = replace(I, 1, main)
    return O
```
training 045e512c train 0.0 156.20270090434946 1.764172335600907 0.42906703040803207 158.39594027035838
```python
def dsl5(I):
    # LOWER‑LEFT‑CORNER anchoring replication of the whole pattern.
    #   – Upscale the whole coloured pattern 2×.
    #   – Use the lower‑left corner of the enlarged pattern as the anchor.
    #   – Paste a copy anchored at every original non‑zero cell.
    whole   = merge(objects(I, F, F, T))
    sub     = subgrid(backdrop(whole), I)
    big     = upscale(sub, TWO)
    anchor  = llcorner(asobject(big))
    anchors = merge(apply(lambda c: ofcolor(I, c), palette(I)))   # all coloured cells
    copies  = apply(lambda p: shift(asobject(big), subtract(p, anchor)), anchors)
    O = paint(canvas(0, shape(I)), merge(copies))
    return O
```
training 05a7bcf2 train 0.0 321.5656372004054 1.0755555555555554 0.27105759942289875 322.91225035538383
```python
def dsl3(I):
    # COLOR‑FILTERING – replace colours then add neighbour cells.
    O = replace(I, 8, 4)                         # 8 → 4 (left cell)
    O = fill(O, 4, shift(ofcolor(I, 8), (0, 1))) # right neighbour of 8 → 4
    O = replace(O, 2, 8)                         # 2 → 8 (left cell)
    O = fill(O, 3, shift(ofcolor(I, 2), (0, 1))) # right neighbour of 2 → 3
    return O
```
training 1c786137 train 24.476215473033584 353 146 2.176872136536147 525.6530876095698
```python
def dsl2(I):
    # OBJECT EXTRACTION – keep the *smallest* coloured object, extract its bounding box and mirror it horizontally
    objs      = objects(I, True, False, True)                 # all coloured objects
    smallest  = argmin(objs, lambda o: size(o))               # object with fewest cells
    sub       = subgrid(smallest, I)                         # its minimal bounding box
    O         = hmirror(sub)                                 # horizontal mirror
    return O
```
training c909285e train 20.67017498218515 245 362 0.9525102180569394 628.622685200242
```python
def dsl1(I):
    # GLOBAL – remove uniform outer margin, detect period on the remaining object,
    # crop the fundamental tile and recolour its background with the tile's dominant colour.
    bg      = mostcolor(I)
    O0      = replace(I, bg, 0)                     # background → 0
    O1      = compress(O0)                          # strip outer 0‑rows/cols
    nb      = difference(asindices(O1), ofcolor(O1, 0))
    obj     = toobject(nb, O1)                      # coloured object for period detection
    hp      = hperiod(obj)                          # horizontal period
    vp      = vperiod(obj)                          # vertical period
    anchor  = first(nb)                              # top‑left non‑bg cell after trim
    tile    = crop(O1, anchor, astuple(vp, hp))     # fundamental tile
    fillcol = mostcolor(tile)                       # dominant colour inside the tile
    O       = replace(tile, 0, fillcol)             # restore background with that colour
    return O
```
training 1be83260 train 3.6502815398728847 260 684 0.09348288734108055 947.7437644272139
```python
def dsl3(I):
    # OBJECT‑LEVEL – work with individual colour objects,
    # recolour them and finally compose on a 1‑background.
    C   = compress(I)                                         # crop zeros
    BG  = recolor(1, toobject(ofcolor(C, 0), C))              # 0 → 1
    O2  = recolor(3, toobject(ofcolor(C, 2), C))              # 2 → 3
    O3  = recolor(2, toobject(ofcolor(C, 3), C))              # 3 → 2
    O4  = toobject(ofcolor(C, 4), C)                          # colour 4 unchanged
    ALL = combine(combine(combine(combine(BG, O2), O3), O4), BG) # union of all objects
    O   = paint(replace(C, 0, 1), ALL)                        # paint on 1‑background
    return O
```
training 1190e5a7 train 30.72024634330557 903 413 1.5196271653105575 1348.2398735086163
```python
def dsl5(I):
    # Relational: periodicity of the dominant‑colour mask,
    # with a fallback to the whole grid when the period is zero.
    dom      = mostcolor(I)
    dom_mask = ofcolor(I, dom)
    obj      = toobject(dom_mask, I)
    vsize    = vperiod(obj)
    hsize    = hperiod(obj)
    vsize    = branch(equality(vsize, ZERO), shape(I)[0], vsize)
    hsize    = branch(equality(hsize,   ZERO), shape(I)[1], hsize)
    O        = canvas(dom, (vsize, hsize))
    return O
```
training 0a938d79 train 3.414213562373095 206.87817782917153 1157.5 0.4123281420588456 1368.2047195336036
```python
def dsl1(I):
    # ── GLOBAL‑TRANSFORM ──  compress → pattern → tile both axes
    slice_ = compress(I)                                   # tight bounding box
    objs   = objects(slice_, False, False, True)           # objects already relative
    hb, wb = height(slice_), width(slice_)

    base = canvas(0, (hb, wb))

    rows_pat = merge(apply(
        lambda o: fill(base,
                       color(o),
                       {(r, c) for (r, c) in asindices(base)
                        if r == center(o)[0]}),
        objs))

    cols_pat = merge(apply(
        lambda o: fill(base,
                       color(o),
                       {(r, c) for (r, c) in asindices(base)
                        if c == center(o)[1]}),
        objs))

    pat = branch(greater(hb, wb), rows_pat, cols_pat)      # orientation by aspect
    tmp = vupscale(pat, divide(height(I), hb))             # repeat vertically
    result = hupscale(tmp, divide(width(I), wb))            # repeat horizontally
    return result
```
training 15660dd6 train 9.857300762134084 1213 287 0.23639329961725675 1510.0936940617516
```python
def dsl4(I):
    # GEOMETRIC – rotate so that vertical repetitions become horizontal,
    # trim, compute the horizontal period, split that rectangle, keep the
    # first block and rotate back.
    c   = trim(I)
    c   = replace(c, 8, 5)
    c   = replace(c, 1, 9)
    c   = replace(c, 3, 8)
    G   = replace(c, 2, 7)
    R   = rot90(G)                         # height ↔ width
    R   = trim(R)                         # remove the former top/bottom borders
    pat = asobject(R)
    per = hperiod(pat)                    # horizontal period = original vertical period
    parts = hsplit(R, per)                # horizontal slices of width = period
    part = first(parts)                   # keep the first slice
    O = rot270(part)                      # rotate back to original orientation
    return O
```
training 1a6449f1 train 48.52134072229297 1736 1108 1.406944427647852 2893.9282851499406
```python
def dsl2(I):
    # Periodic tile after removing the uniform outer border
    trimmed = trim(I)                      # cut away the uniform background border
    obj = asobject(trimmed)               # object of the trimmed grid
    vp  = vperiod(obj)                    # vertical period
    hp  = hperiod(obj)                    # horizontal period
    O   = crop(trimmed, ORIGIN, (vp, hp)) # tile of the trimmed picture
    return O
```
training 05269061 train nan nan nan nan nan
```python
def dsl1(I):
    # GLOBAL‑TILE:  build a 3×3 colour prototype from the three colours
    # (ordered by centre‑of‑mass) and repeat it over the whole grid.
    objs = objects(I, univalued=True, diagonal=False, without_bg=True)

    sum_of = lambda o: add(centerofmass(o)[0], centerofmass(o)[1])
    o0 = argmin(objs, sum_of)
    o1 = argmin(difference(objs, {o0}), sum_of)
    o2 = argmin(difference(objs, {o0, o1}), sum_of)

    c0 = color(o0); c1 = color(o1); c2 = color(o2)

    # all coordinates of a 3×3 square
    proto_coords = combine(
        apply(lambda r: apply(lambda c: (r, c), interval(0, 3, 1)),
        interval(0, 3, 1))

    # masks for (r+c) % 3 == 0,1,2  (using equality with both possible sums)
    mk0 = merge(apply(
        lambda rc: branch(either(equality(add(rc[0], rc[1]), 0),
                           equality(add(rc[0], rc[1]), 3)),
                       initset(rc), set()),
        proto_coords))

    mk1 = merge(apply(
        lambda rc: branch(either(equality(add(rc[0], rc[1]), 1),
                           equality(add(rc[0], rc[1]), 4)),
                       initset(rc), set()),
        proto_coords))

    mk2 = merge(apply(
        lambda rc: branch(either(equality(add(rc[0], rc[1]), 2),
                           equality(add(rc[0], rc[1]), 5)),
                       initset(rc), set()),
        proto_coords))

    obj0 = recolor(c0, mk0)
    obj1 = recolor(c1, mk1)
    obj2 = recolor(c2, mk2)

    empty = canvas(0, (3, 3))
    proto = paint(paint(paint(empty, obj0), obj1), obj2)

    # tile the prototype
    row_offs = interval(0, height(I), 3)
    col_offs = interval(0, width(I), 3)
    anchors = merge(apply(lambda r: apply(lambda c: (r, c), col_offs), row_offs))

    tiled = apply(lambda off: paint(empty, shift(proto, off)), anchors)
    O = merge(tiled)
    return O
```
training 0607ce86 train nan nan nan nan nan
```python
def dsl1(I):
    # RELATIONAL – replace each non‑zero, non‑8 row by the most frequent such row
    zero_row = repeat(0, width(I))
    rows         = apply(identity, I)                                   # all rows as tuples
    cand_rows    = mfilter(rows, lambda r: any(c != 0 and c != 8 for c in r))
    most_common  = mostcommon(cand_rows)                                 # the prototype row
    O = apply(
        lambda r: r if any(c == 8 for c in r) else                      # keep rows that contain 8
                 (most_common if any(c != 0 for c in r) else zero_row), # replace others
        I)
    return O
```
training 070dd51e train nan nan nan nan nan
```python
def dsl1(I):
    # Object‑level: each non‑background object appears exactly twice.
    # Connect its two cells with a straight Manhattan segment,
    # drawing colors in ascending order so later (higher) colors overwrite.
    C = order(
            mfilter(palette(I), lambda c: colorcount(I, c) == 2),
            lambda c: c)                                 # low → high
    G = canvas(0, shape(I))
    _ = apply(
            lambda c:
                fill(
                    G, c,
                    connect(
                        argmin(corners(toobject(ofcolor(I, c), I)),
                                lambda p: p[0] + p[1]),
                        argmax(corners(toobject(ofcolor(I, c), I)),
                                lambda p: p[0] + p[1]))
                ),
            C)
    return G
```
training 0962bcdd train nan nan nan nan nan
```python
def dsl1(I):
    # GLOBAL PERIODIC TILING OF THE MINIMAL NON‑ZERO PATTERN
    prim = argmax(difference(palette(I), initset(0)),
                  lambda c: colorcount(I, c))
    sec0 = other(difference(palette(I), initset(0)), prim)
    sec  = branch(equality(sec0, initset(0)), SIX, sec0)

    # minimal pattern (all non‑zero cells)
    pat   = combine(ofcolor(I, prim), ofcolor(I, sec0))

    # horizontal / vertical periods of that pattern
    hp    = hperiod(pat)
    vp    = vperiod(pat)

    # all shifts that tile the whole canvas
    hs    = interval(0, width(I), hp)
    vs    = interval(0, height(I), vp)

    # shifted copies of the pattern
    shifted = mapply(lambda dv, dh: shift(pat, (dv, dh)), vs, hs)

    # union of all copies
    tiled = merge(shifted)

    O = canvas(0, shape(I))
    O = fill(O, prim, ofcolor(tiled, prim))
    O = fill(O, sec , ofcolor(tiled, sec))
    return O
```
training 0a1d4ef5 train nan nan nan nan nan
```python
def dsl1(I):
    # ---------- Global colour‑frequency ----------
    # 1. Identify the background colour.
    # 2. Take all other colours.
    # 3. Count how many cells each colour occupies.
    # 4. Sort the counts descending and return them as a tuple.
    bg       = mostcolor(I)
    cols     = difference(palette(I), initset(bg))
    cnts     = apply(lambda c: colorcount(I, c), cols)
    sorted_c = order(cnts, lambda n: -n)
    O = totuple(sorted_c)
    return O
```
training 0b148d64 test nan nan nan nan nan
```python
def dsl1(I):
    # global‑difference: colour that appears only in the lower half
    top      = tophalf(I)
    bottom   = bottomhalf(I)
    new_cols = difference(palette(bottom), palette(top))
    target   = first(sfilter(new_cols, lambda c: c != 0))
    O        = subgrid(ofcolor(I, target), I)
    return O
```
training 0bb8deee train nan nan nan nan nan
```python
def dsl1(I):
    # colour that forms a full‑height or full‑width line (the separator)
    sep = extract(palette(I),
                  lambda c: either(equality(height(box(ofcolor(I, c))), height(I)),
                                 equality(width(box(ofcolor(I, c))),  width(I)))
    # erase the separator
    cleaned = replace(I, sep, 0)

    # bring the internal zero column to a border, compress, bring it back;
    # then do the same for a possible internal zero row.
    step1 = vmirror(cleaned)                     # vertical mirror
    step2 = compress(step1)                      # remove outer zero columns
    step3 = vmirror(step2)                       # restore orientation
    step4 = hmirror(step3)                        # horizontal mirror
    step5 = compress(step4)                      # remove outer zero rows
    step6 = hmirror(step5)                       # restore orientation

    O = trim(step6)                              # final border cleanup
    return O


# ----------------------------------------------------------------------
# 2️⃣  Object‑extraction & side‑by‑side concatenation
# ----------------------------------------------------------------------
```
training 0becf7df train nan nan nan nan nan
```python
def dsl1(I):
    # GLOBAL – cascade two global colour‑swaps with SWITCH
    C   = palette(I) - {ZERO}
    a1  = valmax(C, lambda c: colorcount(I, c))
    r1  = difference(C, initset(a1))
    a2  = branch(equality(size(r1), ZERO), ZERO,
                 lambda: valmax(r1, lambda c: colorcount(I, c)))
    r2  = difference(r1, initset(a2))
    a3  = branch(equality(size(r2), ZERO), ZERO,
                 lambda: valmax(r2, lambda c: colorcount(I, c)))
    r3  = difference(r2, initset(a3))
    a4  = branch(equality(size(r3), ZERO), ZERO,
                 lambda: valmax(r3, lambda c: colorcount(I, c)))
    O1 = switch(I, a1, a2)          # first most‑frequent pair
    O  = switch(O1, a3, a4)         # second most‑frequent pair
    return O
```
training 0f63c0b9 train nan nan nan nan nan
```python
def dsl1(I):
    # GLOBAL – each row gets the colour of its nearest seed row.
    # Seed rows and the two border rows become completely filled,
    # all other rows keep only the two border cells.
    H = height(I); W = len(I[0])
    S = fgpartition(I)                                      # seed objects

    r   = lambda o: first(toindices(o))[0]                 # row of a seed
    col = lambda y: color(argmin(S, lambda o: abs(r(o)-y)))  # nearest‑seed colour

    rows      = interval(0, H, 1)                           # all row indices
    full_rows = combine(combine(apply(r, S), initset(0)), initset(H-1))

    full_patch = lambda y: shift(connect((0, 0), (0, W-1)), (y, 0))
    edge_patch = lambda y: frozenset({(y, 0), (y, W-1)})

    full_objs = apply(lambda y: recolor(col(y), full_patch(y)), full_rows)
    edge_objs = apply(lambda y: recolor(col(y), edge_patch(y)), rows)

    O = paint(canvas(0, (H, W)), combine(full_objs, edge_objs))
    return O
```
training 103eff5b train nan nan nan nan nan
```python
def dsl1(I):
    # SCALE‑AND‑CLIP – scale the visible template to the mask size
    # and keep only the cells that lie inside the original 8‑mask.
    region8 = ofcolor(I, 8)
    box8    = backdrop(region8)

    tmpl_objs = {o for o in objects(I, False, True, True) if color(o) != 8}
    tmpl      = merge(tmpl_objs)
    box_tmpl  = backdrop(tmpl)
    tmpl_grid = subgrid(box_tmpl, I)

    vfac = divide(height(box8), height(box_tmpl))
    hfac = divide(width (box8), width (box_tmpl))

    scaled    = hupscale(vupscale(tmpl_grid, vfac), hfac)
    scaledobj = toobject(asindices(scaled), scaled)

    # keep only the part that coincides with the mask
    inside    = intersection(toindices(scaledobj), region8)
    clipped   = asobject(inside, scaled)

    cleared = cover(I, region8)
    O = paint(cleared, clipped)
    return O
```
training 1190bc91 train nan nan nan nan nan
```python
def dsl1(I):
    # STRUCTURAL REASONING – fill both diagonals of every coloured cell.
    # Directions for the four diagonal rays.
    dr  = astuple( 1,  1)   # down‑right
    ul  = astuple(-1, -1)   # up‑left
    dl  = astuple( 1, -1)   # down‑left
    ur  = astuple(-1,  1)   # up‑right

    # All indices of the input grid.
    all_idx = asindices(I)

    # For each index, produce the union of the four diagonal rays that
    # pass through it (including the index itself).
    def diag_union(p):
        return union(
                union(shoot(p, dr), shoot(p, ul)),
                union(shoot(p, dl), shoot(p, ur))
        )

    # Apply the above to every coloured cell (value > 0) and collect the
    # coloured points together with their original colour.
    coloured = apply(lambda p: recolor(index(I, p), diag_union(p)),
                     difference(all_idx, ofcolor(I, 0)))

    # Start from a blank canvas and paint every coloured point.
    O = paint(canvas(0, shape(I)), colored_union(coloured))
    return O
```
training 11dc524f train nan nan nan nan nan
```python
def dsl1(I):
    # GLOBAL – clear both objects, then paint the moved 2 and the unchanged 5.
    obj2 = ofcolor(I, 2)
    obj5 = ofcolor(I, 5)

    # direction from 2 to 5 (unit vector)
    dir_vec = gravitate(obj2, obj5)

    # raw gaps on each axis
    h_raw = subtract(leftmost(obj5), rightmost(obj2))
    v_raw = subtract(uppermost(obj5), lowermost(obj2))

    # total Manhattan gap
    gap = add(multiply(h_raw, sign(h_raw)),
               multiply(v_raw, sign(v_raw)))

    # distance to move (gap‑1, but not negative)
    shift_len = branch(greater(gap, 0), decrement(gap), ZERO)
    shift_vec = multiply(dir_vec, shift_len)

    # erase both objects, then repaint 5 and the shifted 2
    O = cover(I, combine(obj2, obj5))                 # background where the two objects were
    O = paint(O, shift(obj2, shift_vec))              # moved colour‑2
    O = paint(O, obj5)                               # original colour‑5
    return O
```
training 11e1fe23 train nan nan nan nan nan
```python
def dsl1(I):
    # Global – use the full grid dimensions to locate the centre,
    # then shift every non‑zero cell two steps toward that centre.
    h, w = shape(I)
    rc0 = halve(h)
    rc = subtract(rc0, branch(even(rc0), 0, 1))
    cc = halve(w)                                   # floor‑mid column
    nz = difference(asindices(I), ofcolor(I, 0))
    def mover(p):
        v  = index(I, p)
        dr = multiply(sign(subtract(rc, p[0])), 2)
        dc = multiply(sign(subtract(cc, p[1])), 2)
        np = add(p, astuple(dr, dc))
        return (v, np)
    O = paint(I, apply(mover, nz))
    O = recolor(5, {(rc, cc)})
    return O
```
training 12422b43 train nan nan nan nan nan
```python
def dsl1(I):
    # OBJECT‑EXTRACTION – rows that contain colour 5 are cleared and tiled vertically
    anchor      = ofcolor(I, 5)                                            # cells with colour 5
    rows_set    = { r for r,_ in anchor }                                 # row indices that hold a 5
    rows_cells  = product(rows_set, interval(ZERO, width(I), ONE))          # full‑width cells of those rows
    cleared     = recolor(0, anchor)                                      # erase the 5s
    I0          = paint(I, cleared)                                       # grid with the block cleared
    pattern_o   = asobject(subgrid(rows_cells, I0))                        # cleared rows as an object

    nz          = difference(asindices(I), ofcolor(I, 0))                  # all non‑zero cells in the original
    max_nz_row = valmax(nz, lambda p: p[0])                                 # lowest occupied row
    empty_rows  = subtract(height(I), add(max_nz_row, ONE))                 # rows still empty at the bottom
    repeat_cnt  = divide(empty_rows, size(rows_set))                       # how many full copies fit

    # vertical offsets for the copies (skip the original block)
    offsets = mapply(lambda i: astuple(multiply(add(i, ONE), size(rows_set)), ZERO),
                     interval(ZERO, repeat_cnt, ONE))
    tiled   = merge(mapply(lambda off: shift(pattern_o, off), offsets))

    O = paint(I, tiled)                                                    # overlay the tiled block
    return O
```
training 12997ef3 train nan nan nan nan nan
```python
def dsl1(I):
    # GLOBAL – erase colour 1, compress, down‑scale, repeat rows three times, trim.
    O = trim(vupscale(downscale(switch(compress(I), 1, 0), 2), 3)
    return O
```
training 12eac192 train nan nan nan nan nan
```python
def dsl1(I):
    # GLOBAL – keep colours that appear at least 6 times, everything else → 3
    cols   = palette(I)                                         # all colours present
    keep_c = {c for c in cols if greater(colorcount(I, c), FIVE)}  # frequent colours
    keep   = merge(apply(lambda c: ofcolor(I, c), keep_c)        # their cells
    rest   = difference(asindices(I), keep)                     # all other cells
    return fill(I, THREE, rest)
```
training 13713586 train nan nan nan nan nan
```python
def dsl1(I):
    # RECTANGLE‑FILL: replace each interior object by the rectangle of its bounding box,
    # clipped to stay inside the dominant border colour.
    BG   = mostcommon(I)
    CAN  = canvas(BG, shape(I))
    CLS  = difference(palette(I), initset(BG))
    BC   = argmax(CLS, lambda c: size(ofcolor(I, c)))          # colour of the solid border
    B    = ofcolor(I, BC)                                     # border cells
    OBJ  = objects(I, False, False, True)                     # all coloured objects
    BOBJ = colorfilter(OBJ, BC)                               # border object(s)
    OTH  = difference(OBJ, BOBJ)                             # interior objects
    RCT  = apply(lambda o:
                 recolor(
                     color(o),
                     difference(
                         backdrop(combine(toindices(o), B)),
                         B)),
                 OTH)
    O    = underpaint(CAN, merge(RCT))
    return O
```
training 137eaa0f train nan nan nan nan nan
```python
def dsl1(I):
    # COLOR‑BLOCK‑MAJORITY (non‑zero fallback to 0)
    f = max(divide(height(I), THREE), divide(width(I), THREE))

    block = lambda r, c: crop(I, (multiply(r, f), multiply(c, f)), (f, f)

    cell = lambda r, c: branch(
        equal(size(difference(palette(block(r, c)), initset(ZERO))), ZERO,
        argmax(
            difference(palette(block(r, c)), initset(ZERO)),
            lambda col: colorcount(block(r, c), col)))
    rows = apply(
        lambda r: tuple(apply(lambda c: cell(r, c),
                             interval(ZERO, THREE, ONE)),
        interval(ZERO, THREE, ONE))
    O = tuple(rows)
    return O
```
training 137f0df0 train nan nan nan nan nan
```python
def dsl1(I):
    # GLOBAL – compress the empty border, rotate, work on the rotated view,
    # fill the interior of the least‑frequent colour (the lattice),
    # add the outer‑corner mask, rotate back and merge with the original.
    C   = leastcolor(I)                                 # colour that forms the lattice
    CMP = compress(I)                                   # strip empty outer border
    R90 = rot90(CMP)                                    # turn picture 90° clockwise
    OBJ = ofcolor(R90, C)                               # lattice cells in rotated view
    BBOX   = backdrop(OBJ)                              # bounding box of the lattice
    INSIDE = difference(BBOX, OBJ)                      # cells inside the box but not lattice
    R1 = fill(R90, 2, INSIDE)                          # colour 2 the interior
    ROWS = merge(apply(lambda p: shoot((p[0], 0), RIGHT), OBJ))
    COLS = merge(apply(lambda p: shoot((0, p[1]), DOWN),  OBJ))
    ONE  = intersection(
              difference(R90, ROWS),
              intersection(difference(R90, COLS), backdrop(COLS))
           )                                            # outer‑corner mask
    R2 = fill(R1, 1, ONE)                              # colour 1 the corners
    O_rot = rot270(R2)                                  # undo the rotation
    O = combine(I, O_rot)                               # keep original lattice cells
    return O
```
training 13f06aa5 train nan nan nan nan nan
```python
def dsl1(I):
    # Global – repeat the horizontal pattern of the most frequent colour across the whole grid.
    bg      = mostcolor(I)
    obj     = ofcolor(I, {bg})
    period  = hperiod(obj)                     # smallest horizontal repeat length
    pat     = crop(I, (0, 0), (height(I), period))
    factor  = divide(width(I), period)         # integer scaling factor
    O       = hupscale(pat, factor)
    return O
```
training 1478ab18 train nan nan nan nan nan
```python
def dsl1(I):
    # GLOBAL – build the rectangle with interval/merge instead of backdrop
    five        = ofcolor(I, 5)                                 # cells = {(r,c)...}
    rows        = {r for r, _ in five}
    cols        = {c for _, c in five}
    rmin        = valmin(rows, lambda x: x)                      # topmost row
    rmax        = valmax(rows, lambda x: x)                      # bottommost row
    cmin        = valmin(cols, lambda x: x)                      # leftmost column
    cmax        = valmax(cols, lambda x: x)                      # rightmost column
    all_rows    = interval(rmin, rmax + ONE, ONE)                # all rows inside bbox
    rect_cells  = merge(apply(lambda r: shoot((r, cmin), RIGHT), all_rows)  # full rectangle
    O1          = fill(I, 8, rect_cells)                        # colour rectangle 8
    O           = paint(O1, toobject(five, O1))                  # restore the 5s
    return O
```
training 15696249 train nan nan nan nan nan
```python
def dsl1(I):
    # GLOBAL‑TRANSFORMATION: split rows, pick the middle one, test uniformity,
    # tile the whole input horizontally and place it either at top or centre.
    ROWS   = vsplit(I, THREE)                                    # three 1×3 rows
    MID    = apply(lambda g: g[ONE], ROWS)                        # the middle row
    UNIF   = equality(size(palette(MID)), ONE)                    # all three equal ?
    OFF    = branch(UNIF, (THREE, ZERO), (ZERO, ZERO))           # centre or top
    TILE   = hconcat(hconcat(I, I), I)                             # 3‑times side‑by‑side
    CANV   = canvas(ZERO, (9, 9))
    O      = move(CANV, asobject(TILE), OFF)
    return O
```
training 195ba7dc train nan nan nan nan nan
```python
def dsl1(I):
    # GLOBAL VERTICAL SPLIT – split the grid at the 2‑bar and keep the left half.
    twos   = ofcolor(I, 2)
    cut_w  = leftmost(twos)                                 # column where the bar starts
    left   = first(vsplit(I, cut_w))                        # left sub‑grid obtained by a vertical split
    sev    = ofcolor(left, 7)                               # 7‑pixels inside the left part
    O      = paint(canvas(0, shape(left)), recolor(1, sev))
    return O
```
training 1990f7a8 train nan nan nan nan nan
```python
def dsl1(I):
    # GLOBAL‑VERTICAL‑PERIOD DOWNSCALING
    # Detect the vertical repetition period of the 2‑colored cells,
    # downscale the whole picture by that factor and trim empty borders.
    patch   = ofcolor(I, 2)
    obj     = toobject(patch, I)
    period  = vperiod(obj)                # vertical period of the pattern
    O       = trim(downscale(I, period))
    return O
```
training 1b59e163 train nan nan nan nan nan
```python
def dsl1(I):
    # Global – mirror the left half of the picture onto the right half.
    bg = 4
    L = lefthalf(I)               # left‑hand side sub‑grid
    M = vmirror(L)                # its horizontal mirror (appears on the right side)
    O = fill(I, bg, L)            # erase coloured cells that were on the left
    O = underfill(O, bg, M)       # paste the mirrored pattern on the right
    return O
```
training 1b60fb0c train nan nan nan nan nan
```python
def dsl1(I):
    # GLOBAL‑TRANSFORMATION
    # shift the whole 1‑object two cells left and colour only the interior
    # cells of its bounding box that become covered.
    shape      = ofcolor(I, ONE)
    shifted    = shift(shift(shape, LEFT), LEFT)                 # two‑step left
    interior   = delta(box(shape), shape)                        # bbox minus shape
    target     = intersection(shifted, interior)
    return fill(I, TWO, target)
```
training 1b8318e3 train nan nan nan nan nan
```python
def dsl1(I):
    # RELATIONAL – each non‑5 coloured cell walks straight toward the nearest 5
    # and stops one step away (king‑step distance 1). 5‑cells stay put.
    five      = ofcolor(I, FIVE)                                         # all 5‑cells
    nonzero   = difference(asindices(I), ofcolor(I, ZERO))               # coloured cells
    movers    = difference(nonzero, five)                               # cells that must move

    relocate = lambda idx: recolor(
        index(I, idx),                                                  # original colour
        initset(add(
            idx,
            multiply(
                gravitate(initset(idx), five),                         # unit direction toward 5
                subtract(manhattan(initset(idx), five), ONE)            # steps needed to be adjacent
            )
        ))
    moved = merge(apply(relocate, movers))

    O = canvas(ZERO, shape(I))
    O = cover(O, toobject(five, I))      # keep the original 5‑objects
    O = cover(O, moved)                # paste the displaced cells
    return O
```
training 1bfc4729 train nan nan nan nan nan
```python
def dsl1(I):
    # RELATIONAL + OBJECT‑EXTRACTION
    # – full rows of the original coloured pixels
    # – all border cells coloured by the nearest original pixel (Manhattan,
    #   tie‑break by the smaller colour)
    objs      = objects(I, False, False, True)               # the two single‑pixel objects
    rows      = merge(apply(lambda o: recolor(color(o),
                                      shoot(astuple(uppermost(o), ZERO), RIGHT)),
                     objs)                                 # full rows

    # border = top, bottom, left, right edges of the grid
    top    = shoot(astuple(ZERO, ZERO), RIGHT)
    bot    = shoot(astuple(subtract(height(I), ONE), ZERO), RIGHT)
    left   = shoot(astuple(ZERO, ZERO), DOWN)
    right  = shoot(astuple(ZERO, subtract(width(I), ONE)), DOWN)
    border = union(union(top, bot), union(left, right))

    # colour each border cell by the nearest original pixel
    def nearest(loc):
        dists = {o: manhattan(toobject({loc}, I), o) for o in objs}
        mind  = valmin(dists.values(), lambda x: x)
        cand  = {o for o, d in dists.items() if d == mind}
        col   = valmin({color(o) for o in cand}, lambda x: x)
        return recolor(col, toobject({loc}, I))

    border_col = merge(apply(nearest, asindices(paint(canvas(ZERO, shape(I)), border))))

    O = paint(paint(canvas(ZERO, shape(I)), rows), border_col)
    return O
```
training 1c02dbbe train nan nan nan nan nan
```python
def dsl1(I):
    # COLOR‑LEVEL: draw a filled bounding‑box for every colour that is NOT the most common one
    dom   = mostcolor(I)
    cols  = difference(palette(I), initset(dom))
    rects = mapply(
              lambda c: recolor(
                          c,
                          toindices(
                            shift(
                              asobject(
                                canvas(
                                  ONE,
                                  (add(subtract(lowermost(ofcolor(I, c)),
                                         uppermost(ofcolor(I, c))),
                                      ONE),
                                   add(subtract(rightmost(ofcolor(I, c)),
                                         leftmost(ofcolor(I, c))),
                                      ONE)))),
                              (uppermost(ofcolor(I, c)),
                               leftmost(ofcolor(I, c)))))),
              cols)
    O = paint(I, merge(rects))
    return O
```
training 1c0d0a4b train nan nan nan nan nan
```python
def dsl1(I):
    # relational – a background cell becomes 2 when it has ≥2 orthogonal neighbours of colour 8
    mask8   = ofcolor(I, 8)                                 # all 8‑cells
    zeros   = ofcolor(I, 0)                                 # all 0‑cells
    region  = mfilter(zeros,
                      lambda p: size(intersection(dneighbors(p), mask8)) >= 2)
    temp    = replace(I, 8, 0)                              # erase the 8s
    O       = underpaint(temp, recolor(2, region))           # paint the 2s
    return O
```
training 1c56ad9f train nan nan nan nan nan
```python
def dsl1(I):
    # COLOR‑FILTER – add colour C to interior cells that have at least
    # two orthogonal neighbours already coloured C.
    C        = mostcolor(I)
    frm      = ofcolor(I, C)
    interior = delta(frm)

    core      = intersection(interior, ofcolor(I, C))
    background = difference(interior, core)

    up    = shift(core, UP)
    down  = shift(core, DOWN)
    left  = shift(core, LEFT)
    right = shift(core, RIGHT)

    # cells that appear in at least two of the four neighbour‑sets
    n1 = intersection(up,    left)
    n2 = intersection(up,    right)
    n3 = intersection(down,  left)
    n4 = intersection(down,  right)
    n5 = intersection(up,    down)
    n6 = intersection(left,  right)

    many_neighbors = combine(combine(combine(combine(combine(n1, n2), n3), n4), combine(n5, n6))

    add = intersection(many_neighbors, background)
    O   = fill(I, C, add)
    return O
```
training 1da012fc train nan nan nan nan nan
```python
def dsl1(I):
    # OBJECT‑SIZE ordering → smallest = 2, medium = 4,
    # border of largest = 6, interior of largest = 3
    objs   = objects(I, univalued=True, diagonal=False, without_bg=True)
    tgtcol = branch(colorcount(I, 1) > 0, 1, 8)
    tgts   = colorfilter(objs, tgtcol)

    ordered = order(tgts, size)               # increasing size
    sp_obj  = first(ordered)                  # smallest
    lp_obj  = last(ordered)                   # largest
    mid_objs = difference(difference(tgts,
                                     initset(sp_obj)),
                          initset(lp_obj))

    sp_idx   = toindices(sp_obj)
    mid_idx  = merge(apply(toindices, mid_objs))
    border   = box(lp_obj)                     # outline of the largest object
    interior = difference(lp_obj, border)     # its interior

    O = fill(fill(fill(fill(I, 2, sp_idx), 4, mid_idx), 6, border)
    O = fill(O, 3, interior)
    return O
```
training d10ecb37 train nan nan nan nan nan
```python
def dsl1(I):
    # GLOBAL – count left‑right adjacencies of single cells
    colors   = palette(I)

    left_of = lambda a, b: size(
                intersection(
                    ofcolor(I, a),
                    shift(ofcolor(I, b), LEFT)))

    pairs   = mfilter(product(colors, colors),
                     lambda p: p[0] != p[1])

    max1    = valmax(pairs, lambda p: left_of(p[0], p[1]))
    best1   = extract(pairs,
                     lambda p: left_of(p[0], p[1]) == max1)

    pairs2  = difference(pairs, initset(best1))
    max2    = valmax(pairs2, lambda p: left_of(p[0], p[1]))
    best2   = extract(pairs2,
                     lambda p: left_of(p[0], p[1]) == max2)

    n1 = add(multiply(best1[0], 10), best1[1])
    n2 = add(multiply(best2[0], 10), best2[1])
    return ((n1,), (n2,))
```
