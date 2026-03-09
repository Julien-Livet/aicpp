```python
def dsl1(I):
    # Iterative alternating propagation downwards:
    # +2 rows: place SIX at columns where source row has THREE flanked by SEVENs
    # +4 rows: place SEVEN at columns where source row has SEVEN flanked by THREEs (both in previous THREE-set)
    # +6 rows: repeat alternation until set becomes empty or bottom reached
    H = height(I)
    W = width(I)
    O = I
    idx7 = ofcolor(I, SEVEN)
    if size(idx7) == 0:
        return O
    rsrc = minimum(apply(lambda x: x[0], idx7))
    # initial set of 7-columns in source row
    S = set([j for (i, j) in idx7 if i == rsrc])
    if len(S) == 0:
        return O
    offset = 2
    # step 1: from 7-set to 3-set (A)
    while True:
        if rsrc + offset >= H:
            break
        # from S -> A (THREE positions between two 7s)
        A = set()
        for j in range(W):
            if j-1 in S and j+1 in S and index(I, (rsrc, j)) == THREE:
                A.add(j)
        if len(A) == 0:
            break
        patchA = frozenset({(rsrc + offset, j) for j in A})
        O = fill(O, SIX, patchA)
        offset += 2
        if rsrc + offset >= H:
            break
        # from A -> S (SEVEN positions between two THREEs of A)
        S2 = set()
        for j in range(W):
            if j-1 in A and j+1 in A and index(I, (rsrc, j)) == SEVEN:
                S2.add(j)
        if len(S2) == 0:
            break
        patchS2 = frozenset({(rsrc + offset, j) for j in S2})
        O = fill(O, SEVEN, patchS2)
        S = S2
        offset += 2
    return O

def dsl2(I):
    # One full cycle only: +2 SIX for internal THREEs, +4 SEVEN for isolated SEVENs
    H = height(I)
    W = width(I)
    O = I
    idx7 = ofcolor(I, SEVEN)
    if size(idx7) == 0:
        return O
    rsrc = minimum(apply(lambda x: x[0], idx7))
    S = set([j for (i, j) in idx7 if i == rsrc])
    if len(S) == 0:
        return O
    # A1
    A1 = set()
    for j in range(W):
        if j-1 in S and j+1 in S and index(I, (rsrc, j)) == THREE:
            A1.add(j)
    if len(A1) > 0 and rsrc + 2 < H:
        O = fill(O, SIX, frozenset({(rsrc + 2, j) for j in A1}))
    # S1
    S1 = set()
    for j in range(W):
        if j-1 in A1 and j+1 in A1 and index(I, (rsrc, j)) == SEVEN:
            S1.add(j)
    if len(S1) > 0 and rsrc + 4 < H:
        O = fill(O, SEVEN, frozenset({(rsrc + 4, j) for j in S1}))
    return O

def dsl3(I):
    # Only first layer: +2 SIX at positions of THREE flanked by SEVENs in source row
    H = height(I)
    W = width(I)
    O = I
    idx7 = ofcolor(I, SEVEN)
    if size(idx7) == 0:
        return O
    rsrc = minimum(apply(lambda x: x[0], idx7))
    S = set([j for (i, j) in idx7 if i == rsrc])
    if len(S) == 0 or rsrc + 2 >= H:
        return O
    A = set()
    for j in range(W):
        if j-1 in S and j+1 in S and index(I, (rsrc, j)) == THREE:
            A.add(j)
    if len(A) > 0:
        O = fill(O, SIX, frozenset({(rsrc + 2, j) for j in A}))
    return O

def dsl4(I):
    # Full iterative like dsl1 but ensures we never overwrite non-background and stops earlier if needed
    H = height(I)
    W = width(I)
    O = I
    idx7 = ofcolor(I, SEVEN)
    if size(idx7) == 0:
        return O
    rsrc = minimum(apply(lambda x: x[0], idx7))
    S = set([j for (i, j) in idx7 if i == rsrc])
    if not S:
        return O
    offset = 2
    while True:
        if rsrc + offset >= H:
            break
        # A from S
        A = set()
        for j in range(W):
            if j-1 in S and j+1 in S and index(I, (rsrc, j)) == THREE:
                A.add(j)
        if not A:
            break
        patchA = frozenset({(rsrc + offset, j) for j in A if index(O, (rsrc + offset, j)) == THREE})
        if size(patchA) > 0:
            O = fill(O, SIX, patchA)
        offset += 2
        if rsrc + offset >= H:
            break
        # S' from A
        S2 = set()
        for j in range(W):
            if j-1 in A and j+1 in A and index(I, (rsrc, j)) == SEVEN:
                S2.add(j)
        if not S2:
            break
        patchS2 = frozenset({(rsrc + offset, j) for j in S2 if index(O, (rsrc + offset, j)) == THREE})
        if size(patchS2) > 0:
            O = fill(O, SEVEN, patchS2)
        S = S2
        offset += 2
    return O

def dsl5(I):
    # Two-and-a-half layers: +2 SIX (A1), +4 SEVEN (S1), +6 SIX (A2) if possible
    H = height(I)
    W = width(I)
    O = I
    idx7 = ofcolor(I, SEVEN)
    if size(idx7) == 0:
        return O
    rsrc = minimum(apply(lambda x: x[0], idx7))
    S0 = set([j for (i, j) in idx7 if i == rsrc])
    if not S0:
        return O
    # A1
    A1 = set()
    for j in range(W):
        if j-1 in S0 and j+1 in S0 and index(I, (rsrc, j)) == THREE:
            A1.add(j)
    if A1 and rsrc + 2 < H:
        O = fill(O, SIX, frozenset({(rsrc + 2, j) for j in A1}))
    # S1
    S1 = set()
    for j in range(W):
        if j-1 in A1 and j+1 in A1 and index(I, (rsrc, j)) == SEVEN:
            S1.add(j)
    if S1 and rsrc + 4 < H:
        O = fill(O, SEVEN, frozenset({(rsrc + 4, j) for j in S1}))
    # A2
    A2 = set()
    for j in range(W):
        if j-1 in S1 and j+1 in S1 and index(I, (rsrc, j)) == THREE:
            A2.add(j)
    if A2 and rsrc + 6 < H:
        O = fill(O, SIX, frozenset({(rsrc + 6, j) for j in A2}))
    return O
```