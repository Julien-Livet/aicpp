```python
def dsl1(I):
    # Per-color row spans (single pass): for each color and row, fill between leftmost and rightmost occurrence
    h, w = height(I), width(I)
    O = I
    cols = tuple(c for c in palette(I) if c != ZERO)
    for c in cols:
        for i in range(h):
            js = [j for j in range(w) if index(I, (i, j)) == c]
            if not js:
                continue
            seg = connect((i, min(js)), (i, max(js)))
            O = fill(O, c, seg)
    return O

def dsl2(I):
    # Per-color column spans (single pass): for each color and column, fill between topmost and bottommost occurrence
    h, w = height(I), width(I)
    O = I
    cols = tuple(c for c in palette(I) if c != ZERO)
    for c in cols:
        for j in range(w):
            is_ = [i for i in range(h) if index(I, (i, j)) == c]
            if not is_:
                continue
            seg = connect((min(is_), j), (max(is_), j))
            O = fill(O, c, seg)
    return O

def dsl3(I):
    # Bounding-box fill per connected univalued object
    O = I
    objs = objects(I, True, False, True)
    for obj in objs:
        c = color(obj)
        bbox = backdrop(obj)  # full rectangle covering the object
        O = fill(O, c, bbox)
    return O

def dsl4(I):
    # Bounding rectangle fill per color (across all occurrences of that color)
    O = I
    for c in tuple(x for x in palette(I) if x != ZERO):
        pts = ofcolor(I, c)
        if size(pts) == 0:
            continue
        is_ = [p[0] for p in pts]
        js = [p[1] for p in pts]
        mini, maxi = min(is_), max(is_)
        minj, maxj = min(js), max(js)
        P = initset((mini, minj))
        P = insert((maxi, maxj), P)
        rect = backdrop(P)
        O = fill(O, c, rect)
    return O

def dsl5(I):
    # Replace least common nonzero color with most common nonzero color
    cols = tuple(c for c in palette(I) if c != ZERO)
    if not cols:
        return I
    # compute counts
    counts = {c: colorcount(I, c) for c in cols}
    most = max(cols, key=lambda c: counts[c])
    least = min(cols, key=lambda c: counts[c])
    O = replace(I, least, most)
    return O
```