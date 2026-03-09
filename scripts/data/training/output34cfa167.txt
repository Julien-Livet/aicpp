```python
def dsl1(I):
    # Make 4 the background, then extend each present color (1,2,8) along its extreme rows and columns
    bg = mostcolor(I)
    O = replace(I, bg, FOUR)
    P1 = ofcolor(I, ONE)
    O = branch(size(P1)==0, O, fill(O, ONE, hfrontier(astuple(uppermost(P1), 0))))
    O = branch(size(P1)==0, O, fill(O, ONE, hfrontier(astuple(lowermost(P1), 0))))
    O = branch(size(P1)==0, O, fill(O, ONE, vfrontier(astuple(0, leftmost(P1)))))
    O = branch(size(P1)==0, O, fill(O, ONE, vfrontier(astuple(0, rightmost(P1)))))
    P2 = ofcolor(I, TWO)
    O = branch(size(P2)==0, O, fill(O, TWO, hfrontier(astuple(uppermost(P2), 0))))
    O = branch(size(P2)==0, O, fill(O, TWO, hfrontier(astuple(lowermost(P2), 0))))
    O = branch(size(P2)==0, O, fill(O, TWO, vfrontier(astuple(0, leftmost(P2)))))
    O = branch(size(P2)==0, O, fill(O, TWO, vfrontier(astuple(0, rightmost(P2)))))
    P8 = ofcolor(I, EIGHT)
    O = branch(size(P8)==0, O, fill(O, EIGHT, hfrontier(astuple(uppermost(P8), 0))))
    O = branch(size(P8)==0, O, fill(O, EIGHT, hfrontier(astuple(lowermost(P8), 0))))
    O = branch(size(P8)==0, O, fill(O, EIGHT, vfrontier(astuple(0, leftmost(P8)))))
    O = branch(size(P8)==0, O, fill(O, EIGHT, vfrontier(astuple(0, rightmost(P8)))))
    return O

def dsl2(I):
    # Replace background by 4 and overlay all four symmetries (original, H, V, 180) of the colored content
    bg = mostcolor(I)
    O = replace(I, bg, FOUR)
    G0 = I
    G1 = hmirror(I)
    G2 = vmirror(I)
    G3 = rot180(I)
    forG = (G0, G1, G2, G3)
    # inline expansion without loops
    g = G0
    P = difference(asindices(g), ofcolor(g, ZERO))
    Obj = toobject(P, g)
    O = paint(O, Obj)
    g = G1
    P = difference(asindices(g), ofcolor(g, ZERO))
    Obj = toobject(P, g)
    O = paint(O, Obj)
    g = G2
    P = difference(asindices(g), ofcolor(g, ZERO))
    Obj = toobject(P, g)
    O = paint(O, Obj)
    g = G3
    P = difference(asindices(g), ofcolor(g, ZERO))
    Obj = toobject(P, g)
    O = paint(O, Obj)
    return O

def dsl3(I):
    # Make bg=4, then lay periodic stripe grids from the first occurrences of 8/2/1 with distinct steps
    bg = mostcolor(I)
    O = replace(I, bg, FOUR)
    # 8: dense grid every 2
    P8 = ofcolor(I, EIGHT)
    r0 = branch(size(P8)==0, 0, uppermost(P8))
    c0 = branch(size(P8)==0, 0, leftmost(P8))
    r1 = add(r0, TWO); r2 = add(r1, TWO)
    c1 = add(c0, TWO); c2 = add(c1, TWO)
    O = branch(size(P8)==0, O, fill(O, EIGHT, hfrontier(astuple(r0, 0))))
    O = branch(size(P8)==0, O, fill(O, EIGHT, hfrontier(astuple(r1, 0))))
    O = branch(size(P8)==0, O, fill(O, EIGHT, hfrontier(astuple(r2, 0))))
    O = branch(size(P8)==0, O, fill(O, EIGHT, vfrontier(astuple(0, c0))))
    O = branch(size(P8)==0, O, fill(O, EIGHT, vfrontier(astuple(0, c1))))
    O = branch(size(P8)==0, O, fill(O, EIGHT, vfrontier(astuple(0, c2))))
    # 2: medium grid every 4
    P2 = ofcolor(I, TWO)
    r0 = branch(size(P2)==0, 0, uppermost(P2))
    c0 = branch(size(P2)==0, 0, leftmost(P2))
    r1 = add(r0, FOUR); r2 = add(r1, FOUR)
    c1 = add(c0, FOUR); c2 = add(c1, FOUR)
    O = branch(size(P2)==0, O, fill(O, TWO, hfrontier(astuple(r0, 0))))
    O = branch(size(P2)==0, O, fill(O, TWO, hfrontier(astuple(r1, 0))))
    O = branch(size(P2)==0, O, fill(O, TWO, hfrontier(astuple(r2, 0))))
    O = branch(size(P2)==0, O, fill(O, TWO, vfrontier(astuple(0, c0))))
    O = branch(size(P2)==0, O, fill(O, TWO, vfrontier(astuple(0, c1))))
    O = branch(size(P2)==0, O, fill(O, TWO, vfrontier(astuple(0, c2))))
    # 1: sparse grid every 6
    P1 = ofcolor(I, ONE)
    r0 = branch(size(P1)==0, 0, uppermost(P1))
    c0 = branch(size(P1)==0, 0, leftmost(P1))
    six = add(FOUR, TWO)
    r1 = add(r0, six); r2 = add(r1, six)
    c1 = add(c0, six); c2 = add(c1, six)
    O = branch(size(P1)==0, O, fill(O, ONE, hfrontier(astuple(r0, 0))))
    O = branch(size(P1)==0, O, fill(O, ONE, hfrontier(astuple(r1, 0))))
    O = branch(size(P1)==0, O, fill(O, ONE, hfrontier(astuple(r2, 0))))
    O = branch(size(P1)==0, O, fill(O, ONE, vfrontier(astuple(0, c0))))
    O = branch(size(P1)==0, O, fill(O, ONE, vfrontier(astuple(0, c1))))
    O = branch(size(P1)==0, O, fill(O, ONE, vfrontier(astuple(0, c2))))
    return O

def dsl4(I):
    # Replace bg by 4 and overlay six symmetries (original + H + V + 180 + both diagonals)
    bg = mostcolor(I)
    O = replace(I, bg, FOUR)
    Gs = (I, hmirror(I), vmirror(I), rot180(I), dmirror(I), cmirror(I))
    # inline expansion without loops
    g = Gs[0]
    P = difference(asindices(g), ofcolor(g, ZERO))
    Obj = toobject(P, g)
    O = paint(O, Obj)
    g = Gs[1]
    P = difference(asindices(g), ofcolor(g, ZERO))
    Obj = toobject(P, g)
    O = paint(O, Obj)
    g = Gs[2]
    P = difference(asindices(g), ofcolor(g, ZERO))
    Obj = toobject(P, g)
    O = paint(O, Obj)
    g = Gs[3]
    P = difference(asindices(g), ofcolor(g, ZERO))
    Obj = toobject(P, g)
    O = paint(O, Obj)
    g = Gs[4]
    P = difference(asindices(g), ofcolor(g, ZERO))
    Obj = toobject(P, g)
    O = paint(O, Obj)
    g = Gs[5]
    P = difference(asindices(g), ofcolor(g, ZERO))
    Obj = toobject(P, g)
    O = paint(O, Obj)
    return O

def dsl5(I):
    # Make 4 the background, then draw rectangular outlines (in 3) around each color class 1,2,8
    bg = mostcolor(I)
    O = replace(I, bg, FOUR)
    B1 = box(ofcolor(I, ONE))
    B2 = box(ofcolor(I, TWO))
    B8 = box(ofcolor(I, EIGHT))
    U = combine(B1, combine(B2, B8))
    O = fill(O, THREE, U)
    # Emphasize centers of 2 and 8 boxes
    I2 = inbox(ofcolor(I, TWO))
    I8 = inbox(ofcolor(I, EIGHT))
    M = combine(I2, I8)
    O = fill(O, EIGHT, M)
    return O
```