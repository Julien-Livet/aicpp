```python
def dsl1(I):
    O = upscale(I, TWO)
    return O

def dsl2(I):
    dims2 = mpapply(multiply, shape(I), TWO_BY_TWO)
    obj2 = upscale(asobject(I), TWO)
    O = paint(canvas(ZERO, dims2), obj2)
    return O

def dsl3(I):
    dims2 = mpapply(multiply, shape(I), TWO_BY_TWO)
    f = chain(rbind(upscale, TWO), fork(recolor, identity, rbind(ofcolor, I)))
    objs = apply(f, palette(I))
    big = merge(objs)
    O = paint(canvas(ZERO, dims2), big)
    return O

def dsl4(I):
    O = vupscale(hupscale(I, TWO), TWO)
    return O

def dsl5(I):
    dims2 = mpapply(multiply, shape(I), TWO_BY_TWO)
    f = chain(rbind(upscale, TWO), fork(recolor, rbind(index, I), initset))
    objs = apply(f, asindices(I))
    big = merge(objs)
    O = paint(canvas(ZERO, dims2), big)
    return O
```