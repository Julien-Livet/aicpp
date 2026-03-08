```python
def dsl1(I):
    # Map -1 slope adjacency to 8, others to 2
    S = ofcolor(I, FIVE)
    A = replace(I, FIVE, TWO)
    S_ur = shift(S, UP_RIGHT)
    S_dl = shift(S, DOWN_LEFT)
    neg_neigh = combine(S_ur, S_dl)
    neg_slope = intersection(S, neg_neigh)
    obj8 = recolor(EIGHT, neg_slope)
    O = paint(A, obj8)
    return O

def dsl2(I):
    # Map +1 slope adjacency to 8, others to 2
    S = ofcolor(I, FIVE)
    A = replace(I, FIVE, TWO)
    S_dr = shift(S, UNITY)
    S_ul = shift(S, NEG_UNITY)
    pos_neigh = combine(S_dr, S_ul)
    pos_slope = intersection(S, pos_neigh)
    obj8 = recolor(EIGHT, pos_slope)
    O = paint(A, obj8)
    return O

def dsl3(I):
    # Map -1 slope adjacency to 2, others to 8
    S = ofcolor(I, FIVE)
    A = replace(I, FIVE, EIGHT)
    S_ur = shift(S, UP_RIGHT)
    S_dl = shift(S, DOWN_LEFT)
    neg_neigh = combine(S_ur, S_dl)
    neg_slope = intersection(S, neg_neigh)
    obj2 = recolor(TWO, neg_slope)
    O = paint(A, obj2)
    return O

def dsl4(I):
    # Map +1 slope adjacency to 2, others to 8
    S = ofcolor(I, FIVE)
    A = replace(I, FIVE, EIGHT)
    S_dr = shift(S, UNITY)
    S_ul = shift(S, NEG_UNITY)
    pos_neigh = combine(S_dr, S_ul)
    pos_slope = intersection(S, pos_neigh)
    obj2 = recolor(TWO, pos_slope)
    O = paint(A, obj2)
    return O

def dsl5(I):
    # Data-driven orientation choice: larger diagonal family -> 8, other -> 2
    S = ofcolor(I, FIVE)
    S_ur = shift(S, UP_RIGHT)
    S_dl = shift(S, DOWN_LEFT)
    S_dr = shift(S, UNITY)
    S_ul = shift(S, NEG_UNITY)
    neg_slope = intersection(S, combine(S_ur, S_dl))
    pos_slope = intersection(S, combine(S_dr, S_ul))
    cond = greater(size(pos_slope), size(neg_slope))
    eight_set = branch(cond, pos_slope, neg_slope)
    A = replace(I, FIVE, TWO)
    obj8 = recolor(EIGHT, eight_set)
    O = paint(A, obj8)
    return O
```