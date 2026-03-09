```python
def dsl1(I):
    O = I
    A = asindices(I)
    p8 = ofcolor(I, EIGHT)
    p2 = ofcolor(I, TWO)
    u1 = UP
    u2 = add(UP, UP)
    u3 = add(u2, UP)
    u4 = add(u3, UP)
    # 8-columns: fill ones then top 8
    s81 = intersection(A, shift(p8, u1))
    s82 = intersection(A, shift(p8, u2))
    s83 = intersection(A, shift(p8, u3))
    O = fill(O, ONE, s81)
    O = fill(O, ONE, s82)
    O = fill(O, EIGHT, s83)
    # 2-columns: fill ones then top 2
    s21 = intersection(A, shift(p2, u1))
    s22 = intersection(A, shift(p2, u2))
    s23 = intersection(A, shift(p2, u3))
    s24 = intersection(A, shift(p2, u4))
    O = fill(O, ONE, s21)
    O = fill(O, ONE, s22)
    O = fill(O, ONE, s23)
    O = fill(O, TWO, s24)
    return O

def dsl2(I):
    O = I
    A = asindices(I)
    p8 = ofcolor(I, EIGHT)
    p2 = ofcolor(I, TWO)
    u1 = UP
    u2 = add(UP, UP)
    u3 = add(u2, UP)
    u4 = add(u3, UP)
    # place tops first
    top8 = intersection(A, shift(p8, u3))
    top2 = intersection(A, shift(p2, u4))
    O = fill(O, EIGHT, top8)
    O = fill(O, TWO, top2)
    # underfill ones beneath (will not overwrite tops)
    ones8 = combine(intersection(A, shift(p8, u1)), intersection(A, shift(p8, u2)))
    ones2a = intersection(A, shift(p2, u1))
    ones2b = intersection(A, shift(p2, u2))
    ones2c = intersection(A, shift(p2, u3))
    ones = combine(combine(ones8, ones2a), combine(ones2b, ones2c))
    O = underfill(O, ONE, ones)
    return O

def dsl3(I):
    O = I
    A = asindices(I)
    p8 = ofcolor(I, EIGHT)
    p2 = ofcolor(I, TWO)
    u1 = UP
    u2 = add(UP, UP)
    u3 = add(u2, UP)
    u4 = add(u3, UP)
    # build 8 towers
    O = fill(O, ONE, intersection(A, shift(p8, u1)))
    O = fill(O, ONE, intersection(A, shift(p8, u2)))
    O = fill(O, EIGHT, intersection(A, shift(p8, u3)))
    # build 2 towers
    O = fill(O, ONE, intersection(A, shift(p2, u1)))
    O = fill(O, ONE, intersection(A, shift(p2, u2)))
    O = fill(O, ONE, intersection(A, shift(p2, u3)))
    O = fill(O, TWO, intersection(A, shift(p2, u4)))
    return O

def dsl4(I):
    O = I
    A = asindices(I)
    p8 = ofcolor(I, EIGHT)
    p2 = ofcolor(I, TWO)
    # precompute offsets
    u1 = UP
    u2 = add(UP, UP)
    u3 = add(u2, UP)
    u4 = add(u3, UP)
    # union all "one" locations then paint once
    ones = combine(
        combine(intersection(A, shift(p8, u1)), intersection(A, shift(p8, u2))),
        combine(
            intersection(A, shift(p2, u1)),
            combine(intersection(A, shift(p2, u2)), intersection(A, shift(p2, u3)))
        )
    )
    O = fill(O, ONE, ones)
    # paint tops
    O = fill(O, EIGHT, intersection(A, shift(p8, u3)))
    O = fill(O, TWO, intersection(A, shift(p2, u4)))
    return O
```