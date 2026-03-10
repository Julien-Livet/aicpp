```python
def dsl1(I):
    objs = objects(I, T, F, T)
    ones = colorfilter(objs, ONE)
    twos = colorfilter(objs, TWO)
    o1 = first(ones)
    o2 = first(twos)
    s1 = ulcorner(o1)
    s2 = lrcorner(o2)
    r = asindices(I)
    l1 = intersection(shoot(s1, NEG_UNITY), r)
    l2 = intersection(shoot(s2, UNITY), r)
    x = fill(I, ONE, l1)
    O = fill(x, TWO, l2)
    return O

def dsl2(I):
    objs = objects(I, T, F, T)
    o1 = first(colorfilter(objs, ONE))
    o2 = first(colorfilter(objs, TWO))
    s1 = ulcorner(o1)
    s2 = lrcorner(o2)
    idx = asindices(I)
    p1 = intersection(shoot(s1, NEG_UNITY), idx)
    p2 = intersection(shoot(s2, UNITY), idx)
    obj1 = recolor(ONE, p1)
    obj2 = recolor(TWO, p2)
    O = paint(I, combine(obj1, obj2))
    return O

def dsl3(I):
    objs = objects(I, T, F, T)
    a = first(colorfilter(objs, ONE))
    b = first(colorfilter(objs, TWO))
    u = ulcorner(a)
    v = lrcorner(b)
    allidx = asindices(I)
    d1 = intersection(shoot(u, NEG_UNITY), allidx)
    d2 = intersection(shoot(v, UNITY), allidx)
    y = fill(I, ONE, d1)
    O = fill(y, TWO, d2)
    return O

def dsl4(I):
    oset = objects(I, T, F, T)
    a1 = first(colorfilter(oset, ONE))
    a2 = first(colorfilter(oset, TWO))
    p_up = intersection(shoot(ulcorner(a1), NEG_UNITY), asindices(I))
    p_dn = intersection(shoot(lrcorner(a2), UNITY), asindices(I))
    O = underpaint(fill(I, ONE, p_up), recolor(TWO, p_dn))
    return O

def dsl5(I):
    obs = objects(I, T, F, T)
    oneobj = first(colorfilter(obs, ONE))
    twoobj = first(colorfilter(obs, TWO))
    line_one = intersection(shoot(ulcorner(oneobj), NEG_UNITY), asindices(I))
    line_two = intersection(shoot(lrcorner(twoobj), UNITY), asindices(I))
    tmp = fill(I, ONE, line_one)
    O = fill(tmp, TWO, line_two)
    return O
```