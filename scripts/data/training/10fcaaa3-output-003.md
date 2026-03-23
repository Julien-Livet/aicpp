```python
def dsl1(I):
    T0 = hconcat(I, I)
    T = vconcat(T0, T0)
    Fs = frontiers(T)
    L = merge(Fs)
    O = underfill(T, EIGHT, L)
    return O

def dsl2(I):
    h = height(I)
    w = width(I)
    H2 = double(h)
    W2 = double(w)
    dims = astuple(H2, W2)
    base = canvas(ZERO, dims)
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
    O = replace(G, ZERO, EIGHT)
    return O

def dsl3(I):
    h = height(I)
    w = width(I)
    H2 = double(h)
    W2 = double(w)
    dims = astuple(H2, W2)
    base = canvas(ZERO, dims)
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
    V = shoot(off2, DOWN)
    H = shoot(off3, RIGHT)
    L = combine(V, H)
    O = underfill(G, EIGHT, L)
    return O

def dsl4(I):
    T0 = hconcat(I, I)
    T = vconcat(T0, T0)
    Os = objects(T, T, F, T)
    Cs = mapply(center, Os)
    Ds = insert(DOWN, insert(UP, insert(LEFT, initset(RIGHT))))
    Rays = prapply(shoot, Cs, Ds)
    L = merge(Rays)
    O = underfill(T, EIGHT, L)
    return O

def dsl5(I):
    T0 = hconcat(I, I)
    T = vconcat(T0, T0)
    All = asindices(T)
    Os = objects(T, T, F, T)
    Cs = mapply(center, Os)
    Ks = insert(ulcorner(All), insert(urcorner(All), insert(llcorner(All), initset(lrcorner(All)))))
    Segs = prapply(connect, Cs, Ks)
    L = merge(Segs)
    O = underfill(T, EIGHT, L)
    return O
```