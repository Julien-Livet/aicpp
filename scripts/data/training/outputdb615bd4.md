```python
def dsl1(I):
    # Hypothesis: recolor mapping to normalize stripes and background
    O = switch(I, EIGHT, FOUR)
    O = switch(O, ONE, TWO)
    return O

def dsl2(I):
    # Hypothesis: unify scattered 4s into a solid rectangle
    O = I
    p4 = ofcolor(I, FOUR)
    b4 = backdrop(p4)
    O = fill(O, FOUR, b4)
    return O

def dsl3(I):
    # Hypothesis: expand each signal color (4,2,3,9) to its bounding rectangle
    O = I
    O = fill(O, FOUR, backdrop(ofcolor(I, FOUR)))
    O = fill(O, TWO, backdrop(ofcolor(I, TWO)))
    O = fill(O, THREE, backdrop(ofcolor(I, THREE)))
    O = fill(O, NINE, backdrop(ofcolor(I, NINE)))
    return O

def dsl4(I):
    # Hypothesis: emphasize the frame/outline around the 4-region
    O = I
    p = backdrop(ofcolor(I, FOUR))
    border = box(p)
    O = fill(O, FOUR, border)
    return O

def dsl5(I):
    # Hypothesis: change background to 4, then project 2/3/9 blocks by their backdrops
    X = replace(I, EIGHT, FOUR)
    O = X
    O = fill(O, TWO, backdrop(ofcolor(I, TWO)))
    O = fill(O, THREE, backdrop(ofcolor(I, THREE)))
    O = fill(O, NINE, backdrop(ofcolor(I, NINE)))
    return O
```