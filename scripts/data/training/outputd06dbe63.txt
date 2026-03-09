```python
def dsl1(I):
    s = first(totuple(ofcolor(I, EIGHT)))
    # centers along anti-diagonals by distance parity, then shift one toward the 8 horizontally
    up_odd = shift(shoot(add(s, UP_RIGHT), double(UP_RIGHT)), LEFT)                  # singles
    up_even = shift(difference(shoot(s, double(UP_RIGHT)), initset(s)), LEFT)        # triple centers
    dn_odd = shift(shoot(add(s, DOWN_LEFT), double(DOWN_LEFT)), RIGHT)               # singles
    dn_even = shift(difference(shoot(s, double(DOWN_LEFT)), initset(s)), RIGHT)      # triple centers
    tri_up = combine(up_even, combine(shift(up_even, LEFT), shift(up_even, RIGHT)))
    tri_dn = combine(dn_even, combine(shift(dn_even, LEFT), shift(dn_even, RIGHT)))
    p = combine(combine(up_odd, dn_odd), combine(tri_up, tri_dn))
    p = intersection(p, asindices(I))
    O = underpaint(I, recolor(FIVE, p))
    return O

def dsl2(I):
    s = first(totuple(ofcolor(I, EIGHT)))
    # direct offset-start method (no explicit shift): centers already biased toward the 8
    up_sing = shoot(add(s, UP), double(UP_RIGHT))                      # singles centers (rows: s+UP, s+UP+2*UR, ...)
    up_tri_c = shoot(add(add(s, UP), UP_RIGHT), double(UP_RIGHT))      # triple centers (rows between singles)
    dn_sing = shoot(add(s, DOWN), double(DOWN_LEFT))                   # singles centers
    dn_tri_c = shoot(add(add(s, DOWN), DOWN_LEFT), double(DOWN_LEFT))  # triple centers
    tri_up = combine(up_tri_c, combine(shift(up_tri_c, LEFT), shift(up_tri_c, RIGHT)))
    tri_dn = combine(dn_tri_c, combine(shift(dn_tri_c, LEFT), shift(dn_tri_c, RIGHT)))
    p = combine(combine(up_sing, dn_sing), combine(tri_up, tri_dn))
    p = intersection(p, asindices(I))
    O = underpaint(I, recolor(FIVE, p))
    return O

def dsl3(I):
    s = first(totuple(ofcolor(I, EIGHT)))
    # variant: build halves separately then merge
    # upper half
    u_s = shoot(add(s, UP), double(UP_RIGHT))
    u_c = shoot(add(add(s, UP), UP_RIGHT), double(UP_RIGHT))
    u_t = combine(u_c, combine(shift(u_c, LEFT), shift(u_c, RIGHT)))
    # lower half
    d_s = shoot(add(s, DOWN), double(DOWN_LEFT))
    d_c = shoot(add(add(s, DOWN), DOWN_LEFT), double(DOWN_LEFT))
    d_t = combine(d_c, combine(shift(d_c, LEFT), shift(d_c, RIGHT)))
    p = combine(combine(u_s, d_s), combine(u_t, d_t))
    p = intersection(p, asindices(I))
    O = underpaint(I, recolor(FIVE, p))
    return O

def dsl4(I):
    s = first(totuple(ofcolor(I, EIGHT)))
    # generate diagonal nodes first, then bias by one toward the 8 horizontally
    ur_all = difference(shoot(s, UP_RIGHT), initset(s))
    dl_all = difference(shoot(s, DOWN_LEFT), initset(s))
    # split by parity via two-phase stepping
    ur_odd = shoot(add(s, UP_RIGHT), double(UP_RIGHT))
    ur_even = difference(intersection(ur_all, shoot(s, double(UP_RIGHT))), initset(s))
    dl_odd = shoot(add(s, DOWN_LEFT), double(DOWN_LEFT))
    dl_even = difference(intersection(dl_all, shoot(s, double(DOWN_LEFT))), initset(s))
    # shift one toward 8 horizontally
    u_s = shift(ur_odd, LEFT)
    u_c = shift(ur_even, LEFT)
    d_s = shift(dl_odd, RIGHT)
    d_c = shift(dl_even, RIGHT)
    tri_u = combine(u_c, combine(shift(u_c, LEFT), shift(u_c, RIGHT)))
    tri_d = combine(d_c, combine(shift(d_c, LEFT), shift(d_c, RIGHT)))
    p = combine(combine(u_s, d_s), combine(tri_u, tri_d))
    p = intersection(p, asindices(I))
    O = underpaint(I, recolor(FIVE, p))
    return O

def dsl5(I):
    s = first(totuple(ofcolor(I, EIGHT)))
    # compact formulation: compute all four center streams, expand triples, merge
    streams = (
        shoot(add(s, UP), double(UP_RIGHT)),                       # up singles
        shoot(add(add(s, UP), UP_RIGHT), double(UP_RIGHT)),        # up triple centers
        shoot(add(s, DOWN), double(DOWN_LEFT)),                    # down singles
        shoot(add(add(s, DOWN), DOWN_LEFT), double(DOWN_LEFT))     # down triple centers
    )
    up_s, up_c, dn_s, dn_c = streams
    tri_up = combine(up_c, combine(shift(up_c, LEFT), shift(up_c, RIGHT)))
    tri_dn = combine(dn_c, combine(shift(dn_c, LEFT), shift(dn_c, RIGHT)))
    p = combine(combine(up_s, dn_s), combine(tri_up, tri_dn))
    p = intersection(p, asindices(I))
    O = underpaint(I, recolor(FIVE, p))
    return O
```