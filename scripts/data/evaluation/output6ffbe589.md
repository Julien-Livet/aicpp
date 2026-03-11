```python
def dsl1(I):
    # Largest multi-color connected component (4-adjacent), then crop to its bbox
    obs = objects(I, F, F, T)
    pick = argmax(obs, size)
    O = subgrid(pick, I)
    return O

def dsl2(I):
    # Prefer largest multi-color component not touching border (8-adjacent), else largest overall
    obs = objects(I, F, T, T)
    inner = sfilter(obs, compose(flip, rbind(bordering, I)))
    pick = branch(positive(size(inner)), argmax(inner, size), argmax(obs, size))
    O = subgrid(pick, I)
    return O

def dsl3(I):
    # Find a single-color rectangular ring (outline == object), crop to its bbox; fallback to largest single-color object
    sobj = objects(I, T, F, T)
    rings = sfilter(sobj, fork(equality, box, toindices))
    pick = branch(positive(size(rings)), argmax(rings, size), argmax(sobj, size))
    O = subgrid(pick, I)
    return O

def dsl4(I):
    # Prefer largest multi-color component not touching border (4-adjacent), else largest overall
    obs = objects(I, F, F, T)
    inner = sfilter(obs, compose(flip, rbind(bordering, I)))
    pick = branch(positive(size(inner)), argmax(inner, size), argmax(obs, size))
    O = subgrid(pick, I)
    return O

def dsl5(I):
    # Among single-color objects, maximize how much lies on its own bbox outline (favours rings), then crop
    sobj = objects(I, T, F, T)
    score = fork(size, box, toindices)
    pick = argmax(sobj, score)
    O = subgrid(pick, I)
    return O
```