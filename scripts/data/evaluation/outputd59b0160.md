```python
def dsl1(I):
    # Keep cells if their column is non-7 in the bottom row OR their row is non-7 in the rightmost column; else set to 7
    h, w = shape(I)
    keep_cols = {j for j in range(w) if I[h-1][j] != SEVEN}
    keep_rows = {i for i in range(h) if I[i][w-1] != SEVEN}
    O = [list(row) for row in I]
    for i in range(h):
        for j in range(w):
            if (j not in keep_cols) and (i not in keep_rows):
                O[i][j] = SEVEN
    return tuple(tuple(r) for r in O)

def dsl2(I):
    # Keep only the union of the top band up to the last row containing a 3 and the left band up to the last column containing a 3
    h, w = shape(I)
    rmax = -1
    cmax = -1
    for i in range(h):
        for j in range(w):
            if I[i][j] == THREE:
                if i > rmax:
                    rmax = i
                if j > cmax:
                    cmax = j
    if rmax == -1 and cmax == -1:
        return I
    O = []
    for i in range(h):
        row = []
        for j in range(w):
            if i <= rmax or j <= cmax:
                row.append(I[i][j])
            else:
                row.append(SEVEN)
        O.append(tuple(row))
    return tuple(O)

def dsl3(I):
    # For each row, clear everything strictly after the last 7 in that row
    h, w = shape(I)
    O = []
    for i in range(h):
        row = list(I[i])
        last7 = -1
        for j in range(w):
            if row[j] == SEVEN:
                last7 = j
        if last7 < w - 1:
            for j in range(last7 + 1, w):
                row[j] = SEVEN
        O.append(tuple(row))
    return tuple(O)

def dsl4(I):
    # For each row, keep only the first contiguous non-7 run; clear later non-7 runs to 7
    h, w = shape(I)
    O = []
    for i in range(h):
        row = list(I[i])
        started = False
        ended = False
        for j in range(w):
            if not started:
                if row[j] != SEVEN:
                    started = True
            else:
                if not ended:
                    if row[j] == SEVEN:
                        ended = True
                else:
                    if row[j] != SEVEN:
                        row[j] = SEVEN
        O.append(tuple(row))
    return tuple(O)

def dsl5(I):
    # For each row, keep only the rightmost contiguous non-7 run; clear earlier non-7 runs to 7
    h, w = shape(I)
    O = []
    for i in range(h):
        row = list(I[i])
        # find rightmost run [a..b] of non-7
        a = b = -1
        j = w - 1
        while j >= 0:
            if row[j] != SEVEN:
                b = j
                while j >= 0 and row[j] != SEVEN:
                    j -= 1
                a = j + 1
                break
            j -= 1
        if a != -1:
            # clear all non-7 outside [a..b]
            for j in range(0, a):
                if row[j] != SEVEN:
                    row[j] = SEVEN
            for j in range(b + 1, w):
                if row[j] != SEVEN:
                    row[j] = SEVEN
        else:
            # no non-7: row remains as is
            pass
        O.append(tuple(row))
    return tuple(O)
```