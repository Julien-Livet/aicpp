```python
def dsl1(I):
    G = replace(I, FIVE, ZERO)
    O = downscale(G, THREE)
    return O

def dsl2(I):
    G = replace(I, FIVE, ZERO)
    HS = hsplit(G, THREE)
    T = first(HS)
    B = last(HS)
    M = first(remove(T, remove(B, HS)))
    VT = vsplit(T, THREE)
    LT = first(VT)
    RT = last(VT)
    CT = first(remove(LT, remove(RT, VT)))
    r1 = hconcat(canvas(mostcolor(LT), UNITY),
                 hconcat(canvas(mostcolor(CT), UNITY), canvas(mostcolor(RT), UNITY)))
    VM = vsplit(M, THREE)
    LM = first(VM)
    RM = last(VM)
    CM = first(remove(LM, remove(RM, VM)))
    r2 = hconcat(canvas(mostcolor(LM), UNITY),
                 hconcat(canvas(mostcolor(CM), UNITY), canvas(mostcolor(RM), UNITY)))
    VB = vsplit(B, THREE)
    LB = first(VB)
    RB = last(VB)
    CB = first(remove(LB, remove(RB, VB)))
    r3 = hconcat(canvas(mostcolor(LB), UNITY),
                 hconcat(canvas(mostcolor(CB), UNITY), canvas(mostcolor(RB), UNITY)))
    O = vconcat(r1, vconcat(r2, r3))
    return O

def dsl3(I):
    G = replace(I, FIVE, ZERO)
    VS = vsplit(G, THREE)
    L = first(VS)
    R = last(VS)
    C = first(remove(L, remove(R, VS)))
    DL = downscale(L, THREE)
    DC = downscale(C, THREE)
    DR = downscale(R, THREE)
    O = hconcat(DL, hconcat(DC, DR))
    return O

def dsl4(I):
    G = replace(I, FIVE, ZERO)
    H = hmirror(G)
    D = downscale(H, THREE)
    O = hmirror(D)
    return O

def dsl5(I):
    A = downscale(switch(I, FIVE, ZERO), THREE)
    B = downscale(replace(I, FIVE, ZERO), THREE)
    O = cellwise(A, B, ZERO)
    return O
```