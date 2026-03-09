```python
def dsl1(I):
    # Clone the TWO-shape diagonally upward into the top row of tiles:
    # up-left as 5, up-right as 8
    P2 = ofcolor(I, TWO)
    UL = astuple(subtract(ZERO, FOUR), subtract(ZERO, FOUR))
    UR = astuple(subtract(ZERO, FOUR), FOUR)
    S1 = shift(P2, UL)
    S2 = shift(P2, UR)
    O1 = underfill(I, FIVE, S1)
    O = underfill(O1, EIGHT, S2)
    return O

def dsl2(I):
    # Orthogonal propagation from TWO-shape: left as 8, down as 5 (only onto background)
    P2 = ofcolor(I, TWO)
    L = astuple(ZERO, subtract(ZERO, FOUR))
    D = astuple(FOUR, ZERO)
    SL = shift(P2, L)
    SD = shift(P2, D)
    O1 = underfill(I, EIGHT, SL)
    O = underfill(O1, FIVE, SD)
    return O

def dsl3(I):
    # Propagate TWO-shape to all four diagonal neighboring tiles:
    # UL and DL as 5, UR and DR as 8 (only onto background)
    P2 = ofcolor(I, TWO)
    UL = astuple(subtract(ZERO, FOUR), subtract(ZERO, FOUR))
    UR = astuple(subtract(ZERO, FOUR), FOUR)
    DL = astuple(FOUR, subtract(ZERO, FOUR))
    DR = astuple(FOUR, FOUR)
    SUL = shift(P2, UL)
    SUR = shift(P2, UR)
    SDL = shift(P2, DL)
    SDR = shift(P2, DR)
    O1 = underfill(I, FIVE, SUL)
    O2 = underfill(O1, EIGHT, SUR)
    O3 = underfill(O2, FIVE, SDL)
    O = underfill(O3, EIGHT, SDR)
    return O

def dsl4(I):
    # Mirror TWO-shape across grid midlines: horizontal -> 5, vertical -> 8 (only onto background)
    P2 = ofcolor(I, TWO)
    H = toindices(hmirror(P2))
    V = toindices(vmirror(P2))
    O1 = underfill(I, FIVE, H)
    O = underfill(O1, EIGHT, V)
    return O

def dsl5(I):
    # Orthogonal propagation alternative: up as 5 and right as 8 (only onto background)
    P2 = ofcolor(I, TWO)
    U = astuple(subtract(ZERO, FOUR), ZERO)
    R = astuple(ZERO, FOUR)
    SU = shift(P2, U)
    SR = shift(P2, R)
    O1 = underfill(I, FIVE, SU)
    O = underfill(O1, EIGHT, SR)
    return O
```