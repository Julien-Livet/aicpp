```python
def dsl1(I):
    x0 = replace(I, ONE, TWO)
    a = crop(x0, ORIGIN, THREE_BY_THREE)
    b = crop(x0, astuple(THREE, ZERO), THREE_BY_THREE)
    c = branch(equality(a, b), a, vmirror(a))
    O = vconcat(a, vconcat(b, c))
    return O

def dsl2(I):
    x0 = replace(I, ONE, TWO)
    a = crop(x0, ORIGIN, THREE_BY_THREE)
    b = crop(x0, astuple(THREE, ZERO), THREE_BY_THREE)
    O = vconcat(a, vconcat(b, a))
    return O

def dsl3(I):
    x0 = replace(I, ONE, TWO)
    a = crop(x0, ORIGIN, THREE_BY_THREE)
    b = crop(x0, astuple(THREE, ZERO), THREE_BY_THREE)
    c = vmirror(a)
    O = vconcat(a, vconcat(b, c))
    return O

def dsl4(I):
    x0 = replace(I, ONE, TWO)
    a = crop(x0, ORIGIN, THREE_BY_THREE)
    b = crop(x0, astuple(THREE, ZERO), THREE_BY_THREE)
    c = vmirror(b)
    O = vconcat(a, vconcat(b, c))
    return O

def dsl5(I):
    x0 = replace(I, ONE, TWO)
    a = crop(x0, ORIGIN, THREE_BY_THREE)
    O = vconcat(x0, a)
    return O
```