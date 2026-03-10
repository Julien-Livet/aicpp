```python
def dsl1(I):
    # Four-direction border projection:
    # - Top/bottom seeds project vertically inside H-interior (between 2s horizontally), blocked by 3s.
    # - Left/right seeds project horizontally inside V-interior (between 2s vertically), blocked by 3s.
    g = lbind(index, I)
    H = height(I)
    W = width(I)

    nz = compose(flip, matcher(g, ZERO))
    n2 = compose(flip, matcher(g, TWO))
    n3 = compose(flip, matcher(g, THREE))
    keepEdge = fork(both, nz, fork(both, n2, n3))

    # Borders
    top = hfrontier(astuple(ZERO, ZERO))
    bot = hfrontier(astuple(subtract(H, ONE), ZERO))
    lef = vfrontier(astuple(ZERO, ZERO))
    rig = vfrontier(astuple(ZERO, subtract(W, ONE)))

    topSeeds = sfilter(top, keepEdge)
    botSeeds = sfilter(bot, keepEdge)
    leftSeeds = sfilter(lef, keepEdge)
    rightSeeds = sfilter(rig, keepEdge)

    # Interiors from 2-walls
    twos = ofcolor(I, TWO)
    leftRays = mapply(rbind(shoot, LEFT), twos)
    rightRays = mapply(rbind(shoot, RIGHT), twos)
    interH = intersection(leftRays, rightRays)
    upRays = mapply(rbind(shoot, UP), twos)
    downRays = mapply(rbind(shoot, DOWN), twos)
    interV = intersection(upRays, downRays)

    # 3s as blockers
    threes = ofcolor(I, THREE)
    blockDown = mapply(rbind(shoot, DOWN), threes)
    blockUp = mapply(rbind(shoot, UP), threes)
    blockRight = mapply(rbind(shoot, RIGHT), threes)
    blockLeft = mapply(rbind(shoot, LEFT), threes)

    # Rays
    rayDown = rbind(shoot, DOWN)
    rayUp = rbind(shoot, UP)
    rayRight = rbind(shoot, RIGHT)
    rayLeft = rbind(shoot, LEFT)

    # Allowed sets
    topAllowed = compose(rbind(difference, blockDown), compose(lbind(intersection, interH), rayDown))
    botAllowed = compose(rbind(difference, blockUp), compose(lbind(intersection, interH), rayUp))
    leftAllowed = compose(rbind(difference, blockRight), compose(lbind(intersection, interV), rayRight))
    rightAllowed = compose(rbind(difference, blockLeft), compose(lbind(intersection, interV), rayLeft))

    makeT = fork(recolor, g, topAllowed)
    makeB = fork(recolor, g, botAllowed)
    makeL = fork(recolor, g, leftAllowed)
    makeR = fork(recolor, g, rightAllowed)

    objT = mapply(makeT, topSeeds)
    objB = mapply(makeB, botSeeds)
    objL = mapply(makeL, leftSeeds)
    objR = mapply(makeR, rightSeeds)
    obj = combine(combine(objT, objB), combine(objL, objR))

    O = underpaint(I, obj)
    return O


def dsl2(I):
    # Variant: project from all borders into the union of H- and V-interiors, blocked by 3s.
    g = lbind(index, I)
    H = height(I)
    W = width(I)

    nz = compose(flip, matcher(g, ZERO))
    n2 = compose(flip, matcher(g, TWO))
    n3 = compose(flip, matcher(g, THREE))
    keepEdge = fork(both, nz, fork(both, n2, n3))

    top = hfrontier(astuple(ZERO, ZERO))
    bot = hfrontier(astuple(subtract(H, ONE), ZERO))
    lef = vfrontier(astuple(ZERO, ZERO))
    rig = vfrontier(astuple(ZERO, subtract(W, ONE)))

    topSeeds = sfilter(top, keepEdge)
    botSeeds = sfilter(bot, keepEdge)
    leftSeeds = sfilter(lef, keepEdge)
    rightSeeds = sfilter(rig, keepEdge)

    twos = ofcolor(I, TWO)
    interH = intersection(mapply(rbind(shoot, LEFT), twos), mapply(rbind(shoot, RIGHT), twos))
    interV = intersection(mapply(rbind(shoot, UP), twos), mapply(rbind(shoot, DOWN), twos))
    interU = combine(interH, interV)

    threes = ofcolor(I, THREE)
    blockDown = mapply(rbind(shoot, DOWN), threes)
    blockUp = mapply(rbind(shoot, UP), threes)
    blockRight = mapply(rbind(shoot, RIGHT), threes)
    blockLeft = mapply(rbind(shoot, LEFT), threes)

    topAllowed = compose(rbind(difference, blockDown), compose(lbind(intersection, interU), rbind(shoot, DOWN)))
    botAllowed = compose(rbind(difference, blockUp), compose(lbind(intersection, interU), rbind(shoot, UP)))
    leftAllowed = compose(rbind(difference, blockRight), compose(lbind(intersection, interU), rbind(shoot, RIGHT)))
    rightAllowed = compose(rbind(difference, blockLeft), compose(lbind(intersection, interU), rbind(shoot, LEFT)))

    makeT = fork(recolor, g, topAllowed)
    makeB = fork(recolor, g, botAllowed)
    makeL = fork(recolor, g, leftAllowed)
    makeR = fork(recolor, g, rightAllowed)

    obj = combine(
        combine(mapply(makeT, topSeeds), mapply(makeB, botSeeds)),
        combine(mapply(makeL, leftSeeds), mapply(makeR, rightSeeds))
    )
    O = underpaint(I, obj)
    return O


def dsl3(I):
    # Horizontal-only: left/right border seeds project into V-interior, blocked by 3s.
    g = lbind(index, I)
    H = height(I)
    W = width(I)

    nz = compose(flip, matcher(g, ZERO))
    n2 = compose(flip, matcher(g, TWO))
    n3 = compose(flip, matcher(g, THREE))
    keepEdge = fork(both, nz, fork(both, n2, n3))

    lef = vfrontier(astuple(ZERO, ZERO))
    rig = vfrontier(astuple(ZERO, subtract(W, ONE)))
    leftSeeds = sfilter(lef, keepEdge)
    rightSeeds = sfilter(rig, keepEdge)

    twos = ofcolor(I, TWO)
    interV = intersection(mapply(rbind(shoot, UP), twos), mapply(rbind(shoot, DOWN), twos))

    threes = ofcolor(I, THREE)
    blockRight = mapply(rbind(shoot, RIGHT), threes)
    blockLeft = mapply(rbind(shoot, LEFT), threes)

    leftAllowed = compose(rbind(difference, blockRight), compose(lbind(intersection, interV), rbind(shoot, RIGHT)))
    rightAllowed = compose(rbind(difference, blockLeft), compose(lbind(intersection, interV), rbind(shoot, LEFT)))

    makeL = fork(recolor, g, leftAllowed)
    makeR = fork(recolor, g, rightAllowed)

    obj = combine(mapply(makeL, leftSeeds), mapply(makeR, rightSeeds))
    O = underpaint(I, obj)
    return O


def dsl4(I):
    # All borders into the strict core: intersection of H- and V-interiors, blocked by 3s.
    g = lbind(index, I)
    H = height(I)
    W = width(I)

    nz = compose(flip, matcher(g, ZERO))
    n2 = compose(flip, matcher(g, TWO))
    n3 = compose(flip, matcher(g, THREE))
    keepEdge = fork(both, nz, fork(both, n2, n3))

    top = hfrontier(astuple(ZERO, ZERO))
    bot = hfrontier(astuple(subtract(H, ONE), ZERO))
    lef = vfrontier(astuple(ZERO, ZERO))
    rig = vfrontier(astuple(ZERO, subtract(W, ONE)))

    topSeeds = sfilter(top, keepEdge)
    botSeeds = sfilter(bot, keepEdge)
    leftSeeds = sfilter(lef, keepEdge)
    rightSeeds = sfilter(rig, keepEdge)

    twos = ofcolor(I, TWO)
    interH = intersection(mapply(rbind(shoot, LEFT), twos), mapply(rbind(shoot, RIGHT), twos))
    interV = intersection(mapply(rbind(shoot, UP), twos), mapply(rbind(shoot, DOWN), twos))
    interBoth = intersection(interH, interV)

    threes = ofcolor(I, THREE)
    blockDown = mapply(rbind(shoot, DOWN), threes)
    blockUp = mapply(rbind(shoot, UP), threes)
    blockRight = mapply(rbind(shoot, RIGHT), threes)
    blockLeft = mapply(rbind(shoot, LEFT), threes)

    topAllowed = compose(rbind(difference, blockDown), compose(lbind(intersection, interBoth), rbind(shoot, DOWN)))
    botAllowed = compose(rbind(difference, blockUp), compose(lbind(intersection, interBoth), rbind(shoot, UP)))
    leftAllowed = compose(rbind(difference, blockRight), compose(lbind(intersection, interBoth), rbind(shoot, RIGHT)))
    rightAllowed = compose(rbind(difference, blockLeft), compose(lbind(intersection, interBoth), rbind(shoot, LEFT)))

    makeT = fork(recolor, g, topAllowed)
    makeB = fork(recolor, g, botAllowed)
    makeL = fork(recolor, g, leftAllowed)
    makeR = fork(recolor, g, rightAllowed)

    obj = combine(
        combine(mapply(makeT, topSeeds), mapply(makeB, botSeeds)),
        combine(mapply(makeL, leftSeeds), mapply(makeR, rightSeeds))
    )
    O = underpaint(I, obj)
    return O


def dsl5(I):
    # Two-phase:
    # 1) Vertical from top/bottom into H-interior, blocked by 3s.
    # 2) From all nonzero non-2 non-3 seeds (including left/right borders and interior),
    #    spread horizontally into V-interior, blocked by 3s.
    g = lbind(index, I)
    H = height(I)
    W = width(I)

    nz = compose(flip, matcher(g, ZERO))
    n2 = compose(flip, matcher(g, TWO))
    n3 = compose(flip, matcher(g, THREE))
    keepEdge = fork(both, nz, fork(both, n2, n3))

    top = hfrontier(astuple(ZERO, ZERO))
    bot = hfrontier(astuple(subtract(H, ONE), ZERO))
    topSeeds = sfilter(top, keepEdge)
    botSeeds = sfilter(bot, keepEdge)

    twos = ofcolor(I, TWO)
    interH = intersection(mapply(rbind(shoot, LEFT), twos), mapply(rbind(shoot, RIGHT), twos))
    interV = intersection(mapply(rbind(shoot, UP), twos), mapply(rbind(shoot, DOWN), twos))

    threes = ofcolor(I, THREE)
    blockDown = mapply(rbind(shoot, DOWN), threes)
    blockUp = mapply(rbind(shoot, UP), threes)
    blockRight = mapply(rbind(shoot, RIGHT), threes)
    blockLeft = mapply(rbind(shoot, LEFT), threes)

    topAllowed = compose(rbind(difference, blockDown), compose(lbind(intersection, interH), rbind(shoot, DOWN)))
    botAllowed = compose(rbind(difference, blockUp), compose(lbind(intersection, interH), rbind(shoot, UP)))
    makeT = fork(recolor, g, topAllowed)
    makeB = fork(recolor, g, botAllowed)

    objV = combine(mapply(makeT, topSeeds), mapply(makeB, botSeeds))
    J = underpaint(I, objV)

    # Phase 2: horizontal spread from any valid seed in updated grid
    g2 = lbind(index, J)
    nz2 = compose(flip, matcher(g2, ZERO))
    n2_2 = compose(flip, matcher(g2, TWO))
    n3_2 = compose(flip, matcher(g2, THREE))
    keepAny = fork(both, nz2, fork(both, n2_2, n3_2))

    seedsAll = sfilter(asindices(J), keepAny)

    rightAllowedAny = compose(rbind(difference, blockRight), compose(lbind(intersection, interV), rbind(shoot, RIGHT)))
    leftAllowedAny = compose(rbind(difference, blockLeft), compose(lbind(intersection, interV), rbind(shoot, LEFT)))

    makeR2 = fork(recolor, g2, rightAllowedAny)
    makeL2 = fork(recolor, g2, leftAllowedAny)

    objH = combine(mapply(makeR2, seedsAll), mapply(makeL2, seedsAll))

    O = underpaint(J, objH)
    return O
```