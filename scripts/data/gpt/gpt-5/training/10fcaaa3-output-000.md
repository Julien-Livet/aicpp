```python
def dsl1(I):
    # Global tiling: duplicate grid 2x horizontally and vertically
    H = hconcat(I, I)
    O = vconcat(H, H)
    return O

def dsl2(I):
    # Object extraction: tile 2x2, then paint only non-zero cells onto an 8 canvas
    H = hconcat(I, I)
    B = vconcat(H, H)
    C = canvas(EIGHT, shape(B))
    NZ = difference(asindices(B), ofcolor(B, ZERO))
    NZOBJ = toobject(NZ, B)
    O = paint(C, NZOBJ)
    return O

def dsl3(I):
    # Color filtering: tile 2x2, then turn all zeros into 8
    H = hconcat(I, I)
    B = vconcat(H, H)
    O = replace(B, ZERO, EIGHT)
    return O

def dsl4(I):
    # Geometric upscaling: upscale by 2x in both directions, then turn zeros into 8
    U = vupscale(hupscale(I, TWO), TWO)
    O = replace(U, ZERO, EIGHT)
    return O

def dsl5(I):
    # Relational/structural: tile 2x2, then draw 8s along color frontiers
    H = hconcat(I, I)
    B = vconcat(H, H)
    F = frontiers(B)
    O = fill(B, EIGHT, F)
    return O
```