```python
def dsl1(I):
    T0 = hconcat(I, I)
    T = vconcat(T0, T0)
    inds = asindices(T)
    c = center(inds)
    H = hfrontier(c)
    V = vfrontier(c)
    P = combine(H, V)
    O = underfill(T, EIGHT, P)
    return O

def dsl2(I):
    h = height(I)
    w = width(I)
    H2 = double(h)
    W2 = double(w)
    dims = astuple(H2, W2)
    base = canvas(EIGHT, dims)
    obj = asobject(I)
    off1 = ORIGIN
    off2 = tojvec(w)
    off3 = toivec(h)
    off4 = add(off2, off3)
    G1 = move(base, obj, off1)
    G2 = move(G1, obj, off2)
    G3 = move(G2, obj, off3)
    O = move(G3, obj, off4)
    return O

def dsl3(I):
    T0 = hconcat(I, I)
    T = vconcat(T0, T0)
    base8 = replace(T, ZERO, EIGHT)
    L = lefthalf(T)
    ZL = ofcolor(L, ZERO)
    Top = tophalf(T)
    ZT = ofcolor(Top, ZERO)
    P = combine(ZL, ZT)
    O = cover(base8, P)
    return O

def dsl4(I):
    TL = I
    TR = hmirror(I)
    BL = vmirror(I)
    BR = rot180(I)
    T = vconcat(hconcat(TL, TR), hconcat(BL, BR))
    B = box(asindices(T))
    O = underfill(T, EIGHT, B)
    return O

def dsl5(I):
    T0 = hconcat(I, I)
    T = vconcat(T0, T0)
    Fs = frontiers(T)
    U = mapply(toindices, Fs)
    O = underfill(T, EIGHT, U)
    return O
```