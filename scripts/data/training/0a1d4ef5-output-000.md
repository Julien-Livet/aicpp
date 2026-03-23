```python
def dsl1(I):
    # Global summarization via block downscaling and cropping to nonzero
    ds = downscale(I, TEN)
    nz = difference(asindices(ds), ofcolor(ds, ZERO))
    O = subgrid(nz, ds)
    return O

def dsl2(I):
    # Global compression of frontiers followed by cropping to nonzero
    C = compress(I)
    nz = difference(asindices(C), ofcolor(C, ZERO))
    O = subgrid(nz, C)
    return O

def dsl3(I):
    # Geometric: extract and render only frontiers (boundaries)
    frs = frontiers(I)
    merged = merge(frs)
    base = canvas(ZERO, shape(I))
    O = paint(base, merged)
    return O

def dsl4(I):
    # Geometric + reduction: render frontiers, compress them, then crop to nonzero
    frs = frontiers(I)
    merged = merge(frs)
    base = canvas(ZERO, shape(I))
    F = paint(base, merged)
    C = compress(F)
    nz = difference(asindices(C), ofcolor(C, ZERO))
    O = subgrid(nz, C)
    return O

def dsl5(I):
    # Relational: compress each half, then combine and compress again
    L = lefthalf(I)
    R = righthalf(I)
    CL = compress(L)
    CR = compress(R)
    H = hconcat(CL, CR)
    O = compress(H)
    return O
```