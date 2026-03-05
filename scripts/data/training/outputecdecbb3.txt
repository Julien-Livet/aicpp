```python
def dsl1(I):
    s8 = ofcolor(I, EIGHT)
    s2 = ofcolor(I, TWO)
    objs8 = colorfilter(objects(I, True, False, True), EIGHT)
    ex8 = first(objs8)
    is_vert = vline(ex8)
    rmin = uppermost(s8); rmax = lowermost(s8)
    cmin = leftmost(s8); cmax = rightmost(s8)
    gate = lambda p: combine(combine(neighbors(p), ineighbors(p)), initset(p))
    def contacts(p):
        rp = uppermost(initset(p)); cp = rightmost(initset(p))
        if is_vert:
            L = astuple(rp, cmin); R = astuple(rp, cmax)
            if equality(cmin, cmax): 
                return initset(L)
            dL = manhattan(initset(p), initset(L)); dR = manhattan(initset(p), initset(R))
            tie = equality(dL, dR)
            between = both(greater(cp, cmin), greater(cmax, cp))
            boths = either(tie, between)
            return branch(boths, combine(initset(L), initset(R)), branch(greater(dL, dR), initset(R), initset(L)))
        else:
            U = astuple(rmin, cp); D = astuple(rmax, cp)
            if equality(rmin, rmax):
                return initset(U)
            dU = manhattan(initset(p), initset(U)); dD = manhattan(initset(p), initset(D))
            tie = equality(dU, dD)
            between = both(greater(rp, rmin), greater(rmax, rp))
            boths = either(tie, between)
            return branch(boths, combine(initset(U), initset(D)), branch(greater(dU, dD), initset(D), initset(U)))
    def wires(p):
        rp = uppermost(initset(p)); cp = rightmost(initset(p))
        if is_vert:
            L = astuple(rp, cmin); R = astuple(rp, cmax)
            if equality(cmin, cmax):
                return connect(p, L)
            dL = manhattan(initset(p), initset(L)); dR = manhattan(initset(p), initset(R))
            tie = equality(dL, dR)
            between = both(greater(cp, cmin), greater(cmax, cp))
            boths = either(tie, between)
            return branch(boths, combine(connect(p, L), connect(p, R)), branch(greater(dL, dR), connect(p, R), connect(p, L)))
        else:
            U = astuple(rmin, cp); D = astuple(rmax, cp)
            if equality(rmin, rmax):
                return connect(p, U)
            dU = manhattan(initset(p), initset(U)); dD = manhattan(initset(p), initset(D))
            tie = equality(dU, dD)
            between = both(greater(rp, rmin), greater(rmax, rp))
            boths = either(tie, between)
            return branch(boths, combine(connect(p, U), connect(p, D)), branch(greater(dU, dD), connect(p, D), connect(p, U)))
    C = merge(apply(contacts, s2))
    W = merge(apply(wires, s2))
    G = merge(apply(gate, C))
    O = fill(fill(fill(I, TWO, W), EIGHT, G), TWO, C)
    return O

def dsl2(I):
    s8 = ofcolor(I, EIGHT)
    s2 = ofcolor(I, TWO)
    ex8 = first(colorfilter(objects(I, True, False, True), EIGHT))
    is_vert = vline(ex8)
    rmin = uppermost(s8); rmax = lowermost(s8)
    cmin = leftmost(s8); cmax = rightmost(s8)
    gate = lambda p: combine(combine(neighbors(p), ineighbors(p)), initset(p))
    def pick_targets(p):
        r = uppermost(initset(p)); c = rightmost(initset(p))
        if is_vert:
            L = astuple(r, cmin); R = astuple(r, cmax)
            two_cols = flip(equality(cmin, cmax))
            dL = manhattan(initset(p), initset(L)); dR = manhattan(initset(p), initset(R))
            tie = equality(dL, dR)
            between = both(greater(c, cmin), greater(cmax, c))
            boths = both(two_cols, either(tie, between))
            return branch(boths, combine(initset(L), initset(R)), branch(greater(dL, dR), initset(R), initset(L)))
        else:
            U = astuple(rmin, c); D = astuple(rmax, c)
            two_rows = flip(equality(rmin, rmax))
            dU = manhattan(initset(p), initset(U)); dD = manhattan(initset(p), initset(D))
            tie = equality(dU, dD)
            between = both(greater(r, rmin), greater(rmax, r))
            boths = both(two_rows, either(tie, between))
            return branch(boths, combine(initset(U), initset(D)), branch(greater(dU, dD), initset(D), initset(U)))
    def wire_for(p):
        t = pick_targets(p)
        return merge(apply(lambda q: connect(p, q), t))
    centers = merge(apply(pick_targets, s2))
    wires = merge(apply(wire_for, s2))
    rings = merge(apply(gate, centers))
    O = fill(fill(fill(I, TWO, wires), EIGHT, rings), TWO, centers)
    return O

def dsl3(I):
    s8 = ofcolor(I, EIGHT)
    s2 = ofcolor(I, TWO)
    ex8 = first(colorfilter(objects(I, True, False, True), EIGHT))
    is_vert = vline(ex8)
    rmin = uppermost(s8); rmax = lowermost(s8)
    cmin = leftmost(s8); cmax = rightmost(s8)
    gate = lambda p: combine(combine(neighbors(p), ineighbors(p)), initset(p))
    def targets_and_wires(p):
        r = uppermost(initset(p)); c = rightmost(initset(p))
        if is_vert:
            L = astuple(r, cmin); R = astuple(r, cmax)
            if equality(cmin, cmax):
                return pair(initset(L), initset(connect(p, L)))
            dL = manhattan(initset(p), initset(L)); dR = manhattan(initset(p), initset(R))
            tie = equality(dL, dR)
            between = both(greater(c, cmin), greater(cmax, c))
            boths = either(tie, between)
            Cs = branch(boths, combine(initset(L), initset(R)), branch(greater(dL, dR), initset(R), initset(L)))
            Ws = merge(apply(lambda q: connect(p, q), Cs))
            return pair(Cs, Ws)
        else:
            U = astuple(rmin, c); D = astuple(rmax, c)
            if equality(rmin, rmax):
                return pair(initset(U), initset(connect(p, U)))
            dU = manhattan(initset(p), initset(U)); dD = manhattan(initset(p), initset(D))
            tie = equality(dU, dD)
            between = both(greater(r, rmin), greater(rmax, r))
            boths = either(tie, between)
            Cs = branch(boths, combine(initset(U), initset(D)), branch(greater(dU, dD), initset(D), initset(U)))
            Ws = merge(apply(lambda q: connect(p, q), Cs))
            return pair(Cs, Ws)
    pairs = apply(targets_and_wires, s2)
    centers = merge(apply(first, pairs))
    wires = merge(apply(last, pairs))
    rings = merge(apply(gate, centers))
    O = fill(fill(fill(I, TWO, wires), EIGHT, rings), TWO, centers)
    return O

def dsl4(I):
    s8 = ofcolor(I, EIGHT)
    s2 = ofcolor(I, TWO)
    ex8 = first(colorfilter(objects(I, True, False, True), EIGHT))
    is_horiz = hline(ex8)
    rmin = uppermost(s8); rmax = lowermost(s8)
    cmin = leftmost(s8); cmax = rightmost(s8)
    gate = lambda p: combine(combine(neighbors(p), ineighbors(p)), initset(p))
    def endpts(p):
        r = uppermost(initset(p)); c = rightmost(initset(p))
        if is_horiz:
            U = astuple(rmin, c); D = astuple(rmax, c)
            if equality(rmin, rmax): 
                return initset(U)
            dU = manhattan(initset(p), initset(U)); dD = manhattan(initset(p), initset(D))
            tie = equality(dU, dD)
            between = both(greater(r, rmin), greater(rmax, r))
            return branch(either(tie, between), combine(initset(U), initset(D)), branch(greater(dU, dD), initset(D), initset(U)))
        else:
            L = astuple(r, cmin); R = astuple(r, cmax)
            if equality(cmin, cmax): 
                return initset(L)
            dL = manhattan(initset(p), initset(L)); dR = manhattan(initset(p), initset(R))
            tie = equality(dL, dR)
            between = both(greater(c, cmin), greater(cmax, c))
            return branch(either(tie, between), combine(initset(L), initset(R)), branch(greater(dL, dR), initset(R), initset(L)))
    centers = merge(apply(endpts, s2))
    wires = merge(apply(lambda p: merge(apply(lambda q: connect(p, q), endpts(p))), s2))
    rings = merge(apply(gate, centers))
    O = fill(fill(fill(I, TWO, wires), EIGHT, rings), TWO, centers)
    return O

def dsl5(I):
    s8 = ofcolor(I, EIGHT)
    s2 = ofcolor(I, TWO)
    ex8 = first(colorfilter(objects(I, True, False, True), EIGHT))
    is_vert = vline(ex8)
    rmin = uppermost(s8); rmax = lowermost(s8)
    cmin = leftmost(s8); cmax = rightmost(s8)
    gate = lambda p: combine(combine(neighbors(p), ineighbors(p)), initset(p))
    def near_or_both(p):
        r = uppermost(initset(p)); c = rightmost(initset(p))
        if is_vert:
            L = astuple(r, cmin); R = astuple(r, cmax)
            if equality(cmin, cmax): 
                return pair(initset(L), initset(connect(p, L)))
            dL = manhattan(initset(p), initset(L)); dR = manhattan(initset(p), initset(R))
            tie = equality(dL, dR)
            between = both(greater(c, cmin), greater(cmax, c))
            Cs = branch(either(tie, between), combine(initset(L), initset(R)), branch(greater(dL, dR), initset(R), initset(L)))
            Ws = merge(apply(lambda q: connect(p, q), Cs))
            return pair(Cs, Ws)
        else:
            U = astuple(rmin, c); D = astuple(rmax, c)
            if equality(rmin, rmax): 
                return pair(initset(U), initset(connect(p, U)))
            dU = manhattan(initset(p), initset(U)); dD = manhattan(initset(p), initset(D))
            tie = equality(dU, dD)
            between = both(greater(r, rmin), greater(rmax, r))
            Cs = branch(either(tie, between), combine(initset(U), initset(D)), branch(greater(dU, dD), initset(D), initset(U)))
            Ws = merge(apply(lambda q: connect(p, q), Cs))
            return pair(Cs, Ws)
    pairs = apply(near_or_both, s2)
    centers = merge(apply(first, pairs))
    wires = merge(apply(last, pairs))
    rings = merge(apply(gate, centers))
    O = fill(fill(fill(I, TWO, wires), EIGHT, rings), TWO, centers)
    return O
```