```python
def dsl1(I):
    T0 = hconcat(I, I)
    T = vconcat(T0, T0)
    h = height(I)
    w = width(I)
    H = hfrontier(toivec(h))
    V = vfrontier(tojvec(w))
    L = combine(H, V)
    O = underfill(T, EIGHT, L)
    return O

def dsl2(I):
    h = height(I)
    w = width(I)
    H2 = double(h)
    W2 = double(w)
    base = canvas(ZERO, astuple(H2, W2))
    Os = objects(I, T, F, T)
    MO = merge(Os)
    off1 = ORIGIN
    off2 = tojvec(w)
    off3 = toivec(h)
    off4 = add(off2, off3)
    G1 = move(base, MO, off1)
    G2 = move(G1, MO, off2)
    G3 = move(G2, MO, off3)
    G = move(G3, MO, off4)
    Hc = hfrontier(off3)
    Vc = vfrontier(off2)
    L = combine(Hc, Vc)
    O = underfill(G, EIGHT, L)
    return O

def dsl3(I):
    T0 = hconcat(I, I)
    T = vconcat(T0, T0)
    Os = objects(T, T, F, T)
    Bs = mapply(box, Os)
    L = merge(Bs)
    O = underfill(T, EIGHT, L)
    return O

def dsl4(I):
    T0 = hconcat(I, I)
    T = vconcat(T0, T0)
    h = height(I)
    w = width(I)
    c = add(toivec(h), tojvec(w))
    All = asindices(T)
    Ks = corners(All)
    Segs = prapply(connect, Ks, initset(c))
    L = merge(Segs)
    O = underfill(T, EIGHT, L)
    return O

def dsl5(I):
    T0 = hconcat(I, I)
    T = vconcat(T0, T0)
    Fs = frontiers(T)
    Hs = sfilter(Fs, hline)
    Vs = sfilter(Fs, vline)
    Lh = merge(Hs)
    Lv = merge(Vs)
    L = combine(Lh, Lv)
    O = underfill(T, EIGHT, L)
    return O
```