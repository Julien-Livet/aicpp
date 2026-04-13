```python
def dsl1(I):
    O = hconcat(I, vmirror(I))
    return O

def dsl2(I):
    c = leastcolor(I)
    L = ofcolor(I, c)
    R = ofcolor(vmirror(I), c)
    Z = canvas(ZERO, shape(I))
    G1 = fill(Z, c, L)
    G2 = fill(Z, c, R)
    O = hconcat(G1, G2)
    return O

def dsl3(I):
    c = leastcolor(I)
    Lobj = recolor(c, ofcolor(I, c))
    Robj = recolor(c, ofcolor(vmirror(I), c))
    Z = canvas(ZERO, shape(I))
    Left = paint(Z, Lobj)
    Right = paint(Z, Robj)
    O = hconcat(Left, Right)
    return O

def dsl4(I):
    f = chain(rot90, hmirror, rot270)
    J = f(I)
    O = hconcat(I, J)
    return O

def dsl5(I):
    h = height(I)
    w = width(I)
    dims = astuple(h, double(w))
    O0 = canvas(ZERO, dims)
    c = leastcolor(I)
    Lobj = recolor(c, ofcolor(I, c))
    O1 = paint(O0, Lobj)
    Ri = ofcolor(vmirror(I), c)
    shiftvec = tojvec(w)
    Rshift = shift(Ri, shiftvec)
    Robj = recolor(c, Rshift)
    O = paint(O1, Robj)
    return O
```