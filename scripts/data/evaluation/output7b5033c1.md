```python
def dsl1(I):
    # Group by color, order colors by their topmost occurrence, stack blocks with height equal to pixel count
    bg = mostcolor(I)
    cols = [c for c in totuple(palette(I)) if c != bg]
    items = []
    for c in cols:
        r = uppermost(ofcolor(I, c))
        items.append((r, c))
    items.sort(key=lambda t: t[0])
    O = None
    for _, c in items:
        h = colorcount(I, c)
        block = canvas(c, astuple(h, ONE))
        O = block if O is None else vconcat(O, block)
    return O

def dsl2(I):
    # Order foreground objects by topmost row; merge consecutive objects of the same color and sum sizes
    objs = order(fgpartition(I), uppermost)
    O = None
    prevc = None
    acc = 0
    for o in objs:
        c = color(o)
        if prevc is None:
            prevc = c
            acc = size(o)
        elif c == prevc:
            acc += size(o)
        else:
            block = canvas(prevc, astuple(acc, ONE))
            O = block if O is None else vconcat(O, block)
            prevc = c
            acc = size(o)
    if prevc is not None:
        block = canvas(prevc, astuple(acc, ONE))
        O = block if O is None else vconcat(O, block)
    return O

def dsl3(I):
    # Aggregate all components per color; sort colors by minimal topmost among their components; height = total pixels per color
    objs = objects(I, T, F, T)
    agg = {}
    for o in objs:
        c = color(o)
        r = uppermost(o)
        cnt = size(o)
        if c not in agg:
            agg[c] = {'r': r, 'cnt': cnt}
        else:
            agg[c]['r'] = min(agg[c]['r'], r)
            agg[c]['cnt'] += cnt
    items = [(v['r'], c, v['cnt']) for c, v in agg.items()]
    items.sort(key=lambda t: t[0])
    O = None
    for _, c, cnt in items:
        block = canvas(c, astuple(cnt, ONE))
        O = block if O is None else vconcat(O, block)
    return O

def dsl4(I):
    # Row-major scan of non-background cells; output contiguous runs (in scan order) as stacked blocks
    h = height(I)
    w = width(I)
    bg = mostcolor(I)
    O = None
    curr = None
    run = 0
    for i in range(h):
        for j in range(w):
            c = index(I, astuple(i, j))
            if c == bg:
                continue
            if curr is None:
                curr = c
                run = 1
            elif c == curr:
                run += 1
            else:
                block = canvas(curr, astuple(run, ONE))
                O = block if O is None else vconcat(O, block)
                curr = c
                run = 1
    if curr is not None and run > 0:
        block = canvas(curr, astuple(run, ONE))
        O = block if O is None else vconcat(O, block)
    return O

def dsl5(I):
    # Group by color; order by the row of the color's center of mass; height = total pixels per color
    bg = mostcolor(I)
    cols = [c for c in totuple(palette(I)) if c != bg]
    items = []
    for c in cols:
        patch = ofcolor(I, c)
        obj = toobject(patch, I)
        r = centerofmass(obj)[0]
        cnt = size(patch)
        items.append((r, c, cnt))
    items.sort(key=lambda t: t[0])
    O = None
    for _, c, cnt in items:
        block = canvas(c, astuple(cnt, ONE))
        O = block if O is None else vconcat(O, block)
    return O
```