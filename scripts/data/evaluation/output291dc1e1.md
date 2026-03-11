```python
def dsl1(I):
    x = replace(I, ZERO, EIGHT)
    x = replace(x, ONE, EIGHT)
    x = replace(x, TWO, EIGHT)
    x = trim(x)
    x = rot270(x)
    O = compress(x)
    return O

def dsl2(I):
    x = replace(I, ZERO, EIGHT)
    x = replace(x, ONE, EIGHT)
    x = replace(x, TWO, EIGHT)
    x = dmirror(x)
    O = compress(x)
    return O

def dsl3(I):
    x = replace(I, ZERO, EIGHT)
    x = replace(x, ONE, EIGHT)
    x = replace(x, TWO, EIGHT)
    x = cmirror(x)
    O = compress(x)
    return O

def dsl4(I):
    x = replace(I, ZERO, EIGHT)
    x = replace(x, ONE, EIGHT)
    x = replace(x, TWO, EIGHT)
    x = rot180(x)
    O = compress(x)
    return O

def dsl5(I):
    x = replace(I, ZERO, EIGHT)
    x = replace(x, ONE, EIGHT)
    x = replace(x, TWO, EIGHT)
    x = vmirror(x)
    O = compress(x)
    return O
```