```python
def dsl1(I):
    J = trim(I)
    W = width(J)
    H = height(J)
    T = ZERO
    M = halve(H)
    B = decrement(H)
    RU = crop(J, toivec(T), astuple(ONE, W))
    RM = crop(J, toivec(M), astuple(ONE, W))
    RB = crop(J, toivec(B), astuple(ONE, W))
    def row_last3(R):
        NZ = difference(asindices(R), ofcolor(R, ZERO))
        NZ1 = combine(NZ, initset(astuple(ZERO, NEG_ONE)))
        J3 = rightmost(NZ1)
        NZ2 = difference(NZ1, initset(astuple(ZERO, J3)))
        J2 = rightmost(NZ2)
        NZ3 = difference(NZ2, initset(astuple(ZERO, J2)))
        J1 = rightmost(NZ3)
        C1 = branch(greater(J1, NEG_ONE), index(R, astuple(ZERO, J1)), ZERO)
        C2 = branch(greater(J2, NEG_ONE), index(R, astuple(ZERO, J2)), ZERO)
        C3 = branch(greater(J3, NEG_ONE), index(R, astuple(ZERO, J3)), ZERO)
        return hconcat(hconcat(canvas(C1, UNITY), canvas(C2, UNITY)), canvas(C3, UNITY))
    O = vconcat(vconcat(row_last3(RU), row_last3(RM)), row_last3(RB))
    return O

def dsl2(I):
    P = palette(I)
    PNZ = remove(ZERO, P)
    UP = chain(uppermost, lbind(ofcolor, I), identity)
    Ctop = argmin(PNZ, UP)
    R1 = remove(Ctop, PNZ)
    Cmid = branch(positive(size(R1)), argmin(R1, UP), Ctop)
    Cbot = argmax(PNZ, UP)
    W = width(I)
    RT = crop(I, toivec(UP(Ctop)), astuple(ONE, W))
    RM = crop(I, toivec(UP(Cmid)), astuple(ONE, W))
    RB = crop(I, toivec(UP(Cbot)), astuple(ONE, W))
    def row_last3(R):
        NZ = difference(asindices(R), ofcolor(R, ZERO))
        NZ1 = combine(NZ, initset(astuple(ZERO, NEG_ONE)))
        J3 = rightmost(NZ1)
        NZ2 = difference(NZ1, initset(astuple(ZERO, J3)))
        J2 = rightmost(NZ2)
        NZ3 = difference(NZ2, initset(astuple(ZERO, J2)))
        J1 = rightmost(NZ3)
        C1 = branch(greater(J1, NEG_ONE), index(R, astuple(ZERO, J1)), ZERO)
        C2 = branch(greater(J2, NEG_ONE), index(R, astuple(ZERO, J2)), ZERO)
        C3 = branch(greater(J3, NEG_ONE), index(R, astuple(ZERO, J3)), ZERO)
        return hconcat(hconcat(canvas(C1, UNITY), canvas(C2, UNITY)), canvas(C3, UNITY))
    O = vconcat(vconcat(row_last3(RT), row_last3(RM)), row_last3(RB))
    return O

def dsl3(I):
    P = palette(I)
    PNZ = remove(ZERO, P)
    UP = chain(uppermost, lbind(ofcolor, I), identity)
    C1 = argmin(PNZ, UP)
    R1 = remove(C1, PNZ)
    C2 = branch(positive(size(R1)), argmin(R1, UP), C1)
    R2 = remove(C2, R1)
    C3 = branch(positive(size(R2)), argmin(R2, UP), C2)
    def row_of(c):
        return hconcat(hconcat(canvas(c, UNITY), canvas(c, UNITY)), canvas(c, UNITY))
    O = vconcat(vconcat(row_of(C1), row_of(C2)), row_of(C3))
    return O

def dsl4(I):
    J = rot90(I)
    W = width(J)
    H = height(J)
    T = ZERO
    M = halve(H)
    B = decrement(H)
    RT = crop(J, toivec(T), astuple(ONE, W))
    RM = crop(J, toivec(M), astuple(ONE, W))
    RB = crop(J, toivec(B), astuple(ONE, W))
    def row_last3(R):
        NZ = difference(asindices(R), ofcolor(R, ZERO))
        NZ1 = combine(NZ, initset(astuple(ZERO, NEG_ONE)))
        J3 = rightmost(NZ1)
        NZ2 = difference(NZ1, initset(astuple(ZERO, J3)))
        J2 = rightmost(NZ2)
        NZ3 = difference(NZ2, initset(astuple(ZERO, J2)))
        J1 = rightmost(NZ3)
        C1 = branch(greater(J1, NEG_ONE), index(R, astuple(ZERO, J1)), ZERO)
        C2 = branch(greater(J2, NEG_ONE), index(R, astuple(ZERO, J2)), ZERO)
        C3 = branch(greater(J3, NEG_ONE), index(R, astuple(ZERO, J3)), ZERO)
        return hconcat(hconcat(canvas(C1, UNITY), canvas(C2, UNITY)), canvas(C3, UNITY))
    O = vconcat(vconcat(row_last3(RT), row_last3(RM)), row_last3(RB))
    return O

def dsl5(I):
    NZ = difference(asindices(I), ofcolor(I, ZERO))
    JL = leftmost(NZ)
    JR = rightmost(NZ)
    JM = divide(add(JL, JR), TWO)
    H = height(I)
    CL = crop(I, astuple(ZERO, JL), astuple(H, ONE))
    CM = crop(I, astuple(ZERO, JM), astuple(H, ONE))
    CR = crop(I, astuple(ZERO, JR), astuple(H, ONE))
    RL = rot90(CL)
    RM = rot90(CM)
    RR = rot90(CR)
    def row_last3(R):
        NZr = difference(asindices(R), ofcolor(R, ZERO))
        NZ1 = combine(NZr, initset(astuple(ZERO, NEG_ONE)))
        J3 = rightmost(NZ1)
        NZ2 = difference(NZ1, initset(astuple(ZERO, J3)))
        J2 = rightmost(NZ2)
        NZ3 = difference(NZ2, initset(astuple(ZERO, J2)))
        J1 = rightmost(NZ3)
        C1 = branch(greater(J1, NEG_ONE), index(R, astuple(ZERO, J1)), ZERO)
        C2 = branch(greater(J2, NEG_ONE), index(R, astuple(ZERO, J2)), ZERO)
        C3 = branch(greater(J3, NEG_ONE), index(R, astuple(ZERO, J3)), ZERO)
        return hconcat(hconcat(canvas(C1, UNITY), canvas(C2, UNITY)), canvas(C3, UNITY))
    O = vconcat(vconcat(row_last3(RL), row_last3(RM)), row_last3(RR))
    return O
```