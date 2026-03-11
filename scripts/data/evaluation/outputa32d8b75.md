```python
def dsl1(I):
    h = height(I)
    w = width(I)
    s6 = ofcolor(I, SIX)
    j6 = leftmost(s6)
    start = astuple(ZERO, add(j6, ONE))
    dims = astuple(h, subtract(w, add(j6, ONE)))
    O = crop(I, start, dims)
    return O

def dsl2(I):
    h = height(I)
    w = width(I)
    s6 = ofcolor(I, SIX)
    j6 = leftmost(s6)
    start = astuple(ZERO, add(j6, ONE))
    dims = astuple(h, subtract(w, add(j6, ONE)))
    R = crop(I, start, dims)
    O = hmirror(R)
    return O

def dsl3(I):
    h = height(I)
    w = width(I)
    s6 = ofcolor(I, SIX)
    j6 = leftmost(s6)
    # right-of-6 region we need to fill
    R = crop(I, astuple(ZERO, add(j6, ONE)), astuple(h, subtract(w, add(j6, ONE))))
    # left region as the micro-pattern source (exclude the 6 column)
    L = crop(I, ORIGIN, astuple(h, j6))
    P = palette(L)
    Pnz = remove(SIX, remove(ZERO, P))
    # union of all nonzero, non-six colored indices in L
    U = mapply(lbind(ofcolor, L), Pnz)
    leftobj = toobject(U, L)
    G = subgrid(leftobj, L)
    # scale the micro-pattern up to the size of R
    hr = height(R); wr = width(R)
    hg = height(G); wg = width(G)
    fy = branch(greater(hr, hg), divide(hr, hg), ONE)
    fx = branch(greater(wr, wg), divide(wr, wg), ONE)
    U1 = vupscale(G, fy)
    U2 = hupscale(U1, fx)
    T = crop(U2, ORIGIN, astuple(hr, wr))
    O = T
    return O

def dsl4(I):
    h = height(I)
    w = width(I)
    s6 = ofcolor(I, SIX)
    j6 = leftmost(s6)
    R = crop(I, astuple(ZERO, add(j6, ONE)), astuple(h, subtract(w, add(j6, ONE))))
    L = crop(I, ORIGIN, astuple(h, j6))
    P = palette(L)
    Pnz = remove(SIX, remove(ZERO, P))
    U = mapply(lbind(ofcolor, L), Pnz)
    leftobj = toobject(U, L)
    G = subgrid(leftobj, L)
    # mirror the pattern before scaling
    Gm = hmirror(G)
    hr = height(R); wr = width(R)
    hg = height(Gm); wg = width(Gm)
    fy = branch(greater(hr, hg), divide(hr, hg), ONE)
    fx = branch(greater(wr, wg), divide(wr, wg), ONE)
    U1 = vupscale(Gm, fy)
    U2 = hupscale(U1, fx)
    T = crop(U2, ORIGIN, astuple(hr, wr))
    O = T
    return O

def dsl5(I):
    # Remove the 6-divider by converting it to background, then compress away the left padding,
    # finally crop to the common output width (right-focused hypothesis).
    x = replace(I, SIX, ZERO)
    y = compress(x)
    O = crop(y, ORIGIN, astuple(height(y), TWENTYFOUR))  # 24 columns target
    return O
```