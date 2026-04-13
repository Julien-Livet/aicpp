```python
def dsl1(I):
    O = crop(I, ORIGIN, astuple(height(I), hperiod(asobject(I))))
    return O

def dsl2(I):
    O = first(vsplit(I, size(occurrences(I, asobject(crop(I, ORIGIN, astuple(height(I), ONE)))))))
    return O

def dsl3(I):
    O = crop(I, ORIGIN, astuple(height(I), hperiod(toobject(ofcolor(I, leastcolor(I)), I))))
    return O

def dsl4(I):
    O = crop(I, ORIGIN, astuple(height(I), vperiod(asobject(rot90(I)))))
    return O

def dsl5(I):
    O = crop(I, ORIGIN, astuple(height(I), hperiod(asobject(crop(I, ORIGIN, astuple(ONE, width(I)))))))
    return O
```