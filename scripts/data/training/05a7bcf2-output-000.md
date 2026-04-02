```python
def dsl1(I):
    top = tophalf(I)
    bot = bottomhalf(I)
    top2 = replace(top, FOUR, THREE)
    O = vconcat(top2, bot)
    return O

def dsl2(I):
    eights = ofcolor(I, EIGHT)
    band = inbox(eights)
    obj = recolor(EIGHT, band)
    O = underpaint(I, obj)
    return O

def dsl3(I):
    O1 = replace(I, TWO, EIGHT)
    O2 = replace(O1, THREE, EIGHT)
    O3 = replace(O2, FOUR, EIGHT)
    return O3

def dsl4(I):
    O = vmirror(I)
    return O

def dsl5(I):
    left = ofcolor(I, FOUR)
    right = ofcolor(I, TWO)
    anchors = combine(left, right)
    rect = inbox(anchors)
    obj = recolor(EIGHT, rect)
    O = underpaint(I, obj)
    return O
```