```python
def dsl1(I):
    # Keep only ONEs that touch a non-ONE non-zero; then insert ONEs in immediate A-0-A sandwiches (h/v).
    h = height(I)
    w = width(I)
    O = [list(row) for row in I]
    # Step 1: prune ONEs not adjacent (4-neigh) to any non-ONE non-zero
    for i in range(h):
        for j in range(w):
            if O[i][j] != ONE:
                continue
            keep = False
            for di, dj in ((1,0),(-1,0),(0,1),(0,-1)):
                ii, jj = i+di, j+dj
                if 0 <= ii < h and 0 <= jj < w:
                    v = index(I, (ii, jj))
                    if v != ZERO and v != ONE:
                        keep = True
                        break
            if not keep:
                O[i][j] = ZERO
    # Step 2: immediate horizontal/vertical sandwich fill
    for i in range(h):
        for j in range(w):
            if O[i][j] != ZERO:
                continue
            # horizontal immediate
            if 0 < j < w-1:
                L = index(I, (i, j-1))
                R = index(I, (i, j+1))
                if L == R and L != ZERO and L != ONE:
                    O[i][j] = ONE
                    continue
            # vertical immediate
            if 0 < i < h-1:
                U = index(I, (i-1, j))
                D = index(I, (i+1, j))
                if U == D and U != ZERO and U != ONE:
                    O[i][j] = ONE
    return tuple(tuple(row) for row in O)

def dsl2(I):
    # Remove all ONEs; then only fill zeros that are in immediate horizontal A-0-A sandwiches.
    h = height(I)
    w = width(I)
    O = [list(row) for row in I]
    for i in range(h):
        for j in range(w):
            if O[i][j] == ONE:
                O[i][j] = ZERO
    for i in range(h):
        for j in range(1, w-1):
            if O[i][j] != ZERO:
                continue
            L = index(I, (i, j-1))
            R = index(I, (i, j+1))
            if L == R and L != ZERO and L != ONE:
                O[i][j] = ONE
    return tuple(tuple(row) for row in O)

def dsl3(I):
    # Gate row-wise gap fill: remove ONEs; activate rows where any ONE is 4-neigh to a non-ONE in this or adjacent rows;
    # then fill zeros between leftmost and rightmost non-zero with ONE (preserving existing non-zero colors).
    h = height(I)
    w = width(I)
    base = [list(row) for row in I]
    # remove ONEs
    for i in range(h):
        for j in range(w):
            if base[i][j] == ONE:
                base[i][j] = ZERO
    # find active rows
    active = [False]*h
    for i in range(h):
        for j in range(w):
            if index(I, (i, j)) != ONE:
                continue
            for di, dj in ((1,0),(-1,0),(0,1),(0,-1)):
                ii, jj = i+di, j+dj
                if 0 <= ii < h and 0 <= jj < w:
                    v = index(I, (ii, jj))
                    if v != ZERO and v != ONE:
                        active[i] = True
                        break
            if active[i]:
                continue
        # also inherit activation from immediate neighbors if they host ONE touching non-ONE
    # perform gated fill
    O = [row[:] for row in base]
    for i in range(h):
        if not active[i]:
            continue
        left = None
        right = None
        for j in range(w):
            if index(I, (i, j)) != ZERO:
                left = j
                break
        for j in range(w-1, -1, -1):
            if index(I, (i, j)) != ZERO:
                right = j
                break
        if left is None or right is None or right - left <= 1:
            continue
        for j in range(left+1, right):
            if O[i][j] == ZERO:
                O[i][j] = ONE
    return tuple(tuple(row) for row in O)

def dsl4(I):
    # Keep ONEs only if they touch a non-ONE on the left or above; remove others; then do immediate horizontal sandwich fill.
    h = height(I)
    w = width(I)
    O = [list(row) for row in I]
    for i in range(h):
        for j in range(w):
            if O[i][j] != ONE:
                continue
            keep = False
            # left neighbor
            if j-1 >= 0:
                v = index(I, (i, j-1))
                if v != ZERO and v != ONE:
                    keep = True
            # above neighbor
            if not keep and i-1 >= 0:
                v = index(I, (i-1, j))
                if v != ZERO and v != ONE:
                    keep = True
            if not keep:
                O[i][j] = ZERO
    # horizontal immediate A-0-A fill
    for i in range(h):
        for j in range(1, w-1):
            if O[i][j] != ZERO:
                continue
            L = index(I, (i, j-1))
            R = index(I, (i, j+1))
            if L == R and L != ZERO and L != ONE:
                O[i][j] = ONE
    return tuple(tuple(row) for row in O)

def dsl5(I):
    # Connectivity-based pruning: keep only ONEs reachable from any non-ONE via paths stepping through ONEs; then immediate sandwich fill.
    h = height(I)
    w = width(I)
    from collections import deque
    # mark reachable ONEs by BFS starting from all non-ONE non-zero cells
    reach = [[False]*w for _ in range(h)]
    q = deque()
    for i in range(h):
        for j in range(w):
            v = index(I, (i, j))
            if v != ZERO and v != ONE:
                reach[i][j] = True
                q.append((i, j))
    while q:
        i, j = q.popleft()
        for di, dj in ((1,0),(-1,0),(0,1),(0,-1)):
            ii, jj = i+di, j+dj
            if 0 <= ii < h and 0 <= jj < w and not reach[ii][jj]:
                if index(I, (ii, jj)) == ONE:
                    reach[ii][jj] = True
                    q.append((ii, jj))
    O = [list(row) for row in I]
    # prune ONEs not reachable
    for i in range(h):
        for j in range(w):
            if O[i][j] == ONE and not reach[i][j]:
                O[i][j] = ZERO
    # immediate horizontal/vertical A-0-A sandwich fill
    for i in range(h):
        for j in range(w):
            if O[i][j] != ZERO:
                continue
            if 0 < j < w-1:
                L = index(I, (i, j-1))
                R = index(I, (i, j+1))
                if L == R and L != ZERO and L != ONE:
                    O[i][j] = ONE
                    continue
            if 0 < i < h-1:
                U = index(I, (i-1, j))
                D = index(I, (i+1, j))
                if U == D and U != ZERO and U != ONE:
                    O[i][j] = ONE
    return tuple(tuple(row) for row in O)
```