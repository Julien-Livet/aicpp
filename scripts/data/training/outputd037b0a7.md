```python
def dsl1(I):
    x1 = objects(I, T, F, T)
    f1 = compose(rbind(shoot, DOWN), ulcorner)
    f2 = fork(recolor, color, f1)
    x2 = mapply(f2, x1)
    O = underpaint(I, x2)
    return O

def dsl2(I):
    x1 = objects(I, T, F, T)
    fcol = compose(vfrontier, ulcorner)
    fabv = compose(rbind(shoot, UP), ulcorner)
    fsing = compose(initset, ulcorner)
    fstr = fork(difference, fabv, fsing)
    fdown = fork(difference, fcol, fstr)
    fline = fork(recolor, color, fdown)
    x2 = mapply(fline, x1)
    O = underpaint(I, x2)
    return O

def dsl3(I):
    x1 = fgpartition(I)
    f1 = compose(rbind(shoot, DOWN), ulcorner)
    f2 = fork(recolor, color, f1)
    x2 = mapply(f2, x1)
    O = underpaint(I, x2)
    return O

def dsl4(I):
    x1 = fgpartition(I)
    fcol = compose(vfrontier, ulcorner)
    fabv = compose(rbind(shoot, UP), ulcorner)
    fsing = compose(initset, ulcorner)
    fstr = fork(difference, fabv, fsing)
    fdown = fork(difference, fcol, fstr)
    fline = fork(recolor, color, fdown)
    x2 = mapply(fline, x1)
    O = underpaint(I, x2)
    return O
```