```python
def dsl1(I):
    obs = objects(I, T, F, T)
    zobs = colorfilter(obs, ZERO)
    best = argmax(zobs, size)
    O = subgrid(best, I)
    return O

def dsl2(I):
    obs = objects(I, T, F, T)
    zobs = colorfilter(obs, ZERO)
    best = argmax(zobs, width)
    O = subgrid(best, I)
    return O

def dsl3(I):
    obs = objects(I, T, F, T)
    zobs = colorfilter(obs, ZERO)
    best = argmax(zobs, height)
    O = subgrid(best, I)
    return O

def dsl4(I):
    obs = objects(I, T, F, T)
    zobs = colorfilter(obs, ZERO)
    best = argmax(zobs, size)
    inside = delta(best)
    x1 = fill(I, ZERO, inside)
    O = subgrid(best, x1)
    return O

def dsl5(I):
    obs = objects(I, T, F, T)
    zobs = colorfilter(obs, ZERO)
    best = argmax(zobs, size)
    sub = subgrid(best, I)
    dims = shape(sub)
    O = canvas(ZERO, dims)
    return O
```