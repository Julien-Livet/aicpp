```python
def dsl1(I):
    # Mirror all non-2 objects across every detected '2' axis (vertical lines, horizontal lines, and single pivots).
    H = height(I)
    W = width(I)
    O = I
    twos = colorfilter(objects(I, True, False, True), TWO)

    for ax in twos:
        if vline(ax):
            c = leftmost(ax)
            dc = subtract(double(c), decrement(W))
            VM = vmirror(I)
            vm_objs = objects(VM, True, False, True)
            vm_non2 = difference(vm_objs, colorfilter(vm_objs, TWO))
            for obj in vm_non2:
                O = underpaint(O, shift(obj, astuple(ZERO, dc)))
        elif hline(ax):
            r = uppermost(ax)
            dr = subtract(double(r), decrement(H))
            HM = hmirror(I)
            hm_objs = objects(HM, True, False, True)
            hm_non2 = difference(hm_objs, colorfilter(hm_objs, TWO))
            for obj in hm_non2:
                O = underpaint(O, shift(obj, astuple(dr, ZERO)))
        else:
            r = uppermost(ax)
            c = leftmost(ax)
            dr = subtract(double(r), decrement(H))
            dc = subtract(double(c), decrement(W))
            R = rot180(I)
            r_objs = objects(R, True, False, True)
            r_non2 = difference(r_objs, colorfilter(r_objs, TWO))
            for obj in r_non2:
                O = underpaint(O, shift(obj, astuple(dr, dc)))
    return O

def dsl2(I):
    # One pass per axis type: mirror all non-2 objects once for any vertical/horizontal axis; per-pivot for singletons.
    H = height(I)
    W = width(I)
    O = I
    twos = colorfilter(objects(I, True, False, True), TWO)
    v_axes = sfilter(twos, vline)
    h_axes = sfilter(twos, hline)
    pivots = difference(twos, combine(v_axes, h_axes))

    if size(v_axes) > 0:
        ax = first(v_axes)
        c = leftmost(ax)
        dc = subtract(double(c), decrement(W))
        VM = vmirror(I)
        vm_objs = objects(VM, True, False, True)
        vm_non2 = difference(vm_objs, colorfilter(vm_objs, TWO))
        for obj in vm_non2:
            O = underpaint(O, shift(obj, astuple(ZERO, dc)))

    if size(h_axes) > 0:
        ax = first(h_axes)
        r = uppermost(ax)
        dr = subtract(double(r), decrement(H))
        HM = hmirror(I)
        hm_objs = objects(HM, True, False, True)
        hm_non2 = difference(hm_objs, colorfilter(hm_objs, TWO))
        for obj in hm_non2:
            O = underpaint(O, shift(obj, astuple(dr, ZERO)))

    for ax in pivots:
        r = uppermost(ax)
        c = leftmost(ax)
        dr = subtract(double(r), decrement(H))
        dc = subtract(double(c), decrement(W))
        R = rot180(I)
        r_objs = objects(R, True, False, True)
        r_non2 = difference(r_objs, colorfilter(r_objs, TWO))
        for obj in r_non2:
            O = underpaint(O, shift(obj, astuple(dr, dc)))

    return O

def dsl3(I):
    # Replace 2s with background in mirrored copies, then underpaint shifted whole-asobject once per axis instance.
    H = height(I)
    W = width(I)
    B = mostcolor(I)
    O = I
    twos = colorfilter(objects(I, True, False, True), TWO)

    for ax in twos:
        if vline(ax):
            c = leftmost(ax)
            dc = subtract(double(c), decrement(W))
            MV = replace(vmirror(I), TWO, B)
            O = underpaint(O, shift(asobject(MV), astuple(ZERO, dc)))
        elif hline(ax):
            r = uppermost(ax)
            dr = subtract(double(r), decrement(H))
            MH = replace(hmirror(I), TWO, B)
            O = underpaint(O, shift(asobject(MH), astuple(dr, ZERO)))
        else:
            r = uppermost(ax)
            c = leftmost(ax)
            dr = subtract(double(r), decrement(H))
            dc = subtract(double(c), decrement(W))
            MR = replace(rot180(I), TWO, B)
            O = underpaint(O, shift(asobject(MR), astuple(dr, dc)))

    return O

def dsl4(I):
    # Palette-wise mirroring across axes: for each non-2, non-background color, underpaint its mirrored indices from mirrored grid(s).
    H = height(I)
    W = width(I)
    B = mostcolor(I)
    O = I
    pals = palette(I)
    pals = remove(TWO, pals)
    pals = remove(B, pals)
    twos = colorfilter(objects(I, True, False, True), TWO)

    for ax in twos:
        if vline(ax):
            c = leftmost(ax)
            dc = subtract(double(c), decrement(W))
            VM = vmirror(I)
            for col in pals:
                P = ofcolor(VM, col)
                if size(P) > 0:
                    O = underpaint(O, toobject(shift(P, astuple(ZERO, dc)), VM))
        elif hline(ax):
            r = uppermost(ax)
            dr = subtract(double(r), decrement(H))
            HM = hmirror(I)
            for col in pals:
                P = ofcolor(HM, col)
                if size(P) > 0:
                    O = underpaint(O, toobject(shift(P, astuple(dr, ZERO)), HM))
        else:
            r = uppermost(ax)
            c = leftmost(ax)
            dr = subtract(double(r), decrement(H))
            dc = subtract(double(c), decrement(W))
            R = rot180(I)
            for col in pals:
                P = ofcolor(R, col)
                if size(P) > 0:
                    O = underpaint(O, toobject(shift(P, astuple(dr, dc)), R))

    return O

def dsl5(I):
    # Aggregate all axis effects: do at most one vertical pass, one horizontal pass, and all pivot passes; exclude 2s via object filtering.
    H = height(I)
    W = width(I)
    O = I
    twos = colorfilter(objects(I, True, False, True), TWO)
    v_axes = sfilter(twos, vline)
    h_axes = sfilter(twos, hline)
    pivots = difference(twos, combine(v_axes, h_axes))

    if size(v_axes) > 0:
        c = leftmost(first(v_axes))
        dc = subtract(double(c), decrement(W))
        VM = vmirror(I)
        vm_objs = objects(VM, True, False, True)
        for obj in difference(vm_objs, colorfilter(vm_objs, TWO)):
            O = underpaint(O, shift(obj, astuple(ZERO, dc)))

    if size(h_axes) > 0:
        r = uppermost(first(h_axes))
        dr = subtract(double(r), decrement(H))
        HM = hmirror(I)
        hm_objs = objects(HM, True, False, True)
        for obj in difference(hm_objs, colorfilter(hm_objs, TWO)):
            O = underpaint(O, shift(obj, astuple(dr, ZERO)))

    for ax in pivots:
        r = uppermost(ax)
        c = leftmost(ax)
        dr = subtract(double(r), decrement(H))
        dc = subtract(double(c), decrement(W))
        R = rot180(I)
        r_objs = objects(R, True, False, True)
        for obj in difference(r_objs, colorfilter(r_objs, TWO)):
            O = underpaint(O, shift(obj, astuple(dr, dc)))

    return O
```