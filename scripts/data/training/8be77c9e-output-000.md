```python
def dsl1(I):
    O = vconcat(I, hmirror(I))
    return O

def dsl2(I):
    O = vconcat(I, rot270(vmirror(rot90(I))))
    return O

def dsl3(I):
    A = asobject(I)
    G = paint(canvas(0, shape(I)), A)
    O = vconcat(G, hmirror(G))
    return O

def dsl4(I):
    c = leastcolor(I)
    p = ofcolor(I, c)
    obj = recolor(c, p)
    G = paint(canvas(0, shape(I)), obj)
    O = vconcat(G, hmirror(G))
    return O

def dsl5(I):
    O = vconcat(I, vmirror(rot180(I)))
    return O
```