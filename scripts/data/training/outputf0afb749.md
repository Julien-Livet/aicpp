```python
def dsl1(I):
    U = upscale(I, TWO)
    OB = objects(I, T, F, T)
    P0 = apply(ulcorner, OB)
    P = apply(double, P0)
    DR = add(DOWN, RIGHT)
    UL = add(UP, LEFT)
    dr = rbind(shoot, DR)
    ul = rbind(shoot, UL)
    a = compose(lrcorner, dr)
    b = compose(ulcorner, ul)
    linefun = fork(connect, a, b)
    L = mapply(linefun, P)
    O = underfill(U, ONE, L)
    return O

def dsl2(I):
    U = upscale(I, TWO)
    OB = objects(U, T, F, T)
    P = apply(ulcorner, OB)
    DR = add(DOWN, RIGHT)
    UL = add(UP, LEFT)
    dr = rbind(shoot, DR)
    ul = rbind(shoot, UL)
    a = compose(lrcorner, dr)
    b = compose(ulcorner, ul)
    linefun = fork(connect, a, b)
    L = mapply(linefun, P)
    O = underfill(U, ONE, L)
    return O

def dsl3(I):
    U = upscale(I, TWO)
    OB = objects(I, T, F, T)
    P0 = apply(lrcorner, OB)
    P = apply(double, P0)
    DR = add(DOWN, RIGHT)
    UL = add(UP, LEFT)
    dr = rbind(shoot, DR)
    ul = rbind(shoot, UL)
    a = compose(lrcorner, dr)
    b = compose(ulcorner, ul)
    linefun = fork(connect, a, b)
    L = mapply(linefun, P)
    O = underfill(U, ONE, L)
    return O

def dsl4(I):
    U = upscale(I, TWO)
    OB = objects(I, T, F, T)
    P0 = apply(urcorner, OB)
    P = apply(double, P0)
    DR = add(DOWN, RIGHT)
    UL = add(UP, LEFT)
    dr = rbind(shoot, DR)
    ul = rbind(shoot, UL)
    a = compose(lrcorner, dr)
    b = compose(ulcorner, ul)
    linefun = fork(connect, a, b)
    L = mapply(linefun, P)
    O = underfill(U, ONE, L)
    return O

def dsl5(I):
    U = upscale(I, TWO)
    OB = objects(I, T, F, T)
    P0 = apply(centerofmass, OB)
    P = apply(double, P0)
    DR = add(DOWN, RIGHT)
    UL = add(UP, LEFT)
    dr = rbind(shoot, DR)
    ul = rbind(shoot, UL)
    a = compose(lrcorner, dr)
    b = compose(ulcorner, ul)
    linefun = fork(connect, a, b)
    L = mapply(linefun, P)
    O = underfill(U, ONE, L)
    return O
```