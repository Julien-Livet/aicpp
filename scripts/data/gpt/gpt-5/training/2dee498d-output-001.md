```python
def dsl1(I):
    O = crop(I, ORIGIN, astuple(height(I), divide(width(I), THREE)))
    return O

def dsl2(I):
    O = first(vsplit(I, THREE))
    return O

def dsl3(I):
    O = crop(I, ORIGIN, astuple(height(I), hperiod(toobject(ofcolor(I, mostcolor(I)), I))))
    return O

def dsl4(I):
    O = rot270(first(hsplit(rot90(I), THREE)))
    return O

def dsl5(I):
    S = first(vsplit(I, THREE))
    O = underpaint(canvas(ZERO, shape(S)), asobject(S))
    return O
```