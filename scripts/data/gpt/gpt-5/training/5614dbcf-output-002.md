```python
def dsl1(I):
    G = switch(I, FIVE, ZERO)
    O = rot90(downscale(rot270(G), THREE))
    return O

def dsl2(I):
    G = switch(I, FIVE, ZERO)
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
    G = switch(I, FIVE, ZERO)
    H = compress(G)
    O = downscale(H, THREE)
    return O

def dsl4(I):
    G = switch(I, FIVE, ZERO)
    H = hmirror(G)
    D = downscale(H, THREE)
    O = hmirror(D)
    return O

def dsl5(I):
    G = switch(I, FIVE, ZERO)
    VS = vsplit(G, THREE)
    L = first(VS)
    R = last(VS)
    C = first(remove(L, remove(R, VS)))
    HL = hsplit(L, THREE)
    LC = first(HL)
    RC = last(HL)
    CC = first(remove(LC, remove(RC, HL)))
    row1 = hconcat(canvas(mostcolor(LC), UNITY),
                   hconcat(canvas(mostcolor(CC), UNITY), canvas(mostcolor(RC), UNITY)))
    HC = hsplit(C, THREE)
    LC2 = first(HC)
    RC2 = last(HC)
    CC2 = first(remove(LC2, remove(RC2, HC)))
    row2 = hconcat(canvas(mostcolor(LC2), UNITY),
                   hconcat(canvas(mostcolor(CC2), UNITY), canvas(mostcolor(RC2), UNITY)))
    HR = hsplit(R, THREE)
    LC3 = first(HR)
    RC3 = last(HR)
    CC3 = first(remove(LC3, remove(RC3, HR)))
    row3 = hconcat(canvas(mostcolor(LC3), UNITY),
                   hconcat(canvas(mostcolor(CC3), UNITY), canvas(mostcolor(RC3), UNITY)))
    O = vconcat(row1, vconcat(row2, row3))
    return O
```