```python
def dsl1(I):
    # Vertical interior: 5-cells with both up and down 5-neighbors become 2; all 5->8
    P = ofcolor(I, FIVE)
    Vert = intersection(shift(P, UP), shift(P, DOWN))
    Core = intersection(P, Vert)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, Core)
    return O

def dsl2(I):
    # Per-object bbox-center vertical: draw vertical line through each 5-object's bbox center, clipped to object; 5->8
    Os = colorfilter(objects(I, T, F, T), FIVE)
    C = center
    Up = rbind(shoot, UP)
    Down = rbind(shoot, DOWN)
    Vline = fork(combine, compose(Up, C), compose(Down, C))
    Inside = fork(intersection, compose(toindices, identity), Vline)
    Lines = merge(apply(Inside, Os))
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, Lines)
    return O

def dsl3(I):
    # Right edges only: rightmost 5s of each horizontal run become 2; others 5->8
    P = ofcolor(I, FIVE)
    RightEdges = difference(P, shift(P, RIGHT))
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, RightEdges)
    return O

def dsl4(I):
    # Vertical symmetry core: cells where 5 overlaps its vertical mirror become 2; others 5->8
    P = ofcolor(I, FIVE)
    Sym = intersection(P, vmirror(P))
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, Sym)
    return O

def dsl5(I):
    # Top-of-vertical segments: top three cells of any vertical 5-segment (length>=3) and isolated singles become 2; others 5->8
    P = ofcolor(I, FIVE)
    P1 = shift(P, DOWN)
    P2 = shift(P1, DOWN)
    Top3Seeds = intersection(P, intersection(P1, P2))
    Seg1 = Top3Seeds
    Seg2 = intersection(P, shift(Top3Seeds, DOWN))
    Seg3 = intersection(P, shift(Seg2, DOWN))
    TopStripe = combine(Seg1, combine(Seg2, Seg3))
    Iso = difference(P, combine(shift(P, UP), shift(P, DOWN)))
    Marks = combine(TopStripe, Iso)
    base = replace(I, FIVE, EIGHT)
    O = fill(base, TWO, Marks)
    return O
```