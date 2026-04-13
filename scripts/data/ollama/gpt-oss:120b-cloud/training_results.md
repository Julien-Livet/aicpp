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
training 017c7c7b train 0.0 2.8284271247461903 0.07407407407407407 0.0 2.9025011988202642
```python
def dsl1(I):
    # Global transformation: recolour 1→2, take the upper half and append it below.
    G   = switch(I, ONE, TWO)                     # 1 → 2
    top, _ = vsplit(G, TWO)                       # upper half
    O   = vconcat(G, top)                         # original + upper half
    return O
```
training 0b17323b train 0.0 6.0 0.022222222222222254 0.3999999999057191 6.4222222221279415
```python
def dsl1(I):
    # OBJECT‑EXTRACTION – build the missing diagonal with a ray (shoot) instead of connect
    ones       = ofcolor(I, 1)
    last_one   = astuple(lowermost(ones), rightmost(ones))
    # whole main diagonal from (0,0) to bottom‑right
    full_diag  = shoot(astuple(0, 0), astuple(1, 1))
    # diagonal up to and including the last 1
    part_up_to = shoot(astuple(0, 0), last_one)
    # cells that have to become 2
    mask       = difference(full_diag, part_up_to)
    O          = fill(I, 2, mask)
    return O
```
training 0520fde7 train 0.0 8.292528739883945 0.6666666666666667 1.4676472830281688 10.42684268957878
```python
def dsl3(I):
    # Color‑filter + centre placement:
    # find the centre of mass of all 1‑cells, create a 3×3 canvas and place a single 2 there
    cm     = centerofmass(ofcolor(I, 1))       # centre of mass of color‑1 cells
    base   = canvas(0, (3, 3))                # empty 3×3 grid
    patch  = initset(cm)                       # turn the centre coordinate into a patch
    O      = fill(base, 2, patch)              # paint a 2 at the centre location
    return O
```
training 1478ab18 train 0.0 10.610201530069254 0.609375 0.0 11.219576530069254
```python
def dsl1(I):
    O = I
    return O
```
training 1a244afd train 0.0 12.086776687980937 0.16937500000000005 0.0 12.256151687980937
```python
def dsl1(I):
    O = I
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
training 11852cab train 0.0 15.588457268119894 0.09000000000000008 0.0 15.678457268119896
```python
def dsl1(I):
    O = I
    return O
```
training 18419cfa train 0.0 16.47213595499958 0.06534555109922757 0.0 16.537481506098807
```python
def dsl1(I):
    O = I
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
training 18286ef8 train 0.0 19.209372712298546 0.08104166666666668 0.0 19.29041437896521
```python
def dsl1(I):
    O = I
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
    # Global right‑shift: treat every coloured cell (including all colours) as one patch,
    # shift it one step to the right and paint the result on an empty canvas.
    empty   = canvas(0, shape(I))                     # all‑zero background of same size
    shifted = shift(asobject(I), RIGHT)                # shift whole coloured patch right
    O       = paint(empty, shifted)                    # paint shifted cells onto background
    return O
```
training 05f2a901 train 0.0 24.357756514513238 0.47705627705627696 0.39264757134482997 25.227460362914346
```python
def dsl1(I):
    O = I
    return O
```
training 08ed6ac7 train 0.0 29.40873222920515 0.5555555555555556 0.0 29.964287784760707
```python
def dsl1(I):
    O = I
    return O
```
training 1d61978c train 0.0 31.15549442140351 0.2109375 0.0 31.36643192140351
```python
def dsl1(I):
    O = I
    return O
```
training 1caeab9d train 0.0 30.760760615165587 0.48 0.3032678015843035 31.54402841674989
```python
def dsl1(I):
    O = I
    return O
```
training 1acc24af train 0.0 35.61895003862225 0.2569444444444444 0.0 35.875894483066695
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
training 17829a00 train 0.0 36.330637871500485 0.390625 0.0 36.721262871500485
```python
def dsl1(I):
    O = I
    return O
```
training 182e5d0f train 0.0 36.50408594145745 0.2883382642998028 0.0 36.79242420575725
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
training 1b59e163 train 0.0 37.223906643972136 0.2685185185185186 0.0 37.492425162490655
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
training 178fcbfb train 0.0 38.15525173386875 0.9909231200897868 0.32336080319443794 39.469535657152974
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
training 15113be4 train 0.0 41.39513950544653 0.056710775047258966 0.0 41.45185028049379
```python
def dsl1(I):
    O = I
    return O
```
training 11dc524f train 0.0 41.41421529368845 0.16568047337278102 0.0 41.57989576706123
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
training 045e512c train 0.0 51.42199198954002 0.20861678004535156 0.6444139582387098 52.27502272782408
```python
def dsl1(I):
    O = I
    return O
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
training 0ca9ddb6 train 0.0 55.05253949517696 0.3950617283950617 0.21465018353547038 55.66225140710749
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
training 1b8318e3 train 0.0 61.10030564145592 0.2911111111111111 0.07071067810198808 61.462127430669014
```python
def dsl1(I):
    O = I
    return O
```
training 17b866bd train 0.0 61.54066802494782 0.22972470238095233 0.0 61.77039272732877
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
training 05269061 train 0.0 66.17963783826141 1.959183673469388 0.0 68.1388215117308
```python
def dsl1(I):
    # OBJECT‑CENTRIC → fill each column according to its (col % 3) residue.
    objs = objects(I, univalued=True, diagonal=False, without_bg=True)

    # order the three single‑colour objects by centre‑of‑mass (gives residues 0,1,2)
    sum_of = lambda o: add(centerofmass(o)[0], centerofmass(o)[1])
    o0 = argmin(objs, sum_of)
    o1 = argmin(difference(objs, {o0}), sum_of)
    o2 = argmin(difference(objs, {o0, o1}), sum_of)

    c0 = color(o0); c1 = color(o1); c2 = color(o2)

    # a full‑height column of a given colour
    col_obj = lambda col, colc: recolor(colc,
                     toobject(apply(lambda r: (r, col), interval(0, height(I), 1)), I))

    obj0 = merge(apply(lambda c: col_obj(c, c0), interval(0, width(I), 3)))
    obj1 = merge(apply(lambda c: col_obj(c, c1), interval(1, width(I), 3)))
    obj2 = merge(apply(lambda c: col_obj(c, c2), interval(2, width(I), 3)))

    empty = canvas(0, shape(I))
    G0 = paint(empty, obj0)
    G1 = paint(G0,    obj1)
    O  = paint(G1,    obj2)
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
training 1d0a4b61 train 0.0 74.00842223237059 0.3408000000000001 0.0 74.3492222323706
```python
def dsl1(I):
    O = I
    return O
```
training 0e206a2e train 0.0 78.9029386942249 0.26001984126984123 0.4673445197186872 79.63030305521342
```python
def dsl1(I):
    O = I
    return O
```
training 03560426 train 0.0 78.37817225368099 1.1400000000000001 0.8369391191074397 80.35511137278844
```python
def dsl1(I):
    O = I
    return O
```
training 18447a8d train 0.0 84.97320659876738 1.0941999177293296 0.0 86.0674065164967
```python
def dsl1(I):
    O = I
    return O
```
training 1c56ad9f train 0.0 88.87615686537718 0.4121611721611721 0.138140602982528 89.42645864052088
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
training 0e671a1a train 0.0 93.19541459439118 0.5147928994082841 0.0 93.71020749379946
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
training 17cae0c1 train 0.0 90.75298207082034 4.0 0.10540925528339042 94.85839132610373
```python
def dsl1(I):
    O = I
    return O
```
training 00dbd492 train 0.0 102.8811770259009 0.8977996037336696 0.0 103.77897662963458
```python
def dsl1(I):
    O = I
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
training 184a9768 train 0.0 123.21839785539751 0.4462577639751554 0.395295846938856 124.05995146631153
```python
def dsl1(I):
    O = I
    return O
```
training 09629e4f train 0.0 128.72990749418273 1.8760330578512396 0.0 130.60594055203399
```python
def dsl1(I):
    O = I
    return O
```
training 13713586 train 0.0 155.57454828152072 1.095242214532872 0.0 156.66979049605357
```python
def dsl1(I):
    O = I
    return O
```
training 140c817e train 0.0 160.49090666944778 1.6794597097627402 0.0 162.17036637921052
```python
def dsl1(I):
    O = I
    return O
```
training 0a2355a6 train 0.0 172.0626319883776 1.3210162853019995 0.0 173.3836482736796
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
training 137eaa0f train 33.941125496954285 35 390 1.3355546119994286 460.27668010895377
```python
def dsl1(I):
    O = I
    return O
```
training 0692e18c train 25.45584412271571 259 270 1.4999999991161166 555.9558441218319
```python
def dsl1(I):
    O = I
    return O
```
training 0c9aba6e train 28.0 240 304 1.3886900653656893 573.3886900653657
```python
def dsl1(I):
    O = I
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
training 15696249 train 33.94112549695428 238 360 1.4936728727918855 633.4347983697462
```python
def dsl1(I):
    O = I
    return O
```
training 12997ef3 train 34.136789494449125 157 574 0.8217678785160549 765.9585573729651
```python
def dsl1(I):
    O = I
    return O
```
training 0c786b71 train 15.0 579 180 0.9999999993333333 774.9999999993333
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
training 10fcaaa3 train 20.959942099337262 625 255 1.6047995507220398 902.5647416500592
```python
def dsl1(I):
    O = I
    return O
```
training 1b2d62fb train 20.0 637 250 1.7154391490706367 908.7154391490706
```python
def dsl1(I):
    O = I
    return O
```
training 007bbfb7 train 42.426406871192846 490 450 2.530330084398899 984.9567369555919
```python
def dsl1(I):
    O = I
    return O
```
training 195ba7dc train 28.0 793 380 1.304090011323967 1202.304090011324
```python
def dsl1(I):
    O = I
    return O
```
training 1990f7a8 train 51.70154039685654 0 1271 0.9757439792570779 1323.6772843761137
```python
def dsl1(I):
    O = I
    return O
```
training 1a2e2828 train 57.681284781066644 1030 462 3.8180703911748726 1553.4993551722416
```python
def dsl1(I):
    O = I
    return O
```
training 1be83260 train 15.65685424949238 455 1102 0.13296270778504948 1572.7898169572775
```python
def dsl1(I):
    O = I
    return O
```
training 0b148d64 train 45.28848668074106 1507 1323 1.1611445015768556 2876.4496311823177
```python
def dsl1(I):
    O = I
    return O
```
training 19bb5feb train 54.57344845505498 2229 671 1.6842890822117285 2956.257737537267
```python
def dsl1(I):
    O = I
    return O
```
training 1a6449f1 train 56.78578653171118 2175 1334 1.5218030985822721 3567.3075896302935
```python
def dsl1(I):
    O = I
    return O
```
training 1c786137 train 48.70686666029874 2717 1140 1.4258348580242277 3907.1327015183233
```python
def dsl1(I):
    O = I
    return O
```
training 1190e5a7 train 59.4847935962098 2862 1119 1.9598723860929503 4042.4446659823025
```python
def dsl1(I):
    O = I
    return O
```
training 15660dd6 train 30.26665112032805 2863 1246 0.587354261239019 4139.854005381568
```python
def dsl1(I):
    O = I
    return O
```
training 0a1d4ef5 train 115.26483304570058 6458 2724 2.4825571952410286 9299.747390240942
```python
def dsl1(I):
    O = I
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
