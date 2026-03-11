```python
def dsl1(I):
    # For each nonzero color, draw the border of its bounding box and stack centered
    H, W = shape(I)
    O = canvas(ZERO, (H, W))
    cols = sorted([c for c in palette(I) if c != ZERO])
    r = 0
    for c in cols:
        patch = ofcolor(I, c)
        if size(patch) == 0:
            continue
        bbox = backdrop(patch)  # full bounding box indices
        outline = box(bbox)     # border of the bounding box
        noutline = normalize(outline)
        h = height(noutline)
        w = width(noutline)
        if h <= 0 or w <= 0 or r + h > H:
            continue
        cc = (W - w) // 2
        obj = recolor(c, noutline)
        O = paint(O, shift(obj, (r, cc)))
        r += h + 1
    return O

def dsl2(I):
    # Compress each quadrant and stack the four compressed quadrants vertically, centered horizontally
    H, W = shape(I)
    O = canvas(ZERO, (H, W))
    h1, h2 = divide(H, TWO), H - divide(H, TWO)
    w1, w2 = divide(W, TWO), W - divide(W, TWO)
    quads = [
        crop(I, (0, 0), (divide(H, TWO), divide(W, TWO))),
        crop(I, (0, divide(W, TWO)), (divide(H, TWO), W - divide(W, TWO))),
        crop(I, (divide(H, TWO), 0), (H - divide(H, TWO), divide(W, TWO))),
        crop(I, (divide(H, TWO), divide(W, TWO)), (H - divide(H, TWO), W - divide(W, TWO))),
    ]
    r = 0
    for g in quads:
        cg = compress(g)
        h, w = shape(cg)
        if h == 0 or w == 0 or r + h > H:
            continue
        cc = (W - w) // 2
        for c in sorted([x for x in palette(cg) if x != ZERO]):
            patch = ofcolor(cg, c)
            if size(patch) == 0:
                continue
            obj = toobject(patch, cg)
            O = paint(O, shift(obj, (r, cc)))
        r += h + 1
    return O

def dsl3(I):
    # Catalog: for each nonzero color, draw a 4x5 hollow rectangle tile stacked, centered horizontally
    H, W = shape(I)
    O = canvas(ZERO, (H, W))
    cols = sorted([c for c in palette(I) if c != ZERO])
    hrect, wrect = 4, 5
    r = 0
    for c in cols:
        if r + hrect > H:
            break
        idxs = set()
        for i in range(hrect):
            for j in range(wrect):
                if i == 0 or i == hrect - 1 or j == 0 or j == wrect - 1:
                    idxs.add((i, j))
        tile = frozenset(idxs)
        cc = (W - wrect) // 2
        obj = recolor(c, tile)
        O = paint(O, shift(obj, (r, cc)))
        r += hrect + 1
    return O

def dsl4(I):
    # Center the compressed entire input within the original canvas
    H, W = shape(I)
    O = canvas(ZERO, (H, W))
    C = compress(I)
    h, w = shape(C)
    if h == 0 or w == 0:
        return O
    r0 = (H - h) // 2
    c0 = (W - w) // 2
    for c in [x for x in palette(C) if x != ZERO]:
        patch = ofcolor(C, c)
        if size(patch) == 0:
            continue
        obj = toobject(patch, C)
        O = paint(O, shift(obj, (r0, c0)))
    return O

def dsl5(I):
    # Pull all objects horizontally to the central column while preserving their rows
    H, W = shape(I)
    O = canvas(ZERO, (H, W))
    tcol = W // 2
    for o in fgpartition(I):
        com_r, com_c = centerofmass(toindices(o))
        dc = tcol - com_c
        O = paint(O, shift(o, (0, dc)))
    return O
```