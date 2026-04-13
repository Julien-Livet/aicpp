```python
def dsl1(I):
    top = canvas(ZERO, astuple(halve(height(I)), width(I)))
    bot = bottomhalf(I)
    O = vconcat(top, bot)
    return O

def dsl2(I):
    parts = partition(I)
    border_sel = sfilter(parts, rbind(bordering, I))
    kept = merge(border_sel)
    O = paint(canvas(ZERO, shape(I)), kept)
    return O

def dsl3(I):
    c = leastcolor(I)
    idx = ofcolor(I, c)
    obj = toobject(idx, I)
    O = paint(canvas(ZERO, shape(I)), obj)
    return O

def dsl4(I):
    O = vmirror(I)
    return O

def dsl5(I):
    p1 = ofcolor(I, ONE)
    p2 = ofcolor(I, TWO)
    c1 = centerofmass(p1)
    c2 = centerofmass(p2)
    path = connect(c1, c2)
    wire = recolor(THREE, path)
    t1 = toobject(p1, I)
    t2 = toobject(p2, I)
    t4 = toobject(ofcolor(I, FOUR), I)
    terms = combine(combine(t1, t2), t4)
    allobj = combine(terms, wire)
    O = paint(canvas(ZERO, shape(I)), allobj)
    return O
```