```python
def dsl1(I):
    M = ofcolor(I, ONE)
    O1 = toobject(M, I)
    UL = ulcorner(O1)
    G = subgrid(O1, I)
    K = vmirror(G)
    Mk = shift(ofcolor(K, ONE), UL)
    Lh = lefthalf(G)
    Lmask = shift(asindices(Lh), UL)
    P = difference(intersection(Mk, Lmask), M)
    O = underpaint(I, recolor(TWO, P))
    return O

def dsl2(I):
    M = ofcolor(I, ONE)
    O1 = toobject(M, I)
    UL = ulcorner(O1)
    S = toindices(O1)
    SN = normalize(S)
    SM = vmirror(SN)
    SA = shift(SM, UL)
    B = backdrop(S)
    LI = intersection(B, shift(B, RIGHT))
    P = difference(intersection(SA, LI), M)
    O = underpaint(I, recolor(TWO, P))
    return O

def dsl3(I):
    M = ofcolor(I, ONE)
    O1 = toobject(M, I)
    UL = ulcorner(O1)
    G = subgrid(O1, I)
    R1 = rot90(G)
    C = cmirror(R1)
    K = rot270(C)
    Mk = shift(ofcolor(K, ONE), UL)
    Lmask = shift(asindices(lefthalf(G)), UL)
    P = difference(intersection(Mk, Lmask), M)
    O = underpaint(I, recolor(TWO, P))
    return O

def dsl4(I):
    M = ofcolor(I, ONE)
    O1 = toobject(M, I)
    UL = ulcorner(O1)
    S = toindices(O1)
    SN = normalize(S)
    R1 = rot90(SN)
    C = cmirror(R1)
    V = rot270(C)
    SA = shift(V, UL)
    B = backdrop(S)
    LI = intersection(B, shift(B, RIGHT))
    P = difference(intersection(SA, LI), M)
    O = underpaint(I, recolor(TWO, P))
    return O

def dsl5(I):
    M = ofcolor(I, ONE)
    O1 = toobject(M, I)
    UL = ulcorner(O1)
    S = toindices(O1)
    SN = normalize(S)
    SM = vmirror(SN)
    SA = shift(SM, UL)
    B = backdrop(S)
    RightCol = difference(B, shift(B, RIGHT))
    Lmask = difference(B, RightCol)
    P = difference(intersection(SA, Lmask), M)
    O = underpaint(I, recolor(TWO, P))
    return O
```