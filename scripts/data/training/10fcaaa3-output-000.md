```python
def dsl1(I):
    O = vupscale(hupscale(I, TWO), TWO)
    return O

def dsl2(I):
    O = vconcat(hconcat(I, I), hconcat(I, I))
    return O

def dsl3(I):
    O0 = hconcat(I, I)
    O = replace(O0, ZERO, EIGHT)
    return O

def dsl4(I):
    TL = I
    TR = hmirror(I)
    BL = vmirror(I)
    BR = rot180(I)
    O = vconcat(hconcat(TL, TR), hconcat(BL, BR))
    return O

def dsl5(I):
    h = height(I)
    w = width(I)
    H2 = double(h)
    W2 = double(w)
    dims = astuple(H2, W2)
    base = canvas(ZERO, dims)
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
```