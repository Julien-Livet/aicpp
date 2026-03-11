```python
def dsl1(I):
    A = hconcat(I, I)
    AA = hconcat(A, A)
    B = vconcat(AA, AA)
    O = crop(B, ORIGIN, (20, 20))
    return O

def dsl2(I):
    T = hconcat(I, vmirror(I))
    U = vconcat(T, hmirror(T))
    V = vconcat(U, hmirror(U))
    O = crop(V, ORIGIN, (20, 20))
    return O

def dsl3(I):
    A = hconcat(I, rot90(I))
    B = hconcat(rot270(I), rot180(I))
    C = vconcat(A, B)
    D = hconcat(C, C)
    E = vconcat(D, D)
    O = crop(E, ORIGIN, (20, 20))
    return O

def dsl4(I):
    S = upscale(I, TWO)
    A = hconcat(S, vmirror(S))
    B = vconcat(A, hmirror(A))
    O = crop(B, ORIGIN, (20, 20))
    return O

def dsl5(I):
    D = dmirror(I)
    A = hconcat(I, D)
    B = vconcat(A, vmirror(A))
    C = vconcat(B, hmirror(B))
    O = crop(C, ORIGIN, (20, 20))
    return O
```