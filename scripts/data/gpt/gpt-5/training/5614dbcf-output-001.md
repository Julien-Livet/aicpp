```python
def dsl1(I):
    O = downscale(switch(I, FIVE, ZERO), THREE)
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
    r1 = hconcat(canvas(mostcolor(LT), UNITY), hconcat(canvas(mostcolor(CT), UNITY), canvas(mostcolor(RT), UNITY)))
    VM = vsplit(M, THREE)
    LM = first(VM)
    RM = last(VM)
    CM = first(remove(LM, remove(RM, VM)))
    r2 = hconcat(canvas(mostcolor(LM), UNITY), hconcat(canvas(mostcolor(CM), UNITY), canvas(mostcolor(RM), UNITY)))
    VB = vsplit(B, THREE)
    LB = first(VB)
    RB = last(VB)
    CB = first(remove(LB, remove(RB, VB)))
    r3 = hconcat(canvas(mostcolor(LB), UNITY), hconcat(canvas(mostcolor(CB), UNITY), canvas(mostcolor(RB), UNITY)))
    O = vconcat(r1, vconcat(r2, r3))
    return O

def dsl3(I):
    HS = hsplit(I, THREE)
    T = first(HS)
    B = last(HS)
    M = first(remove(T, remove(B, HS)))
    VT = vsplit(T, THREE)
    LT = first(VT)
    RT = last(VT)
    CT = first(remove(LT, remove(RT, VT)))
    r1 = hconcat(canvas(mostcolor(replace(LT, leastcolor(LT), ZERO)), UNITY),
                 hconcat(canvas(mostcolor(replace(CT, leastcolor(CT), ZERO)), UNITY),
                         canvas(mostcolor(replace(RT, leastcolor(RT), ZERO)), UNITY)))
    VM = vsplit(M, THREE)
    LM = first(VM)
    RM = last(VM)
    CM = first(remove(LM, remove(RM, VM)))
    r2 = hconcat(canvas(mostcolor(replace(LM, leastcolor(LM), ZERO)), UNITY),
                 hconcat(canvas(mostcolor(replace(CM, leastcolor(CM), ZERO)), UNITY),
                         canvas(mostcolor(replace(RM, leastcolor(RM), ZERO)), UNITY)))
    VB = vsplit(B, THREE)
    LB = first(VB)
    RB = last(VB)
    CB = first(remove(LB, remove(RB, VB)))
    r3 = hconcat(canvas(mostcolor(replace(LB, leastcolor(LB), ZERO)), UNITY),
                 hconcat(canvas(mostcolor(replace(CB, leastcolor(CB), ZERO)), UNITY),
                         canvas(mostcolor(replace(RB, leastcolor(RB), ZERO)), UNITY)))
    O = vconcat(r1, vconcat(r2, r3))
    return O

def dsl4(I):
    G = switch(I, leastcolor(I), ZERO)
    O = downscale(G, THREE)
    return O

def dsl5(I):
    O = switch(downscale(I, THREE), FIVE, ZERO)
    return O
```