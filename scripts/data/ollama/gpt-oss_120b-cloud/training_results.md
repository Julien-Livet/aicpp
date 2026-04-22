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
training 1cf80156 test 0.0 0.0 0.0 0.0 0.0
```python
def dsl1(I):
    # Global collapse: remove empty outer rows/columns
    O = compress(I)
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
def dsl1(I):
    O = I
    return O
```
training 1478ab18 train 0.0 10.610201530069254 0.609375 0.0 11.219576530069254
```python
def dsl1(I):
    O = I
    return O
```
training 90f3ed37 train 0.0 11.652228585557584 0.30666666666666664 0.027735009803569147 11.98663026202782
```python
def dsl1(I):
    O = I
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
training 195ba7dc train 0.0 13.640812281839786 1.5666666666666667 0.0 15.207478948506452
```python
def dsl5(I):
    # RELATIONAL DIFFERENCE – subtract the right side (including the bar) from the whole set of 7‑pixels.
    twos      = ofcolor(I, 2)
    cut_w     = leftmost(twos)
    # whole set of 7‑pixels
    all_sev   = ofcolor(I, 7)
    # region on the right side (bar + everything to its right)
    right_grid = crop(I, (0, cut_w), (height(I), subtract(width(I), cut_w)))
    right_sev  = ofcolor(right_grid, 7)
    # keep only those 7‑pixels that are not in the right region
    left_sev   = difference(all_sev, right_sev)
    O          = paint(canvas(0, (height(I), cut_w)), recolor(1, left_sev))
    return O
```
training 18419cfa train 0.0 16.47213595499958 0.06534555109922757 0.0 16.537481506098807
```python
def dsl1(I):
    O = I
    return O
```
training 18286ef8 train 0.0 16.970562748477143 0.054027777777777675 0.0 17.02459052625492
```python
def dsl1(I):
    # GLOBAL – direct colour substitution everywhere.
    O = replace(I, 6, 9)
    return O
```
training 11e1fe23 train 0.0 17.602814689998944 0.0636363636363636 0.0 17.66645105363531
```python
def dsl1(I):
    O = I
    return O
```
training 1b60fb0c train 0.0 18.151738036178624 0.28 0.21213203428096425 18.64387007045959
```python
def dsl1(I):
    O = I
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
training 11dc524f train 0.0 19.184603507961064 0.07692307692307687 0.0 19.26152658488414
```python
def dsl3(I):
    # COLOR‑FILTERING – compute the (gap‑1) offset with pure sign arithmetic.
    obj2 = ofcolor(I, 2)
    obj5 = ofcolor(I, 5)

    h_raw = subtract(leftmost(obj5), rightmost(obj2))
    v_raw = subtract(uppermost(obj5), lowermost(obj2))

    h_dir = sign(h_raw)
    v_dir = sign(v_raw)

    h_gap = multiply(h_raw, h_dir)          # |h_raw|
    v_gap = multiply(v_raw, v_dir)          # |v_raw|

    h_step = branch(greater(h_gap, 0), decrement(h_gap), ZERO)
    v_step = branch(greater(v_gap, 0), decrement(v_gap), ZERO)

    shift_vec = astuple(multiply(v_step, v_dir), multiply(h_step, h_dir))

    O = fill(I, 7, combine(obj2, obj5))          # background over both objects
    O = fill(O, 2, shift(obj2, shift_vec))        # moved colour‑2
    O = fill(O, 5, obj5)                         # restore colour‑5
    return O
```
training 0d87d2a6 train 0.0 20.700105363302715 0.6061813186813186 0.0 21.306286681984034
```python
def dsl1(I):
    O = I
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
training 137eaa0f train 0.0 26.050499399249148 2.4444444444444446 0.0 28.49494384369359
```python
def dsl2(I):
    # GLOBAL‑DOWN‑SCALE + ZERO‑FILL
    trimmed = trim(I)
    f = max(divide(height(trimmed), THREE), divide(width(trimmed), THREE))
    raw = downscale(trimmed, f)                                 # 3×3, may contain zeros
    maincol = argmax(
        difference(palette(I), initset(ZERO)),
        lambda c: colorcount(I, c))                             # most common non‑zero colour
    O = replace(raw, ZERO, maincol)                             # fill zeros
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
training 1b59e163 train 0.0 28.881118916422295 0.15740740740740744 0.0 29.0385263238297
```python
def dsl5(I):
    # Relational – treat all coloured cells as a single patch, erase them,
    # then shift the whole patch right by one horizontal period and paint the
    # shifted cells with their original colours.
    bg = 4
    objs   = objects(I, False, False, True)                 # all coloured objects
    patch  = {c for obj in objs for c in obj}               # union of their cells
    p      = hperiod(patch)                                # basic horizontal period
    O      = fill(I, bg, patch)                             # clear original coloured cells
    shifted = shift(patch, (0, p))                          # move them one period to the right
    O      = fill(O, bg, shifted)                           # place the shifted patch
    O      = paint(O, toobject(shifted, I))                # restore the original colours
    return O
```
training 1d61978c train 0.0 31.15549442140351 0.2109375 0.0 31.36643192140351
```python
def dsl1(I):
    O = I
    return O
```
training 137f0df0 train 0.0 34.911415961767126 1.24 0.2724744870428246 36.42389044880995
```python
def dsl1(I):
    O = I
    return O
```
training 1a07d186 train 0.0 36.47817131228487 0.11203007518796992 0.3279849992228211 36.91818638669566
```python
def dsl1(I):
    O = I
    return O
```
training 14754a24 train 0.0 36.90300016727839 0.1566311612364245 0.0 37.05963132851482
```python
def dsl1(I):
    O = I
    return O
```
training 15663ba9 train 0.0 37.831760318526534 0.3358739551047243 0.0 38.167634273631265
```python
def dsl1(I):
    O = I
    return O
```
training 150deff5 train 0.0 38.72042633005687 0.6690656565656565 0.0 39.389491986622524
```python
def dsl1(I):
    O = I
    return O
```
training 12eac192 train 0.0 38.72558815868272 1.017063492063492 0.0 39.74265165074621
```python
def dsl1(I):
    O = I
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
training 15113be4 train 0.0 41.39513950544653 0.056710775047258966 0.0 41.45185028049379
```python
def dsl1(I):
    O = I
    return O
```
training 09c534e7 train 0.0 42.05826595696517 0.2059567901234568 0.0 42.26422274708863
```python
def dsl1(I):
    O = I
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
training 15696249 train 0.0 42.14943835511909 0.8888888888888888 0.5773502689628212 43.615677512970805
```python
def dsl3(I):
    # COLOR‑FILTERING: look at the palette of the middle row,
    # pick any colour present and see if it occurs three times in the whole grid.
    MID    = crop(I, (ONE, ZERO), (ONE, THREE))
    COL    = first(palette(MID))                                 # some colour of the row
    UNIF   = equality(colorcount(I, COL), THREE)                  # appears three times ?
    OFF    = branch(UNIF, (THREE, ZERO), (ZERO, ZERO))
    TILE   = hconcat(hconcat(I, I), I)
    CANV   = canvas(ZERO, (9, 9))
    O      = move(CANV, asobject(TILE), OFF)
    return O
```
training 13f06aa5 train 0.0 44.74143209076087 0.45379342879342877 0.0 45.19522551955429
```python
def dsl1(I):
    O = I
    return O
```
training 0becf7df train 0.0 45.72308974098779 0.57 0.0 46.29308974098779
```python
def dsl1(I):
    O = I
    return O
```
training 14b8e18c train 0.0 48.2842712474619 0.31999999999999995 0.0 48.6042712474619
```python
def dsl1(I):
    O = I
    return O
```
training 1da012fc train 0.0 50.732859278766455 0.2028708133971292 0.0 50.935730092163595
```python
def dsl1(I):
    O = I
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
training 045e512c train 0.0 51.42199198954002 0.20861678004535156 0.6444139582387098 52.27502272782408
```python
def dsl1(I):
    O = I
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
def dsl1(I):
    O = I
    return O
```
training 0962bcdd train 0.0 54.33900150900391 0.33333333333333326 0.11785113016303571 54.79018597250027
```python
def dsl1(I):
    O = I
    return O
```
training 070dd51e train 0.0 54.71991129788118 0.1466666666666666 0.0 54.866577964547844
```python
def dsl1(I):
    O = I
    return O
```
training 1c02dbbe train 0.0 55.526976727089995 0.8222222222222223 0.1276142374614607 56.47681318677368
```python
def dsl1(I):
    O = I
    return O
```
training 0607ce86 train 0.0 57.07697654355131 0.2784721865749533 0.3123947131204499 57.66784344324671
```python
def dsl1(I):
    O = I
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
training 1b8318e3 train 0.0 61.10030564145592 0.2911111111111111 0.07071067810198808 61.462127430669014
```python
def dsl1(I):
    O = I
    return O
```
training 1bfc4729 train 0.0 66.71325041455275 1.0 0.3705501408540922 68.08380055540684
```python
def dsl1(I):
    O = I
    return O
```
training 06df4c85 train 0.0 69.13704857008466 0.18610586011342156 0.0 69.32315443019809
```python
def dsl1(I):
    O = I
    return O
```
training 103eff5b train 0.0 72.70966944691453 0.31993006993007 0.0 73.0295995168446
```python
def dsl1(I):
    O = I
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
training 05269061 train 0.0 80.93413937868704 2.326530612244898 0.4285714283549673 83.6892414192869
```python
def dsl1(I):
    O = I
    return O
```
training 1c56ad9f train 0.0 85.47030230553636 0.43008547008547005 0.138140602982528 86.03852837860437
```python
def dsl4(I):
    # RELATIONAL – generate a regular lattice (spacing 2) inside the
    # interior and unite it with the original coloured cells.
    C        = mostcolor(I)
    frm      = ofcolor(I, C)
    interior = delta(frm)

    ul = ulcorner(interior)
    lr = lrcorner(interior)

    rows = interval(add(ul[0], 2), lr[0] + 1, 2)
    cols = interval(add(ul[1], 2), lr[1] + 1, 2)
    lattice = product(rows, cols)                     # set of (r,c) points

    core = intersection(interior, ofcolor(I, C))
    pattern = intersection(combine(core, lattice), interior)

    O = fill(I, C, pattern)
    return O
```
training 18447a8d train 0.0 84.97320659876738 1.0941999177293296 0.0 86.0674065164967
```python
def dsl1(I):
    O = I
    return O
```
training 12422b43 train 0.0 85.69591093921868 0.8512393162393164 1.0084762804494918 87.55562653590746
```python
def dsl1(I):
    O = I
    return O
```
training 17b80ad2 train 0.0 92.664692303632 0.4639862674388703 0.1809856641470599 93.30966423521792
```python
def dsl1(I):
    O = I
    return O
```
training 1d398264 train 0.0 92.35225542535714 0.5563888888888888 0.9614569143926276 93.87010122863866
```python
def dsl1(I):
    O = I
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
training 009d5c81 train 0.0 107.51831060398987 0.729591836734694 0.740060442872642 108.9879628835972
```python
def dsl1(I):
    O = I
    return O
```
training 1190bc91 train 0.0 106.58896493989263 2.005 0.40784271226413354 109.00180765215676
```python
def dsl1(I):
    O = I
    return O
```
training 0a938d79 train 0.0 113.59451997931947 1.2373537706255098 1.1157453863965838 115.94761913634156
```python
def dsl1(I):
    O = I
    return O
```
training 1c0d0a4b train 0.0 117.7436851552917 1.3213675213675213 0.03589790791800031 119.10095058457725
```python
def dsl1(I):
    O = I
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
training 13713586 train 0.0 155.57454828152072 1.095242214532872 0.0 156.66979049605357
```python
def dsl1(I):
    O = I
    return O
```
training 0f63c0b9 train 0.0 226.687984517288 1.6888888888888887 0.7257928913524146 229.10266629752925
```python
def dsl1(I):
    O = I
    return O
```
training 05a7bcf2 train 0.0 314.7205663211121 0.8222222222222223 0.28284271244128567 315.8256312557756
```python
def dsl1(I):
    O = I
    return O
```
training 12997ef3 train 24.922336414692815 216 94 3.5352443237113573 338.4575807384042
```python
def dsl4(I):
    # GEOMETRIC – mirror vertically, rotate 90°, erase colour 1,
    # then compress, down‑scale, repeat rows three times, trim.
    O = trim(vupscale(downscale(switch(rot90(vmirror(compress(I))), 1, 0), 2), 3))
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
training 1990f7a8 train 18.55638278750559 38 523 0.7084372748646549 580.2648200623702
```python
def dsl4(I):
    # ROTATION‑BASED CROPPING
    # Rotate the whole grid 90° clockwise, then crop tightly around the 2‑cells
    # of the rotated picture and trim the result.
    rot     = rot90(I)                    # rotate clockwise
    patch   = ofcolor(rot, 2)
    sub     = subgrid(patch, rot)         # bounding box in the rotated view
    O       = trim(sub)
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
training d10ecb37 train 24.91246523799996 469 184 1.7679474862916247 679.6804127242917
```python
def dsl1(I):
    O = I
    return O
```
training 0bb8deee train 32.28320249797487 156 651 1.1651349688638812 840.4483374668387
```python
def dsl1(I):
    O = I
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
training 0a1d4ef5 train 115.26483304570058 6458 2724 2.4825571952410286 9299.747390240942
```python
def dsl1(I):
    O = I
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
