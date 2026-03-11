```python
def dsl1(I):
    # Hypothesis A: Horizontally dilate only the non-1, non-background colors across 8s until blocked.
    objs = objects(I, T, F, T)
    non1 = difference(objs, colorfilter(objs, ONE))
    seed = merge(non1)
    O = I
    # spread right (12 steps)
    s = shift(seed, RIGHT); O = underpaint(O, s)
    s = shift(s, RIGHT);    O = underpaint(O, s)
    s = shift(s, RIGHT);    O = underpaint(O, s)
    s = shift(s, RIGHT);    O = underpaint(O, s)
    s = shift(s, RIGHT);    O = underpaint(O, s)
    s = shift(s, RIGHT);    O = underpaint(O, s)
    s = shift(s, RIGHT);    O = underpaint(O, s)
    s = shift(s, RIGHT);    O = underpaint(O, s)
    s = shift(s, RIGHT);    O = underpaint(O, s)
    s = shift(s, RIGHT);    O = underpaint(O, s)
    s = shift(s, RIGHT);    O = underpaint(O, s)
    s = shift(s, RIGHT);    O = underpaint(O, s)
    # spread left (12 steps)
    s = shift(seed, LEFT);  O = underpaint(O, s)
    s = shift(s, LEFT);     O = underpaint(O, s)
    s = shift(s, LEFT);     O = underpaint(O, s)
    s = shift(s, LEFT);     O = underpaint(O, s)
    s = shift(s, LEFT);     O = underpaint(O, s)
    s = shift(s, LEFT);     O = underpaint(O, s)
    s = shift(s, LEFT);     O = underpaint(O, s)
    s = shift(s, LEFT);     O = underpaint(O, s)
    s = shift(s, LEFT);     O = underpaint(O, s)
    s = shift(s, LEFT);     O = underpaint(O, s)
    s = shift(s, LEFT);     O = underpaint(O, s)
    s = shift(s, LEFT);     O = underpaint(O, s)
    return O

def dsl2(I):
    # Hypothesis B: Vertically dilate only the non-1, non-background colors across 8s until blocked.
    objs = objects(I, T, F, T)
    non1 = difference(objs, colorfilter(objs, ONE))
    seed = merge(non1)
    O = I
    # spread down (12 steps)
    s = shift(seed, DOWN);  O = underpaint(O, s)
    s = shift(s, DOWN);     O = underpaint(O, s)
    s = shift(s, DOWN);     O = underpaint(O, s)
    s = shift(s, DOWN);     O = underpaint(O, s)
    s = shift(s, DOWN);     O = underpaint(O, s)
    s = shift(s, DOWN);     O = underpaint(O, s)
    s = shift(s, DOWN);     O = underpaint(O, s)
    s = shift(s, DOWN);     O = underpaint(O, s)
    s = shift(s, DOWN);     O = underpaint(O, s)
    s = shift(s, DOWN);     O = underpaint(O, s)
    s = shift(s, DOWN);     O = underpaint(O, s)
    s = shift(s, DOWN);     O = underpaint(O, s)
    # spread up (12 steps)
    s = shift(seed, UP);    O = underpaint(O, s)
    s = shift(s, UP);       O = underpaint(O, s)
    s = shift(s, UP);       O = underpaint(O, s)
    s = shift(s, UP);       O = underpaint(O, s)
    s = shift(s, UP);       O = underpaint(O, s)
    s = shift(s, UP);       O = underpaint(O, s)
    s = shift(s, UP);       O = underpaint(O, s)
    s = shift(s, UP);       O = underpaint(O, s)
    s = shift(s, UP);       O = underpaint(O, s)
    s = shift(s, UP);       O = underpaint(O, s)
    s = shift(s, UP);       O = underpaint(O, s)
    s = shift(s, UP);       O = underpaint(O, s)
    return O

def dsl3(I):
    # Hypothesis C: First horizontal then vertical dilation of non-1 colors across background (union of shifted seeds).
    objs = objects(I, T, F, T)
    non1 = difference(objs, colorfilter(objs, ONE))
    seed = merge(non1)
    O = I
    # horizontal both ways
    s = shift(seed, RIGHT); O = underpaint(O, s)
    s = shift(s, RIGHT);    O = underpaint(O, s)
    s = shift(s, RIGHT);    O = underpaint(O, s)
    s = shift(s, RIGHT);    O = underpaint(O, s)
    s = shift(s, RIGHT);    O = underpaint(O, s)
    s = shift(seed, LEFT);  O = underpaint(O, s)
    s = shift(s, LEFT);     O = underpaint(O, s)
    s = shift(s, LEFT);     O = underpaint(O, s)
    s = shift(s, LEFT);     O = underpaint(O, s)
    s = shift(s, LEFT);     O = underpaint(O, s)
    # vertical both ways
    s = shift(seed, DOWN);  O = underpaint(O, s)
    s = shift(s, DOWN);     O = underpaint(O, s)
    s = shift(s, DOWN);     O = underpaint(O, s)
    s = shift(s, DOWN);     O = underpaint(O, s)
    s = shift(s, DOWN);     O = underpaint(O, s)
    s = shift(seed, UP);    O = underpaint(O, s)
    s = shift(s, UP);       O = underpaint(O, s)
    s = shift(s, UP);       O = underpaint(O, s)
    s = shift(s, UP);       O = underpaint(O, s)
    s = shift(s, UP);       O = underpaint(O, s)
    return O

def dsl4(I):
    # Hypothesis D: Vertical-first then horizontal dilation (order variation) of non-1 colors across background.
    objs = objects(I, T, F, T)
    non1 = difference(objs, colorfilter(objs, ONE))
    seed = merge(non1)
    O = I
    # vertical first
    s = shift(seed, DOWN);  O = underpaint(O, s)
    s = shift(s, DOWN);     O = underpaint(O, s)
    s = shift(s, DOWN);     O = underpaint(O, s)
    s = shift(seed, UP);    O = underpaint(O, s)
    s = shift(s, UP);       O = underpaint(O, s)
    s = shift(s, UP);       O = underpaint(O, s)
    # horizontal after
    s = shift(seed, RIGHT); O = underpaint(O, s)
    s = shift(s, RIGHT);    O = underpaint(O, s)
    s = shift(s, RIGHT);    O = underpaint(O, s)
    s = shift(seed, LEFT);  O = underpaint(O, s)
    s = shift(s, LEFT);     O = underpaint(O, s)
    s = shift(s, LEFT);     O = underpaint(O, s)
    return O

def dsl5(I):
    # Hypothesis E: Two-pass approach. Pass1: horizontal dilate non-1 colors. Pass2: rotate, re-seed on updated grid, horizontal again, rotate back.
    # This allows vertical propagation using fresh seeds from the intermediate result.
    objs1 = objects(I, T, F, T)
    non1_1 = difference(objs1, colorfilter(objs1, ONE))
    seed1 = merge(non1_1)
    A = I
    # Pass1 horizontal
    s = shift(seed1, RIGHT); A = underpaint(A, s)
    s = shift(s, RIGHT);     A = underpaint(A, s)
    s = shift(s, RIGHT);     A = underpaint(A, s)
    s = shift(seed1, LEFT);  A = underpaint(A, s)
    s = shift(s, LEFT);      A = underpaint(A, s)
    s = shift(s, LEFT);      A = underpaint(A, s)
    # Pass2 on rotated grid
    R = rot90(A)
    objs2 = objects(R, T, F, T)
    non1_2 = difference(objs2, colorfilter(objs2, ONE))
    seed2 = merge(non1_2)
    # horizontal on rotated (i.e., vertical in original)
    s = shift(seed2, RIGHT); R = underpaint(R, s)
    s = shift(s, RIGHT);     R = underpaint(R, s)
    s = shift(s, RIGHT);     R = underpaint(R, s)
    s = shift(seed2, LEFT);  R = underpaint(R, s)
    s = shift(s, LEFT);      R = underpaint(R, s)
    s = shift(s, LEFT);      R = underpaint(R, s)
    O = rot270(R)
    return O
```