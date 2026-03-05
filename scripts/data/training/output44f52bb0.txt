```python
def dsl1(I):
    x1 = vmirror(I)
    x2 = hmirror(I)
    c1 = equality(I, x1)
    c2 = equality(I, x2)
    cond = either(c1, c2)
    val = branch(cond, ONE, SEVEN)
    O = canvas(val, UNITY)
    return O

def dsl2(I):
    x1 = rot180(I)
    cond = equality(I, x1)
    val = branch(cond, ONE, SEVEN)
    O = canvas(val, UNITY)
    return O

def dsl3(I):
    x1 = vmirror(I)
    cond = equality(I, x1)
    val = branch(cond, ONE, SEVEN)
    O = canvas(val, UNITY)
    return O

def dsl4(I):
    x1 = hmirror(I)
    cond = equality(I, x1)
    val = branch(cond, ONE, SEVEN)
    O = canvas(val, UNITY)
    return O

def dsl5(I):
    x1 = vmirror(I)
    x2 = hmirror(I)
    c1 = equality(I, x1)
    c2 = equality(I, x2)
    cond = both(c1, c2)
    val = branch(cond, ONE, SEVEN)
    O = canvas(val, UNITY)
    return O
```