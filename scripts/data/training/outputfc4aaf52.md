```python
def dsl1(I):
    # Swap the two foreground colors; place full swapped subgrid to the right and below the original
    fg = difference(asindices(I), ofcolor(I, EIGHT))
    S = subgrid(fg, I)
    cols = remove(EIGHT, palette(S))
    a = minimum(cols)
    b = maximum(cols)
    S2 = switch(S, a, b)
    idx = difference(asindices(S2), ofcolor(S2, EIGHT))
    obj = toobject(idx, S2)
    h = height(S)
    w = width(S)
    ul = ulcorner(fg)
    O = canvas(EIGHT, shape(I))
    O = paint(O, shift(obj, add(ul, tojvec(w))))   # to the right
    O = paint(O, shift(obj, add(ul, toivec(h))))   # below
    return O

def dsl2(I):
    # Swap colors; place rotated copy to the right and unrotated copy below
    fg = difference(asindices(I), ofcolor(I, EIGHT))
    S = subgrid(fg, I)
    cols = remove(EIGHT, palette(S))
    a = minimum(cols)
    b = maximum(cols)
    S2 = switch(S, a, b)
    S2r = rot90(S2)
    obj_r = toobject(difference(asindices(S2r), ofcolor(S2r, EIGHT)), S2r)
    obj = toobject(difference(asindices(S2), ofcolor(S2, EIGHT)), S2)
    h = height(S)
    w = width(S)
    ul = ulcorner(fg)
    O = canvas(EIGHT, shape(I))
    O = paint(O, shift(obj_r, add(ul, tojvec(w))))  # rotated to the right
    O = paint(O, shift(obj, add(ul, toivec(h))))    # unrotated below
    return O

def dsl3(I):
    # No color swap; place diagonal-mirrored subgrid to the right and below
    fg = difference(asindices(I), ofcolor(I, EIGHT))
    S = subgrid(fg, I)
    Sx = dmirror(S)
    obj = toobject(difference(asindices(Sx), ofcolor(Sx, EIGHT)), Sx)
    h = height(S)
    w = width(S)
    ul = ulcorner(fg)
    O = canvas(EIGHT, shape(I))
    O = paint(O, shift(obj, add(ul, tojvec(w))))
    O = paint(O, shift(obj, add(ul, toivec(h))))
    return O

def dsl4(I):
    # Swap colors; place one copy half-way down-right and another to the right
    fg = difference(asindices(I), ofcolor(I, EIGHT))
    S = subgrid(fg, I)
    cols = remove(EIGHT, palette(S))
    a = minimum(cols)
    b = maximum(cols)
    S2 = switch(S, a, b)
    obj = toobject(difference(asindices(S2), ofcolor(S2, EIGHT)), S2)
    h = height(S)
    w = width(S)
    dh = divide(h, 2)
    dw = divide(w, 2)
    ul = ulcorner(fg)
    O = canvas(EIGHT, shape(I))
    O = paint(O, shift(obj, add(ul, tojvec(w))))              # to the right
    O = paint(O, shift(obj, add(ul, astuple(dh, dw))))        # halfway down-right
    return O

def dsl5(I):
    # Swap colors; place copies to the right and diagonally down-right
    fg = difference(asindices(I), ofcolor(I, EIGHT))
    S = subgrid(fg, I)
    cols = remove(EIGHT, palette(S))
    a = minimum(cols)
    b = maximum(cols)
    S2 = switch(S, a, b)
    obj = toobject(difference(asindices(S2), ofcolor(S2, EIGHT)), S2)
    h = height(S)
    w = width(S)
    ul = ulcorner(fg)
    O = canvas(EIGHT, shape(I))
    O = paint(O, shift(obj, add(ul, tojvec(w))))           # to the right
    O = paint(O, shift(obj, add(ul, astuple(h, w))))       # down-right
    return O
```