```python
def dsl1(I):
    # Orientation-adaptive periodic fill with bounding when endpoint colors differ.
    H, W = height(I), width(I)
    row_pairs = 0
    col_pairs = 0
    for i in range(H):
        js = []
        for j in range(W):
            if index(I, astuple(i, j)) != ZERO:
                js.append(j)
        if len(js) >= 2:
            row_pairs += 1
    for j in range(W):
        is_ = []
        for i in range(H):
            if index(I, astuple(i, j)) != ZERO:
                is_.append(i)
        if len(is_) >= 2:
            col_pairs += 1

    O = I
    if col_pairs > row_pairs:
        # Column mode: minimal-gap periodic fill, using bottommost color, bounded to bottommost if colors differ
        for j in range(W):
            is_ = []
            for i in range(H):
                if index(I, astuple(i, j)) != ZERO:
                    is_.append(i)
            if len(is_) < 2:
                continue
            is_.sort()
            best_p = None
            i0 = None
            for k in range(len(is_) - 1):
                p = is_[k+1] - is_[k]
                if (best_p is None) or (p < best_p):
                    best_p = p
                    i0 = is_[k]
            if best_p is None or best_p <= 0:
                continue
            i_last = is_[-1]
            c0 = index(I, astuple(i0, j))
            cfill = index(I, astuple(i_last, j))
            bounded = (c0 != cfill)
            patch = set()
            for i in range(H):
                if ((i - i0) % best_p) == 0:
                    if (not bounded) or (i <= i_last):
                        patch.add(astuple(i, j))
            if patch:
                O = fill(O, cfill, frozenset(patch))
    else:
        # Row mode: minimal-gap periodic fill, using rightmost color, bounded to rightmost if colors differ
        for i in range(H):
            js = []
            for j in range(W):
                if index(I, astuple(i, j)) != ZERO:
                    js.append(j)
            if len(js) < 2:
                continue
            js.sort()
            best_p = None
            j0 = None
            for k in range(len(js) - 1):
                p = js[k+1] - js[k]
                if (best_p is None) or (p < best_p):
                    best_p = p
                    j0 = js[k]
            if best_p is None or best_p <= 0:
                continue
            j_last = js[-1]
            c0 = index(I, astuple(i, j0))
            cfill = index(I, astuple(i, j_last))
            bounded = (c0 != cfill)
            patch = set()
            for j in range(W):
                if ((j - j0) % best_p) == 0:
                    if (not bounded) or (j <= j_last):
                        patch.add(astuple(i, j))
            if patch:
                O = fill(O, cfill, frozenset(patch))
    return O

def dsl2(I):
    # Dual-direction later-anchor fill on rows and columns; overlay columns after rows
    H, W = height(I), width(I)
    O = I
    # Row pass: use later anchor of min-gap pair; fill rightward
    for i in range(H):
        js = []
        for j in range(W):
            if index(I, astuple(i, j)) != ZERO:
                js.append(j)
        if len(js) < 2:
            continue
        js.sort()
        best_p = None
        j1 = None
        for k in range(len(js) - 1):
            p = js[k+1] - js[k]
            if (best_p is None) or (p < best_p):
                best_p = p
                j1 = js[k+1]
        if best_p is None or best_p <= 0:
            continue
        cfill = index(I, astuple(i, j1))
        patch = set()
        j = j1
        while j < W:
            patch.add(astuple(i, j))
            j += best_p
        if patch:
            O = fill(O, cfill, frozenset(patch))
    # Column pass: later anchor; fill downward; columns override
    for j in range(W):
        is_ = []
        for i in range(H):
            if index(I, astuple(i, j)) != ZERO:
                is_.append(i)
        if len(is_) < 2:
            continue
        is_.sort()
        best_p = None
        i1 = None
        for k in range(len(is_) - 1):
            p = is_[k+1] - is_[k]
            if (best_p is None) or (p < best_p):
                best_p = p
                i1 = is_[k+1]
        if best_p is None or best_p <= 0:
            continue
        cfill = index(I, astuple(i1, j))
        patch = set()
        i = i1
        while i < H:
            patch.add(astuple(i, j))
            i += best_p
        if patch:
            O = fill(O, cfill, frozenset(patch))
    return O

def dsl3(I):
    # Two-pass overlay: row min-gap with rightmost bounded; then column min-gap with bottommost full-height
    H, W = height(I), width(I)
    O = I
    # Row pass
    for i in range(H):
        js = []
        for j in range(W):
            if index(I, astuple(i, j)) != ZERO:
                js.append(j)
        if len(js) < 2:
            continue
        js.sort()
        best_p = None
        j0 = None
        for k in range(len(js) - 1):
            p = js[k+1] - js[k]
            if (best_p is None) or (p < best_p):
                best_p = p
                j0 = js[k]
        if best_p is None or best_p <= 0:
            continue
        j_last = js[-1]
        c0 = index(I, astuple(i, j0))
        cfill = index(I, astuple(i, j_last))
        bounded = (c0 != cfill)
        patch = set()
        for j in range(W):
            if ((j - j0) % best_p) == 0:
                if (not bounded) or (j <= j_last):
                    patch.add(astuple(i, j))
        if patch:
            O = fill(O, cfill, frozenset(patch))
    # Column pass (overrides rows)
    for j in range(W):
        is_ = []
        for i in range(H):
            if index(I, astuple(i, j)) != ZERO:
                is_.append(i)
        if len(is_) < 2:
            continue
        is_.sort()
        best_p = None
        i0 = None
        for k in range(len(is_) - 1):
            p = is_[k+1] - is_[k]
            if (best_p is None) or (p < best_p):
                best_p = p
                i0 = is_[k]
        if best_p is None or best_p <= 0:
            continue
        i_bot = is_[-1]
        cfill = index(I, astuple(i_bot, j))
        patch = set()
        for i in range(H):
            if ((i - i0) % best_p) == 0:
                patch.add(astuple(i, j))
        if patch:
            O = fill(O, cfill, frozenset(patch))
    return O

def dsl4(I):
    # GCD-based periodic extension with adaptive orientation and bounding to the extreme anchor if colors differ
    def _gcd(a, b):
        while b:
            a, b = b, a % b
        return a if a is not None else 0

    H, W = height(I), width(I)
    row_pairs = 0
    col_pairs = 0
    for i in range(H):
        js = []
        for j in range(W):
            if index(I, astuple(i, j)) != ZERO:
                js.append(j)
        if len(js) >= 2:
            row_pairs += 1
    for j in range(W):
        is_ = []
        for i in range(H):
            if index(I, astuple(i, j)) != ZERO:
                is_.append(i)
        if len(is_) >= 2:
            col_pairs += 1

    O = I
    if col_pairs > row_pairs:
        # Column mode
        for j in range(W):
            is_ = []
            for i in range(H):
                if index(I, astuple(i, j)) != ZERO:
                    is_.append(i)
            if len(is_) < 2:
                continue
            is_.sort()
            p = 0
            for k in range(len(is_) - 1):
                d = is_[k+1] - is_[k]
                p = d if p == 0 else _gcd(p, d)
            if p <= 0:
                continue
            i_ref = is_[-1]
            cfill = index(I, astuple(i_ref, j))
            cfirst = index(I, astuple(is_[0], j))
            bounded = (cfirst != cfill)
            patch = set()
            for i in range(H):
                if ((i - i_ref) % p) == 0:
                    if (not bounded) or (i <= i_ref):
                        patch.add(astuple(i, j))
            if patch:
                O = fill(O, cfill, frozenset(patch))
    else:
        # Row mode
        for i in range(H):
            js = []
            for j in range(W):
                if index(I, astuple(i, j)) != ZERO:
                    js.append(j)
            if len(js) < 2:
                continue
            js.sort()
            p = 0
            for k in range(len(js) - 1):
                d = js[k+1] - js[k]
                p = d if p == 0 else _gcd(p, d)
            if p <= 0:
                continue
            j_ref = js[-1]
            cfill = index(I, astuple(i, j_ref))
            cfirst = index(I, astuple(i, js[0]))
            bounded = (cfirst != cfill)
            patch = set()
            for j in range(W):
                if ((j - j_ref) % p) == 0:
                    if (not bounded) or (j <= j_ref):
                        patch.add(astuple(i, j))
            if patch:
                O = fill(O, cfill, frozenset(patch))
    return O

def dsl5(I):
    # Color-specific minimal-period per line; choose the most periodic color; adaptive orientation
    H, W = height(I), width(I)
    row_pairs = 0
    col_pairs = 0
    for i in range(H):
        js = []
        for j in range(W):
            if index(I, astuple(i, j)) != ZERO:
                js.append(j)
        if len(js) >= 2:
            row_pairs += 1
    for j in range(W):
        is_ = []
        for i in range(H):
            if index(I, astuple(i, j)) != ZERO:
                is_.append(i)
        if len(is_) >= 2:
            col_pairs += 1

    O = I
    if row_pairs >= col_pairs:
        # Row-focused
        for i in range(H):
            color_pos = {}
            all_js = []
            for j in range(W):
                v = index(I, astuple(i, j))
                if v != ZERO:
                    all_js.append(j)
                    color_pos.setdefault(v, []).append(j)
            best = None  # (p, rightmost, color, firstpos)
            for c, pos in color_pos.items():
                if len(pos) >= 2:
                    pos.sort()
                    p = None
                    for k in range(len(pos) - 1):
                        d = pos[k+1] - pos[k]
                        if (p is None) or (d < p):
                            p = d
                    cand = (p, pos[-1], c, pos[0])
                    if (best is None) or (p < best[0]) or (p == best[0] and pos[-1] > best[1]):
                        best = cand
            if best is None:
                # Fallback: use all marks min-gap with rightmost color, bounded
                if len(all_js) < 2:
                    continue
                all_js.sort()
                p = None
                j0 = None
                for k in range(len(all_js) - 1):
                    d = all_js[k+1] - all_js[k]
                    if (p is None) or (d < p):
                        p = d
                        j0 = all_js[k]
                j_last = all_js[-1]
                cfill = index(I, astuple(i, j_last))
                cstart = index(I, astuple(i, j0))
                bounded = (cfill != cstart)
                patch = set()
                for j in range(W):
                    if ((j - j0) % p) == 0 and ((not bounded) or (j <= j_last)):
                        patch.add(astuple(i, j))
                if patch:
                    O = fill(O, cfill, frozenset(patch))
            else:
                p, j_ref, cfill, j_first = best
                if p is None or p <= 0:
                    continue
                # Fill leftward from rightmost occurrence (bounded to the rightmost)
                patch = set()
                j = j_ref
                while j >= 0:
                    patch.add(astuple(i, j))
                    j -= p
                if patch:
                    O = fill(O, cfill, frozenset(patch))
    else:
        # Column-focused
        for j in range(W):
            color_pos = {}
            all_is = []
            for i in range(H):
                v = index(I, astuple(i, j))
                if v != ZERO:
                    all_is.append(i)
                    color_pos.setdefault(v, []).append(i)
            best = None  # (p, bottommost, color)
            for c, pos in color_pos.items():
                if len(pos) >= 2:
                    pos.sort()
                    p = None
                    for k in range(len(pos) - 1):
                        d = pos[k+1] - pos[k]
                        if (p is None) or (d < p):
                            p = d
                    cand = (p, pos[-1], c)
                    if (best is None) or (p < best[0]) or (p == best[0] and pos[-1] > best[1]):
                        best = cand
            if best is None:
                if len(all_is) < 2:
                    continue
                all_is.sort()
                p = None
                i0 = None
                for k in range(len(all_is) - 1):
                    d = all_is[k+1] - all_is[k]
                    if (p is None) or (d < p):
                        p = d
                        i0 = all_is[k]
                i_last = all_is[-1]
                cfill = index(I, astuple(i_last, j))
                cstart = index(I, astuple(i0, j))
                bounded = (cfill != cstart)
                patch = set()
                for i in range(H):
                    if ((i - i0) % p) == 0 and ((not bounded) or (i <= i_last)):
                        patch.add(astuple(i, j))
                if patch:
                    O = fill(O, cfill, frozenset(patch))
            else:
                p, i_ref, cfill = best
                if p is None or p <= 0:
                    continue
                # Fill upward from bottommost occurrence (bounded to bottommost)
                patch = set()
                i = i_ref
                while i >= 0:
                    patch.add(astuple(i, j))
                    i -= p
                if patch:
                    O = fill(O, cfill, frozenset(patch))
    return O
```